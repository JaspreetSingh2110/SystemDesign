/*
 * Description:
 * Low leve design framework for Hotel Management System.
 *
 * Created on: 4/22/2025
 * @author: Jaspreet Singh, mr.jaspreet2110@gmail.com.
 */

#ifndef HOTELMANAGEMENTSYSTEM_H
#define HOTELMANAGEMENTSYSTEM_H

#include <iostream>
#include <map>
#include <vector>


//Forward declarations.
class HMS_RoomHouseKeeping;
class HMS_RoomKey;
class Invoice;
class HMS_Room;
class RoomBooking;

/**************************** *  * enums *  * *************************************************************************/
//Room style
enum RoomStyle {
  RS_STANDARD,
  RS_DELUXE,
  RS_FAMILY_SUITE,
  RS_BUSINESS_SUITE
};

enum RoomStatus {
  RS_AVAILABLE,
  RS_RESERVED,
  RS_OCCUPIED,
  RS_UNAVAILABLE,
  RS_BEING_SERVICED,
  RS_OTHER
};

enum BookingStatus {
  BS_REQUESTED,
  BS_PENDING,
  BS_CONFIRMED,
  BS_REJECTED,
  BS_CANCELLED
};

enum HMS_AccountStatus {
  HMS_AS_ACTIVE,
  HMS_AS_CLOSED,
  HMS_AS_BLOCKED,
  HMS_AS_BLACKLISTED
};

enum HMS_AccountType {
  HMS_AT_GUEST,
  HMS_AT_MANAGER,
  HMS_AT_RECEPTIONIST,
  HMS_AS_MEMBER
};

enum HMS_PaymentStatus {
  HMS_PS_UNPAID,
  HMS_PS_PENDING,
  HMS_PS_COMPLETED,
  HMS_PS_DECLINED,
  HMS_PS_CANCELLED,
  HMS_PS_SETTLING,
  HMS_PS_SETTLED,
  HMS_PS_REFUNDED
};

/**************************** *  * Address and Account *  * ***********************************************************/
class HMS_Address {
private:
  std::string streetAddress;
  std::string city;
  std::string state;
  std::string country;
  std::string zipcode;
};

class HMS_Account {
private:
  std::string accountId;
  std::string password;
  HMS_AccountStatus status;

public:
  void ResetPassword();
};

/**************************** *  * Person *  * ************************************************************************/
class HMS_Person {
private:
  std::string name;
  std::string emailId;
  std::string phone;
  HMS_Address address;
  HMS_Account account;
};

class HMS_Guest : public HMS_Person {
  private:
  std::vector<RoomBooking> roomBookings;
  int totalRoomsCheckedIn;

public:
  std::vector<RoomBooking> GetBookings();
};

class Receptionist : public HMS_Person {
public:
  std::vector<HMS_Room> SearchRooms();
  bool CreateBooking();
};

class HouseKeeping : public HMS_Person {
public:
  void AssignToRoom(HMS_Room &room);
};

/**************************** *  * Service *  * ********************************************************************/
class Service {
private:
  time_t issuedAt;

public:
  void AddToInvoice(Invoice &invoice);
};


class Amenity : public Service {
  private:
  std::string name;
  std::string description;
};

class RoomService : public Service {
  private:
  bool isChargable;
};

class LaundryService : public Service {
  private:
  int nosOfClothes;
  double chargePerCloth;

public:
  void GenerateLaundryInvoice();
};

class KitchenService : public Service {
  private:
  std::string description;
};

/**************************** *  * Invoice *  * ***********************************************************************/
class Invoice {
  private:
  double amount;

  public:
  void GenerateInvoice();
};

/**************************** *  * Room Booking *  * **************************************************************/
class RoomBooking {
  private:
  std::string reservationId;
  time_t startDate;
  int nosOfDays;

  BookingStatus status;
  time_t checkIn;
  time_t checkOut;

  int guestId;
  HMS_Room *room;
  Invoice invoice;

public:
  RoomBooking FetchReservationDetails(std::string reservationId);
};

/**************************** *  * Bill transaction *  * **************************************************************/
class BillTransaction {
  private:
  double amount;
  time_t transactionTime;
  HMS_PaymentStatus status;

public:
  virtual void InitiateTransaction() = 0;
};


class CardTransaction : public BillTransaction {
  private:
  std::string cardNumber;
  std::string expiryDate;
  std::string pin;
  std::string billingStatus;

public:
  void InitiateTransaction() override;
};

class CashTransaction : public BillTransaction {
public:
  void InitiateTransaction() override;
};

/**************************** *  * Notification *  * ******************************************************************/
class HMS_Notification {
private:
  time_t createdAt;
  std::string content;
  std::string notificationId;

public:
  virtual void SendNotification() = 0;
};

class HMS_SMSNotification : public HMS_Notification {
public:
  void SendNotification() override;
};

class HMS_EmailNotification : public HMS_Notification {
public:
  void SendNotification() override;
};

/**************************** *  * Search and Catalog *  * ************************************************************/
class HMS_Search {
private:
  std::vector<HMS_Room> GetRoomByType(RoomStyle style, time_t startDate, time_t endDate);
};

class HMS_Catalog : public HMS_Search {
private:
  std::map<RoomStyle, std::vector<HMS_Room>> rooms;

public:
  std::vector<HMS_Room> GetRoomByType(RoomStyle style, time_t startDate, time_t endDate);
};

/**************************** *  * Room and Room key *  * *************************************************************/
class HMS_Room {
  std::string roomNumber;
  RoomStyle style;
  RoomStatus status;

  double bookingPrice;
  bool isSmoking;
  std::vector<HMS_RoomKey> roomKeys;
  std::vector<HMS_RoomHouseKeeping> houseKeepers;

public:
  bool IsRoomAvailable();
  void CheckIn();
  void CheckOut();
};

class HMS_RoomKey {
  private:
  std::string keyId;
  bool isMasterKey;
  bool isActive;
  time_t issuedAt;

  public:
  void AssignRoom(HMS_Room room);
};

/**************************** *  * Room Housekeeping *  * ************************************************************/
class HMS_RoomHouseKeeping {
  private:
  HouseKeeping houseKeeper;
  time_t startDate;
  time_t endDate;
  std::string description;

public:
  void AddRoomHouseKeeping(HMS_Room room);
};

/**************************** *  * Hotel and HotelBranch *  * *********************************************************/
class HMS_HotelBranch {
private:
  std::string name;
  HMS_Address address;
  HMS_Catalog catalog;

public:
  std::vector<HMS_Room> GetRooms(RoomStyle style, time_t startDate, time_t endDate);
};

class HMS_Hotel {
  private:
  std::string name;
  std::vector<HMS_HotelBranch> hotelBranches;

public:
  void AddHotelBranch(HMS_HotelBranch hotelBranch);
};
/**************************** *  * END *  * ***************************************************************************/

#endif //HOTELMANAGEMENTSYSTEM_H
