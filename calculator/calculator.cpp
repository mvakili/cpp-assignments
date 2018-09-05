#include <iostream>
#include <cstdlib>
using namespace std;

class Math
{
	private:
		float number;
	public:
		Math(float num);
		float Plus(float nums[],int len);
		float Mines(float nums[],int len);
		float Multi(float nums[],int len);
		float Divide(float num);
};
Math::Math(float num)
{
    number = num;
}
float Math::Plus(float nums[],int len)
{
	float temp_num = number;
	for (int i = 0; i < len; ++i)
	{
		temp_num += nums[i];
	}
	return temp_num;
}
float Math::Mines(float nums[],int len)
{
	float temp_num = number;
	for (int i = 0; i < len; ++i)
	{
		temp_num -= nums[i];
	}
	return temp_num;
}
float Math::Multi(float nums[],int len)
{
	float temp_num = number;
	for (int i = 0; i < len; ++i)
	{
		temp_num *= nums[i];
	}
	return temp_num;
}
float Math::Divide(float num)
{

	return number/num;
}

void Plus(Math a);
void Mines(Math a);
void Multi(Math a);
void Devide(Math a);
int main()
{
    char tempchar;

	do
	{
	    system("CLS");
        float num;
        cout<<"Enter Number: ";
        cin>>num;
        Math a(num);
        int input;
		cout<<"1. Plus"<<endl<<"2. Mines"<<endl<<"3. Multiply"<<endl<<"4. Devide"<<endl;
		cin>>input;
		switch(input)
		{
			case 1:
				Plus(a);
				break;
            case 2:
                Mines(a);
                break;
            case 3:
                Multi(a);
                break;
            case 4:
                Devide(a);
                break;
            default:
                break;
		}
		cout<<"Do you want to continue?(y/n)";

		cin>>tempchar;
	} while (tempchar == 'y');
	return 0;
}
void Plus(Math a){
    int count;
	cout<<"How many numbers? ";
	cin.ignore(1024, '\n');
    cin>>count;
	float *b = new float (count);
	for (int i = 0; i < count; ++i)
	{
		float temp;
		cout<<i+1<<". Number: ";
		cin.ignore(1024, '\n');
		cin>>temp;
		b[i] = temp;
	}
    cout<<"Plus :"<< a.Plus(b,count)<<endl;
    delete [] b;
}
void Mines(Math a){
    int count;
	cout<<"How many numbers? ";
	cin.ignore(1024, '\n');
    cin>>count;
	float *b = new float (count);
	for (int i = 0; i < count; ++i)
	{
		float temp;
		cout<<i+1<<". Number: ";
		cin.ignore(1024, '\n');
		cin>>temp;
		b[i] = temp;
	}
    cout<<"Mines :"<< a.Mines(b,count)<<endl;
    delete [] b;
}
void Multi(Math a){
    int count;
	cout<<"How many numbers? ";
	cin.ignore(1024, '\n');
    cin>>count;
	float *b = new float (count);
	for (int i = 0; i < count; ++i)
	{
		float temp;
		cout<<i+1<<". Number: ";
		cin.ignore(1024, '\n');
		cin>>temp;
		b[i] = temp;
	}
    cout<<"Multiply :"<< a.Multi(b,count)<<endl;
    delete [] b;
}
void Devide(Math a){
    float num;
    cout<<"Enter a number: ";
    cin>>num;
    cout<<"Devision: "<< a.Divide(num)<<endl;
}
