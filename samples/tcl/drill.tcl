# Sample: creation of simple twist drill bit
#Category: Modeling
#Title: Drill

pload MODELING VISUALIZATION

# drill parameters (some terms taken from http://www.drill-bits.cn/drill-bits-quality.asp)
dset R  4.    ;# outer radius
dset D  2*R   ;# diameter
dset Rr 3.5   ;# chisel radius (outer radius minus body clearance)

dset b  1.    ;# web thickness (approximate)
dset d  b/2

dset H  80.   ;# height of the spiral part
dset a  3.*pi ;# total angle of spiral rotation

dset sigma 118 ;# point angle, in degrees

# Create section profile by sequence of Boolean operations
# on simple planar objects
puts "Creating the drill section profile..."

polyline rectangle1 d -R 0  R -R 0  -d R 0  -R R 0  d -R 0

circle circle1 0 0 0  0 0 1 R
mkedge circle1 circle1
wire circle1 circle1

circle circle2 0 0 0  0 0 1 Rr
mkedge circle2 circle2
wire circle2 circle2

plane p0
mkface rectangle1 p0 rectangle1
mkface circle1 p0 circle1
mkface circle2 p0 circle2

bcommon sec rectangle1 circle1
# note use of 'fuse' instead of 'bfuse' -- we need to get single face
fuse sec sec circle2

# Construct flute profile so as to have cutting lip straight after sharpening.
# Here we need to take into account spiral shift of the flute edge
# along the point length -- the way to do that is to make spiral
# from the desired cutting lip edge and then intersect it by plane
polyline lip d -d/2 0  d -R -R/tan(sigma/2*pi/180)

polyline sp 0 0 0  0 0 H
cylinder cc 0 0 0  0 0 1  0 -4 0  4
line ll 0 0 a 80
trim ll ll 0 sqrt(a*a+H*H)

vertex v1 0 -R 0
vertex v2 0 -R H
trotate v2 0 0 0 0 0 1 180.*a/pi
mkedge ee ll cc v1 v2
wire gg ee
 
mksweep sp
setsweep -G gg 0 0
addsweep lip
buildsweep spiral -S

mkface f0 p0 -R R -R R
bsection sflute spiral f0

# here we rely on that section curve is parameterized from 0 to 1 
# and directed as cutting lip edge;
# note that this can change if intersection algorithm is modified
explode sflute e
mkcurve cflute sflute_1
cvalue cflute 0. x0 y0 z0
cvalue cflute 1. x1 y1 z1
vertex vf0 x0 y0 z0 
vertex vf1 x1 y1 z1

# -- variant: replace curve by arc with start at x0,y0,z0 and end at x1,y1,z1,
# -- such that tanget at start point is along Y
#dset Rflute ((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0))/(2*(x1-x0))
#circle aflute x0+Rflute y0 0  0 0 1  Rflute
#mkedge sflute_1 aflute vf0 vf1

# make rounding in the flute; use circle with radius Rr/2
circle cround x0+Rr/2 y0 0  0 0 1 Rr/2
vertex vf3 x0+Rr y0 0 
mkedge sflute_2 cround vf3 vf0
vertex vf2 R -R 0
edge sflute_3 vf3 vf2
edge sflute_4 vf2 vf1
wire w2 sflute_1 sflute_2 sflute_3 sflute_4
mkface flute p0 w2

# cut flute from profile
bcut sec sec flute
trotate flute 0 0 0 0 0 1 180.
bcut sec sec flute
donly sec

# sweep profile to get a drill body
puts "Sweeping the profile..."

mksweep sp
setsweep -G gg 0 0
explode sec w
addsweep sec_1
buildsweep base -S

# sharpen the drill (see http://tool-land.ru/zatochka-sverla.php)
puts "Sharpening..."

dset theta a*R/H*sin((90-sigma/2)*pi/180)
plane ax1 d 1.9*D "H+1.9*D/tan(pi/180.*sigma/2.)" 0 -1 -1
pcone sh1 ax1 0 100*sin((sigma-90)/2*pi/180.) 100
trotate sh1 0 0 0 0 0 1 -theta*180/pi
tcopy sh1 sh2
trotate sh2 0 0 0 0 0 1 180
box sh -D/2 -D/2 72 D D 20
bcommon qq sh1 sh2
bcut sharpener sh qq

bcut body base sharpener

# make a shank
puts "Making a shank..."
plane pl2 0 0 -40  0 0 1
pcylinder shank pl2 4 40
pcone transit R 0 R
plane pl3 0 0 -40  0 0 -0.5
pcone tail pl3 R 0 0.5
bfuse shank shank tail
bfuse shank shank transit
bfuse drill body shank

# check result
checkshape drill

# show result
puts "Displaying result..."
incmesh drill 0.01
vdisplay drill
vsetdispmode drill 1
vfit

# show section and sweep path
ttranslate sec_1 0 0 H; trotate sec_1 0 0 0 0 0 1 a*180/pi; incmesh gg 0.01; vdisplay gg sec_1
