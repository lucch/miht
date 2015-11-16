# NOTE: With the 'REQUIRED' option, 'find_package' issues an error if the
#       package can't be found.
find_package(OpenMP REQUIRED)

# Adds compile options for targets in this directory and below.
add_compile_options(-Wall -std=c11)

# Passes the required OpenMP/pthreads flags to the compiler.  NOTE: Using
# 'target_compile_options()' works for gcc, but doesn't work for icc, because
# it needs the flag '-openmp' also in the linking stage.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Intel")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -qopt-report=5 -qopt-report-phase=ipo,loop,vec")
endif ()

option(BENCHMARK "BENCHMARK" OFF)
if (BENCHMARK)
    message(STATUS "BENCHMARK: ON")
    add_definitions(-DBENCHMARK)
else()
    message(STATUS "BENCHMARK: OFF")
endif()

# Serial (CPU)
add_executable(miht
    main.c
    ip.c
    ip.h
    miht.c
    prettyprint.c
)

target_link_libraries(miht m)

# Parallel (CPU)
add_executable(miht_par
    main.c
    ip.c
    ip.h
    miht.c
    prettyprint.c
)

target_compile_definitions(miht_par PRIVATE -DLOOKUP_PARALLEL)

target_link_libraries(miht_par m)

option(MIC "MIC" OFF)
if (MIC)
    message(STATUS "MIC: ON")
    add_compile_options(-mmic)
    # Serial (MIC)
    add_executable(miht_mic
        main.c
        ip.c
        ip.h
        miht.c
        prettyprint.c
    )

    target_link_libraries(miht_mic m)

    # Parallel (MIC)
    add_executable(miht_mic_par
        main.c
        ip.c
        ip.h
        miht.c
        prettyprint.c
    )

    target_compile_definitions(miht_mic_par PRIVATE -DLOOKUP_PARALLEL)

target_link_libraries(miht_mic_par m)
else()
    message(STATUS "MIC: OFF")
endif()

