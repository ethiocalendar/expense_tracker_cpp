
    Course: Computer Programming 1
    Project: Expense Tracker with Multiple Features

=====================================================================================


This is a full-featured "Expense Tracker" program implemented in C++. The user of this program will be able to add, view, search, and summarize expenses. The description of features and their implementations is as follows:




### Features
1. **Add New Expense**:
   - The user will be able to provide information about an expense: date, category, description, and amount.
- Date is validated to the format YYYY-MM-DD, not being a future date. If no date is given, it defaults to today.
   - Amounts should be positive numeric values.
  
2. **View All Expenses**:
   - Lists all expenses organized into daily, monthly, yearly, and previous year's sections.
- Provides a summary of each category in color, using ANSI, to make it more readable.

3. **Search by Category**:
   - A user can search for an expense in a specific category.
   - Results will be displayed in tabular format.

4. **Search by Date Range**:
   - Users will be able to search for expenses within a certain date range.
- It checks all the dates to be correct and in order.

5. **Summary by Period**:
   - Daily, monthly, or yearly summarizing of expenditures
   - Categorizes expenditures and provides a total of each

6. **User-Friendly Interface:**
 - Includes a welcome banner, options, and guideline instructions.
- Uses ANSI escape code text coloring to enhance user interaction with the terminal where possible.

7. **Validation and Error Handling**:
   - Validates user input, such as date format and numeric amounts.
   - Reports error on invalid input and provides for retry.

8. **Exit Option**:
- User can exit the program from the main menu anytime.

### Implementation Details
- **Data Storage**:
  - Expenses are stored in fixed-size arrays - up to 100 expenses.
  - Arrays include `categories`, `descriptions`, `dates`, and `amounts`.

- **Functions**:
  - `addExpense()`: It encapsulates the process of adding a new expense.
  - `viewAllExpenses()`: It lists all the expenses, which are categorized.
- `searchByCategory()`: This displays the expenses in any particular category.
- `searchByDateRange()`: Examines the date and displays the expense of all the dates within any given date range.
- `displayPeriodSummary()`: Summarizes expenses in periods such as day to day, monthly, or even yearly.
- `isValidAmount()`: For numeric input of amount.
- `isValidDate()`: The date format is correct and it is not in the future.
- `getCurrentDate()`: Returns the current date in YYYY-MM-DD format.
  - `isDateInRange()`: Tells if a date is within a certain range.

- **Formatting**:
  - `iomanip` library used to align output in columns with precision for amounts.
  - Colorful and styled text output, such as bold, green, and red, using ANSI escape codes.

### Workflow
1. The program starts a welcome banner and shows a menu of options.
2. Based on the users' input, the respective action is carried out.
3. The user inputs are validated at every step.
4. The program continues in a loop until the user chooses to exit.

### Example Use Cases
- A user wants to track daily expenses and view the totals by category.
- User wants a summary of monthly expenses compared to budget planning.
- Retrieval of travel expenses booked for a vacation period.

This is a simple yet powerful program, basically a personal finance manager meant for a terminal-based environment; features and their own validation included.


For school project pupose 
