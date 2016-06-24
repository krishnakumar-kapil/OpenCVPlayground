import cv2
import numpy as np

def main():
    image = cv2.imread('../../Pictures/Momentum/river.jpg')
    row, col, ch = image.shape

    noise_sigma = 25
    gauss = np.random.normal(0, noise_sigma, (row, col, ch))
    gauss = gauss.reshape(row,col, ch)
    cv2.imshow('gauss', gauss)
#    noisy = cv2.add(gauss, image) 
    noisy = gauss + image
    cv2.imshow('noisy', noisy)
    cv2.waitKey(0)

    kernel_size = 11
    filter_sigma = 2
#    gauss_kernel = cv2.getGaussianKernel(kernel_size, filter_sigma)
    blurred = cv2.GaussianBlur(image, (kernel_size, kernel_size), filter_sigma)
    cv2.imshow('blurred', blurred)
    cv2.waitKey(0)

if __name__ == '__main__':
   main()
   cv2.destroyAllWindows()
