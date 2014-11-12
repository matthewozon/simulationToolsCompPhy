cmake_minimum_required(VERSION 2.6)

#Configuration du projet
project(testEULER)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BUILD_TYPE})

#Inclusion de Boost
include_directories(. ../../compPhy)
link_directories(. ../../../lib)

#Configuration de l'exécutable
file(
	GLOB
	source_files
	*.cpp *.h
)
add_executable(
        testEULER
	${source_files}
)

#Configuration de l'édition de liens
target_link_libraries(
        testEULER
        compPhy
)





