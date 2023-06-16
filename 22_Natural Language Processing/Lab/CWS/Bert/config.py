import os

# 文件路径
BASE_DIR = os.getcwd() + "/"
DATA_DIR = BASE_DIR + "data/"
MODEL_DIR = BASE_DIR + "model/"
BEST_MODEL_DIR = BASE_DIR + "model/best/"
MODEL_PREFIX = MODEL_DIR + "model_epoch"
LOG_PATH = BASE_DIR + "log.txt"
TRAINING_DATA = DATA_DIR + "train_pku.txt"
TEST_DATA = DATA_DIR + "test_data.txt"
TRAINING_PATH = DATA_DIR + "training.pkl"
TESTING_PATH = DATA_DIR + "testing.pkl"
BERT_MODEL_PATH = BASE_DIR + "pretrained/chinese-macbert-base/"
MODEL_PATH=MODEL_DIR+"mode.pkl"
# 超参数
lr = 0.005
max_epoch = 10
min_epoch = 5
clip_grad = 5
batch_size = 1
hidden_dim = 200
embedding_dim = 100
weight_decay = 0.01
# worker数量
num_workers = 2
# 是否使用gpu
cuda = True
# 是否对Bert进行微调
full_fine_tuning = True
# 每行最大长度
max_len = 500
# 切分分隔符
sep_word = '@'
sep_label = 'S'
# 训练集和验证集划分
train_test_split_size = 0.1
random_state = 43
# 是否重新处理数据
reprocess_data = False
patience=5
# 标注
tag2id = {'B': 0, 'M': 1, 'E': 2, 'S': 3}
id2tag = {_id: _label for _label, _id in list(tag2id.items())}
