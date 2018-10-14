#include<iostream>
#include<string>
#include<istream>
#include<fstream>
using namespace std;
#include "BiList.h"
#include "Iterator.h"

/*
исключение 1 - некорректный индекс при использовании []
исключение 2 - выход за пределы списка итератора  при использовании ++ -- + -
*/

class STUDENT
{
	friend istream& operator >> (istream& os, STUDENT& S);
	friend ostream& operator << (ostream& os, STUDENT& S);
private:
	string FIO;
	int GroupNumber;
	int assessments[5];//оценки
public:
	STUDENT() {}
	STUDENT(string FIO, int GroupNumber, int assessment[])
	{
		this->FIO = FIO;
		this->GroupNumber = GroupNumber;
		for (int i = 0; i < 5; i++)
			this->assessments[i] = assessment[i]; 
	}
	bool operator < (STUDENT& Second)
	{
		if ((this->GroupNumber) < (Second.GroupNumber))
			return true;
		else
			return false;
	}
	int& operator[](int index)
	{
		if (index > 4 || index < 0)
			throw 1;
		return assessments[index];
	}
	void setName(string s)
	{
		FIO = s;
	}
	void setGroupNumber(int n)
	{
		this->GroupNumber = n;
	}

	float AverageScore()
	{
		int sum = 0;
		for (int i = 0; i < 5; i++)
			sum += assessments[i];
		return sum / 5.;
	}
};

istream& operator >> (istream& os, STUDENT& S)
{
	
	os >> S.FIO >> S.GroupNumber;
	for (int i = 0; i < 5; i++)
		os >> S.assessments[i];
	return os;
}

ostream& operator << (ostream& os, STUDENT& S)
{
	os << S.FIO << '\t' << "Group number: " << S.GroupNumber << '\t' << "Assessment:";
	for (int i = 0; i < 5; i++)
		os << ' ' << S.assessments[i];
	return os;
}
int main()
{
	setlocale(LC_ALL, "Rus");
	BiList<STUDENT> test;

	ifstream file("sotrudniki.txt");
	
	string FIO;
	int otsenki[5];
	while (getline(file, FIO, '$'))
	{
		if (FIO[0] == '\n')
			FIO.erase(0, 1);
		int GroupNumber;
		file >> GroupNumber;
		for (int i = 0; i < 5; i++)
			file >> otsenki[i];
		
		test.PushBack(STUDENT(FIO, GroupNumber, otsenki));
	}

	//Print(test.Begin(), test.End());
	//cout << endl << endl;

	Sort(test.Begin(), test.End());

	Print(test.Begin(), test.End());
	cout << endl << endl;

	Iterator<STUDENT> Iter = test.Begin();

	while(true)
	{
		if (Iter.getData().AverageScore() > 4.0)
			cout << (Iter.getData()) << endl;
		try
		{
			Iter++;
		}
		catch (int i)
		{
			break;
		}
	}

	system("pause");
	return 0;
}