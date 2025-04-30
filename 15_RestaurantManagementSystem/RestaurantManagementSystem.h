/*
 * Description:
 * Low level design framework for Restaurant Management System.
 *
 * Created on: 5/1/2025
 * @author: Jaspreet Singh, mr.jaspreet2110@gmail.com.
 */

#ifndef RESTAURANTMANAGEMENTSYSTEM_H
#define RESTAURANTMANAGEMENTSYSTEM_H

#include <iostream>
#include <string>

/*********************************** ** * Enums * ** ******************************************************************/
enum RMS_PaymentStatus {
  RMS_PS_Unpaid,
  RMS_PS_Pending,
  RMS_PS_Completed,
  RMS_PS_Failed,
  RMS_PS_Declined,
  RMS_PS_Cancelled,
  RMS_PS_Refunded
};

enum RMS_TableStatus {
  RMS_TS_Free,
  RMS_TS_Occupied,
  RMS_TS_Reserved,
  RMS_TS_None
};

enum RMS_SeatType {
  RMS_ST_Regular,
  RMS_ST_Kid,
  RMS_ST_Other
};

enum RMS_AccountStatus {
  RMS_AS_Active,
  RMS_AS_Blocked,
  RMS_AS_Cancelled,
  RMS_AS_BlackListed,
  RMS_AS_Closed
};

enum RMS_OrderStatus {
  RMS_OS_Requested,
  RMS_OS_Received,
  RMS_OS_Preparing,
  RMS_OS_Cancelled,
  RMS_OS_Served
};

enum RMS_ReservationStatus {
  RMS_RS_Requested,
  RMS_RS_Pending,
  RMS_RS_Confirmed,
  RMS_RS_Cancelled,
  RMS_RS_CheckedIn
};

/*********************************** ** * Address * ** ****************************************************************/
class RMS_Address {
private:
  std::string streetAddress;
  std::string city;
  std::string state;
  std::string country;
  std::string zipCode;
};

/*********************************** ** * Account * ** ****************************************************************/
class RMS_Account {
  private:
  std::string username;
  std::string password;
  RMS_AccountStatus accountStatus;
};

/*********************************** ** * Person: Employee, Customer. * ** ********************************************/
/*********************************** ** * Employee: Receptionist, Waiter, Manager, Chef * ** **************************/
class RMS_Person {
private:
  std::string name;
  std::string phone;
  std::string email;
};

class RMS_Customer : public RMS_Person {
  private:
  time_t lastVisited;
};

class RMS_Employee : public RMS_Person {
  private:
  std::string employeeId;
  RMS_Address address;
  RMS_Account account;
};

class RMS_Receptionist : public RMS_Employee {
public:
  void MakeReservation();
};

class RMS_Manager : public RMS_Employee {
  public:
  void MakeReservation();
  void CancelReservation();
  void TakeOrder();
  void AddEmployee();
};

class RMS_Waiter : public RMS_Employee {
  public:
  void TakeOrder();
  void ServeOrder();
};

class RMS_Chef : public RMS_Employee {
  public:
  void PrepareFood();
};

/*********************************** ** * Table and Seat * ** *********************************************************/
class RMS_Seat {
private:
  std::string seatId;
  RMS_SeatType seatType;

public:
  void UpdateSeatType(RMS_SeatType seatType);
};

class RMS_Table {
  private:
  std::string tableId;
  RMS_TableStatus tableStatus;
  std::vector<RMS_Seat> seats;

  public:
  void AddSeat(RMS_Seat seat);
  void AddReservation();
  bool IsFree();
};

/*********************************** ** * Menu, Menu Item and Menu section * ** ***************************************/
class RMS_MenuItem {
  private:
  std::string itemId;
  std::string itemName;
  std::string itemDescription;
  double price;
  bool isVegetarian;

  public:
  void UpdatePrice();
};

class RMS_MenuSection {
  private:
  std::string menuSectionId;
  std::string sectionName;
  std::string sectionDescription;
  std::vector<RMS_MenuItem> items;

  public:
  void AddMenuItem(RMS_MenuItem item);
};

class RMS_Menu {
  private:
  std::string menuId;
  std::string menuDescription;
  std::vector<RMS_MenuSection> sections;

  public:
  void AddMenuSection(RMS_MenuSection section);
};

/*********************************** ** * Order * ** ******************************************************************/
class RMS_Order {
  private:
  std::string orderId;
  time_t createdAt;
  RMS_OrderStatus orderStatus;

  RMS_Table table;
  RMS_Waiter waiter;
  RMS_Chef chef;

  std::map<RMS_MenuItem, int> itemsOrdered;  //Menu item mapped to quantity.

  public:
  void AddFoodItem(RMS_MenuItem item, int quantity);
  void RemoveFoodItem(RMS_MenuItem item, int quantity);
};

/*********************************** ** * Kitchen * ** ******************************************************************/
class RMS_Kitchen {
  private:
  std::string kitchenId;
  std::vector<RMS_Chef> chefs;

public:
  void AddChef(RMS_Chef chef);
  void RemoveChef(RMS_Chef chef);
};

/*********************************** ** * Reservation * ** ************************************************************/
class RMS_Reservation {
  private:
  std::string reservationId;
  std::string notes;  // extra requests for reservation.
  time_t createdAt;
  time_t checkinTime;
  int peopleCount;
  RMS_Customer reservationCustomer;
  RMS_ReservationStatus reservationStatus;
  std::vector<RMS_Table> tables;

public:
  void UpdatePeopleCount(int count);
};

/*********************************** ** * Bill * ** *******************************************************************/
class RMS_Bill {
  private:
  std::string billId;
  time_t billCreatedAt;
  time_t billCheckedAt;
  double amount;
  double serviceCharge;
  double tip;
  double taxes;
  bool isPaid;
};

/*********************************** ** * Payment * ** ****************************************************************/
class RMS_Payment {
  private:
  std::string paymentId;
  double amount;
  time_t creationTime;
  RMS_PaymentStatus status;

  public:
  virtual void MakePayment() = 0;
};

class RMS_CardPayment : public RMS_Payment {
  private:
  std::string cardNumber;
  std::string nameOnCard;
  std::string pin;

  public:
  void MakePayment() override;
};

class RMS_CashPayment : public RMS_Payment {
public:
  void MakePayment() override;
};

/*********************************** ** * Notification * ** ***********************************************************/
class RMS_Notification {
  private:
  std::string notificationId;
  std::string content;
  time_t createdAt;

public:
  virtual void SendNotification() = 0;
};

class RMS_EmailNotification : public RMS_Notification {
  private:
  std::string email;

public:
  void SendNotification() override;
};

class RMS_SmsNotification : public RMS_Notification {
  private:
  std::string phone;

  public:
  void SendNotification() override;
};

/*********************************** ** * Seating chart * ** **********************************************************/
class RMS_SeatingChart {
  private:
  std::string seatingChartId;
  int image[];

public:
  void PrintSeatingChart();
};

/*********************************** ** * Branch and Restaurant * ** **************************************************/
class RMS_RestaurantBranch {
  private:
  std::string restaurantBranchId;
  RMS_Address address;
  RMS_Kitchen kitchen;
  RMS_Menu menu;
  RMS_SeatingChart seatingChart;
};

class RMS_Restaurant {
  private:
  std::string restaurantId;
  std::string restaurantName;
  std::string restaurantDescription;
  std::vector<RMS_RestaurantBranch> restaurantBranches;

  public:
  void AddNewBranch(RMS_RestaurantBranch newBranch);
  void RemoveBranch(RMS_RestaurantBranch branch);
};

/*********************************** ** * End * ** ********************************************************************/

#endif //RESTAURANTMANAGEMENTSYSTEM_H
