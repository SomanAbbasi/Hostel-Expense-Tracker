# Hostellite Expense Tracker

A C++ application to manage shared expenses among hostel roommates with automatic tracking and calculations.

##  Project Structure

```
HostelExpenseTracker/
├── include/
│   ├── constants.h
│   ├── structures.h
│   ├── file_management.h
│   ├── group_operations.h
├── source/
│   ├── main.cpp
│   ├── file_management.cpp
│   ├── group_operations.cpp
├── build.bat
└── reports/
    └── Groups/
        ├── data.txt
        └── report.txt
```

##  Features

- **Group Management**: Create and manage expense sharing groups
- **Member Tracking**: Add members with individual balance tracking
- **Expense Recording**: Log shared expenses with 11 categories
- **Auto Calculations**: Automatic settlement calculations
- **Borrow/Lend Tracking**: Record personal loans between members
- ** Save/Load**: Data  saved and loaded by user
- **Financial Reports**: Generate detailed expense reports

##  How to Run

**Method 1 - Build Script:**
```bash
.\build.bat
```

**Method 2 - Manual Compile:**
```bash
g++ source/main.cpp source/group_operations.cpp source/file_management.cpp -o main
```

##  System Limits

- Max Groups: 50
- Max Members per Group: 20
- Max Expenses per Group: 100
- Max Transactions per Group: 200

##  Purpose

Automates expense tracking and settlement calculations for hostel students and roommates, eliminating manual calculations and disputes.


**Team Members:** [Ahmad Fayaz](https://github.com/ahmad-fayyaz626) • [Ali Hamza Bhatti](https://github.com/Alihamzabhatti560)
