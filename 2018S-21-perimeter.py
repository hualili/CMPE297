import numpy as np
import cv2

img = cv2.imread('car.jpg', 0)
cv2.imshow('car', img)
ret, thresh = cv2.threshold(img, 127, 255, 0)
im2, contours, hierarchy = cv2.findContours(thresh, 1, 2)

cnt = contours[0]
M = cv2.moments(cnt)
#print(M)

cx = int(M['m10']/M['m00'])
cx = int(M['m01']/M['m00'])

perimeter = cv2.arcLength(cnt,True)
print(perimeter)
cv2.waitKey(0)
