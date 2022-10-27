cmake_minimum_required(VERSION 3.21.2)

add_executable(common.test common.test.cpp)
target_link_libraries(common.test PUBLIC libDamien gtest_main)
add_test(
  NAME common.test
  COMMAND common.test
)

add_executable(instruments.test instruments.test.cpp)
target_link_libraries(instruments.test PRIVATE libDamien gtest_main)
add_test(
  NAME instruments.test
  COMMAND instruments.test
)

add_executable(pricers.test pricers.test.cpp)
target_link_libraries(pricers.test PRIVATE libDamien gtest_main)
add_test(
  NAME pricers.test
  COMMAND pricers.test
)
