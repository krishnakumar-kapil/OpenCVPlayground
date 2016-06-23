import cv2

def blend(a, b, alpha):
    return cv2.addWeighted(a, alpha, b, 1 - alpha, 0)

def main():
    a = cv2.imread('../Pictures/Momentum/river.jpg')
    b = cv2.imread('../Pictures/Momentum/tree.jpg')

    blended = blend(a, b, 0.5)
    cv2.imshow('blended', blended)
    cv2.waitKey(0)

if __name__ == '__main__':
    main()
