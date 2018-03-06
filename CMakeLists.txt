cmake_minimum_required(VERSION 3.9)
project(RT)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

include_directories(include minilibx)
link_directories(minilibx)

add_executable(RT
        cl_wrap.h
        include/ft_rtv.h
        cl_wrapper.c
        scene.c
        scenes.c
        hooks.c
        create.c
        main.c)

target_link_libraries(RT -lmlx  "-framework OpenGL -framework OpenCL -framework AppKit")
