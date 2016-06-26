import cv2
import numpy as np

image = cv2.imread('../../Pictures/boat.jpg')
width, height, channel = image.shape
print width, height
template = cv2.imread('../../Pictures/boat_temp.jpg')
w, h, ch= template.shape

res = cv2.matchTemplate(image, template,cv2.TM_CCOEFF_NORMED)
cv2.imshow('result', res)

min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(res)
top_left = max_loc
bottom_right = (top_left[0] + w, top_left[1] + h)
cv2.rectangle(image, top_left, bottom_right, 255, 2)
cv2.imshow('rect', image)
cv2.waitKey(0)
