cmake_minimum_required(VERSION 2.8)

project(tests)

set (PATH_TO_PROJECT "/home/gh/Desktop/")

include_directories("lib/Catch/single_include/")
include_directories("${PATH_TO_PROJECT}task/src")


set (HEADERS 
	${PATH_TO_PROJECT}task/src/SimpleObj.h
	${PATH_TO_PROJECT}task/src/ObjectsManager.h
    ) 


set (SOURCES 
	${PATH_TO_PROJECT}task/src/SimpleObj.cpp
	${PATH_TO_PROJECT}task/src/ObjectsManager.cpp
	src/main.cpp
	src/tests.cpp
    ) 

add_executable(tests ${SOURCES} ${HEADERS})
target_link_libraries(tests -lpthread)


