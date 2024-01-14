#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<ctime>
using namespace std;
class Loan
{
public:
	int userID;
	long int amount;
	Loan(int id = 0, long int am = 0)
	{
		userID = id;
		amount = am;
	}
};
class Transaction
{
public:
	string date = "07-05-2023";
	int userID;
	long int amount;
	string type;
	int user2ID;
	Transaction(int id = 0, long int am = 0, string t = "", int id2 = 0)
	{
		userID = id;
		amount = am;
		type = t;
		user2ID = id2;
	}
};
class Card
{
public:
	int userID;
	long long int number;
	int pin;
	Card(int id = 0, long long int num = 0, int p = 0)
	{
		userID = id;
		number = num;
		pin = p;
	}
	int loaddata(Card*& arr)
	{
		ifstream f1;
		f1.open("cards.txt");
		string s;
		int lines = 0;
		while (getline(f1, s))
			lines++;
		f1.close();
		arr = new Card[lines];
		f1.open("cards.txt");
		for (int i = 0; i < lines; i++)
		{
			getline(f1, s, ',');
			arr[i].userID = stoi(s);
			getline(f1, s, ',');
			arr[i].number = stoll(s);
			getline(f1, s, '\n');
			arr[i].pin = stoi(s);
		}
		f1.close();
		return lines;
	}
	int loaddata1(Card*& arr)
	{
		ifstream f1;
		f1.open("cards2.txt");
		string s;
		int lines = 0;
		while (getline(f1, s))
			lines++;
		f1.close();
		arr = new Card[lines];
		f1.open("cards2.txt");
		for (int i = 0; i < lines; i++)
		{
			getline(f1, s, ',');
			arr[i].userID = stoi(s);
			getline(f1, s, ',');
			arr[i].number = stoll(s);
			getline(f1, s, '\n');
			arr[i].pin = stoi(s);
		}
		f1.close();
		return lines;
	}
	int pin_check(Card*& arr, int id, int l)
	{
		for (int i = 0; i < l; i++)
		{
			if (arr[i].userID == id)
				if (arr[i].pin == 0000)
					return 1;
		}
		return 0;
	}
	int pin_check(Card*& arr, int id, int pin, int l)
	{
		for (int i = 0; i < l; i++)
		{
			if (arr[i].userID == id)
				if (arr[i].pin == pin)
					return 1;
		}
		return 0;
	}
	void setpin(Card*& arr, int id, int pin, int l)
	{
		for (int i = 0; i < l; i++)
		{
			if (arr[i].userID == id)
				arr[i].pin = pin;
		}
		ofstream f2;
		f2.open("cards.txt");
		for (int i = 0; i < l; i++)
		{
			f2 << arr[i].userID << ",";
			f2 << arr[i].number << ",";
			f2 << arr[i].pin << "\n";
		}
		f2.close();
	}
	void setpin1(Card*& arr, int id, int pin, int l)
	{
		for (int i = 0; i < l; i++)
		{
			if (arr[i].userID == id)
				arr[i].pin = pin;
		}
		ofstream f2;
		f2.open("cards2.txt");
		for (int i = 0; i < l; i++)
		{
			f2 << arr[i].userID << ",";
			f2 << arr[i].number << ",";
			f2 << arr[i].pin << "\n";
		}
		f2.close();
	}
};
class AccountType
{
public:
	bool bronze;
	bool gold;
	bool business;
	AccountType(bool br = false, bool g = false, bool bu = false)
	{
		bronze = br;
		gold = g;
		business = bu;
	}
};
class User
{
public:
	string name;
	string address;
	string loginID;
	string password;
	long int limit;
	int userID;
	long int balance;
	User(string n = "", string a = "", string id = "", string pass = "", long int l = 0, int id1 = 0, long int b = 0)
	{
		name = n;
		address = a;
		loginID = id;
		password = pass;
		limit = l;
		userID = id1;
		balance = b;
	}
	virtual void show_menu()
	{
		cout << "Here are the list of functions:" << endl;
		cout << "1.Deposit amount\n2.Withdraw amount\n3.View balance\n4.View transaction history\n5.Transfer funds to the other accounts" << endl;
	}
};
class User_client : public User
{
public:
	string phone_no;
	string CNIC;
	Transaction t;
	AccountType acc_type;
	Card card;
	User_client(string n = "", string a = "", string id = "", string pass = "", long int l = 0, int id1 = 0, long int b = 0, string ph = "", string cnic = "") :User(n, a, id, pass, l, id1, b)
	{
		phone_no = ph;
		CNIC = cnic;
	}
	string getaccount_type()
	{
		if (acc_type.gold == true)
			return "gold";
		else if (acc_type.bronze == true)
			return "bronze";
		else
			return "business";
	}
	long int getbalance()
	{
		return balance;
	}
	void setbalance(long int b)
	{
		balance = b;
	}
	int searchdata(User_client*& arr, string ID, string password, int l)
	{
		for (int i = 0; i < l; i++)
		{
			if (arr[i].loginID == ID)
				if (arr[i].password == password)
					return i;
		}
		return -1;
	}
	int searchdata2(User_client*& arr, string ID, int l)
	{
		for (int i = 0; i < l; i++)
		{
			if (arr[i].userID == stoi(ID))
				return i;
		}
		return -1;
	}
	int getID(User_client*& arr, int index)
	{
		return arr[index].userID;
	}
	int searchdata1(User_client*& arr, int id, int l)
	{
		for (int i = 0; i < l; i++)
		{
			if (arr[i].t.userID == id)
				return 1;
		}
		return 0;
	}
	void viewhistory(User_client*& arr, int id, int l)
	{
		for (int i = 0, k = 0; i < l; i++)
		{
			if (arr[i].t.userID == id)
			{

				cout << k + 1 << ".\n";
				k++;
				cout << "\tYour transaction date is: " << arr[i].t.date << endl;
				cout << "\tYour transaction amount is: " << arr[i].t.amount << endl;
				cout << "\tYour transaction type is: " << arr[i].t.type << endl;
				if (arr[i].t.user2ID > 0)
					cout << "\tYou transfered amount to the user with ID: " << arr[i].t.user2ID << endl;
			}
		}
	}
	int loaddata(User_client*& arr)
	{
		ifstream f1;
		f1.open("users.txt");
		string s;
		int lines = 0;
		while (getline(f1, s))
			lines++;
		arr = new User_client[lines];
		f1.close();
		f1.open("users.txt");
		for (int i = 0; i < lines; i++)
		{
			getline(f1, s, ',');
			arr[i].userID = stoi(s);
			getline(f1, arr[i].name, ',');
			getline(f1, arr[i].phone_no, ',');

			getline(f1, arr[i].address, ',');
			getline(f1, arr[i].CNIC, ',');

			getline(f1, arr[i].loginID, ',');
			getline(f1, arr[i].password, ',');
			getline(f1, s, ',');
			arr[i].limit = stol(s);
			getline(f1, s, ',');
			if (s == "bronze")
				arr[i].acc_type.bronze = true;
			else if (s == "gold")
				arr[i].acc_type.gold = true;
			else
				arr[i].acc_type.business = true;
			getline(f1, s, '\n');
			arr[i].balance = stol(s);
		}
		f1.close();
		return lines;
	}
	int loaddata_trans(User_client*& arr)
	{
		ifstream f1;
		f1.open("transactions.txt");
		string s;
		int lines = 0;
		while (getline(f1, s))
			lines++;
		arr = new User_client[lines];
		f1.close();
		f1.open("transactions.txt");
		for (int i = 0; i < lines; i++)
		{

			getline(f1, arr[i].t.date, ',');
			getline(f1, s, ',');
			arr[i].t.userID = stoi(s);
			getline(f1, s, ',');
			arr[i].t.amount = stol(s);
			string s1;
			getline(f1, s1, '\n');
			int len = s1.length();
			int j, count = 0;
			arr[i].t.type = "";
			for (j = 0; j < len; j++)
			{
				if (s1[j] != ',')
					arr[i].t.type += s1[j];
				else
				{
					count = 1;
					break;
				}
			}
			string s2 = "";
			if (count == 1)
			{
				for (int l = j + 1; l < len; l++)
				{

					s2 += s1[l];

				}
				arr[i].t.user2ID = stoi(s2);
			}
		}
		f1.close();
		return lines;
	}
	void request_data(User_client& obj)
	{
		ofstream f2;
		f2.open("Account Requests.txt", ios::app);
		f2 << obj.name << ",";
		f2 << obj.phone_no << ",";
		f2 << obj.address << ",";
		f2 << obj.CNIC << ",";
		f2 << obj.loginID << ",";
		f2 << obj.password << ",";
		f2 << obj.limit << ",";
		if (obj.acc_type.bronze == true)
			f2 << "bronze" << "\n";
		else if (obj.acc_type.gold == true)
			f2 << "gold" << "\n";
		else
			f2 << "business" << "\n";
		f2.close();
	}
	void signup()
	{
		User_client obj;
		string s;
		cout << "Enter your details:" << endl;
		cout << "Enter your name: ";
		cin.ignore();
		getline(cin, obj.name);
	c:cout << "Enter your phone number(must be 11 digit): ";
		getline(cin, s);
		int len = s.length();
		while (len != 11)
		{
			cout << "Enter valid phone number: ";
			getline(cin, s);
			len = s.length();
		}
		int count = 0;
		for (int i = 0; i < len; i++)
		{

			int a = int(s[i]);
			if (a < 48 || a > 57)
				count = 1;
		}
		if (count == 1)
		{
			cout << "Enter a valid phone number." << endl;
			goto c;
		}
		obj.phone_no = s;
		cout << "Enter your address: ";
		getline(cin, obj.address);
	c1:cout << "Enter your CNIC(must be 13 digit): ";
		getline(cin, s);
		len = s.length();
		while (len != 13)
		{
			cout << "Enter valid CNIC: ";
			getline(cin, s);
			len = s.length();
		}
		count = 0;
		for (int i = 0; i < len; i++)
		{

			int a = int(s[i]);
			if (a < 48 || a > 57)
				count = 1;
		}
		if (count == 1)
		{
			cout << "Enter a valid CNIC." << endl;
			goto c1;
		}
		obj.CNIC = s;
		cout << "Enter login ID: ";
		getline(cin, obj.loginID);
		cout << "Enter password: ";
		getline(cin, obj.password);
	c2:cout << "Enter your estimated daily withdrawal limit: ";
		getline(cin, s);
		len = s.length();
		count = 0;
		for (int i = 0; i < len; i++)
		{

			int a = int(s[i]);
			if (a < 48 || a > 57)
				count = 1;
		}
		if (count == 1)
		{
			cout << "Enter a valid limit." << endl;
			goto c2;
		}
		obj.limit = stol(s);
		if (obj.limit <= 100000)
			obj.acc_type.bronze = true;
		else if (obj.limit <= 500000)
			obj.acc_type.gold = true;
		else
			obj.acc_type.business = true;
		request_data(obj);
	}
	void returndata(User_client*& arr, int l)
	{
		ofstream f2;
		f2.open("users.txt");
		for (int i = 0; i < l; i++)
		{
			f2 << arr[i].userID << ",";
			f2 << arr[i].name << ",";
			f2 << arr[i].phone_no << ",";
			f2 << arr[i].address << ",";
			f2 << arr[i].CNIC << ",";
			f2 << arr[i].loginID << ",";
			f2 << arr[i].password << ",";
			f2 << arr[i].limit << ",";
			if (arr[i].acc_type.bronze == true)
				f2 << "bronze" << ",";
			else if (arr[i].acc_type.gold == true)
				f2 << "gold" << ",";
			else
				f2 << "business" << ",";
			f2 << arr[i].balance << "\n";

		}
		f2.close();

	}
	void returndata(User_client*& arr, int i, int l)
	{
		ofstream f2;
		f2.open("users.txt", ios::app);

		f2 << l + 1 << ",";
		f2 << arr[i].name << ",";
		f2 << arr[i].phone_no << ",";
		f2 << arr[i].address << ",";
		f2 << arr[i].CNIC << ",";
		f2 << arr[i].loginID << ",";
		f2 << arr[i].password << ",";
		f2 << arr[i].limit << ",";
		if (arr[i].acc_type.bronze == true)
			f2 << "bronze" << ",";
		else if (arr[i].acc_type.gold == true)
			f2 << "gold" << ",";
		else
			f2 << "business" << ",";
		f2 << "0\n";
		f2.close();
		string s = "";
		srand(time(0));
		for (int i = 0; i < 16; i++)
		{
			int a = (rand() % 9) + 1;
			s += to_string(a);
		}
		f2.open("cards.txt", ios::app);
		f2 << l + 1 << ",";
		f2 << s << ",";
		f2 << "0000" << "\n";
		f2.close();

	}
	void return_trans(User_client& obj)
	{
		ofstream f2;
		f2.open("transactions.txt", ios::app);
		f2 << obj.t.date << ",";
		f2 << obj.t.userID << ",";
		f2 << obj.t.amount << ",";
		f2 << obj.t.type << "\n";
		f2.close();
	}
	void deposit(User_client*& arr, int index, int l, int id, Card*& arr1, int l1)
	{
		int balance, pin;
	x:cout << "ENter your pin number: ";
		cin >> pin;
		int check = arr->card.pin_check(arr1, id, pin, l1);
		if (check != 1)
		{
			cout << "Your entered pin number is not valid" << endl;
			goto x;
		}
		else
		{
			cout << "Enter the amount you want to deposit in your account: ";
			cin >> balance;
			while (balance < 0)
			{
				cout << "Enter a valid amount: ";
				cin >> balance;
			}
			arr[index].balance += balance;
			returndata(arr, l);
			l = loaddata(arr);
			User_client obj;
			obj.t.userID = id;
			obj.t.amount = balance;
			obj.t.type = "Deposit";
			return_trans(obj);
			cout << "Your entered amount has been deposited." << endl;
		}

	}
	void viewbalance(User_client*& arr, int index)
	{
		cout << "Your current balance is: " << arr[index].balance << endl;
	}
	void withdraw(User_client*& arr, int index, int l, int id, Card*& arr1, int l1)
	{
		int balance, pin;
	x1:cout << "ENter your pin number: ";
		cin >> pin;
		int check = arr->card.pin_check(arr1, id, pin, l1);
		if (check != 1)
		{
			cout << "Your entered pin number is not valid" << endl;
			goto x1;
		}
		else
		{
			cout << "Enter the amount you want to withdraw from your account: ";
			cin >> balance;
			while (balance < 0)
			{
				cout << "Enter a valid amount: ";
				cin >> balance;
			}
			while (balance > arr[index].limit)
			{
				cout << "You are exceeding your daily withdrawal limit enter a valid amount: ";
				cin >> balance;
			}
			while (balance > arr[index].balance)
			{
				cout << "You have not much amount in your account enter a valid amount: ";
				cin >> balance;
			}

			arr[index].balance -= balance;
			returndata(arr, l);
			User_client obj;
			l = obj.loaddata(arr);
			obj.t.userID = id;
			obj.t.amount = balance;
			obj.t.type = "Withdraw";
			return_trans(obj);
			cout << "Your entered amount has been withdrawn." << endl;
		}
	}
	void return_trans1(User_client& obj)
	{
		ofstream f2;
		f2.open("transactions.txt", ios::app);
		f2 << obj.t.date << ",";
		f2 << obj.t.userID << ",";
		f2 << obj.t.amount << ",";
		f2 << obj.t.type << ",";
		f2 << obj.t.user2ID << "\n";
		f2.close();
	}
	void transfer(User_client*& arr, int index, int l, int id, Card*& arr1, int l1)
	{

		int balance, pin;
	x2:cout << "ENter your pin number: ";
		cin >> pin;
		int check = arr->card.pin_check(arr1, id, pin, l1);
		if (check != 1)
		{
			cout << "Your entered pin number is not valid" << endl;
			goto x2;
		}
		else
		{
			cout << "Enter the amount you want to transfer to other account: ";
			cin >> balance;
			while (balance < 0)
			{
				cout << "Enter a valid amount: ";
				cin >> balance;
			}
			while (balance > arr[index].balance)
			{
				cout << "You have not much amount in your account enter a valid amount: ";
				cin >> balance;
			}
			string s;
			cout << "Enter the other's account user id: ";
			cin.ignore();
			getline(cin, s);
			int i = searchdata2(arr, s, l);
			while (i == -1)
			{
				cout << "This user's account does not exist enter a valid id: ";
				getline(cin, s);
				i = searchdata2(arr, s, l);
			}
			arr[index].balance -= balance;
			arr[i].balance += balance;
			returndata(arr, l);
			l = loaddata(arr);
			User_client obj;
			obj.t.userID = id;
			obj.t.amount = balance;
			obj.t.type = "Transfer";
			obj.t.user2ID = stoi(s);
			return_trans1(obj);
			cout << "Your entered amount has bees transfered." << endl;
		}
	}

};
class Company_client : public User
{
public:
	long int tax_no;
	Transaction t;
	AccountType acc_type;
	Card card;
	Company_client(string n = "", string a = "", string id = "", string pass = "", long int l = 0, int id1 = 0, long int b = 0, long int tax = 0) :User(n, a, id, pass, l, id1, b)
	{
		tax_no = tax;
	}
	void return_trans(Company_client& obj)
	{
		ofstream f2;
		f2.open("transactions2.txt", ios::app);
		f2 << obj.t.date << ",";
		f2 << obj.t.userID << ",";
		f2 << obj.t.amount << ",";
		f2 << obj.t.type << "\n";
		f2.close();
	}
	void return_trans1(Company_client& obj)
	{
		ofstream f2;
		f2.open("transactions2.txt", ios::app);
		f2 << obj.t.date << ",";
		f2 << obj.t.userID << ",";
		f2 << obj.t.amount << ",";
		f2 << obj.t.type << ",";
		f2 << obj.t.user2ID << "\n";
		f2.close();
	}
	string getaccount_type()
	{
		if (acc_type.gold == true)
			return "gold";
		else if (acc_type.bronze == true)
			return "bronze";
		else
			return "business";
	}
	void show_menu()
	{
		User::show_menu();
		cout << "6.Request for a loan" << endl;
		cout << "7.Exit" << endl;
	}
	int searchdata2(Company_client*& arr, string ID, int l)
	{
		for (int i = 0; i < l; i++)
		{
			if (arr[i].userID == stoi(ID))
				return i;
		}
		return -1;
	}
	void request_data(Company_client& obj)
	{
		ofstream f2;
		f2.open("Account Requests2.txt", ios::app);
		f2 << obj.name << ",";

		f2 << obj.address << ",";
		f2 << obj.tax_no << ",";
		f2 << obj.loginID << ",";
		f2 << obj.password << ",";
		f2 << obj.limit << ",";
		if (obj.acc_type.bronze == true)
			f2 << "bronze" << "\n";
		else if (obj.acc_type.gold == true)
			f2 << "gold" << "\n";
		else
			f2 << "business" << "\n";
		f2.close();
	}
	void signup()
	{
		Company_client obj;
		string s;
		cout << "Enter your details:" << endl;
		cout << "Enter your company's name: ";
		cin.ignore();
		getline(cin, obj.name);
		cout << "Enter your company's address: ";
		getline(cin, obj.address);
	c:cout << "Enter Company's tax number: ";
		getline(cin, s);
		int len = s.length();
		int count = 0;
		for (int i = 0; i < len; i++)
		{

			int a = int(s[i]);
			if (a < 48 || a > 57)
				count = 1;
		}
		if (count == 1)
		{
			cout << "Enter a valid tax number." << endl;
			goto c;
		}
		obj.tax_no = stol(s);
		cout << "Enter Account's ID: ";
		getline(cin, obj.loginID);
		cout << "Enter Account's password: ";
		getline(cin, obj.password);
	c1:cout << "Enter your estimated daily withdrawal limit: ";
		getline(cin, s);
		len = s.length();
		count = 0;
		for (int i = 0; i < len; i++)
		{

			int a = int(s[i]);
			if (a < 48 || a > 57)
				count = 1;
		}
		if (count == 1)
		{
			cout << "Enter a valid limit." << endl;
			goto c1;
		}
		obj.limit = stol(s);
		if (obj.limit <= 100000)
			obj.acc_type.bronze = true;
		else if (obj.limit <= 500000)
			obj.acc_type.gold = true;
		else
			obj.acc_type.business = true;
		request_data(obj);
	}
	int searchdata(Company_client*& arr, string ID, string password, int l)
	{
		for (int i = 0; i < l; i++)
		{
			if (arr[i].loginID == ID)
				if (arr[i].password == password)
					return i;
		}
		return -1;
	}
	int getID(Company_client*& arr, int index)
	{
		return arr[index].userID;
	}
	int searchdata1(Company_client*& arr, int id, int l)
	{
		for (int i = 0; i < l; i++)
		{
			if (arr[i].t.userID == id)
				return 1;
		}
		return 0;
	}
	void viewhistory(Company_client*& arr, int id, int l)
	{
		for (int i = 0, k = 0; i < l; i++)
		{
			if (arr[i].t.userID == id)
			{

				cout << k + 1 << ".\n";
				k++;
				cout << "\tYour transaction date is: " << arr[i].t.date << endl;
				cout << "\tYour transaction amount is: " << arr[i].t.amount << endl;
				cout << "\tYour transaction type is: " << arr[i].t.type << endl;
				if (arr[i].t.user2ID > 0)
					cout << "\tYou transfered amount to the user with ID: " << arr[i].t.user2ID << endl;
			}
		}
	}
	int loaddata(Company_client*& arr)
	{
		ifstream f1;
		f1.open("companies.txt");
		string s;
		int lines = 0;
		while (getline(f1, s))
			lines++;
		arr = new Company_client[lines];
		f1.close();
		f1.open("companies.txt");
		for (int i = 0; i < lines; i++)
		{
			getline(f1, s, ',');
			arr[i].userID = stoi(s);
			getline(f1, arr[i].name, ',');


			getline(f1, arr[i].address, ',');
			getline(f1, s, ',');
			arr[i].tax_no = stol(s);
			getline(f1, arr[i].loginID, ',');
			getline(f1, arr[i].password, ',');
			getline(f1, s, ',');
			arr[i].limit = stol(s);
			getline(f1, s, ',');
			if (s == "bronze")
				arr[i].acc_type.bronze = true;
			else if (s == "gold")
				arr[i].acc_type.gold = true;
			else
				arr[i].acc_type.business = true;
			getline(f1, s, '\n');
			arr[i].balance = stol(s);
		}
		f1.close();
		return lines;
	}
	int loaddata_trans(Company_client*& arr)
	{
		ifstream f1;
		f1.open("transactions2.txt");
		string s;
		int lines = 0;
		while (getline(f1, s))
			lines++;
		arr = new Company_client[lines];
		f1.close();
		f1.open("transactions2.txt");
		for (int i = 0; i < lines; i++)
		{

			getline(f1, arr[i].t.date, ',');
			getline(f1, s, ',');
			arr[i].t.userID = stoi(s);
			getline(f1, s, ',');
			arr[i].t.amount = stol(s);
			string s1;
			getline(f1, s1, '\n');
			int len = s1.length();
			int j, count = 0;
			arr[i].t.type = "";
			for (j = 0; j < len; j++)
			{
				if (s1[j] != ',')
					arr[i].t.type += s1[j];
				else
				{
					count = 1;
					break;
				}
			}
			string s2 = "";
			if (count == 1)
			{
				for (int l = j + 1; l < len; l++)
				{

					s2 += s1[l];

				}
				arr[i].t.user2ID = stoi(s2);
			}
		}
		f1.close();
		return lines;
	}
	void returndata(Company_client*& arr, int l)
	{
		ofstream f2;
		f2.open("companies.txt");
		for (int i = 0; i < l; i++)
		{
			f2 << arr[i].userID << ",";
			f2 << arr[i].name << ",";

			f2 << arr[i].address << ",";
			f2 << arr[i].tax_no << ",";
			f2 << arr[i].loginID << ",";
			f2 << arr[i].password << ",";
			f2 << arr[i].limit << ",";
			if (arr[i].acc_type.bronze == true)
				f2 << "bronze" << ",";
			else if (arr[i].acc_type.gold == true)
				f2 << "gold" << ",";
			else
				f2 << "business" << ",";
			f2 << arr[i].balance << "\n";

		}
		f2.close();
	}
	void returndata(Company_client*& arr, int i, int l)
	{
		ofstream f2;
		f2.open("companies.txt", ios::app);

		f2 << l + 1 << ",";
		f2 << arr[i].name << ",";

		f2 << arr[i].address << ",";
		f2 << arr[i].tax_no << ",";
		f2 << arr[i].loginID << ",";
		f2 << arr[i].password << ",";
		f2 << arr[i].limit << ",";
		if (arr[i].acc_type.bronze == true)
			f2 << "bronze" << ",";
		else if (arr[i].acc_type.gold == true)
			f2 << "gold" << ",";
		else
			f2 << "business" << ",";
		f2 << "0\n";
		f2.close();
		string s = "";
		srand(time(0));
		for (int i = 0; i < 16; i++)
		{
			int a = (rand() % 9) + 1;
			s += to_string(a);
		}
		f2.open("cards2.txt", ios::app);
		f2 << l + 1 << ",";
		f2 << s << ",";
		f2 << "0000" << "\n";
		f2.close();

	}
	void deposit(Company_client*& arr, int index, int l, int id, Card*& arr1, int l1)
	{
		int balance, pin;
	x:cout << "ENter your pin number: ";
		cin >> pin;
		int check = arr->card.pin_check(arr1, id, pin, l1);
		if (check != 1)
		{
			cout << "Your entered pin number is not valid" << endl;
			goto x;
		}
		else
		{
			cout << "Enter the amount you want to deposit in your account: ";
			cin >> balance;
			while (balance < 0)
			{
				cout << "Enter a valid amount: ";
				cin >> balance;
			}
			arr[index].balance += balance;
			returndata(arr, l);
			l = loaddata(arr);
			Company_client obj;
			obj.t.userID = id;
			obj.t.amount = balance;
			obj.t.type = "Deposit";
			return_trans(obj);
			cout << "Your entered amount has been deposited." << endl;
		}
	}
	void viewbalance(Company_client*& arr, int index)
	{
		cout << "Your current balance is: " << arr[index].balance << endl;
	}
	void withdraw(Company_client*& arr, int index, int l, int id, Card*& arr1, int l1)
	{
		int balance, pin;
	x1:cout << "ENter your pin number: ";
		cin >> pin;
		int check = arr->card.pin_check(arr1, id, pin, l1);
		if (check != 1)
		{
			cout << "Your entered pin number is not valid" << endl;
			goto x1;
		}
		else
		{
			cout << "Enter the amount you want to withdraw from your account: ";
			cin >> balance;
			while (balance < 0)
			{
				cout << "Enter a valid amount: ";
				cin >> balance;
			}
			while (balance > arr[index].limit)
			{
				cout << "You are exceeding your daily withdrawal limit enter a valid amount: ";
				cin >> balance;
			}
			while (balance > arr[index].balance)
			{
				cout << "You have not much amount in your account enter a valid amount: ";
				cin >> balance;
			}

			arr[index].balance -= balance;
			returndata(arr, l);
			l = loaddata(arr);
			Company_client obj;
			obj.t.userID = id;
			obj.t.amount = balance;
			obj.t.type = "Withdraw";
			return_trans(obj);
			cout << "Your entered amount has been withdrawn." << endl;
		}
	}
	void transfer(Company_client*& arr, int index, int l, int id, Card*& arr2, int l1)
	{
		int balance, pin;
	x2:cout << "ENter your pin number: ";
		cin >> pin;
		int check = arr->card.pin_check(arr2, id, pin, l1);
		if (check != 1)
		{
			cout << "Your entered pin number is not valid" << endl;
			goto x2;
		}
		else
		{
			cout << "Enter the amount you want to transfer to other account: ";
			cin >> balance;
			while (balance < 0)
			{
				cout << "Enter a valid amount: ";
				cin >> balance;
			}
			while (balance > arr[index].balance)
			{
				cout << "You have not much amount in your account enter a valid amount: ";
				cin >> balance;
			}
			string s;
			cout << "Enter the other's account user id: ";
			cin.ignore();
			getline(cin, s);
			User_client* arr1;
			User_client obj;
			int l1 = obj.loaddata(arr1);
			int i = obj.searchdata2(arr1, s, l1);
			while (i == -1)
			{
				cout << "This user's account does not exist enter a valid id: ";
				getline(cin, s);
				i = obj.searchdata2(arr1, s, l1);
			}
			arr[index].balance -= balance;
			long int b = arr1[i].getbalance();
			b += balance;
			arr1[i].setbalance(b);
			obj.returndata(arr1, l1);
			returndata(arr, l);
			l = loaddata(arr);
			Company_client obj1;
			obj1.t.userID = id;
			obj1.t.amount = balance;
			obj1.t.type = "Transfer";
			obj1.t.user2ID = stoi(s);
			return_trans1(obj1);
			delete[]arr1;
			arr1 = NULL;
			cout << "Your entered amount has been transfered." << endl;
		}
	}
	void request_loan(Company_client*& arr, int i)
	{
		long int amount;
		cout << "Enter the amount of loan you want to request: ";
		cin >> amount;
		while (amount < 0)
		{
			cout << "ENter a valid amount: ";
			cin >> amount;
		}
		ofstream f2;
		f2.open("Loan Requests.txt", ios::app);
		f2 << arr[i].userID << ",";
		f2 << amount << "\n";
		f2.close();

	}
};
class Bank_employee : public User
{
public:
	User_client* u_client;
	Company_client* c_client;
	Loan* loan;
	Bank_employee()
	{
		u_client = NULL;
		c_client = NULL;
		loan = NULL;
	}
	~Bank_employee()
	{
		delete[]u_client;
		u_client = NULL;
		delete[]c_client;
		c_client = NULL;
		delete[]loan;
		loan = NULL;
	}
	void show_menu()
	{
		cout << "Here are the list of functions:" << endl;
		cout << "1.View client's accounts\n2.View new account applications\n3.View loan requests\n4.View transaction history\n5.Freeze or close someone's account\n6.Exit" << endl;
	}
	int loaddata_app(User_client*& arr)
	{
		ifstream f1;
		f1.open("Account Requests.txt");
		string s;
		int lines = 0;
		while (getline(f1, s))
			lines++;
		if (lines == 0)
			arr = NULL;
		else
		{
			arr = new User_client[lines];
			f1.close();
			f1.open("Account Requests.txt");
			for (int i = 0; i < lines; i++)
			{
				getline(f1, arr[i].name, ',');
				getline(f1, arr[i].phone_no, ',');

				getline(f1, arr[i].address, ',');
				getline(f1, arr[i].CNIC, ',');

				getline(f1, arr[i].loginID, ',');
				getline(f1, arr[i].password, ',');
				getline(f1, s, ',');
				arr[i].limit = stol(s);
				getline(f1, s, '\n');
				if (s == "bronze")
					arr[i].acc_type.bronze = true;
				else if (s == "gold")
					arr[i].acc_type.gold = true;
				else
					arr[i].acc_type.business = true;
			}
			f1.close();
		}
		return lines;
	}
	int loaddata_app(Company_client*& arr)
	{
		ifstream f1;
		f1.open("Account Requests2.txt");
		string s;
		int lines = 0;
		while (getline(f1, s))
			lines++;
		if (lines == 0)
			arr = NULL;
		else
		{
			arr = new Company_client[lines];
			f1.close();
			f1.open("Account Requests2.txt");
			for (int i = 0; i < lines; i++)
			{
				getline(f1, arr[i].name, ',');
				getline(f1, arr[i].address, ',');
				getline(f1, s, ',');
				arr[i].tax_no = stol(s);
				getline(f1, arr[i].loginID, ',');
				getline(f1, arr[i].password, ',');
				getline(f1, s, ',');
				arr[i].limit = stol(s);
				getline(f1, s, '\n');
				if (s == "bronze")
					arr[i].acc_type.bronze = true;
				else if (s == "gold")
					arr[i].acc_type.gold = true;
				else
					arr[i].acc_type.business = true;
			}
			f1.close();
		}
		return lines;
	}
	void viewaccounts()
	{
		User_client obj;
		int l = obj.loaddata(u_client);
		Company_client obj1;
		int l1 = obj1.loaddata(c_client);
		cout << "User client's accounts are following" << endl;
		for (int i = 0; i < l; i++)
		{
			cout << i + 1 << ".\n";
			cout << "\tUser's id: " << u_client[i].userID << endl;
			cout << "\tUser's name: " << u_client[i].name << endl;
			cout << "\tUser's phone number: " << u_client[i].phone_no << endl;
			cout << "\tUser's address: " << u_client[i].address << endl;
			cout << "\tUser's CNIC: " << u_client[i].CNIC << endl;
			cout << "\tUser's login id: " << u_client[i].loginID << endl;
			cout << "\tUser's password: " << u_client[i].password << endl;
			cout << "\tUser's daily withdrawal limit: " << u_client[i].limit << endl;
			cout << "\tUser's account type: " << u_client[i].getaccount_type() << endl;
			cout << "\tUser's account balance: " << u_client[i].balance << endl << endl;
		}
		cout << "Company client's accounts are following" << endl;
		for (int i = 0; i < l1; i++)
		{
			cout << i + 1 << ".\n";
			cout << "\tUser's id: " << c_client[i].userID << endl;
			cout << "\tUser's name: " << c_client[i].name << endl;

			cout << "\tUser's address: " << c_client[i].address << endl;
			cout << "\tUser's tax number: " << c_client[i].tax_no << endl;
			cout << "\tUser's login id: " << c_client[i].loginID << endl;
			cout << "\tUser's password: " << c_client[i].password << endl;
			cout << "\tUser's daily withdrawal limit: " << c_client[i].limit << endl;
			cout << "\tUser's account type: " << c_client[i].getaccount_type() << endl;
			cout << "\tUser's account balance: " << c_client[i].balance << endl << endl;
		}
	}
	int searchdata(Bank_employee*& arr, string ID, string password, int l)
	{
		for (int i = 0; i < l; i++)
		{
			if (arr[i].loginID == ID)
				if (arr[i].password == password)
					return i;
		}
		return -1;
	}
	int loaddata(Bank_employee*& arr)
	{
		ifstream f1;
		f1.open("bank_employees.txt");
		string s;
		int lines = 0;
		while (getline(f1, s))
			lines++;
		arr = new Bank_employee[lines];
		f1.close();
		f1.open("bank_employees.txt");
		for (int i = 0; i < lines; i++)
		{
			getline(f1, arr[i].loginID, ',');
			getline(f1, arr[i].password, '\n');
		}
		f1.close();
		return lines;
	}
	int loaddata(Loan*& arr)
	{
		ifstream f1;
		f1.open("Loan Requests.txt");
		string s;
		int lines = 0;
		while (getline(f1, s))
			lines++;
		if (lines > 0)
		{
			arr = new Loan[lines];
			f1.close();
			f1.open("Loan Requests.txt");
			for (int i = 0; i < lines; i++)
			{
				getline(f1, s, ',');
				arr[i].userID = stoi(s);
				getline(f1, s, '\n');
				arr[i].amount = stol(s);
			}
			f1.close();
		}
		else
			arr = NULL;
		return lines;
	}
	int searchdata(User_client*& arr, string  n, string cnic, int l)
	{
		for (int i = 0; i < l; i++)
		{
			if (arr[i].name == n)
				if (arr[i].CNIC == cnic)
					return i;
		}
		return -1;
	}
	int searchdata(Company_client*& arr, string  n, string number, int l)
	{
		for (int i = 0; i < l; i++)
		{
			if (arr[i].name == n)
				if (arr[i].tax_no == stol(number))
					return i;
		}
		return -1;
	}
	int searchdata(Company_client*& arr, int n, int l)
	{
		for (int i = 0; i < l; i++)
		{
			if (arr[i].userID == n)
				return i;
		}
		return -1;
	}
	int searchdata(Loan*& arr, int n, int l)
	{
		for (int i = 0; i < l; i++)
		{
			if (arr[i].userID == n)
				return i;
		}
		return -1;
	}
	void returndata_app(User_client*& arr, int l)
	{
		if (l > 0)
		{
			ofstream f2;
			f2.open("Account Requests.txt");
			for (int i = 0; i < l; i++)
			{
				f2 << arr[i].name << ",";
				f2 << arr[i].phone_no << ",";
				f2 << arr[i].address << ",";
				f2 << arr[i].CNIC << ",";
				f2 << arr[i].loginID << ",";
				f2 << arr[i].password << ",";
				f2 << arr[i].limit << ",";
				if (arr[i].acc_type.bronze == true)
					f2 << "bronze\n";
				else if (arr[i].acc_type.gold == true)
					f2 << "gold\n";
				else
					f2 << "business\n";
			}
			f2.close();
		}
		else
		{
			ofstream f2;
			f2.open("Account Requests.txt");
			for (int i = 0; i < 1; i++)
			{
				f2 << " ";
			}
			f2.close();
		}

	}
	void returndata_app(Company_client*& arr, int l)
	{
		if (l > 0)
		{
			ofstream f2;
			f2.open("Account Requests2.txt");
			for (int i = 0; i < l; i++)
			{
				f2 << arr[i].name << ",";

				f2 << arr[i].address << ",";
				f2 << arr[i].tax_no << ",";
				f2 << arr[i].loginID << ",";
				f2 << arr[i].password << ",";
				f2 << arr[i].limit << ",";
				if (arr[i].acc_type.bronze == true)
					f2 << "bronze\n";
				else if (arr[i].acc_type.gold == true)
					f2 << "gold\n";
				else
					f2 << "business\n";
			}
			f2.close();
		}
		else
		{
			ofstream f2;
			f2.open("Account Requests2.txt");
			for (int i = 0; i < 1; i++)
			{
				f2 << " ";
			}
			f2.close();
		}

	}
	void returndata_loan(Loan*& arr, int l)
	{
		if (l > 0)
		{
			ofstream f2;
			f2.open("Loan Requests.txt");
			for (int i = 0; i < l; i++)
			{
				f2 << arr[i].userID << ",";
				f2 << arr[i].amount << "\n";
			}
			f2.close();
		}
		else
		{
			ofstream f2;
			f2.open("Loan Requests.txt");
			for (int i = 0; i < 1; i++)
			{
				f2 << " ";
			}
			f2.close();
		}

	}
	void approvedata(User_client*& arr, int index, int& l)
	{
		if (l > 1)
		{
			User_client* arr1 = new User_client[l - 1];
			for (int i = 0, k = 0; k < l; k++)
			{
				if (k == index)
					continue;
				else
				{
					arr1[i].name = arr[k].name;
					arr1[i].phone_no = arr[k].phone_no;
					arr1[i].address = arr[k].address;
					arr1[i].CNIC = arr[k].CNIC;
					arr1[i].loginID = arr[k].loginID;
					arr1[i].password = arr[k].password;
					arr1[i].limit = arr[k].limit;
					arr1[i].acc_type.bronze = arr[k].acc_type.bronze;
					arr1[i].acc_type.gold = arr[k].acc_type.gold;
					arr1[i].acc_type.business = arr[k].acc_type.business;
					i++;
				}
			}
			delete[]arr;
			arr = arr1;
		}
		if (l == 1)
		{
			delete[]arr;
			arr = NULL;
		}
		l--;
		returndata_app(arr, l);
	}
	void approveloan(Loan*& arr, int index, int& l)
	{
		if (l > 1)
		{
			Loan* arr1 = new Loan[l - 1];
			for (int i = 0, k = 0; k < l; k++)
			{
				if (k == index)
					continue;
				else
				{
					arr1[i].userID = arr[k].userID;
					arr1[i].amount = arr[k].amount;
					i++;
				}
			}
			delete[]arr;
			arr = arr1;
		}
		if (l == 1)
		{
			delete[]arr;
			arr = NULL;
		}
		l--;
		returndata_loan(arr, l);
	}
	void approvedata(Company_client*& arr, int index, int& l)
	{
		if (l > 1)
		{
			Company_client* arr1 = new Company_client[l - 1];
			for (int i = 0, k = 0; k < l; k++)
			{
				if (k == index)
					continue;
				else
				{
					arr1[i].name = arr[k].name;
					arr1[i].address = arr[k].address;
					arr1[i].tax_no = arr[k].tax_no;
					arr1[i].loginID = arr[k].loginID;
					arr1[i].password = arr[k].password;
					arr1[i].limit = arr[k].limit;
					arr1[i].acc_type.bronze = arr[k].acc_type.bronze;
					arr1[i].acc_type.gold = arr[k].acc_type.gold;
					arr1[i].acc_type.business = arr[k].acc_type.business;
					i++;
				}
			}
			delete[]arr;
			arr = arr1;
		}
		if (l == 1)
		{
			delete[]arr;
			arr = NULL;
		}
		l--;
		returndata_app(arr, l);
	}
	void rejectdata(User_client*& arr, int index, int& l)
	{
		if (l > 1)
		{
			User_client* arr1 = new User_client[l - 1];
			for (int i = 0, k = 0; k < l; k++)
			{
				if (k == index)
					continue;
				else
				{
					arr1[i].name = arr[k].name;
					arr1[i].phone_no = arr[k].phone_no;
					arr1[i].address = arr[k].address;
					arr1[i].CNIC = arr[k].CNIC;
					arr1[i].loginID = arr[k].loginID;
					arr1[i].password = arr[k].password;
					arr1[i].limit = arr[k].limit;
					arr1[i].acc_type.bronze = arr[k].acc_type.bronze;
					arr1[i].acc_type.gold = arr[k].acc_type.gold;
					arr1[i].acc_type.business = arr[k].acc_type.business;
					i++;
				}
			}
			delete[]arr;
			arr = arr1;
		}
		if (l == 1)
		{
			delete[]arr;
			arr = NULL;
		}
		l--;
		returndata_app(arr, l);
	}
	void rejectloan(Loan*& arr, int index, int& l)
	{
		if (l > 1)
		{
			Loan* arr1 = new Loan[l - 1];
			for (int i = 0, k = 0; k < l; k++)
			{
				if (k == index)
					continue;
				else
				{
					arr1[i].userID = arr[k].userID;
					arr1[i].amount = arr[k].amount;
					i++;
				}
			}
			delete[]arr;
			arr = arr1;
		}
		if (l == 1)
		{
			delete[]arr;
			arr = NULL;
		}
		l--;
		returndata_loan(arr, l);
	}
	void rejectdata(Company_client*& arr, int index, int& l)
	{
		if (l > 1)
		{
			Company_client* arr1 = new Company_client[l - 1];
			for (int i = 0, k = 0; k < l; k++)
			{
				if (k == index)
					continue;
				else
				{
					arr1[i].name = arr[k].name;
					arr1[i].address = arr[k].address;
					arr1[i].tax_no = arr[k].tax_no;
					arr1[i].loginID = arr[k].loginID;
					arr1[i].password = arr[k].password;
					arr1[i].limit = arr[k].limit;
					arr1[i].acc_type.bronze = arr[k].acc_type.bronze;
					arr1[i].acc_type.gold = arr[k].acc_type.gold;
					arr1[i].acc_type.business = arr[k].acc_type.business;
					i++;
				}
			}
			delete[]arr;
			arr = arr1;
		}
		if (l == 1)
		{
			delete[]arr;
			arr = NULL;
		}
		l--;
		returndata_app(arr, l);
	}
	int view_account_app()
	{
		int l = loaddata_app(u_client);
		int l1 = loaddata_app(c_client);
		int choice = -1;
		cout << "Enter 1 if you want to view User client's account applications\nEnter 2 if you want to view Company client's account applications\n";
		cin >> choice;
		while (choice < 0 || choice>2)
		{
			cout << "Enter a valid number: ";
			cin >> choice;
		}
		if (choice == 1)
		{
		a:cout << "User client's accounts are following" << endl;
			for (int i = 0; i < l; i++)
			{
				cout << i + 1 << ".\n";
				cout << "\t\tUser's name: " << u_client[i].name << endl;
				cout << "\t\tUser's phone number: " << u_client[i].phone_no << endl;
				cout << "\t\tUser's address: " << u_client[i].address << endl;
				cout << "\t\tUser's CNIC: " << u_client[i].CNIC << endl;
				cout << "\t\tUser's login id: " << u_client[i].loginID << endl;
				cout << "\t\tUseris password: " << u_client[i].password << endl;
				cout << "\t\tUser's daily withdrawal limit: " << u_client[i].limit << endl;
				cout << "\t\tUser's account type: " << u_client[i].getaccount_type() << endl << endl;
			}
			int choice2 = -1;
			cout << "Enter 1 if you want to approve User client's account application\nEnter 2 if you want to reject User client's account application\n";
			cin >> choice2;
			while (choice2 < 0 || choice2>2)
			{
				cout << "Enter a valid number: ";
				cin >> choice2;
			}
			if (choice2 == 1)
			{
				system("cls");
				string n, cnic;
				cout << "Enter the name of the client: ";
				cin.ignore();
				getline(cin, n);
				cout << "Enter the CNIC of the client: ";
				getline(cin, cnic);
				int countee = searchdata(u_client, n, cnic, l);
				if (countee != -1)
				{
					User_client obj, * arr;
					int l2 = obj.loaddata(arr);
					obj.returndata(u_client, countee, l2);
					approvedata(u_client, countee, l);
					delete[]arr;
					arr = NULL;
					cout << "Your entered account has been approved!!!" << endl;
					return 0;
				}
				else
				{
					int c;
					cout << "Your entered name has not requested for an account" << endl;
					cout << "enter 1 if you want to do again: ";
					cin >> c;
					if (c == 1)
						goto a;
					else
						return 0;
				}
			}
			else
			{
				system("cls");
				string n, cnic;
				cout << "Enter the name of the client: ";
				cin.ignore();
				getline(cin, n);
				cout << "Enter the CNIC of the client: ";
				getline(cin, cnic);
				int countee = searchdata(u_client, n, cnic, l);
				if (countee != -1)
				{
					rejectdata(u_client, countee, l);
					cout << "Your entered account has been rejected!!!" << endl;
					return 0;
				}
				else
				{
					int c;
					cout << "Your entered name has not requested for an account" << endl;
					cout << "enter 1 if you want to do again: ";
					cin >> c;
					if (c == 1)
						goto a;
					else
						return 0;
				}
			}
		}
		else
		{
		a1:cout << "Company client's accounts are following" << endl;
			for (int i = 0; i < l1; i++)
			{
				cout << i + 1 << ".\n";
				cout << "\t\tCompany's name: " << c_client[i].name << endl;

				cout << "\t\tCompany's address: " << c_client[i].address << endl;
				cout << "\t\tCompany's Tax number: " << c_client[i].tax_no << endl;
				cout << "\t\tCompany's login id: " << c_client[i].loginID << endl;
				cout << "\t\tCompany's password: " << c_client[i].password << endl;
				cout << "\t\tCompany's daily withdrawal limit: " << c_client[i].limit << endl;
				cout << "\t\tCompany's account type: " << c_client[i].getaccount_type() << endl << endl;
			}
			int choice2 = -1;
			cout << "Enter 1 if you want to approve Company client's account application\nEnter 2 if you want to reject Company client's account application\n";
			cin >> choice2;
			while (choice2 < 0 || choice2>2)
			{
				cout << "Enter a valid number: ";
				cin >> choice2;
			}
			if (choice2 == 1)
			{
				system("cls");
				string name, n;
				cout << "Enter the name of the company: ";
				cin.ignore();
				getline(cin, name);
				cout << "Enter the tax number of the company: ";
				getline(cin, n);
				int countee = searchdata(c_client, name, n, l1);
				if (countee != -1)
				{
					Company_client obj, * arr;
					int l2 = obj.loaddata(arr);
					obj.returndata(c_client, countee, l2);
					approvedata(c_client, countee, l1);
					delete[]arr;
					arr = NULL;
					cout << "Your entered account has been approved!!!" << endl;
					return 0;
				}
				else
				{
					int c;
					cout << "Your entered name has not requested for an account" << endl;
					cout << "enter 1 if you want to do again: ";
					cin >> c;
					if (c == 1)
						goto a1;
					else
						return 0;
				}
			}
			else
			{
				system("cls");
				string name, n;
				cout << "Enter the name of the company: ";
				cin.ignore();
				getline(cin, name);
				cout << "Enter the Tax number of the client: ";
				getline(cin, n);
				int countee = searchdata(c_client, name, n, l1);
				if (countee != -1)
				{
					rejectdata(c_client, countee, l1);
					cout << "Your entered account has been rejected!!!" << endl;
					return 0;
				}
				else
				{
					int c;
					cout << "Your entered name has not requested for an account" << endl;
					cout << "enter 1 if you want to do again: ";
					cin >> c;
					if (c == 1)
						goto a1;
					else
						return 0;
				}
			}
		}
	}
	int view_loan_req()
	{
		int l = loaddata(loan);
	a1:cout << "Details of Loan requests are following: " << endl;
		if (l == 0)
		{
			cout << "There are no requests for loan." << endl;
			return 0;
		}
		for (int i = 0; i < l; i++)
		{
			cout << i + 1 << ".\n";
			cout << "\t\tCompany's ID: " << loan[i].userID << endl;
			cout << "\t\tRequested Amount: " << loan[i].amount << endl;
		}
		int choice2 = -1;
		cout << "Enter 1 if you want to approve Company's loan request\nEnter 2 if you want to reject Company's loan request\n";
		cin >> choice2;
		while (choice2 < 0 || choice2>2)
		{
			cout << "Enter a valid number: ";
			cin >> choice2;
		}
		if (choice2 == 1)
		{
			system("cls");
			int n;
			cout << "Enter the ID of the company: ";
			cin >> n;
			Company_client obj;
			int l1 = obj.loaddata(c_client);
			int countee = searchdata(c_client, n, l1);
			if (countee != -1)
			{
				int countee1 = searchdata(loan, n, l);
				c_client[countee].balance += loan[countee1].amount;
				obj.returndata(c_client, l1);
				approveloan(loan, countee1, l);
				cout << "Your entered account's loan request has been approved!!!" << endl;
				return 0;
			}
			else
			{
				int c;
				cout << "Your entered ID has not requested for a loan" << endl;
				cout << "enter 1 if you want to do again: ";
				cin >> c;
				if (c == 1)
					goto a1;
				else
					return 0;
			}
		}
		else
		{
			system("cls");
			int n;
			cout << "Enter the ID of the company: ";
			cin >> n;
			int countee = searchdata(loan, n, l);
			if (countee != -1)
			{
				rejectloan(loan, countee, l);
				cout << "Your entered account's loan request has been rejected!!!" << endl;
				return 0;
			}
			else
			{
				int c;
				cout << "Your entered ID has not requested for a loan" << endl;
				cout << "enter 1 if you want to do again: ";
				cin >> c;
				if (c == 1)
					goto a1;
				else
					return 0;
			}

		}
	}
	void freeze_account(User_client*& arr, int index, int& l)
	{
		if (l > 1)
		{
			User_client* arr1 = new User_client[l - 1];
			for (int i = 0, k = 0; k < l; k++)
			{
				if (k == index)
					continue;
				else
				{
					arr1[i].userID = i + 1;
					arr1[i].name = arr[k].name;
					arr1[i].phone_no = arr[k].phone_no;
					arr1[i].address = arr[k].address;
					arr1[i].CNIC = arr[k].CNIC;
					arr1[i].loginID = arr[k].loginID;
					arr1[i].password = arr[k].password;
					arr1[i].limit = arr[k].limit;
					arr1[i].acc_type.bronze = arr[k].acc_type.bronze;
					arr1[i].acc_type.gold = arr[k].acc_type.gold;
					arr1[i].acc_type.business = arr[k].acc_type.business;
					arr1[i].balance = arr[k].balance;
					i++;
				}
			}
			delete[]arr;
			arr = arr1;
		}
		if (l == 1)
		{
			delete[]arr;
			arr = NULL;
		}
		l--;
		User_client obj;
		obj.returndata(arr, l);
	}
	void freeze_account(Company_client*& arr, int index, int& l)
	{
		if (l > 1)
		{
			Company_client* arr1 = new Company_client[l - 1];
			for (int i = 0, k = 0; k < l; k++)
			{
				if (k == index)
					continue;
				else
				{
					arr1[i].userID = i + 1;
					arr1[i].name = arr[k].name;

					arr1[i].address = arr[k].address;
					arr1[i].tax_no = arr[k].tax_no;
					arr1[i].loginID = arr[k].loginID;
					arr1[i].password = arr[k].password;
					arr1[i].limit = arr[k].limit;
					arr1[i].acc_type.bronze = arr[k].acc_type.bronze;
					arr1[i].acc_type.gold = arr[k].acc_type.gold;
					arr1[i].acc_type.business = arr[k].acc_type.business;
					arr1[i].balance = arr[k].balance;
					i++;
				}
			}
			delete[]arr;
			arr = arr1;
		}
		if (l == 1)
		{
			delete[]arr;
			arr = NULL;
		}
		l--;
		Company_client obj;
		obj.returndata(arr, l);
	}
	int freeze_account()
	{
		int choice = 1;
	b: cout << "Enter 1 if you want to freeze an account of user client: " << endl;
		cout << "Enter 2 if you want to freeze an account of company client: " << endl;
		cin >> choice;
		while (choice < 1 || choice>2)
		{
			cout << "Enter a valid number: ";
			cin >> choice;
		}
		if (choice == 1)
		{
			User_client obj;
			int l = obj.loaddata(u_client);
			string id;
			cout << "Enter the id of the user client account you want to freeze or close: ";
			cin.ignore();
			getline(cin, id);
			int countee = obj.searchdata2(u_client, id, l);
			if (countee != -1)
			{
				freeze_account(u_client, countee, l);
				cout << "Your entered account has been closed successfully!!!" << endl;
				return 0;
			}
			else
			{
				int c;
				cout << "The account does not exist with the entered user id." << endl;
				cout << "Press 1 if you want to do again: ";
				cin >> c;
				system("cls");
				if (c == 1)
					goto b;
				else
					return 0;
			}
		}
		else
		{
			Company_client obj;
			int l = obj.loaddata(c_client);
			string id;
			cout << "Enter the id of the company client account you want to freeze or close: ";
			cin.ignore();
			getline(cin, id);
			int countee = obj.searchdata2(c_client, id, l);
			if (countee != -1)
			{
				freeze_account(c_client, countee, l);
				cout << "Your entered account has been closed successfully!!!" << endl;
				return 0;
			}
			else
			{
				int c;
				cout << "The account does not exist with the entered user id." << endl;
				cout << "Press 1 if you want to do again: ";
				cin >> c;
				system("cls");
				if (c == 1)
					goto b;
				else
					return 0;
			}

		}

	}
};
void company_view(Company_client*& arr, int countee, int id1, int l)
{
f:int id = id1;
	Company_client obj;
	system("cls");
	Card* tt;
	int lines = obj.card.loaddata1(tt);
	int f = obj.card.pin_check(tt, id, lines);
	if (f == 1)
	{
		int pin;
		cout << "Enter your pin number: ";
		cin >> pin;
		obj.card.setpin1(tt, id, pin, lines);
	}
	system("cls");
	int choice2;
	obj.show_menu();
	cout << "Enter your choice: ";
	cin >> choice2;
	while (choice2 < 0 || choice2>7)
	{
		cout << "Enter a valid choice: ";
		cin >> choice2;
	}
	if (choice2 == 1)
	{
		system("cls");
		obj.deposit(arr, countee, l, id, tt, lines);
		cout << "Press any key to continue: ";
		_getch();
		system("cls");
		goto f;
	}
	else if (choice2 == 2)
	{
		system("cls");
		obj.withdraw(arr, countee, l, id, tt, lines);
		cout << "Press any key to continue: ";
		_getch();
		system("cls");
		goto f;
	}
	else if (choice2 == 3)
	{
		system("cls");
		obj.viewbalance(arr, countee);
		cout << "Press any key to continue: ";
		_getch();
		goto f;
	}
	else if (choice2 == 4)
	{
		system("cls");
		Company_client* arr1;
		int l1 = obj.loaddata_trans(arr1);
		int count = obj.searchdata1(arr1, id, l1);
		if (count == 1)
		{
			obj.viewhistory(arr1, id, l1);
		}
		else
			cout << "You don't have any transaction histrory." << endl << endl;
		cout << "Press any key to continue: ";
		_getch();
		system("cls");
		goto f;
	}
	else if (choice2 == 5)
	{
		system("cls");
		obj.transfer(arr, countee, l, id, tt, lines);
		cout << "Press any key to continue: ";
		_getch();
		system("cls");
		goto f;
	}
	else if (choice2 == 6)
	{
		system("cls");
		obj.request_loan(arr, countee);
		cout << "\n\nYour loan request has been sent to  the Banking Employee." << endl;
		cout << "Press any key to continue: ";
		_getch();
		system("cls");
		goto f;
	}
	else {
		system("exit");
		delete[]tt;
		tt = NULL;
		delete[]arr;
		arr = NULL;
	}
}
int main()
{
	int choice = -1;
	cout << "************************Welcome to Bank Management System********************\n\n\n" << endl;
	cout << "Press 1 if you are a User Client\nPress 2 if you are Company Client\nPress 3 if you are Bank Employee\nPress 4 if you want to exit" << endl << endl << endl;
	cout << "Enter your choice: ";
	cin >> choice;
	while (choice < 0 || choice>4)
	{
		cout << "Enter a valid choice: ";
		cin >> choice;
	}
	if (choice == 1)
	{
		system("cls");
		cout << "************User Client Login Page*************\n\n";
		int choice1 = -1;
		cout << "Press 1 if you are a new client else press 2 for login:";
		cin >> choice1;
		while (choice1 < 0 || choice1>2)
		{
			cout << "Enter a valid choice: ";
			cin >> choice1;
		}
		if (choice1 == 1)
		{
			system("cls");
			User_client obj;
			obj.signup();
			cout << "\n\nYour account request has been sent to  the Banking Employee." << endl;
			cout << "Press any key to continue: ";
			_getch();
			system("cls");
			main();
		}
		else
		{
			User_client* arr;
			User_client obj;
			int l = obj.loaddata(arr);
			system("cls");
			cout << "Enter your login details." << endl;
			string ID, password;
			cout << "\n\nEnter your login ID: ";
			cin.ignore();
			getline(cin, ID);
			cout << "Enter your password: ";
			getline(cin, password);
			int countee = obj.searchdata(arr, ID, password, l);

			if (countee == -1)
			{
				cout << "\nThis account does not exist." << endl;
				cout << "Press any key to continue: ";
				_getch();
				system("cls");
				delete[]arr;
				arr = NULL;
				main();
			}
			else
			{
			p:int choice3 = -1;
				cout << "Enter 1 if you want to login your personal account: " << endl;
				cout << "Enter 2 if you want to login your company account: " << endl;
				cin >> choice3;
				while (choice3 < 0 || choice3>2)
				{
					cout << "Enter a valid number: ";
					cin >> choice3;
				}
				if (choice3 == 1)
				{
				e:int id = obj.getID(arr, countee);
					Card* tt;
					int lines = obj.card.loaddata(tt);
					int f = obj.card.pin_check(tt, id, lines);
					if (f == 1)
					{
						int pin;
						cout << "Enter your pin number: ";
						cin >> pin;
						obj.card.setpin(tt, id, pin, lines);
					}
					system("cls");
					int choice2;
					obj.show_menu();
					cout << "6.Exit" << endl;
					cout << "Enter your choice: ";
					cin >> choice2;
					while (choice2 < 0 || choice2>6)
					{
						cout << "Enter a valid choice: ";
						cin >> choice2;
					}
					if (choice2 == 1)
					{
						system("cls");
						obj.deposit(arr, countee, l, id, tt, lines);
						cout << "Press any key to continue: ";
						_getch();
						system("cls");
						goto e;
					}
					else if (choice2 == 2)
					{
						system("cls");
						obj.withdraw(arr, countee, l, id, tt, lines);
						cout << "Press any key to continue: ";
						_getch();
						system("cls");
						goto e;
					}
					else if (choice2 == 3)
					{
						system("cls");
						obj.viewbalance(arr, countee);
						cout << "Press any key to continue: ";
						_getch();
						system("cls");
						goto e;
					}
					else if (choice2 == 4)
					{
						system("cls");
						User_client* arr1;
						int l1 = obj.loaddata_trans(arr1);
						int count = obj.searchdata1(arr1, id, l1);
						if (count == 1)
						{
							obj.viewhistory(arr1, id, l1);
						}
						else
							cout << "You don't have any transaction histrory." << endl << endl;
						cout << "Press any key to continue: ";
						_getch();
						system("cls");
						goto e;
					}
					else if (choice2 == 5)
					{
						system("cls");
						obj.transfer(arr, countee, l, id, tt, lines);
						cout << "Press any key to continue: ";
						_getch();
						system("cls");
						goto e;
					}
					else {
						system("exit");
						delete[]arr;
						arr = NULL;
						delete[]tt;
						tt = NULL;
					}
				}
				else
				{
					int id = obj.getID(arr, countee);
					string id1 = "";
					int j = 0, lines = 0;
					string s;
					ifstream f1;
					f1.open("companies_employees.txt");
					while (getline(f1, s))
						lines++;
					f1.close();
					f1.open("companies_employees.txt");
					for (int i = 0; i < lines; i++)
					{
						getline(f1, s, ',');
						if (stoi(s) == id)
						{
							getline(f1, s, '\n');
							id1 = s;
							j = 1;
							break;
						}
						getline(f1, s, '\n');
					}
					f1.close();
					if (j == 1)
					{
						Company_client* arr1;
						Company_client obj1;
						int l1 = obj1.loaddata(arr1);
						int countee1 = obj1.searchdata2(arr1, id1, l);
						delete[]arr;
						arr = NULL;
						company_view(arr1, countee1, stoi(id1), l1);
					}
					else
					{
						cout << "You are not an employee of any company." << endl;
						cout << "Press any key to continue: ";
						_getch();
						system("cls");
						delete[]arr;
						arr = NULL;
						goto p;
					}

				}
			}
		}
	}
	else if (choice == 2)
	{
		system("cls");
		cout << "************Company Client Login Page*************\n\n";
		int choice1 = -1;
		cout << "Press 1 if you want to open a shared account for your company else press 2 for login:";
		cin >> choice1;
		while (choice1 < 0 || choice1>2)
		{
			cout << "Enter a valid choice: ";
			cin >> choice1;
		}
		if (choice1 == 1)
		{
			system("cls");
			Company_client obj;
			obj.signup();
			cout << "\n\nYour account request has been sent to  the Banking Employee." << endl;
			cout << "Press any key to continue: ";
			_getch();
			system("cls");
			main();
		}
		else
		{
			Company_client* arr;
			Company_client obj;
			int l = obj.loaddata(arr);
			system("cls");
			cout << "Enter your login details." << endl;
			string ID, password;
			cout << "\n\nEnter your login ID: ";
			cin.ignore();
			getline(cin, ID);
			cout << "Enter your password: ";
			getline(cin, password);
			int countee = obj.searchdata(arr, ID, password, l);

			if (countee == -1)
			{
				cout << "\nThis account does not exist." << endl;
				cout << "Press any key to continue: ";
				_getch();
				system("cls");
				delete[]arr;
				arr = NULL;
				main();
			}
			int id = obj.getID(arr, countee);
			company_view(arr, countee, id, l);
		}
	}
	else if (choice == 3)
	{
		system("cls");
		cout << "************ Bank Employee Login Page*************\n\n";
		Bank_employee* arr;
		Bank_employee obj;
		int l = obj.loaddata(arr);
		system("cls");
		cout << "Enter your login details." << endl;
		string ID, password;
		cout << "\n\nEnter your login ID: ";
		cin.ignore();
		getline(cin, ID);
		cout << "Enter your password: ";
		getline(cin, password);
		int countee = obj.searchdata(arr, ID, password, l);
		if (countee == -1)
		{
			cout << "\nThis account does not exist." << endl;
			cout << "Press any key to continue: ";
			_getch();
			system("cls");
			delete[]arr;
			arr = NULL;
			main();
		}
		else
		{
		g:system("cls");
			int choice2;
			obj.show_menu();
			cout << "Enter your choice: ";
			cin >> choice2;
			while (choice2 < 0 || choice2>6)
			{
				cout << "Enter a valid choice: ";
				cin >> choice2;
			}
			if (choice2 == 1)
			{
				system("cls");
				obj.viewaccounts();
				cout << "Press any key to continue: ";
				_getch();
				system("cls");
				goto g;
			}
			else if (choice2 == 2)
			{
				system("cls");
				obj.view_account_app();
				cout << "Press any key to continue: ";
				_getch();
				system("cls");
				goto g;
			}
			else if (choice2 == 3)
			{
				system("cls");
				obj.view_loan_req();
				cout << "Press any key to continue: ";
				_getch();
				system("cls");
				goto g;
			}
			else if (choice2 == 4)
			{
				system("cls");
				int choice3 = -1;
				cout << "Enter 1 if you view history of user client account's transactions: " << endl;
				cout << "Enter 2 if you view history of Company client account's transactions: " << endl;
				cin >> choice3;
				while (choice3 < 0 || choice3>2)
				{
					cout << "ENter a valid number: ";
					cin >> choice3;
				}
				if (choice3 == 1)
				{
					string id3;
				a2:cout << "ENter the id of user client whose transacations you want to see: ";
					cin.ignore();
					getline(cin, id3);
					User_client obj1;
					User_client* arr3;
					int l2 = obj1.loaddata(arr3);
					int coun = obj1.searchdata2(arr3, id3, l2);
					if (coun != -1)
					{
						int l1 = obj1.loaddata_trans(obj.u_client);
						cout << "Transaction details of user client's account are: " << endl;
						obj1.viewhistory(obj.u_client, stoi(id3), l1);
						delete[]arr3;
						arr3 = NULL;
					}
					else
					{
						cout << "Your entered user account's ID does not exist." << endl;
						cout << "Press any key to continue: ";
						_getch();
						system("cls");
						delete[]arr3;
						arr3 = NULL;
						goto a2;
					}
				}
				else
				{
					string id3;
				a3:cout << "ENter the id of company client whose transacations you want to see: ";
					cin.ignore();
					getline(cin, id3);
					Company_client obj2;
					Company_client* arr3;
					int l1 = obj2.loaddata(arr3);
					int coun = obj2.searchdata2(arr3, id3, l1);
					if (coun != -1)
					{
						int l2 = obj2.loaddata_trans(obj.c_client);
						cout << "Transaction details of Company client's accounts are: " << endl;
						obj2.viewhistory(obj.c_client, stoi(id3), l2);
						delete[]arr3;
						arr3 = NULL;
					}
					else
					{
						cout << "Your entered user account's ID does not exist." << endl;
						cout << "Press any key to continue: ";
						_getch();
						system("cls");
						delete[]arr3;
						arr3 = NULL;
						goto a3;
					}
				}
				cout << "Press any key to continue: ";
				_getch();
				system("cls");
				goto g;
			}
			else if (choice2 == 5)
			{
				system("cls");
				obj.freeze_account();
				cout << "Press any key to continue: ";
				_getch();
				system("cls");
				goto g;
			}
			else {
				system("exit");
				delete[]arr;
				arr = NULL;
			}
		}
	}
	else
	{
		system("exit");
	}
}