SET(PROJECT_NAME YaPLY)

PROJECT(${PROJECT_NAME})
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)


ADD_DEFINITIONS(
	-std=c++11
	-O3
)

################################################################################
set( YaPLY_LIBRARIES "" )
set( YaPLY_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include )

################################################################################
# build the sample application

FIND_PACKAGE( Eigen3 REQUIRED )
INCLUDE_DIRECTORIES(${YaPLY_INCLUDE_DIR} ${EIGEN3_INCLUDE_DIR} )

ADD_EXECUTABLE(yaply_sample src/example.cpp)

################################################################################
INSTALL(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        FILES_MATCHING PATTERN "*.hpp" )
