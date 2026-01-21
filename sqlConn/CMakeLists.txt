###########


cmake_minimum_required(VERSION 3.0.0)


project(test)

include_directories(/usr/include/mysql)

link_directories(/lib64/)

add_executable(test test.cpp sqlConn.cpp)

target_link_libraries(test mysqlclient)


