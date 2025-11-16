#pragma once
#include "structures.h"
#include <string>

using namespace std;

// file management functions
bool checkFolderExists(const string& folderPath);
void createReportsDirectory();
void createGroupDirectory(const string& groupId);

// File paths
string getGroupDirectoryPath(const string& groupId);
string getGroupReportFilePath(const string& groupId);
string getGroupDataFilePath(const string& groupId);

// Save and load functions
void saveGroupToFile(Group& group);
void loadGroupFromFile(Group& group);
void createGroupReport(Group& group);
void saveAllGroupsData(Group groups[], int groupCount);
void loadAllGroupsData(Group groups[], int& groupCount);