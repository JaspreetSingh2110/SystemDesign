/*
 * Description:
 * Low level design framework for Jigsaw Puzzle.
 *
 * Created on: 5/1/2025
 * @author: Jaspreet Singh, mr.jaspreet2110@gmail.com.
 */

#ifndef JIGSAWPUZZLE_H
#define JIGSAWPUZZLE_H

#include <iostream>
#include <vector>

/********************* ** * Enums * ** ********************************************************************************/
enum JP_EdgeType {
  JP_ET_Flat,
  JP_ET_Intrusion,
  JP_ET_Extrusion
};

/********************* ** * Side * ** *********************************************************************************/
class JP_Side {
private:
  JP_EdgeType edge;
};

/********************* ** * Piece * ** ********************************************************************************/
class JP_Piece {
  private:
  JP_Side side[4];  // each piece is made of 4 sides.

public:
  bool IsMiddlePiece();
  bool IsCornerPiece();
  bool IsEdgePiece();
};

/********************* ** * Puzzle * ** *******************************************************************************/
class JigsawPuzzle {
private:
  int rows = 5; //default
  int cols = 5; //default
  std::vector<std::vector<JP_Piece*>> board;  //Board
  std::vector<JP_Piece*> freePieces;  //list of free pieces.
public:
  void InsertPiece(JP_Piece *piece, int row, int col);
};

/********************* ** * Jigsaw puzzle solver * ** *****************************************************************/
//It attempts to solve the puzzle.
class JigsawPuzzleSolver {
  private:
  JigsawPuzzle puzzle;

  public:
  void SolvePuzzle();
  bool MatchPiece(JP_Piece *piece, int row, int col);
};

/********************* ** * End * ** **********************************************************************************/

#endif //JIGSAWPUZZLE_H
