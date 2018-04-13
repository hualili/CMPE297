import cv2
import numpy as np

def thresh_callback(thresh):
    edges = cv2.Canny(blur,thresh,thresh*2)
    drawing = np.zeros(frame.shape,np.uint8)     # Image to draw the contours
    _,contours,hierarchy = cv2.findContours(edges,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
    for cnt in contours:
        hull = cv2.convexHull(cnt)
        cv2.drawContours(drawing,[cnt],0,(0,255,0),2)   # draw contours in green color
        cv2.drawContours(drawing,[hull],0,(0,0,255),2)  # draw convex hull contours in red color
        cv2.imshow('output',drawing)
        print(cv2.isContourConvex(cnt))

src = cv2.VideoCapture(0)

while(1):
    ret, frame = src.read()
    # img = cv2.imread('test.jpg')
    gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    blur = cv2.GaussianBlur(gray,(5,5),0)
    ret, thresh = cv2.threshold(blur, 127, 255, 0)

    thresh_callback(ret)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

src.release()
cv2.destroyAllWindows()
