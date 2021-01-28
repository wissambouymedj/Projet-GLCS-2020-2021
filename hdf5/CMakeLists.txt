cmake_minimum_required(VERSION 3.18)

find_package(HDF5 REQUIRD COMPONENTS C )

add_library(hdf5
		src/hdf5.cpp
		
)
target_include_directories(hdf5 PUBLIC include/)
target_link_libraries(hdf5 PUBLIC MPI::MPI_CXX hdf5::hdf5 baselib)
add_library(GLCS2020_project::baselib ALIAS hdf5)
