#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>


using namespace std;

class Book {
    string title;
    string author;
    long long int ISBN;
    bool availability;

public:
    Book(string t, string a, long long int isbn) : title(t), author(a), ISBN(isbn), availability(true) {}

    void setAvailability(bool t) {
        availability = t;
    }

    string getTitle() const {
        return title;
    }

    string getAuthor() const {
        return author;
    }

    long long int getISBN() const {
        return ISBN;
    }
    string display() const {
        return title + " " + author + " " + to_string(ISBN) + " " + (availability ? "Available" : "Not Available");
    }
};

class User {
    static int lastId;
    string name;
    int id;
    int age;

public:
    User(string n, int a) : name(n), age(a), id(++lastId) {}

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }
};

int User::lastId = 0;

class Library {
public:
    void addBook(const Book& b) {
        ofstream myFile("Booksdatabase.txt", ios::app);
        myFile << b.display() << endl;
    }

    void displayBooks() const {
        ifstream myFile("Booksdatabase.txt");
        if (myFile.is_open()) {
            string line;
            while (getline(myFile, line)) {
                cout << line << endl;
            }
            myFile.close();
        }
        else {
            cout << "Unable to open file" << endl;
        }
    }

    void searchBook(const string& bookName) const {
        ifstream inputFile("Booksdatabase.txt");
        if (inputFile.is_open()) {
            string line;
            bool found = false;
            while (getline(inputFile, line)) {
                stringstream ss(line);
                string title, author, availabilityStr;
                long long int currentIsbn;

                ss >> title >> author >> currentIsbn >> availabilityStr;
                if (title == bookName) {
                    found = true;
                    cout << "Book Found!!!! Details:" << endl;
                    cout << line << endl;
                    break; 
                }
            }
            if (!found) {
                cout << "Book not found." << endl;
            }
            inputFile.close();
        }
        else {
            cout << "Unable to open file" << endl;
        }
    }
    void checkoutBook() {
        cout << "Enter Your Name: ";
        string name;
        getline(cin >> ws, name);

        long long int isbn;
        cout << "Enter ISBN of book to checkout: ";
        cin >> isbn;

        ifstream inputFile("Booksdatabase.txt");
        ofstream tempFile("temp.txt");
        ofstream logFile("CheckoutLog.txt", ios::app);

        string bookName;
        bool bookFound = false;

        if (inputFile.is_open() && tempFile.is_open() && logFile.is_open()) {
            string line;
            while (getline(inputFile, line)) {
                istringstream iss(line);
                string title, author, availabilityStr;
                long long int currentIsbn;

                if (!(iss >> title >> author >> currentIsbn >> availabilityStr)) {
                    cerr << "Error reading line from file." << endl;
                    break;
                }

                if (currentIsbn == isbn) {
                    bookFound = true;
                    bookName = title;
                    tempFile << title << " " << author << " " << currentIsbn << " NotAvailable" << endl;

                    logFile << "Book: " << title << " ISBN: " << currentIsbn << " checked out by: " << name << endl;
                }
                else {
                    tempFile << line << endl;
                }
            }

            inputFile.close();
            tempFile.close();
            logFile.close();

            if (remove("Booksdatabase.txt") != 0) {
                cerr << "Error removing the original file." << endl;
            }

            if (rename("temp.txt", "Booksdatabase.txt") != 0) {
                cerr << "Error renaming the temp file." << endl;
            }

            if (bookFound) {
                cout << "Book " << bookName << " successfully checked out by " << name << endl;
            }
            else {
                cout << "Book with ISBN " << isbn << " not found." << endl;
            }
        }
        else {
            cerr << "Error opening files." << endl;
        }
    }

    void bookReturn() {
        string returnPerson;
        long long int isbn;

        cout << "Enter Your Name: ";
        getline(cin >> ws, returnPerson);

        cout << "Enter book ISBN to return: ";
        cin >> isbn;

        ifstream logFile("CheckoutLog.txt");
        ofstream tempLogFile("tempLog.txt");

        bool bookFound = false;
        string logEntry;
        while (getline(logFile, logEntry)) {
            istringstream logIss(logEntry);
            string logBook, logTitle, logISBN, checkedOutBy;

            logIss >> logBook >> logTitle >> logISBN;
            string temp;
            logIss >> temp >> logISBN;
            logIss >> ws;
            getline(logIss >> ws, checkedOutBy);

            long long int logIsbn;
            istringstream(temp) >> logIsbn;

            if (logIsbn == isbn && checkedOutBy == "out by: " + returnPerson) {
                bookFound = true;
                cout << "Book " << logTitle << " found " << endl;
            }
            else {
                tempLogFile << logEntry << endl;
            }
        }

        logFile.close();
        tempLogFile.close();

        if (remove("CheckoutLog.txt") != 0) {
           
            return;
        }

        if (rename("tempLog.txt", "CheckoutLog.txt") != 0) {
            
            return;
        }

        if (bookFound) {
            // Update the book status in Booksdatabase.txt
            ifstream inputFile("Booksdatabase.txt");
            ofstream tempFile("temp.txt");

            if (inputFile.is_open() && tempFile.is_open()) {
                string line;
                while (getline(inputFile, line)) {
                    istringstream iss(line);
                    string title, author, availabilityStr;
                    long long int currentIsbn;

                    if (!(iss >> title >> author >> currentIsbn >> availabilityStr)) {
                        
                        break;
                    }

                    if (currentIsbn == isbn) {
                        // Update the status to "Available"
                        tempFile << title << " " << author << " " << currentIsbn << " Available" << endl;
                    }
                    else {
                        tempFile << line << endl;
                    }
                }

                inputFile.close();
                tempFile.close();

                if (remove("Booksdatabase.txt") != 0) {
                    
                    return;
                }

                if (rename("temp.txt", "Booksdatabase.txt") != 0) {
                    
                    return;
                }

                cout << "Book successfully returned by " << returnPerson << endl;
                calfine();
            }
            else {
                cerr << "Error opening files." << endl;
            }
        }
        else {
            cout << "Book with ISBN " << isbn << " not found or not checked out by " << returnPerson << endl;
        }

       

       
    }
    void calfine() {
        srand(time(0));
        // Generate a random number of days (from 1 to 30)
        int days = rand() % 30 + 1;
        cout << "book was returned in " << days << " days " << endl;
        // Calculate fine
        int fine = 0;
        if (days > 15) {
          //  cout << "book was returned in " << days << " days " << endl;
            fine = 10;
            cout << "Fine: $" << fine << endl;
            
        }

    }


};

int main() {
    const char* filename = "Booksdatabase.txt";
    remove(filename);
    const char* filename2 = "CheckoutLog.txt";
    remove(filename2);

    int userchoice;
    int userchoice2;
    bool Program = true;
    string name;
    Library l;
    Book b1("Book1", "Person1", 123456789);
    Book b2("Book2", "Person2", 987654321);
    Book b3("Book3", "Person3", 112233445);
    Book b4("Book4", "Person4", 567891234);
    Book b5("Book5", "Person5", 678912345);
    Book b6("Book6", "Person6", 789123456);
    Book b7("Book7", "Person7", 891234567);
    Book b8("Book8", "Person8", 912345678);
    Book b9("Book9", "Person9", 111222333);


    l.addBook(b1);
    l.addBook(b2);
    l.addBook(b3);
    l.addBook(b4);
    l.addBook(b5);
    l.addBook(b6);
    l.addBook(b7);
    l.addBook(b8);
    l.addBook(b9);

    while (Program) {
        cout << "**************************LIBRARY MANAGEMENT SYSTEM**************************"<< endl << endl;
        l.displayBooks();
        cout << endl << endl;
        cout << "Press 1 to View Book DataBase" << endl;
        cout << "Press 2 to Search Book" << endl;
        cout << "Press 3 to Checkout Book" << endl;
        cout << "Press 4 to Return Book" << endl;
        cin >> userchoice;

        cout << endl;

      switch (userchoice) {
        case 1:
            system("cls");
            l.displayBooks();
            cout << "Press any digit to Go Back: " << endl;
            cin >> userchoice2;
            system("cls");
            break;

        case 2:
           
            cout << "Enter the Book Name to Search: ";
            cin >> name;
            system("cls");
            l.searchBook(name);
            cout << "Press any digit to Go Back: " << endl;
            cin >> userchoice2;
            system("cls");

            break;

        case 3:
            l.checkoutBook();
            cout << "Press any digit to Go Back: " << endl;
            cin >> userchoice2;
            system("cls");
            
            break;
        case 4:
            l.bookReturn();
            cout << "Press any digit to Go Back: " << endl;
            cin >> userchoice2;
            system("cls");
        }
    }

    return 0;
}

