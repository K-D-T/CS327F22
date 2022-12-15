#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <cmath>
#include "ncurses.h"
#include "build.h"

void Board::initBoard(){
	Piece p; 
	p.createPiece(' ',0,0,false);
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(i == 1 || i == 6){
				p.setPiece('P',i,j,true);
				p.firstMove = true;
				if(i == 1)
					p.setColor(color::black);
				else
					p.setColor(color::white);
				board[i][j] = p;
			}
			if(i == 2 || i == 3 || i == 4 || i == 5){
				p.setPiece(' ',i,j, false);
				p.setColor(color::clean);
				board[i][j] = p;
			}
			if(i == 0 || i == 7){
				if(j == 0 || j == 7){
					p.setPiece('R',i,j,false);
					if(i == 0)
						p.setColor(color::black);
					else
						p.setColor(color::white);
					board[i][j] = p;
				}
				if(j == 1 || j == 6){
					p.setPiece('N',i,j,false);//N for Knight
					if(i == 0)
						p.setColor(color::black);
					else
						p.setColor(color::white);
					board[i][j] = p;
				}
				if(j == 2 || j == 5){
					p.setPiece('B',i,j,false);
					if(i == 0)
						p.setColor(color::black);
					else
						p.setColor(color::white);
					board[i][j] = p;
				}
				if(j == 3){
					p.setPiece('Q',i,j,false);
					if(i == 0)
						p.setColor(color::black);
					else
						p.setColor(color::white);
					board[i][j] = p;
				}
				if(j == 4){
					p.setPiece('K',i,j,false);
					if(i == 0){
						p.setColor(color::black);
						bKingX = i;
						bKingY = j;
						BKChkMt = false;
					}else{
						p.setColor(color::white);
						wKingX = i;
						wKingY = j;
						WKChkMt = false;
					}
					board[i][j] = p;
				}
			}
		}
	}
}

void Piece::move(int x, int y){
	int prev_x = this->x;
	int prev_y = this->y;
	this->setPieceX(x);
	this->setPieceY(y);
	this->cleanSpace(x,y);
	//figure out how to place the piece 
}

void Board::move(int pre_x, int pre_y, int x, int y){
	//Piece::move(x,y);
	Piece p; 
	p.setPiece(board[pre_x][pre_y].item, board[x][y].x,
			board[x][y].y,board[pre_x][pre_y].update);
	p.setColor(board[pre_x][pre_y].getColor());
	board[pre_x][pre_y].move(x,y);
	if(p.item == 'P' && p.firstMove == true)
		p.firstMove = false;
	if(p.item == 'K' && p.getColor() == color::white){
		setWKingX(x);
		setWKingY(y);
	}
	if(p.item == 'K' && p.getColor() == color::black){
		setBKingX(x);
		setBKingY(y);
	}
	enum color n;
	if(p.getColor() == color::white)
		n = color::black;	
	else if(p.getColor() == color::black)
		n = color::white;
	board[x][y] = p;
	if(p.item == 'P' && p.getColor() == color::white && x == 0){
		displayPawnUpgrade(p);
		board[x][y] = p;
	}
	if(p.item == 'P' && p.getColor() == color::black && x == 7){
		displayPawnUpgrade(p);
		board[x][y] = p;
	}
}

void Board::print(){
	int r1 = 0, f = 7;
	int bi = 0 ,bj = 0;
	int padi = 1, padj = 0, padf = 0;
	char rank[] = {'A','B','C','D','E','F','G','H'};
	char file[] = {'1','2','3','4','5','6','7','8'};
	for(int i = 0; i < 16; i++){
		for(int j = 0; j < 16; j++){
			if(i % 2 == 0 && j % 2 == 0){// place rank, rollover at 7
				if(r1 == 8)
					r1 = 0;
				mvaddch(padi+i,j+padj,rank[r1]);
				r1++;
				padj++;
			}
			if(i % 2 == 0 && j % 2 != 0){//place piece
				if(bj == 8){
					bj = 0;
					bi+= 1;
				}
				mvaddch(padi+i,j+padj,board[bi][bj].item);
				bj++;
				padj++;
			}
			if(i % 2 != 0 && j % 2 == 0){//place file, rollover at 7
				mvaddch(padi+i,j+padf,file[f]);
				padf+=2;
			}
		}
		padi++;
		padj = 0;
		padf = 0;
		f = f - 2 + 3;
	}
	//for(int i  = 0; i < 8; i++){
	//	for(int j = 0; j < 8; j++){
			//std::cout << board[i][j].item << " "; 
	//		mvaddch(i,j,board[i][j].item);
	//	}
		//std::cout << std::endl;
	//}
	refresh();
}

void Piece::cleanSpace(int x, int y){
	this->item = ' ';
	this->x = x;
	this->y = y;
	this->c = color::clean;
}

Piece Piece::createPiece(char item, int x, int y, bool update){
	Piece p;
	p.setPiece(item, x, y, update);
	return p;	
}

void Piece::setPiece(char item, int x, int y, bool update){
	this->item = item;
	this->x = x;
	this->y = y;
	this->update = update;	
}

void Piece::setColor(color c){
	this->c = c;
}

void Piece::setPieceX(int x){
	this->x = x;
}

void Piece::setPieceY(int y){
	this->y = y;
}

enum color Piece::getColor(){
	if(this->c == color::white)
		return color::white;
	else if(this->c == color::black)
		return color::black;
	else
		return color::clean;
}

std::array<std::array<int,8>,8> Board::pMoves(int x, int y){
	std::array<std::array<int,8>,8> arr;
	arr.fill({});
	//Piece p = board[x][y];
	char c = board[x][y].item;
	if(c == 'K'){
		for(int i = x - 1; i <= x + 1; i++){
			for(int j = y - 1; j <= y + 1; j++){
				if(i >= 0 && i < 8 && j >= 0 && j < 8
					&& (board[i][j].getColor() != 
					board[x][y].getColor() && 
					board[i][j].item != 'K')){
					arr[i][j] = 1;
				}
			}
		}
	}
	if(c == 'R'){
		char t = 'v';
		for(int i = x; i >= 0; i--){
			t = board[i][y].item;
			if(board[x][y].getColor() == board[i][y].getColor()
				&& (i != x)){
				break;
			}
			if((x != i) && (t == 'K' || t == 'Q' || t == 'R' ||
				t == 'P' || t == 'B' || t == 'N')){
				arr[i][y] = 1;
				break;
			}
			arr[i][y] = 1;
		}
		for(int i = y; i < 8; i++){
			t = board[x][i].item;
			if(board[x][y].getColor() == board[x][i].getColor()
				&& (i != y)){
				break;
			}
			if((y != i) && (t == 'K' || t == 'Q' || t == 'R' ||
				t == 'P' || t == 'B' || t == 'N')){
				arr[x][i] = 1;
				break;
			}
			arr[x][i] = 1;
		}
		for(int i = x; i < 8; i++){
			t = board[i][y].item;
			if(board[x][y].getColor() == board[i][y].getColor()
				&& (i != x)){
				break;
			}
			if((i != x) && (t == 'K' || t == 'Q' || t == 'R' ||
				t == 'P' || t == 'B' || t == 'N')){
				arr[i][y] = 1;
				break;
			}
			arr[i][y] = 1;
		}
		for(int i = y; i >= 0; i--){
			t = board[x][i].item;
			if(board[x][y].getColor() == board[x][i].getColor()
				&& (i != y)){
				break;
			}
			if((y != i) && (t == 'K' || t == 'Q' || t == 'R' ||
				t == 'P' || t == 'B' || t == 'N')){
				arr[x][i] = 1;
				break;
			}
			arr[x][i] = 1;
		}
	}
	if(c == 'P'){
		char c; 
		if(board[x][y].getColor() == color::white){
			if(x-2 > 0){
				if(board[x-1][y].item == ' ')
					arr[x-1][y] = 1;
				if(board[x-2][y].item == ' ' 
					&& board[x][y].firstMove == true)
					arr[x-2][y] = 1;
			}
			if(x - 1 >= 0){
				if(board[x-1][y].item == ' ')
					arr[x-1][y] = 1;
			}
			if(x - 1 >= 0 && y - 1 >= 0){
				c = board[x-1][y-1].item;
				if((board[x][y].getColor() != 
					board[x-1][y-1].getColor()) 
					&& (c == 'P' || c == 'R' || 
					c == 'Q' || c == 'K' || c == 'N' || c == 'B'))
					arr[x-1][y-1] = 1;
			}
			if(x - 1 >= 0 && y + 1 < 8){
				c = board[x-1][y+1].item;
				if((board[x][y].getColor() != 
					board[x-1][y+1].getColor())
					&& (c == 'P' || c == 'R' || c == 'Q'
					|| c == 'K' || c == 'N' || c == 'B'))
					arr[x-1][y+1] = 1;
			}
		}
		else{
			if(x+2 < 8){
				if(board[x+2][y].item == ' '
					&& board[x][y].firstMove == true)
					arr[x+2][y] = 1;
				if(board[x+1][y].item == ' ')
					arr[x+1][y] = 1;
			}
			if(x + 1 <= 7){
				if(board[x+1][y].item == ' ')
					arr[x+1][y] = 1;
			}
			if(x + 1 <= 7 && y - 1 >= 0){
				c = board[x+1][y-1].item;
				if((board[x][y].getColor() !=
					board[x+1][y-1].getColor())
					&& (c == 'P' || c == 'R' || c == 'Q'
					|| c == 'K' || c == 'N' || c == 'B'))
					arr[x+1][y-1] = 1;
			}
			if(x + 1 <= 7 && y + 1 < 8){
				c = board[x+1][y+1].item;
				if((board[x][y].getColor() != 
					board[x+1][y+1].getColor()) 
					&& (c == 'P' || c == 'R' || c == 'Q'
					|| c == 'K' || c == 'N' || c == 'B'))
				arr[x+1][y+1] = 1;
			}
		}
	}
	if(c == 'N'){
		int aux[8] = {2,1,-1,-1,1,-2,-2,2};
		int auy[8] = {1,2,2,-2,-2,1,-1,-1};
		for(int i = 0; i < 8; i++){
			if(x+aux[i] >= 0 && x+aux[i] < 8 
				&& y+auy[i] >=0 && y+auy[i] < 8
				&& board[x+aux[i]][y+auy[i]].getColor() 
				!= board[x][y].getColor()){
				arr[x+aux[i]][y+auy[i]] = 1;
			}
		}		
	}
	if(c == 'B'){
		char t = 'v';
		int v_x = x, v_y = y;
		//(-1,-1), (1,1), (-1,1), (1,-1)
		while(v_x >= 0 && v_y >= 0){ // (-1,-1)
			t = board[v_x][v_y].item;
			if(board[v_x][v_y].getColor() == board[x][y].getColor()
				&& (v_x != x && v_y != y)){
				break;
			}
			else if((v_x != x && v_y) && 
					(t == 'P' || t == 'R' || t == 'Q' 
					|| t == 'K'|| t == 'B' || t == 'N')){
				arr[v_x][v_y] = 1;
				break;
			}
			arr[v_x][v_y] = 1;
			v_x -= 1;
			v_y -= 1;
		}
		v_x = x; v_y = y;
		while(v_x >= 0 && v_y < 8){//(-1,1)
			t = board[v_x][v_y].item;
			if(board[v_x][v_y].getColor() == board[x][y].getColor()
				&& (v_x != x && v_y != y)){
				break;
			}
			else if((v_x != x && v_y != y) && 
					(t == 'P' || t == 'R' || t == 'Q'
					|| t == 'K' || t == 'B' || t == 'N')){
				arr[v_x][v_y] = 1;
				break;
			}
			arr[v_x][v_y] = 1;
			v_x -= 1;
			v_y += 1;
		}
		v_x = x; v_y = y;
		while(v_x < 8 && v_y < 8){//(1,1)
			t = board[v_x][v_y].item;
			if(board[v_x][v_y].getColor() == board[x][y].getColor()
				&& (v_x != x && v_y != y)){
				break;
			}
			else if((v_x != x && v_y != y) && 
					(t == 'P' || t == 'R' || t == 'Q'
					|| t == 'K' || t == 'B' || t == 'N')){
				arr[v_x][v_y] = 1;
				break;
			}
			arr[v_x][v_y] = 1;
			v_x += 1;
			v_y += 1;
		}
		v_x = x; v_y = y;
		while(v_x < 8 && v_y >= 0){//(1,-1)
			t = board[v_x][v_y].item;
			if(board[v_x][v_y].getColor() == board[x][y].getColor()
				&& (v_x != x && v_y != y)){
				break;
			}
			else if((v_x != x && v_y != y) && 
					(t == 'P' || t == 'R' || t == 'Q'
					|| t == 'K' || t == 'B' || t == 'N')){
				arr[v_x][v_y] = 1;
				break;
			}

			arr[v_x][v_y] = 1;
			v_x += 1;
			v_y -= 1;
		}
	}
	if(c == 'Q'){
		for(int i = x - 1; i <= x + 1; i++){
			for(int j = y - 1; j <= y + 1; j++){
				if(i >= 0 && i < 8 && j >= 0 && j < 8
					&& (board[i][j].getColor() != 
					board[x][y].getColor())){
					arr[i][j] = 1;
				}
			}
		}
		char t = 'v';
		for(int i = x; i >= 0; i--){
			t = board[i][y].item;
			if(board[x][y].getColor() == board[i][y].getColor()
				&& (i != x)){
				break;
			}
			if((x != i) && (t == 'K' || t == 'Q' || t == 'R' ||
				t == 'P' || t == 'B' || t == 'N')){
				arr[i][y] = 1;
				break;
			}
			arr[i][y] = 1;
		}
		for(int i = y; i < 8; i++){
			t = board[x][i].item;
			if(board[x][y].getColor() == board[x][i].getColor()
				&& (i != y)){
				break;
			}
			if((y != i) && (t == 'K' || t == 'Q' || t == 'R' ||
				t == 'P' || t == 'B' || t == 'N')){
				arr[x][i] = 1;
				break;
			}
			arr[x][i] = 1;
		}
		for(int i = x; i < 8; i++){
			t = board[i][y].item;
			if(board[x][y].getColor() == board[i][y].getColor()
				&& (i != x)){
				break;
			}
			if((i != x) && (t == 'K' || t == 'Q' || t == 'R' ||
				t == 'P' || t == 'B' || t == 'N')){
				arr[i][y] = 1;
				break;
			}
			arr[i][y] = 1;
		}
		for(int i = y; i >= 0; i--){
			t = board[x][i].item;
			if(board[x][y].getColor() == board[x][i].getColor()
				&& (i != y)){
				break;
			}
			if((y != i) && (t == 'K' || t == 'Q' || t == 'R' ||
				t == 'P' || t == 'B' || t == 'N')){
				arr[x][i] = 1;
				break;
			}
			arr[x][i] = 1;
		}

		t = 'v';
		int v_x = x, v_y = y;
		//(-1,-1), (1,1), (-1,1), (1,-1)
		while(v_x >= 0 && v_y >= 0){ // (-1,-1)
			t = board[v_x][v_y].item;
			if(board[v_x][v_y].getColor() == board[x][y].getColor()
				&& (v_x != x && v_y != y)){
				break;
			}
			else if((v_x != x && v_y) && 
					(t == 'P' || t == 'R' || t == 'Q' 
					|| t == 'K'|| t == 'B' || t == 'N')){
				arr[v_x][v_y] = 1;
				break;
			}
			arr[v_x][v_y] = 1;
			v_x -= 1;
			v_y -= 1;
		}
		v_x = x; v_y = y;
		while(v_x >= 0 && v_y < 8){//(-1,1)
			t = board[v_x][v_y].item;
			if(board[v_x][v_y].getColor() == board[x][y].getColor()
				&& (v_x != x && v_y != y)){
				break;
			}
			else if((v_x != x && v_y != y) && 
					(t == 'P' || t == 'R' || t == 'Q'
					|| t == 'K' || t == 'B' || t == 'N')){
				arr[v_x][v_y] = 1;
				break;
			}
			arr[v_x][v_y] = 1;
			v_x -= 1;
			v_y += 1;
		}
		v_x = x; v_y = y;
		while(v_x < 8 && v_y < 8){//(1,1)
			t = board[v_x][v_y].item;
			if(board[v_x][v_y].getColor() == board[x][y].getColor()
				&& (v_x != x && v_y != y)){
				break;
			}
			else if((v_x != x && v_y != y) && 
					(t == 'P' || t == 'R' || t == 'Q'
					|| t == 'K' || t == 'B' || t == 'N')){
				arr[v_x][v_y] = 1;
				break;
			}
			arr[v_x][v_y] = 1;
			v_x += 1;
			v_y += 1;
		}
		v_x = x; v_y = y;
		while(v_x < 8 && v_y >= 0){//(1,-1)
			t = board[v_x][v_y].item;
			if(board[v_x][v_y].getColor() == board[x][y].getColor()
				&& (v_x != x && v_y != y)){
				break;
			}
			else if((v_x != x && v_y != y) && 
					(t == 'P' || t == 'R' || t == 'Q'
					|| t == 'K' || t == 'B' || t == 'N')){
				arr[v_x][v_y] = 1;
				break;
			}

			arr[v_x][v_y] = 1;
			v_x += 1;
			v_y -= 1;
		}
	}

	arr[x][y] = 5; //set a random val for starting point;

	return arr;
}

bool Board::validAux(std::array<std::array<int,8>,8> &arr, int st_x, int st_y, int cr_x, int cr_y){
	//not an eligible move
	if(arr[cr_x][cr_y] != 1)
		return false;
	else{
		//can'r move into location occupied by same piece
		if(board[cr_x][cr_y].getColor() == board[st_x][st_x].getColor()){
			return false;
		}//handles first move for pawns if 2 steps
		if(board[st_x][st_y].item == 'P' && 
				((abs(st_x - cr_x) == 2) || (abs(st_y - cr_y) == 2)) 
				&& (board[st_x][st_y].firstMove == true)){
			return true;
		}
		if(board[st_x][st_y].item == 'P' && (abs(st_y - cr_y) == 1) )
			return true;
		if(board[st_x][st_y].getColor() != board[cr_x][cr_y].getColor() 
				&& board[cr_x][cr_y].item != 'K'){
			return true;
		}
	}
	return false;
}

bool Board::isCheck(enum color c){
	//color will be the opposite of last move
	std::array<std::array<int,8>,8> arr;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(board[i][j].getColor() != c){
				arr = pMoves(i,j);
				for(int h = 0; h < 8; h++){
					for(int g = 0; g < 8; g++){
						if(c == color::white){
							if(h == getWKingX()
								&& g == getWKingY()
								&& arr[h][g] == 1)
								return true;
						}else if(c == color::black){
							if(h == getBKingX()
								&& g == getBKingY()
								&& arr[h][g] == 1)
								return true;
						}
					}
				}
			}
		}
	}
	return false;			
}

bool Board::isCheckMate(enum color c){
	std::array<std::array<int,8>,8> kmoves;
	std::array<std::array<int,8>,8> vMoves;
	if(c == color::white){
		kmoves = pMoves(getWKingX(),getWKingY());
	}else{
		kmoves = pMoves(getBKingX(),getBKingY());
	}
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(kmoves[i][j] == 1){//i,j is the location of pMoves
				for(int g = 0; g < 8; g++){
					for(int h = 0; h < 8; h++){
						if(c == color::white){
							if(board[g][h].getColor()
								== color::black){
								vMoves = pMoves(g,h);
								for(int r = 0; r < 8; r++){
									for(int t = 0; t < 8; t++){
										if(vMoves[r][t] == 1 && (r == i && t == j)){
											
										}
									}
								}
							}
						}else if(c == color::black){
						
						}
					}
				}
			}
		}
	}
	if(c == color::white){
		
	}else if(c == color::black){
	
	}
	return false;
}

void Board::setBKingX(int x){
	bKingX = x;
}

void Board::setBKingY(int y){
	bKingY = y;
}

void Board::setWKingX(int x){
	wKingX = x;
}

void Board::setWKingY(int y){
	wKingY = y;
}

int Board::getWKingX(){
	return wKingX;
}
int Board::getWKingY(){
	return wKingY;
}
int Board::getBKingX(){
	return bKingX;
}
int Board::getBKingY(){
	return bKingY;
}

void Board::displayPawnUpgrade(Piece &p){
	int ch;
	initscr();
	int height = 10, width = 40;
	int x = (20 - height) / 2 + 1;
	int y = (80 - width) / 2 + 1;
	WINDOW *pad = newpad(20,width);
	keypad(stdscr,TRUE);
	cbreak();
	noecho();	
	int pad_pos = 0;
	wprintw(pad, "Press 'Q' to change to Queen.\n");
	wprintw(pad, "Press 'N' to change to Knight.\n");
	wprintw(pad, "Press 'B' to change to Bishop.\n");
	wprintw(pad, "Press 'R' to change to Rook.\n");
	do{

		prefresh(pad,pad_pos,0,x,y,10,50);
		ch = getch();
	
		switch(ch){
			case 'Q':
			case 'q':
				p.item = 'Q';
				break;
			case 'N':
			case 'n':
				p.item = 'N';
				break;
			case 'b':
			case 'B':
				p.item = 'B';
				break;
			case 'r':
			case 'R':
				p.item = 'R';
				break;
		}

	}while(ch != 'Q' && ch != 'q' && ch != 'N' && ch != 'n'
		       	&& ch != 'B' && ch != 'b' && ch != 'r' && ch != 'R');

	clear();

}

void Board::displayPawn(){
	int ch;
	initscr();
	int height = 10, width = 40;
	int x = (20 - height) / 2 + 1;
	int y = (80 - width) / 2 + 1;
	WINDOW *pad = newpad(20,width);
	keypad(stdscr,TRUE);
	cbreak();
	noecho();	
	int pad_pos = 0;
	wprintw(pad,"Press Escape to close!\n");
	wprintw(pad, "Press 'i' to move up.\n");
	wprintw(pad, "Press 'u' to capture to the left.\n");
	wprintw(pad, "Press 'o' to capture to the right.\n");
	do{

		prefresh(pad,pad_pos,0,x,y,10,50);
		ch = getch();
	
		switch(ch){
		}

	}while(ch != 27);

	clear();
}

void Board::displayKing(){
	int ch;
	initscr();
	int height = 10, width = 40;
	int x = (20 - height) / 2 + 1;
	int y = (80 - width) / 2 + 1;
	WINDOW *pad = newpad(20,width);
	keypad(stdscr,TRUE);
	cbreak();
	noecho();	
	int pad_pos = 0;
	wprintw(pad,"Press Escape to close!\n");
	wprintw(pad,"Press 'r' for upper-left, 't' for up 1, 'y' for upper-right.\n");
	wprintw(pad,"Press 'f' for left, 'h' for right.\n");
	wprintw(pad,"Press 'v' for lower left, 'b' for down, 'n' for lower right.\n");
	do{

		prefresh(pad,pad_pos,0,x,y,10,50);
		ch = getch();
	
		switch(ch){
		}

	}while(ch != 27);

	clear();

}

void Board::displayQueen(){
	int ch;
	initscr();
	int height = 10, width = 40;
	int x = (20 - height) / 2 + 1;
	int y = (80 - width) / 2 + 1;
	WINDOW *pad = newpad(20,width);
	keypad(stdscr,TRUE);
	cbreak();
	noecho();	
	int pad_pos = 0;
	wprintw(pad,"Press Escape to close!\n");
	wprintw(pad,"Press 'i' for up, 'j' for left.\n");
	wprintw(pad,"Press 'k' for down, 'l' for right.\n");
	wprintw(pad,"Press 'o' for upper-right, 'u' for upper-left.\n");
	wprintw(pad,"Press 'n' for lower-left, 'm' for upper-left.\n");
	do{

		prefresh(pad,pad_pos,0,x,y,10,50);
		ch = getch();
	
		switch(ch){
		}

	}while(ch != 27);

	clear();
}

void Board::displayRook(){
	int ch;
	initscr();
	int height = 10, width = 40;
	int x = (20 - height) / 2 + 1;
	int y = (80 - width) / 2 + 1;
	WINDOW *pad = newpad(20,width);
	keypad(stdscr,TRUE);
	cbreak();
	noecho();	
	int pad_pos = 0;
	wprintw(pad,"Press Escape to close!\n");
	wprintw(pad,"Press 'i' for up, 'j' for left.\n");
	wprintw(pad,"Press 'k' for down, 'l' for right.\n");
	do{

		prefresh(pad,pad_pos,0,x,y,10,50);
		ch = getch();
	
		switch(ch){
		}

	}while(ch != 27);

	clear();

}

void Board::displayBishop(){
	int ch;
	initscr();
	int height = 10, width = 40;
	int x = (20 - height) / 2 + 1;
	int y = (80 - width) / 2 + 1;
	WINDOW *pad = newpad(20,width);
	keypad(stdscr,TRUE);
	cbreak();
	noecho();	
	int pad_pos = 0;
	wprintw(pad,"Press Escape to close!\n");
	wprintw(pad,"Press 't' for up-left, 'u' for up-right.\n");
	wprintw(pad,"Press 'b' for down-left, 'n' for down-right.\n");
	do{

		prefresh(pad,pad_pos,0,x,y,10,50);
		ch = getch();
	
		switch(ch){
		}

	}while(ch != 27);

	clear();
}

void Board::displayKnight(){
	int ch;
	initscr();
	int height = 10, width = 40;
	int x = (20 - height) / 2 + 1;
	int y = (80 - width) / 2 + 1;
	WINDOW *pad = newpad(20,width);
	keypad(stdscr,TRUE);
	cbreak();
	noecho();	
	int pad_pos = 0;
	wprintw(pad,"Press Escape to close!\n");
	wprintw(pad,"Press 'w' for up, 'd' for right.\n");
	wprintw(pad,"Press 'a' for left, 's' for down.\n");
	do{

		prefresh(pad,pad_pos,0,x,y,10,50);
		ch = getch();
	
		switch(ch){
		}

	}while(ch != 27);

	clear();
}

int Board::getLoc(char c){
	int x;
	if(c == '1')
		x = 7;
	if(c == '2')
		x = 6;
	if(c == '3')
		x = 5;
	if(c == '4')
		x = 4;
	if(c == '5')
		x = 3;
	if(c == '6')
		x = 2;
	if(c == '7')
		x = 1;
	if(c == '8')
		x = 0;

	switch(c){
		case 'A':
		case 'a':
			x = 0;
			break;
		case 'B':
		case 'b':
			x = 1;
			break;
		case 'c':
		case 'C':
			x = 2;
			break;
		case 'd':
		case 'D':
			x = 3;
			break;
		case 'e':
		case 'E':
			x = 4;
			break;
		case 'f':
		case 'F':
			x = 5;
			break;
		case 'g':
		case 'G':
			x = 6;
			break;
		case 'H':
		case 'h':
			x = 7;
			break;
		}
	//std::cout << "x:" << x << std::endl;
	return x;
}

void Board::play(){
	int ch;
	initscr();
	keypad(stdscr,TRUE);
	cbreak();
	noecho();
	curs_set(0);
	refresh();
	displayMoves();
	refresh();
	bool wTurn = true;//white turn active, switch off and on
	bool valid = false;
	int x,y;
	std::string location;
	while(BKChkMt == false && WKChkMt == false){	
		displaySteps();
		refresh();
		while(valid == false){
			std::cin >> location;
			if(location.size() == 2){
				if(wTurn == true){
					valid = validateLoc(location,color::white);
				}else if(wTurn == false){
					valid = validateLoc(location,color::black);
				}
				if(valid == true){
					x = getLoc(location.at(1));
					y = getLoc(location.at(0));
					//displayMoves();
					if(wTurn == true)
						valid = mainControl(x,y,color::white);
					else if(wTurn == false)
						valid = mainControl(x,y,color::black);
					if(valid == true){
						if(wTurn == true)
							wTurn = false;
						else if(wTurn == false)
							wTurn = true;
					}
				}
			}
		}
	valid = false;	
	}
}

bool Board::mainControl(int x, int y, enum color col){
	//std::array<std::array<char,8>,8> dup;
	std::array<std::array<int,8>,8> moves;
	char c = board[x][y].item; 
	enum color cur = board[x][y].getColor();
	if(col != cur)
		return false;
	moves = pMoves(x,y);
	Piece dup[8][8];
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			dup[i][j] = board[i][j];	
		}
	}
	int ch;
	noecho();
	cbreak();
	//displayInfo();
	int w = x;
	int e = y;
	do{

		ch = getch();
	
		switch(ch){
			case 't':
			case 'T':
				if(cur == color::white){
					if(boundary(w-1,e-1) == true){
						move(w,e,w-1,e-1);
						w-=1;
						e-=1;
					}		
				}else if(cur == color::black){
					if(boundary(w+1,e+1) == true){
						move(w,e,w+1,e+1);
						w+=1;
						e+=1;
					}
				}
				break;
			case 'Y':
			case 'y':
				if(cur == color::white){
					if(boundary(w-1,e) == true){
						move(w,e,w-1,e);
						w-=1;
						clear();
						print();
					}
				}else if(cur == color::black){
					if(boundary(w+1,e) == true){
						move(w,e,w+1,e);
						w+=1;
						clear();
						print();
					}
				}
				break;
			case 'u':
			case 'U':
				if(cur == color::white){
					if(boundary(w-1,e+1) == true){
						move(w,e,w-1,e+1);
						w-=1;
						e+=1;
					}
				}else if(cur == color::black){
					if(boundary(w+1,e-1) == true){
						move(w,e,w+1,e-1);
						w+=1;
						e-=1;
					}
				}
				break;
			case 'G':
			case 'g':
				if(cur == color::white){
					if(boundary(w,e-1) == true){
						move(w,e,w,e-1);
						e-=1;
					}
				}else if(cur == color::black){
					if(boundary(w,e+1) == true){
						move(w,e,w,e+1);
						e+=1;
					}
				}
				break;
			case 'j':
			case 'J':
				if(cur == color::white){
					if(boundary(w,e+1) == true){
						move(w,e,w,e+1);
						e+=1;
					}	
				}else if(cur == color::black){
					if(boundary(w,e-1) == true){
						move(w,e,w,e-1);
						e-=1;
					}
				}
				break;
			case 'b':
			case 'B':
				if(cur == color::white){
					if(boundary(w+1,e-1) == true){
						move(w,e,w+1,e-1);
						w+=1;
						e-=1;
					}
				}else if(cur == color::black){
					if(boundary(w+1,e+1) == true){
						move(w,e,w+1,e+1);
						w+=1;
						e+=1;
					}
				}
				break;
			case 'n':
			case 'N':
				if(cur == color::white){
					if(boundary(w+1,e) == true){
						move(w,e,w+1,e);
						w+=1;
					}
				}else if(cur == color::black){
					if(boundary(w-1,e) == true){
						move(w,e,w-1,e);
						w-=1;
					}
				}
				break;
			case 'm':
			case 'M':
				if(cur == color::white){
					if(boundary(w+1,e+1) == true){
						move(w,e,w+1,e+1);
						w+=1;
						e+=1;
					}
				}else if(cur == color::black){
					if(boundary(w-1,e-1) == true){
						move(w,e,w-1,e-1);
						w-=1;
						e-=1;
					}
				}
				break;
		}
		refresh();
		clear();
		print();

	}while(ch != 'q' && ch != 'Q' && ch != 'f' && ch != 'F');
	
	if(ch == 'q' || ch == 'Q'){
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				board[i][j] = dup[i][j];
			}
		}
		clear();
		print();
		return false;
	}
	if(ch == 'f' || ch == 'F'){
		if(moves[w][e] != 1){
			clear();
			print();
			for(int i = 0; i < 8; i++)
				for(int j = 0; j < 8; j++)
					board[i][j] = dup[i][j];
			clear();
			print();
			return false;
		}
		else if(moves[w][e] == 1)
			return true;
	}
	return false;
}

bool Board::boundary(int x, int y){
	if(x > 7 || x < 0 || y < 0 || y > 7)
		return false;
	return true;
}

void Board::displayInfo(){
	int ch; 
	int height = 10, width = 40;
	int v = (20 - height) / 2 + 1;
	int b = (80 - width) / 2 + 1;
	WINDOW *pad = newpad(20,width+20);
	keypad(stdscr,TRUE);
	cbreak();
	noecho();
	refresh();	
	wprintw(pad,"Press Escape to close!\n");
	wprintw(pad,"Once closed, Press 'f' to finalize your move\n");
	wprintw(pad,"Press 'Q' to cancel move, and choose different piece");

	do{

		ch = getch();
		prefresh(pad,0,0,v,b,20,100);	
		switch(ch){
		}

	}while(ch != 27);
	clear();
	print();
}

bool Board::validateLoc(std::string l, enum color c){
	char a = l.at(0);
	char b = l.at(1);
	int x = -1, y = -1;
	std::array<std::array<int,8>,8> moves;
	if((a == 'A' || a == 'a' || a == 'B' || a == 'b' ||
		a == 'C' || a == 'c' || a == 'D' || a == 'd'||
		a == 'e' || a == 'E' || a == 'F' || a == 'f'||
		a == 'g' || a == 'G' || a == 'H' || a == 'h') 
		&& (b == '1' || b == '2' || b == '3' || b == '4'
		||b == '5' || b == '6' || b == '7' || b == '8')){
			
	
		if(b == '1')
			x = 7;
		if(b == '2')
			x = 6;
		if(b == '3')
			x = 5;
		if(b == '4')
			x = 4;
		if(b == '5')
			x = 3;
		if(b == '6')
			x = 2;
		if(b == '7')
			x = 1;
		if(b == '8')
			x = 0;

		switch(a){
			case 'A':
			case 'a':
				y = 0;
				break;
			case 'B':
			case 'b':
				y = 1;
				break;
			case 'c':
			case 'C':
				y = 2;
				break;
			case 'd':
			case 'D':
				y = 3;
				break;
			case 'e':
			case 'E':
				y = 4;
				break;
			case 'f':
			case 'F':
				y = 5;
				break;
			case 'g':
			case 'G':
				y = 6;
				break;
			case 'H':
			case 'h':
				y = 7;
				break;
		}
	}
	if(x == -1 || y == -1)
		return false;
	if(board[x][y].getColor() != c)
		return false;
	moves = pMoves(x,y);
	return canMove(moves);

}

bool Board::canMove(std::array<std::array<int,8>,8> a){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(a[i][j] == 1)
				return true;
		}
	}
	return false;
}
void Board::displaySteps(){
	int ch;
	initscr();
	int height = 10, width = 40;
	int x = (20 - height) / 2 + 1;
	int y = (80 - width) / 2 + 1;
	WINDOW *pad = newpad(25,width);
	keypad(stdscr,TRUE);
	cbreak();
	noecho();
	refresh();	
	int pad_pos = 0;
	wprintw(pad,"Press Escape to close!\n");
	wprintw(pad,"Enter a two-digit combo for\nyour piece you want to move.\n");
	wprintw(pad,"Like A8, where A-H, and 1-8");
	do{

		prefresh(pad,pad_pos,0,x,y,10,50);
		ch = getch();
	
		switch(ch){
		}

	}while(ch != 27);

	clear();
	print();
}

void Board::displayMoves(){
	int ch; 
	int height = 10, width = 40;
	int v = (20 - height) / 2 + 1;
	int b = (80 - width) / 2 + 1;
	WINDOW *pad = newpad(20,width+20);
	keypad(stdscr,TRUE);
	cbreak();
	noecho();	
	wprintw(pad,"Press Escape to close!\n");
	wprintw(pad,"Press 'T' for upper left move, 'Y' for up directly, 'U' for upper right\n");
	wprintw(pad,"Press 'G' for left move, 'J' for right move\n");
	wprintw(pad,"Press 'B' for lower left, 'N' for down, 'M' for lower right\n");

	prefresh(pad,0,0,v,b,20,100);
	do{

		ch = getch();
		prefresh(pad,0,0,v,b,20,100);	
		switch(ch){
		}

	}while(ch != 27);
	clear();
	print();

}
