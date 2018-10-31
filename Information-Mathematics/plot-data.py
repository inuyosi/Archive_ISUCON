import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

def Y(x, W):
    N = len(x)
    P = []
    for i in range(N):     # 多項式計算
        tmp = 0
        for j in range(D+1):
            tmp += (x[i]**(j)) * W[j]
        P.append(tmp)
    return np.array(P)

def estimate(x, y):
    # 対数尤度の式を各係数で編微分した結果から得られる方程式の係数行列を作成
    Sym = []
    for i in range(D+1):
        for j in range(D+1):
            Sym.append((x**(i+j)).sum())
    Sym = np.array(Sym).reshape(D+1, D+1)
    R = []
    N = len(y)
    for i in range(D+1):     # 右辺の列ベクトルを作成
        tmp = 0
        for j in range(N):
            tmp += y[j] * x[j]**i
        R.append(tmp)
    R = np.array(R).T
    W = np.linalg.solve(Sym, R)
    return W

def main():
    data = pd.read_csv('input.txt') # データセットを読み込む
    data.Score /= 200 #絶対値を揃える
    sns.set(font_scale=1)
    sns.lmplot(x='Score', y='Y', hue='A', data=data,palette="Set1")
    data1 = data[data.A != 0]
    data = data[data.A != 1]
    sns.distplot(data1['Score'],color="r")
    sns.distplot(data['Score'])
    plt.show()
    data = data.sort_values(by='Score')     #ソート
    x = np.array(data['Score'])
    y = np.array(data['Y'])
    n = len(x)
    w = estimate(x, y)     # 多項式の係数を推定
    p = Y(x, w)
    data1 = data1.sort_values(by='Score')     #ソート
    x1 = np.array(data1['Score'])
    y1 = np.array(data1['Y'])
    n1 = len(x1)
    w1 = estimate(x1, y1)     # 多項式の係数を推定
    p1 = Y(x1, w1)
    beta = np.sqrt(((p-y)**2).sum() / n)    # 予測値の標準偏差を求める
    beta1 = np.sqrt(((p1-y1)**2).sum() / n1)    # 予測値の標準偏差を求める
    print('標準偏差')
    print(beta)
    print('標準偏差')
    print(beta1)
    up  = p + 1.96*beta    # 95%信頼区間
    low = p - 1.96*beta
    up1  = p1 + 1.96*beta1    # 95%信頼区間
    low1 = p1 - 1.96*beta1
    sns.set_style("whitegrid")
    sns.set(font_scale=1)
    plt.title('{} dimensions'.format(D))
    plt.plot(x, y, 'g--', label='observation') # 観測データ
    plt.plot(x, p, 'b-' , label='prediction')  # 予測データ
    plt.plot(x, up, 'y--')
    plt.plot(x, low, 'y--')
    plt.legend() # ラベルを表示
    plt.xlabel('Score')
    plt.ylabel('Prediction')
    plt.show()
    plt.title('{} dimensions'.format(D))
    plt.plot(x1, y1, 'g--', label='observation') # 観測データ
    plt.plot(x1, p1, 'r-' , label='prediction')  # 予測データ
    plt.plot(x1, up1, 'y--')
    plt.plot(x1, low1, 'y--')
    plt.legend() # ラベルを表示
    plt.xlabel('Score')
    plt.ylabel('Prediction')
    plt.show()

if __name__ == '__main__':
    D = 3 # n次多項式の次数
    main()
