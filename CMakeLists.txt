cmake_minimum_required(VERSION 3.2)

project(testCmake VERSION 0.0.1)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

add_executable(testCmake_cli main.cpp)
add_library(testCmake project_version.cpp)
add_executable(test_version test_version.cpp)

set_target_properties(testCmake_cli testCmake test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(testCmake
    PRIVATE "${CMAKE_BINARY_DIR}"
)
set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(testCmake_cli PRIVATE
    testCmake
)
target_link_libraries(test_version
    ${Boost_LIBRARIES}
    testCmake
)

if (MSVC)
    target_compile_options(testCmake_cli PRIVATE
        /W4
    )
    target_compile_options(testCmake PRIVATE
        /W4
    )
    target_compile_options(test_version PRIVATE
        /W4
    )
else ()
    target_compile_options(testCmake_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(testCmake PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS testCmake_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT ap@devandy.me)

include(CPack)

enable_testing()

add_test(test_version test_version)