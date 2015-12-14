# This script creates a model described at
# http://www.caddd.org/2010/04/opencascade-challenge.html
#Category: Modeling
#Title: CAD shape

pload MODELING VISUALIZATION

# make base 
box b0 0  0 0 12 7 6
explode b0 e
blend b01 b0 1 b0_8
blend b02 b01 1 b0_6

# make cut at bottom
box b1 3 -1 0 2 9 1.5
bcut b2 b02 b1
explode b2 e
blend b3 b2 1 b2_27
blend b4 b3 1 b2_30

# make central cut
box h1 3 -1 2.5 2 9 0.5
box h2 3 -1 3 2 9 2
plane p 4 -1 3 0 1 0
pcylinder c p 1 9
bcommon h3 h2 c
bcut b5 b4 h1
bcut b6 b5 h3

# make side cut
box b7 9 -1 1 2 9 4
explode b7 e
blend b71 b7 1 b7_6
blend b72 b71 1 b7_8
bcut b8 b6 b72

# make box for inner cylindrical cut
box bc1 -1 0 2 9 1 4
box bc2 2 -1 2 4 3 3
bcut bc3 bc1 bc2
explode bc3 e
blend bc4 bc3 1 bc3_20
blend bc5 bc4 1 bc3_23
blend bc6 bc5 1.99 bc3_21
blend bc7 bc6 1.99 bc3_22

# make inner cylindrical cut
explode bc7 f
revol r bc7_1 -1 0 6 1 0 0 100
bcut b9 b8 r

# make outer cylindrical cut
plane p2 -1 0 6 1 0 0
pcylinder c2 p2 6 15
bcommon res b9 c2

# show result
donly res
trotate res 0 0 0 0 0 1 90
vinit
vdisplay res
vsetdispmode 1
vshowfaceboundary res 1 255 255 255
vfit
