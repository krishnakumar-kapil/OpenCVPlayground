import cv2
import numpy as np
import math
import heapq

class HoughVal:
    theta = 0
    rho = 0
    num = 0
    def __init__(self, theta, rho, num):
        self.theta = theta
        self.rho = rho
        self.num = num

def draw_hough_lines(img, peaks, ):



def hough_peaks(H, num_peaks = 10, threshold = 1, nhood_size = 1):
    heap = []
    width, height = H.shape
    for rho in range(0,width):
        for theta in range(0, height):
            hough_val = HoughVal(theta, rho, H[rho][theta])
            if len(heap) < num_peaks:
                heapq.heappush(heap, hough_val)
            elif hough_val.num > heap[0].num:
                heapq.heappop(heap)
                heapq.heappush(heap, hough_val)

    q = np.zeros((num_peaks, 2))
    for i in range(0, num_peaks):
        val = heap[i]
        q[i] = [val.rho, val.theta]
    return q


def hough_transform(BW):
    h_size = 400
    height, width = BW.shape
    base_theta = 90
    delta_theta = 15
    theta = range(-base_theta, base_theta, delta_theta)
    rho = range(0,h_size)
    hough_array = np.zeros((2 * h_size, 2 * base_theta))
    for x in range(0, width):
        for y in range(0, height):
            if BW[x,y] > 0:
                for theta_val in theta:
                    rho_val = int(x * math.cos(theta_val) + y * math.sin(theta_val))
                    theta_val = int(theta_val)
#                    print "%s, %s" % (theta_val, rho_val)
#                    print(rho_val)
                    hough_array[rho_val][theta_val + base_theta] += 1
    return hough_array, theta, rho


def oneA():
    img = cv2.imread("input/ps1-input0.png")
    img_edges = cv2.Canny(img, 20, 40)
    cv2.imshow('edges', img_edges)
    cv2.imwrite('output/ps1-1-a-1.png', img_edges)
    return img_edges

def main():
    img_edges = oneA()
#    hough_transform(img_edges)
    hough_array, theta, rho = hough_transform(img_edges)
    cv2.imshow('hough',hough_array) 
    cv2.waitKey(0)
#    print(hough_array)
    peaks = hough_peaks(hough_array, num_peaks=10)
    print(peaks)

if __name__ == '__main__':
    main()
