
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
    Member *members;
    int memberCount;
    int memberCapcaity;
    Expense *expenses;
    int expenseCount;
    int expenseCapacity;
    Transaction *transactions;
    int transactionCount;
    int transactionCapacity;
};


