cmake_minimum_required(VERSION 3.16)
project(DataStructureCpp17 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(ds_core INTERFACE)

target_include_directories(ds_core
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(seq_list_demo
    examples/sequential_list_demo.cpp
)

target_link_libraries(seq_list_demo
    PRIVATE
        ds_core
)

add_executable(sorting_demo
    examples/sorting_demo.cpp
)

target_link_libraries(sorting_demo
    PRIVATE
        ds_core
)

add_executable(singly_linked_list_demo
    examples/singly_linked_list_demo.cpp
)

target_link_libraries(singly_linked_list_demo
    PRIVATE
        ds_core
)

add_executable(linked_stack_demo
    examples/linked_stack_demo.cpp
)

target_link_libraries(linked_stack_demo
    PRIVATE
        ds_core
)

add_executable(linked_queue_demo
    examples/linked_queue_demo.cpp
)

target_link_libraries(linked_queue_demo
    PRIVATE
        ds_core
)

add_executable(skip_list_demo
    examples/skip_list_demo.cpp
)

target_link_libraries(skip_list_demo
    PRIVATE
        ds_core
)

add_executable(binary_tree_demo
    examples/binary_tree_demo.cpp
)

target_link_libraries(binary_tree_demo
    PRIVATE
        ds_core
)

add_executable(binary_search_tree_demo
    examples/binary_search_tree_demo.cpp
)

target_link_libraries(binary_search_tree_demo
    PRIVATE
        ds_core
)

add_executable(binary_heap_demo
    examples/binary_heap_demo.cpp
)

target_link_libraries(binary_heap_demo
    PRIVATE
        ds_core
)

add_executable(disjoint_set_demo
    examples/disjoint_set_demo.cpp
)

target_link_libraries(disjoint_set_demo
    PRIVATE
        ds_core
)

add_executable(adjacency_matrix_graph_demo
    examples/adjacency_matrix_graph_demo.cpp
)

target_link_libraries(adjacency_matrix_graph_demo
    PRIVATE
        ds_core
)

add_executable(adjacency_list_graph_demo
    examples/adjacency_list_graph_demo.cpp
)

target_link_libraries(adjacency_list_graph_demo
    PRIVATE
        ds_core
)

add_executable(hash_table_demo
    examples/hash_table_demo.cpp
)

target_link_libraries(hash_table_demo
    PRIVATE
        ds_core
)

add_executable(sequential_string_demo
    examples/sequential_string_demo.cpp
)

target_link_libraries(sequential_string_demo
    PRIVATE
        ds_core
)

enable_testing()

add_executable(test_sequential_list
    tests/test_sequential_list.cpp
)

target_link_libraries(test_sequential_list
    PRIVATE
        ds_core
)

add_test(NAME sequential_list_tests COMMAND test_sequential_list)

add_executable(test_sorting
    tests/test_sorting.cpp
)

target_link_libraries(test_sorting
    PRIVATE
        ds_core
)

add_test(NAME sorting_tests COMMAND test_sorting)

add_executable(test_singly_linked_list
    tests/test_singly_linked_list.cpp
)

target_link_libraries(test_singly_linked_list
    PRIVATE
        ds_core
)

add_test(NAME singly_linked_list_tests COMMAND test_singly_linked_list)

add_executable(test_linked_stack
    tests/test_linked_stack.cpp
)

target_link_libraries(test_linked_stack
    PRIVATE
        ds_core
)

add_test(NAME linked_stack_tests COMMAND test_linked_stack)

add_executable(test_linked_queue
    tests/test_linked_queue.cpp
)

target_link_libraries(test_linked_queue
    PRIVATE
        ds_core
)

add_test(NAME linked_queue_tests COMMAND test_linked_queue)

add_executable(test_skip_list
    tests/test_skip_list.cpp
)

target_link_libraries(test_skip_list
    PRIVATE
        ds_core
)

add_test(NAME skip_list_tests COMMAND test_skip_list)

add_executable(test_tree_and_heap
    tests/test_tree_and_heap.cpp
)

target_link_libraries(test_tree_and_heap
    PRIVATE
        ds_core
)

add_test(NAME tree_and_heap_tests COMMAND test_tree_and_heap)

add_executable(test_graph
    tests/test_graph.cpp
)

target_link_libraries(test_graph
    PRIVATE
        ds_core
)

add_test(NAME graph_tests COMMAND test_graph)

add_executable(test_disjoint_set_and_hash_table
    tests/test_disjoint_set_and_hash_table.cpp
)

target_link_libraries(test_disjoint_set_and_hash_table
    PRIVATE
        ds_core
)

add_test(NAME disjoint_set_and_hash_table_tests COMMAND test_disjoint_set_and_hash_table)

add_executable(test_string
    tests/test_string.cpp
)

target_link_libraries(test_string
    PRIVATE
        ds_core
)

add_test(NAME string_tests COMMAND test_string)
