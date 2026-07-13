#pragma once


#include <iostream>
#include <string>
using namespace std;


namespace NexaInput
{

	int ReadIntFromUser(string message)
	{
		int Number = 0;

		cout << message << endl;
		cin >> Number;

		while (cin.fail())
		{

			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Invalid Number, Enter Again:\n";
			cin >> Number;

		}
		return Number;
	}

	string ReadStringFromUser(string message)
	{
		string Text = "";

		cout << message << endl;
		getline(cin, Text);

		return Text;
	}

	float ReadFloatFromUser(string message)
	{
		float Number = 0;

		cout << message << endl;
		cin >> Number;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Invalid Number, Enter Again:\n";
			cin >> Number;

		}
		return Number;

	}

	double ReadDoubleFromUser(string message)
	{
		double Number = 0;

		cout << message << endl;
		cin >> Number;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Invalid Number, Enter Again:\n";
			cin >> Number;

		}
		return Number;

	}

	void ClearInputBuffer()
	{
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	int ReadPositiveNumber(string Message)
	{
		int Number = 0;

		cout << Message << endl;
		cin >> Number;

		while (cin.fail() || Number <= 0)
		{

			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Please enter a Positive Number:\n";
			cin >> Number;

		}
		return Number;
	}

	int ReadNumberInRange(int From, int To, string Message)
	{
		int Number = 0;

		do
		{
			Number = ReadIntFromUser(Message);

		} while (Number < From || Number > To);

		return Number;
	}

}