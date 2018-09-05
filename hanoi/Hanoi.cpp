#include <iostream>
#include <cstdlib>

using namespace std;

class Bar
{
private:
	int levelWidth[5];
public:
	Bar()
	{
		for (int i = 0; i <= 4; ++i)
		{
			levelWidth[i] = 0;
		}
	}
	bool addNut(int _width)
	{
		if (_width == 0)
		{
			return 0;
		}
		for (int i = 0; i < 4; ++i)
		{
			if (levelWidth[i] == 0)
			{
				levelWidth[i] = _width;
				return 1;
			}
			if (levelWidth[i] > _width)
			{
				continue;
			}
			if (levelWidth[i] <= _width)
			{
				return 0;
			}
		}
	}
	void removeNut()
	{
		for (int i = 3; i >=0; i--)
		{
			if (levelWidth[i] != 0)
			{
				levelWidth[i] = 0;
				return ;
			}
		}
	}
	int getNut()
	{
		for (int i = 3; i >= 0 ; i--)
		{
			if (levelWidth[i] != 0)
			{
				return levelWidth[i];
			}
		}
		return 0;
	}
	void printBar()
	{
		for (int i = 4; i >= -1; i--)
		{
			cout<<"   ";
			if (i == -1)
			{
				cout<<"========="<<endl;
				break;
			}
			if (levelWidth[i] == 0)
			{
				cout<<"    |"<<endl;
			}
			if (levelWidth[i] > 0)
			{
				for (int j = 0; j <= 4-levelWidth[i]; ++j)
				{
					cout<<" ";
				}
				for (int j = 0; j < (levelWidth[i] * 2 -1); ++j)
				{
					cout<<"*";
				}
				cout<<endl;
			}

		}
	}
	/* data */
};

int main()
{
	string move;
	int start,end;
	Bar bars[3];
	bars[0].addNut(4);
	bars[0].addNut(3);
	bars[0].addNut(2);
	do
	{
		cout<<"For Exit : 0"<<endl;
		cout<<"Bar Number 1:"<<endl;
		bars[0].printBar();
		cout<<endl;
		cout<<"Bar Number 2:"<<endl;
		bars[1].printBar();
		cout<<endl;
		cout<<"Bar Number 3:"<<endl;
		bars[2].printBar();
		cout<<"Please Type Move:(e: 1>3) ";
		cin>>move;
		start = move[0] - 49;
		end = move[2] - 49;
		if (start == end +2 || end == start +2) continue;
		if (bars[end].addNut(bars[start].getNut()))
		{
			bars[start].removeNut();
		}

	} while (move != "0");

	return 0;
}

