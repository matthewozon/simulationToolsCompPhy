Simple iteractions: dynamics scene
======================

#Thanks
VTK code deeply inspired by the examples:

    1. http://www.vtk.org/Wiki/VTK/Examples/Cxx/Filtering/CombinePolyData
    2. http://www.vtk.org/Wiki/VTK/Examples/Cxx/Utilities/AnimationScene
I thanks the authors of thoses examples that were really helpfull.

#In brief

This code is a simple example of how to simulate interaction between two objects (proportional to the distance) and show the result in an animated scene. Only one mapper and actor are used. The appendPolyData gather the objects to be rendered

#note to my future self

use a vector of objects whose interaction are given by the library compPhy
