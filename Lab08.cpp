#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
struct clientData {
    int accountNumber;
    char lastName[16];
    char firstName[11];
    float balance;
};
void create()
{
    fstream fails;
    clientData blankClient = { 0, "", "", 0.0 };
    fails.open("credit.dat", ios::out | ios::binary);
    for (int i = 1; i <= 100; i++)
        fails.write((char*)&blankClient, sizeof(clientData));
    fails.close();
}
void fill()
{
    clientData client;
    fstream fails;
    fails.open("credit.dat", ios::in | ios::out | ios::binary);
    cout << "\nEnter account number (1 to 100, or press 0 to end input)" << endl;
    cin >> client.accountNumber;
    while (client.accountNumber != 0)
    {
        cout << "Enter last name, first name, balance" << endl;
        cin >> client.lastName >> client.firstName >> client.balance;
        fails.seekp((client.accountNumber - 1) * sizeof(clientData), ios::beg);
        fails.write((char*)&client, sizeof(clientData));
        cout << "Enter account number or press 0 to exit" << endl;
        cin >> client.accountNumber;
    }
    fails.close();
}
void read()
{
    clientData client;
    fstream fails;
    fails.open("credit.dat", ios::in | ios::binary);
    cout << setw(10) << "Account" << setw(10) << "Lastname" << setw(10) << "Firstname" << setw(10) <<
        "Balance" << endl;
    fails.read((char*)&client, sizeof(clientData));
    while (fails)
    {
        if (client.accountNumber != 0)
            cout << setw(10) << client.accountNumber << setw(10) << client.lastName << setw(10) <<
            client.firstName << setw(10) << client.balance << endl;
        fails.read((char*)&client, sizeof(clientData));
    }
    fails.close();
}
int main()
{
    int x = 0;
    while (x != 4)
    {
        cout << "\t\nPlease input an option 1-4:\n\n";
        cout << "1 - Create new file" << endl;
        cout << "2 - Write/Update records" << endl;
        cout << "3 - Print out all records" << endl;
        cout << "4 - Exit program" << endl;
        cin >> x;
        switch (x)
        {
        case 1:
            create();
            break;
        case 2:
            fill();
            break;
        case 3:
            read();
            break;
        case 4:
            cout << "Have a great day!\n";
            break;
        default:
            cout << "Wrong input, try again!" << endl;
            break;
        }
    }
    system("Pause");
    return 0;
}