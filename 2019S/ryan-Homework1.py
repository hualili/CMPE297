# program: .py;    coded by:                        *
# architect:                                        * 
# date   : Jan 01, 2019;    status  : tested;       * 
# purpose:                                          * 
#                                                   * 
#---------------------------------------------------* 
import cv2
import numpy as np

# Load an color image in grayscale
img = cv2.imread('IMG_3923.jpg',cv2.IMREAD_GRAYSCALE)
res = cv2.resize(img,None,fx=1/5,fy=1/5,interpolation = cv2.INTER_CUBIC)
shape = res.shape
# Blurring using Gaussian filtering
blur = cv2.GaussianBlur(res,(5,5),0)

# Otsu’s Binarization
ret, thresh = cv2.threshold(blur,0,255,cv2.THRESH_BINARY+cv2.THRESH_OTSU)

# Find contours
contours, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    
# Area threshold and hierarchy select
areaThresh = []
areas = []

for i, cnt in enumerate (contours):
    area = cv2.contourArea(cnt)
    areas.append(area);
    if(area > 490 and area < 11000):
        
        areaThresh.append(cnt)
areas.sort(reverse = True)

"""
print(areas)
canvas_tmp = np.zeros((830,1200,3), np.uint8)
cv2.drawContours(canvas_tmp, areaThresh, -1, (0,255,0), 3)
cv2.imshow('canvas_tmp',canvas_tmp)
"""

canvas = np.zeros((shape[0],shape[1],3), np.uint8)

roiNum = 0
sop = []
for i, cnt in enumerate(areaThresh):
    x1 = True
    x2 = True
    x3 = True

    x,y,w,h = cv2.boundingRect(cnt)

    # Stage II:
    # Aspect ratio
    aspect_ratio = float(w)/h
    if(aspect_ratio > 0.9):
        x1 = False
#        sop.append(cnt)

    # Orientation
    if(cnt.shape[0] > 4):
        (xo,yo),(MA,ma),angle = cv2.fitEllipse(cnt)
        if(angle < 140 and angle > 30):
            x2 = False
#            sop.append(cnt)

    if hierarchy[0][i][3] == -1:
        x3 = False

#cv2.drawContours(canvas, sop, -1, (0,255,0), 3)
#cv2.imshow('Contours',canvas)        

    if(x1 and x2 and x3 == True):
        sop.append(cnt)
        #Stage II: Bouding rectangle
        cv2.rectangle(canvas,(x,y),(x+w,y+h),(0,255,0),2)
        roi = res[y:y+h, x:x+w]

        #cv2.imshow('ROI',roi)
        #k = cv2.waitKey(0) & 0xFF

        cv2.imwrite('ROI' + str(roiNum) + '.png',roi)        
        roiRes = cv2.resize(roi,(28,28),interpolation = cv2.INTER_CUBIC)
        cv2.imwrite('ROI_Resize' + str(roiNum) + '.png',roiRes)  
        roiNum = roiNum + 1

digits = cv2.drawContours(canvas, sop, -1, (0,255,0), 3)
cv2.imshow('Contours',canvas)

cv2.imshow('original digits',res)
cv2.imshow('blured digits',blur)
cv2.imshow('digits with binarization',thresh)

k = cv2.waitKey(0) & 0xFF
if k == 27:         # wait for ESC key to exit
    cv2.destroyAllWindows()
elif k == ord('s'): # wait for 's' key to save and exit
    cv2.imwrite('messigray.png',img)
    cv2.destroyAllWindows()
