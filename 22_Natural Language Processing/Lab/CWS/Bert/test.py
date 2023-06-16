import torch
import pickle
import config
from data_loader import Sentence
from torch.utils.data import DataLoader

from model import BertSeg

if __name__ == '__main__':
    # 加载模型
    model = BertSeg.from_pretrained(
        config.BERT_MODEL_PATH, num_labels=len(config.tag2id))
    model.eval()
    # 是否使用cuda
    enable_cuda = config.cuda and torch.cuda.is_available()
    # 输出文件
    output = open('cws_result.txt', 'w', encoding='utf-8')
    # 加载测试集
    with open(config.TESTING_PATH, 'rb') as inp:
        word_test = pickle.load(inp)
        label_test = pickle.load(inp)
    # 测试集
    test_dataset = Sentence(word_test, label_test)
    test_loader = DataLoader(
        dataset=test_dataset,
        shuffle=False,
        batch_size=config.batch_size,
        collate_fn=test_dataset.collate_fn,
        drop_last=False,
        num_workers=config.num_workers
    )

    id2tag = config.id2tag
    pred_labels = []

    print("Start predict...")

    with torch.no_grad():
        for idx, batch_samples in enumerate(test_loader):
            batch_data, batch_token_starts, batch_labels, ori_data = batch_samples
            if enable_cuda:
                batch_data = batch_data.cuda()
                batch_token_starts = batch_token_starts.cuda()
                batch_labels = batch_labels.cuda()
            # 获取mask
            batch_masks = batch_data.gt(0)
            label_masks = batch_labels.gt(-1)
            # 计算模型预测值
            batch_output = model((batch_data, batch_token_starts),
                                 token_type_ids=None, attention_mask=batch_masks)[0]
            batch_output = model.crf.decode(batch_output, mask=label_masks)
            pred_labels.extend([[id2tag.get(idx) for idx in indices]
                             for indices in batch_output])

    print("Start output...")
    # 输出结果
    with open(config.TEST_DATA, 'r', encoding='utf-8') as f:
        for idx, test in enumerate(f):
            if (idx < pred_labels.__len__()):
                for i in range(len(test)):
                    print(test[i], end='', file=output)
                    if (i < pred_labels[idx].__len__() and pred_labels[idx][i] in ['E', 'S']):
                        print(' ', end='', file=output)
                print(file=output)
    print("Done!")
