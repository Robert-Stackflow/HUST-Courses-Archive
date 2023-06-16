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

    @staticmethod
    def cut(raw, max_len, sep):
        """
        将raw按照max_len切分，分隔符为sep_word
        """
        list_groups = zip(*(iter(raw),) * max_len)
        end_list = [list(i) + list(sep) for i in list_groups]
        count = len(raw) % max_len
        if count != 0:
            end_list.append(raw[-count:])
        else:
            end_list[-1] = end_list[-1][:-1]
        return end_list

    @staticmethod
    def toTag(input):
        """
        将每个字转换为BMES标注
        """
        output_str = []
        if len(input) == 1:
            output_str.append('S')
        elif len(input) == 2:
            output_str = ['B', 'E']
        else:
            M_num = len(input) - 2
            M_list = ['M'] * M_num
            output_str.append('B')
            output_str.extend(M_list)
            output_str.append('E')
        return output_str

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
        with open(origin_path, 'r', encoding='utf-8') as f:
            words_list = []
            tags_list = []
            # 行数
            count = 0
            # 切分次数
            sep_count = 0
            for line in f:
                words = []
                tags = []
                line = line.strip()
                if not line:
                    continue
                # 读取每个字到words
                for i in range(len(line)):
                    if line[i] == " ":
                        continue
                    words.append(line[i])
                # 将每个字转换为BIES标注,记录在labels
                line = line.split(" ")
                for item in line:
                    if item == "":
                        continue
                    tags.extend(Processor.toTag(item))
                # 如果字数大于设定的最大长度，则进行切分
                if len(words) > config.max_len:
                    # 获取切分后的words列表
                    sub_words_list = Processor.cut(words, config.max_len - 5, config.sep_word)
                    sub_labels_list = Processor.cut(tags, config.max_len - 5, config.sep_label)
                    words_list.extend(sub_words_list)
                    tags_list.extend(sub_labels_list)
                    sep_count += 1
                else:
                    words_list.append(words)
                    tags_list.append(tags)
                count += 1
            # 将结果输出为二进制
            with open(path, 'wb') as outp:
                pickle.dump(words_list, outp)
                pickle.dump(tags_list, outp)


class Parser:
    """
    数据读取器
    """

    def analysis(self, mode='training'):
        len_list, word_list = self.read_file(mode)
        lens = {'<100': 0, '100-200': 0, '200-500': 0, '500-1000': 0, '>1000': 0}
        print(len(len_list), "sentences in the", mode, "file.")
        for i in len_list:
            if i <= 100:
                lens['<100'] += 1
            elif 100 < i <= 200:
                lens['100-200'] += 1
            elif 200 < i <= 500:
                lens['200-500'] += 1
            elif 500 < i <= 1000:
                lens['500-1000'] += 1
            elif i > 1000:
                lens['>1000'] += 1
        return lens

    def read_file(self, mode='training'):
        """
        读取文件
        """
        word_list = []
        len_list = []
        if mode == "train":
            origin_path = config.TRAINING_DATA
        else:
            origin_path = config.TEST_DATA
        with open(origin_path, 'r', encoding='utf-8') as f:
            for line in f:
                words = []
                line = line.strip()
                if not line:
                    continue
                for i in range(len(line)):
                    if line[i] == " ":
                        continue
                    words.append(line[i])
                if len(words) > config.max_len:
                    sub_word_list = self.get_sep_list(words, config.sep_word)
                    for wl in sub_word_list:
                        if len(wl) > config.max_len or len(wl) == 0:
                            continue
                        word_list.append(wl)
                        len_list.append(len(wl))
                else:
                    word_list.append(words)
                    len_list.append(len(words))
        return len_list, word_list

    def get_sep_list(self, init_list, sep_word):
        """
        按标点切分
        """
        w = "".join(init_list)
        s = re.split(r"(。)", w)
        s = self.add_sep_word(s, sep_word)
        s.append("")
        s = ["".join(i) for i in zip(s[0::2], s[1::2])]
        r = []
        for sub_list in s:
            r.append(list(sub_list))
        return r

    def add_sep_word(self, s_, sep_word):
        """
        add sep word to string
        """
        new = []
        for i, item in enumerate(s_):
            if item == "，" or item == "。" or item == "；":
                if i == len(s_) - 2:
                    if s_[-1] == '':
                        new.append(item)
                        continue
                item += sep_word
            new.append(item)
        s_ = new
        return s_


def run():
    if os.path.exists(config.TRAINING_PATH):
        os.remove(config.TRAINING_PATH)
    if os.path.exists(config.TESTING_PATH):
        os.remove(config.TESTING_PATH)
    Processor().process()


def anlysis():
    print(Parser().analysis("train"))
    print(Parser().analysis("test"))


if __name__ == "__main__":
    run()
    anlysis()
