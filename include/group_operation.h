#pragma once
#include "structures.h"

void initializeSystem();
void showMainMenu();
void createGroup(Group*& groups, int& groupCount, int& groupCapacity);
void manageGroup(Group* groups, int groupCount);
void showAllGroups(const Group* groups, int groupCount);
int findGroupById(const Group* groups, int groupCount, const string& groupId);
void addMemberToGroup(Group& group);
void showGroupMembers(const Group& group);
void addExpenseToGroup(Group& group);
void addTransactionToGroup(Group& group);
void showGroupExpenses(const Group& group);
void showGroupTransactions(const Group& group);
void calculateGroupSettlement(const Group& group);
void showFinancialOverview(const Group* groups, int groupCount, int specificGroupIndex = -1);
void showMonthlySummary(const Group& group);
void settleTransaction(Group& group);
void updateBalances(Group& group);
void displayCategories();
int findMemberInGroup(const Group& group, const string& memberId);
bool isValidDate(const string& date);
void clearScreen();
void pauseConsole();
void printHeader();


