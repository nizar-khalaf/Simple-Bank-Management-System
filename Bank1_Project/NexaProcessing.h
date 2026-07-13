#pragma once


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "NexaInput.h"


using namespace std;


namespace NexaRandom_Functions
{

	int RandomNumber(int from, int to)
	{
		return rand() % (to - from + 1) + from;
	}

	char GetRandomCharacter(char From, char To)
	{
		return char(RandomNumber(From, To));
	}

	string GenerateWord(short int Length)
	{
		string word = "";

		for (int i = 1; i <= Length; i++)
		{
			word = word + GetRandomCharacter('A', 'Z');
		}
		return word;
	}

	string GenerateKey(short int Groups, short int WordLength)  //Groups = Key Length
	{

		string Key = "";

		for (short int i = 1; i <= Groups; i++)
		{
			Key = Key + GenerateWord(WordLength);


			if (i < Groups)
			{
				Key = Key + "-";
			}

		}

		return Key;
	}

	void GenerateKeys(short int NumberOfKeys)
	{
		for (int i = 1; i <= NumberOfKeys; i++)
		{
			cout << "Key [" << i << "] : ";
			cout << GenerateKey(4, 4) << endl;
		}

	}

}



namespace NexaMath_Functions
{

	enum enOddOrEven { Odd = 1, Even = 2};

	enum enPrimeNotPrime { Prime = 1, NotPrime = 2 };

	enOddOrEven CheckOddOrEven(int Number)
	{
		if (Number % 2 != 0)
		{
			return enOddOrEven::Odd;
		}
		else
		{
			return enOddOrEven::Even;
		}
	}

	int Factorial(int Number)
	{
		int factorial = 1;

		for (int Counter = Number; Counter >= 1; Counter--)
		{
			factorial *= Counter;
		}

		return factorial;
	}

	enPrimeNotPrime CheckPrime(int Number)
	{

		int M = round(Number / 2);


		for (int Counter = 2; Counter <= M; Counter++)
		{

			if (Number % Counter == 0)
				return enPrimeNotPrime::NotPrime;

		}

		return enPrimeNotPrime::Prime;
	
	}

	int ReverseNumber(int Number)
	{

		int Remainder = 0, Number2 = 0;

		while (Number > 0)
		{
			Remainder = Number % 10;
			Number = Number / 10;
			Number2 = Number2 * 10 + Remainder;
		}

		return Number2;
	}

	bool IsPalindromeNumber(int Number)
	{
		return Number == ReverseNumber(Number);
	}


}



namespace NexaTable_Functions
{

	void PrintTableHeader()
	{
		cout << "|--------------------|---------------|--------------------------------|---------------|---------------|" << endl;
		cout << "|Account Number      |PIN Code       |Client Name                     |Phone          |Balance        |" << endl;
		cout << "|--------------------|---------------|--------------------------------|---------------|---------------|" << endl;
	}

	void PrintTable(string AccountNumber, string PINcode, string ClientName, string Phone, double Balance)
	{
		cout << "|"
			 << left << setw(20) << AccountNumber
			 << "|"
			 << left << setw(15) << PINcode
			 << "|"
			 << left << setw(32) << ClientName
			 << "|"
			 << left << setw(15) << Phone
			 << "|"
			 << left << setw(15) << Balance
			 << "|" << endl;
	}

	void PrintTableFooter()
	{
		cout << "|--------------------|---------------|--------------------------------|---------------|---------------|" << endl;
	}

}



namespace NexaSwap_Functions
{
	void Swap(int& Number1, int& Number2)
	{
		int temp;

		temp = Number1;
		Number1 = Number2;
		Number2 = temp;
	}

	void SwapIfGreater(int& Number1, int& Number2)
	{
		if (Number1 > Number2)
		{
			Swap(Number1, Number2);
		}
	}
}

