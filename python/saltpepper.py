import cv2
import numpy as np

def sandp(sigma, image, salt_prop):
    op = image
    num_salt = np.ceil(sigma * image.size * salt_prop)
    coords = [np.random.randint(0, i - 1, int(num_salt))
                for i in image.shape]

    op[coords] = 1
    num_pepper = np.ceil(sigma* image.size * (1. - salt_prop))
    coords = [np.random.randint(0, i - 1, int(num_pepper))
                 for i in image.shape]
    op[coords] = 0
    return op

def main():
    image = cv2.imread('../../Pictures/lena.tiff',0)
    op = sandp(.004, image, 0.5)
    cv2.imshow('s&p', op)
    cv2.waitKey(0)

    op = cv2.medianBlur(op, 5)
    cv2.imshow('s&p', op)
    cv2.waitKey(0)



if __name__ == '__main__':
    main()
