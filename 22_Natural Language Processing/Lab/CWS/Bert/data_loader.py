import numpy as np
import torch
import pickle
from torch.utils.data import Dataset, DataLoader
from transformers import BertTokenizer

import config


class Sentence(Dataset):
    """
    数据集对象
    """

    def __init__(self, words, tags):
        self.tokenizer = BertTokenizer.from_pretrained(config.BERT_MODEL_PATH, do_lower_case=True)
        self.dataset = self.preprocess(words, tags)
        self.word_pad_idx = 0
        self.label_pad_idx = -1

    def preprocess(self, origin_words_list, origin_tags_list):
        data = []
        words_list = []
        tags_list = []
        for origin_words in origin_words_list[0:1]:
            words = []
            words_len = []
            for token in origin_words:
                words.append(self.tokenizer.tokenize(token))
                words_len.append(len(token))
            words = ['[CLS]'] + [item for token in words for item in token]
            token_start_idxs = 1 + np.cumsum([0] + words_len[:-1])
            words_list.append(((self.tokenizer.convert_tokens_to_ids(words), token_start_idxs), origin_words))
        for origin_tags in origin_tags_list[0:1]:
            tags = [config.tag2id.get(t) for t in origin_tags]
            tags_list.append(tags)
        for words, tags in zip(words_list, tags_list):
            data.append((words, tags))
        return data

    def __len__(self):
        return len(self.dataset)

    def __getitem__(self, idx):
        word = self.dataset[idx][0]
        label = self.dataset[idx][1]
        return [word, label]

    def collate_fn(self, batch):
        """
            生成batch
                process batch data, including:
                    1. padding: 将每个batch的data padding到同一长度（batch中最长的data长度）
                    2. aligning: 找到每个sentence sequence里面有label项，文本与label对齐
                    3. tensor：转化为tensor
        """
        # 处理后句子
        sentences = [x[0][0] for x in batch]
        # 原始句子
        ori_sentences = [x[0][1] for x in batch]
        # 标签
        labels = [x[1] for x in batch]
        # batch大小
        batch_len = len(sentences)
        # 最长的句子长度
        max_len = max([len(s[0]) for s in sentences])
        max_label_len = 0

        # 初始化对齐后数据
        batch_data = self.word_pad_idx * np.ones((batch_len, max_len))
        batch_label_starts = []

        # 对齐数据
        for j in range(batch_len):
            cur_len = len(sentences[j][0])
            batch_data[j][:cur_len] = sentences[j][0]

            word_indexs = sentences[j][-1]
            label_starts = np.zeros(max_len)
            # 标记label开始位置
            label_starts[[idx for idx in word_indexs if idx < max_len]] = 1
            batch_label_starts.append(label_starts)
            max_label_len = max(int(sum(label_starts)), max_label_len)

        # 初始化对齐后标签
        batch_labels = self.label_pad_idx * np.ones((batch_len, max_label_len))

        # 对齐标签
        for j in range(batch_len):
            cur_tags_len = len(labels[j])
            batch_labels[j][:cur_tags_len] = labels[j]
        # 转化为tensor
        batch_label_starts = np.array(batch_label_starts)
        batch_data = torch.LongTensor(batch_data)
        batch_label_starts = torch.LongTensor(batch_label_starts)
        batch_labels = torch.LongTensor(batch_labels)
        return [batch_data, batch_label_starts, batch_labels, ori_sentences]


if __name__ == '__main__':
    with open(config.TRAINING_PATH, 'rb') as inp:
        words = pickle.load(inp)
        labels = pickle.load(inp)
    dataset = Sentence(words, labels)
    train_dataloader = DataLoader(dataset, batch_size=config.batch_size, shuffle=True,
                                  collate_fn=dataset.collate_fn)
    for batch_data, batch_label_starts, batch_labels, ori_sentences in train_dataloader:
        print(batch_data, batch_label_starts, batch_labels, ori_sentences)
        break
