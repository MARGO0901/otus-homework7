set(SOURCES main.cpp context.cpp state.cpp)

add_executable(bulk ${SOURCES})

target_include_directories(bulk PRIVATE ${CMAKE_CURRENT_DIR})

find_package(Boost REQUIRED COMPONENTS filesyastem system)

target_link_libraries(bulk PRIVATE Boost::filesystem Boost::system)

install(TARGETS bulk RUNTIME DESTINATION bin COMPONENT bulk_runtime)
