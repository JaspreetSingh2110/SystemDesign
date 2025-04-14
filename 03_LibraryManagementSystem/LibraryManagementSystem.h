/*
 * Description:
 * Low level design framework for Library management system.
 *
 * Created on: 4/14/2025
 * @author: Jaspreet Singh, mr.jaspreet2110@gmail.com.
 */

#ifndef LIBRARYMANAGEMENTSYSTEM_H
#define LIBRARYMANAGEMENTSYSTEM_H

#include <cstdint>
#include <iostream>
#include <list>
#include <map>

class Rack;
class Librarian;
class Member;

/**********************************  * Enumerations *  ****************************************************************/

enum BookType {
  BT_HARDCOVER,
  BT_PAPERBACK,
  BT_EBOOK,
  BT_AUDIOBOOK,
  BT_MAGAZINE,
  BT_JOURNAL,
  BT_NEWSPAPER
};

enum BookStatus {
  BS_AVAILABLE,
  BS_LOANED,
  BS_RESERVED,
  BS_LOST
};

enum ReservationStatus {
  RS_WAITING,
  RS_PENDING,
  RS_CANCELLED,
  RS_NONE
};

/**********************************  * Person *  **********************************************************************/
/*
 * CLASS PERSON: Commented to avoid build issue. It has been declared also in Parking Lot design.
 *
class Person {
  private:
  std::string name;
  std::string address;
  std::string phone;
  std::string email;
};
*/
/**********************************  * Person *  **********************************************************************/

class Author {
  private:
  Person person;
  std::string country;
};
/**********************************  * Address *  *********************************************************************/

class Address {
  private:
  std::string houseNumber;
  std::string streetAddress;
  std::string city;
  std::string state;
  std::string country;
  std::string zipcode;
};

/**********************************  * Book, BookItem and Racks *  ****************************************************/

class Book {
private:
  std::string isbn;
  std::string title;
  std::list<Author*> authors;
  std::string subject;
  std::string publisher;
  std::string language;
  std::string nosOfPages;
};

class BookItem {
  private:
  std::string id;
  BookType bookType;
  BookStatus bookStatus;
  uint32_t publishedDate;
  uint32_t borrowedDate;
  uint32_t dueDate;
  uint32_t purchasedDate;
  double price;

  Book *book;
  Rack *placedAt;

public:
  Book *GetBook();
  bool LendBook(std::string memberId);
  Rack* GetplacedAt();
  void SetPlacedAt(Rack *rack);
  void SetAddedBy(Librarian *librarian);
};

class Rack {
  private:
  int rackNo;
  std::string identifier;
  std::list<BookItem*> bookItems;

  public:
  void AddBookItem(BookItem *bookItem);
};

/**********************************  * LibraryCard *  *****************************************************************/

class LibraryCard {
  std::string id;
  uint32_t createdDate;
  uint32_t validUpto;
  Member *member;

public:
  bool IsValid();
};
/**********************************  * User (abstract) <- Librarian and Member *  *************************************/

class User {
  private:
  Person person;
  Address address;
  std::string id;
  std::string password;
  AccountStatus accountStatus;
  LibraryCard libCard;

public:
  virtual void ResetPassword() = 0;
};

class Librarian : public User {
public:
  void ResetPassword() override;

  void AddBookItem(BookItem* bookItem);
  bool BlockMember(User* user);
  bool UnblockMember(User* user);
};

class Member : public User {
private:
  int dateOfMembership;
  int totalBooksLoaned;

public:
  void ResetPassword() override;
  bool ReserveBookItem(BookItem *bookItem);
  bool CancelBookReservation(BookItem *bookItem);
  bool RenewBookItem(BookItem *bookItem);
  bool ReturnBookItem(BookItem *bookItem);
  int IncrementTotalBooksLoaned();
  int DecrementTotalBooksLoaned();
};

/**********************************  * Book reservation, lending and fine *  ******************************************/

class BookReservation {
  private:
  uint32_t creationDate;
  ReservationStatus reservationStatus;
  std::string bookId;
  std::string memberId;

public:
  BookReservation* GetBookReservationDetails(std::string bookItemId);
};

class BookLending {
  private:
  std::string bookItemId;
  std::string memberId;
  uint32_t creationDate;
  uint32_t dueDate;
  uint32_t returnDate;
  BookReservation *bookReservation;
  User *user;

  public:
  void SetBookReservation(BookReservation *bookReservation);
  bool LendBook(std::string bookItemId, std::string memberId);
};

class BookFine {
  private:
  uint32_t dueDate;
  uint32_t returnDate;
  uint32_t creationDate;
  std::string bookId;
  std::string memberId;

  public:
  double CalculateFine();
  bool CollectFine(double amount);
};

/**********************************  * Search and Catalog *  **********************************************************/

class Search {
public:
  virtual std::list<BookItem*> SearchByTitle(std::string title) = 0;
  virtual std::list<BookItem*> SearchBySubject(std::string subject) = 0;
  virtual std::list<BookItem*> SearchByAuthor(std::string author) = 0;
  virtual std::list<BookItem*> SearchByPublisher(std::string publisher) = 0;
};

class Catalog : public Search {
private:
  std::map<std::string, std::list<BookItem*>> booksByTitles;
  std::map<std::string, std::list<BookItem*>> booksBySubjects;
  std::map<std::string, std::list<BookItem*>> booksByAuthors;
  std::map<std::string, std::list<BookItem*>> booksByPublishers;

  public:
  std::list<BookItem*> SearchByTitle(std::string title) override;
  std::list<BookItem*> SearchBySubject(std::string subject) override;
  std::list<BookItem*> SearchByAuthor(std::string author) override;
  std::list<BookItem*> SearchByPublisher(std::string publisher) override;
};
/**********************************  * Notifications *  ***************************************************************/

class Notification {
  private:
  std::string notificationId;
  std::string content;
  uint32_t creationDate;
  BookReservation *bookReservation;
  BookLending *bookLending;

  public:
  virtual bool SendNotification() = 0;
};

class PostalNotification : public Notification {
  private:
  std::string address;

public:
  bool SendNotification() override;
};

class EmailNotification : public Notification {
private:
  std::string email;

  public:
  bool SendNotification() override;
};

/**********************************  * Library *  *********************************************************************/

class Library {
  private:
  std::string name;
  std::string address;

  std::list<Librarian *> librarians;
  std::map<std::string, std::list<Member *>> members;
  Catalog *catalog;

  static Library *library;
  public:
  static Library* GetInstance()
  {
    if (library == nullptr) {
      library = new Library();
    }
    return library;;
  }

  bool LoadLibrary();

  //Entry points to search books. These APIs will use catalog object to perform action and get results.
  std::list<std::string> SearchByTitle(std::string title);
  std::list<std::string> SearchBySubject(std::string subject);
  std::list<std::string> SearchByAuthor(std::string author);
  std::list<std::string> SearchByPublisher(std::string publisher);

  //These APIs shall use librarian object to perform actions.
  bool AddMember(/*details*/);
  bool RemoveMember(std::string memberId);
  bool AddBook(std::string bookId);
  bool RemoveBook(std::string bookId);
  bool AddLibrarian(Librarian *librarian);
  bool RemoveLibrarian(Librarian *librarian);

  //Transactions
  //These APIs must use member instance to perform action.
  bool LendBook(std::string title, Member *member);
  bool AddBookReservation(BookReservation *bookReservation);
  bool RemoveBookReservation(BookReservation *bookReservation);
};
/**********************************  * End *  *************************************************************************/

#endif //LIBRARYMANAGEMENTSYSTEM_H
