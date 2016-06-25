#Program to test the visibility of noise sigmas in the images
# https://docs.google.com/document/d/1PO9SuHMYhx6nDbB38ByB1QANasP1UaEiXaeGeHmp3II/pub?embedded=true

import cv2
import numpy as np

RED = 0
GREEN = 1
BLUE = 2

def noise_channel(channel, max):
    image = cv2.imread('../../../Pictures/lena.tiff')
    row, col, ch = image.shape

    for noise_sigma in range(1,max):
        gauss_noise = np.random.normal(0, noise_sigma, (row,col))
        noisy_image = image[:,:,:].copy()
        noisy_image[:,:,channel] = gauss_noise + image[:,:,channel]
        display = "noisy_image: " + str(noise_sigma)
        cv2.imshow(display, noisy_image)
        cv2.waitKey(0)

def main():
    noise_channel(BLUE, 20)


if __name__ == '__main__':
    main()
