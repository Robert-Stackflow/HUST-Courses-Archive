import lightgbm as lgb
from xgboost import XGBRegressor
from lightgbm import early_stopping
from sklearn.model_selection import GridSearchCV


def get_lightgbm_best_params(X_train, y_train, X_test, y_test):
    """
    对LightGBM模型进行调参\n
    :return: 返回最佳参数的字典
    """
    # 参数字典
    best_params = {}
    # LightGBM调参
    print(">>>Start Get Params of LightGBM...")

    # 调参:n_estimators
    print(">>>Get Param:n_estimators...")
    cv_params = {'n_estimators': [20, 25, 30, 40, 50, 60, 70, 80, 90, 100]}
    other_params = {'learning_rate': 0.1, 'n_estimators': 500, 'max_depth': 5, 'min_child_weight': 1, 'seed': 0,
                    'subsample': 0.8, 'colsample_bytree': 0.8, 'gamma': 0, 'reg_alpha': 0, 'reg_lambda': 1}
    model = XGBRegressor(**other_params)
    xgb = GridSearchCV(estimator=model, param_grid=cv_params, scoring='r2', cv=5, verbose=1, n_jobs=4)
    xgb.fit(X_train, y_train)
    print(f'Best Score:{format(xgb.best_score_)}')
    best_params['n_estimators'] = xgb.best_params_['n_estimators']
    print(f'>>>Best n_estimators:{best_params["n_estimators"]}\n')

    # 调参:max_depth和num_leaves
    print(">>>Get Param:max_depth and num_leaves...")
    params_test1 = {
        'max_depth': range(3, 8, 1),
        'num_leaves': range(5, 10, 1)
    }
    lgb_model1 = lgb.LGBMRegressor(boosting_type='gbdt', objective='regression', num_leaves=50,
                                   learning_rate=0.1, n_estimators=best_params["n_estimators"], max_depth=6,
                                   metric='auc', bagging_fraction=0.8, feature_fraction=0.8)
    gsearch1 = GridSearchCV(estimator=lgb_model1, param_grid=params_test1, scoring='roc_auc', cv=5,
                            verbose=0, n_jobs=4)
    gsearch1.fit(X_train, y_train)
    best_params['max_depth'] = gsearch1.best_params_['max_depth']
    best_params['num_leaves'] = gsearch1.best_params_['num_leaves']
    print(f'>>>Best max_depth:{best_params["max_depth"]}\n>>>Best num_leaves:{best_params["max_depth"]}\n')

    # 调参:min_child_samples和min_child_weight
    print(">>>Get Param:min_child_samples and min_child_weight...")
    params_test2 = {
        'min_child_samples': [18, 19, 20, 21, 22],
        'min_child_weight': [0.001, 0.002]
    }
    lgb_model2 = lgb.LGBMRegressor(objective='regression', num_leaves=best_params["n_estimators"],
                                   learning_rate=0.1, n_estimators=best_params["max_depth"],
                                   max_depth=best_params["max_depth"],
                                   metric='auc')
    gsearch2 = GridSearchCV(estimator=lgb_model2, param_grid=params_test2, scoring='neg_mean_squared_error', cv=5,
                            verbose=1, n_jobs=4)
    gsearch2.fit(X_train, y_train)
    best_params["min_child_samples"] = gsearch2.best_params_['min_child_samples']
    best_params["min_child_weight"] = gsearch2.best_params_['min_child_weight']
    print(f'>>>Best min_child_samples:{best_params["min_child_samples"]}\n'
          f'>>>Best min_child_weight:{best_params["min_child_weight"]}\n')

    # 调参:feature_fraction 和 bagging_fraction
    print(">>>Get Param:feature_fraction and bagging_fraction...")
    params_test3 = {
        'feature_fraction': [0.6, 0.7, 0.8, 0.9, 1.0],
        'bagging_fraction': [0.6, 0.7, 0.8, 0.9, 1.0]
    }
    lgb_model3 = lgb.LGBMRegressor(objective='regression', num_leaves=best_params['num_leaves'],
                                   learning_rate=0.1, n_estimators=best_params["n_estimators"],
                                   max_depth=best_params['max_depth'],
                                   metric='auc', min_child_samples=best_params["min_child_samples"])
    gsearch3 = GridSearchCV(estimator=lgb_model3, param_grid=params_test3, scoring='neg_mean_squared_error', cv=5,
                            verbose=1, n_jobs=4)
    gsearch3.fit(X_train, y_train)
    best_params["feature_fraction"] = gsearch3.best_params_['feature_fraction']
    best_params["bagging_fraction"] = gsearch3.best_params_['bagging_fraction']
    print(f'>>>Best feature_fraction:{best_params["feature_fraction"]}\n'
          f'>>>Best bagging_fraction:{best_params["bagging_fraction"]}\n')
    best_params['learning_rate'] = 0.001
    print(">>>Get Params of LightGBM Successfully!")
    print(f">>>The Best Params of LightGBM:{best_params}\n")
    return best_params


def get_xgboost_best_params(X_train, y_train, X_test, y_test):
    """
    对XGBoost模型进行调参\n
    :return: 返回最佳参数的字典
    """
    # 参数字典
    best_params = {}
    # XGBoost调参
    print(">>>Start Get Params of XGBoost...\n")

    # 调参:n_estimators
    print(">>>Get Param:n_estimators...")
    cv_params = {'n_estimators': [20, 25, 30, 40, 50, 60, 70, 80, 90, 100]}
    other_params = {'learning_rate': 0.1, 'n_estimators': 500, 'max_depth': 5, 'min_child_weight': 1, 'seed': 0,
                    'subsample': 0.8, 'colsample_bytree': 0.8, 'gamma': 0, 'reg_alpha': 0, 'reg_lambda': 1}
    model = XGBRegressor(**other_params)
    xgb = GridSearchCV(estimator=model, param_grid=cv_params, scoring='r2', cv=5, verbose=1, n_jobs=4)
    xgb.fit(X_train, y_train)
    print(f'Best Score:{format(xgb.best_score_)}')
    best_params['n_estimators'] = xgb.best_params_['n_estimators']
    print(f'>>>Best n_estimators:{best_params["n_estimators"]}\n')

    # 调参:max_depth和min_child_weight
    print(">>>Get Param:max_depth and min_child_weight...")
    cv_params = {'max_depth': [3, 4, 5, 6, 7, 8, 9, 10], 'min_child_weight': [1, 2, 3, 4, 5, 6]}
    other_params = {'learning_rate': 0.1, 'n_estimators': best_params["n_estimators"], 'max_depth': 5,
                    'min_child_weight': 1, 'seed': 0,
                    'subsample': 0.8, 'colsample_bytree': 0.8, 'gamma': 0, 'reg_alpha': 0, 'reg_lambda': 1}
    model = XGBRegressor(**other_params)
    xgb = GridSearchCV(estimator=model, param_grid=cv_params, scoring='r2', cv=5, verbose=1, n_jobs=4)
    xgb.fit(X_train, y_train)
    print(f'Best Score:{format(xgb.best_score_)}')
    best_params['max_depth'] = xgb.best_params_['max_depth']
    best_params['min_child_weight'] = xgb.best_params_['min_child_weight']
    print(f'>>>Best max_depth:{best_params["max_depth"]}\n'
          f'>>>Best min_child_weight:{best_params["min_child_weight"]}\n')

    # 调参:gamma
    print(">>>Get Param:gamma...")
    cv_params = {'gamma': [0.1, 0.2, 0.3, 0.4, 0.5, 0.6]}
    other_params = {'learning_rate': 0.1, 'n_estimators': best_params["n_estimators"], 'seed': 0,
                    'max_depth': best_params["max_depth"], 'min_child_weight': best_params["min_child_weight"],
                    'subsample': 0.8, 'colsample_bytree': 0.8, 'gamma': 0, 'reg_alpha': 0, 'reg_lambda': 1}
    model = XGBRegressor(**other_params)
    xgb = GridSearchCV(estimator=model, param_grid=cv_params, scoring='r2', cv=5, verbose=1, n_jobs=4)
    xgb.fit(X_train, y_train)
    print(f'Best Score:{format(xgb.best_score_)}')
    best_params['gamma'] = xgb.best_params_['gamma']
    print(f'>>>Best gamma:{best_params["gamma"]}\n')

    # 调参:subsample和colsample_bytree
    print(">>>Get Param:subsample and colsample_bytree...")
    cv_params = {'subsample': [0.6, 0.7, 0.8, 0.9], 'colsample_bytree': [0.6, 0.7, 0.8, 0.9]}
    other_params = {'learning_rate': 0.1, 'n_estimators': best_params["n_estimators"], 'seed': 0, 'reg_lambda': 1,
                    'max_depth': best_params["max_depth"], 'min_child_weight': best_params["min_child_weight"],
                    'subsample': 0.8, 'colsample_bytree': 0.8, 'gamma': best_params["gamma"], 'reg_alpha': 0}
    model = XGBRegressor(**other_params)
    xgb = GridSearchCV(estimator=model, param_grid=cv_params, scoring='r2', cv=5, verbose=1, n_jobs=4)
    xgb.fit(X_train, y_train)
    print(f'Best Score:{format(xgb.best_score_)}')
    best_params['subsample'] = xgb.best_params_['subsample']
    best_params['colsample_bytree'] = xgb.best_params_['colsample_bytree']
    print(f'>>>Best subsample:{best_params["subsample"]}\n'
          f'>>>Best colsample_bytree:{best_params["colsample_bytree"]}\n')

    # 调参:reg_alpha和reg_lambda
    print(">>>Get Param:reg_alpha and reg_lambda...")
    cv_params = {'reg_alpha': [0.05, 0.1, 1, 2, 3], 'reg_lambda': [0.05, 0.1, 1, 2, 3]}
    other_params = {'learning_rate': 0.1, 'n_estimators': best_params["n_estimators"], 'seed': 0, 'reg_lambda': 1,
                    'max_depth': best_params["max_depth"], 'min_child_weight': best_params["min_child_weight"],
                    'subsample': best_params["subsample"], 'colsample_bytree': best_params["colsample_bytree"],
                    'gamma': best_params["gamma"], 'reg_alpha': 0}
    model = XGBRegressor(**other_params)
    xgb = GridSearchCV(estimator=model, param_grid=cv_params, scoring='r2', cv=5, verbose=1, n_jobs=4)
    xgb.fit(X_train, y_train)
    print(f'Best Score:{format(xgb.best_score_)}')
    best_params['reg_alpha'] = xgb.best_params_['reg_alpha']
    best_params['reg_lambda'] = xgb.best_params_['reg_lambda']
    print(f'>>>Best reg_alpha:{best_params["reg_alpha"]}\n'
          f'>>>Best reg_lambda:{best_params["reg_lambda"]}\n')

    # 调参:learning_rate
    print(">>>Get Param:learning_rate...")
    cv_params = {'learning_rate': [0.01, 0.05, 0.07, 0.1, 0.2]}
    other_params = {'learning_rate': 0.1, 'n_estimators': best_params["n_estimators"], 'seed': 0,
                    'max_depth': best_params["max_depth"], 'min_child_weight': best_params["min_child_weight"],
                    'subsample': best_params["subsample"], 'colsample_bytree': best_params["colsample_bytree"],
                    'gamma': best_params["gamma"], 'reg_alpha': best_params["reg_alpha"],
                    'reg_lambda': best_params["reg_lambda"]}
    model = XGBRegressor(**other_params)
    xgb = GridSearchCV(estimator=model, param_grid=cv_params, scoring='r2', cv=5, verbose=1, n_jobs=4)
    xgb.fit(X_train, y_train)
    print(f'Best Score:{format(xgb.best_score_)}')
    best_params['learning_rate'] = xgb.best_params_['learning_rate']
    print(f'>>>Best learning_rate:{best_params["learning_rate"]}\n')

    print(">>>Get Params of XGBoost Successfully!")
    print(f">>>The Best Params of XGBoost:{best_params}\n")
    return best_params
