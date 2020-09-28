cmake_minimum_required(VERSION 3.3)
project(final-project CXX)
include(.cs211/cmake/CMakeLists.txt)

set(MODEL_SRC
        # LIST ADDITIONAL MODEL .cxx FILES HERE:
        src/bullet.cxx
        src/geometry.cxx
        src/ship.cxx
        src/model.cxx)

add_program(galactic_offensive
        src/galactic_offensive.cxx
        src/ui.cxx
        # LIST ADDITIONAL NON-MODEL (UI) .cxx FILES HERE:
        ${MODEL_SRC})
target_link_libraries(galactic_offensive ge211)

add_test_program(model_test
    test/model_test.cxx
    ${MODEL_SRC})
target_link_libraries(model_test ge211)

# vim: ft=cmake
