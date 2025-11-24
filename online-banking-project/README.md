# Online Banking System (C)

**Student:** Kaseke Morven

**Student Number:** 2025-01-59-91

## Project Overview

This is a console-based Online Banking System implemented in C. It covers the required features for the Rockview University Final Promotion Individual Project.

### Implemented Features
- User registration (create account with full name, account number, password, initial deposit)
- Login system (account number + password)
- Deposit funds
- Withdraw funds (checks for sufficient balance)
- Online transfer between accounts (validates both accounts and checks balance)
- Change password (securely, does not display password)
- Display account details (name, account number, balance)
- File handling: all accounts are stored in a binary file `accounts.dat` for persistence
- Input validation and basic error handling
- Menu implemented with switch-case and functions

## How to compile and run

1. Save the C source file as `online_banking_2025-01-59-91.c`.
2. Open a terminal and compile with `gcc`:

   ```bash
   gcc online_banking_2025-01-59-91.c -o online_banking
