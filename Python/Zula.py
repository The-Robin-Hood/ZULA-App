#Locations 
Locations = {'A':0,'C':4,'D':7,'F':9,'B':15,'G':18,'H':20,'E':23}
class Database:
    def __init__(self,name,data):
        self.name = name
        self.data = data

    def add(self,data):
        self.data.append(data)
    
    def user (self,user):
        for data in self.data:
            if data.name == user:
                return data
        
    def info(self):
        info = {}
        for i in self.data :
            info [i.name]= i.pswd
        return info
    
    def iD(self,id):
        for i in self.data:
            if i.id == id:
                return i
    

class Customer:
    class Rides:
        def __init__(self,cabId,source,destination):
            self.cabId = cabId
            self.source =source
            self.destination=destination
            self.fare = abs(Locations[destination] - Locations[source]) *10
        
        def rideDetails(self):
            print("{:<7} {:<13} {:<13} {:<9} ".format(self.source,self.destination,self.cabId,self.fare))
    id = 1


    def __init__(self,name,pswd,age,rides=[]):
        self.id = Customer.id
        self.name = name
        self.pswd = pswd
        self.age = age 
        self.rides = rides
        Customer.id +=1

    def details(self):
        print(f'{self.id}   {self.name}    {self.pswd}    {self.age}')
    
    def rideAdd(self,cabId,source,destination):
        self.rides.append(self.Rides(cabId,source,destination))
    
    def rideHistory(self):
        if self.rides:
            print ("{:<7} {:<13} {:<13} {:<5} ".format('Source','Destination','Cab-ID','Fare'))
            for i in self.rides:
                i.rideDetails()
        else:
            print('\nNo Records Found')






class Drivers:
    class Trips:
        def __init__(self,customerId,source,destination):
            self.customerId = customerId
            self.source =source
            self.destination=destination
            self.fare = abs(Locations[destination] - Locations[source]) *10
            self.ZCommission = self.fare * 0.3
        
        def tripDetails(self):
            print("{:<7} {:<13} {:<13} {:<9} {:<5}".format(self.source,self.destination,self.customerId,self.fare,self.ZCommission))

            
    id = 1
    def __init__(self,name,pswd,age,location,trips = []):
        self.id = Drivers.id
        self.name = name
        self.pswd = pswd
        self.age = age 
        self.location = location
        self.trips =[]
        if trips:
            for trip in trips:
                self.trips.append(self.Trips( *trip))
        Drivers.id +=1
    
    def details(self):
        if self.id == 1:
            print ("{:<5} {:<5} {:<10} {:<5} {:<5}".format('ID','Name','Password','Age','Location'))
        print ("{:<5} {:<5} {:<10} {:<7} {:<5}".format(self.id,self.name,self.pswd,self.age,self.location))
    
    def tripsInfo(self):
        if self.trips:
            print ("{:<7} {:<13} {:<13} {:<5} {:<5}".format('Source','Destination','Customer-ID','Fare','ZULA Commission'))
            for i in self.trips:
                i.tripDetails()
        else:
            print('\nNo Records Found')
    
    def tripadd(self,source,destination,customerId):
        self.trips.append(self.Trips(customerId,source,destination))

#Customers
ww = Customer('ww', 55,25)
xx = Customer('xx', 66,36)
yy = Customer('yy', 77,31)

#Drivers
aaa= Drivers('aaa',111,25,'D',[(4,'D','H'),(2,'E','G'),(2,'C','B')])
bbb=Drivers('bbb',222,36,'G')
ccc =Drivers('ccc',333,31,'H')
ddd= Drivers('ddd',444,28,'A')


CustomerDB =Database('Customer',[ww,xx,yy])
DriversDB = Database('Drivers',[aaa,bbb,ccc,ddd])


def clrscr():
    import os 
    os.system('cls')


def driver_Portal(username = None , password =None):
    def derror():
        print('1.Driver Login \n2.Main Menu ')
        choice = int(input("Choose option : "))
        if choice ==1:
            driver_Portal()
        elif choice == 2:
            clrscr()
            main()
            quit()
        else:
            clrscr()
            print('Enter Appropriate value')
            main()
            quit()

    if username==None and password == None:
        username = input("\nEnter the username: ")
        password = int(input("Enter the password: " ))
    if username in DriversDB.info().keys():
        if password == DriversDB.info()[username]:
            clrscr()
            print('Driver Logged In \n')
            opt = int(input("1.Show Records \n2.Main Menu \n3.Exit \nChoose Option: "))
            if opt ==1:
                DriversDB.user(username).tripsInfo()
                input()
                driver_Portal(username,password)
            elif opt == 2:
                main()
                quit()
            else:
                quit()
        else:
            clrscr()
            print("Invalid password")
            derror()
            quit()

    else:
        clrscr()
        print('Invalid Username !!')
        derror()
        quit()

def customer_Portal():
    def nearby_Drivers(source):
        l=[]
        for i in DriversDB.data:
            l.append(abs(Locations[source]-Locations[i.location]))
        v = l.index(min(l))+1
        return v


    def customer_Login(username= None,password=None): #Customer Login
        if username == None:
            username = input("\nEnter the username: ")
            password = int(input("Enter the password: " ))
        if username in CustomerDB.info().keys():
            if password == CustomerDB.info()[username]:
                clrscr()
                print("1.Book ride \n2.Ride History  \n3.Main Menu")
                Options = int(input("Choose an option : "))
                if (Options == 1):
                    print("Locations : ", end=' ')
                    for i in Locations:
                        print(i,end = ' ')
                    source = input("\nEnter current location : ")
                    destination = input("Enter drop location : ")
                    if (source == destination):
                        clrscr()
                        print("Source and destination shouldn't be same")
                        customer_Login(username,password)
                        quit()
                    Fare = 10*(Locations[destination]-Locations[source])
                    print("Total Fare Price : ",abs(Fare))
                    cnf = int(input('Confirm Ride (1 - YES/0 - NO)'))
                    if cnf:
                        cab = nearby_Drivers(source)
                        print("Booking confirmed - Cab id ",cab)
                        DriversDB.iD(cab).tripadd(source,destination,CustomerDB.user(username).id)
                        DriversDB.iD(cab).location = destination
                        CustomerDB.user(username).rideAdd(cab,source,destination)

                        print("1.Main menu \n2.Exit")
                        cho = int(input('Choose Option : '))
                        if cho == 1:
                            main()
                        else:
                            print("Exiting")
                            quit()
                    else:
                        customer_Login(username,password)

                elif Options ==2:
                    CustomerDB.user(username).rideHistory()
                    input()
                    customer_Login(username,password)
                elif Options == 3:
                    main()
                    quit()
                else:
                    clrscr()
                    print("Error Occured Sign in ")
                    customer_Login()
            else:
                clrscr()
                print("Password Error")
                customer_Login()
                quit()
        else:
            clrscr()
            print("User doesn't exist")
            customer_Login()
    
    def customer_Signup():
        username = input("Enter the username :")
        if username in CustomerDB.info().keys():
            clrscr()
            print("Username already taken. Try Different Username")
            customer_Signup()
        else:
            password = int(input("Enter numerical passowrd: "))
            age = int(input("Enter your age : "))
            CustomerDB.add(Customer(username,password,age))
            clrscr()
            print("User Created")
            customer_Login()
            quit()
    
    print("1.Login \n2.Signup \n3.Exit")
    option= int(input("Choose an option: "))
    if option ==1:
        customer_Login()
        quit()
    elif option == 2:
        customer_Signup()
        quit()
    elif option == 3:
        quit()
    else:
        clrscr()
        print('Enter appropriate Value')
        customer_Login()

def admin_Portal():
    id = int(input("Enter Cab ID :"))
    dr = DriversDB.iD(id)
    print("Total Number of Trips :", len(dr.trips))
    totalF =0
    zC = 0
    for i in dr.trips:
        totalF = totalF + i.fare
        zC = zC + i.ZCommission
    print("Total Fare Collected :", totalF)
    print("Total ZULA Commission :", zC)
    print('Trip Details :')
    dr.tripsInfo()
    
    opt = int(input("\n1.Main Menu \n2.Exit \nChoose a option : "))
    if opt == 1:
        clrscr()
        main()
        quit()
    elif opt == 2:
        quit()
    else:
        print("Error Retry")
        admin_Portal()

def main():
    print("Welcome to ZULA!!")
    print("1.Cab driver login\n2.Customer login\n3.Admistration login\n4.Quit ")
    service = int(input("Please choose service : "))
    if service == 1:
        clrscr()
        driver_Portal()
    elif service == 2:
        clrscr()
        customer_Portal()
    elif service == 3:
        clrscr()
        admin_Portal()
    elif service ==4:
        print(" Exiting ") 
        quit() 
    else:
        main()
        quit()


if __name__ =='__main__':
    clrscr()
    main()