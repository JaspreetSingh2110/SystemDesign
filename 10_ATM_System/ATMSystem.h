/*
 * Description:
 * Low level design framework for ATM system.
 *
 * Created on: 4/22/2025
 * @author: Jaspreet Singh, mr.jaspreet2110@gmail.com.
 */

#ifndef ATMSYSTEM_H
#define ATMSYSTEM_H

#include <iostream>


/**************************** *  * Enums *  * *************************************************************************/
enum ATM_Status {
  AS_UNKNOWN = 0,
  AS_POWERED_OFF,
  AS_POWERED_ON,
  AS_IDLE,
  AS_HAS_CARD,
  AS_SELECT_OPTION,
  AS_SHOW_BALANCE,
  AS_CASH_WITHDRAW,
  AS_BALANCE_TRANSFER
};

/**************************** *  * ATM card *  * ***********************************************************************/
class ATM_Card {
  private:
  std::string cardNumber;
  std::string nameOnCard;
  std::string expiryDate;
  std::string cvv;
  std::string pin;
};

/**************************** *  * Bank and Bank Account *  * *********************************************************/
class Bank {
  private:
  std::string name;
  std::string bankCode;

public:
  void AddATM();
};

class BankAccount {
  private:
  std::string bankAccountNumber;
  time_t creationDate;
  double accountBalance;
};

class SavingsBankAccount : public BankAccount {
public:
  double GetWithdrawalLimit();
};

class CurrentBankAccount : public BankAccount {
public:
  double GetWithdrawalLimit();
};

/**************************** *  * Person *  * ************************************************************************/
class ATM_Person {
  private:
  ATM_Card card;
  BankAccount account;
};

/**************************** *  * ATM components: card reader, screen, cash dispenser etc. *  * **********************/
class ATM_CardReader {
public:
  void ReadCard();
};

class ATM_Screen {
  public:
  void DisplayData();
};

class ATM_CashDispenser {
  public:
  void DispenseCash();
};

class ATM_Keypad {
  public:
  void GetInputs();
};

class ATM_Printer {
  public:
  void PrintReceipts();
};

/**************************** *  * ATM state *  * *********************************************************************/
class ATM_State {
public:
  virtual void InsertCard() = 0;
  virtual void AuthenticatePin() = 0;
  virtual void ShowOptions() = 0;
  virtual void TakeInputs() = 0;
  virtual void ShowBalance() = 0;
  virtual void DispenseCash() = 0;
  virtual void TransferCash() = 0;
  virtual void PrintReceipt() = 0;
  virtual void ReturnCard() = 0;
  virtual void exit() = 0;
  ~ATM_State();
};

class ATM_IdleState : public ATM_State {
  public:
  void InsertCard() override;
  void AuthenticatePin() override;
  void ShowOptions() override;
  void TakeInputs() override;
  void ShowBalance() override;
  void DispenseCash() override;
  void TransferCash() override;
  void PrintReceipt() override;
  void ReturnCard() override;
  void exit() override;
};

class ATM_HasCardState : public ATM_State {
public:
  void InsertCard() override;
  void AuthenticatePin() override;
  void ShowOptions() override;
  void TakeInputs() override;
  void ShowBalance() override;
  void DispenseCash() override;
  void TransferCash() override;
  void PrintReceipt() override;
  void ReturnCard() override;
  void exit() override;
};

class ATM_SelectOperations : public ATM_State {
public:
  void InsertCard() override;
  void AuthenticatePin() override;
  void ShowOptions() override;
  void TakeInputs() override;
  void ShowBalance() override;
  void DispenseCash() override;
  void TransferCash() override;
  void PrintReceipt() override;
  void ReturnCard() override;
  void exit() override;
};

class ATM_ShowBalanceState : public ATM_State {
public:
  void InsertCard() override;
  void AuthenticatePin() override;
  void ShowOptions() override;
  void TakeInputs() override;
  void ShowBalance() override;
  void DispenseCash() override;
  void TransferCash() override;
  void PrintReceipt() override;
  void ReturnCard() override;
  void exit() override;
};

class ATM_DispenseCashState : public ATM_State {
public:
  void InsertCard() override;
  void AuthenticatePin() override;
  void ShowOptions() override;
  void TakeInputs() override;
  void ShowBalance() override;
  void DispenseCash() override;
  void TransferCash() override;
  void PrintReceipt() override;
  void ReturnCard() override;
  void exit() override;
};

class ATM_TransferMoneyState : public ATM_State {
public:
  void InsertCard() override;
  void AuthenticatePin() override;
  void ShowOptions() override;
  void TakeInputs() override;
  void ShowBalance() override;
  void DispenseCash() override;
  void TransferCash() override;
  void PrintReceipt() override;
  void ReturnCard() override;
  void exit() override;
};

/**************************** *  * ATM and ATM room *  * **************************************************************/
class ATM {
private:
  ATM_CardReader cardReader;
  ATM_Keypad keypad;
  ATM_Screen screen;
  ATM_CashDispenser cashDispenser;
  ATM_Printer printer;
  ATM_State *state;

  // Related to money in ATM.
  double atmBalance;
  int hundredBillCount;
  int fiveHundredBillCount;

public:
  bool InitialiseATM();
};

class ATM_Room {
private:
  std::vector<ATM> atms;
  std::vector<ATM_Person> persons;
};

/**************************** *  * END *  * ***************************************************************************/


#endif //ATMSYSTEM_H
