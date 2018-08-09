import numpy as np
import cv2
import matplotlib.pyplot as plt


def contrast(imgs):  # absolute Laplacian value
    h,w,c = imgs[0].shape
    n = len(imgs)
    W = np.zeros((h,w,n))
    for i in range(n):
        gray = cv2.cvtColor(imgs[i],cv2.COLOR_BGR2GRAY)
        W[:,:,i] = gray
    return W


def saturation(imgs):  # standard deviation of color (R,G,B)
    
    return imgs


def exposure(imgs):  # middle value is the best of pixel values (gaussian weighting)
    return imgs


def demoFeatures():
    img = cv2.imread('img/flash/ambient.jpg')
    print(img)
    if (img == None).any():
        print("IOerror")
    #    return
    f = contrast([img])

    cv2.imshow('contrast',f/255)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == '__main__':
    demoFeatures()
