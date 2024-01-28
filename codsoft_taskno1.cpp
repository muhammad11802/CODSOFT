#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;



int main() {
    srand(time(0));
    bool hint = false;
    long long int number = 0;
    long long int guess;
    int userchoice;
    int userchoice2;
    long int score = 0;
    bool correct = false;
    bool game = true;

    while (game) {
        cout << "*************NUMBER GUESSING GAME*************" << endl << endl;
        cout << "Press 1 to Start Game" << endl;
        cout << "Press 2 to Quit" << endl;
        cin >> userchoice;
        cout << endl;

        switch (userchoice) {
        case 1:
            cout << "Select Difficulty Level" << endl;
            cout << "1. Easy (Guess number between 1 and 20)" << endl;
            cout << "2. Normal (Guess number between 1 and 200)" << endl;
            cout << "3. Hard (Guess without any range)" << endl;
            int difficulty;
            cin >> difficulty;

            switch (difficulty) {
            case 1:
                number = rand() % 10 + 1; // Random number between 1 and 10
                break;
            case 2:
                number = rand() % 30 + 1; // Random number between 1 and 30
                break;
            case 3:
                number = rand(); // Guess without any range
                break;
            default:
                cout << "Invalid difficulty level. Exiting game." << endl;
                game = false;
                break;
            }

            if (game) {
                correct = false;
                while (!correct) {
                    cout << "Guess The Number: ";
                    cin >> guess;
                    cout << endl;

                    if (number == guess) {
                        cout << "Your Guess is right, correct number is: "<<number << endl;
                        if (hint) {
                            score += 8;
                        }
                        else {
                            score += 10;
                        }
                        cout << "Current score: " << score << endl << endl;
                        correct = true;

                        cout << "Do you wish to Try again? ";
                        cout << "Press 1 - Yes" << endl;
                        cout << "Press 2 - No" << endl;
                        cin >> userchoice2;

                        if (userchoice2 == 2) {
                            game = false;
                        }
                       
                    }
                    else if (guess < number) {
                        int difference = abs(number - guess);

                        if (difference < 10) {
                            cout << "Your Guess is low but Too Close....Try again" << endl;
                        }
                        else if (difference < 50) {
                            cout << "Your Guess is low but Close....Try again" << endl;
                        }
                        else {
                            cout << "Your Guess is low and Far Away....Try again" << endl;
                        }
                    }
                    else {  // guess > number
                        int difference = abs(guess - number);

                        if (difference < 10) {
                            cout << "Your Guess is high but Too Close....Try again" << endl;
                        }
                        else if (difference < 50) {
                            cout << "Your Guess is high but Close....Try again" << endl;
                        }
                        else {
                            cout << "Your Guess is high and Far Away....Try again" << endl;
                        }
                    }
                }
            }
            break;

        case 2:
            game = false;
            break;
        }
    }

    return 0;
}
