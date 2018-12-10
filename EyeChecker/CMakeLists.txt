cmake_minimum_required(VERSION 3.12)
project(EyeChecker)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(x64)
include_directories(x64/Debug)

add_executable(EyeChecker
        x64/Debug/EyeChecker.pch
        EyeChecker.cpp
        EyeChecker.vcxproj
        EyeChecker.vcxproj.filters
        EyeChecker.vcxproj.user
        mmm.cpp
        pch.cpp
        pch.h)
