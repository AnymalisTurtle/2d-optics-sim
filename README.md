# 2d-optics-sim

A fun little program to provide a simple 2d simulation for refraction and reflection.

---

## *Attention!*

Compiling and executing this program requires SFML. Since I do not have any experience with SFML yet, I will just direct you to the [Tutorial which I used](https://www.youtube.com/watch?v=rZE700aaT5I).

---

## Current State

![static image showing a point source interacting with w reflective wall and two refractive polygons: a triangle and a octagon](media\\reflection_and_refraction.png)
Refraction and Reflection have been implemented. The point source can be moved and the rays will be recalculated.
The Refractive Index is still fixed for all bodies. There is a problem due to the limits of the arcus functions: When the incomming angle of the refraction is very shallow, the multiplication with the refractive index can result in values outside of the function definition. For the time being, this has been resolved by limiting the calculated values. This however causes some weird behaviour at the edges and corners of the bodies. In reality, total internal reflaction would probably occur bevor such a shallow angle is reached -> Investigate this in the future.

![1000 pixel squared image; point source radiating 30 rays, which collide with and stop at two straight lines](media\collision.png)
Functions are in place to find the normal vector of an arbitrary line. Rays emitted by a point source collide with "walls" and do not run any further.
