/*
 * Description:
 * Low level design framework for Amazon's Online shopping system.
 *
 * Created on: 4/23/2025
 * @author: Jaspreet Singh, mr.jaspreet2110@gmail.com.
 */

#ifndef AMAZONONLINESHOPPINGSYSTEM_H
#define AMAZONONLINESHOPPINGSYSTEM_H

#include <iostream>

class AOSS_OrderLog;
class AOSS_Order;
class AOSS_ShipmentLog;
class AOSS_ShoppingCart;
class AOSS_ProductCategory;
class AOSS_ProductReview;
class AOSS_Product;
class AOSS_CardPayment;
class AOSS_BankTransfer;

/**************************** *  * enums *  * *************************************************************************/
enum AOSS_AccountStatus {
  AOSS_AS_ACTIVE,
  AOSS_AS_BLOCKED,
  AOSS_AS_CLOSED
};

enum AOSS_OrderStatus {
  AOSS_OS_PENDING,
  AOSS_OS_CONFIRMED,
  AOSS_OS_SHIPPED,
  AOSS_OS_CANCELLED,
  AOSS_OS_DELIVERED,
};

enum AOSS_ShipmentStatus {
  AOSS_SS_PREPARING,   //Getting packet/collected.
  AOSS_SS_DISPATCHED,
  AOSS_SS_DELIVERING,
  AOSS_SS_DELIVERED,
  AOSS_SS_CANCELLED,
  AOSS_SS_LOST
};

enum AOSS_PaymentStatus {
  AOSS_PS_PENDING,
  AOSS_PS_COMPLETED,
  AOSS_PS_DECLINED,
  AOSS_PS_REFUNDED
};

/**************************** *  * Required classes/components *  * ***************************************************/
/**************************** *  * Address *  * ***********************************************************************/
class AOSS_Address {
private:
  std::string streetAddress;
  std::string city;
  std::string state;
  std::string country;
  std::string zipcode;
};

/**************************** *  * Account *  * ***********************************************************************/
class AOSS_Account {
private:
  std::string username;
  std::string password;
  std::string email;
  std::string phone;
  AOSS_AccountStatus status;
  std::vector<AOSS_Address> shippingAddresses;

  /*
   * NOTE: Shopping cart is not part of account, because the guest user will not have an account
   * but will still be holding a shopping cart.
   * So, Shopping cart will be direct members of Guest and Registered customers.
   */

  //Payment options associated with account.
  std::vector<AOSS_CardPayment> creditCards;
  std::vector<AOSS_BankTransfer> bankAccounts;

public:
  void AddShippingAddress(AOSS_Address address);
  void AddCreditCard(AOSS_Address address);
  void AddBankAccount(AOSS_Address address);
  void AddProductToShoppingCart(AOSS_Product product);
  void RemoveProductFromShoppingCart(AOSS_Product product);
  void AddProductReview(AOSS_Product product, AOSS_ProductReview review);
};

/**************************** *  * Admin *  * *************************************************************************/
class AOSS_Admin {
  private:
  AOSS_Account account;

  public:
  void BlockAccount(AOSS_Account account);
  void UnblockAccount(AOSS_Account account);
  void AddNewProductCategory(AOSS_ProductCategory category);
  void DeleteProductCategory(AOSS_ProductCategory category);
  void UpdateProductCategory(AOSS_ProductCategory category);
};

/**************************** *  * Customer : Guest, Registered *  * **************************************************/
class AOSS_Customer {
  private:
  AOSS_ShoppingCart *shoppingCart;

  public:
  virtual AOSS_ShoppingCart GetShoppingCart() = 0;
  void PlaceOrder();
};

class AOSS_GuestCustomer : AOSS_Customer {
  public:
  void RegisterAccount();
  AOSS_ShoppingCart GetShoppingCart() override;
};

class AOSS_RegisteredCustomer : AOSS_Customer {
private:
  AOSS_Account account;
  std::vector<AOSS_Order> orders;

  public:
  AOSS_ShoppingCart GetShoppingCart() override;
};

/**************************** *  * Product, Product Category and Product review *  * **********************************/
class AOSS_Product {
  private:
  std::string name;
  std::string description;
  std::string productCode; //or Id
  std::vector<char> image;
  double price;
  int availableQuantity;
  AOSS_ProductCategory *category;
  std::vector<AOSS_ProductReview> reviews;
  AOSS_Account sellerAccount;

  public:
  void UpdatePrice(double price);
  void UpdateAvailableQuantity(int quantity);
};

class AOSS_ProductCategory {
  private:
  std::string name;
  std::string description;

  std::vector<Product> products;
};

class AOSS_ProductReview {
  private:
  double rating;
  std::string reviewDescription;
  std::vector<std::vector<char>> images;
  AOSS_RegisteredCustomer customer;
};

/**************************** *  * CartItem and Shopping Cart *  * ****************************************************/
class AOSS_CartItem {
  private:
  int quantity;
  AOSS_Product product;

public:
  double GetBillingPrice();
  void UpdateQuantity(int quantity);
};

class AOSS_ShoppingCart {
  private:
  double totalPrice;
  std::vector<AOSS_CartItem> cartItems;

public:
  void AddItemToCart(AOSS_CartItem cartItem);
  void DeleteItemFromCart(AOSS_CartItem cartItem);
  bool Checkout();
};

/**************************** *  * Order and Order log *  * ***********************************************************/
class AOSS_Order {
private:
  std::string orderId;
  time_t placedAt;
  AOSS_OrderStatus status;
  AOSS_ShoppingCart shoppingCart;
  std::vector<AOSS_OrderLog> orderLogs;

  public:
  void UpdateOrderStatus(AOSS_OrderStatus status);
  AOSS_OrderStatus GetOrderStatus();
  void UpdateOrderLogs(AOSS_OrderLog orderLog);

  void MakePayment();
  void SendForShipment();
};

class AOSS_OrderLog {
  private:
  std::string orderId;
  AOSS_OrderStatus status;
  time_t logTimeStamp;
};

/**************************** *  * Shipment and Shipment log *  * *****************************************************/
class AOSS_Shipment {
  private:
  std::string shipmentId;
  AOSS_ShipmentStatus status;
  time_t shipmentDate;
  time_t expectedShipmentArrivalDate;
  std::vector<AOSS_ShipmentLog> shipmentLogs;

  public:
  void UpdateShipmentStatus(AOSS_ShipmentStatus status);
  AOSS_ShipmentStatus GetShipmentStatus();
  void AddShipmentLog(AOSS_ShipmentLog shipmentLog);
};

class AOSS_ShipmentLog {
  private:
  std::string shipmentId;
  AOSS_ShipmentStatus status;
  time_t logTimeStamp;
};

/**************************** *  * Payment: Card, Cash and BankTransfer *  * ******************************************/
class AOSS_Payment {
  private:
  double amount;
  AOSS_PaymentStatus status;
  time_t paymentTimestamp;

public:
  virtual void MakePayment() = 0;
};

class AOSS_CardPayment : public AOSS_Payment {
  private:
  std::string cardNumber;
  std::string nameOnCard;
  std::string expiryDate;
  std::string cvv;
  std::string pin;
  std::string billingAddress;

public:
  void MakePayment() override;
};

class AOSS_BankTransfer : public AOSS_Payment {
  private:
  std::string bankName;
  std::string bankAccountNumber;
  std::string billingAddress;

  public:
  void MakePayment() override;
};

class AOSS_CashPayment : public AOSS_Payment {
public:
  void MakePayment() override;
};

/**************************** *  * Notification: SMS and Email *  * ***************************************************/
class AOSS_Notification {
private:
  std::string notificationId;
  std::string content;
  time_t timestamp;

public:
  virtual void SendNotification(AOSS_Account account) = 0;
};

class AOSS_SmsNotification : public AOSS_Notification {
public:
  void SendNotification(AOSS_Account account) override;
};

class AOSS_EmailNotification : public AOSS_Notification {
  public:
  void SendNotification(AOSS_Account account) override;
};

/**************************** *  * Search and Catalog *  * ************************************************************/
class AOSS_Search {
  public:
  virtual std::vector<AOSS_Product> SearchByProductCategory(AOSS_ProductCategory category) = 0;
  virtual std::vector<AOSS_Product> SearchByProductName(std::string productName) = 0;
};

class AOSS_Catalog : public AOSS_Search {
private:
  std::map<std::string, std::vector<AOSS_Product>> productsByName;
  std::map<AOSS_ProductCategory, std::vector<AOSS_Product>> productsByCategory;

  public:
  std::vector<AOSS_Product> SearchByProductCategory(AOSS_ProductCategory category) override;
  std::vector<AOSS_Product> SearchByProductName(std::string productName) override;
};

/**************************** *  * END *  * ***************************************************************************/

#endif //AMAZONONLINESHOPPINGSYSTEM_H
