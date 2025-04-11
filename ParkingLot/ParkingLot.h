/*
 * Description:
 * Low level design framework for Parking Lot.
 *
 * Created on: 4/11/2025
 * @author: Jaspreet Singh, mr.jaspreet2110@gmail.com.
 */

#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

class ParkingLot;
class DisplayBoard;
class Exit;
class Entrance;
class Payment;
class ParkingTicket;
class Vehicle;

enum PaymentStatus {
  UNKNOWN,
  PENDING,
  UNPAID,
  PAID,
  REFUNDED
};

enum AccountStatus {
  ACTIVE,
  CLOSED,
  BLACKLISTED,
  NONE
};

enum ParkingSpotType {
  PS_UNKNOWN,
  PS_MotorCycle,
  PS_Compact,
  PS_Large,
  PS_Handicapped,
  PS_MAX
};

/******************************************  Vehicle  *****************************************************************/

class Person {
  public:
  std::string name;
  std::string address;
  std::string phone;
  std::string email;
};

/******************************************  Vehicle  *****************************************************************/

class Vehicle {
private:
  std::string registrationNumber; // vehicle registration number.

public:
  //API to assign ticket.
  //Derived classes will define this functionality based upon the vehicle type.
  //Because for each type of vehicle, different type of parking spot needs to assigned.
  virtual bool AssignTicket(ParkingTicket pTicket) = 0;
};

class MotorCycle : public Vehicle {
public:
  bool AssignTicket(ParkingTicket pTicket) override;
};

class Car : public Vehicle {
public:
  bool AssignTicket(ParkingTicket pTicket) override;
};

class Van : public Vehicle {
public:
  bool AssignTicket(ParkingTicket pTicket) override;
};

class Truck : public Vehicle {
public:
  bool AssignTicket(ParkingTicket pTicket) override;
};

/******************************************  Parking Spot  ************************************************************/

class ParkingSpot {
private:
  int id;  // unique id.
  bool isFree;  // status of spot.
  Vehicle *vehicle;  // vehicle currently using the spot.
  // type of spot.
  // Shall be used while assigning vehicle and display information in display boards.
  ParkingSpotType type;

  public:
  bool IsFree();
  virtual bool AssignVehicle(Vehicle *vehicle) = 0;
  bool RemoveVehicle(Vehicle *vehicle);
};

class HandicappedParking : public ParkingSpot {
public:
  bool AssignVehicle(Vehicle *vehicle) override;;
};

class CompactParking : public ParkingSpot {
public:
  bool AssignVehicle(Vehicle *vehicle) override;;
};

class LargeParking : public ParkingSpot {
public:
  bool AssignVehicle(Vehicle *vehicle) override;;
};

class MotorCycleParking : public ParkingSpot {
public:
  bool AssignVehicle(Vehicle *vehicle) override;;
};

/******************************************  Account  *****************************************************************/

class Account {
private:
  std::string userName;
  std::string password;
  Person person;  // details of the person holding the account.
  AccountStatus status;  // status of the account.

  public:
  virtual bool ResetPassword() = 0;
};

class Admin : public Account {
  public:
  //APIs to process tasks handled by admin.
  bool AddParkingSpot(ParkingSpotType, ParkingSpot *parkingSpot);
  bool AddEntrance(Entrance entrance);
  bool AddExit(Exit exit);
  bool AddDisplayBoard(DisplayBoard displayBoard);

  bool ResetPassword() override;
  void AddPerson(Person person);
  void SetAccountStatus(AccountStatus aStatus);
};

class ParkingAgent : public Account {
  public:
  //APIs to handle functionalities of parking agents.
  void ProcessTicket(ParkingTicket ticket);
  bool ResetPassword() override;
};

/******************************************  Display Board  ***********************************************************/

class DisplayBoard {
private:
  int id;  // unique id for the display board.
  std::map<ParkingSpotType, int> parkingSpots;  // map to hold parking spots count for each type.

public:
  DisplayBoard(int id) : id(id) {}
  //API to update the parking spot counts whenever it gets occupied or get freed.
  bool UpdateParkingSpot(ParkingSpotType type, bool free);

  // API to display free spots information.
  void DisplayParkingSpotsInformation();
};

/******************************************  Parking Rate  ************************************************************/

class ParkingRate {
  private:
  double firstHourRate;  // first hour rate
  double secondHourRate; // 2nd hour rate
  double commonRate;  // 3rd hour onwards rate
  double totalMinutes;  // total time in minutes the parking spot was used.

  public:
  // API to calculate the amount.
  int Calculate();
};

/******************************************  Entrance  ****************************************************************/

class Entrance {
  private:
  int id;  // unique id for entrance gate.
  //Helper API to get parking ticket.
  ParkingTicket GetParkingTicket();

  public:
  //Primary API to process the entry of vehicle.
  // Assigning the parking spot, generating the ticket etc.
  // Update free spots count and dashboards.
  bool ProcessEntrance(Vehicle *vehicle);
};

/******************************************  Exit  ********************************************************************/

class Exit {
  private:
  int id;  // unique Id for the exit gate.
  // helper function to validate the ticket for exit.
  bool ValidateTicket(ParkingTicket ticket);

  public:
  // Main API to be executed to perform all operations related to exit.
  // Calculating the amount, initiating the payment and updating the ticket details etc.
  // Update free spots count and dashboards.
  bool ProcessExit(ParkingTicket ticket);
};

/******************************************  Parking Ticket  **********************************************************/

class ParkingTicket {
  private:
  int ticketNumber;  // unique ticket number
  int entranceTimeStamp;  // timestamp of entrance
  int exitTimestamp;  // timestamp of exit.
  PaymentStatus paymentStatus;  // current payment status.
  double amount;  // total amount to be collected.

  Entrance entrance;  // entrance used to enter the lot.
  Exit exit;  // exit used to exit the lot.
  ParkingSpot *spot;  // parking spot used.
  Vehicle *vehicle;  // vehicle details.
  Payment *payment;  // Payment class object to process the payment.
};

/******************************************  Payment  *****************************************************************/

class Payment {
  private:
  double amount;  // amount to be paid
  PaymentStatus paymentStatus; // status of payment
  int timestamp; // time stamp of payment.

  public:
  // function to process the payment. Derived classes shall implement the logic based upon payment type card/cash.
  virtual bool ProcessPayment(ParkingTicket ticket) = 0;
};

class CashPayment : public Payment {
public:
  bool ProcessPayment(ParkingTicket ticket) override;
};

class CardPayment : public Payment {
public:
  bool ProcessPayment(ParkingTicket ticket) override;
};

/******************************************  Parking Lot  *************************************************************/

class ParkingLot {
private:
  int id;  // parking lot unique id
  std::string name;  // name if parking lot
  std::string address; // address of parking lot.
  ParkingRate parkingRate;  // parking rate for t=given parking lot.

  std::map<int, Entrance> entrances; // map of each entrance in parking lot.
  std::map<int, Exit> exits;  // map of each exits in parking lot.

  std::vector<ParkingAgent> agents;  // parking agents at given parking lot.

  std::map<int, ParkingTicket> tickets; //record of all parking tickets for given parking lot.

public:
  ParkingLot() {}

  bool AddEntrance(Entrance entrance);
  bool AddExit(Exit exit);

  bool IsFull(ParkingSpot *type);
};

/******************************************  *******  *****************************************************************/


#endif //PARKINGLOT_H
