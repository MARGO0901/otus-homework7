cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(bulk VERSION ${PROJECT_VERSION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)

add_executable(bulk main.cpp)

set_target_properties(bulk PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
 #   add_test(test_version test_version)
endif()
