import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from scipy.stats import binom
import sys

argvs = sys.argv  # コマンドライン引数を格納したリストの取得
argc = len(argvs) # 引数の個数

# probability that X=1
p = np.random.rand()
print('確率:',p)
for i in range(2): #引数の数字をそれぞれ描画
    N = int(argvs[i+1])
    k = np.arange(N+1)

    fig, ax = plt.subplots(1,1)
    bin=binom.pmf(k, N, p) #二項分布
    ax.plot(k, bin , 'bo', ms=8)
    ax.vlines(k, 0, bin, colors='b', lw=2, alpha=0.5)
    ax.set_xlabel('k')
    ax.set_ylabel('probability (X=1)')
    ax.set_title('binomial pmf')
    ax.set_ylim((0,1))
    print(N,'回の確率:',bin.argmax()/N)
    plt.show() #描画
