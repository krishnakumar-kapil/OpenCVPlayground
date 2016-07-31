import cv2
import numpy as np

friz = cv2.imread('../../Pictures/frizzy.png')
froom = cv2.imread('../../Pictures/froomer.png')
#cv2.imshow('friz', friz)
#cv2.imshow('froomer', froom)
friz = cv2.GaussianBlur(friz, (5, 5), 1)
froom = cv2.GaussianBlur(froom, (5, 5), 1)

min = 20 
max = 50
edges_friz = cv2.Canny(friz, min, max, 1)
edges_froom = cv2.Canny(froom,min, max, 1)

cv2.imshow('edges froom' , edges_froom)
cv2.imshow('edge fris', edges_friz)
cv2.waitKey(0)

new = edges_friz & edges_froom
cv2.imshow('added', new)

cv2.waitKey(0)
