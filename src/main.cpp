
#include <iostream>
#include <string>
#include "../include/constants.h"
//#include "../include/file_management.h"
#include "../include/structures.h"
#include "../include/group_operation.h"

//  g++ main.cpp group_operation.cpp -o  main

int main()
{
    Group allGroups[MAX_GROUPS];
    int totalGroups = 0;
    int choice;

    do
    {
        showMainMenu();
        cout << "Enter your choice (1-7): ";
        cin >> choice;
        cin.ignore();
        switch (choice)
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
            showSystemInfo();
            break;
        case 6:
            cout << "Thank you for using Hostel Expense Tracker!\n";
            break;

        default:
            cout << "Invalid choice! Please try again.\n";
            pauseConsole();
        }
    } while (choice!=6);
}