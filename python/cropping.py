import cv2

im = cv2.imread('../Pictures/beach.jpg')
cv2.imshow('init', im)
cv2.waitKey(0)
new_im = im[50:100, 50:100]
cv2.imshow('new', new_im)

cv2. waitKey(0)
cv2.destroyAllWindows()
