#----------------------------------------------------------*
# program : load_predict.py;                               *
# last update: April 6, 2019                               * 
# version : x0.10;                    status: tested;      *  
#                                                          *
# purpose : demo of mnist net for hand written numerals    * 
#           recognition with pre-trained model in "*.h5"   *  
#           file and test it out with image input.         * 
#----------------------------------------------------------*
from keras.models import load_model
import cv2
import numpy as np
from PIL import Image

model = load_model('mnist.h5')
model.compile(optimizer='rmsprop',
                loss='categorical_crossentropy',
                metrics=['accuracy'])

img = Image.open('1.jpg').convert('L') # Image.open('1.jpg').convert('L') to greyscale mode
img = np.resize(img, (28,28,1))
im2arr = np.array(img)
im2arr = im2arr.reshape(1,28*28)
im2arr = im2arr.astype('float32')/255
y_pred = model.predict_classes(im2arr)
print(y_pred)

