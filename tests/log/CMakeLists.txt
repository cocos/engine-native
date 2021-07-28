


add_executable(test-log test-log.cpp)
target_link_libraries(test-log PUBLIC cclog)
target_include_directories(test-log PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/../..
    ${CMAKE_CURRENT_LIST_DIR}/../../cocos
)