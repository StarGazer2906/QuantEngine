add_library(qe STATIC 
src/Calendar.cpp
src/Schedule.cpp
src/calendar/USExchangeCalendar.cpp
src/date/Date.cpp
src/daycount/Actual360.cpp
src/daycount/ActualActual.cpp
src/daycount/Actual365.cpp 
src/daycount/Thirty360.cpp
)

target_include_directories(qe PUBLIC include)