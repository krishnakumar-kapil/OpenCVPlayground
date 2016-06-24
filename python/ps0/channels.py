# Program to swap the channels of an image  based on 
# https://docs.google.com/document/d/1PO9SuHMYhx6nDbB38ByB1QANasP1UaEiXaeGeHmp3II/pub?embedded=true
import cv2
import numpy as np

def pixel_values(image):
    width, height, ch = image.shape
    green_channel = image[:,:, 1]
    mean = np.mean(green_channel)
    std = np.std(green_channel)

    green_mean = green_channel - np.full((width, height), mean)
    cv2.imshow('green - mean', green_mean)

def rep_pixels(image):
    width, height, ch = image.shape
    sub_image = image[0:100, 0:100, 1]

    new_image = np.zeros((width, height, 3), dtype=np.uint8)
    new_image[0:100,0:100,1] = sub_image
    new_image[:, :, 0]= image[:, :, 0]
    new_image[0:100,0:100,0] = np.zeros((100,100), dtype=np.uint8)

    cv2.imshow('new_image', new_image)
    cv2.waitKey(0)


def red(image):
    cv2.imshow('red', image[:,:,0])
    cv2.waitKey(0)

# Green channel works better since it doesn't seem faded and correctly represents the image in greyscale
def green(image):
    cv2.imshow('green', image[:,:,1])
    cv2.waitKey(0)

def swapper(image):
    red_channel = image[:,:,0]
    blue_channel = image[:,:,2]
    image[:,:,0] = blue_channel
    image[:,:,2] = red_channel
    cv2.imshow('image', image)
    cv2.waitKey(0)

def main():
    image = cv2.imread('../../../Pictures/lena.tiff')
    #swapper(image)
    #green(image)
    #red(image)
    rep_pixels(image)

if __name__ == '__main__':
    main()
