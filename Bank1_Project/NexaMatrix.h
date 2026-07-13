#pragma once

#include <iostream> 
#include <iomanip>



using namespace std;

namespace NexaMatrix
{

	void PrintMatrix(int arr[3][3], short Rows, short Coloms)
	{
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Coloms; j++)
			{
				cout << left << setw(3) << arr[i][j] << "\t";
			}

			cout << endl;
		}
	}
}
