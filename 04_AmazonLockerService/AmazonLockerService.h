/*
 * Description:
 * Low level design framework for Amazon Locker service.
 *
 * Created on: 4/15/2025
 * @author: Jaspreet Singh, mr.jaspreet2110@gmail.com.
 */

#ifndef AMAZONLOCKERSERVICE_H
#define AMAZONLOCKERSERVICE_H

#include <iostream>
#include <list>
#include <map>

/***********************  * Enumerations *  ***************************************************************************/
enum LockerState {
  LS_AVAILABLE,
  LS_BOOKED,  // Booked but no package in yet.
  LS_CLOSED  //Closed with package inside.
};

enum LockerSize {
  LS_SMALL,
  LS_MEDIUM,
  LS_LARGE,
  LS_XLARGE,
  LS_XXLARGE
};

/***********************  * Item and Order *  *************************************************************************/

class Item {
private:
  int itemId;
  int quantity;
};

class Order {
  private:
  int orderId;
  std::list<Item*> items;
  int deliveryDate;
  std::string deliveryLocation;
};

/***********************  * Package and LockerPackage *  **************************************************************/

//Generic package as a box.
class Package {
  private:
  int packageId;
  double packageSize;
  Order order;

public:
  void Pack();
};

//Package in association with locker.
class LockerPackage {
  private:
  int lockerId;
  int packageId;
  int deliveredDate;
  int deliveryTime;
  std::string code;
  int codeValidityDays;

public:
  bool VerifyCode(std::string code);
  bool IsValidCode();
};

/***********************  * Locker *  *********************************************************************************/
class Locker {
  private:
  int lockerId;
  LockerSize lockerSize;
  LockerState lockerState;
  std::string locationId;

public:
  void AddPackage(Package package);
  void RemovePackage(Package package);
};

/***********************  * Locker location *  ************************************************************************/
// location/premises where locker are placed.
//Location, open close timings, and list of lockers.
class LockerLocation {
  private:
  int locationId;
  double altitude;
  double longitude;
  int opentime;
  int closeTime;
  std::map<LockerSize, std::list<Locker>> lockers;

  public:
  void AddPackage(Package package);
  void RemovePackage(Package package);
};

/***********************  * Notification *  ***************************************************************************/

//Send notification at each step of packet transit till delivery.
class Notification {
  private:
  int notificationId;
  std::string content;
  std::string customerId;
  int orderId;
  int lockerId;
  std::string code;
  int codeValidityDays;

  public:
  void SendNotification();
};

/***********************  * Locker service *  *************************************************************************/

class LockerService {
  private:
  std::vector<LockerLocation> lockerLocations;

public:
  void AddPackage(LockerLocation location, Package package);
  void RemovePackage(LockerLocation location, Package package);
};

/***********************  *** END ***  ********************************************************************************/
#endif //AMAZONLOCKERSERVICE_H
