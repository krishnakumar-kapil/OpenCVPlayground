import cv2 
import numpy as np

image = cv2.imread('../../Pictures/boat.jpg', 0)
image = cv2.GaussianBlur(image, (25, 25), 3)
sobelX = cv2.Sobel(image, cv2.CV_64F, 1,0, ksize=5)
sobelY = cv2.Sobel(image, cv2.CV_64F, 0,1, ksize=5)

cv2.imshow('x', sobelX)
cv2.imshow('y', sobelY)
cv2.waitKey(0)
