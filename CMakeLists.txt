cmake_minimum_required(VERSION 2.6.2)
PROJECT(bumot)
find_package(wxWidgets COMPONENTS core base REQUIRED)
INCLUDE(${wxWidgets_USE_FILE})

set(SRCS bumot.cpp bumotdb.cpp sqlite3.c)
list(APPEND SRCS bumotdb.hpp bumotstrings.hpp)

ADD_EXECUTABLE(bumot ${SRCS})
TARGET_LINK_LIBRARIES(bumot ${wxWidgets_LIBRARIES} dl)
