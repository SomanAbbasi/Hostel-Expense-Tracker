
#pragma once
#include "structures.h"

bool folderExists(const string& path);
void createReportsFolder();
void createGroupFolder(const string& groupId);
string getGroupFolderPath(const string& groupId);
string getGroupTextReportPath(const string& groupId);
string getGroupBinaryDataPath(const string& groupId);
void saveGroupBinaryData(Group& group);
void loadGroupBinaryData(Group& group);
void generateGroupTextReport(Group& group);
void saveGroupData(Group& group);
void loadGroupData(Group& group);
void saveAllData(Group* groups, int groupCount);
void loadAllData(Group*& groups, int& groupCount);


