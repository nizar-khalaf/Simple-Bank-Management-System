#pragma once
#include <iostream> 
#include <string>
#include <cctype>
#include <vector>


using namespace std;


namespace NexaString
{


	string UpperAllString(string S1)
	{

		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = toupper(S1[i]);
		}

		return S1;
	}

	string LowerAllString(string S1)
	{

		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = tolower(S1[i]);
		}

		return S1;
	}

	char InvertLetterCase(char char1)
	{
		return isupper(char1) ? tolower(char1) : toupper(char1);
	}

	short CountLetter(string S1, char Letter, bool MatchCase = true)
	{
		short counter = 0;

		for (short i = 0; i < S1.length(); i++)
		{
			if (MatchCase)
			{
				if (S1[i] == Letter)
				{
					counter++;
				}
			}
			else
			{
				if (tolower(S1[i]) == tolower(Letter))
				{
					counter++;
				}
			}
		}
		return counter;
	}

	vector <string> SplitString(string S1, string Delimi)
	{
		vector <string> vString;

		//cout << "\nYour string words are:\n\n";

		short pos = 0;
		string sWord;

		while ((pos = S1.find(Delimi)) != std::string::npos)
		{
			sWord = S1.substr(0, pos);

			if (sWord != "")
			{
				vString.push_back(sWord);
			}

			S1.erase(0, pos + Delimi.length());
		}

		if (S1 != "")
		{
			vString.push_back(S1);
		}

		return vString;

	}

	string JoinString(vector <string> vString, string Delim)
	{
		string S1 = "";

		for (string& s : vString)
		{
			S1 = S1 + s + Delim;
		}


		return S1.substr(0, S1.length() - Delim.length());
	}


}