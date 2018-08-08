import numpy as np
import cv2
import matplotlib.pyplot as plt


def contrast(imgs):  # absolute Laplacian value
    return imgs


def saturation(imgs):  # standard deviation of color (R,G,B)
    return imgs


def exposure(imgs):  # middle value is the best of pixel values (gaussian weighting)
    return imgs


def demoFeatures():
    img = cv2.imread('img/flash/ambient.jpg')
    f = contrast([img])

    cv2.imshow('contrast', f)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == '__main__':
    demoFeatures()
