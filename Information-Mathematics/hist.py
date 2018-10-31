import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

def main():
    mu1, sigma1 = 100, 15
    mu2, sigma2 = 150, 10
    x1 = mu1 + sigma1 * np.random.randn(10000)
    x2 = mu2 + sigma2 * np.random.randn(10000)
    
    print(x1)
    print(x2)

    sns.set(font_scale=1)
    sns.distplot(x1)
    sns.distplot(x2)
    plt.show()


if __name__ == '__main__':
    main()
