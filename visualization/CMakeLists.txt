# you may have a problem for compile if you run ubuntu 14.04 (maybe others too, but I did try)
# at the compilation, an error concerning python2.7 may occure
# a quick and dirty solution is to create a link. Here is what I did and it fixed the problem (but I cannot say about long term... and I am NOT proud of myself)
# sudo ln -sf /usr/lib/x86_64-linux-gnu/libpython2.7.so.1 /usr/lib/x86_64-linux-gnu/libpython2.7.so
# sudo ldconfig

cmake_minimum_required(VERSION 2.8)
 
PROJECT(simpleIteraction)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 

file(
        GLOB
        source_files
        simpleIteraction.cpp
)
add_executable(
        simpleIteraction
        ${source_files}
)

if(VTK_LIBRARIES)
  target_link_libraries(simpleIteraction ${VTK_LIBRARIES})
else()
  target_link_libraries(simpleIteraction vtkHybrid vtkWidgets)
endif()
