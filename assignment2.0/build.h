#include <vector>
#include <string>
#include <array>
// move keep a secondary board and if not valid move, send back to original board
enum color {white, black, clean};

class Piece{
	public:

		char item;
		int x;
		int y;
		bool update;
		bool firstMove;

		void updatePawn(Piece p);
		int listColor(Piece p);
		bool isUpgradable(Piece p);
		bool isValidMove(int x, int y);
		//change location on board and update
		//void updateCoor(Board b, Piece p, int x, int y);
		void move(int x, int y);
		void setPieceX(int x);
		void setPieceY(int y);
		//call at beginning to create every piece
		Piece createPiece(char item, int x, int y, bool update);
		void setPiece(char item, int x, int y, bool update);
		//when a piece moves clean the previous location
		void cleanSpace(int x, int y);
		void setColor(enum color);
		enum color getColor();
	private:
		color c;
};

class Board{
	public:
		Piece board[8][8];
		//build board to start out
		void initBoard();
		void print();
		void move(int pre_x, int pre_y, int x, int y);	
		int bKingX;
		int bKingY;
		int wKingX;
		int wKingY;
		
		bool BKChk;
		bool WKChk;
		bool BKChkMt;
		bool WKChkMt;

		bool isCheck(enum color c);
		//if isCheck is true, then we check checkmate
		bool isCheckMate(enum color);
		void setBKingX(int x);
		int getBKingX();
		void setBKingY(int y);
		int getBKingY();
		void setWKingX(int x);
		int getWKingX();
		void setWKingY(int y);
		int getWKingY();
		int getLoc(char c);
		bool validateLoc(std::string l, enum color c);	
		bool canMove(std::array<std::array<int,8>,8> a);
		bool mainControl(int x, int y, enum color col);

		void play();
		void displayPawn();
		void displayPawnUpgrade(Piece &p);
		void displayKing();
		void displayQueen();
		void displayRook();
		void displayBishop();
		void displayKnight();
		void displaySteps();
		void displayInfo();
		bool boundary(int x, int y);
		void displayMoves();


		//display possible moves in 2d-array
		std::array<std::array<int,8>,8> pMoves(int x, int y);
		bool validAux(std::array<std::array<int,8>,8> &arr, int st_x, int st_y, int cr_x, int cr_y);

};


