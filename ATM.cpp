#include <iostream>
#include <string>
using namespace std;
 
// ============================
//   Constants & Global Data
// ============================
const int    MAX_ATTEMPTS    = 3;
const int    MAX_HISTORY     = 50;
const string CORRECT_PIN     = "1234";
const double INITIAL_BALANCE = 5000.0;
 
// ============================
//   Function Declarations
// ============================
bool  login();
void  showMenu();
void  checkBalance(double balance);
double deposit(double balance);
double withdraw(double balance);
void  showHistory(string history[], int count);
void  addHistory(string history[], int& count, string record);
void  printLine(char ch, int len);
 
// ============================
//        Main Program
// ============================
int main() {
    // Attempt login
    if (!login()) {
        cout << "\n  Card blocked. Please contact your bank.\n";
        return 0;
    }
 
    double balance = INITIAL_BALANCE;
    string history[MAX_HISTORY];
    int    historyCount = 0;
    int    choice;
 
    addHistory(history, historyCount, "Login successful.");
 
    do {
        showMenu();
        cout << "  Enter choice: ";
        cin  >> choice;
 
        switch (choice) {
            case 1:
                checkBalance(balance);
                addHistory(history, historyCount, "Checked balance: $" + to_string((int)balance));
                break;
 
            case 2:
                balance = deposit(balance);
                break;
 
            case 3:
                balance = withdraw(balance);
                break;
 
            case 4:
                showHistory(history, historyCount);
                break;
 
            case 5:
                printLine('-', 40);
                cout << "  Thank you for using our ATM!\n";
                cout << "  Please take your card.\n";
                printLine('-', 40);
                addHistory(history, historyCount, "Session ended.");
                break;
 
            default:
                cout << "\n  [!] Invalid option. Try again.\n";
        }
 
    } while (choice != 5);
 
    return 0;
}
 
// ============================
//    Function Definitions
// ============================
 
// --- Helper: print a line ---
void printLine(char ch, int len) {
    for (int i = 0; i < len; i++) cout << ch;
    cout << "\n";
}
 
// --- Login with PIN and limited attempts ---
bool login() {
    string enteredPin;
    int attempts = 0;
 
    printLine('=', 40);
    cout << "     WELCOME TO MAX BANK ATM\n";
    printLine('=', 40);
 
    while (attempts < MAX_ATTEMPTS) {
        cout << "  Enter PIN: ";
        cin  >> enteredPin;
        attempts++;
 
        if (enteredPin == CORRECT_PIN) {
            cout << "\n  Access granted. Welcome!\n";
            printLine('-', 40);
            return true;
        } else {
            int remaining = MAX_ATTEMPTS - attempts;
            if (remaining > 0)
                cout << "  [!] Wrong PIN. " << remaining << " attempt(s) left.\n";
            else
                cout << "  [!] Wrong PIN. No attempts remaining.\n";
        }
    }
    return false;
}
 
// --- Show main menu ---
void showMenu() {
    cout << "\n";
    printLine('=', 40);
    cout << "           MAIN MENU\n";
    printLine('=', 40);
    cout << "  1. Check Balance\n";
    cout << "  2. Deposit\n";
    cout << "  3. Withdraw\n";
    cout << "  4. Transaction History\n";
    cout << "  5. Exit\n";
    printLine('-', 40);
}
 
// --- Check Balance ---
void checkBalance(double balance) {
    printLine('-', 40);
    cout << "  Current Balance: $" << balance << "\n";
    printLine('-', 40);
}
 
// --- Deposit ---
double deposit(double balance) {
    double amount;
    cout << "\n  Enter deposit amount: $";
    cin  >> amount;
 
    if (amount <= 0) {
        cout << "  [!] Invalid amount.\n";
        return balance;
    }
 
    balance += amount;
    cout << "  Deposit successful!\n";
    cout << "  New Balance: $" << balance << "\n";
    return balance;
}
 
// --- Withdraw ---
double withdraw(double balance) {
    double amount;
    cout << "\n  Enter withdrawal amount: $";
    cin  >> amount;
 
    if (amount <= 0) {
        cout << "  [!] Invalid amount.\n";
        return balance;
    }
 
    if (amount > balance) {
        cout << "  [!] Insufficient funds.\n";
        cout << "  Available: $" << balance << "\n";
        return balance;
    }
 
    balance -= amount;
    cout << "  Withdrawal successful!\n";
    cout << "  New Balance: $" << balance << "\n";
    return balance;
}
 
// --- Add to history array ---
void addHistory(string history[], int& count, string record) {
    if (count < MAX_HISTORY) {
        history[count] = record;
        count++;
    }
}
 
// --- Show Transaction History ---
void showHistory(string history[], int count) {
    printLine('-', 40);
    cout << "     TRANSACTION HISTORY\n";
    printLine('-', 40);
 
    if (count == 0) {
        cout << "  No transactions yet.\n";
    } else {
        for (int i = 0; i < count; i++) {
            cout << "  [" << (i + 1) << "] " << history[i] << "\n";
        }
    }
    printLine('-', 40);
}

