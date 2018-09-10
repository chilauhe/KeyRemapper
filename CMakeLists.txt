cmake_minimum_required(VERSION 3.2)
PROJECT(KeyRemapper)
SET(CMAKE_SOURCE_DIR .)
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -D_DEBUG")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
#add_definitions(-D_DEBUG)

FIND_LIBRARY(COMM_LIB heact)
INCLUDE_DIRECTORIES(
.
)
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
SET(KEY_REMAP
${DIR_SRCS}
)

link_libraries(${PROJECT_SOURCE_DIR}/heact/heact.a)

include (CheckFunctionExists)
check_function_exists (strdup HAVE_STRDUP)
check_function_exists (strndup HAVE_STRNDUP)
check_function_exists (malloc HAVE_MALLOC)
check_function_exists (free HAVE_FREE)
check_function_exists (printf HAVE_PRINTF)

ADD_EXECUTABLE(${PROJECT_NAME} ${KEY_REMAP})
target_link_libraries(${PROJECT_NAME})

install (TARGETS ${PROJECT_NAME} DESTINATION bin)
install (FILES mkr.conf DESTINATION etc)