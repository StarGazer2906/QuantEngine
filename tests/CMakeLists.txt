# =====================================================================
# 1. Download GoogleTest once and add it to the build
# =====================================================================
include(FetchContent)        # loads CMake's "download a dependency" tool

FetchContent_Declare(
    googletest                                             # our name for the dependency
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2   # pinned release: same version on every machine, every time
    GIT_SHALLOW    TRUE      # download only that version, not the whole history
)
FetchContent_MakeAvailable(googletest)   # downloads it (first configure only) and creates
                                         # the targets GTest::gtest and GTest::gtest_main

include(GoogleTest)          # gives us gtest_discover_tests()

# =====================================================================
# 2. GoogleTest-based tests
# =====================================================================
add_executable(test_date test_date.cpp)
target_link_libraries(test_date PRIVATE qe GTest::gtest_main)  # our library + GoogleTest (with a ready-made main)
gtest_discover_tests(test_date)          # registers every TEST(...) in the file with CTest, one by one

# =====================================================================
# 3. Old assert-based tests (ported to GoogleTest one at a time)
# =====================================================================
add_executable(test_calendar test_calendar.cpp)
target_link_libraries(test_calendar PRIVATE qe)
add_test(NAME test_calendar COMMAND test_calendar)

add_executable(test_daycount test_daycount.cpp)
target_link_libraries(test_daycount PRIVATE qe)
add_test(NAME test_daycount COMMAND test_daycount)

add_executable(test_schedule test_schedule.cpp)
target_link_libraries(test_schedule PRIVATE qe)
add_test(NAME test_schedule COMMAND test_schedule)
