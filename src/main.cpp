
#include <iostream>
#include <string>
#include "../include/constants.h"
#include "../include/file_management.h"
#include "../include/structures.h"
#include "../include/group_operation.h"

//  g++ main.cpp group_operation.cpp -o  main
// g++ main.cpp group_operation.cpp file_management.cpp -o  main

int main()
{
    Group allGroups[MAX_GROUPS];
    int totalGroups = 0;

    initializeSystem();
    // Ensuring to have the Files
    createReportsDirectory();


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
            saveAllGroupsData(allGroups,totalGroups);
            pauseConsole();
            break;
        case 6:
            loadAllGroupsData(allGroups,totalGroups);
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