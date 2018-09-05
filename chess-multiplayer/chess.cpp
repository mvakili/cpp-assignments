#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "tcp_client.h"
#include "tcp_server.h"
using namespace std;

#ifndef WHITE
#define WHITE 1
#endif

#ifndef BLACK
#define BLACK 0
#endif
/*==== Class Prototypes ====*/
class Position;
class Piece;
class Board;

/*==== End Class Prototypes ====*/

/**
	TCP Client class
*/

/*==== Class Piece ====*/
class Piece
{
private:
	Position* position;
	int pieceType;
	bool home;
	int moveCount;
	vector<Position>* positions;
	bool pawnIsMoveCorrect(Position &p);
	bool rockIsMoveCorrect(Position &p);
	bool knightIsMoveCorrect(Position &p);
	bool bishopISMoveCorrect(Position &p);
	bool queenIsMoveCorrect(Position &p);
	bool kingIsMoveCorrect(Position &p);
public:
	Piece();
	Piece(int _pieceType,bool _home);
	int getPieceType();
	bool isMoveCorrect(Position &p);
	string getPieceName();
	Position* getPosition();
	bool getTurn();
	void plusMoveCount();
	int getMoveCount();
	void setPositions(vector<Position>* v);
	void setPosition(Position *_position);
	/* data */
};

/*==== End Class Piece ====*/

/*==== Class Position ====*/
class Position
{
private:
	Piece* reservePiece;
	int x,y;
	bool filled;
	Piece* piece;
	vector<Position>* positions;
public:
	Position(){};
	Position(int _x,int _y);
	Position(string a);
	void setPosition(int _x,int _y);
	void setPosition(string a);
	Piece* getReservePiece();
	void setReservePiece(Piece* _piece);
	int getX();
	int getY();
	void setEmpty();
	void setFilled();
	void setPiece(Piece *_piece);
	void setPositions(vector<Position>* v);
	bool isFilled();
	bool isMoveCorrect(Position &p2);
	void move(Position &p2);
	void testMove(Position &p2);
	string getPositionAsString();
	Piece* getPiece();
	void printPosition();
	bool operator ==(Position p);
	/* data */
};

/*==== End Class Position ====*/

/*==== Class Board ====*/
class Board
{
private:
	vector<Position> positions;
	bool turn;
	string log;
public:
	Board();
	void printPositions();
	void printBoard();
	bool getTurn();
	string getTurnAsString();
	string getLog();
	void move(Position p1,Position p2);
	/* data */
};

/*==== End Class Board ====*/



/*===============*/
Piece::Piece()
{

}

/*===============*/
Piece::Piece(int _pieceType,bool _home)
{
	pieceType = _pieceType;
	home = _home;
	moveCount = 0;
}

/*===============*/
int Piece::getPieceType()
{
	return pieceType;
}

/*===============*/
bool Piece::isMoveCorrect(Position &p)
{

	if(p.isFilled() && p.getPiece()->getTurn() == getTurn())
	{
		return 0;
	}
	switch (pieceType)
	{
		case 1:
			return kingIsMoveCorrect(p);
		case 2:
			return queenIsMoveCorrect(p);
		case 3:
			return bishopISMoveCorrect(p);
		case 4:
			return knightIsMoveCorrect(p);
		case 5:
			return rockIsMoveCorrect(p);
		case 6:
			return pawnIsMoveCorrect(p);
		default:
			return 0;
	}
}

/*===============*/
bool Piece::pawnIsMoveCorrect(Position &p)
{
	int _x,_y;
	_x = position->getX() - p.getX();
	_y = position->getY() - p.getY();
	_x = (_x < 0) ? -_x : _x;
	_y = (_y < 0) ? - _y : _y;
	int pX,pY;
	pX = (p.getX() > position->getX()) ? 1 : -1;
	pY = (p.getY() > position->getY()) ? 1 : -1;
	if (_y == 0 )
	{
		if (_x == 1)
		{
			return 1;
		}
		if (_x == 2 && moveCount == 0 && positions->at((position->getX() - 1 + pX) * 8 + p.getY() - 1).isFilled() == 0)
		{
			return 1;
		}
		return 0;
	}
	if (_y == 1 && _x == 1 && p.isFilled() && p.getPiece()->getTurn() != getTurn())
	{
		return 1;
	}
	return 0;
}

/*===============*/
bool Piece::rockIsMoveCorrect(Position &p)
{
	int _x,_y;
	_x = position->getX() - p.getX();
	_y = position->getY() - p.getY();
	if (_x != 0 && _y != 0)
	{
		return 0;
	}
	int pX,pY;
	pX = (p.getX() > position->getX()) ? 1 : -1;
	pY = (p.getY() > position->getY()) ? 1 : -1;
	if (_x != 0)
	{
		for (int i = position->getX() - 1 + pX; i != p.getX() - 1 ; i+= pX)
		{
			if (positions->at(i * 8 + p.getY() - 1).isFilled())
			{
				return 0;
			}
		}
	}
	if (_y != 0)
	{
		for (int j = position->getY() - 1 + pY; j != p.getY() - 1 ; j+= pY)
		{
			if (positions->at((p.getX() - 1) * 8 + j).isFilled())
			{
				return 0;
			}
		}
	}
	return 1;
}

/*===============*/
bool Piece::knightIsMoveCorrect(Position &p)
{
	int _x,_y;
	_x = position->getX() - p.getX();
	_y = position->getY() - p.getY();
	_x = (_x < 0) ? -_x : _x;
	_y = (_y < 0) ? - _y : _y;
	return ( _x != 0 && _y != 0 && _x + _y == 3);
}

/*===============*/
bool Piece::bishopISMoveCorrect(Position &p)
{
	int _x,_y;
	_x = position->getX() - p.getX();
	_y = position->getY() - p.getY();
	_x = (_x < 0) ? -_x : _x;
	_y = (_y < 0) ? - _y : _y;
	if (_x != _y)
	{
		return 0;
	}
	int pX,pY;
	pX = (p.getX() > position->getX()) ? 1 : -1;
	pY = (p.getY() > position->getY()) ? 1 : -1;
	for (int i = position->getX() - 1 + pX , j = position->getY() - 1 + pY; i != p.getX() - 1 ; i += pX, j += pY )
	{
		if (positions->at(i * 8 + j).isFilled())
		{
			return 0;
		}
	}
	return 1;
}

/*===============*/
bool Piece::queenIsMoveCorrect(Position &p)
{
	return ( rockIsMoveCorrect(p) || bishopISMoveCorrect(p));
}

/*===============*/
bool Piece::kingIsMoveCorrect(Position &p)
{
	int _x,_y;
	_x = position->getX() - p.getX();
	_y = position->getY() - p.getY();
	_x = (_x < 0) ? -_x : _x;
	_y = (_y < 0) ? - _y : _y;
	return ( _x <= 1 && _y <= 1);
}

/*===============*/
string Piece::getPieceName()
{
	string tmp;
	switch (pieceType)
	{
		case 1:
			tmp = " K";
			break;
		case 2:
			tmp = " q";
			break;
		case 3:
			tmp = " b";
			break;
		case 4:
			tmp = " k";
			break;
		case 5:
			tmp = " r";
			break;
		case 6:
			tmp = " p";
			break;
		default:
			abort();
	}
	tmp += (home) ? "w" : "b";
	return tmp;
}

/*===============*/
Position* Piece::getPosition()
{
	return position;
}

/*===============*/
bool Piece::getTurn()
{
	return home;
}

/*===============*/
void Piece::plusMoveCount()
{
	moveCount ++;
}

/*===============*/
int Piece::getMoveCount()
{
	return moveCount;
}

/*===============*/
void Piece::setPositions(vector<Position>* v)
{
	positions = v;
}

/*===============*/
void Piece::setPosition(Position *_position)
{
	position = _position;
}

/*===============*/
Position::Position(int _x,int _y)
{
	setPosition(_x,_y);
	filled = 0;
}

/*===============*/
Position::Position(string a)
{
	setPosition(a);
}

/*===============*/
void Position::setPosition(string a)
{
	int _x,_y;
	if (a[0]>=97 && a[0] <= 122)
	{
		_x = a[0] - 96;
	} else if (a[0]>=65 && a[0] <= 90)
	{
		_x = a[0] - 64;
	} else
	{
		abort();
	}
	setPosition(_x,a[1]-48);
}

/*===============*/
void Position::setPosition(int _x,int _y)
{
	x = _x;
	y = _y;
}

/*===============*/
Piece* Position::getReservePiece()
{
	return reservePiece;
}

/*===============*/
void Position::setReservePiece(Piece* _piece)
{
	reservePiece = _piece;
}
/*===============*/
void Position::setEmpty()
{
	filled = 0;
}

/*===============*/
void Position::setFilled()
{
	filled = 1;
}

/*===============*/
int Position::getX()
{
	return x;
}

/*===============*/
int Position::getY()
{
	return y;
}

/*===============*/
void Position::setPiece(Piece *_piece)
{
	piece = _piece;
	filled = 1;
	_piece->setPosition(this);
	_piece->setPositions(positions);
}

/*===============*/
void Position::setPositions(vector<Position>* v)
{
	positions = v;
}

/*===============*/
bool Position::isFilled()
{
	return filled;
}

/*===============*/
bool Position::isMoveCorrect(Position &p2)
{
	if (filled)
	{
		if (piece->isMoveCorrect(p2))
		{
			bool k = 1;
			if (p2.isFilled())
			{
				p2.setReservePiece(p2.getPiece());
				k = 0;
			}
			move(p2);
			for (int i = 0; i < positions->size(); ++i)
			{
				if (positions->at(i).isFilled() && positions->at(i).getPiece()->getPieceType() == 1 && positions->at(i).getPiece()->getTurn() == getPiece()->getTurn())
				{
					for (int j = 0; j < positions->size(); ++j)
					{
						if (positions->at(j).isFilled() && positions->at(j).getPiece()->isMoveCorrect(positions->at(i)))
						{
							p2.testMove(*this);
							if (k == 0)
							{
								p2.setFilled();
								p2.setPiece(p2.getReservePiece());
							}
							setFilled();
							return 0;
						}
					}
					break;
				}
			}
			p2.testMove(*this);
			if (k == 0)
			{
				p2.setFilled();
				p2.setPiece(p2.getReservePiece());
			}
			setFilled();
			return 1;
		}
	}
	return 0;
}

/*===============*/
void Position::move(Position &p2)
{
		p2.setPiece(piece);
		piece->plusMoveCount();
		setEmpty();
}

/*===============*/
void Position::testMove(Position &p2)
{
		p2.setPiece(piece);
		setEmpty();
}
/*===============*/
string Position::getPositionAsString()
{
	string a;
	a = (char)(x+64);
	a +=(char)(y+48);
	return a;
}

/*===============*/
Piece* Position::getPiece()
{
	return piece;
}

/*===============*/
void Position::printPosition()
{
	if (filled)
	{
		cout<<piece->getPieceName();
	} else if ((x + y) % 2 == 0)
	{
		cout<<"'  ";
	}else
	{
		cout<<"   ";
	}
}

/*===============*/
bool Position::operator ==(Position p)
{
	return (x == p.getX() && y == p.getY());
}

/*===============*/
Board::Board()
{
	turn = WHITE;//1 for Home , 0 for Away
	log = "";
	for (int x = 1; x <= 8; ++x)
	{
		for (int y = 1; y <= 8; ++y)
		{
			Position temp(x,y);
			positions.push_back(temp);
		}
	}
	for (int i = 0; i < positions.size(); ++i)
	{
		positions[i].setPositions(&positions);
	}
	for (int i = 0; i<= 1; i++)
	{
		Piece* tmp = new Piece(5,!i);
		positions[0 + i * 8 * 7].setPiece(tmp);
		tmp = new Piece(4,!i);
		positions[1 + i * 8 * 7].setPiece(tmp);
		tmp = new Piece(3,!i);
		positions[2 + i * 8 * 7].setPiece(tmp);
		tmp = new Piece(2,!i);
		positions[3 + i * 8 * 7].setPiece(tmp);
		tmp = new Piece(1,!i);
		positions[4 + i * 8 * 7].setPiece(tmp);
		tmp = new Piece(3,!i);
		positions[5 + i * 8 * 7].setPiece(tmp);
		tmp = new Piece(4,!i);
		positions[6 + i * 8 * 7].setPiece(tmp);
		tmp = new Piece(5,!i);
		positions[7 + i * 8 * 7].setPiece(tmp);
		for (int j = 8; j <= 15; ++j)
		{
			tmp = new Piece(6,!i);
			positions[j + i * 8 * 5].setPiece(tmp);
		}
	}
}

/*===============*/
void Board::printPositions()
{

}

/*===============*/
void Board::printBoard()
{
	cout<<" ";
	for (int i = 1; i <= 8; ++i)
	{
		cout<<" "<<i<<" ";
	}
	for (int i = 0; i < positions.size(); ++i)
	{
		if (i % 8 == 0)
		{
			cout<<endl;
			cout<<(char)(i/8 +65)<<" ";
		}
		positions.at(i).printPosition();
	}
}

/*===============*/
bool Board::getTurn()
{
	return turn;
}

/*===============*/
string Board::getTurnAsString()
{
	string a;
	a = (turn == WHITE)? "White" : "Black";
	return a;
}

/*===============*/
string Board::getLog()
{
	return log;
}

/*===============*/
void Board::move(Position p1,Position p2)
{
	int first = -1,second = -1;
	for (int i = 0; i < positions.size(); ++i)
	{
		if (positions[i] == p1)
		{
			first = i;
			break;
		}
	}
	for (int i = 0; i < positions.size(); ++i)
	{
		if (positions[i] == p2)
		{
			second = i;
			break;
		}
	}
	if (first == -1 || second == -1)
	{
		return;
	}
	if (turn == positions[first].getPiece()->getTurn())
	{
		if (positions[first].isMoveCorrect(positions[second]))
		{
			positions[first].move(positions[second]);
			turn = !turn;
			log += positions[first].getPositionAsString() + " > " + positions[second].getPositionAsString() + "\n";
		}
	}
}


/*====== Functions =====*/
void play_single();
void play_as_server();
void play_as_client();
/*===== End Functions =====*/

/*===============*/
int main(int argc, char const *argv[])
{
	string input;
	do {
		cout<<"1. Single Play"<<endl
			<<"2. Multi play"<<endl
			<<endl<<"0. Exit"<<endl;
		cin>>input;

		if(input == "1") play_single();
		else if(input == "2")
		{
			do {

				cout<<"1. Create game"<<endl
					<<"2. Join game"<<endl
					<<endl<<"0. Back"<<endl;
				cin>>input;

				if(input == "1") play_as_server();
				else if (input == "2") play_as_client();
			} while (input != "0");
			input = "";
		}
	} while (input != "0");
}


void play_single()
{
	Board b1;
	do
	{
		b1.printBoard();
		string a;
		cout<<endl<<endl<<b1.getTurnAsString()<<"'s Turn";
		cout<<endl<<"Enter Start Position: ";
		cin>>a;
		Position s(a);
		cout<<"Enter End Position: ";
		cin>>a;
		Position e(a);
		b1.move(s,e);
	} while (1);
}

void play_as_server()
{
	int port;
	tcp_server* ser = new tcp_server();
	cout<<"Enter Port Number: ";
	cin>>port;

	bool me = WHITE;

	if(! ser->create_socket(port))
	{
		cout<<"An error accured :("<<endl;
	} else {
		cout<<"Waiting for client join"<<endl;
		if (ser->accept_tcp())
		{
			Board b1;
			do
			{
				b1.printBoard();
				string a, b;
				cout<<endl<<endl<<b1.getTurnAsString()<<"'s Turn"<<endl;
				if (b1.getTurn() != me)
				{
					cout<<"Waiting for Client Move..."<<endl;
					a = ser->listen_tcp();
					Position s(a);
					
					b = ser->listen_tcp();
					Position e(b);
					cout<<"Client Moved: "<<a<<" > "<< b<<endl;
					b1.move(s,e);
				} else {
					cout<<endl<<"Enter Start Position: ";
					cin>>a;
					if (!ser->write_tcp(a)) continue;
					Position s(a);
					cout<<"Enter End Position: ";
					cin>>b;
					if (!ser->write_tcp(b)) continue;
					Position e(b);
					b1.move(s,e);
				}
			} while (1);
		}
	}

}

void play_as_client()
{
	int port;
	string host;
	tcp_client* cli = new tcp_client();
	cout<<"Enter Host Address: ";
	cin>>host;
	cout<<"Enter Port Number: ";
	cin>>port;

	bool me = BLACK;

	if(! cli->conn(host, port))
	{
		cout<<"An error accured :("<<endl;
	} else {
		Board b1;
		do
		{
			b1.printBoard();
			string a, b;
			cout<<endl<<endl<<b1.getTurnAsString()<<"'s Turn"<<endl;
			if (b1.getTurn() != me)
			{
				cout<<"Waiting for Server Move..."<<endl;
				a = cli->receive();
				Position s(a);
				
				b = cli->receive();
				Position e(b);
				cout<<"Server Moved: "<<a<<" > "<< b<<endl;
				b1.move(s,e);
			} else {
				cout<<endl<<"Enter Start Position: ";
				cin>>a;
				if (!cli->send_data(a)) continue;
				Position s(a);
				cout<<"Enter End Position: ";
				cin>>b;
				if (!cli->send_data(b)) continue;
				Position e(b);
				b1.move(s,e);
			}
		} while (1);
	}

}

