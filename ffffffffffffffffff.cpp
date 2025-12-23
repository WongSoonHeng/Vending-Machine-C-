#include <iostream>
#include <string>
#include<fstream>
#include<ctime>
#include <cstdlib>
using namespace std;

// Structure to hold details about each item
struct Menu {
    int id;
    string name;
    double price;
};

// Function declarations
void displayMenu(const Menu Cake[]);
void calculateTotal(const Menu Cake[], int ID, int addIDs[], int addQuantities[], int quantity, int addCount, double& total);
void addOrder(const Menu Cake[], int addIDs[], int addQuantities[], int& addCount);
void selectPayment(int& pay);

int main() {
    int ID;
    int quantity;
    int addIDs[10]; // Stores the Cake ID of the additional order
    int addQuantities[10]; // stores the quantity of additional orders
    int addCount = 0; //Additional order counter
    int pay;
    int choice;
    double cash;
    double total = 0;
    double totalcash = 0;


    //array
    // List of cakes in vending machine
    Menu Cake[] = {
        {0, "Chocolate Cake", 80},
        {1, "Vanilla Cake", 70},
        {2, "Cheese Cake", 70},
        {3, "Coffee Cake 6inch", 50},
        {4, "Black Forest Cake", 80},
        {5, "Strawberry Cake", 70},
        {6, "Blueberry Cake", 80},
        {7, "Black Chocolate Cake", 90},
        {8, "Mixed Fruit Cake", 80},
        {9, "Tiramisu", 50}
    };

    // Display welcome
    cout << "Welcome to Vending Cake Machine!" << endl;
    cout << "Welcome to INTI Cake SS15 Subang Jaya!" << endl;
    displayMenu(Cake);  // Display cake menu

    // Customer enter Cake ID
    cout << "All Cake is 6 inch" << endl;
    cout << "Please enter Cake ID, enter a value between 0 and 9. : ";
    cin >> ID;

    // Validate Cake ID   If Statements
    if (ID >= 0 && ID < 10) {
        cout << "Enter Quantity: ";
        cin >> quantity;

        // Display order details
        cout << "-----------------------" << endl;
        cout << "Your Order" << endl;
        cout << "Cake ID: " << Cake[ID].id << endl;
        cout << "Your Selected: " << Cake[ID].name << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Cake Price RM " << Cake[ID].price << endl;
        cout << "Total Price RM " << Cake[ID].price * quantity << endl;

        // Ask customer if they need an additional order   While Loop
        while (true) {
            cout << "-----------------------" << endl;
            cout << "Do you want to add another order? Yes(1)/No(0): ";
            cin >> choice;
            cout << "-----------------------" << endl;

            // If else Statements
            if (choice == 1) {
                // Customer chooses to add another order
                addOrder(Cake, addIDs, addQuantities, addCount);
            }
            else if (choice == 0) {
                // Customer chooses to proceed to payment
                cout << "Display Total Order Detail..." << endl;
                break;
            }
            else {
                cout << "Error. Please enter Yes(1) or No(0)." << endl;
            }
        }

        // Calculate total price   function
        calculateTotal(Cake, ID, addIDs, addQuantities, quantity, addCount, total);

        // Display final order details  array
        cout << "-----------------------" << endl;
        cout << "Your Order: " << Cake[ID].name;
        //for loop
        for (int i = 0; i < addCount; ++i) {  //display all additional order
            cout << " , " << Cake[addIDs[i]].name;
        }
        cout << endl;

        //sum total quantity
        int totalQuantity = quantity;
        // for loop
        for (int i = 0; i < addCount; ++i) {  //sum all quantity of additional orders
            totalQuantity += addQuantities[i];
        }
        cout << "Total Quantity: " << totalQuantity << endl;
        cout << "Total Price RM " << total << endl;

        // Select payment method   function
        cout << "-----------------------" << endl;
        selectPayment(pay);

        cout << "Payment Method Selected: ";
        // switch statements
        switch (pay) {
        case 1:
            cout << "Credit Card" << endl;
            break;
        case 2:
            cout << "Debit Card" << endl;
            break;
        case 3:
            cout << "TNG eWallet" << endl;
            break;
        case 4:
            cout << "Cash" << endl;
            break;
        default:
            cout << "Invalid Payment Option" << endl;
            break;
        }
        //if customer using credit and Debit    if else statements
        if (pay == 1 || pay == 2) {
            cout << "-----------------------" << endl;
            cout << "Total Price RM " << total << endl;
            cout << "Please tap the card" << endl;
            cout << "Process........" << endl;
            cout << "Payment successful" << endl;
        }
        //if customer using TNG
        else if (pay == 3) {
            cout << "-----------------------" << endl;
            cout << "Total Price RM " << total << endl;
            cout << "Please scan the QR code" << endl;
            cout << "Process........" << endl;
            cout << "Payment successful" << endl;
        }
        //if customer using cash payment
        else if (pay == 4) {
            cout << "-----------------------" << endl;
            cout << "Accept RM1, 5, 10, 20, 50, 100" << endl;

            //while loop
            cout << "-----------------------" << endl;
            cout << "Total Price RM " << total << endl;
            while (true) {
                cout << "Please insert cash: RM";
                cin >> cash;

                //only can accept RM 5, 10, 20, 50, 100
                if (cash == 1 || cash == 5 || cash == 10 || cash == 20 || cash == 50 || cash == 100) {
                    totalcash += cash; //Accumulated payment amount

                    if (totalcash >= total) {
                        cout << "Payment successful" << endl;
                        cout << "Change due RM" << totalcash - total << endl;
                        cout << "-----------------------" << endl;
                        break; // Payment completed, exit loop
                    }
                    else if (totalcash < total) {
                        //display still need houw much money
                        cout << "Not enough money. You still need RM" << total - totalcash << endl;
                        cout << "-----------------------" << endl;
                    }
                }
                else {
                    cout << "Invalid denomination. Please insert RM1, 5, 10, 20, 50, or 100 only." << endl;
                }
            }
        }

        // Get the current time
        std::time_t now = std::time(nullptr);  // Get the current timestamp

        // get the current time
        std::tm localTime;
        localtime_s(&localTime, &now);  // Use localtime_s to handle local time

        // Formatted time output
        char dateTime[100];
        std::strftime(dateTime, sizeof(dateTime), "%Y-%m-%d %H:%M:%S", &localTime);

        // save receipt
        ofstream outfile;
        outfile.open("receipt.txt", ios::out);

        if (!outfile) {
            cout << "File could not be opened !";
        }
        // Writing the receipt to file     text file
        outfile << "Receipt" << endl;
        outfile << "====================================" << endl;
        outfile << "INTI Cake SS15 Subang Jaya" << endl;
        outfile << "No. 3, Jalan SS15/8,47500 Subang Jaya," << endl <<" Selangor Darul Ehsan, Malaysia" << endl;
        outfile << "Phone:+603 5633 4350" << endl;
        outfile << "====================================" << endl;
        outfile << "Your Order: " << endl;
        outfile << Cake[ID].name << " x" << quantity << " " << "RM" << Cake[ID].price * quantity << endl;
        for (int i = 0; i < addCount; ++i) {  // Write additional orders   for loop
            outfile << Cake[addIDs[i]].name << " x" << addQuantities[i] << " "
                << "RM" << Cake[addIDs[i]].price * addQuantities[i] << endl;
        }

        totalQuantity = quantity;
        // calculate total quantity    for loop
        for (int i = 0; i < addCount; ++i) {
            totalQuantity += addQuantities[i];
        }
        outfile << "Total Quantity: " << totalQuantity << endl;
        outfile << "Total Price RM " << total << endl;

        outfile << "Payment Method Selected: ";

        //switch statements
        switch (pay) {
        case 1:
            outfile << "Credit Card" << endl;
            break;
        case 2:
            outfile << "Debit Card" << endl;
            break;
        case 3:
            outfile << "TNG eWallet" << endl;
            break;
        case 4:
            outfile << "Cash" << endl;
            outfile << "Cash:RM" << totalcash << endl;
            outfile << "Change Due RM" << (totalcash - total) << endl;
            break;
        default:
            outfile << "Invalid Payment Option" << endl;
            break;
        }

        outfile << "====================================" << endl;
        outfile << "Date and Time: " << dateTime << endl;  // Add date and time        
        outfile << "Thank You!" << endl;
        outfile.close();  // Close the file
        cout << "Receipt saved successfully!" << endl;
        system("receipt.txt"); //open the receipt

    }
    else {
        cout << "Cake ID not found. Please enter a value between 0 and 9." << endl;
    }
    return 0;
}
// Function to display the cake menu
void displayMenu(const Menu Cake[]) {  //array
    cout << "Menu:" << endl;
    for (int i = 0; i < 10; ++i) {
        cout << "ID: " << Cake[i].id << endl;
        cout << "Cake Name: " << Cake[i].name << endl;
        cout << "Cake Price RM " << Cake[i].price << endl;
        cout << "-----------------------" << endl;
    }
}

// Function to calculate total price
void calculateTotal(const Menu Cake[], int ID, int addIDs[], int addQuantities[], int quantity, int addCount, double& total) {
    total = Cake[ID].price * quantity; // Calculate main order price

    //calculate additional order price + main order price    for loop
    for (int i = 0; i < addCount; ++i) {
        total += Cake[addIDs[i]].price * addQuantities[i];
    }
}

// Function to payment selection
void selectPayment(int& pay) {
    cout << "Payment Methods" << endl;
    cout << "1. Credit Card" << endl;
    cout << "2. Debit Card" << endl;
    cout << "3. TNG eWallet" << endl;
    cout << "4. Cash" << endl;
    cout << "Please select your payment: ";
    cin >> pay;

    //switch statemtns
    switch (pay) {
    case 1:
        cout << "You selected Credit Card." << endl;
        break;
    case 2:
        cout << "You selected Debit Card." << endl;
        break;
    case 3:
        cout << "You selected TNG eWallet." << endl;
        break;
    case 4:
        cout << "You selected Cash." << endl;
        break;
    default:
        cout << "Error. Invalid option. Please try again." << endl;
        break;
    }
}

// Function to handle additional orders
void addOrder(const Menu Cake[], int addIDs[], int addQuantities[], int& addCount) {
    int addID, addquantity;

    cout << "All Cake is 6 inch" << endl;
    cout << "Please enter Cake ID: ";
    cin >> addID;

    // Verify Cake ID is valid   if else statements
    if (addID >= 0 && addID < 10) {
        cout << "Enter Quantity: ";
        cin >> addquantity;

        //array
        //if else statements
        //If the number of additional orders is less than the maximum number
        if (addCount < 10) {
            addIDs[addCount] = addID;    // Stores the Cake ID of the additional order  
            addQuantities[addCount] = addquantity;  // stores the quantity of additional orders
            addCount++; //increment additional order counter

            // display additional order detail
            cout << "-----------------------" << endl;
            cout << "Your Additional Order:" << endl;
            cout << "Cake ID: " << Cake[addID].id << endl;
            cout << "Selected Cake: " << Cake[addID].name << endl;
            cout << "Quantity: " << addquantity << endl;
            cout << "Cake Price RM " << Cake[addID].price << endl;
            cout << "Total Price RM " << Cake[addID].price * addquantity << endl;
        }
        else {
            cout << "You cannot add more orders. Maximum limit reached!" << endl;
        }
    }
    else {
        cout << "Error. Invalid Cake ID. Please try again." << endl;
    }
}