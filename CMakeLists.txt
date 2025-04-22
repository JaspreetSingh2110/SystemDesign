cmake_minimum_required(VERSION 3.29)
project(SystemDesign)

set(CMAKE_CXX_STANDARD 14)

add_executable(SystemDesign main.cpp
        01_ParkingLot/ParkingLot.cpp
        01_ParkingLot/ParkingLot.h
        02_ElevatorSystem/ElevatorSystem.h
        03_LibraryManagementSystem/LibraryManagementSystem.h
        04_AmazonLockerService/AmazonLockerService.h
        05_VendingMachine/VendingMachine.h
        06_OnlineBlackJackGame/OnlineBlackJackGame.h
        07_MeetingScheduler/MeetingScheduler.h
        08_MovieTicketBookingSystem/MovieTicketBookingSystem.h
        09_VehicleRentalSystem/VehicleRentalSystem.h
        10_ATM_System/ATMSystem.h
        11_OnlineChessGame/OnlineChessGame.h
        12_HotelManagementSystem/HotelManagementSystem.h
)
