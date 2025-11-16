#pragma once
#include "file_management.h"
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include "group_operation.h"
using namespace std;
bool checkFolderExists(const string& folderPath){
    
    //demo file for checking folder
    string file = folderPath + "/check.txt";
    ofstream out (file);
    if (out){
        out.close ();
        remove (file.c_str());
        return true;
    }
    return false;
}

void createReportsDirectory(){
    if (!checkFolderExists("reports")){
        system ("mkdir reports");
    }

    if (!checkFolderExists("reports/Groups")){
        system ("mkdir reports/Groups");
    } 
}

void createGroupDirectory(const string& groupId){
    createReportsDirectory();

    string groupNo = "mkdir reports/Groups/G" + groupId;
    system(groupNo.c_str());
}

string getGroupDirectoryPath(const string& groupId){
    return ("reports/Groups/G"+groupId);
}

string getGroupDataFilePath(const string& groupId){
    return ("reports/Groups/G"+groupId+"/data.bin");
}

string getGroupReportFilePath(const string& groupId){
    return ("reports/Groups/G"+groupId+"/report.txt");
}

void saveGroupToFile(Group& group) {
    createReportsDirectory();
    createGroupDirectory(group.groupId);
    string path = getGroupDataFilePath(group.groupId);
    ofstream out (path , ios::binary);
    if (!out){
        cout <<"File opening error\n";
        return;
    } else {
        cout <<"File opened sucessfully\n";
    }

    out.write ((char*)&group,sizeof(group));

    out.close ();
    cout <<"Data has been saved successfully\n";
}


void loadGroupFromFile(Group& group){
    string path = getGroupDataFilePath(group.groupId);
    ifstream in (path , ios::binary);

     if (!in){
        cout <<"File opening error\n";
        return;
    } else {
        cout <<"File opened sucessfully\n";
    }

    in.read ((char*)&group,sizeof(group));

    in.close ();

    cout <<"Data has been loaded sucessfully\n";

}

void createGroupReport(Group& group){
    createReportsDirectory();
    createGroupDirectory(group.groupId);

    string path = getGroupReportFilePath (group.groupId);

    ofstream out (path);

     if (!out){
        cout <<"File opening error\n";
        return;
    } else {
        cout <<"File opened sucessfully\n";
    }

    out <<"---------Group Report-------------\n";
    out <<"Group Name: "<<group.groupName<<"\n";
    out<<"Group ID: "<<group.groupId<<"\n";
    out<<"Members: "<<"\n";

    for (int i=0 ; i<group.memberCount ; i++){
        double balance = group.members[i].totalPaid - group.members[i].totalSpent;
        out << " -> "<<group.members[i].name << " (ID: " << group.members[i].id
         << " )" << " | Paid: " << fixed <<setprecision (2) << group.members[i].totalPaid << " | Spent: " << group.members[i].totalSpent << " | Balance: " << balance << endl; 
    }


    out << "\nExpenses:\n";
    for (int i=0 ; i<group.expenseCount ; i++){
        out << " -> " << group.expenses[i].category << " | Rs:" << 
        fixed << setprecision (2) << group.expenses[i].amount
        <<" | Paid by: " << group.members[group.expenses[i].paidBy].name
        << " | Date: " << group.expenses[i].date 
        << " | " << group.expenses[i].description 
        << " | " << (group.expenses[i].isSettled ? "Settled" : "Not Settled")
        <<endl;

        
    }


    out <<"\nTransactions: \n";

    for (int i=0 ; i<group.transactionCount ; i++){
        out << " -> " << group.members[group.transactions[i].fromMember].name
        <<" owes " << group.members[group.transactions[i].toMember].name
        <<" Rs: " << fixed << setprecision(2) << group.transactions[i].amount
        << " | Date: " << group.transactions[i].date 
        << " | " << group.transactions[i].description <<" | "
        << (group.transactions[i].isSettled ? "Settled" : "Not Setlled")
        <<endl;
    }


    out.close ();

    cout <<"Report has been created sucessfully\n";

}


void saveAllGroupsData(Group groups[], int groupCount){
     if (groupCount == 0)
    {
        cout << "No groups found.\n";
        pauseConsole();
        return;
    }

    ofstream file ("reports/Groups/Groups_list.txt");
    if (!file){
        cout <<"File opening error\n";
        return;
    }
    else {
        cout <<"File opened successfully\n";
    }

    for (int i=0 ; i<groupCount ; i++){
        saveGroupToFile (groups[i]);
        createGroupReport(groups[i]);
        file << groups[i].groupId << endl;
    }
    file.close ();

    cout <<"All groups has been saved successfully\n";
}

void loadAllGroupsData(Group groups[], int& groupCount){
    groupCount=0;

    ifstream file("reports/Groups/Groups_list.txt");

    if (!file){
        cout <<"File opening error\n";
        return;
    }
    else {
        cout <<"File opened successfully\n";
    }

    string groupID;

    while (getline(file,groupID)) {
        groups[groupCount].groupId = groupID;
        loadGroupFromFile(groups[groupCount]);
        groupCount++;
    }

    file.close ();

    cout <<"All the data has been loaded successfully\n";
    
}






















