import numpy as np

def gauss(x, A, mean, sigma):
    fx = A * np.sqrt(2 * np.pi) * np.exp(- (x - mean) * (x - mean) / (2 * sigma * sigma))

    return fx

def normalize(mu, sigma):
    s = 0
    for k in range(0, 161):
        s = s + np.exp(- (k - mu) * (k - mu) / (2 * sigma * sigma))

    return s
