#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <string>

using namespace std;

struct Car {
    string brand;
    string model;
    string colour;
    int price;
};

/*
 * Arguments:
 *
 *   unused - Ignored in this case, see the documentation for sqlite3_exec
 *    count - The number of columns in the result set
 *     data - The row's data
 *  columns - The column names
 */
static int myCallback(void* unused, int count, char** data, char** columns) {

    cout << "There are " << count << " column(s)\n";

    int i;
    for (i = 0; i < count; i++) {
        cout << columns[i] << ": "<< data[i] << endl;
    }
    cout << endl;
    return 0;
    
}

int addCar() {
    return 0;
}

int main()
{
    sqlite3 *db;
    int rc = 0;
    int selection{ 0 };

    string insertSQL = "INSERT INTO Cars (Brand, Model, Colour, Price)";

    //Connect and open the Database
    rc = sqlite3_open("Items.db", &db);
    if (rc) {
        cout << "Unable to connect to database\n";
        return 0;
    }
    else
        cout << "Connection Successful!\n\n";

    int loop = 1;
    while (loop == 1) {
    cout << "\n1. Show Cars" << endl;
    cout << "2. Add a Car" << endl;
    cout << "0. Quit" << endl;
    cout << "Select an option: ";
    cin >> selection;

    
    switch(selection) {
        case 0:
            loop = 0;
        case 1:
        {
            string myQuery{ "SELECT * FROM Cars" };
            sqlite3_exec(db, myQuery.c_str(), myCallback, NULL, NULL); 
            break;
        }
        case 2:
        {
            Car carToAdd;
            cout << "Brand: ";
            cin >> carToAdd.brand;
            
            cout << "Model: ";
            cin >> carToAdd.model;

            cout << "Colour: ";
            cin >> carToAdd.colour;

            cout << "Price: ";
            cin >> carToAdd.price;

            string x = insertSQL + " VALUES('" + carToAdd.brand + "', '" + carToAdd.model + "', '" + carToAdd.colour + "', " + to_string(carToAdd.price) + ")";

            sqlite3_exec(db, x.c_str(), myCallback, NULL, NULL);

            break;
        }
        }
    }


    
    sqlite3_close(db);
    return 0;
}


