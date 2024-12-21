cmake_minimum_required(VERSION 3.20)
project(JobManagementSystem)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif ()

add_executable(JobManagementSystem
        main.cpp
        User.cpp
        User.h
        Candidate.cpp
        Candidate.h
        Employer.cpp
        Employer.h
        Jobs.cpp
        Jobs.h
        Application.cpp
        Application.h
)