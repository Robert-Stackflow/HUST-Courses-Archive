import os
import pickle
import re
import config


class Processor:
    """
    数据处理器
    """

    def process(self):
        self.process_data("train")
        self.process_data("test")

    def getTypes(self):
        unique = set()
        with open(config.TRAINING_DATA, 'r')as f:
            for line in f:
                try:
                    unique.update([line.strip('\n').split(' ')[1]])
                except:
                    pass
        id2tag = list(unique)
        tag2id = {}
        for i, label in enumerate(id2tag):
            tag2id[label] = i
        config.tag2id = tag2id

    def process_data(self, mode):
        # 判断训练集或测试集结果是否已存在
        if mode == "train":
            path = config.TRAINING_PATH
            origin_path = config.TRAINING_DATA
        else:
            path = config.TESTING_PATH
            origin_path = config.TEST_DATA
        if os.path.exists(path) is True:
            return
        words_list = []
        tags_list = []
        with open(origin_path, 'r') as f:
            words = []
            tags = []
            for line in f:
                line = line.strip()
                if not line:
                    words_list.append(words)
                    tags_list.append(tags)
                    words = []
                    tags = []
                    continue

                line = line.split(" ")
                words.append(line[0])
                tags.append(line[1])
            print(words_list[0])
            print(tags_list[0])
            with open(path, 'wb') as outp:
                pickle.dump(words_list, outp)
                pickle.dump(tags_list, outp)

def run():
    if os.path.exists(config.TRAINING_PATH):
        os.remove(config.TRAINING_PATH)
    if os.path.exists(config.TESTING_PATH):
        os.remove(config.TESTING_PATH)
    Processor().process()

if __name__ == "__main__":
    run()
