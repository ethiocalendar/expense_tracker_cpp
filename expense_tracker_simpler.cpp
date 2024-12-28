#include <iostream>    
#include <iomanip>     // For manipulating input/output formatting (e.g., fixed, setprecision)
#include <string>      // For handling strings and string operations
#include <sstream>     // For string stream operations (convert between strings and other types)
#include <map>         // For using the map container (associative array for key-value pairs)
#include <chrono>      // For high-precision time operations
#include <ctime>       // For working with calendar time and converting to human-readable format
#include <algorithm>  // For transform()

using namespace std;

// ANSI escape codes
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string GREEN = "\033[32m";
const string CYAN = "\033[36m";
const string YELLOW = "\033[33m";
const string RED = "\033[31m";
const string BLUE = "\033[34m";


// Function to validate if the input is a valid positive numeric value
bool isValidAmount(const string& input, double& amount) {
    stringstream ss(input);
    ss >> amount;
    return !ss.fail() && ss.eof() && amount >= 0;
}

// Function to get the current date in YYYY-MM-DD format
string getCurrentDate() {
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    tm* local_time = localtime(&now_time);

    char dateBuffer[11];
    strftime(dateBuffer, sizeof(dateBuffer), "%Y-%m-%d", local_time);

    return string(dateBuffer);
}

//  isValidDate function
bool isValidDate(const string& date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') return false;

    int year, month, day;
    char sep1, sep2;
    stringstream ss(date);
    ss >> year >> sep1 >> month >> sep2 >> day;

    if (ss.fail() || sep1 != '-' || sep2 != '-') return false;

    if (month < 1 || month > 12 || day < 1) return false;

    // Days per month
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Check for leap year
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29;
    }

    return day <= daysInMonth[month - 1];  // Only check if day is valid for the month
}



// Function to compare two dates in YYYY-MM-DD format
bool isDateInRange(const string& date, const string& startDate, const string& endDate) {
    return date >= startDate && date <= endDate;
}

// Function to add a new expense
void addExpense(string categories[], string descriptions[], string dates[], double amounts[], int& expenseCount, int maxExpenses) {
    while (expenseCount < maxExpenses) {
        cout << "\nEnter details for expense " << expenseCount + 1 << ":\n";

        string currentDate = getCurrentDate(); // Get today's date
        cout << "Today's Date (default): " << currentDate << endl;

      // Date Input
string enteredDate;
while (true) {
    cout << "Enter date (YYYY-MM-DD) or press Enter to use today's date: ";
    getline(cin, enteredDate); // Use getline consistently for user input

    if (enteredDate.empty()) {
        dates[expenseCount] = currentDate; // Use today's date if no input
        break;
    } else if (isValidDate(enteredDate)) {
        dates[expenseCount] = enteredDate; // Use the valid entered date
        break;
    } else {
        cout << "Invalid date format. Please enter a valid date (YYYY-MM-DD).\n";
        // No need to use cin.clear or ignore as getline already handles buffer clearing
    }
}



        // Category Input
        cout << "Category (e.g., Food, Transport, Entertainment): ";
        getline(cin, categories[expenseCount]);

        // Description Input
        cout << "Description: ";
        getline(cin, descriptions[expenseCount]);

        // Amount Input
        string inputAmount;
        double amount;
        while (true) {
            cout << "Amount: $";
            cin >> inputAmount;
            if (isValidAmount(inputAmount, amount)) {
                amounts[expenseCount] = amount; // Store the valid amount
                break;
            } else {
                cout << "Invalid input. Please enter a valid numeric amount.\n";
            }
        }

        expenseCount++;

        // Ask the user if they want to add another expense
        cout << "\nWould you like to add another expense? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore(); // Clear the buffer to handle the next loop correctly

        if (choice != 'y' && choice != 'Y') {
            break;
        }
    }

    if (expenseCount >= maxExpenses) {
        cout << "Expense limit reached! Cannot add more expenses.\n";
    }
}


// Function to search expenses by category
void searchByCategory(const string categories[], const string descriptions[], const string dates[], const double amounts[], int expenseCount, const string& searchCategory) {
    // Print with the exact category string that was entered by the user
    cout << "\nExpenses in category \"" << searchCategory << "\":" << endl;
    cout << left << setw(12) << "Date" << setw(15) << "Category" << setw(30) << "Description" << setw(10) << "Amount" << endl;
    cout << string(67, '-') << endl;

    bool found = false;
    for (int i = 0; i < expenseCount; i++) {
        if (categories[i] == searchCategory) {
            cout << left << setw(12) << dates[i]
                 << setw(15) << categories[i]
                 << setw(30) << descriptions[i]
                 << fixed << setprecision(2) << amounts[i] << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No expenses found in this category.\n";
    }
}

// Function to search expenses by date range
void searchByDateRange(const string categories[], const string descriptions[], const string dates[], const double amounts[], int expenseCount) {
    cout << "\nEnter the start date (YYYY-MM-DD): ";
    string startDate;
    getline(cin, startDate);

    if (!isValidDate(startDate)) {
        cout << "Invalid date format. Please use YYYY-MM-DD format.\n";
        return;
    }

    cout << "Enter the end date (YYYY-MM-DD): ";
    string endDate;
    getline(cin, endDate);

    if (!isValidDate(endDate)) {
        cout << "Invalid date format. Please use YYYY-MM-DD format.\n";
        return;
    }

    if (endDate < startDate) {
        cout << "End date must be after start date.\n";
        return;
    }

    // Get current date for future date warning
    string currentDate = getCurrentDate();
    if (startDate > currentDate || endDate > currentDate) {
        cout << "\nNote: Search includes future dates. No expenses will be found for dates after " 
             << currentDate << ".\n";
    }

    cout << "\nExpenses from " << startDate << " to " << endDate << ":\n";
    cout << left << setw(12) << "Date" << setw(15) << "Category" << setw(30) << "Description" << setw(10) << "Amount" << endl;
    cout << string(67, '-') << endl;

    bool found = false;
    for (int i = 0; i < expenseCount; i++) {
        if (isDateInRange(dates[i], startDate, endDate)) {
            cout << left << setw(12) << dates[i]
                 << setw(15) << categories[i]
                 << setw(30) << descriptions[i]
                 << setw(10) << fixed << setprecision(2) << amounts[i] << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No expenses found in the given date range.\n";
    }
}

// Function to display all expenses with separation into daily, monthly, yearly and previous year groups
void viewAllExpenses(const string categories[], const string descriptions[], const string dates[], const double amounts[], int expenseCount) {
    string currentDate = getCurrentDate();         // Get today's date
    string currentMonth = currentDate.substr(0, 7); // Extract current month (YYYY-MM)
    string currentYear = currentDate.substr(0, 4);  // Extract current year (YYYY)

    // Daily expenses
    cout << "\n" << CYAN << BOLD << "🌟 Daily Expenses (For " << currentDate << "): 🌟" << RESET << "\n";
    cout << string(80, '-') << endl;
    cout << left << setw(12) << "Date" << setw(15) << "Category" << setw(30) << "Description" << setw(10) << "Amount" << endl;
    cout << string(80, '-') << endl;

    double dailyTotal = 0.0;
    for (int i = 0; i < expenseCount; i++) {
        if (dates[i] == currentDate) {
            cout << left << setw(12) << dates[i]
                 << setw(15) << categories[i]
                 << setw(30) << descriptions[i]
                 << GREEN << setw(10) << fixed << setprecision(2) << amounts[i] << RESET << endl;
            dailyTotal += amounts[i];
        }
    }
    cout << string(80, '-') << endl;
    cout << BOLD << "Daily Total: " << GREEN << "$" << fixed << setprecision(2) << dailyTotal << RESET << "\n";

    // Monthly expenses
    cout << "\n" << CYAN << BOLD << "📅 Monthly Expenses (For " << currentMonth << "): 📅" << RESET << "\n";
    cout << string(80, '-') << endl;
    cout << left << setw(12) << "Date" << setw(15) << "Category" << setw(30) << "Description" << setw(10) << "Amount" << endl;
    cout << string(80, '-') << endl;

    double monthlyTotal = 0.0;
    for (int i = 0; i < expenseCount; i++) {
        if (dates[i].substr(0, 7) == currentMonth) {
            cout << left << setw(12) << dates[i]
                 << setw(15) << categories[i]
                 << setw(30) << descriptions[i]
                 << YELLOW << setw(10) << fixed << setprecision(2) << amounts[i] << RESET << endl;
            monthlyTotal += amounts[i];
        }
    }
    cout << string(80, '-') << endl;
    cout << BOLD << "Monthly Total: " << YELLOW << "$" << fixed << setprecision(2) << monthlyTotal << RESET << "\n";

    // Yearly expenses
    cout << "\n" << CYAN << BOLD << "📆 Yearly Expenses (For " << currentYear << "): 📆" << RESET << "\n";
    cout << string(80, '-') << endl;
    cout << left << setw(12) << "Date" << setw(15) << "Category" << setw(30) << "Description" << setw(10) << "Amount" << endl;
    cout << string(80, '-') << endl;

    double yearlyTotal = 0.0;
    for (int i = 0; i < expenseCount; i++) {
        if (dates[i].substr(0, 4) == currentYear) {
            cout << left << setw(12) << dates[i]
                 << setw(15) << categories[i]
                 << setw(30) << descriptions[i]
                 << BLUE << setw(10) << fixed << setprecision(2) << amounts[i] << RESET << endl;
            yearlyTotal += amounts[i];
        }
    }
    cout << string(80, '-') << endl;
    cout << BOLD << "Yearly Total: " << BLUE << "$" << fixed << setprecision(2) << yearlyTotal << RESET << "\n";

    // Previous years expenses
    map<string, double> previousYearTotals;

    for (int i = 0; i < expenseCount; i++) {
        string year = dates[i].substr(0, 4);
        if (year < currentYear) {
            previousYearTotals[year] += amounts[i];
        }
    }

    if (!previousYearTotals.empty()) {
        cout << "\n" << RED << BOLD << "💼 Expenses from Previous Years: 💼" << RESET << "\n";
        cout << string(80, '-') << endl;
        cout << left << setw(12) << "Year" << setw(15) << "Category" << setw(30) << "Description" << setw(10) << "Amount" << endl;
        cout << string(80, '-') << endl;

        for (int i = 0; i < expenseCount; i++) {
            string year = dates[i].substr(0, 4);
            if (year < currentYear) {
                cout << left << setw(12) << dates[i]
                     << setw(15) << categories[i]
                     << setw(30) << descriptions[i]
                     << RED << setw(10) << fixed << setprecision(2) << amounts[i] << RESET << endl;
            }
        }

        cout << string(80, '-') << endl;
        cout << BOLD << "Total for All Previous Years:" << RESET << endl;

        for (const auto& [year, total] : previousYearTotals) {
            cout << "Year: " << year << " Total: " << RED << "$" << fixed << setprecision(2) << total << RESET << "\n";
        }
    } else {
        cout << "\n" << RED << "No expenses found for previous years." << RESET << "\n";
    }
}



// Function to group expenses and display a summary for a given period
void displayPeriodSummary(const string dates[], const string categories[], const double amounts[], int expenseCount, const string& period) {
    map<string, map<string, double>> groupedExpenses;
    string currentDate = getCurrentDate();
    string currentMonth = currentDate.substr(0, 7); // Extract YYYY-MM
    string currentYear = currentDate.substr(0, 4);  // Extract YYYY

    for (int i = 0; i < expenseCount; i++) {
        string key;

        if (period == "daily") {
            if (dates[i] == currentDate) {
                key = dates[i]; // Include only today's expenses
            } else {
                continue;
            }
        } else if (period == "monthly") {
            // Include expenses from the current month
            if (dates[i].substr(0, 7) == currentMonth) {
                key = currentMonth;
            } else {
                continue;
            }
        } else if (period == "yearly") {
            // Include expenses from the current year
            if (dates[i].substr(0, 4) == currentYear) {
                key = currentYear;
            } else {
                continue;
            }
        }

        groupedExpenses[key][categories[i]] += amounts[i];
    }

    cout << "\nSummary of Expenses (" << period << "):\n";
    cout << left << setw(15) << "Period" << setw(20) << "Category" << setw(10) << "Total" << endl;
    cout << string(45, '-') << endl;

    double grandTotal = 0.0;
    for (const auto& entry : groupedExpenses) {
        for (const auto& categoryEntry : entry.second) {
            cout << left << setw(15) << entry.first
                 << setw(20) << categoryEntry.first
                 << right << setw(10) << fixed << setprecision(2) << categoryEntry.second << endl;
            grandTotal += categoryEntry.second;
        }
    }

    cout << string(45, '-') << endl;
    cout << "Grand Total: $" << fixed << setprecision(2) << grandTotal << endl;
}


// Function to display a pretty divider
void printDivider() {
    cout << string(50, '-') << endl;
}

// Function for a welcome banner
void displayWelcomeBanner() {
    cout << CYAN << BOLD << "==========================" << RESET << endl;
    cout << CYAN << BOLD << "  Expense Tracker  " << RESET << endl;
    cout << CYAN << BOLD << "==========================" << RESET << endl;
    cout << "\n" << YELLOW << "Welcome to the Expense Tracker!" << RESET << endl;
    printDivider();
}

int main() {
    const int maxExpenses = 100;
    string categories[maxExpenses];
    string descriptions[maxExpenses];
    string dates[maxExpenses];
    double amounts[maxExpenses];
    int expenseCount = 0;

    displayWelcomeBanner();

    while (true) {
        // Main Menu
        cout << "\n" << BLUE << BOLD << "What would you like to do next?" << RESET << endl;
        printDivider();
        cout << "1. Add a new expense" << endl;
        cout << "2. View all expenses" << endl;
        cout << "3. Search expenses by category" << endl;
        cout << "4. Search expenses by date range" << endl;
        cout << "5. Display summary by daily, monthly, or yearly periods" << endl;
        cout << "6. Exit" << endl;
        cout << "\n" << BOLD << "Enter your choice: " << RESET;
        int choice;
        cin >> choice;
        cin.ignore(); // Clear the newline character left in the input buffer

        switch (choice) {
        case 1:
            cout << GREEN << "Adding a new expense..." << RESET << endl;
            addExpense(categories, descriptions, dates, amounts, expenseCount, maxExpenses);
            break;

        case 2:
            cout << GREEN << "Viewing all expenses..." << RESET << endl;
            viewAllExpenses(categories, descriptions, dates, amounts, expenseCount);
            break;

       case 3: {
            cout << "\n" << BLUE << BOLD << "Enter category to search: " << RESET;
            string searchCategory;
            getline(cin, searchCategory);  // This alone is sufficient
            searchByCategory(categories, descriptions, dates, amounts, expenseCount, searchCategory);
            break;
            }

        case 4:
            cout << "\n" << BLUE << BOLD << "Enter start and end dates for the search (YYYY-MM-DD): " << RESET << endl;
            searchByDateRange(categories, descriptions, dates, amounts, expenseCount);
            break;

        case 5: {
            cout << "\n" << BLUE << "Select a period for the summary:" << RESET << endl;
            cout << "1. Daily\n2. Monthly\n3. Yearly" << endl;
            cout << "\n" << BOLD << "Enter your choice: " << RESET;
            int periodChoice;
            cin >> periodChoice;
            cin.ignore(); // Clear the newline character
            switch (periodChoice) {
            case 1:
                cout << GREEN << "Displaying daily summary..." << RESET << endl;
                displayPeriodSummary(dates, categories, amounts, expenseCount, "daily");
                break;
            case 2:
                cout << GREEN << "Displaying monthly summary..." << RESET << endl;
                displayPeriodSummary(dates, categories, amounts, expenseCount, "monthly");
                break;
            case 3:
                cout << GREEN << "Displaying yearly summary..." << RESET << endl;
                displayPeriodSummary(dates, categories, amounts, expenseCount, "yearly");
                break;
            default:
                cout << RED << "Invalid choice. Returning to main menu." << RESET << endl;
            }
            break;
        }

        case 6:
            cout << GREEN << "Goodbye! Thank you for using the Expense Tracker!" << RESET << endl;
            return 0;

        default:
            cout << RED << "Invalid choice. Please try again." << RESET << endl;
        }
    }
}

