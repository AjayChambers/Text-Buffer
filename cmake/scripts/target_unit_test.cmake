# Generates a test including a source file located in the dir
# target_unit_test(...) is called in, an executable with a
# generated test name, and a list of linked libraries that has
# to be passed in as an argument.

function(target_unit_test test_name file_name libs)
    set(test_filepath "${CMAKE_SOURCE_DIR}/tests/${file_name}")

    if(NOT EXISTS ${test_filepath})
        file(TOUCH ${test_filepath})
    endif()

    add_executable(${test_name} ${test_filepath})
    add_test(${test_name} ${test_name})


    target_link_libraries(${test_name} PUBLIC ${libs})
    target_include_directories(${test_name} PUBLIC
        "${CMAKE_SOURCE_DIR}/include"
        "${CMAKE_SOURCE_DIR}/build/_deps")
endfunction()

