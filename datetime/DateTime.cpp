#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
using namespace std;

/*============= Class DateTime ==============*/
class DateTime
{
public:
	DateTime();
	DateTime(int y = 1,int m = 1,int d = 1,int h = 0,int mn = 0,int s = 0);
	void resetDate(int y = 1,int m = 1,int d = 1);
	void resetTime(int h = 0,int mn = 0,int s = 0);
	double getTimeAsSec();
	double getDateAsDay();
	double getDateTimeAsSec();
	void printDateTime();
	bool isLeapYear();
	bool isLeapYear(int y);
	static double getDistanceAsSecond(DateTime a,DateTime b){
        return a.getDateTimeAsSec() - b.getDateTimeAsSec();
	}

	/*==========*/
	string operator-(DateTime& b);
	string operator+(DateTime& b);
	DateTime& operator+(int d);
	DateTime& operator-(int d);
	DateTime& operator+(double ms);
	DateTime& operator-(double ms);
	bool operator<(DateTime& b);
	bool operator>(DateTime& b);
	bool operator<=(DateTime& b);
	bool operator>=(DateTime& b);
	bool operator==(DateTime& b);
	bool operator!=(DateTime& b);
	string returnString();
	void dateToStandard();

private:
	int year,month,day,hour,min,sec;
	bool isValidTime(int h,int mn,int s);
	bool isValidDate(int y,int m,int d);
	/* data */
};

/*========= DateTime Functions =========*/
/*======================================*/
DateTime::DateTime()
{
	DateTime(1,1,1,0,0,0);
}

/*======================================*/
DateTime::DateTime(int y,int m,int d,int h,int mn,int s)
{
	if (isValidTime(h,mn,s) && isValidDate(y,m,d))
	{
		year = y;
		month = m;
		day = d;
		hour = h;
		min = mn;
		sec = s;
	}
	else DateTime(1,1,1,0,0,0);
}

/*======================================*/
void DateTime::resetDate(int y,int m,int d)
{
	if (isValidDate(y,m,d))
	{
		year = y;
		month = m;
		day = d;
	}
}

/*======================================*/
void DateTime::resetTime(int h,int mn,int s)
{
	if(isValidTime(h,mn,s))
	{
		hour = h;
		min = mn;
		sec = s;
	}
}

/*======================================*/
double DateTime::getTimeAsSec()
{
	return sec + (hour * 60 + min) * 60;
}

/*======================================*/
double DateTime::getDateAsDay()
{
	double d = day;
	d += ((year-1) / 33) * (365 * 25 + 366 * 8);
	for (int i = 1; i < (year-1) % 33; ++i)
	{
		if (isLeapYear(i))
		{
			d += 366;
		} else
		{
			d += 365;
		}
	}
	for (int i = 1; i < month-1; ++i)
	{
		if (i<7)
		{
			d += 31;
		} else
		{
			d += 30;
		}
	}
	return d;
}

/*======================================*/
double DateTime::getDateTimeAsSec()
{
	return getDateAsDay() * (24 * 60 * 60) + getTimeAsSec();
}

/*======================================*/
void DateTime::printDateTime()
{
	cout<<year<<"/"<<month<<"/"<<day<<" "<<hour<<":"<<min<<":"<<sec;
}

/*======================================*/
bool DateTime::isLeapYear()
{
	return isLeapYear(year);
}

/*======================================*/
bool DateTime::isLeapYear(int y)
{
	int i = y % 33;
	return (i == 1 || i == 5 || i == 9 || i == 13 || i == 17 || i == 22 || i == 26 || i == 30);
}


/*======================================*/
bool DateTime::isValidTime(int h,int mn,int s)
{
	return !(h<0 || h>23 || mn<0 || mn>59 || s<0 || s>59);
}

/*======================================*/
bool DateTime::isValidDate(int y,int m,int d)
{
	return !(y<1 || m<1 || m>12 || d<1 || d>31 || (m>7 && d>30) || (m == 12 && d == 30 && isLeapYear(y)));
}

/*======================================*/
string DateTime::operator-(DateTime& b)
{
	sec -= b.getTimeAsSec();
	while (sec < 0)
	{
		sec += 24 * 60 * 60;
		day --;
	}
	min += sec / 60;
	sec = sec % 60;
	hour += min / 60;
	min = min % 60;
	day += hour / 24;
	hour = hour % 24;
	day -= b.day;
	month -= b.month;
	year -= b.year;
	this->dateToStandard();
	return returnString();
}

/*======================================*/
string DateTime::operator+(DateTime& b)
{
	sec += b.getTimeAsSec();
	while (sec < 0)
	{
		sec += 24 * 60 * 60;
		day --;
	}
	min += sec / 60;
	sec = sec % 60;
	hour += min / 60;
	min = min % 60;
	day += hour / 24;
	hour = hour % 24;
	day += b.day;
	month += b.month;
	year += b.year;
	this->dateToStandard();
	return returnString();
}

/*======================================*/
DateTime& DateTime::operator+(int d)
{
	day += d;
	this->dateToStandard();
	return *this;
}

/*======================================*/
DateTime& DateTime::operator-(int d)
{
	day -= d;
	this->dateToStandard();
	return *this;
}

/*======================================*/
DateTime& DateTime::operator+(double ms)
{
	sec +=(int)(ms / 100);
	min += sec / 60;
	sec = sec % 60;
	hour += min / 60;
	min = min % 60;
	day += hour / 24;
	hour = hour % 24;
	this->dateToStandard();
	return *this;
}

/*======================================*/
DateTime& DateTime::operator-(double ms)
{
	sec -=(int)(ms / 100);
	while(sec < 0)
	{
		sec += 60;
		min --;
	}
	while (min < 0)
	{
		min += 60;
		hour --;
	}
	while( hour < 0)
	{
		hour += 24;
		day --;
	}
	this->dateToStandard();
	return *this;
}

/*======================================*/
bool DateTime::operator<(DateTime& b)
{
	return (getDateTimeAsSec()<b.getDateTimeAsSec());
}

/*======================================*/
bool DateTime::operator>(DateTime& b)
{
	return (getDateTimeAsSec()>b.getDateTimeAsSec());
}

/*======================================*/
bool DateTime::operator<=(DateTime& b)
{
	return (getDateTimeAsSec()<=b.getDateTimeAsSec());
}

/*======================================*/
bool DateTime::operator>=(DateTime& b)
{
	return (getDateTimeAsSec()>=b.getDateTimeAsSec());
}

/*======================================*/
bool DateTime::operator==(DateTime& b)
{
	return (getDateTimeAsSec()==b.getDateTimeAsSec());
}

/*======================================*/
bool DateTime::operator!=(DateTime& b)
{
	return (getDateTimeAsSec()!=b.getDateTimeAsSec());
}

/*======================================*/
string DateTime::returnString()
{
	string retVal = "";
	ostringstream convertYear,convertMonth,convertDay,convertHour,convertMin,convertSec;   // stream used for the conversion
    convertYear << year;
	retVal.append(convertYear.str());
	retVal.append("/");

	convertMonth << month;
	retVal.append(convertMonth.str());
	retVal.append("/");

	convertDay << day;
	retVal.append(convertDay.str());
	retVal.append(" ");

	convertHour << hour;
	retVal.append(convertHour.str());
	retVal.append(":");

	convertMin << min;
	retVal.append(convertMin.str());
	retVal.append(":");

	convertSec << sec;
	retVal.append(convertSec.str());
	return retVal;
}

/*======================================*/
void DateTime::dateToStandard()
{
	while (month < 1)
	{
		month += 12;
		year --;
	}
	while (day < 1)
	{
		month --;
		if (month < 1)
		{
			month += 12;
			year --;
		}
		if (month < 7 )
		{
			day += 31;
		} else if (month == 12 && isLeapYear(year))
		{
			day += 29;
		} else if (month >= 7)
		{
			day += 30;
		}
	}


	if (day > 31 || (month >= 7 && day > 30) || (isLeapYear(year + 1) && day > 29))
		{
			if (month < 7)
			{
				day -= 31;
			} else if (month >= 7 && month < 12)
			{
				day -= 30;
			}
			month ++;
			if (month > 12)
			{
				month = 1;
				year ++;
			}
		}

}
/*======================================*/
/*============== Patterns =============*/
void plusDay(DateTime a);
void plusMiliSecond(DateTime a);

/*================ Main ===============*/
int main()
{
	int tY,tM,tD,tH,tMn,tS,input;
	cout<<"Enter Date1:(e: 1392 12 11) ";
	cin>>tY>>tM>>tD;
	cout<<"Enter Time1:(e: 13 42 26) ";
	cin>>tH>>tMn>>tS;
	DateTime a(tY,tM,tD,tH,tMn,tS);

	cout<<"Enter Date2:(e: 1392 12 11) ";
	cin>>tY>>tM>>tD;
	cout<<"Enter Time2:(e: 13 42 26) ";
	cin>>tH>>tMn>>tS;
	DateTime b(tY,tM,tD,tH,tMn,tS);


	do
	{
		cout<<endl<<"Date Time 1  is: ";
		a.printDateTime();
		cout<<endl
        <<"Time As Sec: "<<a.getTimeAsSec()<<endl
		<<"Date As Day: "<<a.getDateAsDay()<<endl
		<<"DateTime As Sec: "<<a.getDateTimeAsSec()<<endl<<endl;


		cout<<endl<<"Date Time 2  is: ";
		b.printDateTime();
		cout<<endl
		<<"Time 2 As Sec: "<<b.getTimeAsSec()<<endl
		<<"Date 2 As Day: "<<b.getDateAsDay()<<endl
		<<"DateTime 2 As Sec: "<<b.getDateTimeAsSec()<<endl<<endl;


		a.printDateTime();
		cout<<" < ";
		b.printDateTime();
		cout<<(a<b ? "true" : "false")<<endl;

		a.printDateTime();
		cout<<" > ";
		b.printDateTime();
		cout<<(a>b ? "true" : "false")<<endl;

		a.printDateTime();
		cout<<" <= ";
		b.printDateTime();
		cout<<(a<=b ? "true" : "false")<<endl;

		a.printDateTime();
		cout<<" >= ";
		b.printDateTime();
		cout<<(a>=b ? "true" : "false")<<endl;

		a.printDateTime();
		cout<<" == ";
		b.printDateTime();
		cout<<(a==b ? "true" : "false")<<endl;

		a.printDateTime();
		cout<<" != ";
		b.printDateTime();
		cout<<(a!=b ? "true" : "false")<<endl;

		DateTime c = a;
		c.printDateTime();
		cout<<" - ";
		b.printDateTime();
		c-b;
		cout<<" = "<<c.returnString();
		cout<<endl;

		c = a;
		c.printDateTime();
		cout<<" + ";
		b.printDateTime();
		c+b;
		cout<<" = "<<c.returnString();
		cout<<endl;

		cout<<"Distance between ";
		a.printDateTime();
		cout<<" And ";
		b.printDateTime();
		cout<<" Is "<<DateTime::getDistanceAsSecond(a,b)<<" Seconds :)"<<endl;
        cout<<endl<<"1. Plus Day"<<endl
		<<"2.Plus Milisecond"<<endl
		<<"0. Exit"<<endl;


		cin>>input;
		switch(input)
		{
			case 0:
				break;
			case 1:
				plusDay(a);
				break;
			case 2:
				plusMiliSecond(a);
				break;
		}
	} while (!(input < 1 || input > 3));

}

/*============= Functions =============*/
void plusDay(DateTime a)
{
	int d;
	cout<<"Enter Date As Day: ";
	cin>>d;
	DateTime c = a;
	c.printDateTime();
	cout<<" + "<<d<<" = ";
	c + d;
	c.printDateTime();
		cout<<endl;
	a.printDateTime();
	cout<<" - "<<d<<" = ";
	a - d;
	a.printDateTime();

	cout<<endl;
	int pause;
	cin>>pause;
}

/*======================================*/
void plusMiliSecond(DateTime a)
{
	double ms;
	cout<<"Enter Time As Mili Second: ";
	cin>>ms;
	DateTime c = a;
	c.printDateTime();
	cout<<" + "<<ms<<" = ";
	c + ms;
	c.printDateTime();
		cout<<endl;
	a.printDateTime();
	cout<<" - "<<ms<<" = ";
	a - ms;
	a.printDateTime();

	cout<<endl;
	int pause;
	cin>>pause;
}
