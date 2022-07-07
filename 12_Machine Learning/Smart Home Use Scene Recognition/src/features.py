import codecs
import datetime
import pandas as pd
import seaborn as sns
from xgboost import XGBClassifier
from lightgbm import LGBMClassifier
from matplotlib import pyplot as plt


def my_readcsv(path, sep=','):
    """
    :param path: 文件路径
    :param sep: 读取文件地分隔符
    :return: 文件对应的DataFrame
    """
    # 使用codecs读取整个文件到lines
    try:
        lines = codecs.open(path, encoding='utf-8').readlines()
    except:
        lines = codecs.open(path, encoding='latin-1').readlines()
    # 获取文件表头header
    header = lines[0].strip().split(sep)
    # 获取文件内容列表content
    content = []
    for line in lines[1:]:
        line = line.strip()
        try:
            # 如果不包含json型数据,则直接使用sep分割line
            index = [i for i, x in enumerate(line) if x == ',']
            if len(index) == len(header) - 1:
                content.append(line.split(sep))
            else:
                json_list = []
                # 将非json型数据读取至json_list中
                index = [0] + index
                for idx in range(len(header) - 1):
                    json_list.append(line[index[idx]:index[idx + 1]].strip(sep))
                json_list.append(line[index[len(header) - 1]:].strip(sep).replace(',', ';'))
                content.append(json_list)
        except:
            pass
    # 返回DataFrame
    return pd.DataFrame(content, columns=header)


def get_feat():
    """
    读取文件,处理数据,获得特征集\n
    :return: train_feat,test_feat
    """
    print(">>>Start Read Files...")
    # 读取训练文件和测试文件
    train_cus = pd.read_csv('./train/cus.csv', sep=',')
    test_cus = pd.read_csv('./test/cus.csv', sep=',')
    train_devupdate = my_readcsv('./train/devUpdata.csv', sep=',')
    test_devupdate = my_readcsv('./test/devUpdata.csv', sep=',')
    train_control = my_readcsv('./train/control.csv', sep=',')
    test_control = my_readcsv('./test/control.csv', sep=',')
    train_devlist = my_readcsv('./train/devList.csv', sep=',')
    test_devlist = my_readcsv('./test/devList.csv', sep=',')
    # 数据统计
    # 统计设备列表中各账号对应的设备种类数、型号种类数、区域种类数 、区域类型集合、区域数目
    # 训练集
    train_devlist_feat = train_devlist.groupby('uid').agg({
        'did': 'nunique',
        'type': 'nunique',
        'area': ['nunique', 'unique', 'count']
    })
    train_devlist_feat.reset_index(inplace=True)
    train_devlist_feat.columns = [x[0] + x[1] for x in train_devlist_feat.columns]
    # 测试集
    test_devlist_feat = test_devlist.groupby('uid').agg({
        'did': 'nunique',
        'type': 'nunique',
        'area': ['nunique', 'unique', 'count']
    })
    test_devlist_feat.reset_index(inplace=True)
    test_devlist_feat.columns = [x[0] + x[1] for x in test_devlist_feat.columns]
    # 统计控制日志中各账号对应的设备种类数、日志种类数、命令类型种类数、命令类型集合、命令数目
    # 训练集
    train_control_feat = train_control.groupby('uid').agg({
        'did': 'nunique',
        'data': 'nunique',
        'form': ['nunique', 'unique', 'count']
    })
    train_control_feat.reset_index(inplace=True)
    train_control_feat.columns = [x[0] + x[1] for x in train_control_feat.columns]
    # 测试集
    test_control_feat = test_control.groupby('uid').agg({
        'did': 'nunique',
        'data': 'nunique',
        'form': ['nunique', 'unique', 'count']
    })
    test_control_feat.reset_index(inplace=True)
    test_control_feat.columns = [x[0] + x[1] for x in test_control_feat.columns]
    # 统计上报日志中各账号对应的设备数目、日志数目
    # 训练集
    train_devupdate_feat = train_devupdate.groupby('uid').agg({
        'did': 'nunique',
        'data': 'nunique',
    })
    train_devupdate_feat.reset_index(inplace=True)
    train_devupdate_feat.columns = ['uid', 'devupdate_did_count', 'devupdate_data_count']
    # 测试集
    test_devupdate_feat = test_devupdate.groupby('uid').agg({
        'did': 'nunique',
        'data': 'nunique',
    })
    test_devupdate_feat.reset_index(inplace=True)
    test_devupdate_feat.columns = ['uid', 'devupdate_did_count', 'devupdate_data_count']
    # 合并特征
    # 训练集
    train_feat = train_cus.merge(train_devlist_feat, on='uid')
    train_feat = train_feat.merge(train_control_feat, on='uid', how='left')
    train_feat = train_feat.merge(train_devupdate_feat, on='uid', how='left')
    train_feat.fillna(0, inplace=True)
    # 测试集
    test_feat = test_cus.merge(test_devlist_feat, on='uid')
    test_feat = test_feat.merge(test_control_feat, on='uid', how='left')
    test_feat = test_feat.merge(test_devupdate_feat, on='uid', how='left')
    test_feat.fillna(0, inplace=True)
    # 使用TF-IDF对设备列表中的area、操作控制日志中的form进行文本数据信息统计
    from sklearn.feature_extraction.text import TfidfVectorizer
    # 统计areaunique列词频
    tfidf = TfidfVectorizer(max_features=400)
    train_dev_tfidf = tfidf.fit_transform(train_feat['areaunique'].apply(lambda x: ' '.join(x)))
    test_dev_tfidf = tfidf.transform(test_feat['areaunique'].apply(lambda x: ' '.join(x)))
    # 设置列名
    features = list(tfidf.get_feature_names_out())
    train_dev_tfidf = pd.DataFrame(train_dev_tfidf.toarray(),
                                   columns=['area_unique_' + str(features.index(x)) for x in features])
    test_dev_tfidf = pd.DataFrame(test_dev_tfidf.toarray(),
                                  columns=['area_unique_' + str(features.index(x)) for x in features])
    # 合并统计信息并删除areaunique列
    train_feat = pd.concat([train_feat, train_dev_tfidf], axis=1)
    train_feat = train_feat.drop(['areaunique'], axis=1)
    test_feat = pd.concat([test_feat, test_dev_tfidf], axis=1)
    test_feat = test_feat.drop(['areaunique'], axis=1)
    # 统计formunique列词频
    tfidf = TfidfVectorizer(max_features=13)
    # 使用'default'替代formunique为0的字段
    train_control_tfidf = tfidf.fit_transform(
        train_feat['formunique'].apply(lambda x: 'default' if isinstance(x, int) is True else ' '.join(x)))
    test_control_tfidf = tfidf.fit_transform(
        test_feat['formunique'].apply(lambda x: 'default' if isinstance(x, int) is True else ' '.join(x)))
    # 设置列名
    features = list(tfidf.get_feature_names_out())
    train_control_tfidf = pd.DataFrame(train_control_tfidf.toarray(),
                                       columns=['form_unique_' + str(features.index(x)) for x in features])
    test_control_tfidf = pd.DataFrame(test_control_tfidf.toarray(),
                                      columns=['form_unique_' + str(features.index(x)) for x in features])
    # 合并统计信息并删除formunique列
    train_feat = pd.concat([train_feat, train_control_tfidf], axis=1)
    train_feat = train_feat.drop(['formunique'], axis=1)
    test_feat = pd.concat([test_feat, test_control_tfidf], axis=1)
    test_feat = test_feat.drop(['formunique'], axis=1)
    # 打印输出
    train_feat.to_csv(
        './feat/' + list(dict(train_feat=train_feat.shape).keys())[0]
        + '_' + datetime.datetime.now().strftime('%Y-%m-%d_%H-%M-%S').__str__() + '.csv')
    test_feat.to_csv(
        './feat/' + list(dict(test_feat=test_feat.shape).keys())[0]
        + '_' + datetime.datetime.now().strftime('%Y-%m-%d_%H-%M-%S').__str__() + '.csv')
    print(">>>Read Files Successfully!\n")
    return train_feat, test_feat, test_cus


def choose_feat(train_feat, test_feat):
    """
    选择特征子集\n
    :param train_feat: 训练集特征集
    :param test_feat: 测试集特征集
    :return: 选择的特征子集best_feats
    """
    print(">>>Start Choose Features...")
    X = train_feat.drop(['uid', 'label'], axis=1)
    y = train_feat['label']
    # best_feats存储最优特征子集
    best_feats = []
    # 绘制相关性热力图,查看相关性较强的特征
    plt.figure(figsize=(18, 14))
    sns.heatmap(round(X[X.columns[0:10]].corr(), 2), cmap='Blues', annot=True)
    plt.show()
    # 使用相关系数法选择特征
    from sklearn.feature_selection import SelectKBest
    from sklearn.feature_selection import f_regression

    selectKBest = SelectKBest(f_regression, k=20)
    bestFeature = selectKBest.fit_transform(X, y)
    best_feats.extend(X.columns[selectKBest.get_support()])
    # 使用递归特征消除法选择特征
    from sklearn.feature_selection import RFE
    from sklearn.linear_model import LinearRegression

    rfe = RFE(estimator=LinearRegression(), n_features_to_select=20)
    sFeature = rfe.fit_transform(X, y)
    best_feats.extend(X.columns[rfe.get_support()])
    # 使用模型分析法选择特征
    from sklearn.feature_selection import SelectFromModel
    from sklearn.linear_model import LogisticRegression
    # 回归模型
    model1 = LogisticRegression(max_iter=10000)
    selectFromModel1 = SelectFromModel(model1)
    selectFromModel1.fit_transform(X, y)
    # LightGBM模型
    model2 = LGBMClassifier()
    selectFromModel2 = SelectFromModel(model2)
    selectFromModel2.fit_transform(X, y)
    # XGBoost模型
    model3 = XGBClassifier()
    selectFromModel3 = SelectFromModel(model3)
    selectFromModel3.fit_transform(X, y)
    best_feats.extend(X.columns[selectFromModel1.get_support()])
    best_feats.extend(X.columns[selectFromModel2.get_support()])
    best_feats.extend(X.columns[selectFromModel3.get_support()])
    # 合并手动选择的特征
    best_feats.extend(['devupdate_data_count', 'devupdate_did_count'])
    best_feats = list(set(best_feats))
    print(">>>Choose Features Successfully!")
    print(f'>>>The Best Features:{best_feats}\n')
    return best_feats
