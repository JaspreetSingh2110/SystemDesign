
#include <iostream>
#include <stdio.h>
#include <cstdint>

#include "ParkingLot/ParkingLot.h"
#include "ElevatorSystem/ElevatorSystem.h"

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
