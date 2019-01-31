'''
Caputure live Camera video, flip every frame in vertical direction and saves it.
'''

import numpy as np
import cv2

cap = cv2.VideoCapture(0)

#fourcc = cv2.VideoWriter_fourcc(*'XVID') # Define codec and create VideoWriter object
fourcc = cv2.VideoWriter_fourcc(*'X264')
out = cv2.VideoWriter('output.avi',fourcc, 20.0, (640,480),1)

'''
VideoWriter object. Specify 
(1) the FourCC code  . 
(2) number of frames per second (fps) and 
(3) frame size. And 
(4) last one is isColor flag. If it is True, encoder expects color frame, otherwise 
it works with grayscale.

FourCC is a 4-byte code, see fourcc.org for details. It is platform dependent.  

In Fedora Linux: DIVX, XVID, MJPG, X264, WMV1, WMV2. 
(XVID is more preferable. MJPG high size video. X264 gives very small size video)
  
'''

while(cap.isOpened()):
    ret, frame = cap.read()
    if ret==True:
        #frame = cv2.flip(frame,0)
        
        out.write(frame) # write the flipped frame

        cv2.imshow('frame',frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    else:
        break

# Release everything if job is finished
cap.release()
out.release()
cv2.destroyAllWindows()


