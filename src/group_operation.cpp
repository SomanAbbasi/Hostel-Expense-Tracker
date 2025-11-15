
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include "../include/constants.h"
//#include "../include/file_management.h"
#include "../include/structures.h"
#include "../include/group_operation.h"

void initializeSystem()
{
    //  createReportsFolder();

    cout << " -- WELCOME TO HOSTELLITE EXPENSE TRACKER --" << endl;
}

void showMainMenu()
{
    clearScreen();
    printHeader();
    cout << "1. Create New Group\n";
    cout << "2. Manage Existing Group\n";
    cout << "4. Financial Overview\n";
    cout << "3. Show All Groups\n";
    cout << "5. Save All Data\n";
    cout << "6. Load All Data\n";
    cout << "7. System Info\n";
    cout << "8. Exit\n";
    cout << "==============================\n";
}

void createNewGroup(Group allGroups[], int &totalGroups)
{
    if (totalGroups >= MAX_GROUPS)
    {
        cout << "Cannot create more groups! Maximum limit reached" << endl;
        pauseConsole();
        return;
    }

    cout << "\n=== CREATE NEW GROUP ===\n";
    cout << "Enter Group ID: ";
    getline(cin, allGroups[totalGroups].groupId);
    // Check if ID already exits
    if (findGroupByID(allGroups, totalGroups, allGroups[totalGroups].groupId) != -1)
    {
        cout << "Error: Group with this ID already exists!\n";
        pauseConsole();
        return;
    }
    cout << "Enter Group Name: ";
    getline(cin, allGroups[totalGroups].groupName);

    // Initialize Group data
    allGroups[totalGroups].memberCount = 0;
    allGroups[totalGroups].expenseCount = 0;
    allGroups[totalGroups].transactionCount = 0;

    totalGroups++;
    cout << "Group created successfully!\n";

    // Add group first member(admin)
    cout << "Let's add yourself as the first member:\n";
    addNewMember(allGroups[totalGroups - 1]);

    pauseConsole();
}

void manageExistingGroup(Group allGroups[], int totalGroups) { cout << "Testing" << endl; }
void showAllGroupsList(Group allGroups[], int totalGroups) { cout << "Testing" << endl; }
void showFinancialSummary(Group allGroups[], int totalGroups) { cout << "Testing" << endl; }
void showSystemInfo() { cout << "Testing" << endl; }

void showGroupMenu(string groupName) { cout << "Testing" << endl; }
void showAllMembers(Group &group) { cout << "Testing" << endl; }
void addNewExpense(Group &group) { cout << "Testing" << endl; }
void addNewTransaction(Group &group) { cout << "Testing" << endl; }
void showAllExpenses(Group &group) { cout << "Testing" << endl; }
void showAllTransactions(Group &group) { cout << "Testing" << endl; }
void calculateSettlements(Group &group) { cout << "Testing" << endl; }
void showGroupFinancials(Group &group) { cout << "Testing" << endl; }
void showMonthlyExpenses(Group &group) { cout << "Testing" << endl; }
void markTransactionSettled(Group &group) { cout << "Testing" << endl; }

void displayAllCategories() { cout << "Testing" << endl; }
bool checkValidDate(string date) { cout << "Testing" << endl ; return true; }
void updateMemberBalances(Group &group) { cout << "Testing" << endl; }

bool isValidDate(const string &date) { cout << "Testing" << endl;return true; }

void addNewMember(Group &group)
{
    if (group.memberCount >= MAX_MEMBERS_PER_GROUP)
    {
        cout << "Cannot add more members! Group is full.\n";
        pauseConsole();
        return;
    }

    cout << "\n=== ADD NEW MEMBER ===\n";
    cout << "Enter member name: ";
    getline(cin, group.members[group.memberCount].name);

    cout << "Enter member ID: ";
    getline(cin, group.members[group.memberCount].id);

    // Check if member ID already exists
    if (findMemberByID(group, group.members[group.memberCount].id) != -1)
    {
        cout << "Error: Member with this ID already exists in the group!\n";
        pauseConsole();
        return;
    }
    group.members[group.memberCount].totalPaid = 0.0;
    group.members[group.memberCount].totalSpent = 0.0;
    group.memberCount += 1;
    cout << "Member added successfully!\n";
    pauseConsole();
}
int findMemberByID(Group &group, string memberId)
{
    for (int i = 0; i < group.memberCount; i++)
    {
        if (group.members[i].id == memberId)
        {
            return 1;
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
            return 1;
        }
    }
    return -1;
}

void clearScreen()
{
    // system("cls");
    cout<<"Testing "<<endl;
}

void pauseConsole()
{
    cout << "\nPress Enter to continue...";
    cin.get();
}

void printHeader()
{
    cout << "==============================\n";
    cout << " -- WELCOME TO HOSTELLITE EXPENSE TRACKER --" << endl;
    cout << "==============================\n";
}
