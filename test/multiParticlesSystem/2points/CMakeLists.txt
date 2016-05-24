cmake_minimum_required(VERSION 2.6)

#Configuration du projet
project(test2Points)
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

#Inclusion de Boost
include_directories(. ../../../compPhy) #/usr/include
link_directories(. ../../../lib) #/usr/lib

#Configuration de l'exécutable
file(
	GLOB
	source_files
	*.cpp *.h
)
add_executable(
        test2Points
	${source_files}
)

#Configuration de l'édition de liens
target_link_libraries(
        test2Points
        compPhy
)



