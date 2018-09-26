project(main)
aux_source_directory(. DIR_SRCS)
add_definitions(-std=c++11)
add_executable(main ${DIR_SRCS})