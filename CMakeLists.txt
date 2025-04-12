cmake_minimum_required(VERSION 3.29)
project(SystemDesign)

set(CMAKE_CXX_STANDARD 14)

add_executable(SystemDesign main.cpp
        ParkingLot/ParkingLot.cpp
        ParkingLot/ParkingLot.h
        main.cpp
        ElevatorSystem/ElevatorSystem.h
)
