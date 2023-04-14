cmake_minimum_required(VERSION 3.14)
project(SmartCam)

add_subdirectory(src)
add_subdirectory(test)

set_target_properties(SmartCam PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../build_smartcam/)
set_property(TARGET SmartCam PROPERTY AUTOMOC ON)
add_compile_options(-Wall)

enable_testing()

add_test(
        NAME test
        COMMAND ./test/main
)