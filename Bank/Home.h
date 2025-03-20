#pragma once
#include "BankAccount.h"

class Home
{
private:
    std::string user_input;
    bool in_bank = true;
    std::string new_name;
    std::string new_password;
    int slot;
    bool validate_username(const std::string& username);
    bool validate_password(const std::string& password);
    bool validate_option(const std::string& input);

public:
    static std::vector<BankAccount*> accounts;
    void main_menu();
    void create_account();
    void log_in();
    int find_account(const std::string& input);
    ~Home();
};