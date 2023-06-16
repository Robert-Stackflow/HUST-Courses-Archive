import pickle
import logging
from train import train

from utils import set_logger
from transformers import get_cosine_schedule_with_warmup

import config
import torch
from torch.utils.data import DataLoader
from data_process import Processor
from data_loader import Sentence
from model import BertSeg
from torch.optim import AdamW
from sklearn.model_selection import train_test_split

def run():
    # 设置日志
    set_logger()
    # 是否开启cuda
    enable_cuda = config.cuda and torch.cuda.is_available()
    # 处理数据
    if config.reprocess_data:
        logging.info("Process data...")
        Processor().process()
    # 加载数据
    logging.info("Load data...")
    with open(config.TRAINING_PATH, 'rb') as inp:
        words = pickle.load(inp)
        labels = pickle.load(inp)
    # 划分训练集和验证集
    word_train, word_test, label_train, label_test = train_test_split(words, labels,
                                                                          test_size=config.train_test_split_size,
                                                                          random_state=config.random_state)
    # 训练集
    train_dataset = Sentence(word_train, label_train)
    train_dataloader = DataLoader(
        dataset=train_dataset,
        shuffle=True,
        batch_size=config.batch_size,
        collate_fn=train_dataset.collate_fn,
        drop_last=False,
        num_workers=config.num_workers
    )
    # 验证集
    test_dataset = Sentence(word_test, label_test)
    test_dataloader = DataLoader(
        dataset=test_dataset,
        shuffle=False,
        batch_size=config.batch_size,
        collate_fn=test_dataset.collate_fn,
        drop_last=False,
        num_workers=config.num_workers
    )
    train_size = len(train_dataset)
    # 加载模型
    logging.info("Load pretrained model...")
    model = BertSeg.from_pretrained(config.BERT_MODEL_PATH, num_labels=len(config.tag2id))
    # 是否使用cuda
    if enable_cuda:
        model = model.cuda()
    if config.full_fine_tuning:
        # 全部参数参与训练
        bert_optimizer = list(model.bert.named_parameters())
        classifier_optimizer = list(model.classifier.named_parameters())
        no_decay = ['bias', 'LayerNorm.bias', 'LayerNorm.weight']
        optimizer_grouped_parameters = [
            {'params': [p for n, p in bert_optimizer if not any(nd in n for nd in no_decay)],
             'weight_decay': config.weight_decay},
            {'params': [p for n, p in bert_optimizer if any(nd in n for nd in no_decay)],
             'weight_decay': 0.0},
            {'params': [p for n, p in classifier_optimizer if not any(nd in n for nd in no_decay)],
             'lr': config.lr * 5, 'weight_decay': config.weight_decay},
            {'params': [p for n, p in classifier_optimizer if any(nd in n for nd in no_decay)],
             'lr': config.lr * 5, 'weight_decay': 0.0},
            {'params': model.crf.parameters(), 'lr': config.lr * 5}
        ]
    else:
        # 只有分类器参与训练
        classifier_optimizer = list(model.classifier.named_parameters())
        optimizer_grouped_parameters = [{'params': [p for n, p in classifier_optimizer]}]
    # 优化器
    optimizer = AdamW(optimizer_grouped_parameters, lr=config.lr)
    # 训练步数
    train_steps_per_epoch = train_size // config.batch_size
    # 学习率衰减
    scheduler = get_cosine_schedule_with_warmup(optimizer,
                                                num_warmup_steps=2 * train_steps_per_epoch,
                                                num_training_steps=config.max_epoch * train_steps_per_epoch)
    # 训练
    train(train_dataloader,test_dataloader, model, optimizer, scheduler, enable_cuda)


if __name__ == '__main__':
    run()
