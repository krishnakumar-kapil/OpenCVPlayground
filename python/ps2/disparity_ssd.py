import numpy as np

def find_best_match(y_slice, img_value):
    min_err = float("inf")
    best_index = 0
    for i, y_val in enumerate(y_slice):
        sq_error = (y_val - img_value)**2
        if sq_error < min_err:
            min_err = sq_error
            best_index = i

    return best_index

def disparity_ssd(L, R):
    """Compute disparity map D(y, x) such that: L(y, x) = R(y, x + D(y, x))
    
    Params:
    L: Grayscale left image
    R: Grayscale right image, same size as L

    Returns: Disparity map, same size as L, R
    """

    # TODO: Your code here
    if L.shape != R.shape:
        return None
    height, width = L.shape
    ssd = np.zeros((height,width))
    for x in range(0, width):
        for y in range(0, height):
            # do we just find the sum of square differences between the values or do we need to figure out what the best match is for that point in the other image.
            best_x = find_best_match(R[:,y], L[x,y])
            ssd[x,y] = x - best_x

    return ssd
