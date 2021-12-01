#include <iostream>
#include <list>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

void menu();
void customerPortal();
void customerLogin(string cUsername = "", string cPasswd = "");
void customerSignup();
int nearbyCab(string src);

class Trips;
class Driver;
class Customer;

map<char, int> Locations = {
    {'A', 0}, {'C', 4}, {'D', 7}, {'F', 9}, {'B', 15}, {'G', 18}, {'H', 20}, {'E', 23}};

//Drivers Section

class Trips
{
public:
    int custId, fare, zCommission;
    char source, destination;
    Trips(int customer, char src, char dest)
    {
        custId = customer;
        source = src;
        destination = dest;
        fare = 10 * abs(Locations[source] - Locations[destination]);

        zCommission = fare * 0.3;
    }

    void details()
    {
        cout
            << left << setw(8)
            << source
            << left
            << setw(13)
            << destination
            << left
            << setw(10)
            << custId
            << left
            << setw(7)
            << fare
            << left
            << setw(7)
            << zCommission
            << endl;
    }
};

class Driver
{
protected:
    static int nextId;

public:
    string dName, dPasswd;
    char dLocation;
    int dAge, id;
    list<Trips> dTrips;
    Driver(string name, string passwd, int age, char location, list<Trips> trips = {}) : id(nextId++)
    {
        dName = name;
        dPasswd = passwd;
        dAge = age;
        dLocation = location;
        dTrips = trips;
    }

    void showRecords()
    {
        if (dTrips.empty())
        {
            cout << " NO RECORDS FOUND !!" << endl;
        }
        else
        {
            cout
                << left << setw(8)
                << "Source"
                << left
                << setw(13)
                << "Destination"
                << left
                << setw(10)
                << "Cust ID"
                << left
                << setw(7)
                << "Fare"
                << left
                << setw(7)
                << "Zcomm"
                << endl;
            for (list<Trips>::iterator it = dTrips.begin(); it != dTrips.end(); ++it)
            {
                it->details();
            }
        }
    }
};

int Driver::nextId = 0;

Driver driver1("aaa", "111", 25, 'D', {Trips(4, 'D', 'H'), Trips(2, 'E', 'G')});
Driver driver2("bbb", "222", 36, 'G');
Driver driver3("ccc", "333", 31, 'H');
Driver driver4("ddd", "444", 28, 'A');
Driver drivers[] = {driver1, driver2, driver3, driver4};

void driverPortal(string dUsername = "", string dPasswd = "")
{
    if (dUsername.empty() || dPasswd.empty())
    {
        cout << "Enter the username " << endl;
        cin >> dUsername;
        cout << "Enter the password " << endl;
        cin >> dPasswd;
        system("clear");
    }
    bool exist = false;
    for (int i = 0; i < 4; i++)
    {
        if (dUsername == drivers[i].dName)
        {
            if (dPasswd == drivers[i].dPasswd)
            {
                cout << "Logged in" << endl;
                cout << "1.Show Records \n2.Main Menu \n3.Exit \nChoose Option: " << endl;
                int option;
                cin >> option;
                switch (option)
                {
                case 1:
                    system("clear");
                    drivers[i].showRecords();
                    cout << endl;
                    driverPortal(dUsername, dPasswd);

                    break;
                case 2:
                    system("clear");
                    menu();
                    break;
                case 3:
                    exit(0);
                    break;

                default:
                    system("clear");
                    cout << "* Invalid Option * \n"
                         << endl;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore();
                    }
                    driverPortal(dUsername, dPasswd);
                }
            }
            else
            {
                cout << "Password Error" << endl;
                driverPortal();
            }
            exist = true;
            break;
        }
    }
    if (!(exist))
    {
        cout << "User Not Found " << endl;
        driverPortal();
    }
}

// CUSTOMER SECTION

class Rides
{
public:
    int cabId, fare;
    char source, destination;
    Rides(int driver, char src, char dest)
    {
        cabId = driver;
        source = src;
        destination = dest;
        fare = 10 * abs(Locations[source] - Locations[destination]);
    }

    void details()
    {
        cout
            << left << setw(8)
            << source
            << left
            << setw(13)
            << destination
            << left
            << setw(10)
            << cabId
            << left
            << setw(7)
            << fare
            << left

            << endl;
    }
};

class Customer
{
protected:
    static int nextId;

public:
    string cName, cPasswd;
    int cAge, id;
    list<Rides> cRides;
    Customer(string name, string passwd, int age, list<Rides> rides = {}) : id(nextId++)
    {
        cName = name;
        cAge = age;
        cPasswd = passwd;
        cRides = rides;
    }

    void rideAdd(Rides r)
    {
        cRides.push_back(r);
    }

    void RideHistory()
    {
        if (cRides.empty())
        {
            cout << " NO RECORDS FOUND !!" << endl;
        }
        else
        {
            cout
                << left << setw(8)
                << "Source"
                << left
                << setw(13)
                << "Destination"
                << left
                << setw(10)
                << "CAB ID"
                << left
                << setw(7)
                << "Fare"
                << left
                << endl;
            for (list<Rides>::iterator it = cRides.begin(); it != cRides.end(); ++it)
            {
                it->details();
            }
        }
    }
};
int Customer::nextId = 0;

Customer cust1("ww", "55", 25);
Customer cust2("xx", "66", 36);
Customer cust3("yy", "77", 31);
list<Customer> customers = {cust1, cust2, cust3};

int nearbyCab(char src)
{
    int l[4];
    for (int i = 0; i < 4; i++)
    {
        l[i] = abs(Locations[src] - Locations[drivers[i].dLocation]);
        cout << l[i] << endl;
    }
    int n = sizeof(l) / sizeof(l[0]);
    auto itr = find(l, l + n, *min_element(l, l + n));
    return distance(l, itr) + 1;
}

void customerPortal()
{
    int options;
    cout << "1.Login \n2.Signup \n3.Exit \nChoose the Option: ";
    cin >> options;
    switch (options)
    {
    case 1:
        system("clear");
        customerLogin();
        break;

    case 2:
        customerSignup();
        break;

    case 3:
        exit(0);

    default:
        system("clear");
        cout << "* Invalid Option * \n"
             << endl;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
        }
        customerPortal();
    }
}

void customerSignup()
{
    string username, passwd;
    int age;
    cout << "Enter the username : ";
    cin >> username;
    for (list<Customer>::iterator i = customers.begin(); i != customers.end(); i++)
    {
        if (username == i->cName)
        {
            system("clear");
            cout << " Username Already Taken . Try different username " << endl;
            customerSignup();
            exit(0);
        }
    }
    cout << "Enter the Password : ";
    cin >> passwd;
    cout << "Enter the age : ";
    cin >> age;
    customers.push_back(Customer(username, passwd, age));
    system("clear");
    cout << " USER CREATED " << endl;
    customerLogin(username, passwd);
}

void customerLogin(string cUsername, string cPasswd)
{
    if (cUsername.empty() || cPasswd.empty())
    {
        cout << "Enter the username " << endl;
        cin >> cUsername;
        cout << "Enter the password " << endl;
        cin >> cPasswd;
        system("clear");
    }
    bool exist = false;
    for (list<Customer>::iterator i = customers.begin(); i != customers.end(); i++)
    {
        if (cUsername == i->cName)
        {
            if (cPasswd == i->cPasswd)
            {
                cout << "Logged in" << endl;
                cout << "1.Book Ride \n2.Ride History \n3.Main Menu \nChoose Option: " << endl;
                int option, customerID;
                cin >> option;
                for (list<Customer>::iterator i = customers.begin(); i != customers.end(); i++)
                {
                    if (cUsername == i->cName)
                    {
                        customerID = i->id;
                        break;
                    }
                }
                switch (option)
                {
                case 1:
                {
                    char source, destination;
                    int fare, confrm;
                    cout << "Available Locations : ";
                    for (map<char, int>::iterator i = Locations.begin(); i != Locations.end(); i++)
                    {
                        cout << i->first << " ";
                    }
                    cout << "\nEnter the source : ";
                    cin >> source;
                    cout << "Enter the destination : ";
                    cin >> destination;
                    if (source == destination)
                    {
                        system("clear");
                        cout << " Source and Destination shouldn't be same " << endl;
                        customerLogin(cUsername, cPasswd);
                    }
                    else
                    {
                        fare = 10 * abs(Locations[source] - Locations[destination]);
                        cout << "Total fair price : " << fare << endl;
                        cout << "Confirm booking (1 - YES / 0 - NO) : ";
                        cin >> confrm;
                        if (confrm)
                        {
                            int cabID = nearbyCab(source);
                            system("clear");
                            cout << " * CAB ID - " << cabID << " Booked * \n"
                                 << endl;

                            drivers[cabID - 1].dTrips.push_back(Trips(customerID + 1, source, destination));
                            list<Customer>::iterator its = customers.begin();
                            advance(its, customerID);
                            its->rideAdd(Rides(cabID, source, destination));
                            customerLogin(cUsername, cPasswd);
                        }
                        else
                        {
                            system("clear");
                            cout << " * Booking Canceled * " << endl;
                            customerLogin(cUsername, cPasswd);
                        }
                    }
                    break;
                }
                case 2:
                {
                    system("clear");
                    list<Customer>::iterator itss = customers.begin();
                    advance(itss, customerID);
                    itss->RideHistory();
                    cout << endl;
                    customerLogin(cUsername, cPasswd);
                    break;
                }
                case 3:
                    system("clear");
                    menu();
                    break;

                default:
                    system("clear");
                    cout << "* Invalid Option * \n"
                         << endl;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore();
                    }
                    customerLogin(cUsername, cPasswd);
                }
            }
            else
            {
                cout << "Password Error" << endl;
                customerLogin();
            }
            exist = true;
            break;
        }
    }
    if (!(exist))
    {
        cout << "User Not Found " << endl;
        customerLogin();
    }
}

//admin section

void adminPortal()
{
    int cabid;
    cout << "Enter the cab id : ";
    cin >> cabid;
    cout << "Total number of trips : " << drivers[cabid - 1].dTrips.size() << endl;
    int totlF = 0, zC = 0;
    for (list<Trips>::iterator it = drivers[cabid - 1].dTrips.begin(); it != drivers[cabid - 1].dTrips.end(); ++it)
    {

        totlF = totlF + it->fare;
        zC = zC + it->zCommission;
    }
    cout << "Total Fare Collected : " << totlF << endl;
    cout << "Total Zula Commission : " << zC << endl;
    cout << "Trip Details :" << endl;
    drivers[cabid - 1].showRecords();
    int opt;
    cout << "\n1.Main Menu \n2.exit \nChoose Option: ";
    cin >> opt;
    switch (opt)
    {
    case 1:
    system("clear");
        menu();
        break;
    case 2:
    system("clear");
     cout<<"Exiting \n";
        exit(0); 

    default:
    system("clear");
                    cout << "* Invalid Option * \n"
                         << endl;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore();
                    }
                   menu();
        break;
    }
}

void menu()
{
    int service;
    cout << "Welcome to ZULA !! \n";
    cout << "1.Cab driver login\n2.Customer login\n3.Admistration login\n4.Quit \n";
    cout << "Please Choose Service : ";
    cin >> service;
    switch (service)
    {
    case 1:
        system("clear");
        driverPortal();
        break;
    case 2:
        system("clear");
        customerPortal();
        break;
    case 3:
        system("clear");
        adminPortal();
        break;
    case 4:
        cout << "Exiting" << endl;
        break;
    default:
        system("clear");
        cout << "* Invalid Option * \n"
             << endl;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
        }
        menu();
    }
}
int main()
{
    system("clear");
    menu();
    return 0;
}