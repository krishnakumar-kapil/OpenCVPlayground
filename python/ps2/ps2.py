# ps2
import os
import numpy as np
import cv2

## 1-a
# Read images
L = cv2.imread(os.path.join('input', 'pair0-L.png'), 0) * (1.0 / 255.0)  # grayscale, [0, 1]
R = cv2.imread(os.path.join('input', 'pair0-R.png'), 0) * (1.0 / 255.0)

# Compute disparity (using method disparity_ssd defined in disparity_ssd.py)
from disparity_ssd import disparity_ssd
D_L = disparity_ssd(L, R)
D_R = disparity_ssd(R, L)

# TODO: Save output images (D_L as output/ps2-1-a-1.png and D_R as output/ps2-1-a-2.png)
# Note: They may need to be scaled/shifted before saving to show results properly
def normalize_im(D):
    min = D.min()
    if min < 0:
        D += np.abs(min)
    max = D.max()
    D *= 255.0/max
    return D

D_L = normalize_im(D_L)
D_R = normalize_im(D_R)
cv2.imwrite('output/ps2-1-a-1.png', np.clip(D_L, 0, 255).astype(np.uint8))
cv2.imwrite('output/ps2-1-a-2.png', np.clip(D_R, 0, 255).astype(np.uint8))

# TODO: Rest of your code here
