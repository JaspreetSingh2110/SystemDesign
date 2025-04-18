/*
 * Description:
 * Low level design framework for Movie ticket booking system.
 *
 * Created on: 4/18/2025
 * @author: Jaspreet Singh, mr.jaspreet2110@gmail.com.
 */

#ifndef MOVIETICKETBOOKINGSYSTEM_H
#define MOVIETICKETBOOKINGSYSTEM_H

#include <map>
#include <string>
#include <vector>

class ShowTime;
class Movie;
class MTBooking;
class Hall;
class Cinema;

/*********************************  * Enums *  ************************************************************************/
//Movie ticket booking payment status.
enum MTBPaymentStatus{
  MTBPaymentStatus_Invalid = 0,
  MTBPaymentStatus_Pending = 1,
  MTBPaymentStatus_Completed = 2,
  MTBPaymentStatus_Failed = 3,
  MTBPaymentStatus_Refunded = 4,
  MTBPaymentStatus_Max
};

//Booking status
enum MTBookingStatus {
  MTBookingStatus_Invalid = 0,
  MTBookingStatus_Pending = 1,
  MTBookingStatus_Completed = 2,
  MTBookingStatus_Failed = 3,
  MTBookingStatus_Cancelled = 4,
  MTBookingStatus_Denied = 5,
  MTBookingStatus_Refunded = 6,
  MTBookingStatus_Max
};

//Status of a seat.
enum MTBSeatStatus {
  MTBSeatStatus_Available,
  MTBSeatStatus_Booked,
  MTBSeatStatus_Reserved,
  MTBSeatStatus_Max
};

/*********************************  * People Involved : Customer, Agents and Admin *  *********************************/
//Abstract user class
//Note: The username and password are not member of abstract class user because a guest user type,
// can continue without registering into website/app.
class MTBUser {
private:
  std::string name;
  std::string address;
  std::string email;
  std::string phone;
};

class MTBCustomer : public MTBUser {
private:
  std::string customerId;
  std::string username;
  std::string password;
  std::vector<MTBooking*> bookings;

public:
  void CreateBooking(MTBooking booking);
  void CancelBooking(MTBooking booking);
};

//Booking agents.
class MTBAgent : public MTBUser {
private:
  std::string agentId;
  std::string username;
  std::string password;

  public:
  void CreateBooking(MTBooking booking);
};


//Admin user.
class MTBAdmin : public MTBUser {
  private:
  std::string adminId;
  std::string username;
  std::string password;

  public:
  void AddAgent(MTBAgent agent);
  void AddMovie(Movie movie);
  void DeleteMovie(Movie movie);
  void AddShow(ShowTime show);
  void UpdateShow(ShowTime show);
  void DeleteShow(ShowTime show);
};

/*********************************  * Seat *  *************************************************************************/
class MTBSeat {
  private:
  int seatNumber;
  double rate;
  MTBSeatStatus seatStatus;

  public:
  bool IsAvailable();
  void UpdateSeatStatus(MTBSeatStatus seatStatus);
  virtual void SetRate(double rate) = 0;
};

//Derived types of seat.

class SilverSeat : public MTBSeat {
  public:
  void SetRate(double rate) override;
};

class GoldSeat : public MTBSeat {
public:
  void SetRate(double rate) override;
};

class PlatinumSeat : public MTBSeat {
public:
  void SetRate(double rate) override;
};


/*********************************  * Movie, Showtime and MovieTickets *  *********************************************/
class Movie {
  private:
  std::string title;
  std::string genre;
  time_t releaseDate;
  std::string language;
  int durationInMinutes;
  std::vector<ShowTime> shows;
};

class ShowTime {
  private:
  int showId;
  time_t showTime;
  time_t showDate;
  int duration;
  std::map<std::string, std::vector<MTBSeat*>> seats;

  public:
  std::vector<MTBSeat*> ShowAvailableSeats();
};

class MovieTicket {
  private:
  int ticketId;
  MTBSeat *seat;
  Movie movie;
  ShowTime show;
};


/*********************************  * City, Cinema and hall *  ********************************************************/
class City {
  private:
  std::string name;
  std::string state;
  std::string pinCode;
  std::vector<Cinema*> cinema;
};

class Cinema {
  private:
  std::string cinemaId;
  std::string name;
  City city;
  std::vector<Hall*> halls;
};

class Hall {
  private:
  std::string hallId;
  std::vector<ShowTime> shows;

public:
  std::vector<ShowTime*> GetShows();
};


/*********************************  * Payment Service *  **************************************************************/
class MTBPayment {
  private:
  double amount;
  time_t paymentTime;
  MTBPaymentStatus paymentStatus;

  public:
  virtual void MakePayment(double amount) = 0;
};

class MTBCardPayment : public MTBPayment {
private:
  std::string cardNumber;
  std::string nameOnCard;
  std::string cvv;
  std::string code;
  std::string billingAddress;

public:
  void MakePayment(double amount);
};

class MTBCashPayment : public MTBPayment {
public:
  void MakePayment(double amount);
};

/*********************************  * MTBNotificationService *  *******************************************************/
class MTBNotification {
  private:
  std::string notificationId;
  std::string content;
  time_t createdOn;

  public:
  virtual void MakeNotification(std::string content) = 0;
  virtual void SendNotification(MTBUser *user) = 0;
};

class MTBEmailNotification : public MTBNotification {
  public:
  void MakeNotification(std::string content) override;
  void SendNotification(MTBUser *user) override;
};

class MTBPhoneNotification : public MTBNotification {
public:
  void MakeNotification(std::string content) override;
  void SendNotification(MTBUser *user) override;
};

/*********************************  * Booking *  **********************************************************************/
class MTBooking {
  private:
  std::string bookingId;
  double amount;
  time_t bookingDate;
  int totalSeats;
  MTBookingStatus bookingStatus;

  MTBPayment *payment;
  std::vector<MovieTicket*> tickets;
  std::vector<MTBSeat*> seats;
};


/*********************************  * Search and Catalog *  ***********************************************************/
class MTBSearch {
private:
  virtual std::vector<Movie*> SearchMoviesByTitle(std::string title) = 0;
  virtual std::vector<Movie*> SearchMoviesByGenre(std::string genre) = 0;
  virtual std::vector<Movie*> SearchMoviesByLanguage(std::string language) = 0;
  virtual std::vector<Movie*> SearchMoviesByReleaseDate(time_t releaseDate) = 0;
};

class MTBCatalog : public MTBSearch {
  private:
  std::map <std::string, std::vector<Movie*>> moviesByTitle;
  std::map <std::string, std::vector<Movie*>> moviesByGenre;
  std::map <std::string, std::vector<Movie*>> moviesByLanguage;
  std::map <time_t, std::vector<Movie*>> moviesByReleaseDate;

public:
  std::vector<Movie*> SearchMoviesByTitle(std::string title);
  std::vector<Movie*> SearchMoviesByGenre(std::string genre);
  std::vector<Movie*> SearchMoviesByLanguage(std::string language);
  std::vector<Movie*> SearchMoviesByReleaseDate(time_t releaseDate);
};


/*********************************  * End *  **************************************************************************/

#endif //MOVIETICKETBOOKINGSYSTEM_H
