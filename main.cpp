//
//  main.cpp
//  CS250_ProgramOne
//
//  Created by Charlotte Luquer on 9/20/24.
// Description: Program assigns passengers seats in an airplane

#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

void getPlaneSize (int &rows, int &seatsPerRow){
    cout << "How many rows are on the plane? ";
    cin >> rows;
    if (rows <= 0) {
        throw invalid_argument("Number of rows must be greater than 0");
    }
    cout << "Enter the number of seats per row: ";
    cin >> seatsPerRow;
    if (seatsPerRow <= 0 || seatsPerRow > 26) {
            throw invalid_argument("Number of seats per row must be between 1 and 26");
        }
}

vector<vector<char>> 

getSeating(int rows, int seatsPerRow) {
    vector<vector<char>> seating(rows, vector<char>(seatsPerRow, '0'));
    return seating;
}

void displaySeating(const vector<vector<char>> &seating) {
    int rows = seating.size();
    int seatsPerRow = seating[0].size();
    
    cout << "    ";
        for (int i = 0; i < seatsPerRow; i++) {
            cout << char('A' + i) << " ";
        }
        cout << endl;

     
        for (int i = 0; i < rows; i++) {
            cout << i + 1 << "   ";
            for (int j = 0; j < seatsPerRow; j++) {
                cout << seating[i][j] << " ";
            }
            cout << endl;
        }

        cout << "0: Available, X: Unavailable" << endl;
    }

bool claimSeat(vector<vector<char>> &seating, int row, char seat) {
    int seatIndex = seat - 'A';  // Convert seat letter to index
    row--;  // Convert 1-based row to 0-based

    if (row < 0 || row >= seating.size() || seatIndex < 0 || seatIndex >= seating[0].size()) {
        cout << "Seat selection is not valid." << endl;
        return false;
    }

    if (seating[row][seatIndex] == 'X') {
        cout << "This seat is already taken." << endl;
        return false;
    }

    seating[row][seatIndex] = 'X';
    return true;
}


bool availability(const vector<vector<char>> &seating) {
    for (const auto &row : seating) {
        for (char seat : row) {
            if (seat == '0') {
                return true;
            }
        }
    }
    return false;
}
    
int totalAvailability(const vector<vector<char>> &seating) {
    int availableSeats = 0;
    for (const auto &row : seating) {
        for (char seat : row) {
        if (seat == '0') {
                availableSeats++;                }
            }
        }
    return availableSeats;
    }
    
    
int main() {
    int rows, seatsPerRow;
        
    try {
        getPlaneSize(rows, seatsPerRow);
        vector<vector<char>> seating = getSeating(rows, seatsPerRow);
            
        char continueBooking = 'Y';
        while (continueBooking == 'Y' && availability(seating)) {
            displaySeating(seating);
                
            int row;
            char seat;
            cout << "Enter row number: ";
            cin >> row;
            cout << "Enter seat letter: ";
            cin >> seat;
            
            if (claimSeat(seating, row, seat)) {
                cout << "Seat was claimed." << endl;
                displaySeating(seating);
                }
    
            if (availability(seating)) {
                cout << "Do you want to book another seat? (Y/N): ";
                cin >> continueBooking;
                continueBooking = toupper(continueBooking);
            } else {
                cout << "No more available seats!" << endl;;
                }
            }
            
      
            displaySeating(seating);
        cout << totalAvailability(seating) << " seats are still available." << endl;
            
            if (!availability(seating)) {
                cout << "Plane is full.\n";
            } else {
                cout << "Thank you for using the seat booking system." << endl;
            }
            
        } catch (const exception &error) {
            cout << "Error: " << error.what() << endl;
        }
        return 0;
}
