# tests project
project(tests)

add_executable(tests "FileTests.cpp")

# download gtest library
include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG        release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# connect gtest lib with tests project
target_link_libraries(tests PRIVATE GTest::gtest_main)

# set up tests
include(GoogleTest)

gtest_discover_tests(tests)

# connect bincryptor to tests
target_link_libraries(tests PRIVATE BinCryptor_lib)
target_include_directories(tests PRIVATE ${BinCryptor_SOURCE_DIR})