# Проверяем что тесты включены
if(BUILD_TESTING)
    # Находим зависимости для тестов
    find_package(Boost REQUIRED COMPONENTS unit_test_framework filesystem system)

    # Исполняемый файл тестов
    add_executable(test_bulk tests.cpp)
    
    # Директории include
    target_include_directories(test_bulk PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src
    )
    
    # Линковка
    target_link_libraries(test_bulk PUBLIC
        Boost::unit_test_framework
        Boost::filesystem
        Boost::system
    )

     # ВАЖНО: Добавляем флаг для динамической линковки Boost.Test
    #target_compile_definitions(test_bulk PRIVATE BOOST_TEST_DYN_LINK)
    
    # Копируем тестовые данные в build директорию
    file(COPY 
        test1.in
        test1.out
        test2.in
        test2.out
        DESTINATION ${CMAKE_BINARY_DIR}/tests
    )
    
    # Добавляем тест в CTest
    add_test(NAME bulk_test 
        COMMAND test_bulk
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )
    
endif()
