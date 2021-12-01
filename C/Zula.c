#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void driverLogin();
void driverSignUp();
void driverPortal();
void customerLogin();
void customerSignUp();
void customerPortal();
void AdminPortal();

typedef struct
{
    char name[30], passwd[30];
    int age, cabId;
} Driver;

typedef struct
{
    char name[30], passwd[30];
    int age, custId;
} Customer;

typedef struct
{
    Driver *driver;
    Customer *customer;
    size_t used;
    size_t size;
} Array;

Array *Drivers;
Array *Customers;

void initDriver(Array *a, size_t initialSize)
{
    a->driver = (Driver *)malloc(initialSize * sizeof(Driver));
    a->used = 0;
    a->size = initialSize;
}

void initCustomer(Array *a, size_t initialSize)
{
    a->customer = (Customer *)malloc(initialSize * sizeof(Customer));
    a->used = 0;
    a->size = initialSize;
}

void insertDriver(Array *a, Driver *element)
{
    if (a->used == a->size)
    {
        a->size += 1;
        a->driver = (Driver *)realloc(a->driver, a->size * sizeof(Driver));
    }
    a->driver[a->used++] = *element;
}

void insertCustomer(Array *a, Customer *element)
{
    if (a->used == a->size)
    {
        a->size += 1;
        a->customer = (Customer *)realloc(a->customer, a->size * sizeof(Customer));
    }
    a->customer[a->used++] = *element;
}

void freeDriver(Array *a)
{
    free(a->driver);
    a->driver = NULL;
    a->used = a->size = 0;
    free(a);
}

void freeCustomer(Array *a)
{
    free(a->customer);
    a->customer = NULL;
    a->used = a->size = 0;
    free(a);
}

void mainMenu()
{
    int option;
    printf("WELCOME TO THE ZULA !! ");
    printf("\n1.Driver Portal \n2.Customer Portal \n3.Admin Portal \n4.Exit\n");
    printf("\nChoose option : ");
    scanf("%d", &option);
    printf("This is the option %d\n", option);
    switch (option)
    {
    case 1:
        system("clear");
        printf("Driver Portal");
        driverPortal();
        break;
    case 2:
        system("clear");
        printf("Customer Portal ");
        customerPortal();
        break;
    case 3:
        system("clear");
        printf("Admin Portal ");
        AdminPortal();

        break;
    case 4:
        system("clear");
        printf("Exiting...\n");
        exit(0);
        break;
    default:
        system("clear");
        printf(" Invalid ");
        mainMenu();
    }
}

void AdminPortal()
{
    int choice;
    printf("\n1.Show Driver Records \n2.Show Customer Records \n3.Main Menu");
    printf("\nChoose option : ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        system("clear");
        printf("\nDriver Records");

        printf("\nCabId\tName\tAge");
        printf("\n-------------------");
        for (int i = 0; i < Drivers->size; i++)
        {
            printf("\n%d\t%s\t%d", Drivers->driver[i].cabId, Drivers->driver[i].name, Drivers->driver[i].age);
        }
        printf("\n");
        AdminPortal();
        break;
    case 2:
        system("clear");
        printf("\nCustomer Records");

        printf("\nCustId\tName\tAge");
        printf("\n-------------------");
        for (int i = 0; i < Customers->size; i++)
        {
            printf("\n%d\t%s\t%d", Customers->customer[i].custId, Customers->customer[i].name, Customers->customer[i].age);
        }
        printf("\n");
        AdminPortal();
        break;

    case 3:
        system("clear");
        mainMenu();
        break;
    default:
        system("clear");
        printf("Invalid");
        AdminPortal();
    }
}

void driverPortal()
{
    int choice;
    Driver newDriver;
    printf("\n1.Login \n2.SignUp \n3.Main Menu\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        driverLogin();
        break;
    case 2:
        driverSignUp();
        break;
    case 3:
        system("clear");
        mainMenu();
        break;
    default:
        printf("\nInvalid Choice");
        driverPortal();
    }
}

void driverLogin()
{
    char driverName[30], driverPasswd[30];
    int flag = 0;
    printf("\nEnter Driver Name: ");
    scanf("%s", driverName);
    for (int i = 0; i < Drivers->size; i++)
    {
        if (strcmp(Drivers->driver[i].name, driverName) == 0)
        {
            flag = 1;
            printf("\nEnter Driver Password: ");
            scanf("%s", driverPasswd);
            if (strcmp(Drivers->driver[i].passwd, driverPasswd) == 0)
            {
                system("clear");
                printf("\nDriver Login Successful");
                driverPortal();
            }
            else
            {
                system("clear");
                printf("\n Password Error");
                driverPortal();
            }
        }
    }
    if (flag == 0)
    {
        system("clear");
        printf("\nDriver Not Found");
        driverPortal();
    }
}

void driverSignUp()
{
    Driver newDriver;
    printf("\nEnter Driver Name: ");
    scanf("%s", newDriver.name);
    printf("\nEnter Driver Password: ");
    scanf("%s", newDriver.passwd);
    printf("\nEnter Driver Age: ");
    scanf("%d", &newDriver.age);
    newDriver.cabId = Drivers->used + 1;
    insertDriver(Drivers, &newDriver);
    system("clear");
    printf("\nDriver SignUp Successful");
    driverPortal();
}

void customerPortal()
{
    int choice;
    printf("\n1.Login \n2.SignUp \n3.Main Menu\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        customerLogin();
        break;
    case 2:
        customerSignUp();
        break;
    case 3:
        system("clear");
        mainMenu();
        break;
    default:
        printf("\nInvalid Choice");
        customerPortal();
    }
}

void customerLogin()
{
    char customerName[30], customerPasswd[30];
    int flag = 0;
    printf("\nEnter Customer Name: ");
    scanf("%s", customerName);
    for (int i = 0; i < Customers->size; i++)
    {
        if (strcmp(Customers->customer[i].name, customerName) == 0)
        {
            flag = 1;
            printf("\nEnter Customer Password: ");
            scanf("%s", customerPasswd);
            if (strcmp(Customers->customer[i].passwd, customerPasswd) == 0)
            {
                system("clear");
                printf("\nCustomer Login Successful");
                customerPortal();
            }
            else
            {
                system("clear");
                printf("\n Password Error");
                customerPortal();
            }
        }
    }
    if (flag == 0)
    {
        system("clear");
        printf("\nCustomer Not Found");
        customerPortal();
    }
}

void customerSignUp()
{
    Customer newCustomer;
    printf("\nEnter Customer Name: ");
    scanf("%s", newCustomer.name);
    printf("\nEnter Customer Password: ");
    scanf("%s", newCustomer.passwd);
    printf("\nEnter Customer Age: ");
    scanf("%d", &newCustomer.age);
    newCustomer.custId = Customers->used + 1;
    insertCustomer(Customers, &newCustomer);
    system("clear");
    printf("\nCustomer SignUp Successful");
    customerPortal();
}

int main()
{
    system("clear");
    Drivers = (Array *)malloc(sizeof(Array));
    Customers = (Array *)malloc(sizeof(Array));
    initDriver(Drivers, 3);
    insertDriver(Drivers, &(Driver){.name = "John", .age = 20, .cabId = 1, .passwd = "123"});
    insertDriver(Drivers, &(Driver){.name = "Jane", .age = 21, .cabId = 2, .passwd = "123"});
    insertDriver(Drivers, &(Driver){.name = "Jack", .age = 22, .cabId = 3, .passwd = "123"});
    initCustomer(Customers, 3);
    insertCustomer(Customers, &(Customer){.name = "Alpha", .passwd = "111", .age = 20, .custId = 1});
    insertCustomer(Customers, &(Customer){.name = "Beta", .passwd = "111", .age = 21, .custId = 2});
    insertCustomer(Customers, &(Customer){.name = "Gamma", .passwd = "111", .age = 22, .custId = 3});

    mainMenu();

    freeDriver(Drivers);
    freeCustomer(Customers);
    return 0;
}
