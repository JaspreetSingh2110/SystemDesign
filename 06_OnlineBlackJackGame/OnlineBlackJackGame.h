/*
 * Description:
 * Low level design framework for 'online' blackjack game.
 *
 * Created on: 4/17/2025
 * @author: Jaspreet Singh, mr.jaspreet2110@gmail.com.
 */

#ifndef ONLINEBLACKJACKGAME_H
#define ONLINEBLACKJACKGAME_H

#include <iostream>
#include <list>
#include <vector>

/****************************  * Enums *  *****************************************************************************/
enum BJGame_AccountStatus {
  BJG_ACTIVE,
  BJG_CLOSED,
  BJG_BLACKLISTED,
  BJG_NONE
};

enum Suit {
  Spades,
  Hearts,
  Diamonds,
  Clubs
};

/****************************  * Person *  ****************************************************************************/
class BJGamePerson {
private:
  std::string name;
  std::string streetAddress;
  std::string city;
  std::string state;
  std::string country;
  std::string zipcode;
};


/****************************  * Card, Deck and Shoes *  **************************************************************/
class Card {
  private:
  int faceValue;
  Suit suit;
};

class Deck {
  private:
  std::vector<Card> cards;
};

class Shoe {
  private:
  std::list<Deck> decks;
  int deckCount;
  int maxDeckCount;

public:
  Shoe(std::list<Deck> decks, int deckCount)
  {
    //CreateShoe();
    //ShuffleShoe();
  }
  void CreateShoe();
  void Shuffle();
  void AddDeck(Deck deck);
  Card DrawCard();
};

/****************************  * Hand *  *****************************************************************************/
class Hand {
  private:
  std::vector<Card> cards;
  int handValue;

  public:
  Hand(Card card1, Card card2)
  {
    //update cards.
    //Calculate hand value.
  }
  void AddCard(Card card);
  void CalculateHandValue();
  int GetHandValue();
};
/****************************  * Player : BlackjackPlayer and Dealer *  ***********************************************/
class Player {
  private:
  std::string id;
  std::string password;
  BJGamePerson person;
  double balance;
  BJGame_AccountStatus accountStatus;
  Hand hand;

  public:
  Player(std::string id, std::string password, BJGame_AccountStatus accountStatus);
  void AddHand(Hand hand);
  void RemoveHand(Hand hand);
  void AddToHand();
  void ResetPassword(std::string password);
};

class BlackJackPlayer : public Player {
  private:
  int bet;

  public:
  BlackJackPlayer(Hand hand);
  void PlaceBet(int amount);
  void ResetPassword(std::string password);
};


class Dealer : public Player {
  public:
  Dealer(Hand hand);
  int getTotalScore();
  void ResetPassword(std::string password);
};

/****************************  * Blackjack Controller *  **************************************************************/
class BlackjackController {
  public:
  bool ValidateAction();
};

/****************************  * Blackjack Game view *  ***************************************************************/

class BlackjackGameView {
  public:
  bool ProcessAction(std::string action);
};

/****************************  * Blackjack Game *  ********************************************************************/
class BlackjackGame {
  private:
  std::list<Player> players;
  Dealer dealer;
  Shoe shoe;
  BlackjackController controller;
  int maxNosOfDecks;

  public:
  BlackjackGame(std::list<Player> players, Dealer dealer);
  void StartGame();
  void Stand();
  void Hit(Hand hand);
  void PlayAction(std::string action);
};
/****************************  * * End * *  ***************************************************************************/

#endif //ONLINEBLACKJACKGAME_H
