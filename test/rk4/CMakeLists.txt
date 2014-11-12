cmake_minimum_required(VERSION 2.6)

#Configuration du projet
project(testRK4)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BUILD_TYPE})

#Inclusion de Boost
include_directories(. ../../compPhy) #/usr/include
link_directories(. ../../../lib) #/usr/lib

#Configuration de l'exécutable
file(
	GLOB
	source_files
	*.cpp *.h
)
add_executable(
        testRK4
	${source_files}
)

#Configuration de l'édition de liens
target_link_libraries(
        testRK4
        compPhy
)





