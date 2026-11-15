add_executable(test_date test_date.cpp)
target_link_libraries(test_date PRIVATE qe)
add_test(NAME test_date COMMAND test_date) #registers the test with CTest

add_executable(test_calendar test_calendar.cpp)
target_link_libraries(test_calendar PRIVATE qe)
add_test(NAME test_calendar COMMAND test_calendar)

add_executable(test_daycount test_daycount.cpp)
target_link_libraries(test_daycount PRIVATE qe)
add_test(NAME test_daycount COMMAND test_daycount) #registers the test with CTest

add_executable(test_schedule test_schedule.cpp)
target_link_libraries(test_schedule PRIVATE qe)
add_test(NAME test_schedule COMMAND test_schedule)
