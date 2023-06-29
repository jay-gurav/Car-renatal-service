#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include<algorithm>
using namespace std;


//*********************************************************Car Class*************************************************************
class Car {
    private:
        /* data */    
        string Model;
        string Manufacturer;
        string Make;
        int SeatCapacity;
        string LicensePlateNo;
        int Price;
        bool isBooked;

    public:    
        int CarId;

        Car(/*args*/ string _model, string _manufacturer, string _make, int _seatCapacity, string _licensePlateNo, int _runningCarID, int _price);

        void Display(){
            cout << "Car ID :- " + to_string( CarId) + "\n";
            cout << " Manufacturer :- " + Manufacturer ;
            cout << " Model :- " + Model + "\n";
            cout << " Make :- " + Make + "\n";
            cout << " Max Seating Capacity :- " + to_string( SeatCapacity ) + "\n";
            if(isBooked){
                cout << " License Plate :- " + LicensePlateNo + "\n";
            }
            cout << " Price Per Day :- " + to_string(Price) + "\n";

            cout << " TnC:  petrol cost will be carried by Customer \n";
        }
        void setBooking(bool _isBooked){
            this->isBooked = _isBooked;
        }
        bool getBooking(){
            return this->isBooked;
        }
        int getPrice(){
            return this->Price;
        }
        ~Car();

};

Car::Car(string _model, 
    string _manufacturer, 
    string _make, 
    int _seatCapacity, 
    string _licensePlateNo, 
    int _runningCarID, 
    int _price){
        this->CarId = _runningCarID + 1;
        this->Make = _make;
        this->Manufacturer = _manufacturer;
        this->Model = _model;
        this->SeatCapacity = _seatCapacity;
        this->LicensePlateNo = _licensePlateNo;
        this->Price = _price;
        //this->isBooked = false;
}

//*********************************************************Car Class*************************************************************
//**********************************************************Booking Class********************************************************

class Booking
{
private:
    /* data */
    string Name;
    long MobileNo;
    
    int bookedDays;
    int finalPrice;

public:
    int bookingId;
    Car* car;
    Booking(/* args */ string _Name,
    long _MobileNo,
    Car & _car,
    int _bookedDays,
    int _finalPrice,
    int _runnigBookingId);

    void Display(){
        cout << " Name :- " + Name + "\n";
        cout << " Booking Id :- " +to_string(bookingId) + "\n";
        cout << " Days Booked for " + to_string( bookedDays ) + "\n";
        car->Display();
        cout << " Total Price " + to_string( finalPrice ) + "\n";
    }

    ~Booking();
};

Booking::Booking(/* args */string _Name,
    long _MobileNo,
    Car & _car,
    int _bookedDays,
    int _finalPrice,
    int _runnigBookingId): car(car)
{
        this->bookingId = _runnigBookingId + 1;
        this->bookedDays = _bookedDays;
        this->MobileNo = _MobileNo;
        this->car = &_car;
        this->Name = _Name;
        this->finalPrice = bookedDays * _car.getPrice();
}

Booking::~Booking()
{
}

//**********************************************************Booking Class********************************************************
//**********************************************************Global Vars *********************************************************

vector<Car*> carStore;
vector<Booking*> bookingStore;

//**********************************************************Global Vars *********************************************************

void initCars(){
    carStore.push_back(new Car("zen", "Maruti", "2007", 5, "MH09AS1288", carStore.size(), 2000));
    carStore.push_back(new Car("Dzire", "Suzuki", "2016", 5, "MH09IK8564", carStore.size(), 4000));
    carStore.push_back(new Car("Innova", "Toyota", "2017", 8, "MH09OL3546", carStore.size(), 8000));
}

void DisplayCars(){
    cout << "We have following Cars in our arsenal. Choose from Following \n";
    cout << "********************************************************************************************************************** \n";
    for (int i = 0; i < carStore.size(); i++)
    {
        if (!carStore[i]->getBooking())
        {
            carStore[i]->Display();
        }
        
    }
    cout << "********************************************************************************************************************** \n";
}

void CreateBooking(){
    Booking* bookingDetails;
    Car* carDetails;
    string name;
    long mobileNo;
    int bookingDays;
    int carId;
    char bookingValidation = 'n';
    while (bookingValidation == 'n')
    {
        cout << "Enter Passanger Name \n";
        cin >>  name;
        cout << "Hello " + name + "\n";
        cout << "Please enter your mobile No \n";
        cin >> mobileNo;
        cout << "How many days long your trip is?  \n";
        cin >> bookingDays;
        bool isValidCar = false;
        while (!isValidCar)
        {
            system("clear");
            DisplayCars();
            cout << "Enter car ID number of the car that u want to book \n";
            cin >> carId;
            for (int i = 0; i < carStore.size(); i++)
            {
                if(carStore[i]->CarId == carId){
                    isValidCar = true;
                    carDetails = carStore[i];
                    system("clear");
                    break; 
                }                
            }
            if(!isValidCar){                
                system("clear");
                cout << "please enter valid car no \n";
                break;
            }

            cout<<"You are booking trip for car ID " + to_string(carId) + " under name of "+name + " for " + to_string(bookingDays) +" days \n with Mobile No " + to_string(mobileNo) + "\n"; 
            carDetails->Display();
            cout<<"Please validate above details if you are fine with it enter Y else N \n";
            cin>>bookingValidation; 
            bookingValidation = tolower(bookingValidation);
        }
        if (bookingValidation == 'y')
        {
            carDetails->setBooking(true);
            bookingDetails = new Booking(name, mobileNo, *carDetails, bookingDays, carDetails->getPrice(), bookingStore.size());
            bookingStore.push_back(bookingDetails);
            bookingDetails->Display();
        } else {
            cout<<"If you want to retry booking enter Y else N \n";
            cin >> bookingValidation;
            bookingValidation = tolower(bookingValidation);
            bookingValidation = bookingValidation == 'y' ? 'n' : 'y';
        }

    }
    

}

void displayAllBookings(){
    cout << "We have following Bookings so far \n";
    cout << "********************************************************************************************************************** \n";
    for (int i = 0; i < bookingStore.size(); i++)
    {
        
            bookingStore[i]->Display();
        
        
    }
    cout << "********************************************************************************************************************** \n";
}

int DisplayBookingForAPerson(){
    int bookingId;
    bool isValidBooking = false;
    cout << "Please enter your booking Id \n";
    cin >> bookingId;
    cout << "********************************************************************************************************************** \n";
    for (int i = 0; i < bookingStore.size(); i++)
    {
        if (bookingStore[i]->bookingId == bookingId )
        {
            isValidBooking = true;
            bookingStore[i]->Display();
        }     
        
        return i;
    }
    if (!isValidBooking)
    {
        cout<<"invalid booking ID!!!!!! Please try again";
        
    }
    
    cout << "********************************************************************************************************************** \n";
    return -1;
}

void CancelBooking(){
    int bookingIndex = DisplayBookingForAPerson();
    if (bookingIndex >= 0)
    {
        char validPop = 'y';
        cout<< "Do you want to cancel above booking if yes enter Y \n";
        cin>>validPop;
        validPop = tolower(validPop);
        if(validPop == 'y')
        {
            bookingStore[bookingIndex]->car->setBooking(false);
            bookingStore.erase(bookingStore.begin() + bookingIndex);
        } else if (validPop != 'y'  )
        {
            cout<< "Cancel Aborted \n";
            validPop = 'y';
        }
    }
    

}


int main() {
    char repeatFlag = 'y';
    int choice;
    initCars();

    while (repeatFlag == 'y')
    {
        cout << "Welcome to Jayesh Car rentals\n";
        cout << "Please enter option no\n";
        cout << "1) Display available Cars\n";
        cout << "2) Book Trip\n";
        cout << "3) Get Your Booking Details\n";        
        cout << "4) Cancel Booking\n";
        //cout << "5) Get All Booking Details\n";

        cin >> choice;
        if (choice == 1)
        {
            system("clear");
            DisplayCars();
        }
        else if (choice == 2)
        {
            system("clear");
            CreateBooking();
        }
        else if (choice == 3)
        {
            system("clear");
            DisplayBookingForAPerson();
        }
        else if (choice == 4)
        {
             system("clear");
             CancelBooking();
        }
        else if(choice == 5){
            system("clear");
            displayAllBookings();
        }
        else 
        {
            cout<<"invalid option!!!!!!";
        }

        cout << "Do you want to choose any other option? if yes enter Y or N \n";
        cin >> repeatFlag;     
        repeatFlag = tolower(repeatFlag);    
        cout << repeatFlag;   
        system("clear");       
        

    }
    

    return 0;
}