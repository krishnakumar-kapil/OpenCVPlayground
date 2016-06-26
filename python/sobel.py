import cv2 
import numpy as np

image = cv2.imread('../../Pictures/boat.jpg')
sobelX = cv2.Sobel(img, cv2.CV_64F, 1,0, ksize=5)
sobelY = cv2.Sobel(img, cv2.CV_64F, 0,1, ksize=5)

imshow('x', sobelX)
imshow('y', sobelY)
