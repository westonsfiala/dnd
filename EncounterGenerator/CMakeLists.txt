cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(EncounterGenerator)

set(src_CPP
    src/Encounter.cpp
	src/Party.cpp
	src/Monster.cpp
	src/GeneratorUtilities.cpp
)
    
set(src_H
    src/Encounter.h
	src/Party.h
	src/Monster.h
	src/GeneratorUtilities.h
)

add_library(${PROJECT_NAME} STATIC
    ${src_CPP}
    ${src_H}
	EncounterGenerator.natvis
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC nlohmann_json::nlohmann_json
)

# Provide our source for Gui to include automatically
target_include_directories(${PROJECT_NAME}
    INTERFACE .
	INTERFACE src
)

