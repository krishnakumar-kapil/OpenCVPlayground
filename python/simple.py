import cv2 
import numpy as np

im = cv2.imread('../Pictures/beach.jpg')
cv2.imshow('res', im)
cv2.waitKey(0)
cv2.destroyAllWindows()
