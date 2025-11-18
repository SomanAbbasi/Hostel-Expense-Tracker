#define byte win_byte_override
#include <windows.h>
#undef byte
#include <iostream>
#include <string>
#include "../include/constants.h"
#include "../include/file_management.h"
#include "../include/structures.h"
#include "../include/group_operation.h"
#include "../include/termcolor.hpp"

//  g++ file_management.cpp main.cpp group_operation.cpp -o main
// .\build.bat
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
        std::cout<<termcolor::green << "Enter your choice (1-8): ";
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
            std::cout<<termcolor::green << "Thank you for using Hostel Expense Tracker!\n";
            break;
        default:
            std::cout<<termcolor::red << "Invalid choice! Please try again.\n";
            pauseConsole();
        }
    } while (userChoice != 8);

    return 0;
}