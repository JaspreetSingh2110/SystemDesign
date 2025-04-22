/*
 * Description:
 * Low level design framework for online chess game.
 *
 * Created on: 4/22/2025
 * @author: Jaspreet Singh, mr.jaspreet2110@gmail.com.
 */

#ifndef ONLINECHESSGAME_H
#define ONLINECHESSGAME_H

#include <iostream>

class ChessPiece;

/**************************** *  * Enums *  * *************************************************************************/
enum ChessGameStatus {
  CGS_ACTIVE = 0,
  CGS_BLACK_WIN,
  CGS_WHITE_WIN,
  CGS_DRAW,
  CGS_STALEMATE,
  CGS_RESIGN
};

enum ChessPlayerAccountStatus {
  CPAS_ACTIVE = 0,
  CPAS_CLOSED,
  CPAS_BLOCKED,
  CPAS_BLACKLISTED,
  CPAS_NONE
};

/**************************** *  * Person *  * ************************************************************************/
class OCG_Person {
private:
  std::string name;
  std::string streetAddress;
  std::string city;
  std::string state;
  std::string country;
  std::string zipcode;
};

/**************************** *  * Box and chessboard *  * ************************************************************/
class ChessBox {
  private:
  int x;
  int y;
  ChessPiece *piece;
};


class ChessBoard {
  private:
  ChessBox boxes[8][8];
  time_t creationDate;

public:
  void ResetChessBoard();
  void UpdateBoard();
};

/**************************** *  * Piece and its derived types. *  * **************************************************/
class ChessPiece {
  private:
  bool isKilled;
  bool isWhite;

  public:
  bool IsKilled() const;
  bool IsWhite() const;
  virtual bool CanMove(ChessBoard& board, ChessBox& sBox, ChessBox& dBox) = 0;
};

class King : public ChessPiece {
  private:
  bool castlingDone;

public:
  bool CanMove(ChessBoard &board, ChessBox &sBox, ChessBox &dBox) override;
};

class Queen : public ChessPiece {
public:
  bool CanMove(ChessBoard &board, ChessBox &sBox, ChessBox &dBox) override;
};

class Knight : public ChessPiece {
public:
  bool CanMove(ChessBoard &board, ChessBox &sBox, ChessBox &dBox) override;
};

class Bishop : public ChessPiece {
public:
  bool CanMove(ChessBoard &board, ChessBox &sBox, ChessBox &dBox) override;
};

class Rook : public ChessPiece {
public:
  bool CanMove(ChessBoard &board, ChessBox &sBox, ChessBox &dBox) override;
};

class Pawn : public ChessPiece {
public:
  bool CanMove(ChessBoard &board, ChessBox &sBox, ChessBox &dBox) override;
};

/**************************** *  * Move *  * **************************************************************************/
class ChessMove {
private:
  ChessBox startBox;
  ChessBox endBox;
  ChessPiece *pieceKilled;  //captured piece
  ChessPiece *pieceMoved;   // moved piece
  bool isCastlingMove;

  public:
  bool IsCastlingMove();
};

/**************************** *  * Account: Player and Admin *  * *****************************************************/
class OCGAccount {
  private:
  std::string accountId;
  std::string password;
  time_t creationDate;
  ChessPlayerAccountStatus status;

  public:
  virtual void ResetPassword() = 0;
};

class OCG_PlayerAccount : public OCGAccount {
  private:
  OCG_Person person;
  bool isWhiteTeam;
  int totalGamesPlayed;

public:
  void ResetPassword() override;
};

class OCG_AdminAccount : public OCG_PlayerAccount {
public:
  void ResetPassword() override;
  void BlockPlayerAccount();
};

/**************************** *  * Chess game view and game controller *  * *******************************************/
class OnlineChessGameView {
public:
  void PlayMove();
};

class OnlineChessGameController {
public:
  bool ValidateMove();
};

/**************************** *  * Chess game *  * ********************************************************************/
class OnlineChessGame {
  private:
  ChessBoard chessboard;
  std::vector<OCG_PlayerAccount> players;
  OCG_PlayerAccount currentTurn;
  std::list<ChessMove > moves;
  ChessGameStatus status;

public:
  bool IsOver();
  bool PlayerMove(Player player, ChessBox &sBox, ChessBox &dBox);  //internally calls MakeMove.
  bool MakeMove(Player player, ChessMove move);
};
/**************************** *  * END *  * ***************************************************************************/

#endif //ONLINECHESSGAME_H
