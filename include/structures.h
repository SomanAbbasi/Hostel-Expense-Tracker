
#pragma once

#include "constants.h"
#include <string>
using namespace std;

struct Member
{
    string name;
    string id;
    double totalPaid;
    double totalSpent;
};

struct Expense
{
    string category;
    double amount;
    int paidBy;
    string date;
    string description;
    bool isSettled;
};

struct Transaction
{
    int fromMember;
    int toMember;
    double amount;
    string date;
    string description;
    bool isSettled;
};

struct Group
{
    string groupId;
    string groupName;
    Member members[MAX_MEMBERS_PER_GROUP];
    // Member *members;
    int memberCount;
    int memberCapcaity;
    Expense expenses[MAX_EXPENSES_PER_GROUP];
    // Expense *expenses;
    int expenseCount;
    int expenseCapacity;
    //   Transaction *transactions;
    Transaction transactions[MAX_TRANSACTIONS_PER_GROUP];
    int transactionCount;
    int transactionCapacity;
};
