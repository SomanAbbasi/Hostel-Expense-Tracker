#define byte win_byte_override
#include <windows.h>
#undef byte
#include "../include/file_management.h"
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include "../include/group_operation.h"
#include "../include/termcolor.hpp"
using namespace std;

bool checkFolderExists(const string& folderPath){
    //demo file for checking folder
    string file = folderPath + "/check.txt";
    ofstream out(file);
    if (out){
        out.close();
        remove(file.c_str());
        return true;
    }
    return false;
}

void createReportsDirectory(){
    // Make sure "reports" exists
    if (!checkFolderExists("reports")){
        system("mkdir reports");
    }

    // Make sure "reports\\Groups" exists (Windows path)
    if (!checkFolderExists("reports\\Groups")){
        system("mkdir reports\\Groups");
    } 
}

void createGroupDirectory(const string& groupId){
    createReportsDirectory();

    // Windows compatible path
    string groupNo = "mkdir reports\\Groups\\G" + groupId;
    system(groupNo.c_str());
}

string getGroupDirectoryPath(const string& groupId){
    return "reports\\Groups\\G" + groupId;
}

string getGroupDataFilePath(const string& groupId){
    return "reports\\Groups\\G" + groupId + "\\data.txt";
}

string getGroupReportFilePath(const string& groupId){
    return "reports\\Groups\\G" + groupId + "\\report.txt";
}

void saveGroupToFile(Group& group) {
    createReportsDirectory();
    createGroupDirectory(group.groupId);

    string path = getGroupDataFilePath(group.groupId);
    ofstream out(path);

    if (!out) {
        std::cout <<termcolor::red<< "File opening error\n";
        return;
    } else {
        std::cout <<termcolor::green<< "File opened successfully\n";
    }

    // Save group basic details
    out << group.groupId << endl;
    out << group.groupName << endl;
    out << group.memberCount << endl;

    // Save members
    for (int i = 0; i < group.memberCount; i++) {
        out << group.members[i].name << endl;
        out << group.members[i].id << endl;
        out << group.members[i].totalPaid << endl;
        out << group.members[i].totalSpent << endl;
    }

    // Save expenses
    out << group.expenseCount << endl;

    for (int i = 0; i < group.expenseCount; i++) {
        out << group.expenses[i].category << endl;
        out << group.expenses[i].amount << endl;
        out << group.expenses[i].paidBy << endl;
        out << group.expenses[i].date << endl;
        out << group.expenses[i].description << endl;
        out << group.expenses[i].isSettled << endl;
    }
    // Save transactions
    out << group.transactionCount << endl;

    for (int i = 0; i < group.transactionCount; i++) {
        out << group.transactions[i].fromMember << endl;
        out << group.transactions[i].toMember << endl;
        out << group.transactions[i].amount << endl;
        out << group.transactions[i].date << endl;
        out << group.transactions[i].description << endl;
        out << group.transactions[i].isSettled << endl;
    }

    out.close();

    std::cout <<termcolor::green<< "Data has been saved successfully\n";
}

void loadGroupFromFile(Group& group) {
    string path = getGroupDataFilePath(group.groupId);
    ifstream in(path);

    if (!in) {
        std::cout<<termcolor::red << "File opening error\n";
        return;
    } else {
        std::cout <<termcolor::green<< "File opened successfully\n";
    }

    // Load group basic info
    getline(in, group.groupId);
    getline(in, group.groupName);

    in >> group.memberCount;
    in.ignore();

    // Load members
    for (int i = 0; i < group.memberCount; i++) {
        getline(in, group.members[i].name);
        getline(in, group.members[i].id);
        in >> group.members[i].totalPaid;
        in >> group.members[i].totalSpent;
        in.ignore();
    }

    // Load expenses
    in >> group.expenseCount;
    in.ignore();

    for (int i = 0; i < group.expenseCount; i++) {
        getline(in, group.expenses[i].category);
        in >> group.expenses[i].amount;
        in >> group.expenses[i].paidBy;
        in.ignore();
        getline(in, group.expenses[i].date);
        getline(in, group.expenses[i].description);
        in >> group.expenses[i].isSettled;
        in.ignore();
    }

    // Load transactions
    in >> group.transactionCount;
    in.ignore();

    for (int i = 0; i < group.transactionCount; i++) {
        in >> group.transactions[i].fromMember;
        in >> group.transactions[i].toMember;
        in >> group.transactions[i].amount;
        in.ignore();
        getline(in, group.transactions[i].date);
        getline(in, group.transactions[i].description);
        in >> group.transactions[i].isSettled;
        in.ignore();
    }

    in.close();

    std::cout <<termcolor::green<< "Data has been loaded successfully\n";
}


void createGroupReport(Group& group){
    createReportsDirectory();
    createGroupDirectory(group.groupId);

    string path = getGroupReportFilePath(group.groupId);
    ofstream out(path);

    if (!out){
        std::cout<<termcolor::red <<"File opening error\n";
        return;
    } else {
        std::cout<<termcolor::green <<"File opened successfully\n";
    }

    out <<"---------Group Report-------------\n";
    out <<"Group Name: "<<group.groupName<<"\n";
    out <<"Group ID: "<<group.groupId<<"\n";
    out <<"Members:\n";

    for (int i=0; i<group.memberCount; i++){
        double balance = group.members[i].totalPaid - group.members[i].totalSpent;
        out << " -> "<<group.members[i].name<<" (ID: "<<group.members[i].id
            <<") | Paid: "<<fixed<<setprecision(2)<<group.members[i].totalPaid
            <<" | Spent: "<<group.members[i].totalSpent
            <<" | Balance: "<<balance<<endl;
    }

    out << "\nExpenses:\n";
    for (int i=0; i<group.expenseCount; i++){
        out << " -> " << group.expenses[i].category
            << " | Rs:" << fixed << setprecision(2) << group.expenses[i].amount
            << " | Paid by: " << group.members[group.expenses[i].paidBy].name
            << " | Date: " << group.expenses[i].date
            << " | " << group.expenses[i].description
            << " | " << (group.expenses[i].isSettled ? "Settled" : "Not Settled")
            << endl;
    }

    out << "\nTransactions:\n";
    for (int i=0; i<group.transactionCount; i++){
        out << " -> " << group.members[group.transactions[i].fromMember].name
            << " owes " << group.members[group.transactions[i].toMember].name
            << " Rs: " << fixed << setprecision(2) << group.transactions[i].amount
            << " | Date: " << group.transactions[i].date
            << " | " << group.transactions[i].description
            << " | " << (group.transactions[i].isSettled ? "Settled" : "Not Settled")
            << endl;
    }

    out.close();
    std::cout<<termcolor::green <<"Report has been created successfully\n";
}

void saveAllGroupsData(Group groups[], int groupCount){
    if (groupCount == 0){
        cout << "No groups found.\n";
        pauseConsole();
        return;
    }

    ofstream file("reports\\Groups\\Groups_list.txt");
    if (!file){
        std::cout<<termcolor::red <<"File opening error for Groups_list.txt\n";
        return;
    } else {
        std::cout<<termcolor::green<<"File opened successfully\n";
    }

    for (int i=0; i<groupCount; i++){
        saveGroupToFile(groups[i]);
        createGroupReport(groups[i]);
        file << groups[i].groupId << endl;
    }
    file.close();

    std::cout<<termcolor::green <<"All groups have been saved successfully\n";
}

void loadAllGroupsData(Group groups[], int& groupCount){
    groupCount = 0;

    ifstream file("reports\\Groups\\Groups_list.txt");
    if (!file){
        std::cout<<termcolor::red <<"File opening error for Groups_list.txt\n";
        return;
    } else {
        std::cout<<termcolor::green <<"File opened successfully\n";
    }

    string groupID;
    while (getline(file, groupID)){
        groups[groupCount].groupId = groupID;
        loadGroupFromFile(groups[groupCount]);
        groupCount++;
    }
    file.close();

    std::cout<<termcolor::green <<"All the data has been loaded successfully\n";
}
