# 2d-optics-sim

A little program to provide a simple 2d simulation for refraction and reflection.

---

## *SFML!*

*Compiling and executing this program requires SFML. Since I do not have any experience with SFML yet, I will just direct you to the [Tutorial which I used](https://www.youtube.com/watch?v=rZE700aaT5I).*

For Convenience, a Template for the Makefile is included in the repository. Simply change the paths for the respective SFML folders and rename the file to "Makefile". Then it should be possible to execute using 'make run' or 'make debug'.
**MAKE NEEDS TO BE INSTALLED**

---

## Current State

### Edit Mode

![Screenshot showing the UI in the new edit mode: controls to rotate, change number of rays, change size and change type of source](https://github.com/AnymalisTurtle/2d-optics-sim/blob/main/media/editModeUI.png)
An edit mode has been added, which has controls to rotate the source, change its number of ray, its size and its type (Point-/Parallel-). The mode is entered by pressing 'E' when moving a source. To signal the change the source cannot be moved in edit mode. It is left with enter, after which the **move mode is NOT reenabled**. This control sheme feels a bit akward and may be subject to change.

## Development History

### Simple UI (tooltip)

![Some Text being displayed that nothing is selected, left-click: select | right-click: create a source](https://github.com/AnymalisTurtle/2d-optics-sim/blob/main/media/noSelectUI.png)
![Text indicates the type of source that has been selected, left-click: set down | scroll: rotate | right-click: remove](https://github.com/AnymalisTurtle/2d-optics-sim/blob/main/media/PLSSelectUI.png)
Basic UI additions: There is now text at the bottom of the screen. It indicates which type of source is selected (Bottom left) and what actions can be performed (Bottom right).

### Dynamically removing sources, Parallel source

![A parallel source emitting rays through a series of convex and concave lenses](https://github.com/AnymalisTurtle/2d-optics-sim/blob/main/media/parallelSource.png)
Sources can now be removed by right clicking while moving them. Parallel sources have been added.

### Rotate Sources, create sources, automatic drawing functions

When clicking the left mouse button to move a source, now the closest source is selected. Scrolling while moving a source rotates it. Clicking the right mousebutton creates a new pointsource in the place of the mouse cursor.
For this purpose Emitters are now also stored as a linked list. The handling of the linked lists has been slightly adjusted for Emitters and Interactables:

```cpp
Interactable ** lastInteractable = new Interactable*;
*lastInteractable = 0;
Emitter ** lastEmitter = new Emitter*;
*lastEmitter = 0;
```

Using a double pointer allows to pass the same ```**Interactable``` to all functions. The actual object that ```*lastInteractable``` points to can be changed without having to pass anything.
The Polygons constructor changes to:

```cpp
Polygon(..., Interactable **last, ...){
    (...)
    this->last_element = *last;
    *last = this;
    (...)
}
```

When a function requires the current last Element, the double pointer is dereferenced and this way the current pointer to the last Element is retrieved. E.g.:

```cpp
Interactable ** obj_ptr;
(...)
r.trace(*(this->obj_ptr));
```

Functions have been introduced to draw all elements of the two linked lists automatically.

```cpp
void drawEmitters(Emitter *, sf::RenderWindow&);
void drawInteractables(Interactable *, sf::RenderWindow&);
```

### Rotatable Lenses

![A point source emitting rays towards a rotated convex and a unrotated concave Lens](https://github.com/AnymalisTurtle/2d-optics-sim/blob/main/media/rotated_Lens.png) **Introducing: Lens, rotated!**\
Vectors now have a function ```void rotate(double angle)``` which rotates the Vector by an angle. The argument phi for the Lens constructor now has a function. The lens polygon is now created like this:
1. calculate raw point from the ```shapeFct``` (stored as a Vector object)
1. rotate the resulting vector
1. get the sum of the vector calculated before and the vector to the centerpoint of the lens (given in the constructer arguments)
1. after iterating over all points, call the Polygon constructor and pass the Array of Vectors

### Concave Lenses (and shape functions)

![A point source sending rays which get refrected first by a convex Lens and then by a concave Lens](https://github.com/AnymalisTurtle/2d-optics-sim/blob/main/media/convex_concave.png)
Concave lenses have been added. The shape of the lens is determined by a lambda function x(y), which is created by a helper function. For this purpose custom types have been introduced:

```cpp
typedef std::function<double(double)> shapeFct;
typedef std::function<shapeFct(double,double)> shapeFctFct;
```

The lens constructor takes a Function of type ```shapeFctFct``` as an argument with the default value ```Lens::convexParabolic```. Together with the ```doubles b``` and ```l``` which are also passed to the constructor the respective ```shapeFct``` is created and stored inside the Lens class. This means that creating Lenses of different shapes only requires writing the corresponding ```shapeFctFct```.

### Parabolic convex lenses, move sources, angle dependent refraction/reflection (as passable functions)

![Video showing a point source being moved, and the rays being refracted by a lensshape](https://github.com/AnymalisTurtle/2d-optics-sim/blob/main/media/lens_demonstration.mp4)
A parabolic lensshape can now be created with half-width b and half-length l. The source follows the cursor after a click of the left mouse button. Clicking again sets the source in place. Refraction and Reflection Intesnsity are now dependent on the angle with which they enter. The specific function, after which these amounts are calculated can be passed as an argument when instantiating the Surface Property (the Polygon constructor also takes this argument and passes it along when creating its SurfaceProperty object). A similar setup is in place for the lensshape-function, allowing future expansion to different lens-shapes.

### Combined Reflection and Refraction

![static image showing a point source and a triangle; the rays both reflect and refract from the walls of the triangle](https://github.com/AnymalisTurtle/2d-optics-sim/blob/main/media/surface_properties.png)
A basic Surface Property class has been implemented. Walls can now reflact and refract at differing intensities. The brightness of the outgoing ray is calculated by multiplying the incomming brightness with the reflection/refraction amount.

### Refraction and Reflection

![static image showing a point source interacting with a reflective wall and two refractive polygons: a triangle and a octagon](https://github.com/AnymalisTurtle/2d-optics-sim/blob/main/media/reflection_and_refraction.png)
Refraction and Reflection have been implemented. The point source can be moved and the rays will be recalculated.
The Refractive Index is still fixed for all bodies. There is a problem due to the limits of the arcus functions: When the incomming angle of the refraction is very shallow, the multiplication with the refractive index can result in values outside of the function definition. For the time being, this has been resolved by limiting the calculated values. This however causes some weird behaviour at the edges and corners of the bodies. In reality, total internal reflaction would probably occur bevor such a shallow angle is reached -> Investigate this in the future.

### Normals and collision

![1000 pixel squared image; point source radiating 30 rays, which collide with and stop at two straight lines](https://github.com/AnymalisTurtle/2d-optics-sim/blob/main/media/collision.png)
Functions are in place to find the normal vector of an arbitrary line. Rays emitted by a point source collide with "walls" and do not run any further.
