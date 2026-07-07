# Minimum CMake version required for Geant4 11
cmake_minimum_required(VERSION 3.16...3.27)

# Project Name
project(FluxGeneration)

# Find Geant4 package, forcing UI and Vis libraries to be included
find_package(Geant4 REQUIRED ui_all vis_all)

# Setup Geant4 include directories and compile definitions
include(${Geant4_USE_FILE})

# Locate all source and header files in the current directory
file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

# Create the executable
add_executable(flux_gen flux_gen.cc ${sources} ${headers})

# Link the Geant4 libraries to your executable
target_link_libraries(flux_gen ${Geant4_LIBRARIES})