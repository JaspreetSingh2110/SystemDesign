/*
 * Description:
 * Low level design framework for Vehicle rental system.
 *
 * Created on: 4/19/2025
 * @author: Jaspreet Singh, mr.jaspreet2110@gmail.com.
 */

#ifndef VEHICLERENTALSYSTEM_H
#define VEHICLERENTALSYSTEM_H

#include <iostream>
#include <map>
#include <vector>

class VehicleLog;
class VRS_VehicleReservation;
class VRS_Customer;

/**************************** *  * Enums *  * *************************************************************************/
enum VRS_VehicleStatus {
  VS_AVAILABLE = 0,
  VS_RESERVED = 1,
  VS_BEING_SERVICED,
  VS_LOST
};

enum VRS_AccountStatus{
  AS_ACTIVE = 0,
  AS_CLOSED = 1,
  AS_CANCELLED = 2,
  AS_BLOCKED = 3,
  AS_BLACKLISTED = 4
};

enum VRS_ReservationStatus {
  VRS_ACTIVE = 0,
  VRS_PENDING = 1,
  VRS_CONFIRMED = 2,
  VRS_CANCELLED = 3,
  VRS_COMPLETED
};

enum VRS_PaymentStatus {
  PS_UNPAID,
  PS_PENDING,
  PS_COMPLETED,
  PS_CANCELLED,
  PS_REFUNDED
};

/*******Vehicle types*****/
enum VRS_VanType {
  VT_CARGO,
  VT_PASSENGER
};

enum VRS_CarType {
  CT_ECONOMY,
  CT_COMPACT,
  CT_PRIME,
  CT_PREMIUM,
  VT_LUXURY
};

enum VRS_BikeType {
  BT_CRUISER,
  BT_SPORTS,
  BT_OFF_ROAD,
  BT_STANDARD
};

enum VRS_TruckType {
  TT_LIGHT_DUTY,
  TT_MEDIUM_DUTY,
  TT_HEAVY_DUTY
};

/******* Vehicle log type **/
enum VehicleLogType {
  VLT_ACCIDENT,
  VLT_REFUEL,
  VLT_REPAIR,
  VLT_CLEANING,
  VLT_OIL_CHANGE,
  VLT_OTHER
};

/**************************** *  * Address *  * ***********************************************************************/
class VRS_Address {
private:
  std::string street_address;
  std::string city;
  std::string state;
  std::string country;
  std::string country_code;
  std::string zipcode;
};

/**************************** *  * Person, Driver *  * ****************************************************************/
class VRS_Person {
private:
  std::string name;
  std::string phone;
  std::string email;
  VRS_Address address;
};

class VRS_Driver : public VRS_Person {
  private:
  std::string driverId;
  std::string drivingLicenseNo;
};

/**************************** *  * Account: Receptionist, Customer *  * ***********************************************/
class VRS_Account : public VRS_Person {
  std::string accountId;
  std::string password;
  VRS_AccountStatus status;
};

class VRS_Receptionist : public VRS_Account {
private:
  time_t joiningDate;

public:
  std::vector<VRS_Customer> SearchCustomers(std::string &name);
  void AddReservation();
  void CancelReservation();
};

class VRS_Customer : public VRS_Account {
  private:
  std::string licenseNumber;
  std::string licenseExpiryDate;

public:
  void AddReservation();
  void CancelReservation();
  std::vector<VRS_VehicleReservation*> GetReservations();
};

/**************************** *  * Vehicle *  * ***********************************************************************/
class VRS_Vehicle {
  private:
  std::string registrationNumber;
  std::string manufacturer;
  std::string model;
  int manufacturingYear;
  double mileage;
  int seatingCapacity;
  bool hasSunRoof;
  VRS_VehicleStatus status;
  std::vector<VehicleLog*> logs;
};

class VRS_Car : public VRS_Vehicle {
  private:
  VRS_CarType carType;
};

class VRS_Van : public VRS_Vehicle {
  private:
  VRS_VanType type;
};

class VRS_Truck : public VRS_Vehicle {
  private:
  VRS_TruckType truckType;
};

class VRS_MotorCycle : public VRS_Vehicle {
  private:
  VRS_BikeType bikeType;
};

/**************************** *  * Equipment *  * *********************************************************************/
class VRS_Equipment {
  private:
  std::string equipmentId;
  double price;
};

class VRS_ChildSeat : public VRS_Equipment {
};

class VRS_Navigation : public VRS_Equipment {
};

/**************************** *  * Service *  * ***********************************************************************/
class VRS_Service {
  private:
  std::string serviceId;
  double price;
};

class VRS_DriverService : public VRS_Service {
};

class VRS_RoadSideAssistanceService : public VRS_Service {
};

/**************************** *  * Payment *  * ***********************************************************************/
class VRS_Payment {
  private:
  double amount;
  time_t paymentTime;
  VRS_PaymentStatus status;

public:
  virtual bool MakePayment() = 0;
};

class VRS_CashPayment : public VRS_Payment {
public:
  bool MakePayment() override;
};

class VRS_CardPayment : public VRS_Payment {
private:
  std::string cardNumber;
  std::string nameOnCard;
  time_t expiryDate;
  std::string code;

public:
  bool MakePayment() override;
};

/**************************** *  * VehicleLog *  * ********************************************************************/
class VRS_VehicleLog {
  private:
  int logId;
  VehicleLogType type;
  std::string description;
  time_t logCreationDate;
};

/**************************** *  * Vehicle reservation *  * ***********************************************************/
class VRS_VehicleReservation {
  private:
  VRS_Vehicle *vehicle;
  VRS_Customer *customer;
  time_t creationDate;
  time_t reservationDate;
  time_t returnDate;
  VRS_ReservationStatus reservationStatus;
  VRS_PaymentStatus paymentStatus;

  //pickup-drop services.
  std::string pickupLocation;
  std::string dropLocation;

  std::vector<VRS_Equipment*> equipments;
  std::vector<VRS_Service*> services;

public:
  void AddEquipment();
  void AddServices();
};

/**************************** *  * Notification *  * ******************************************************************/
class VRS_Notification {
  private:
  std::string notificationId;
  std::string content;
  time_t creationDate;

public:
  virtual bool SendNotification() = 0;
};

class VRS_SMSNotification : public VRS_Notification {
public:
  bool SendNotification() override;
};

class VRS_EmailNotification : public VRS_Notification {
  public:
  bool SendNotification() override;
};

/**************************** *  * Parking stall *  * *****************************************************************/
class VRS_ParkingStall {
  private:
  std::string parkingStallId;
  std::string parkingStallLocationIdentifier;
};

/**************************** *  * Fine *  * **************************************************************************/
class VRS_Fine {
  private:
  double amount;
  std::string reason;

  public:
  double CalculateFine();
};

/**************************** *  * Search interface and Catalog *  * **************************************************/
class VRS_Search {
public:
  virtual std::vector<VRS_Vehicle*> SearchVehicleByName(std::string name) = 0;
  virtual std::vector<VRS_Vehicle*> SearchVehicleByModel(std::string model) = 0;
};

class VRS_Catalog : public VRS_Search {
  private:
  std::map<std::string, std::vector<VRS_Vehicle*>> vehiclesByName;
  std::map<std::string, std::vector<VRS_Vehicle*>> vehiclesByModel;

  public:
  std::vector<VRS_Vehicle*> SearchVehicleByName(std::string name) override;
  std::vector<VRS_Vehicle*> SearchVehicleByModel(std::string model) override;
};

/**************************** *  * Vehicle rental branch *  * *********************************************************/
class VehicleRentalBranch {
  private:
  std::string branchName;
  Address branchAddress;
  std::vector<VRS_ParkingStall*> parkingStalls;

public:
  std::vector<VRS_ParkingStall*> GetParkingStalls();
};

/**************************** *  * Vehicle rental system *  * *********************************************************/
class VehicleRentalSystem {
  private:
  std::vector<VehicleRentalBranch*> carRentalBranches;
  VRS_Catalog catalog;

public:
  void AddVehicleRentalBranch(VehicleRentalBranch *branch);
  void MakeReservation();
  void CancelReservation();
};

/**************************** *  * End *  * ***************************************************************************/
#endif //VEHICLERENTALSYSTEM_H
