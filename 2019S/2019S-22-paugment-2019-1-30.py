"""
pdisplay.py
Demo read and display image
"""
import sys
import cv2
import numpy as np

#main(sys.argv[1:])
window_name = 'Display Image'
 
imageName = sys.argv[1] #get file name from command line 

img = cv2.imread(imageName, cv2.IMREAD_COLOR)

M = cv2.getRotationMatrix2D((img.shape[1] / 2, img.shape[0] / 2), 10, 1)
rotate1 = cv2.warpAffine(img, M, (img.shape[1], img.shape[0]))
M = cv2.getRotationMatrix2D((img.shape[1] / 2, img.shape[0] / 2), -10, 1)
rotate2 = cv2.warpAffine(img, M, (img.shape[1], img.shape[0]))

blur1 = cv2.GaussianBlur(img, (5, 5), 3)
blur2 = cv2.GaussianBlur(img, (7, 7), 5)
blur3 = cv2.GaussianBlur(img, (9, 9), 7)

rotate1_blur1 = cv2.GaussianBlur(rotate1, (5, 5), 3)
rotate1_blur2 = cv2.GaussianBlur(rotate1, (7, 7), 5)
rotate1_blur3 = cv2.GaussianBlur(rotate1, (9, 9), 7)

rotate2_blur1 = cv2.GaussianBlur(rotate2, (5, 5), 3)
rotate2_blur2 = cv2.GaussianBlur(rotate2, (7, 7), 5)
rotate2_blur3 = cv2.GaussianBlur(rotate2, (9, 9), 7)

cv2.imwrite(imageName + "_rotate1.jpg", rotate1)
cv2.imwrite(imageName + "_rotate2.jpg", rotate2)
cv2.imwrite(imageName + "_blur1.jpg", blur1)
cv2.imwrite(imageName + "_blur2.jpg", blur2)
cv2.imwrite(imageName + "_blur3.jpg", blur3)
cv2.imwrite(imageName + "_rotate1_blur1.jpg", rotate1_blur1)
cv2.imwrite(imageName + "_rotate1_blur2.jpg", rotate1_blur2)
cv2.imwrite(imageName + "_rotate1_blur3.jpg", rotate1_blur3)
cv2.imwrite(imageName + "_rotate2_blur1.jpg", rotate2_blur1)
cv2.imwrite(imageName + "_rotate2_blur2.jpg", rotate2_blur2)
cv2.imwrite(imageName + "_rotate2_blur3.jpg", rotate2_blur3)
  
ind = 0

while True: 
    cv2.imshow(window_name, img)

    c = cv2.waitKey(500)
    if c == 27:
       break

    ind += 1

 
