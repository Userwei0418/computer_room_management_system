cmake_minimum_required(VERSION 3.25)
include_directories("D:/mysql/mysql-8.0.35-winx64/include")
link_directories("D:/mysql/mysql-8.0.35-winx64/lib")
link_libraries(libmysql)

project(computer_room_management_system)

set(CMAKE_CXX_STANDARD 17)

add_executable(computer_room_management_system main.cpp Mysql_Connect.cpp ComputerRoom.cpp Identity.cpp orderFile.cpp student.cpp Teacher.cpp Manager.cpp)

target_link_libraries(computer_room_management_system libmysql)