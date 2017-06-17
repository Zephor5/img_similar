import time
import numpy as np
import img_similar as sim
from PIL import Image


# start=time.time()
# im1 = Image.open('take1.jpg')
# im2 = Image.open('take2.jpg')
# print "take ", time.time() - start
# ima1 = np.asarray(im1)
# ima2 = np.asarray(im2)
# print "take ", time.time() - start
# # print sim.get_fingerprint(ima)
# print sim.get_similarity(ima1, ima2)
# print "take ", time.time() - start

# print sim.set_fp_size(7)
start = time.time()
f1 = open("samples/take7.jpg")
f2 = open("samples/take8.jpg")
# time.sleep(1)
cont1=f1.read()
print sim.get_similarity(cont1, f2.read())
print sim.get_fps(cont1)
print "q take ", time.time() - start


# with open('take1.jpg', 'rb') as f:
#     # cont = f.read()
#     # print sim.decode_imgbytes(cont)
#     print sim.decode_imgbytes(f)

