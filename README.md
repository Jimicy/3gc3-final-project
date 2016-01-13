#Inspiration from around the world
Group members: Jimmy Wang, Haris Khan, Kurt DaCosta

##Instructions to run
Have OpenGL and Glut installed.
Run `make` in the directory.

##Description
A 3D globe with inspirational messages from around the world mapped to different parts of the 3D globe. You click on the green globe (message) to display the inspirational message.

Each message is mapped to their latitude & longitude where the person who said the quote lived. We converted the latitude & longitude to map to our to x,y,z on our spherical coordinate system for our 3D globe.

You can select a sphere representing the message at a specific latitude and longitude and it will display the inspirational message and who is was by as text on our 2D TEXT GUI.

The dashed lines represent the Earth Orbital Axis and the Earth Rotation Axis

![Imgur](http://i.imgur.com/Fr1zmvn.png)

We implemented:

+ lighting 5%
+ textures 10%
+ alpha blending 5%
+ Picking 10%
    + Being able to select the green spheres on the map
+ non-geometric primitives (bitmaps, pixel maps) [10%]
    + 2D GUI rasterized Text
    + glutBitmapCharacter
+ Our own idea ~5%
