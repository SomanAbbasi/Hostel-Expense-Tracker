
#include <iostream>
#include <string>
#include "../include/constants.h"
// #include "../include/file_management.h"
#include "../include/structures.h"
#include "../include/group_operation.h"

//  g++ main.cpp group_operation.cpp -o  main
int main()
{
    Group allGroups[MAX_GROUPS];
    int totalGroups = 0;

    initializeSystem();

    int userChoice;

    do
    {
        showMainMenu();
        cout << "Enter your choice (1-8): ";
        cin >> userChoice;
        cin.ignore();

        switch (userChoice)
        {
        case 1:
            createNewGroup(allGroups, totalGroups);
            break;
        case 2:
            manageExistingGroup(allGroups, totalGroups);
            break;
        case 3:
            showAllGroupsList(allGroups, totalGroups);

            break;
        case 4:
            showFinancialSummary(allGroups, totalGroups);

            break;
        case 5:
            cout << "Save feature not implemented in this version.\n";
            pauseConsole();
            break;
        case 6:
            cout << "Load feature not implemented in this version.\n";
            pauseConsole();
            break;
        case 7:
            showSystemInfo();
            break;
        case 8:
            cout << "Thank you for using Hostel Expense Tracker!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
            pauseConsole();
        }
    } while (userChoice != 8);

    return 0;
}