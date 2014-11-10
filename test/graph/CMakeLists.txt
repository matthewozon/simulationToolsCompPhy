cmake_minimum_required(VERSION 2.6)

#Configuration du projet
project(testGraph)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BUILD_TYPE})

#Inclusion de Boost
include_directories(. /usr/include ../../compPhy)
link_directories(. /usr/lib ../../../lib ) #/home/ozon/workspace_qtcreator/simulationToolsCompPhy/lib

#Configuration de l'exécutable
file(
	GLOB
	source_files
	*.cpp *.h
)
add_executable(
        testGraph
	${source_files}
)

#Configuration de l'édition de liens
target_link_libraries(
        testGraph
        compPhy
)





