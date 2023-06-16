import logging
import torch
from tqdm import tqdm
import config
from torch import nn

from utils import f1_score

def train(train_dataloader,test_dataloader, model, optimizer, scheduler,enable_cuda):
    best_f1=0
    patience=0
    # 开始训练
    for epoch in range(config.max_epoch):
        # 训练
        train_epoch(train_dataloader, model, optimizer, scheduler, epoch, enable_cuda)
        # 验证
        result = evaluate(test_dataloader, model, enable_cuda)
        logging.info(
            "Epoch: {}, test loss: {}, fscore: {}, percision: {},recall: {}".format(epoch, result['loss'],
                                                                                    result['f'],
                                                                                    result['p'], result['r']))
        f1 = result['f']
        improve = f1 - best_f1
        if improve > 1e-5:
            best_f1 = f1
            model.save_pretrained(config.BEST_MODEL_DIR)
            if improve < config.patience:
                patience += 1
            else:
                patience = 0
        else:
            patience += 1
        if (patience >= config.patience and epoch > config.min_epoch) or epoch == config.max_epoch:
            break
        # 保存模型
        # torch.save(model, config.MODEL_PREFIX + str(epoch) + ".pkl")

def train_epoch(train_dataloader, model, optimizer, scheduler, epoch, enable_cuda):
    """
    进行一轮训练
    :param train_dataloader: 数据
    :param model: 模型
    :param optimizer: 优化器
    :param scheduler: 学习率预热
    :param epoch: 轮数
    :param enable_cuda: 是否使用cuda
    """
    torch.cuda.empty_cache()
    logging.info("Epoch: {} start...".format(epoch))
    model.train()
    train_losses = 0
    for idx, batch_samples in enumerate(train_dataloader):
        # 获取数据
        batch_data, batch_token_starts, batch_labels, _ = batch_samples
        # 是否使用cuda
        if enable_cuda:
            batch_data = batch_data.cuda()
            batch_token_starts = batch_token_starts.cuda()
            batch_labels = batch_labels.cuda()
        # 获取mask
        batch_masks = batch_data.gt(0)
        # 模型预测
        loss = model((batch_data, batch_token_starts),
                     token_type_ids=None, attention_mask=batch_masks, labels=batch_labels)[0]
        # 计算损失
        train_losses += loss.item()
        # 梯度清零
        model.zero_grad()
        # 反向传播
        loss.backward()
        # 梯度裁剪
        nn.utils.clip_grad_norm_(parameters=model.parameters(), max_norm=config.clip_grad)
        # 更新参数
        optimizer.step()
        # 更新学习率
        scheduler.step()
        if idx%100==0:
            logging.info("Epoch: {}, step: {}".format(epoch, idx))
    # 计算平均损失
    train_loss = float(train_losses) / len(train_dataloader)
    logging.info("Epoch: {}, train loss: {}".format(epoch, train_loss))


def evaluate(test_dataloader, model, enable_cuda):
    """
    评估模型性能
    :param test_dataloader: 验证集数据
    :param model: 模型
    :param enable_cuda: 是否使用cuda
    """
    # 模型评估
    model.eval()
    id2tag = config.id2tag
    true_labels = []
    pred_labels = []
    test_losses = 0
    # 不计算梯度
    with torch.no_grad():
        for batch_samples in test_dataloader:
            batch_data, batch_token_starts, batch_labels, ori_data = batch_samples
            # 是否使用cuda
            if enable_cuda:
                batch_data = batch_data.cuda()
                batch_token_starts = batch_token_starts.cuda()
                batch_labels = batch_labels.cuda()
            # 获取mask
            batch_masks = batch_data.gt(0)
            label_masks = batch_labels.gt(-1)
            # 模型预测
            loss = model((batch_data, batch_token_starts),
                         token_type_ids=None, attention_mask=batch_masks, labels=batch_labels)[0]
            # 计算损失
            test_losses += loss.item()
            # 获取预测结果
            batch_output = model((batch_data, batch_token_starts),
                                 token_type_ids=None, attention_mask=batch_masks)[0]
            # 解码
            batch_output = model.crf.decode(batch_output, mask=label_masks)
            batch_labels = batch_labels.to('cpu').numpy()

            pred_labels.extend([[id2tag.get(idx) for idx in indices] for indices in batch_output])
            true_labels.extend([[id2tag.get(idx) for idx in indices if idx > -1] for indices in batch_labels])

    # 计算f1值
    res = {}
    f, p, r = f1_score(true_labels,pred_labels)
    res['f'] = f
    res['p'] = p
    res['r'] = r
    res['loss'] = float(test_losses) / len(test_dataloader)
    return res