cmake_minimum_required(VERSION 2.8)

project(test_task)

set (HEADERS 
	src/Menu.h
	src/SimpleObj.h
        src/ObjectsManager.h
    ) 
set (SOURCES 
	src/main.cpp
	src/Menu.cpp
	src/SimpleObj.cpp
        src/ObjectsManager.cpp
    ) 

add_executable(test_task ${SOURCES} ${HEADERS})
target_link_libraries(test_task -lpthread)

