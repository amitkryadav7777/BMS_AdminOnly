#include <iostream>
#include <conio.h>
#include <fstream>
#include <istream>
#include <sstream>
#include <ctime>
#include <time.h>
#include <string>
#include <vector>
#include <thread>
#include <graphics.h>

using namespace std;

int invalid = 0;
void home();
void updateAccount(string optionData);
void title()
{
    cout << "\t\t-----------------------------------------------\n";
    cout << "\t\t\t:: Bank Management System ::" << endl;
    cout << "\t\t-----------------------------------------------\n\n";
}

void addAccount()
{
    system("cls");
    title();
    string name, dob, mobile, email, accNum, accType, amount, time, city = "";

    fstream fout;
    fstream out;
    // opens an existing csv file or creates a new file to store account holders' data.
    fout.open("accounts.csv", ios::out | ios::app);
    out.open("statements.csv", ios::out | ios::app);
    cout << "\t\tCreating an account -- \n";
    cout << "\t\tAccount Holder Name : ";
    cin.ignore();
    getline(cin, name);
    cout << "\t\tDOB (dd/mm/yyyy)    : ";
    cin >> dob;
    cout << "\t\tMobile              : ";
    cin >> mobile;
    cout << "\t\tEmail               : ";
    cin >> email;
    cout << "\t\tAccount Number      : ";
    cin >> accNum;
    cout << "\t\tAccount Type(S/C)   : ";
    cin >> accType;
    cout << "\t\tAmount to Deposit   : ";
    cin >> amount;
    cout << "\t\tCity                : ";
    cin.ignore();
    getline(cin, city);
    // Insert the data to file
    fout << name << ","
         << dob << ","
         << mobile << ","
         << email << ","
         << accNum << ","
         << accType << ","
         << city
         << "\n";

    time_t t;
    struct tm *tm;
    char Date[30];
    std::time(&t);
    tm = localtime(&t);
    strftime(Date, sizeof Date, "%x %X", tm);

    time = Date;
    out << accNum << ","
        << "Cr" << ","
        << time << ","
        << amount << ","
        << amount
        << "\n";

    cout << "\t\tAccount successfully created." << endl;
    fout.close();
    out.close();
    delay(1000);
    home();
    return;
}

void update(string accNum, int option){
    fstream fout;
    // opens an existing csv file or creates a new file to store account holders' data.
    fout.open("accounts.csv", ios::in | ios::out);
    if (fout.fail())
    {
        cout << "\n\t\tError opening the file" << endl;
        delay(1000);
        home();
        return;
    }

    vector<string> lines;
    string line;

    char delimiter = ',';
    std::string item;
    std::vector<std::string> row;
    while (std::getline(fout, line))
    {

        row.clear();
        std::stringstream string_stream(line);
        while (std::getline(string_stream, item, delimiter))
        {
            row.push_back(item);
        }
        if (row[4] == accNum)
        {
            line = "";
            string newData;
            switch (option){
                case 1 :
                    cout << "\n\t\tEnter New Name : ";
                    cin.ignore();
                    getline(cin, newData);
                    row[0] = newData;
                    break;
                case 2 :
                    cout << "\n\t\tEnter New DOB : ";
                    cin.ignore();
                    getline(cin, newData);
                    row[1] = newData;
                    break;
                case 3 :
                    cout << "\n\t\tEnter New Mobile : ";
                    cin >> newData;
                    row[2] = newData;
                    break;
                case 4 :
                    cout << "\n\t\tEnter New Email : ";
                    cin >> newData;
                    row[3] = newData;
                    break;
                case 5 :
                    cout << "\n\t\tEnter New City : ";
                    cin.ignore();
                    getline(cin, newData);
                    row[6] = newData;
                    break;
                default :
                    cout << "\n\t\tInvalid option";
                    break;
            }

            for(int i = 0; i < row.size(); i++){
                line.append(row[i]);
                if(i != row.size()-1 ){
                    line.push_back(',');
                }
            }
            lines.push_back(line);
        }
        else{
            lines.push_back(line);
        }
    }
    fout.close();

        fstream fin;
        fin.open("accounts.csv", ios::out);
        for (string l : lines)
        {
            fin << l << "\n";
        }
        fin.close();
        cout << "\n\t\tAccount successfully updated!";

    delay(1000);
    updateAccount(accNum);
    return;
}

void updateAccount(string updateAccNum)
{
    system("cls");
    title();
    
    string accNum = updateAccNum;
    bool accPresent = false;

    fstream file;
    // opens an existing csv file or creates a new file to store account holders' data.
    file.open("accounts.csv", ios::out | ios::app | ios::in);
    // std::ifstream file("statements.csv");
    while (file.eof() == 0)
    {
        char delimiter = ',';
        std::string line;
        std::string item;
        // std::ifstream file("statements.csv");
        std::vector<std::string> row;
        while (std::getline(file, line))
        {

            row.clear();
            std::stringstream string_stream(line);
            while (std::getline(string_stream, item, delimiter))
            {
                row.push_back(item);
            }
            if (row[4] == accNum)
            {
                accPresent = true;
                cout << "\n\t\tAccount No       : " << row[4] << 
                        "\n\t\tAccount Type     : " << row[5] << "\n" << 
                        "\n\t\t1. Name          : " << row[0] << 
                        "\n\t\t2. DOB(dd/mm/yy) : " << row[1] << 
                        "\n\t\t3. Mobile        : " << row[2] << 
                        "\n\t\t4. Email         : " << row[3] << 
                        "\n\t\t5. City          : " << row[6] << endl;
            }
        }
    }
    file.close();
    if (!accPresent)
    {
        cout << "\n\n\t\tInvalid account number..." << endl;
        delay(1000);
    }
    else
    {
        int option;
        cout << "\n\t\tSelect an option to update that detatil or 0 to exit :  ";
        cin >> option;
        if(option == 0){
            home();
            return;
        }
        update(accNum,option);
        updateAccount(accNum);
    }
    home();
    return;
}
void depositAmount(string depositAccNum)
{
    system("cls");
    title();
    cout << "\t\tEnter details to deposit the money-\n";
    string time, amount, balance;
    string accNum = depositAccNum;
    bool accPresent = false;
    long int finalBalance;
    cout << "\t\tEnter amount to deposit : ";
    cin >> amount;

    string trans = "Cr";
    fstream file;
    // opens an existing csv file or creates a new file to store account holders' data.
    file.open("statements.csv", ios::out | ios::app | ios::in);
    // std::ifstream file("statements.csv");
    while (file.eof() == 0)
    {
        char delimiter = ',';
        std::string line;
        std::string item;
        // std::ifstream file("statements.csv");
        std::vector<std::string> row;
        while (std::getline(file, line))
        {

            row.clear();
            std::stringstream string_stream(line);
            while (std::getline(string_stream, item, delimiter))
            {
                row.push_back(item);
            }
            if (row[0] == accNum)
            {
                accPresent = true;
                balance = row[4];
            }
        }
    }
    file.close();
    fstream file1;
    file1.open("statements.csv", ios::out | ios::app);

    time_t t;
    struct tm *tm;
    char Date[30];
    std::time(&t);
    tm = localtime(&t);
    strftime(Date, sizeof Date, "%x %X", tm);

    time = Date;
    if (!accPresent)
    {
        cout << "\n\n\t\tInvalid account number..." << endl;
        delay(1000);
    }
    else
    {
        finalBalance = stoi(balance) + stoi(amount);
        file1 << accNum << ","
              << trans << ","
              << time << ","
              << amount << ","
              << finalBalance
              << "\n";
        // fout.close();
        file1.close();
        cout << "\n\t\tAmount deposited.";
        delay(1000);
    }
    home();
    return;
}
void withdrawalAmount(string withdrawalAccNum)
{
    system("cls");
    title();
    cout << "\t\tEnter details to withdrawal the money-\n";
    string accNum, time, amount, balance;
    accNum = withdrawalAccNum;
    bool accPresent = false;
    long int finalBalance;
    cout << "\t\tEnter amount to withdrawal : ";
    cin >> amount;

    string trans = "Dr";
    fstream file;
    // opens an existing csv file or creates a new file to store account holders' data.
    file.open("statements.csv", ios::out | ios::app | ios::in);
    // std::ifstream file("statements.csv");
    while (file.eof() == 0)
    {
        char delimiter = ',';
        std::string line;
        std::string item;
        // std::ifstream file("statements.csv");
        std::vector<std::string> row;
        while (std::getline(file, line))
        {

            row.clear();
            std::stringstream string_stream(line);
            while (std::getline(string_stream, item, delimiter))
            {
                row.push_back(item);
            }
            if (row[0] == accNum)
            {
                accPresent = true;
                balance = row[4];
            }
        }
    }
    file.close();
    fstream file1;
    file1.open("statements.csv", ios::out | ios::app);

    time_t t;
    struct tm *tm;
    char Date[30];
    std::time(&t);
    tm = localtime(&t);
    strftime(Date, sizeof Date, "%x %X", tm);

    time = Date;
    if (!accPresent)
    {
        cout << "\n\n\t\tInvalid account number..." << endl;
        delay(1000);
    }
    else
    {
        finalBalance = stoi(balance) - stoi(amount);
        if (finalBalance < 0)
        {
            cout << "\n\n\t\tNot enough balance to withdrawal...";
        }
        else
        {
            file1 << accNum << ","
                  << trans << ","
                  << time << ","
                  << amount << ","
                  << finalBalance
                  << "\n";
            // fout.close();
            file1.close();
            cout << "\n\t\tAmount withdrawaled.";
        }
        delay(1000);
    }
    home();
    return;
}
void balanceInqiry(string inquiryAccNum)
{
    system("cls");
    title();
    string accNum, balance;
    accNum = inquiryAccNum;
    cout << "\t\tAccount number : " << accNum << "\n";
    bool accPresent = false;
    long int finalBalance;

    fstream file;
    // opens an existing csv file or creates a new file to store account holders' data.
    file.open("statements.csv", ios::out | ios::app | ios::in);
    // std::ifstream file("statements.csv");
    while (file.eof() == 0)
    {
        char delimiter = ',';
        std::string line;
        std::string item;
        // std::ifstream file("statements.csv");
        std::vector<std::string> row;
        while (std::getline(file, line))
        {

            row.clear();
            std::stringstream string_stream(line);
            while (std::getline(string_stream, item, delimiter))
            {
                row.push_back(item);
            }
            if (row[0] == accNum)
            {
                accPresent = true;
                balance = row[4];
            }
        }
    }
    file.close();
    if (accPresent)
    {
        cout << "\n\n\t\tBalance is : " << balance << endl;
        string back;
        cout << "\n\t\tPress any key to exit... ";
        cin >> back;
    }
    else
    {
        cout << "\n\n\t\tInvalid account number..." << endl;
    }
    delay(1500);
    home();
    return;
}
void passStatement(string statAccNum)
{
    system("cls");
    title();
    string accNum, balance;
    accNum = statAccNum;
    cout << "\t\tAccount number : " << accNum << "\n";
    bool accPresent = false;
    long int finalBalance;

    fstream file;
    // opens an existing csv file or creates a new file to store account holders' data.
    file.open("statements.csv", ios::out | ios::app | ios::in);
    // std::ifstream file("statements.csv");
    cout << "\n\t\tA/C No\tCr./Dr.\tDate & Time\t\tAmount\tBalance" << endl;
    while (file.eof() == 0)
    {
        char delimiter = ',';
        std::string line;
        std::string item;
        // std::ifstream file("statements.csv");
        std::vector<std::string> row;
        while (std::getline(file, line))
        {

            row.clear();
            std::stringstream string_stream(line);
            while (std::getline(string_stream, item, delimiter))
            {
                row.push_back(item);
            }
            if (row[0] == accNum)
            {
                accPresent = true;
                cout << "\t\t" << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t" << row[4] << endl;
            }
        }
    }
    file.close();
    if (!accPresent)
    {
        cout << "\n\n\t\tInvalid account number..." << endl;
        delay(1000);
    }
    else
    {
        string back;
        cout << "\n\t\tPress any key to exit... ";
        cin >> back;
    }
    home();
    return;
}
void deleteAccount(string deleteAccNum)
{
    system("cls");
    title();
    fstream fout;
    // opens an existing csv file or creates a new file to store account holders' data.
    fout.open("accounts.csv", ios::in | ios::out);
    if (fout.fail())
    {
        cout << "\n\t\tError opening the file" << endl;
        delay(1000);
        home();
        return;
    }
    bool accPresent = false;
    string accNum = deleteAccNum;
    vector<string> lines;
    string line;
    // while(getline(fout, line)){

    char delimiter = ',';
    std::string item;
    std::vector<std::string> row;
    while (std::getline(fout, line))
    {

        row.clear();
        std::stringstream string_stream(line);
        while (std::getline(string_stream, item, delimiter))
        {
            row.push_back(item);
        }
        if (row[4] == accNum)
        {
            accPresent = true;
            continue;
        }
        lines.push_back(line);
    }
    fout.close();
    if (!accPresent)
    {
        cout << "\n\t\tAccount doesn't exist.\n";
    }
    else
    {
        fstream fin;
        fin.open("accounts.csv", ios::out);
        for (string l : lines)
        {
            fin << l << "\n";
        }
        fin.close();
        cout << "\n\t\tAccount successfully deleted!";
    }
    // }

    delay(1000);
    home();
    return;
}
int login()
{

    string username, password;
    if (invalid)
    {
        cout << "\t\tInvalid credentials\n\n";
    }
    else
    {
        cout << "\t\tPlease enter your credentials to login-\n";
    }

    cout << "\t\tEnter username : ";
    cin >> username;
    cout << "\t\tEnter password : ";
    cin >> password;

    char delimiter = ',';
    std::string line;
    std::string item;
    std::ifstream file("login.csv");
    std::vector<std::string> row;
    while (std::getline(file, line))
    {
        std::stringstream string_stream(line);
        while (std::getline(string_stream, item, delimiter))
        {
            row.push_back(item);
        }
    }
    if (username == row[0] && password == row[1])
    {
        cout << "\t\tYou have successfully logged in!\n"
             << endl;
        delay(1000);
        file.close();
        return 1;
    }
    else
    {
        cout << "\n\t\tInvalid credentials.\n"
             << endl;
        file.close();
        invalid = 1;
        system("cls");
        title();
        login();
    }
    file.close();
}
void home()
{
    int option = 0;
    system("cls");
    title();

    cout << "\t\t1. Add New Account\n";
    cout << "\t\t2. Update Account\n";
    cout << "\t\t3. Deposit Amount\n";
    cout << "\t\t4. Withdrawal Amount\n";
    cout << "\t\t5. Balance Inquiry\n";
    cout << "\t\t6. Passbook Statement\n";
    cout << "\t\t7. Delete Account\n";
    cout << "\t\t8. Logout & Exit\n";
    cout << "\t\tEnter your choice : ";
    cin >> option;
    string optionData;
    switch (option)
    {
    case 1:
        addAccount();
        break;
    case 2:
        cout << "\n\t\tEnter account number to update detail..: ";
        cin >> optionData;
        updateAccount(optionData);
        break;
    case 3:
        cout << "\n\t\tEnter account number to deposit amount.. : ";
        cin >> optionData;
        depositAmount(optionData);
        break;
    case 4:
        cout << "\n\t\tEnter account number to withdrawal amount.. : ";
        cin >> optionData;
        withdrawalAmount(optionData);
        break;
    case 5:
        cout << "\n\t\tEnter account number to check balance... : ";
        cin >> optionData;
        balanceInqiry(optionData);
        break;
    case 6:
        cout << "\n\t\tEnter account number to see Passbook statement : ";
        cin >> optionData;
        passStatement(optionData);
        break;
    case 7:
        cout << "\n\t\tEnter account number to delete account : ";
        cin >> optionData;
        deleteAccount(optionData);
        break;
    case 8:
        cout << "\n\t\tThank You...";
        return;
    }
    return;
}

int main()
{
    int session = 0;
    fstream flogin;
    flogin.open("login.csv", ios::out | ios::app); // Creating CSV file for authentication

    title();

    if (!session)
    {
        session = login();
    }

    if (session)
    {
        home();
    }
    return 0;
}