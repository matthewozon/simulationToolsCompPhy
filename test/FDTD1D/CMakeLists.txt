cmake_minimum_required(VERSION 2.6)

#Configuration du projet
project(testFDTD1D)
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
        testFDTD1D
	${source_files}
)

#Configuration de l'édition de liens
target_link_libraries(
        testFDTD1D
        compPhy
)





