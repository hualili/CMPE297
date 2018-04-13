import numpy as np
import cv2 as cv

img = cv.imread('star.jpg')
img = cv.resize(img, (0,0), fx=0.3, fy=0.3)

img_gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

ret, thresh = cv.threshold(img_gray,200,255,0)
_, contours, hierarchy = cv.findContours(thresh, cv.RETR_TREE, cv.CHAIN_APPROX_NONE)

contours = [cv.approxPolyDP(cnt, 3, True) for cnt in contours]

cnt = contours[0]

area = cv.contourArea(cnt)

cv.drawContours(img, contours, 1, (255,128,255), cv.FILLED)
cv.namedWindow("Area", cv.WINDOW_NORMAL)
cv.imshow("Area", img)
# cv.resizeWindow("Area", 600, 600)
print(area)
cv.waitKey(0)