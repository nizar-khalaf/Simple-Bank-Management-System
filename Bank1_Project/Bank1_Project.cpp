
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


string UsersFileName = "Users.txt";
string ClientsFileName = "Clients.example.txt";

enum enMainMenueOptions { eShowClientList = 1, 
	                      eAddNewClient = 2, 
	                      eDeletedClient = 3, 
	                      eUpdateClientInfo = 4, 
	                      eFindClient = 5, 
	                      eTransactions = 6,
						  eManageUsers = 7,
	                      eLogout = 8 };

enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eMainMenue = 4 };

enum enManageUsersMenueOptions { eShowUsersList = 1, eAddNewUser = 2, eDeletedUser = 3, eUpdateUserInfo = 4, eFindUser = 5, enMainMenue = 6 };

enum enMainMenuPermissions { pShowClientList = 1,
	                         pAddNewClient = 2, 
	                         pDeleteClient = 4, 
	                         pUpdateClientInfo = 8, 
	                         pFindClient = 16, 
	                         pTransactions = 32, 
	                         pManageUsers = 64, 
	                         pFullAccess = -1 };

struct stClientData
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

struct stUserData
{
	string UserName;
	string Password;
	int Permissions;
	bool MarkForDelete = false;
};


stUserData CurrentUser;


void ShowMainMenue();
void ShowManageUsersScreen();
void ShowTransactionsMeneuScreen();
void LoginScreen();
void GoBackToManageUsersMenue();
void GoBackToMainMenue();


string ConvertUserRecordToLine(stUserData UserData, string Seperator = "#//#")
{
	string User = "";
	User += UserData.UserName + Seperator;
	User += UserData.Password + Seperator;
	User += to_string(UserData.Permissions);
	return User;
}

stUserData ConvertLineToUserRecord(string S1, string Delim = "#//#")
{
	stUserData UserData;
	vector <string> vUser;

	vUser = NexaString::SplitString(S1, Delim);

	UserData.UserName = vUser[0];
	UserData.Password = vUser[1];
	UserData.Permissions = stoi(vUser[2]);

	return UserData;
}

vector <stUserData> LoadUsersDataFromFile(string UsersFileName)
{
	vector <stUserData> vUsers;
	fstream MyFile;

	MyFile.open(UsersFileName, ios::in);  //Read Mode

	if (MyFile.is_open())
	{
		string Line;
		stUserData User;

		while (getline(MyFile, Line))
		{
			User = ConvertLineToUserRecord(Line, "#//#");
			vUsers.push_back(User);
		}

		MyFile.close();
	}
	return vUsers;
}

bool FindUserByUserName(vector <stUserData> vUsers, string UserName, stUserData& User)
{
	for (stUserData& U : vUsers)
	{
		if (U.UserName == UserName)
		{
			User = U;
			return true;
		}
	}
	return false;
}

bool FindUserByUserNameAndPassword(string UserName, string Password, stUserData& CurrentUser)
{

	vector <stUserData> vUsers = LoadUsersDataFromFile(UsersFileName);

	for (stUserData& U : vUsers)
	{
		if (U.UserName == UserName && U.Password == Password)
		{
			CurrentUser = U;
			return true;
		}
	}
	return false;
}

bool LoadUserInfo(string UserName, string Password)
{
	if (FindUserByUserNameAndPassword(UserName, Password, CurrentUser))
		return true;
	else
		return false;
}

void AddUserDataToFile(string UsersFileName, string stDataLine)
{
	fstream MyFile;

	MyFile.open(UsersFileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;
		MyFile.close();
	}
}

int ReadPermissionsToSet()
{
	int Permission = 0;
	string Answer = "";

	cout << "\n[+] Do You want to give full Access? Y/N ";
	getline(cin, Answer);

	Answer = NexaString::LowerAllString(Answer);

	if (Answer == "yes" || Answer == "y")
	{
		return -1;
	}

	cout << "\n[+] Do You want to give Access to: \n";

	cout << "\n[+] Show Client List? y/n? ";
	cin >> Answer;
	Answer = NexaString::LowerAllString(Answer);

	if (Answer == "yes" || Answer == "y")
	{
		Permission += enMainMenuPermissions::pShowClientList;
	}

	cout << "\n[+] Add New Client? y/n? ";
	cin >> Answer;
	Answer = NexaString::LowerAllString(Answer);

	if (Answer == "yes" || Answer == "y")
	{
		Permission += enMainMenuPermissions::pAddNewClient;
	}

	cout << "\n[+] Delete Client? y/n? ";
	cin >> Answer;
	Answer = NexaString::LowerAllString(Answer);

	if (Answer == "yes" || Answer == "y")
	{
		Permission += enMainMenuPermissions::pDeleteClient;
	}

	cout << "\n[+] Update Client? y/n? ";
	cin >> Answer;
	Answer = NexaString::LowerAllString(Answer);

	if (Answer == "yes" || Answer == "y")
	{
		Permission += enMainMenuPermissions::pUpdateClientInfo;
	}

	cout << "\n[+] Find Client? y/n? ";
	cin >> Answer;
	Answer = NexaString::LowerAllString(Answer);

	if (Answer == "yes" || Answer == "y")
	{
		Permission += enMainMenuPermissions::pFindClient;
	}

	cout << "\n[+] Transactions? y/n? ";
	cin >> Answer;
	Answer = NexaString::LowerAllString(Answer);

	if (Answer == "yes" || Answer == "y")
	{
		Permission += enMainMenuPermissions::pTransactions;
	}

	cout << "\n[+] Manage Users? y/n? ";
	cin >> Answer;
	Answer = NexaString::LowerAllString(Answer);

	if (Answer == "yes" || Answer == "y")
	{
		Permission += enMainMenuPermissions::pManageUsers;
	}

	return Permission;
}

stUserData ReadNewUser()
{
	stUserData UserData;
	vector <stUserData> vUser;

	vUser = LoadUsersDataFromFile(UsersFileName);

	cout << "Enter User Name: ";
	getline(cin >> ws, UserData.UserName);

	while (FindUserByUserName(vUser, UserData.UserName, UserData))
	{
		cout << "\nUser with [" << UserData.UserName << "] Name already exists, Please enter another User Name? ";
		getline(cin >> ws, UserData.UserName);
	}

	cout << "Enter Password: ";
	getline(cin, UserData.Password);

	UserData.Permissions = ReadPermissionsToSet();

	return UserData;
}

void AddNewUser()
{
	stUserData User;
	User = ReadNewUser();
	AddUserDataToFile(UsersFileName, ConvertUserRecordToLine(User));
}

void AddNewUsers()
{
	string AddMore = "yes";
	do
	{
		system("cls");
		cout << "Adding New User:\n\n";

		AddNewUser();

		cout << "\nUser Added Successfully, do you want to add more Users? Y/N? ";
		cin >> AddMore;

		AddMore = NexaString::LowerAllString(AddMore);

	} while (AddMore == "yes" || AddMore == "y");
}

void PrintUserRecord(stUserData UserData)
{
	cout << "| " << setw(20) << left << UserData.UserName;
	cout << "| " << setw(20) << left << UserData.Password;
	cout << "| " << setw(10) << left << UserData.Permissions;
}

void PrintAllUsersData()
{
	vector <stUserData> vUsers;
	vUsers = LoadUsersDataFromFile(UsersFileName);

	cout << "\n\t\t\t\t\tUser List (" << vUsers.size() << ") User/s.";
	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;
	cout << "| " << left << setw(20) << "User Name";
	cout << "| " << left << setw(20) << "Password";
	cout << "| " << left << setw(10) << "Permissions";
	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;
	for (stUserData& vUser : vUsers)
	{
		PrintUserRecord(vUser);
		cout << endl;
	}
	cout << "\n_______________________________________________________";
	cout << "___________________________________________________\n" << endl;
}

void PrintUserCard(stUserData User)
{
	cout << "\n\nThe following are the User Details:\n";
	cout << "----------------------------------------------------\n";
	cout << "User Name   : " << User.UserName << endl;
	cout << "Password    : " << User.Password << endl;
	cout << "Permissions : " << User.Permissions << endl;
	cout << "----------------------------------------------------\n";
}

bool MarkUserForDeleteByUserName(vector <stUserData>& vUsers, string UserName)
{
	for (stUserData& U : vUsers)
	{
		if (U.UserName == UserName)
		{
			U.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

string ReadUserName()
{
	string UserName = "";

	cout << "\nPlease enter User Name? ";
	cin >> UserName;

	return UserName;
}

vector <stUserData> SaveUsersDataToFile(string UsersFileName, vector <stUserData> vUsers)
{
	fstream MyFile;

	MyFile.open(UsersFileName, ios::out);
	string DataLine = "";

	if (MyFile.is_open())
	{
		for (stUserData U : vUsers)
		{
			if (U.MarkForDelete == false)
			{
				DataLine = ConvertUserRecordToLine(U);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vUsers;
}

bool DeleteUserByUserName(string UserName, vector <stUserData>& vUsers)
{
	stUserData User;
	string Answer = "";

	if (FindUserByUserName(vUsers, UserName, User))
	{
		if (User.UserName == "Admin")
		{
			cout << "\nYou cannot Delete The Admin.\n";
			GoBackToManageUsersMenue();
		}
		else
		{
			PrintUserCard(User);
		}
		

		cout << "\n\nAre you sure you want delete this User? Y/N? ";
		cin >> Answer;

		Answer = NexaString::LowerAllString(Answer);

		if (Answer == "y" || Answer == "yes")
		{
			MarkUserForDeleteByUserName(vUsers, UserName);
			SaveUsersDataToFile(UsersFileName, vUsers);

			vUsers = LoadUsersDataFromFile(UsersFileName);

			cout << "\n\nUser Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nUser with User Name (" << UserName << ") is Not Found!" << endl;
		return false;
	}
}

stUserData ChangeUserRecord(string UserName)
{
	stUserData User;

	User.UserName = UserName;

	cout << "\n\nPlease enter the Password: ";
	getline(cin >> ws, User.Password);

	User.Permissions = ReadPermissionsToSet();

	return User;
}

void ShowAccessDeniedMessage()
{
	system("cls");
	cout << "\n\n\n-----------------------------------------------------------------\n";
	cout << "\tAccess Denied!\n\tYou don't have Permission to perform this Operation.\n";
	cout << "\tPlease contact your Admin\n";
	cout << "-----------------------------------------------------------------\n";

	GoBackToMainMenue();

}

bool CheckAccessPermission(enMainMenuPermissions Permission)
{
	if (CurrentUser.Permissions == enMainMenuPermissions::pFullAccess)
	{
		return true;
	}

	if ((CurrentUser.Permissions & Permission) == Permission)
	{
		return true;
	}
	else
	{
		return false;
	}
	
	
	
	
}

bool UpdateUserByUserName(vector <stUserData>& vUsers, string UserName)
{
	stUserData User;
	char Answer = 'n';

	if (FindUserByUserName(vUsers, UserName, User))
	{

		if (User.UserName == "Admin")
		{
			cout << "\nYou cannot Update The Admin.\n";
			GoBackToManageUsersMenue();
		}
		else
		{
			PrintUserCard(User);
		}

		cout << "\n\nAre you sure you want Update this User? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			for (stUserData& U : vUsers)
			{
				if (U.UserName == UserName)
				{
					U = ChangeUserRecord(UserName);
					break;
				}
			}
			SaveUsersDataToFile(UsersFileName, vUsers);
			cout << "\nUser Update Successfully." << endl;
			return true;
		}
	}
	else
	{
		cout << "\nUser with User Name (" << UserName << ") is Not Found!" << endl;
		return false;
	}
}

void GoBackToManageUsersMenue()
{
	cout << "\n\nPress any key to go back to Manage Users Menue...";
	system("pause>0");
	ShowManageUsersScreen();
}

void ShowUserListScreen()
{
	
	PrintAllUsersData();
}

void AddNewUsersScreen()
{
	cout << "\n----------------------------------------------------\n";
	cout << "\t\tAdd New User Screen\n";
	cout << "----------------------------------------------------\n";

	AddNewUsers();
}

void ShowDeleteUserScreen()
{
	cout << "\n----------------------------------------------------\n";
	cout << "\t\tDelete User Screen\n";
	cout << "----------------------------------------------------\n";

	vector <stUserData> vUsers = LoadUsersDataFromFile(UsersFileName);
	string UserName = ReadUserName();

	DeleteUserByUserName(UserName, vUsers);
}

void UpdateUserScreen()
{
	cout << "\n----------------------------------------------------\n";
	cout << "\t\tUpdate User Screen\n";
	cout << "----------------------------------------------------\n";

	vector <stUserData> vUsers = LoadUsersDataFromFile(UsersFileName);
	string UserName = ReadUserName();

	UpdateUserByUserName(vUsers, UserName);
}

void FindUserScreen()
{
	cout << "\n----------------------------------------------------\n";
	cout << "\t\tFind User Screen\n";
	cout << "----------------------------------------------------\n";

	vector <stUserData> vUsers = LoadUsersDataFromFile(UsersFileName);
	string UserName = ReadUserName();
	stUserData User;

	if (FindUserByUserName(vUsers, UserName, User))
	{
		PrintUserCard(User);
	}
	else
	{
		cout << "\nUser with User Name (" << UserName << ") is Not Found!" << endl;
	}
}

short ReadManageUsersMenueOption()
{
	short Choice = 0;

	cout << "Choose what do you want to do? [1 to 6]? ";
	cin >> Choice;

	return Choice;
}
		
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

	if (!CheckAccessPermission(enMainMenuPermissions::pAddNewClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

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

	if (!CheckAccessPermission(enMainMenuPermissions::pShowClientList))
	{
		ShowAccessDeniedMessage();
		return;
	}


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
	
	if (!CheckAccessPermission(enMainMenuPermissions::pDeleteClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

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

	if (!CheckAccessPermission(enMainMenuPermissions::pUpdateClientInfo))
	{
		ShowAccessDeniedMessage();
		return;
	}

	cout << "\n----------------------------------------------------\n";
	cout << "\t\tUpdate Client Screen\n";
	cout << "----------------------------------------------------\n";

	vector <stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	UpdateClientByAccountNumber(vClients, AccountNumber);

}

void FindClientScreen()
{

	if (!CheckAccessPermission(enMainMenuPermissions::pFindClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

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
	cout << "Choose wath do you want to do? [1 to 8]? ";
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
		

	case enMainMenueOptions::eManageUsers:

		system("cls");
		ShowManageUsersScreen();
		break;
	
	case enMainMenueOptions::eLogout:
	
		system("cls");
		LoginScreen();
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

void PerformManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOption)
{
	switch (ManageUsersMenueOption)
	{

	case enManageUsersMenueOptions::eShowUsersList:
		system("cls");
		ShowUserListScreen();
		GoBackToManageUsersMenue();
		break;

	case enManageUsersMenueOptions::eAddNewUser:
		system("cls");
		AddNewUsersScreen();
		GoBackToManageUsersMenue();
		break;

	case enManageUsersMenueOptions::eDeletedUser:
		system("cls");
		ShowDeleteUserScreen();
		GoBackToManageUsersMenue();
		break;

	case enManageUsersMenueOptions::eUpdateUserInfo:
		system("cls");
		UpdateUserScreen();
		GoBackToManageUsersMenue();
		break;

	case enManageUsersMenueOptions::eFindUser:
		system("cls");
		FindUserScreen();
		GoBackToManageUsersMenue();
		break;

	case enManageUsersMenueOptions::enMainMenue:
		ShowMainMenue();
		break;
	}

}

void ShowTransactionsMeneuScreen()
{
	if (!CheckAccessPermission(enMainMenuPermissions::pTransactions))
	{
		ShowAccessDeniedMessage();
		return;
	}

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

void ShowManageUsersScreen()
{
	if (!CheckAccessPermission(enMainMenuPermissions::pManageUsers))
	{
		ShowAccessDeniedMessage();
		return;
	}

	system("cls");
	cout << "====================================================\n";
	cout << "\t\tManage Users Menue Screen\n";
	cout << "====================================================\n";
	cout << "\t[1] Show Users List\n";
	cout << "\t[2] Add New User\n";
	cout << "\t[3] Delete User\n";
	cout << "\t[4] Update User Info\n";
	cout << "\t[5] Find User\n";
	cout << "\t[6] Main Menue\n";
	cout << "====================================================\n";
	PerformManageUsersMenueOption((enManageUsersMenueOptions)ReadManageUsersMenueOption());
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
	cout << "\t[6] Transactions\n";
	cout << "\t[7] Manage Users\n";
	cout << "\t[8] Logout\n";
	cout << "====================================================\n";

	PerformMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

void LoginScreen()
{

	
	string UserName = "";
	string Password = "";

	bool LoginSuccess = false;

	do
	{
		system("cls");

		cout << "====================================================\n";
		cout << "\t\tLogin Screen\n";
		cout << "====================================================\n";


		if (LoginSuccess)
		{
			cout << "\nInvalid User Name or Password, Please try again!" << endl;
		}

		cout << "\nPlease enter User Name: ";
		getline(cin >> ws, UserName);

		cout << "Please enter Password: ";
		getline(cin, Password);

		LoginSuccess = !LoadUserInfo(UserName, Password);


	} while (LoginSuccess);

	ShowMainMenue();


}



int main()
{

	

	LoginScreen();



	return 0;
}