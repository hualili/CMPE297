'''
display live CAM video 
'''

import numpy as np
import cv2

cap = cv2.VideoCapture(0)

while(True):

    ret, frame = cap.read() 

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    cv2.imshow('original',frame)
    cv2.imshow('gray scale',gray)

    roi_frame = frame[100:300, 300:500] #row, col
    cv2.imshow('roi',roi_frame)

    #cv2.rectangle(frame,(100,500),(400,700),(0,255,0),3)
    cv2.rectangle(frame,(300,100),(500,400),(0,255,0),3) #col, row

    #r = cv2.selectROI(frame)    # Select ROI
    #roi2 = frame[int(r[1]):int(r[1]+r[3]), int(r[0]):int(r[0]+r[2])]
    cv2.imshow("Draw_roi", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
 
cap.release()
cv2.destroyAllWindows()
