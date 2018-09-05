#include <iostream>
#include <cstdlib>
using namespace std;
const bool WHITE = 0;
const bool BLACK = 1;
const bool HOME = 0;
/*====== Class Patterns =====*/
	class Piece;
	class Board;

/*====== End Class Patterns =====*/
/*====== Class Board =====*/
	class Board
	{
	private:
		Piece* pieces[8][8];
		bool turn;
	public:
		Board();
		Board& importPiece(Piece*,int,int);
		bool isFilled(int,int);
		bool isChecked(bool = WHITE);
		bool move(string);
		bool setEmpty(int _x,int _y) {pieces[_x][_y] = 0;}
		bool takePiece(int _sX,int _sY,int _eX,int _eY){ pieces[_eX][_eY] = pieces[_sX][_sY]; pieces[_sX][_sY] = 0;}
		bool getTurn(){ return turn;}
		Piece& getPiece(int,int);
		~Board();

		/* data */
	};
/*====== End Class Board =====*/

/*====== Class Piece =====*/
	class Piece
	{
	protected:
		bool color;
	public:
		Piece(bool = WHITE);
		void printColor() {cout<<(color ? "b " : "w ");}
		bool getColor() { return color;}
		virtual bool canMove(int,int,int,int,Board*,bool = 0) = 0;
		virtual void print() = 0;
		virtual int getType() = 0;
		~Piece();

		/* data */
	};
/*====== End Class Piece =====*/

/*===== Class Pawn =====*/
	class Pawn: public Piece
	{
	private:
		bool enPassant;
		bool moved;
	public:
		Pawn(bool = WHITE);
		void print() { cout<<"P";printColor();}
		bool canMove(int,int,int,int,Board*,bool = 0);
		int getType() { return 6;}
		~Pawn();

		/* data */
	};
/*====== End Class Pawn =====*/

/*===== Class Rock =====*/
	class Rock: public Piece
	{
	private:
		bool moved;
	public:
		Rock(bool = WHITE);
		void print() { cout<<"R";printColor();}
		bool canMove(int,int,int,int,Board*,bool = 0);
		int getType() { return 5;}
		~Rock();

		/* data */
	};
/*====== End Class Rock =====*/

/*===== Class Knight =====*/
	class Knight: public Piece
	{
	private:
	public:
		Knight(bool = WHITE);
		void print() { cout<<"k";printColor();}
		bool canMove(int,int,int,int,Board*,bool = 0);
		int getType() { return 4;}
		~Knight();

		/* data */
	};
/*====== End Class Knight =====*/

/*===== Class Bishop =====*/
	class Bishop: public Piece
	{
	private:
	public:
		Bishop(bool = WHITE);
		void print() { cout<<"B";printColor();}
		bool canMove(int,int,int,int,Board*,bool = 0);
		int getType() { return 3;}
		~Bishop();

		/* data */
	};
/*====== End Class Bishop =====*/

/*===== Class Queen =====*/
	class Queen: public Piece
	{
	private:
	public:
		Queen(bool = WHITE);
		void print() { cout<<"Q";printColor();}
		bool canMove(int,int,int,int,Board*,bool = 0);
		int getType() { return 2;}
		~Queen();

		/* data */
	};
/*====== End Class Queen =====*/

/*===== Class King =====*/
	class King: public Piece
	{
	private:
		bool moved;
	public:
		King(bool = WHITE);
		bool canMove(int,int,int,int,Board*,bool = 0);
		void print() { cout<<"K";printColor();}
		int getType() { return 1;}
		~King();

		/* data */
	};
/*====== End Class King =====*/

/*====== Board Methods =====*/
	Board::Board()
	{
		turn = HOME;
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				pieces[i][j] = 0;
			}
		}
	}

	Board& Board::importPiece(Piece* _piece,int _x,int _y)
	{
		pieces[_x][_y] = _piece;
		return *this;
	}

	bool Board::isFilled(int _x,int _y)
	{
		return pieces[_x][_y];
	}

	bool Board::isChecked(bool _color)
	{
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				if (isFilled(i,j) && pieces[i][j]->getColor() != _color)
				{
					if(pieces[i][j]->canMove(i,j,0,4,this,1))
					{
						cout<<i<<j;
						int a;
						cin>>a;
						return 1;
					}
						
				}
			}
		}
		return 0;
	}

	bool Board::move(string _move)
	{
		int startX =-1,startY = -1,endX = -1,endY = -1;
		if (_move[0]>=97 && _move[0] <= 122) startY = _move[0] - 'a';
		else if (_move[0]>=65 && _move[0] <= 90) startY = _move[0] - 'A';

		if (_move[2]>=97 && _move[2] <= 122) endY = _move[2] - 'a';
		else if (_move[2]>=65 && _move[2] <= 90) endY = _move[2] - 'A';

		if (_move[1]>= 49 && _move[1] <= 56) startX = _move[1]-'1';
		if (_move[3]>= 49 && _move[3] <= 56) endX = _move[3]-'1';

		if (startX == -1 || startY == -1 || endX == -1 || endY == -1) return 0;
		if (pieces[startX][startY]->getColor() != turn) return 0;

		if (isFilled(startX,startY) && ( (!isFilled(endX,endY)) || (isFilled(endX,endY) && pieces[endX][endY]->getColor() != turn)))
		{
			if (pieces[startX][startY]->canMove(startX,startY,endX,endY,this))
			{
				turn = !turn;
				return 1;
			}
		}
		return 0;
	}

	Piece& Board::getPiece(int _x,int _y)
	{
		return *pieces[_x][_y];
	}


	ostream& operator<<( ostream & _operator, Board _board)
	{
	    for(int i = 7 ;i>= 0;i--)
	    {
	        _operator<<" "<<i+1<<" ";
	        for(int j = 0; j < 8 ;j++)
	        {
	            if (_board.isFilled(i,j))
	            {
	            	_board.getPiece(i,j).print();
	            } else
	            {
	            	_operator<<((i+j)%2 ? "---" : "   ");
	            }
	        }
	        _operator<<endl;
	    }

	    _operator<<"   ";
	    for(int i = 0; i < 8 ;i++)
	        _operator<<" "<<(char) (i + 65)<<" ";
	    _operator<<endl;
	    return _operator;
	}

	Board::~Board()
	{

	}
/*====== End Board Methods =====*/

/*====== Piece Methods =====*/
	Piece::Piece(bool _color)
	{
		color = _color;
	}

	Piece::~Piece()
	{

	}
/*====== End Piece Methods =====*/

/*====== Pawn Methods =====*/
	Pawn::Pawn(bool _color) : Piece(_color)
	{
		enPassant = moved = 0;
	}

	bool Pawn::canMove(int _sX,int _sY,int _eX,int _eY,Board* _board,bool justTest)
	{
		bool correct = 0;
		bool tmpMoved = moved,tmpEnPassant = 0;
		int dX = (_eX >= _sX)? _eX - _sX : _sX - _eX;
		int dY = (_eY >= _sY)? _eY - _sY : _sY - _eY;
		int sX = (_eX >= _sX)? 1 : -1;
		int sY = (_eY >= _sY)? 1 : -1;
		Board tmpBoard = *_board;

		//Move Conditions :
		if (dY == 0)
		{
			if (dX == 1 )
			{
				if (! tmpBoard.isFilled(_eX,_eY)) correct = 1;
			} else if (dX == 2)
				if (moved == 0 && (! tmpBoard.isFilled(_sX + sX,_sY) && ! tmpBoard.isFilled(_eX,_eY)))
				{
					tmpEnPassant = 1;
					correct = 1;
				}
		}
		if (dY == 1 && dX == 1)
		{
			if (tmpBoard.isFilled(_eX,_eY))
			{
				tmpBoard.setEmpty(_eX,_eY);
				correct = 1;
			} else if (tmpBoard.isFilled(_sX,_eY) && tmpBoard.getPiece(_sX,_eY).getColor() != color && tmpBoard.getPiece(_sX,_eY).getType() == 6 && !tmpBoard.isFilled(_eX,_eY))
			{
				tmpBoard.setEmpty(_sX,_eY);
				correct = 1;
			}
		}
		tmpBoard.takePiece(_sX,_sY,_eX,_eY);
		if (!correct) return 0;
		if (justTest) return 1;
		if (tmpBoard.isChecked(color)) return 0;
		
		if (_eX == 7 || _eX == 0)
		{
			int changeTo;
			cout<<"Select One: "<<endl<<"1. Queen"<<endl<<"2. Bishop"<<endl<<"3. Knight"<<endl<<"4. Rock"<<endl;
			cin>>changeTo;
			switch (changeTo)
			{
				case 1:
					tmpBoard.importPiece(new Queen(color),_eX,_eY);
					break;
				case 2:
					tmpBoard.importPiece(new Bishop(color),_eX,_eY);
					break;
				case 3:
					tmpBoard.importPiece(new Knight(color),_eX,_eY);
					break;
				case 4:
					tmpBoard.importPiece(new Rock(color),_eX,_eY);
					break;
				default:
					tmpBoard.importPiece(new Queen(color),_eX,_eY);
					break;
			}
		}
		moved = 1;
		enPassant = tmpEnPassant;
		for (int i = 0; i < 8; ++i)
			for (int j = 0; j < 8; ++j)
				_board->importPiece(&(tmpBoard.getPiece(i,j)),i,j);
		return 1;
	}

	Pawn::~Pawn()
	{

	}
/*====== End Pawn Methods =====*/

/*====== Rock Methods =====*/
	Rock::Rock(bool _color) : Piece(_color)
	{
		moved = 0;
	}

	bool Rock::canMove(int _sX,int _sY,int _eX,int _eY,Board* _board,bool justTest)
	{
		bool correct = 1;
		int dX = (_eX >= _sX)? _eX - _sX : _sX - _eX;
		int dY = (_eY >= _sY)? _eY - _sY : _sY - _eY;
		int sX = (_eX >= _sX)? 1 : -1;
		int sY = (_eY >= _sY)? 1 : -1;
		Board tmpBoard = *_board;

		//Move Conditions :
		if (dY == 0)
		{
			for (int i = _sX + sX; i < _eX; i += sX)
				if (tmpBoard.isFilled(i,_eY))
				{
					return 0;
				}
			/* code */
		}
		else if (dX == 0)
		{
			for (int j = _sY + sY; j < _eY; j += sY)
				if (tmpBoard.isFilled(_eX,j))
				{
					return 0;
				}
			/* code */
		} else return 0;
		cout<<"Rock";
		if (justTest) return 1;
		tmpBoard.takePiece(_sX,_sY,_eX,_eY);

		if (!correct) return 0;

		if (tmpBoard.isChecked(color)) return 0;

		_board->importPiece(&(tmpBoard.getPiece(_sX,_sY)),_sX,_sY);
		_board->importPiece(&(tmpBoard.getPiece(_eX,_eY)),_eX,_eY);
		return 1;
	}

	Rock::~Rock()
	{

	}
/*====== End Rock Methods =====*/

/*====== Knight Methods =====*/
	Knight::Knight(bool _color) : Piece(_color)
	{

	}

	bool Knight::canMove(int _sX,int _sY,int _eX,int _eY,Board* _board,bool justTest)
	{
		bool correct = 0;
		int dX = (_eX >= _sX)? _eX - _sX : _sX - _eX;
		int dY = (_eY >= _sY)? _eY - _sY : _sY - _eY;
		Board tmpBoard = *_board;

		//Move Conditions :
		if (dX && dY && dX+dY == 3)
		{
			correct = 1;
			tmpBoard.takePiece(_sX,_sY,_eX,_eY);
		}
		if (!correct) return 0;
		if (justTest) return 1;
		if (tmpBoard.isChecked(color)) return 0;

		_board->importPiece(&(tmpBoard.getPiece(_sX,_sY)),_sX,_sY);
		_board->importPiece(&(tmpBoard.getPiece(_eX,_eY)),_eX,_eY);

		return 1;
	}

	Knight::~Knight()
	{

	}
/*====== End Knight Methods =====*/

/*====== Bishop Methods =====*/
	Bishop::Bishop(bool _color) : Piece(_color)
	{

	}

	bool Bishop::canMove(int _sX,int _sY,int _eX,int _eY,Board* _board,bool justTest)
	{
		int dX = (_eX >= _sX)? _eX - _sX : _sX - _eX;
		int dY = (_eY >= _sY)? _eY - _sY : _sY - _eY;
		int sX = (_eX >= _sX)? 1 : -1;
		int sY = (_eY >= _sY)? 1 : -1;
		Board tmpBoard = *_board;

		if (dX != dY) return 0;
		for (int i = 1; i + 1 < dX ; i++)
		{
			if (tmpBoard.isFilled(_sX + i * sX,_sY + i * sY))
			{
				return 0;
			}
		}
		if (justTest) return 1;
		tmpBoard.takePiece(_sX,_sY,_eX,_eY);

		if (tmpBoard.isChecked(color)) return 0;

		_board->importPiece(&(tmpBoard.getPiece(_sX,_sY)),_sX,_sY);
		_board->importPiece(&(tmpBoard.getPiece(_eX,_eY)),_eX,_eY);
		return 1;
	}

	Bishop::~Bishop()
	{

	}
/*====== End Bishop Methods =====*/

/*====== Queen Methods =====*/
	Queen::Queen(bool _color) : Piece(_color)
	{

	}

	bool Queen::canMove(int _sX,int _sY,int _eX,int _eY,Board* _board,bool justTest)
	{
		int dX = (_eX >= _sX)? _eX - _sX : _sX - _eX;
		int dY = (_eY >= _sY)? _eY - _sY : _sY - _eY;
		int sX = (_eX >= _sX)? 1 : -1;
		int sY = (_eY >= _sY)? 1 : -1;
		Board tmpBoard = *_board;

		if (dY == 0)
		{
			for (int i = _sX + sX; i < _eX; i += sX)
				if (tmpBoard.isFilled(i,_eY))
				{
					return 0;
				}
			/* code */
		}
		else if (dX == 0)
		{
			for (int j = _sY + sY; j < _eY; j += sY)
				if (tmpBoard.isFilled(_eX,j))
				{
					return 0;
				}
			/* code */
        } 
        else if (dX == dY)
		{
			for (int i = 1; i + 1 < dX ; i++)
			{
				if (tmpBoard.isFilled(_sX + i * sX,_sY + i * sY))
				{
					return 0;
				}
			}
		}
		else return 0;
		if (justTest) return 1;
		tmpBoard.takePiece(_sX,_sY,_eX,_eY);

		if (tmpBoard.isChecked(color)) return 0;

		_board->importPiece(&(tmpBoard.getPiece(_sX,_sY)),_sX,_sY);
		_board->importPiece(&(tmpBoard.getPiece(_eX,_eY)),_eX,_eY);
		return 1;
	}

	Queen::~Queen()
	{

	}
/*====== End Queen Methods =====*/

/*====== King Methods =====*/
	King::King(bool _color) : Piece(_color)
	{
		moved = 0;
	}

	bool King::canMove(int _sX,int _sY,int _eX,int _eY,Board* _board,bool justTest)
	{
		int dX = (_eX >= _sX)? _eX - _sX : _sX - _eX;
		int dY = (_eY >= _sY)? _eY - _sY : _sY - _eY;
		Board tmpBoard = *_board;

		if (!(dX<=1 && dY <=1))
		{
			return 0;
		} else if (1)
		{
			tmpBoard.takePiece(_sX,_sY,_eX,_eY);
		}
		if (justTest) return 1;
		if (tmpBoard.isChecked(color)) return 0;

		_board->importPiece(&(tmpBoard.getPiece(_sX,_sY)),_sX,_sY);
		_board->importPiece(&(tmpBoard.getPiece(_eX,_eY)),_eX,_eY);
		return 0;
	}

	King::~King()
	{

	}
/*====== End King Methods =====*/

/*===== Functions Prototype =====*/
	void insertStandardPieces(Board& );
/*===== End Functions Prototype =====*/

/*===== Main =====*/
	int main()
	{
		Board b1;
		string move,e;
		b1.importPiece(new Pawn,0,0);
		b1.importPiece(new King,0,1);
		insertStandardPieces(b1);
		do
		{
			system("CLS");
			cout<<"Type \"exit\" to Exit Game"<<endl<<endl;
			cout<<b1;
			cout<<(b1.getTurn() == WHITE ? "White" : "Black")<<"'s Turn"<<endl;
			cout<<"Enter Start Position: ";
			cin>>move;
			cout<<"Enter Destination Position: ";
			cin>>e;
			move += e;
			b1.move(move);
		} while (move != "exit");
		return 0;
	}
/*===== End Main =====*/

/*===== Functions =====*/
	void insertStandardPieces(Board& _board)
	{
	    for (int j = 0; j < 8; ++j)
	    {
	        _board.importPiece(new Pawn(HOME),1 ,j)
	            .importPiece(new Pawn(!HOME),6 ,j);
	    }
	        for (int x = 0,color = 0; x <= 7; x += 7, color = 1)
	    {
	        _board.importPiece(new Rock(color),x,0)
	            .importPiece(new Rock(color),x,7)
	            .importPiece(new Knight(color),x,1)
	            .importPiece(new Knight(color),x,6)
	            .importPiece(new Bishop(color),x,2)
	            .importPiece(new Bishop(color),x,5)
	            .importPiece(new Queen(color),x,3)
	            .importPiece(new King(color),x,4);
	    }
	}
/*===== End Functions =====*/
