#define byte win_byte_override
#include <windows.h>
#undef byte
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include "../include/constants.h"
// #include "../include/file_management.h"
#include "../include/structures.h"
#include "../include/group_operation.h"
#include "../include/termcolor.hpp"

using namespace std;

void initializeSystem()
{
    //  createReportsFolder();

    std::cout<<termcolor::green << " -- WELCOME TO HOSTELLITE EXPENSE TRACKER --" << endl;
}

void showMainMenu()
{
    clearScreen();
    printHeader();
    std::cout<<termcolor::blue << "1. Create New Group\n";
    std::cout<<termcolor::blue << "2. Manage Existing Group\n";
    std::cout<<termcolor::blue << "3. Show All Groups\n";
    std::cout<<termcolor::blue << "4. Financial Overview\n";

    std::cout<<termcolor::blue << "5. Save All Data\n";
    std::cout<<termcolor::blue << "6. Load All Data\n";
    std::cout<<termcolor::blue << "7. System Info\n";
    std::cout<<termcolor::blue << "8. Exit\n";
    std::cout<<termcolor::blue << "==============================\n";
}

void createNewGroup(Group allGroups[], int &totalGroups)
{
    if (totalGroups >= MAX_GROUPS)
    {
        std::cout<<termcolor::red << "Cannot create more groups! Maximum limit reached" << endl;
        pauseConsole();
        return;
    }

    std::cout<<termcolor::blue << "\n=== CREATE NEW GROUP ===\n";
    std::cout<<termcolor::green << "Enter Group ID: ";
    getline(cin, allGroups[totalGroups].groupId);
    // Check if ID already exits
    if (findGroupByID(allGroups, totalGroups, allGroups[totalGroups].groupId) != -1)
    {
        std::cout<<termcolor::red << "Error: Group with this ID already exists!\n";
        pauseConsole();
        return;
    }
    std::cout<<termcolor::green << "Enter Group Name: ";
    getline(cin, allGroups[totalGroups].groupName);

    // Initialize Group data
    allGroups[totalGroups].memberCount = 0;
    allGroups[totalGroups].expenseCount = 0;
    allGroups[totalGroups].transactionCount = 0;

    totalGroups++;
    std::cout<<termcolor::green  << "Group created successfully!\n";

    // Add group first member(admin)
    std::cout<<termcolor::green << "Let's add yourself as the first member:\n";
    addNewMember(allGroups[totalGroups - 1]);

    pauseConsole();
}

void manageExistingGroup(Group allGroups[], int totalGroups)
{
    if (totalGroups == 0)
    {
        std::cout<<termcolor::red << "No groups available. Please create a group first.\n";
        pauseConsole();
        return;
    }
    showAllGroupsList(allGroups, totalGroups);
    string selectedGroupId;
    std::cout<<termcolor::green << "Enter Group ID to manage: ";
    getline(cin, selectedGroupId);
    int groupIndex = findGroupByID(allGroups, totalGroups, selectedGroupId);
    if (groupIndex == -1)
    {
        std::cout<<termcolor::red << "Group not found!\n";
        pauseConsole();
        return;
    }

    Group &currentGroup = allGroups[groupIndex];
    int groupChoice;
    do
    {
        clearScreen();
        showGroupMenu(currentGroup.groupName);
        std::cout<<termcolor::green << "Enter your choice (1-13): ";
        cin >> groupChoice;
        cin.ignore();

        switch (groupChoice)
        {
        case 1:
            addNewMember(currentGroup);
            break;
        case 2:
            showAllMembers(currentGroup);
            break;
        case 3:
            addNewExpense(currentGroup);
            break;
        case 4:
            addNewTransaction(currentGroup);
            break;
        case 5:
            showAllExpenses(currentGroup);
            break;
        case 6:
            showAllTransactions(currentGroup);
            break;
        case 7:
            calculateSettlements(currentGroup);
            break;
        case 8:
            showGroupFinancials(currentGroup);
            break;
        case 9:
            showMonthlyExpenses(currentGroup);
            break;
        case 10:
            markTransactionSettled(currentGroup);
            break;
        case 11:
            updateMemberBalances(currentGroup);
            break;
        case 12:
            std::cout<<termcolor::green << "Returning to main menu...\n";
            break;
        default:
            std::cout<<termcolor::red << "Invalid choice!\n";
            pauseConsole();
        }
    } while (groupChoice != 12);
}

void showAllGroupsList(Group allGroups[], int totalGroups)
{
    std::cout<<termcolor::green << "\n=== ALL GROUPS ===\n";

    if (totalGroups == 0)
    {
        std::cout<<termcolor::red << "No groups found.\n";
        pauseConsole();
        return;
    }

    for (int i = 0; i < totalGroups; i++)
    {
        std::cout<<termcolor::blue << (i + 1) << ". " << allGroups[i].groupName
             << " (ID: " << allGroups[i].groupId << ")\n";
        std::cout<<termcolor::blue << "   Members: " << allGroups[i].memberCount
             << " | Expenses: " << allGroups[i].expenseCount
             << " | Transactions: " << allGroups[i].transactionCount << endl;
    }
    pauseConsole();
}

void showFinancialSummary(Group allGroups[], int totalGroups)
{
    if (totalGroups == 0)
    {
        std::cout<<termcolor::red << "No groups available.\n";
        pauseConsole();
        return;
    }

    showAllGroupsList(allGroups, totalGroups);
    string selectedGroupId;
    std::cout<<termcolor::green << "Enter Group ID for financial overview: ";
    getline(cin, selectedGroupId);

    int groupIndex = findGroupByID(allGroups, totalGroups, selectedGroupId);
    if (groupIndex == -1)
    {
       std::cout<<termcolor::red << "Group not found!\n";
        pauseConsole();
        return;
    }

    showGroupFinancials(allGroups[groupIndex]);
}
void showSystemInfo()
{

    clearScreen();
    std::cout<<termcolor::blue << "========================================\n";
    std::cout<<termcolor::blue << "        SYSTEM INFORMATION\n";
    std::cout<<termcolor::blue << "========================================\n";
    std::cout<<termcolor::blue << "Hostel Expense Tracker - Group Management\n";
    std::cout<<termcolor::blue << "\nFeatures:\n";
    std::cout<<termcolor::blue << "- Create and manage multiple groups\n";
    std::cout<<termcolor::blue << "- Track expenses and shared costs\n";
    std::cout<<termcolor::blue << "- Record borrow/lend transactions\n";
    std::cout<<termcolor::blue << "- Calculate settlements automatically\n";
    std::cout<<termcolor::blue << "- View financial summaries\n";
    std::cout<<termcolor::blue << "- Monthly expense tracking\n";
    std::cout<<termcolor::blue << "\nLimits:\n";
    std::cout<<termcolor::blue << "- Maximum " << MAX_GROUPS << " groups\n";
    std::cout<<termcolor::blue << "- Maximum " << MAX_MEMBERS_PER_GROUP << " members per group\n";
    std::cout<<termcolor::blue << "- Maximum " << MAX_EXPENSES_PER_GROUP << " expenses per group\n";
    std::cout<<termcolor::blue << "- Maximum " << MAX_TRANSACTIONS_PER_GROUP << " transactions per group\n";
    std::cout<<termcolor::blue << "========================================\n";
    pauseConsole();
}

void showGroupMenu(string groupName)
{

    printHeader();
    std::cout<<termcolor::blue << "MANAGING GROUP: " << groupName << "\n";
    std::cout<<termcolor::blue << "========================================\n";
    std::cout<<termcolor::blue << "1. Add New Member\n";
    std::cout<<termcolor::blue << "2. Show All Members\n";
    std::cout<<termcolor::blue << "3. Add New Expense\n";
    std::cout<<termcolor::blue << "4. Add Borrow/Lend Transaction\n";
    std::cout<<termcolor::blue << "5. Show All Expenses\n";
    std::cout<<termcolor::blue << "6. Show All Transactions\n";
    std::cout<<termcolor::blue << "7. Calculate Settlements\n";
    std::cout<<termcolor::blue << "8. Financial Overview\n";
    std::cout<<termcolor::blue << "9. Monthly Summary\n";
    std::cout<<termcolor::blue << "10. Settle Transaction\n";
    std::cout<<termcolor::blue << "11. Update Balances\n";
    std::cout<<termcolor::blue << "12. Back to Main Menu\n";
    std::cout<<termcolor::blue << "========================================\n";
}

void addNewMember(Group &group)
{
    if (group.memberCount >= MAX_MEMBERS_PER_GROUP)
    {
        std::cout<<termcolor::red << "Cannot add more members! Group is full.\n";
        pauseConsole();
        return;
    }

    std::cout<<termcolor::blue << "\n=== ADD NEW MEMBER ===\n";
    std::cout<<termcolor::green << "Enter member name: ";
    getline(cin, group.members[group.memberCount].name);

    std::cout<<termcolor::green << "Enter member ID: ";
    getline(cin, group.members[group.memberCount].id);

    // Check if member ID already exists
    if (findMemberByID(group, group.members[group.memberCount].id) != -1)
    {
        std::cout<<termcolor::red << "Error: Member with this ID already exists in the group!\n";
        pauseConsole();
        return;
    }
    group.members[group.memberCount].totalPaid = 0.0;
    group.members[group.memberCount].totalSpent = 0.0;
    group.memberCount += 1;
    std::cout<<termcolor::green << "Member added successfully!\n";
    pauseConsole();
}

void showAllMembers(Group &group)
{
    if (group.memberCount == 0)
    {
        std::cout<<termcolor::red << "No members in group. Please add members first.\n";
        pauseConsole();
        return;
    }
    for (int i = 0; i < group.memberCount; i++)
    {
        std::cout<<termcolor::blue << (i + 1) << ". " << group.members[i].name
             << " (ID: " << group.members[i].id << ")\n";
        std::cout<<termcolor::blue << "   Total Paid: Rs." << fixed << setprecision(2)
             << group.members[i].totalPaid;
        std::cout<<termcolor::blue << " | Total Spent: Rs." << group.members[i].totalSpent;
        std::cout<<termcolor::blue << " | Balance: Rs." << (group.members[i].totalPaid - group.members[i].totalSpent) << endl;
    }
    pauseConsole();
}

void addNewExpense(Group &group)
{
    if (group.memberCount == 0)
    {
        std::cout<<termcolor::red << "No members in group. Please add members first.\n";
        pauseConsole();
        return;
    }

    if (group.expenseCount >= MAX_EXPENSES_PER_GROUP)
    {
        std::cout<<termcolor::red << "Cannot add more expenses! Maximum limit reached.\n";
        pauseConsole();
        return;
    }

    std::cout<<termcolor::red << "\n=== ADD NEW EXPENSE ===\n";

    // Show Categories
    displayAllCategories();
    int categoryChoice;
    std::cout<<termcolor::green << "Select category (1-" << MAX_CATEGORIES << "): ";
    cin >> categoryChoice;
    cin.ignore();

    if (categoryChoice < 1 || categoryChoice > MAX_CATEGORIES)
    {
        std::cout<<termcolor::red << "Invalid category selection!\n";
        pauseConsole();
        return;
    }

    group.expenses[group.expenseCount].category = categories[categoryChoice - 1];

    std::cout<<termcolor::green << "Enter amount: Rs.";
    cin >> group.expenses[group.expenseCount].amount;
    cin.ignore();

    if (group.expenses[group.expenseCount].amount <= 0)
    {
        std::cout<<termcolor::red << "Amount must be positive!\n";
        pauseConsole();
        return;
    }

    showAllMembers(group);
    int payerIndex;
    std::cout<<termcolor::green << "Select who paid (1-" << group.memberCount << "): ";
    cin >> payerIndex;
    cin.ignore();

    if (payerIndex < 1 || payerIndex > group.memberCount)
    {
        std::cout<<termcolor::red << "Invalid member selection!\n";
        pauseConsole();
        return;
    }

    group.expenses[group.expenseCount].paidBy = payerIndex - 1;

    // Update member balances
    group.members[payerIndex - 1].totalPaid += group.expenses[group.expenseCount].amount;

    double sharePerPerson = group.expenses[group.expenseCount].amount / group.memberCount;
    for (int i = 0; i < group.memberCount; i++)
    {
        group.members[i].totalSpent += sharePerPerson;
    }

    std::cout<<termcolor::green << "Enter date (DD-MM-YYYY): ";
    getline(cin, group.expenses[group.expenseCount].date);

    if (!checkValidDate(group.expenses[group.expenseCount].date))
    {
        std::cout<<termcolor::red << "Invalid date format! Using current date.\n";

        //  current date
        time_t now = time(0);
        tm *t = localtime(&now);

        int day = t->tm_mday;
        int month = t->tm_mon + 1;
        int year = t->tm_year + 1900;

        string dayStr = (day < 10) ? "0" + to_string(day) : to_string(day);
        string monthStr = (month < 10) ? "0" + to_string(month) : to_string(month);

        group.expenses[group.expenseCount].date = dayStr + "-" + monthStr + "-" + to_string(year);
    }

    cout<<termcolor::green << "Enter description: ";
    getline(cin, group.expenses[group.expenseCount].description);

    group.expenses[group.expenseCount].isSettled = false;
    group.expenseCount++;

    cout<<termcolor::green << "Expense added successfully!\n";
    cout<<termcolor::green << "Each member owes: Rs." << sharePerPerson << endl;
    pauseConsole();
}

void addNewTransaction(Group &group)
{
    if (group.memberCount < 2)
    {
        std::cout<<termcolor::red << "Need at least 2 members for transactions!\n";
        pauseConsole();
        return;
    }
    if (group.transactionCount >= MAX_TRANSACTIONS_PER_GROUP)
    {
        std::cout<<termcolor::red << "Cannot add more transactions! Maximum limit reached.\n";
        pauseConsole();
        return;
    }

    std::cout<<termcolor::blue << "\n=== ADD BORROW/LEND TRANSACTION ===\n";

    showAllMembers(group);
    int borrowerIndex, lenderIndex;
    std::cout<<termcolor::green << "Select who borrowed money (1-" << group.memberCount << "): ";
    cin >> borrowerIndex;
    std::cout<<termcolor::green << "Select who lent money (1-" << group.memberCount << "): ";
    cin >> lenderIndex;
    cin.ignore();

    if (borrowerIndex < 1 || borrowerIndex > group.memberCount ||
        lenderIndex < 1 || lenderIndex > group.memberCount ||
        borrowerIndex == lenderIndex)
    {
        std::cout<<termcolor::red << "Invalid member selection!\n";
        pauseConsole();
        return;
    }

    group.transactions[group.transactionCount].fromMember = borrowerIndex - 1;
    group.transactions[group.transactionCount].toMember = lenderIndex - 1; // Fixed: use lenderIndex

    std::cout<<termcolor::green << "Enter amount: Rs.";
    cin >> group.transactions[group.transactionCount].amount;
    cin.ignore();

    std::cout<<termcolor::green << "Enter date (DD-MM-YYYY): ";
    getline(cin, group.transactions[group.transactionCount].date);

    if (!checkValidDate(group.transactions[group.transactionCount].date))
    {
        std::cout<<termcolor::red << "Invalid date format! Using current date.\n";

        //  current system date
        time_t now = time(0);
        tm *t = localtime(&now);

        int day = t->tm_mday;
        int month = t->tm_mon + 1;
        int year = t->tm_year + 1900;

        //  date format
        string dayStr = (day < 10) ? "0" + to_string(day) : to_string(day);
        string monthStr = (month < 10) ? "0" + to_string(month) : to_string(month);

        group.transactions[group.transactionCount].date = dayStr + "-" + monthStr + "-" + to_string(year);
    }

    std::cout<<termcolor::green << "Enter reason/description: ";
    getline(cin, group.transactions[group.transactionCount].description);

    group.transactions[group.transactionCount].isSettled = false;
    group.transactionCount++;

    std::cout<<termcolor::green << "Transaction recorded successfully!\n";
    pauseConsole();
}

void showAllExpenses(Group &group)
{
    std::cout<<termcolor::blue << "\n=== ALL EXPENSES ===\n";

    if (group.expenseCount == 0)
    {
        std::cout<<termcolor::red << "No expenses recorded.\n";
        pauseConsole();
        return;
    }

    double totalExpenses = 0;
    for (int i = 0; i < group.expenseCount; i++)
    {
        std::cout<<termcolor::blue << (i + 1) << ". " << group.expenses[i].category
             << " - Rs." << fixed << setprecision(2) << group.expenses[i].amount << "\n";
        std::cout<<termcolor::blue << "   Paid by: " << group.members[group.expenses[i].paidBy].name;
        std::cout<<termcolor::blue << " | Date: " << group.expenses[i].date;
        std::cout<<termcolor::blue << " | " << group.expenses[i].description;
        if (group.expenses[i].isSettled)
        {
            std::cout<<termcolor::green << " [SETTLED]";
        }
        std::cout<<std::endl;
        totalExpenses += group.expenses[i].amount;
    }

    std::cout<<termcolor::green << "\nTotal Expenses: Rs." << totalExpenses << endl;
    pauseConsole();
}
void showAllTransactions(Group &group)
{
    std::cout<<termcolor::blue << "\n=== ALL TRANSACTION ===\n";

    if (group.transactionCount == 0)
    {
        std::cout<<termcolor::red << "No transaction recorded.\n";
        pauseConsole();
        return;
    }

    for (int i = 0; i < group.transactionCount; i++)
    {
        std::cout<<termcolor::blue << (i + 1) << ". " << group.members[group.transactions[i].fromMember].name
             << " borrowed Rs." << fixed << setprecision(2) << group.transactions[i].amount
             << " from " << group.members[group.transactions[i].toMember].name << "\n";
        std::cout<<termcolor::blue << "   Date: " << group.transactions[i].date;
        std::cout<<termcolor::blue << " | Reason: " << group.transactions[i].description;
        if (group.transactions[i].isSettled)
        {
            std::cout<<termcolor::green << " [SETTLED]";
        }
        std::cout<<std::endl;
    }

    pauseConsole();
}
void calculateSettlements(Group &group)
{
    if (group.memberCount == 0)
    {
        std::cout<<termcolor::red << "No members in group.\n";
        pauseConsole();
        return;
    }

    std::cout<<termcolor::blue << "\n=== SETTLEMENT CALCULATIONS ===\n";

    // Calculate net balance for each memeber
    double memberBalances[MAX_MEMBERS_PER_GROUP] = {0};
    for (int i = 0; i < group.expenseCount; i++)
    {
        if (!group.expenses[i].isSettled)
        {
            double share = group.expenses[i].amount / group.memberCount;
            memberBalances[group.expenses[i].paidBy] += group.expenses[i].amount - share;

            for (int j = 0; j < group.memberCount; j++)
            {
                if (j != group.expenses[i].paidBy)
                {
                    memberBalances[j] -= share;
                }
            }
        }
    }

    // Include transactions in balance calculation
    for (int i = 0; i < group.transactionCount; i++)
    {
        if (!group.transactions[i].isSettled)
        {
            memberBalances[group.transactions[i].fromMember] -= group.transactions[i].amount;
            memberBalances[group.transactions[i].toMember] += group.transactions[i].amount;
        }
    }

    // Show current balances
    cout<<termcolor::green << "Current Balances:\n";
    for (int i = 0; i < group.memberCount; i++)
    {
        cout<<termcolor::blue << group.members[i].name << ": Rs." << fixed << setprecision(2) << memberBalances[i];
        if (memberBalances[i] > 0)
        {
            std::cout<<termcolor::green << " (should receive)";
        }
        else if (memberBalances[i] < 0)
        {
            std::cout<<termcolor::green << " (should pay)";
        }
        std::cout<<termcolor::reset << endl;
    }

    std::cout<<termcolor::green << "\nSettlement Instructions:\n";
    bool needsSettlement = false;

    // settlement calculation
    for (int i = 0; i < group.memberCount; i++)
    {
        for (int j = i + 1; j < group.memberCount; j++)
        {
            if (memberBalances[i] < 0 && memberBalances[j] > 0)
            {
                double amount = min(-memberBalances[i], memberBalances[j]);
                if (amount > 0.01)
                {
                    std::cout<<termcolor::blue << group.members[i].name << " should pay "
                         << group.members[j].name << ": Rs." << amount << endl;
                    memberBalances[i] += amount;
                    memberBalances[j] -= amount;
                    needsSettlement = true;
                }
            }
        }
    }

    if (!needsSettlement)
    {
        std::cout<<termcolor::red << "No settlements needed. All balances are settled!\n";
    }

    pauseConsole();
}

void showGroupFinancials(Group &group)
{
    std::cout<<termcolor::blue << "\n=== FINANCIAL OVERVIEW ===\n";

    if (group.memberCount == 0)
    {
        std::cout<<termcolor::red << "No members in group.\n";
        pauseConsole();
        return;
    }
    // Calculate total expenses
    double totalGroupExpenses = 0;
    for (int i = 0; i < group.expenseCount; i++)
    {
        totalGroupExpenses += group.expenses[i].amount;
    }

    std::cout<<termcolor::green << "Total Group Expenses: Rs." << fixed << setprecision(2) << totalGroupExpenses << endl;

    if (group.memberCount > 0)
    {
        std::cout<<termcolor::green << "Average per Member: Rs." << totalGroupExpenses / group.memberCount << endl;
    }

    std::cout<<termcolor::green << "\nMember Contributions:\n";
    for (int i = 0; i < group.memberCount; i++)
    {
        double balance = group.members[i].totalPaid - group.members[i].totalSpent;
        std::cout<<termcolor::blue << group.members[i].name << ":\n";
        std::cout<<termcolor::blue << "  Paid: Rs." << group.members[i].totalPaid;
        std::cout<<termcolor::blue << " | Spent: Rs." << group.members[i].totalSpent;
        std::cout<<termcolor::blue << " | Balance: Rs." << balance;
        if (balance > 0)
        {
            std::cout<<termcolor::green << " (should receive)";
        }
        else if (balance < 0)
        {
            std::cout<<termcolor::green << " (should pay)";
        }
        std::cout<<termcolor::reset << endl;
    }

    std::cout<<termcolor::green << "\nOutstanding Debts:\n";
    bool hasDebts = false;
    for (int i = 0; i < group.transactionCount; i++)
    {
        if (!group.transactions[i].isSettled)
        {
            std::cout<<termcolor::blue << group.members[group.transactions[i].fromMember].name
                 << " owes " << group.members[group.transactions[i].toMember].name
                 << ": Rs. " << group.transactions[i].amount << endl;
            hasDebts = true;
        }
    }

    if (!hasDebts)
    {
        std::cout<<termcolor::green << "No outstanding debts.\n";
    }
    pauseConsole();
}
void showMonthlyExpenses(Group &group)
{
    std::cout<<termcolor::blue << "\n=== MONTHLY EXPENSE SUMMARY ===\n";

    string monthYear;
    std::cout<<termcolor::green << "Enter month and year to view (MM-YYYY): ";
    getline(cin, monthYear);

    if (monthYear.length() != 7 || monthYear[2] != '-')
    {
        std::cout<<termcolor::green << "Invalid format! Please use MM-YYYY format.\n";
        pauseConsole();
        return;
    }

    double monthlyTotal = 0;
    int expenseCount = 0;
    std::cout<<termcolor::green << "\nExpenses for " << monthYear << ":\n";

    for (int i = 0; i < group.expenseCount; i++)
    {
        string expenseMonthYear = group.expenses[i].date.substr(3, 7);
        if (expenseMonthYear == monthYear)
        {
            std::cout<<termcolor::blue << "*" << group.expenses[i].category << " :Rs."
                 << fixed << setprecision(2) << group.expenses[i].amount
                 << "(" << group.members[group.expenses[i].paidBy].name << ")" << endl;
            monthlyTotal += group.expenses[i].amount;
            expenseCount++;
        }
    }

    std::cout<<termcolor::green << "\nSummary for " << monthYear << ":\n";
    std::cout<<termcolor::green << "Total Expenses: Rs." << monthlyTotal << endl;
    std::cout<<termcolor::green << "Number of Expenses: " << expenseCount << endl;

    if (group.memberCount > 0)
    {
        std::cout<<termcolor::green << "Average per Member: Rs." << monthlyTotal / group.memberCount << endl;
    }

    if (expenseCount == 0)
    {
        std::cout<<termcolor::green << "No expenses found for this month.\n";
    }

    pauseConsole();
}
void markTransactionSettled(Group &group)
{
    if (group.transactionCount == 0)
    {
        std::cout<<termcolor::red << "No transactions available.\n";
        pauseConsole();
        return;
    }

    showAllTransactions(group);

    int transactionNumber;
    std::cout<<termcolor::green << "Enter transaction number to mark as settled (1-" << group.transactionCount << "): ";
    cin >> transactionNumber;
    cin.ignore();

    if (transactionNumber < 1 || transactionNumber > group.transactionCount)
    {
        std::cout<<termcolor::red << "Invalid transaction number!\n";
        pauseConsole();
        return;
    }
    group.transactions[transactionNumber - 1].isSettled = true;
    std::cout<<termcolor::green << "Transaction marked as settled!\n";
    pauseConsole();
}

void displayAllCategories()
{
    std::cout<<termcolor::green << "Available Categories:\n";
    for (int i = 0; i < MAX_CATEGORIES; i++)
    {
        std::cout<<termcolor::green << (i + 1) << ". " << categories[i] << endl;
    }
}

void updateMemberBalances(Group &group)
{
    std::cout<<termcolor::blue << "\n=== UPDATING MEMBER BALANCES ===\n";
    // Reset all balances
    for (int i = 0; i < group.memberCount; i++)
    {
        group.members[i].totalPaid = 0.0;
        group.members[i].totalSpent = 0.0;
    }

    // Recalculate from expenses
    for (int i = 0; i < group.expenseCount; i++)
    {
        group.members[group.expenses[i].paidBy].totalPaid += group.expenses[i].amount;

        double share = group.expenses[i].amount / group.memberCount;
        for (int j = 0; j < group.memberCount; j++)
        {
            group.members[j].totalSpent += share;
        }
    }

    std::cout<<termcolor::green << "All member balances have been updated!\n";
    pauseConsole();
}
bool checkValidDate(string date)
{
    if (date.length() != 10)
    {

        return false;
    }
    if (date[2] != '-' || date[5] != '-')
    {
        return false;
    }

    for (int i = 0; i < 10; i++)
    {
        if (i == 2 || i == 5)
        {
            continue;
        }
        if (!isdigit(date[i]))
        {
            return false;
        }
    }
    return true;
}

// bool isValidDate(const string &date)
// {
// }

int findMemberByID(Group &group, string memberId)
{
    for (int i = 0; i < group.memberCount; i++)
    {
        if (group.members[i].id == memberId)
        {
            return i;
        }
    }
    return -1;
}
int findGroupByID(Group allGroups[], int totalGroups, string groupId)
{
    for (int i = 0; i < totalGroups; i++)
    {
        if (allGroups[i].groupId == groupId)
        {
            return i;
        }
    }
    return -1;
}

void clearScreen()
{
    system("cls");
    // cout << "Testing " << endl;
}

void pauseConsole()
{
    std::cout<<termcolor::green << "\nPress Enter to continue...";
    cin.get();
}

void printHeader()
{
    std::cout<<termcolor::blue << "==============================\n";
    std::cout<<termcolor::blue << " -- WELCOME TO HOSTELLITE EXPENSE TRACKER --" << endl;
    std::cout<<termcolor::blue << "==============================\n";
}

