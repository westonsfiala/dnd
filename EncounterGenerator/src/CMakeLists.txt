cmake_minimum_required(VERSION 3.2 FATAL_ERROR)


project(EncounterGenerator)

set(src_CPP
    Encounter.cpp
	Party.cpp
)
    
set(src_H
    Encounter.h
	Party.h
	Tables.h
)

add_library(${PROJECT_NAME} STATIC
    ${src_CPP}
    ${src_H}
	EncounterGenerator.natvis
)

#target_link_libraries(${PROJECT_NAME}
    #PUBLIC		OTHER_PROJECT
	#PRIVATE    OTHER_PROJECT
#)

# Provide our source for Gui to include automatically
target_include_directories(${PROJECT_NAME}
    INTERFACE .
)

