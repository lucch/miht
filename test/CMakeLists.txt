# NOTE: With the 'REQUIRED' option, 'find_package' issues an error if the
#       package can't be found.
find_package(OpenMP REQUIRED)

# Passes the required OpenMP/pthreads flags to the compiler.  NOTE: Using
# 'target_compile_options()' works for gcc, but doesn't work for icc, because
# it needs the flag '-openmp' also in the linking stage.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")

# Adds compile options for targets in this directory and below.
add_compile_options(-Wall  -std=c11)

include_directories(../src)

add_executable(miht_test 
	main.c
	../src/ip.c
	../src/ip.h
	../src/miht.c
)

# Passes the required flags to the linker.
if (UNIX AND NOT APPLE)
	target_link_libraries(miht_test rt)
endif ()

target_link_libraries(miht_test m)

