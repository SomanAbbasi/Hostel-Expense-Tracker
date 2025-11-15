#pragma once
#include "structures.h"

// Main menu functions
void initializeSystem();
void showMainMenu();
void createNewGroup(Group allGroups[], int &totalGroups);
void manageExistingGroup(Group allGroups[], int totalGroups);
void showAllGroupsList(Group allGroups[], int totalGroups);
void showFinancialSummary(Group allGroups[], int totalGroups);
void showSystemInfo();

// Group management functions
void showGroupMenu(string groupName);
void addNewMember(Group &group);
void showAllMembers(Group &group);
void addNewExpense(Group &group);
void addNewTransaction(Group &group);
void showAllExpenses(Group &group);
void showAllTransactions(Group &group);
void calculateSettlements(Group &group);
void showGroupFinancials(Group &group);
void showMonthlyExpenses(Group &group);
void markTransactionSettled(Group &group);

// Helper functions
int findGroupByID(Group allGroups[], int totalGroups, string groupId);
int findMemberByID(Group &group, string memberId);
void displayAllCategories();
bool checkValidDate(string date);
void updateMemberBalances(Group &group);

void clearScreen();
void pauseConsole();
bool isValidDate(const string &date);
void printHeader();
