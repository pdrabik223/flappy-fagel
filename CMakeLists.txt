cmake_minimum_required(VERSION 3.21)
project(fagel)
set(CMAKE_CXX_STANDARD 14)

include_directories(fagel)
include_directories(window)
include_directories(matrix)
include_directories(neural_net)
add_subdirectory(SFML)


set(sfml_window_dir
        window/coord.h
        window/window.h
        window/window.cpp
        window/view.h
        window/view.cpp
        )

set(neural_net_dir
        matrix/matrix.h
        matrix/matrix.cpp
        neural_net/neural_net.h
        neural_net/neural_net.cpp
        neural_net/linear_layer.h
        neural_net/linear_layer.cpp
        )

set(fagel_dir
        fagel/fagel_engine.h
        fagel/fagel_engine.cpp
        fagel/player.h
        fagel/player.cpp
        )
add_executable(main main.cpp
        ${sfml_window_dir}
        ${fagel_dir}
        ${neural_net_dir}
        )


set(executables main)

foreach (executable IN LISTS executables)
    target_link_directories(${executable}
            PUBLIC ${PROJECT_SOURCE_DIR}/SFML/src
            )

    target_link_libraries(${executable}
            sfml-graphics
            sfml-system
            sfml-window
            )

    target_include_directories(${executable}
            PUBLIC ${PROJECT_SOURCE_DIR}/SFML/include
            )
endforeach ()