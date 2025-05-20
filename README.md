# 2d-optics-sim

A little program to provide a simple 2d simulation for refraction and reflection.

---

## *SFML!*

*Compiling and executing this program requires SFML. Since I do not have any experience with SFML yet, I will just direct you to the [Tutorial which I used](https://www.youtube.com/watch?v=rZE700aaT5I).*

For Convenience, a Template for the Makefile is included in the repository. Simply change the paths for the respective SFML folders and rename the file to "Makefile". Then it should be possible to execute using 'make run' or 'make debug'.
**MAKE NEEDS TO BE INSTALLED**

---

## Current State

![A point source sending rays which get refrected first by a convex Lens and then by a concave Lens](https://github.com/AnymalisTurtle/2d-optics-sim/blob/main/media/convex_concave.png)
Concave lenses have been added. The shape of the lens is determined by a lambda function x(y), which is created by a helper function. For this purpose custom types have been introduced:

```cpp
typedef std::function<double(double)> shapeFct;
typedef std::function<shapeFct(double,double)> shapeFctFct;
```

The lens constructor takes a Function of type ```shapeFctFct``` as an argument with the default value ```Lens::convexParabolic```. Together with the ```doubles b``` and ```l``` which are also passed to the constructor the respective ```shapeFct``` is created and stored inside the Lens class. This means that creating Lenses of different shapes only requires writing the corresponding ```shapeFctFct```.

## Development History

![Video showing a point source being moved, and the rays being refracted by a lensshape](https://github.com/AnymalisTurtle/2d-optics-sim/blob/main/media/lens_demonstration.mp4)
A parabolic lensshape can now be created with half-width b and half-length l. The source follows the cursor after a click of the left mouse button. Clicking again sets the source in place. Refraction and Reflection Intesnsity are now dependent on the angle with which they enter. The specific function, after which these amounts are calculated can be passed as an argument when instantiating the Surface Property (the Polygon constructor also takes this argument and passes it along when creating its SurfaceProperty object). A similar setup is in place for the lensshape-function, allowing future expansion to different lens-shapes.

![static image showing a point source and a triangle; the rays both reflect and refract from the walls of the triangle](https://github.com/AnymalisTurtle/2d-optics-sim/blob/main/media/surface_properties.png)
A basic Surface Property class has been implemented. Walls can now reflact and refract at differing intensities. The brightness of the outgoing ray is calculated by multiplying the incomming brightness with the reflection/refraction amount. 

![static image showing a point source interacting with a reflective wall and two refractive polygons: a triangle and a octagon](https://github.com/AnymalisTurtle/2d-optics-sim/blob/main/media/reflection_and_refraction.png)
Refraction and Reflection have been implemented. The point source can be moved and the rays will be recalculated.
The Refractive Index is still fixed for all bodies. There is a problem due to the limits of the arcus functions: When the incomming angle of the refraction is very shallow, the multiplication with the refractive index can result in values outside of the function definition. For the time being, this has been resolved by limiting the calculated values. This however causes some weird behaviour at the edges and corners of the bodies. In reality, total internal reflaction would probably occur bevor such a shallow angle is reached -> Investigate this in the future.

![1000 pixel squared image; point source radiating 30 rays, which collide with and stop at two straight lines](https://github.com/AnymalisTurtle/2d-optics-sim/blob/main/media/collision.png)
Functions are in place to find the normal vector of an arbitrary line. Rays emitted by a point source collide with "walls" and do not run any further.
