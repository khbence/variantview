find_package(GTest)

add_executable(${TEST_BINARY} main.cpp)

target_link_libraries(${TEST_BINARY} ${VARIANT_VIEWS_LIBRARY} gtest gtest_main)
target_sources(${TEST_BINARY} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/tVariantViews.cpp)


enable_testing()

add_test(NAME google_test COMMAND $<TARGET_FILE:${TEST_BINARY}>)
