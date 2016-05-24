cmake_minimum_required(VERSION 2.8)

#Project config
project(compPhy)
set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE}) #lib/
include_directories(. compPhy)
link_directories(.)

#add source files to the library
add_library(
        compPhy
	SHARED
	compPhy/PP_graph.cpp
        compPhy/PP_RK4.cpp
        compPhy/PP_euler.cpp
        compPhy/PP_FDTD_1D.cpp
        compPhy/PP_smartAlloc.cpp
        compPhy/PP_particle.cpp
        compPhy/PP_object.cpp
        compPhy/PP_COORD.cpp
        compPhy/PP_particle_set.cpp
)


target_link_libraries(
        compPhy
)

#options
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-O2")        ## Optimize
    set(CMAKE_EXE_LINKER_FLAGS "-s")  ## Strip binary
endif()
