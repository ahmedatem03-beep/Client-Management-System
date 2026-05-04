#include <ctime>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cctype>
#include "MyLip.h"

using namespace std;
const string FileNameClient = "Client.txt";
void ShowMainMenue();
void ShowTransactionMenueScreen();

enum enCheckClient
{
	ShowClient = 1, AddClient = 2, DeletClient = 3, UpdateClient = 4, FindClient = 5, Transactions = 6, Exit = 7
};

enum enCheckTransactions
{
	Deposit = 1, Withdraw = 2, TotalBalance = 3, ManMenue = 4
};

struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelet = false;

};
sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;

	Client.AccountNumber = AccountNumber;
	cout << "Enter PinCode? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}

sClient ConvertLineToRecord(string Line, string Seperator = "#//#")
{
	sClient Client;
	vector<string>vString;
	vString = MyLip::SplitStringToVector(Line, Seperator);
	Client.AccountNumber = vString[0];
	Client.PinCode = vString[1];
	Client.Name = vString[2];
	Client.Phone = vString[3];
	Client.AccountBalance = stod(vString[4]);
	return Client;
}
string ConvertRecordToLine(sClient Client, string Seperator =
	"#//#")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}
vector<sClient> LoadDataFromFile(string FileName)
{
	vector<sClient> vClient;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string line;
		sClient Client;
		while (getline(MyFile, line))
		{
			Client = ConvertLineToRecord(line);
			vClient.push_back(Client);
		}
		MyFile.close();
	}
	return vClient;
}


bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return false;
}
sClient ReadNewClient()
{
	sClient Client;

	cout << "------------------------------\n";
	cout << "    Add New Client Screen.\n";
	cout << "______________________________\n";
	cout << "Adding New Client\n\n";

	cout << "Pleas Enter Account Number? ";
	getline(cin >> ws, Client.AccountNumber);

	while (ClientExistsByAccountNumber(Client.AccountNumber, FileNameClient))
	{
		cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number ? ";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}

void AddDataLineToFile(string FileName, string DataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << DataLine << endl;
		MyFile.close();
	}
}
void AddNewClients()
{
	sClient Client = ReadNewClient();
	AddDataLineToFile(FileNameClient, ConvertRecordToLine(Client));
}
void AddAllClient()
{
	char AddMore;

	do
	{
		system("cls");
		AddNewClients();
		cout << "\n\nClient Added Successfully, Do you Want To Add More Client? ";
		cin >> AddMore;
	} while (AddMore == 'Y' || AddMore == 'y');
}




void PrintClientToRecord(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintAllClientToFile(vector<sClient> vClient)
{
	cout << "\t\t\t\tClient(" << vClient.size() << ") Client(s).\n\n";
	cout << "________________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n\n________________________________________________________________________________________________\n\n";
	for (sClient Client : vClient)
	{
		PrintClientToRecord(Client);
		cout << endl;
	}
	cout << "\n________________________________________________________________________________________________\n";
}
void PrintClients(sClient Client)
{
	cout << "\n\nThe Follwing Are The Client Deteails:\n";
	cout << "------------------------------------------------\n";
	cout << "Acoount Number : " << Client.AccountNumber << endl;
	cout << "Pin Code       : " << Client.PinCode << endl;
	cout << "Name           : " << Client.Name << endl;
	cout << "Phone          : " << Client.Phone << endl;
	cout << "Account Balance: " << Client.AccountBalance;
	cout << "\n------------------------------------------------\n";
}


string ReadAccountNumber()
{
	string Num;
	cout << "Pleas Enter Account Number? ";
	cin >> Num;
	return Num;
}
bool FindClientByAccountNumber(string Accountnumber, vector<sClient> vClient, sClient& Client)
{

	for (sClient C : vClient)
	{
		if (C.AccountNumber == Accountnumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}


void PrintFindAccountNumber(vector<sClient> vClient)
{
	sClient Client;
	string AccountNumber = ReadAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		PrintClients(Client);
	}
	else
	{
		cout << "\nClient With Account Number (" << AccountNumber << ") IS Not Found.\n";
	}

}

bool MarkClientForDeletByAccountNumber(string AccountNumber, vector<sClient>& vClient)
{
	for (sClient& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelet = true;
			return true;
		}
	}
	return false;
}

vector<sClient> SaveClientDateToFile(string FileName, vector<sClient> vCleint)
{
	fstream Myfile;
	string DataLine;
	Myfile.open(FileName, ios::out);
	if (Myfile.is_open())
	{
		for (sClient C : vCleint)
		{
			if (C.MarkForDelet == false)
			{
				DataLine = ConvertRecordToLine(C);
				Myfile << DataLine << endl;
			}

		}
		Myfile.close();
	}
	return vCleint;
}


bool DeletClientByAccountNumber(string AccountNumber, vector<sClient> vClient)
{

	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		cout << "------------------------------\n";
		cout << "    Delet Client Screen\n";
		cout << "______________________________\n";
		PrintClients(Client);
		cout << "\n\nAre You Sure You Want Delet This Clients? y?n";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			MarkClientForDeletByAccountNumber(AccountNumber, vClient);
			SaveClientDateToFile(FileNameClient, vClient);

			vClient = LoadDataFromFile(FileNameClient);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClient)
{

	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		cout << "-----------------------------------\n";
		cout << "    Update Client Info Screen\n";
		cout << "___________________________________\n";
		PrintClients(Client);
		cout << "\n\nAre You Sure You Want Update This Clients? y?n";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			for (sClient& C : vClient)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}

			SaveClientDateToFile(FileNameClient, vClient);

			cout << "\n\nClient Ubdated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}



void GoBackToMainMenue()
{
	cout << "\nPress Any Key To Go Back To Main Menue... ";
	system("pause>0");
	system("cls");
	ShowMainMenue();

}
short ReadNumber()
{

	short Num = 0;
	cin >> Num;
	return Num;
}

void EndScreen()
{
	cout << "------------------------------\n";
	cout << "       Program Ends : -)\n";
	cout << "______________________________\n";

	system("pause>0");
}

void GoToBackTransactionMenue()
{
	cout << "\nPress Any Key To Go Back To Transaction Menue... ";
	system("pause>0");
	system("cls");
	ShowTransactionMenueScreen();
}

bool DepositeBalanceToClientByAccount(string AccountNumber, double Amount, vector<sClient> vClient)
{
	char Answer = 'n';
	cout << "\n\n Are You Sure Wou Want Perform This Transaction? y/n? ";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		for (sClient& C : vClient)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveClientDateToFile(FileNameClient, vClient);
				cout << "\n\nDone Successfully. New Balance is: " << C.AccountBalance;
				return true;
			}
		}
	}
	return false;
}
void ShowDepositScreen()
{
	cout << "------------------------------\n";
	cout << "      Deposit Screen\n";
	cout << "______________________________\n\n";
	vector<sClient> vClient = LoadDataFromFile(FileNameClient);
	string AccountNumber = ReadAccountNumber();
	sClient Client;


	if (!FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		cout << "Client With [" << AccountNumber << "] Does Not Exist.\n\n";
		AccountNumber = ReadAccountNumber();
	}
	PrintClients(Client);

	double Amount = 0;
	cout << "Pleas Enter Depost Amount? ";
	cin >> Amount;

	DepositeBalanceToClientByAccount(AccountNumber, Amount, vClient);

}

void ShowWithdrawScreen()
{
	cout << "------------------------------\n";
	cout << "      Withdraw Screen\n";
	cout << "______________________________\n\n";
	vector<sClient> vClient = LoadDataFromFile(FileNameClient);
	string AccountNumber = ReadAccountNumber();
	sClient Client;

	if (!FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		cout << "Client With [" << AccountNumber << "] Does Not Exist.\n\n";
		AccountNumber = ReadAccountNumber();
	}
	PrintClients(Client);

	double Amount = 0;
	cout << "Pleas Enter Depost Amount? ";
	cin >> Amount;
	while (Amount > Client.AccountBalance)
	{
		cout << "\n\nAmount Exceeds The Balance, You Can Withdraw up to: " << Client.AccountBalance;
		cout << "\nPleas Enter Depost Amount? ";
		cin >> Amount;
	}
	DepositeBalanceToClientByAccount(AccountNumber, Amount * -1, vClient);

}

void PrintClientToTotalBalance(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowTotalBlance()
{
	vector<sClient> vClient = LoadDataFromFile(FileNameClient);
	double SumTotalBalance = 0;
	cout << "\t\t\t\tClient(" << vClient.size() << ") Client(s).\n\n";
	cout << "________________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n\n________________________________________________________________________________________________\n\n";
	for (sClient Client : vClient)
	{

		PrintClientToTotalBalance(Client);
		cout << endl;
		SumTotalBalance += Client.AccountBalance;
	}
	cout << "________________________________________________________________________________________________\n\n";
	cout << "\t\t\tTotal Balance = " << SumTotalBalance << endl;
}
void CheckTransactionsData(enCheckTransactions CheckTransactions)
{
	vector<sClient> vClient = LoadDataFromFile(FileNameClient);
	switch (CheckTransactions)
	{
	case enCheckTransactions::Deposit:
	{
		system("cls");
		ShowDepositScreen();
		GoToBackTransactionMenue();
		break;
	}
	case enCheckTransactions::Withdraw:
	{
		system("cls");
		ShowWithdrawScreen();
		GoToBackTransactionMenue();
		break;
	}
	case enCheckTransactions::TotalBalance:
	{
		system("cls");
		ShowTotalBlance();
		GoToBackTransactionMenue();
		break;
	}
	case enCheckTransactions::ManMenue:
	{
		system("cls");
		ShowMainMenue();
	}
	}
}
void ShowTransactionMenueScreen()
{
	cout << "==================================================\n";
	cout << "\t\tTransactions Menue Screen\n";
	cout << "==================================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balance.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "==================================================\n";
	cout << "Choose What Do You Want to do? [1 to 4]? ";
	CheckTransactionsData(enCheckTransactions(ReadNumber()));

}



void CheckClientData(enCheckClient CheckClient)
{
	vector<sClient> vClient = LoadDataFromFile(FileNameClient);

	switch (CheckClient)
	{
	case enCheckClient::ShowClient:
	{
		system("cls");
		PrintAllClientToFile(vClient);
		GoBackToMainMenue();
		break;
	}
	case enCheckClient::AddClient:
	{
		system("cls");
		AddAllClient();
		GoBackToMainMenue();
		break;
	}
	case enCheckClient::DeletClient:
	{
		system("cls");
		DeletClientByAccountNumber(ReadAccountNumber(), vClient);
		GoBackToMainMenue();
		break;
	}
	case enCheckClient::UpdateClient:
	{
		system("cls");
		UpdateClientByAccountNumber(ReadAccountNumber(), vClient);
		GoBackToMainMenue();
		break;
	}
	case enCheckClient::FindClient:
	{
		system("cls");
		PrintFindAccountNumber(vClient);
		GoBackToMainMenue();
		break;
	}
	case enCheckClient::Transactions:
	{
		system("cls");
		ShowTransactionMenueScreen();
		break;
	}
	case enCheckClient::Exit:
	{
		system("cls");
		EndScreen();
		break;
	}

	}
}



void ShowMainMenue()
{

	cout << "==================================================\n";
	cout << "\t\tMian Menue Screen\n";
	cout << "==================================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delet Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.\n";
	cout << "==================================================\n";
	cout << "Choos What Do you Want To Do? [1 to 7]? ";
	CheckClientData(enCheckClient(ReadNumber()));


}
int main()
{
	ShowMainMenue();

	system("pause>0");
}
