cmake_minimum_required(VERSION 2.8)

#Configuration du projet
project(compPhy)
set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE}) #EXECUTABLE

#Inclusion de Boost
include_directories(. compPhy)
link_directories(.)

add_library(
        compPhy
	SHARED
	compPhy/PP_graph.cpp
)

#Configuration de l'édition de liens
target_link_libraries(
        compPhy
)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-O3")        ## Optimize
    set(CMAKE_EXE_LINKER_FLAGS "-s")  ## Strip binary
endif()
