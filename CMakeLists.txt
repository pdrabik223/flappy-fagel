cmake_minimum_required(VERSION 3.21)
project(fagel)
set(CMAKE_CXX_STANDARD 14)
#st(game_engine )
set(sfml_window_dir
        window/coord.h
        window/window.h
        window/window.cpp
        window/view.h
        window/view.cpp
        )


add_subdirectory(SFML)


add_executable(main main.cpp
        ${sfml_window_dir})


set(executables main)

foreach (executable IN LISTS executables)
    target_link_directories(${executable}
            PUBLIC ${PROJECT_SOURCE_DIR}/sfml/src
            )

    target_link_libraries(${executable}
            sfml-graphics
            sfml-system
            sfml-window
            )

    target_include_directories(${executable}
            PUBLIC ${PROJECT_SOURCE_DIR}/sfml/include
            )
endforeach ()