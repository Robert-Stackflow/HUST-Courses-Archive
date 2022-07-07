import seaborn as sns
import datetime as dt
import matplotlib.pyplot as plt
from sklearn import metrics
from xgboost import XGBClassifier
from lightgbm import LGBMClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier, VotingClassifier, StackingClassifier

from features import get_feat, choose_feat
from params import get_lightgbm_best_params
from params import get_xgboost_best_params


def draw_heatmap(model_name, true_labels, predict_labels):
    plt.figure(figsize=(8, 6))
    sns.heatmap(metrics.confusion_matrix(true_labels, predict_labels), annot=True, fmt='.20g', cmap='Blues')
    plt.title('The Prediction Heatmap of ' + model_name)
    plt.xlabel('Predicted labels')
    plt.ylabel('True labels')
    plt.show()


def test_model(train_feat, test_feat):
    """
    测试不同模型\n
    :param train_feat: 训练集特征集
    :param test_feat: 测试集特征集
    """
    print(">>>Start Test Model...")
    # 对比不同模型
    from sklearn.model_selection import train_test_split
    # 将train_feat划分为数据和标签,并将训练集划分为训练集和测试集
    X = train_feat.drop(['uid', 'label'], axis=1)
    y = train_feat['label']
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)
    # 记录准确率的列表
    score = []
    # 记录参数的字典
    best_params_list = {}
    # 逻辑回归模型与准确率
    lr = LogisticRegression(random_state=0, solver='lbfgs', max_iter=10000)
    lr = lr.fit(X_train, y_train)
    score.append(['Logistic Regression', lr.score(X_test, y_test)])
    draw_heatmap('Logistic Regression', y_test, lr.predict(X_test))
    # 决策树模型与准确率
    dtc = DecisionTreeClassifier(random_state=0)
    dtc = dtc.fit(X_train, y_train)
    score.append(['Decision Tree', dtc.score(X_test, y_test)])
    draw_heatmap('Decision Tree', y_test, dtc.predict(X_test))
    # 随机森林模型与准确率
    rfc = RandomForestClassifier(random_state=0)
    rfc = rfc.fit(X_train, y_train)
    score.append(['Random Forest', rfc.score(X_test, y_test)])
    draw_heatmap('Random Forest', y_test, rfc.predict(X_test))
    # LightGBM模型
    # 调参前结果
    gbm = LGBMClassifier()
    gbm = gbm.fit(X_train, y_train)
    score.append(['LightGBM', gbm.score(X_test, y_test)])
    draw_heatmap('LightGBM', y_test, gbm.predict(X_test))
    # 调参后结果
    # 获取参数列表
    lightgbm_best_params = get_lightgbm_best_params(X_train, y_train, X_test, y_test)
    best_params_list['LightGBM'] = lightgbm_best_params
    gbm = LGBMClassifier(n_estimators=lightgbm_best_params['n_estimators'],
                         max_depth=lightgbm_best_params['max_depth'],
                         num_leaves=lightgbm_best_params['num_leaves'],
                         min_child_samples=lightgbm_best_params['min_child_samples'],
                         min_child_weight=lightgbm_best_params['min_child_weight'],
                         feature_fraction=lightgbm_best_params['feature_fraction'],
                         bagging_fraction=lightgbm_best_params['bagging_fraction'],
                         learning_rate=lightgbm_best_params['learning_rate'])
    gbm = gbm.fit(X_train, y_train)
    score.append(['Optimized LightGBM', gbm.score(X_test, y_test)])
    draw_heatmap('Optimized LightGBM', y_test, gbm.predict(X_test))
    # XGBoost模型
    # 调参前结果
    xgb = XGBClassifier()
    xgb = xgb.fit(X_train, y_train)
    score.append(['XGBoost', xgb.score(X_test, y_test)])
    draw_heatmap('XGBoost', y_test, xgb.predict(X_test))
    # 调参后结果
    # 获取参数列表
    xgboost_best_params = get_xgboost_best_params(X_train, y_train, X_test, y_test)
    best_params_list['XGBoost'] = xgboost_best_params
    xgb = XGBClassifier(seed=0, learning_rate=xgboost_best_params["learning_rate"],
                        subsample=xgboost_best_params["subsample"],
                        colsample_bytree=xgboost_best_params["colsample_bytree"],
                        gamma=xgboost_best_params["gamma"],
                        n_estimators=xgboost_best_params["n_estimators"],
                        max_depth=xgboost_best_params["max_depth"],
                        min_child_weight=xgboost_best_params["min_child_weight"],
                        reg_alpha=xgboost_best_params["reg_alpha"],
                        reg_lambda=xgboost_best_params["reg_lambda"])
    xgb = xgb.fit(X_train, y_train)
    score.append(['Optimized XGBoost', xgb.score(X_test, y_test)])
    draw_heatmap('Optimized XGBoost', y_test, xgb.predict(X_test))
    # 绘制准确率表格
    plt.title('Accuracy of Different Models')
    table = plt.table(cellText=score,
                      colLabels=['Model Name', 'Accuracy'],
                      loc='center',
                      cellLoc='center',
                      rowLoc='center')
    table.scale(1, 2)
    plt.axis('off')
    plt.show()
    print(">>>Test Model Successfully!\n")
    return best_params_list


def final_test(train_feat, test_feat, test_cus, model, best_params_list, enable):
    """
    最终测试\n
    :param best_params_list: 最佳参数列表
    :param test_cus: 测试结果的账号列表
    :param test_feat: 测试集
    :param train_feat: 训练集
    :param model: 选用的模型
    :param enable: 是否启用特征子集优化
    """
    # 是否启用特征子集优化
    if enable == 1:
        # 选择特征子集
        best_feats = choose_feat(train_feat, test_feat)
        # 根据特征子集更改测试集和训练集
        train_feat = train_feat[list(best_feats) + ['uid', 'label']]
        test_feat = test_feat[list(best_feats) + ['uid']]
    # 划分训练集
    X = train_feat.drop(['uid', 'label'], axis=1)
    y = train_feat['label']
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)
    TEST = test_feat.drop(['uid'], axis=1)
    # 选择模型
    if model == 'Random Forest':
        # 采用随机森林模型预测结果
        rfc = RandomForestClassifier(random_state=0)
        rfc.fit(X, y)
        test_cus['label'] = rfc.predict(TEST, )
        test_cus.to_csv(
            './submit/submit' + '_Random Forest_' + dt.datetime.now().strftime('%Y-%m-%d_%H-%M-%S').__str__() + '.csv',
            index=None)
        print(">>>The Result of Random Forest:")
        print(f"{test_cus['label'].value_counts()}\n")
    elif model == 'LightGBM':
        # 采用LightGBM模型
        lightgbm_best_params = best_params_list['LightGBM']
        print('>>>The Best Params of LightGBM:', lightgbm_best_params)
        gbm = LGBMClassifier(n_estimators=lightgbm_best_params['n_estimators'],
                             max_depth=lightgbm_best_params['max_depth'],
                             num_leaves=lightgbm_best_params['num_leaves'],
                             min_child_samples=lightgbm_best_params['min_child_samples'],
                             min_child_weight=lightgbm_best_params['min_child_weight'],
                             feature_fraction=lightgbm_best_params['feature_fraction'],
                             bagging_fraction=lightgbm_best_params['bagging_fraction'],
                             learning_rate=lightgbm_best_params['learning_rate']
                             )
        gbm.fit(X, y)
        test_cus['label'] = gbm.predict(TEST, )
        test_cus.to_csv(
            './submit/submit' + '_LightGBM_' + dt.datetime.now().strftime('%Y-%m-%d_%H-%M-%S').__str__() + '.csv',
            index=None)
        print(">>>The Result of LightGBM:")
        print(f"{test_cus['label'].value_counts()}\n")
    elif model == 'XGBoost':
        # 采用XGBoost模型
        xgboost_best_params = best_params_list['XGBoost']
        print('>>>The Best Params of XGBoost:', xgboost_best_params)
        xgb = XGBClassifier(seed=0, learning_rate=xgboost_best_params["learning_rate"],
                            subsample=xgboost_best_params["subsample"],
                            colsample_bytree=xgboost_best_params["colsample_bytree"],
                            gamma=xgboost_best_params["gamma"],
                            n_estimators=xgboost_best_params["n_estimators"],
                            max_depth=xgboost_best_params["max_depth"],
                            min_child_weight=xgboost_best_params["min_child_weight"],
                            reg_alpha=xgboost_best_params["reg_alpha"],
                            reg_lambda=xgboost_best_params["reg_lambda"])
        xgb.fit(X, y)
        test_cus['label'] = xgb.predict(TEST, )
        test_cus.to_csv(
            './submit/submit' + '_XGBoost_' + dt.datetime.now().strftime('%Y-%m-%d_%H-%M-%S').__str__() + '.csv',
            index=None)
        print(">>>The Result of XGBoost:")
        print(f"{test_cus['label'].value_counts()}\n")
    elif model == 'Voting Merge':
        # 使用投票法进行模型融合
        rfc = RandomForestClassifier(random_state=0)
        lightgbm_best_params = best_params_list['LightGBM']
        gbm = LGBMClassifier(n_estimators=lightgbm_best_params['n_estimators'],
                             max_depth=lightgbm_best_params['max_depth'],
                             num_leaves=lightgbm_best_params['num_leaves'],
                             min_child_samples=lightgbm_best_params['min_child_samples'],
                             min_child_weight=lightgbm_best_params['min_child_weight'],
                             feature_fraction=lightgbm_best_params['feature_fraction'],
                             bagging_fraction=lightgbm_best_params['bagging_fraction'],
                             learning_rate=lightgbm_best_params['learning_rate']
                             )
        xgboost_best_params = best_params_list['XGBoost']
        xgb = XGBClassifier(seed=0, learning_rate=xgboost_best_params["learning_rate"],
                            subsample=xgboost_best_params["subsample"],
                            colsample_bytree=xgboost_best_params["colsample_bytree"],
                            gamma=xgboost_best_params["gamma"],
                            n_estimators=xgboost_best_params["n_estimators"],
                            max_depth=xgboost_best_params["max_depth"],
                            min_child_weight=xgboost_best_params["min_child_weight"],
                            reg_alpha=xgboost_best_params["reg_alpha"],
                            reg_lambda=xgboost_best_params["reg_lambda"])
        merge = VotingClassifier(estimators=[('rfc', rfc), ('gbm', gbm), ('xgb', xgb)], voting='hard')
        merge.fit(X, y)
        test_cus['label'] = merge.predict(TEST, )
        test_cus.to_csv(
            './submit/submit' + '_Voting Merge_' + dt.datetime.now().strftime('%Y-%m-%d_%H-%M-%S').__str__() + '.csv',
            index=None)
        print(">>>The Result of Voting Merge:")
        print(f"{test_cus['label'].value_counts()}\n")
    elif model == 'Stacking Merge':
        # 5折stacking
        rfc = RandomForestClassifier(random_state=0)
        lightgbm_best_params = best_params_list['LightGBM']
        gbm = LGBMClassifier(n_estimators=lightgbm_best_params['n_estimators'],
                             max_depth=lightgbm_best_params['max_depth'],
                             num_leaves=lightgbm_best_params['num_leaves'],
                             min_child_samples=lightgbm_best_params['min_child_samples'],
                             min_child_weight=lightgbm_best_params['min_child_weight'],
                             feature_fraction=lightgbm_best_params['feature_fraction'],
                             bagging_fraction=lightgbm_best_params['bagging_fraction'],
                             learning_rate=lightgbm_best_params['learning_rate']
                             )
        xgboost_best_params = best_params_list['XGBoost']
        xgb = XGBClassifier(seed=0, learning_rate=xgboost_best_params["learning_rate"],
                            subsample=xgboost_best_params["subsample"],
                            colsample_bytree=xgboost_best_params["colsample_bytree"],
                            gamma=xgboost_best_params["gamma"],
                            n_estimators=xgboost_best_params["n_estimators"],
                            max_depth=xgboost_best_params["max_depth"],
                            min_child_weight=xgboost_best_params["min_child_weight"],
                            reg_alpha=xgboost_best_params["reg_alpha"],
                            reg_lambda=xgboost_best_params["reg_lambda"])
        merge = StackingClassifier(estimators=[('rfc', rfc), ('gbm', gbm), ('xgb', xgb)],
                                   final_estimator=LogisticRegression())
        merge.fit(X, y)
        test_cus['label'] = merge.predict(TEST, )
        test_cus.to_csv(
            './submit/submit' + '_Stacking Merge_' + dt.datetime.now().strftime('%Y-%m-%d_%H-%M-%S').__str__() + '.csv',
            index=None)
        print(">>>The Result of Stacking Merge:")
        print(f"{test_cus['label'].value_counts()}\n")


if __name__ == '__main__':
    # 读取文件得到数据集
    train_feat, test_feat, test_cus = get_feat()
    # 测试模型
    best_params_list = test_model(train_feat, test_feat)
    # 最终测试
    final_test(train_feat=train_feat, test_feat=test_feat, test_cus=test_cus, enable=1, model='Stacking Merge',
               best_params_list=best_params_list)
