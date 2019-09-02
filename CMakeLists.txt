cmake_minimum_required(VERSION 3.9)
project (Simulation2DPhysics)

set(SOURCE_FILES
    "./src/main.cpp"
    "./src/rectangle.cpp"
    )

add_executable(simulation_O0 ${SOURCE_FILES})
target_compile_options (simulation_O0 PRIVATE -std=c++11 -O0)
target_link_libraries (simulation_O0 jsoncpp)

add_executable(simulation_O1 ${SOURCE_FILES})
target_compile_options (simulation_O1 PRIVATE -std=c++11 -O1)
target_link_libraries (simulation_O1 jsoncpp)

add_executable(simulation_O2 ${SOURCE_FILES})
target_compile_options (simulation_O2 PRIVATE -std=c++11 -O2)
target_link_libraries (simulation_O2 jsoncpp)

add_executable(simulation_O3 ${SOURCE_FILES})
target_compile_options (simulation_O3 PRIVATE -std=c++11 -O3)
target_link_libraries (simulation_O3 jsoncpp)

add_executable(simulation_O3F ${SOURCE_FILES})
target_compile_options (simulation_O3F PRIVATE -std=c++11 -ftree-vectorize -ffast-math -mavx -O3)
target_link_libraries (simulation_O3F jsoncpp)