/*
 * Description:
 * Low level design framework for Vending Machine.
 *
 * Created on: 4/16/2025
 * @author: Jaspreet Singh, mr.jaspreet2110@gmail.com.
 */

#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

#include <iostream>
#include <list>
#include <vector>

/************************ *  Enumerations  * **************************************************************************/

enum ProductType {
  PT_BEVERAGE,
  PT_SNACKS,
  PT_CHOCOLATE,
  OTHER
};

/************************ *  State  * *********************************************************************************/
class VendingMachineState {
public:
  virtual void InsertMoney(double money) = 0;
  virtual void PressButton(int rackNo) = 0;
  virtual void ReturnChange();
  virtual void DispenseProduct(int rackNo) = 0;
  virtual void UpdateInventory(int rackNo) = 0;
};

class NoMoneyInsertedState : public VendingMachineState {
  public:
  void InsertMoney(double money) override; //changes state to MoneyInserted state
  void PressButton(int rackNo) override;
  void ReturnChange() override;
  void DispenseProduct(int rackNo) override;
  void UpdateInventory(int rackNo) override;
};

class MoneyInsertedState : public VendingMachineState {
  public:
  void InsertMoney(double money) override;
  void PressButton(int rackNo) override; // Check if product is present, money is valid and change state to DispenseState.
  void ReturnChange() override;
  void DispenseProduct(int rackNo) override;
  void UpdateInventory(int rackNo) override;
};

class DispenseState : public VendingMachineState {
  public:
  void InsertMoney(double money) override;
  void PressButton(int rackNo) override;
  void ReturnChange() override;
  void DispenseProduct(int rackNo) override;  // dispense product and change state to NoMoneyInserted state.
  void UpdateInventory(int rackNo) override;
};

/************************ *  Product, Rack and Inventory  * ***********************************************************/
class Product {
private:
  int ProductId;
  std::string ProductName;
  ProductType type;
  double mrp;
};

class VMRack {
  private:
  int rackNo;
  std::vector<std::pair<Product, int>> products; //List of products mapped to its count.
public:
  bool IsEmpty();
  void AddProduct(Product product);
  void RemoveProduct(Product product);
  bool IsProductAvailable(Product product);
};

class Inventory {
  private:
  int totalProductCount;
  int typesOfProduct;  //How many types of product are present.
  std::vector<std::pair<Product, int>> products; //List of products mapped to its count.
  public:
  bool IsEmpty();
  void AddProduct(Product product);
  void RemoveProduct(Product product);
};

/************************ *  Vending Machine  * ***********************************************************************/

class VendingMachine {
  private:
  int vendingMachineId;
  VendingMachineState *vmState;
  int racksCount;
  std::list<VMRack *> racks;
  double billedAmount;  //total billing till date
  double cashInMachine; // amount in vending machine.

  public:
  void InsertMoney(double money);
  void PressButton(int rackNo);
  void ReturnChange();
  void DispenseProduct(int rackNo);
  void UpdateInventory(int rackNo);
};
/************************ *  End  * ***********************************************************************************/

#endif //VENDINGMACHINE_H
