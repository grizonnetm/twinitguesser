cmake_minimum_required(VERSION 2.8)
project( MatchTemplate_Demo )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( MatchTemplate_Demo MatchTemplate_Demo.cpp )
target_link_libraries( MatchTemplate_Demo ${OpenCV_LIBS} )

add_executable( MatchTemplate_ls MatchTemplate_ls.cpp )
target_link_libraries( MatchTemplate_ls ${OpenCV_LIBS} )
