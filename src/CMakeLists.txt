cmake_minimum_required(VERSION 3.18)
project(hdf5_toy C CXX) # Specify C and C++ as the languages

find_package(MPI REQUIRED)
find_package(HDF5 REQUIRED COMPONENTS C HL)

add_executable(demo_write demo_write.cpp)
target_include_directories(demo_write PRIVATE
    ${MPI_CXX_INCLUDE_PATH} ${HDF5_INCLUDE_DIRS})
target_link_libraries(demo_write PRIVATE
    MPI::MPI_CXX ${HDF5_LIBRARIES})
set_target_properties(demo_write PROPERTIES CXX_STANDARD 17)

