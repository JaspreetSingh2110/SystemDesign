
#include <iostream>
#include <stdio.h>
#include <cstdint>

#include "01_ParkingLot/ParkingLot.h"
#include "02_ElevatorSystem/ElevatorSystem.h"
#include "03_LibraryManagementSystem/LibraryManagementSystem.h"
#include "04_AmazonLockerService/AmazonLockerService.h"

void Test_LowLevelDesign(uint32_t &testCnt)
{

}

int main()
{
    std::cout << "Test low level system design cases:" << std::endl;
    uint32_t testCnt = 0;
    Test_LowLevelDesign(testCnt);

    std::cout << "Total " << testCnt << " tests passed." << std::endl;
    return 0;
}
