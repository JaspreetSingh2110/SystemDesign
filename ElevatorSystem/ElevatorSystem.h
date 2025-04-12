/*
 * Description:
 * Low level class architecture design implementation for elevator system.
 *
 * Created on: 4/12/2025
 * @author: Jaspreet Singh, mr.jaspreet2110@gmail.com.
 */

#ifndef ELEVATORSYSTEM_H
#define ELEVATORSYSTEM_H

#include <iostream>
#include <vector>

/**********************************  Enums used in elevator system  ***************************************************/

// state of lift.
enum State {
  IDLE,
  UP,
  DOWN
};

//Direction of movement
enum Direction {
  DIR_UP,
  DIR_DOWN
};

// door state
enum DoorState {
  DS_CLOSED,
  DS_OPEN
};

class Door;

/**********************************  Button ***************************************************************************/
//Abstract button class
class Button {
private:
  bool status;  // status of button if it is pressed.

public:
  void PressButton();
  virtual void IsPressed() = 0;
};

// Button in Hall. It contains direction buttons.
class HallButton : public Button {
private:
  Direction buttonSign;

public:
  void IsPressed() override;
};

// Button in elevator. It contains floor numbers.
class ElevatorButton : public Button {
private:
  int destinationFloorNumber;

public:
  void IsPressed() override;
};

/**********************************  Panels: Hall panel and Elevator panels  ******************************************/
//Panels in hall. It contains two buttons with up and down signs.
class HallPanel {
private:
  HallButton upButton;
  HallButton downButton;
};

//Elevator panel. It contains buttons for each floors and two other buttons to open and close the door.
class ElevatorPanel {
private:
  std::vector<ElevatorButton> floorButtons;
  ElevatorButton openDoorButton;
  ElevatorButton closeDoorButton;
};

/**********************************  Display  *************************************************************************/
/*
 * Display class is implemented to show the information inside elevator and also on the floor.
 * Common class used to work for both displays as the information is similar.
 * Display information on floor is subset of information inside elevator.
 */
class Display {
private:
  int floorNumber;
  int capacity;
  Direction direction;

public:
  void ShowElevatorDisplay();
  void ShowFloorDisplay();
};
/**********************************  Elevator Car  ********************************************************************/

//Elevator car
class ElevatorCar {
private:
  int id;  // unique id for each elevator car.
  ElevatorPanel elevatorPanel;
  Display elevatorDisplay;
  State elevatorState;
  Door *door;

public:
  void Move();
  void Stop();
};

/**********************************  Door and Floor  ******************************************************************/

class Door {
private:
  DoorState doorState;
public:
  bool IsOpen();
};

class Floor {
private:
  int floorNumber;  // unique floor number
  std::vector<Display> floorDisplay;  // display at each floor.
  std::vector<HallPanel> hallPanel;  // panels at each floor.

public:
  bool IsTopMostFloor();
  bool IsBottomMostFloor();
};

/**********************************  Building  ************************************************************************/

class Building {
private:
  // details of the building
  int buildingId;
  std::string name;
  std::string address;

  std::vector<Floor> floors;  // floors in building
  std::vector<ElevatorCar> elevatorCars;  // elevators in building.

  static Building *building;
public:
  Building* GetBuildingInstance()
  {
    if (building == nullptr) {
      building = new Building();
    }
    return building;
  }
};

/**********************************  Elevator System  *****************************************************************/

class ElevatorSystem {
private:
  Building building;
  static ElevatorSystem* system;

public:
  ElevatorSystem* GetElevatorSystemInstance()
  {
    if (system == nullptr) {
      system = new ElevatorSystem();
    }
    return system;
  }
};

/**********************************  * END *  **************************************************************************/
#endif //ELEVATORSYSTEM_H
