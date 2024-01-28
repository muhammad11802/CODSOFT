#include <iostream>
using namespace std;



int main() {
    double num1, num2;
    char operation;
    bool cal = true;
    char enterKey; 

    while (cal) {
        system("cls");

        cout << "********Simple Calculator********" << endl;
        cout << "Enter the First Number: ";
        cin >> num1;

        cout << "Enter the Second Number: ";
        cin >> num2;

        cout << "Choose an operation (+, -, *, /): ";
        cin >> operation;

        int userchoice;

        switch (operation) {
        case '+':
            cout << "Result: " << num1 + num2 << endl;
            cout << "Press Enter to continue" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get(enterKey);
            if (enterKey == 13) {  
                break;
            }
            else break;
        case '-':
            cout << "Result: " << num1 - num2 << endl;
            cout << "Press Enter to continue" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get(enterKey);
            if (enterKey == 13) {  
                break;
            }
            else break;
        case '*':
            cout << "Result: " << num1 * num2 << endl;
            cout << "Press Enter to continue" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get(enterKey);
            if (enterKey == 13) {  
                break;
            }
            else break;
        case '/':
            if (num2 != 0) {
                cout << "Result: " << num1 / num2 << endl;
                cout << "Press Enter to continue" << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get(enterKey);
                if (enterKey == 13) {  
                    break;
                }
                else break;
            }
            else {
                
                cout << "Error! Division by zero." << endl;
                cout << "Press Enter to continue" << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get(enterKey);

            }
            break;
        default:

            cout << "Invalid operation. Please choose +, -, *, or /." << endl;
            continue;
        }
        system("cls");
        cout << "Do you wish to try again? " << endl;
        cout << "1-Yes\n2-No\n";
        cin >> userchoice;
        if (userchoice == 2) {
            cal = false;
        }
    }

    return 0;
}
