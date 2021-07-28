


add_executable(test-bindings test-bindings.cpp)
target_link_libraries(test-bindings PUBLIC ccbindings)
target_include_directories(test-bindings PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/../..
    ${CMAKE_CURRENT_LIST_DIR}/../../cocos
)