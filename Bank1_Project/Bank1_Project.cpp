
#include <iostream> 
#include <string>
#include <cctype>
#include "NexaString.h"
#include <vector>
#include <fstream>
#include <limits>
#include <iomanip>
#include "NexaProcessing.h"


using namespace std;



string ClientsFileName = "Clients.txt";

enum enMainMenueOptions { eShowClientList = 1, 
	                      eAddNewClient = 2, 
	                      eDeletedClient = 3, 
	                      eUpdateClientInfo = 4, 
	                      eFindClient = 5, 
	                      eTransactions = 6, 
	                      eExit = 7 };

enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eMainMenue = 4 };

struct stClientData
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

void ShowMainMenue();

void ShowTransactionsMeneuScreen();

stClientData ConvertLineToRecord(string S1, string Delim = "#//#")
{
	stClientData ClientData;
	vector <string> vClient;

	vClient = NexaString::SplitString(S1, Delim);

	ClientData.AccountNumber = vClient[0];
	ClientData.PinCode = vClient[1];
	ClientData.Name = vClient[2];
	ClientData.Phone = vClient[3];
	ClientData.AccountBalance = stod(vClient[4]);


	return ClientData;

}

string ConvertRecordToLine(stClientData ClientData, string Seperator = "#//#")
{
	string Client = "";

	Client += ClientData.AccountNumber + Seperator;
	Client += ClientData.PinCode + Seperator;
	Client += ClientData.Name + Seperator;
	Client += ClientData.Phone + Seperator;
	Client += to_string(ClientData.AccountBalance);

	return Client;
}

vector <stClientData> LoadClientsDataFromFile(string ClientsFileName)
{
	vector <stClientData> vClients;

	fstream MyFile;
	MyFile.open(ClientsFileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		stClientData Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line, "#//#");

			vClients.push_back(Client);
		}

		MyFile.close();
	}

	return vClients;
}

bool FindClientByAccountNumber(vector <stClientData> vClients, string AccountNumber, stClientData& Client)
{

	for (stClientData& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}

	return false;
}

stClientData ReadNewClient()
{

	vector <stClientData> vClient;
	stClientData ClientData;
	stClientData Client;

	vClient = LoadClientsDataFromFile(ClientsFileName);

	cout << "Enter Account Number: ";
	getline(cin >> ws, ClientData.AccountNumber);

	while (FindClientByAccountNumber(vClient, ClientData.AccountNumber, ClientData))
	{

		cout << "\nClient with [" << ClientData.AccountNumber << "] already exists, Please enter another Account Number? ";
		getline(cin >> ws, ClientData.AccountNumber);

	}

	cout << "Enter PIN Code: ";
	getline(cin, ClientData.PinCode);

	cout << "Enter Your Name: ";
	getline(cin, ClientData.Name);

	cout << "Enter Your Phone: ";
	getline(cin, ClientData.Phone);

	cout << "Enter Your Account Balance: ";
	cin >> ClientData.AccountBalance;

	return ClientData;
}

void PrintClientRecord(stClientData ClientData)
{

	cout << "| " << setw(15) << left << ClientData.AccountNumber;
	cout << "| " << setw(10) << left << ClientData.PinCode;
	cout << "| " << setw(40) << left << ClientData.Name;
	cout << "| " << setw(15) << left << ClientData.Phone;
	cout << "| " << setw(15) << left << ClientData.AccountBalance;
}

void AddClientDataToFile(string ClientsFileName, string stDataLine)
{
	fstream MyFile;


	MyFile.open(ClientsFileName, ios::out | ios::app);

	if (MyFile.is_open())
	{

		MyFile << stDataLine << endl;

		MyFile.close();
	}
}

void AddNewClient()
{
	stClientData ClientData;

	ClientData = ReadNewClient();
	AddClientDataToFile(ClientsFileName, ConvertRecordToLine(ClientData));
}

void AddNewClients()
{

	string AddMore = "yes";

	do
	{

		cout << "Adding New Client:\n\n";

		AddNewClient();

		cout << "\nclient Added Successfully, do you want to add more Clients? Y/N? ";
		cin >> AddMore;

		AddMore = NexaString::LowerAllString(AddMore);


	} while (AddMore == "yes" || AddMore == "y");


}

void AddClientsScreen()
{

	cout << "\n----------------------------------------------------\n";
	cout << "\t\tAdd New Client Screen\n";
	cout << "----------------------------------------------------\n";

	AddNewClients();
}

double HowMenyYouWantToDeposit()
{
	double HowMachDeposit = 0;

	cout << "\nPlease enter Deposit amount? ";
	cin >> HowMachDeposit;

	return HowMachDeposit;
}

double HowMenyYouWantToWithdraw()
{
	double HowMachWithdraw = 0;

	cout << "\nPlease enter Withdraw amount? ";
	cin >> HowMachWithdraw;

	return HowMachWithdraw;
}

void PrintAllClientsData(vector <stClientData> vClients)
{

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client/s.";

	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "PIN Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(15) << "Phone";
	cout << "| " << left << setw(15) << "Account Balance";

	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;

	for (stClientData& vCleint : vClients)
	{
		PrintClientRecord(vCleint);
		cout << endl;
	}

	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;

}

void PrintClientTotalBalancesRecord(stClientData ClientData)
{

	cout << "| " << setw(15) << left << ClientData.AccountNumber;
	cout << "| " << setw(40) << left << ClientData.Name;
	cout << "| " << setw(15) << left << ClientData.AccountBalance;
}

void PrintAllClientsTotalBalances(vector <stClientData> vClients)
{

	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client/s.";

	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(15) << "Account Balance";

	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;

	double TotalBalances = 0;

	if (vClients.size() == 0)
	{
		cout << "\n\t\t\t\tNo Clients Available in the System!" << endl;
	}
	else
	{
		for (stClientData& Cleint : vClients)
		{
			PrintClientTotalBalancesRecord(Cleint);
			TotalBalances += Cleint.AccountBalance;

			cout << endl;
		}
	}

	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;

	cout << "\n\t\t\t\t\tTotal Balances = " << TotalBalances << endl;

}

void PrintClientCard(stClientData Client)
{
	cout << "\n\nThe following are the Client Details:\n";

	cout << "----------------------------------------------------\n";
	cout << "Account Number : " << Client.AccountNumber << endl;
	cout << "PIN Code       : " << Client.PinCode << endl;
	cout << "Name           : " << Client.Name << endl;
	cout << "Phone          : " << Client.Phone << endl;
	cout << "Account Balance: " << Client.AccountBalance << endl;
	cout << "----------------------------------------------------\n";
}

string ReadClientAccountNumber()
{
	string AccountNumber = "";

	cout << "\nPlease enter Account Number? ";
	cin >> AccountNumber;

	return AccountNumber;
}

void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}

void GoBackToTransactionsMenue()
{
	cout << "\n\nPress any key to go back to Transactions Menue...";
	system("pause>0");
	ShowTransactionsMeneuScreen();
}

bool MarkClientForDeleteByAccountNumber(vector <stClientData>& vClients, string AccountNumber)
{

	for (stClientData& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}

	return false;

}

vector <stClientData> SaveClientsDataToFile(string ClientsFileName, vector <stClientData> vClients)
{
	fstream MyFile;
	MyFile.open(ClientsFileName, ios::out);

	string DataLine = "";

	if (MyFile.is_open())
	{
		for (stClientData C : vClients)
		{
			if (C.MarkForDelete == false)
			{

				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;

			}
		}

		MyFile.close();
	}

	return vClients;

}

bool DeleteClientByAccountNumber(string AccountNumber, vector <stClientData>& vClients)
{

	stClientData Client;
	string Answer = "yes";

	if (FindClientByAccountNumber(vClients, AccountNumber, Client))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want delete this Client? Y/N? ";
		cin >> Answer;

		Answer = NexaString::LowerAllString(Answer);

		if (Answer == "y" || Answer == "Yes")
		{
			MarkClientForDeleteByAccountNumber(vClients, AccountNumber);
			SaveClientsDataToFile(ClientsFileName, vClients);

			vClients = LoadClientsDataFromFile(ClientsFileName);

			cout << "\n\nClient Deleted Successfully.";

			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!" << endl;

		return false;
	}
}

stClientData ChangeClientRecord(string AccountNumber)
{
	stClientData Client;

	Client.AccountNumber = AccountNumber;

	cout << "\n\nPlease enter the PIN Code: ";
	getline(cin >> ws, Client.PinCode);

	cout << "Please enter the Name: ";
	getline(cin, Client.Name);

	cout << "Please enter the Phone: ";
	getline(cin, Client.Phone);

	cout << "Please enter Account Balance: ";
	cin >> Client.AccountBalance;

	return Client;
}

bool UpdateClientByAccountNumber(vector <stClientData>& vClients, string AccountNumber)
{
	stClientData Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(vClients, AccountNumber, Client))
	{

		PrintClientCard(Client);

		cout << "\n\nAre you sure you want Update this Client? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{

			for (stClientData& C : vClients)
			{

				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}

			}

			SaveClientsDataToFile(ClientsFileName, vClients);

			cout << "\nClient Update Successfully." << endl;

			return true;

		}
	}
	else
	{

		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!" << endl;

		return false;

	}

}

bool UpdateClientBalance(vector <stClientData>& vClients, string AccountNumber, double Amount)
{
	
	string Answer = "yes";

	cout << "\nAre you sure you want perform this Transaction? Y/N? ";
	cin >> Answer;

	Answer = NexaString::LowerAllString(Answer);

	if (Answer == "y" || Answer == "yes")
	{
		for (stClientData& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;

				cout << "\nDone Successfully, New Balance is: " << C.AccountBalance << ".-" << endl;
				SaveClientsDataToFile(ClientsFileName, vClients);

				return true;
			}
		}
	}
	return false;
}

void ShowDepositScreen()
{
	cout << "\n----------------------------------------------------\n";
	cout << "\t\tDeposit Screen\n";
	cout << "----------------------------------------------------\n";
	
	stClientData Client;

	vector <stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(vClients, AccountNumber, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] dose no exist!" << endl;
		AccountNumber = ReadClientAccountNumber();
	}


	PrintClientCard(Client);
	double Amount = HowMenyYouWantToDeposit();

	UpdateClientBalance(vClients, AccountNumber, Amount);
}

void ShowWithdrawScreen()
{
	cout << "\n----------------------------------------------------\n";
	cout << "\t\tWithdraw Screen\n";
	cout << "----------------------------------------------------\n";

	vector <stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	stClientData Client;

	while (!FindClientByAccountNumber(vClients, AccountNumber, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] dose no exist!" << endl;
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);

	double Amount = HowMenyYouWantToWithdraw();

	while (Amount <= 0 || Amount > Client.AccountBalance)
	{
		cout << "\nPlease enter a valid Amount between 1 and " << Client.AccountBalance << ": ";
		cin >> Amount;
	}  

	UpdateClientBalance(vClients, AccountNumber, Amount * -1);
}

void DeleteClientScreen()
{
	
	cout << "\n----------------------------------------------------\n";
	cout << "\t\tDelete Client Screen\n";
	cout << "----------------------------------------------------\n";

	vector <stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	DeleteClientByAccountNumber(AccountNumber, vClients);

}

void ShowClientListScreen()
{

	vector <stClientData> vClients;

	vClients = LoadClientsDataFromFile(ClientsFileName);
	PrintAllClientsData(vClients);

}

void ShowTotalBalancesScreen()
{

	vector <stClientData> vClients;

	vClients = LoadClientsDataFromFile(ClientsFileName);
	PrintAllClientsTotalBalances(vClients);

}

void UpdateClientScreen()
{

	cout << "\n----------------------------------------------------\n";
	cout << "\t\tUpdate Client Screen\n";
	cout << "----------------------------------------------------\n";

	vector <stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	UpdateClientByAccountNumber(vClients, AccountNumber);

}

void FindClientScreen()
{

	cout << "\n----------------------------------------------------\n";
	cout << "\t\tUpdate Client Screen\n";
	cout << "----------------------------------------------------\n";

	vector <stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	stClientData Client;


	if (FindClientByAccountNumber(vClients, AccountNumber, Client))
	{
		PrintClientCard(Client);
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!" << endl;

	}

}

void ShowEndScreen()
{

	cout << "\n----------------------------------------------------\n";
	cout << "\t\tProgram End :-)\n";
	cout << "----------------------------------------------------\n";

	system("pause>0");
}

short ReadMainMenueOption()
{
	short Choice = 0;
	cout << "Choose wath do you want to do? [1 to 7]? ";
	cin >> Choice;

	return Choice;
}

short ReadTransactionsMenueOption()
{
	short Choice = 0;
	cout << "Choose wath do you want to do? [1 to 4]? ";
	cin >> Choice;

	return Choice;
}

void PerformMainMenueOption(enMainMenueOptions MainMenueOption)
{

	switch (MainMenueOption)
	{
	case enMainMenueOptions::eShowClientList:
	
		system("cls");
		ShowClientListScreen();
		GoBackToMainMenue();
		break;
	
	case enMainMenueOptions::eAddNewClient:
	
		system("cls");
		AddClientsScreen();
		GoBackToMainMenue();
		break;
	
	case enMainMenueOptions::eDeletedClient:
	
		system("cls");
		DeleteClientScreen();
		GoBackToMainMenue();
		break;
	
	case enMainMenueOptions::eUpdateClientInfo:
	
		system("cls");
		UpdateClientScreen();
		GoBackToMainMenue();
		break;
	
	case enMainMenueOptions::eFindClient:
	
		system("cls");
		FindClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eTransactions:
		
		system("cls");
		ShowTransactionsMeneuScreen();
		break;
	
	case enMainMenueOptions::eExit:
	
		system("cls");
		ShowEndScreen();
		break;
	
	}
}

void PerformTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOption)
{
	switch (TransactionsMenueOption)
	{
	case enTransactionsMenueOptions::eDeposit:
		
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionsMenue();
		break;

	case enTransactionsMenueOptions::eWithdraw:
		
		system("cls");
		ShowWithdrawScreen();
		GoBackToTransactionsMenue();
		break;

	case enTransactionsMenueOptions::eTotalBalances:
		
		system("cls");
		ShowTotalBalancesScreen();
		GoBackToTransactionsMenue();
		break;

	case enTransactionsMenueOptions::eMainMenue:
		
		ShowMainMenue();
		break;

	}
}

void ShowTransactionsMeneuScreen()
{
	system("cls");

	cout << "====================================================\n";
	cout << "\t\tTransactions Menue Screen\n";
	cout << "====================================================\n";
	cout << "\t[1] Deposit\n";
	cout << "\t[2] Withdraw\n";
	cout << "\t[3] Total Balances\n";
	cout << "\t[4] Main Menue\n";
	cout << "====================================================\n";

	PerformTransactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}

void ShowMainMenue()
{
	system("cls");

	cout << "====================================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "====================================================\n";
	cout << "\t[1] Show Client List\n";
	cout << "\t[2] Add New Client\n";
	cout << "\t[3] Delete Client\n";
	cout << "\t[4] Update Client Info\n";
	cout << "\t[5] Find Client\n";
	cout << "\t[6] TransActions\n";
	cout << "\t[7] Exit\n";
	cout << "====================================================\n";

	PerformMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

int main()
{

	
	ShowMainMenue();



	return 0;
}