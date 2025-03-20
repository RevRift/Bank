#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cmath>

class BankAccount
{
private:
    float balance = 100;
    std::string name;
    std::string password;
    int slot_number;
    float interest_rate = 1.2;
    bool is_logged_in = false;
    std::string user_input;
    int chosen_user;
    int amount_to_transfer;
    bool validate_number(const std::string& input);


protected:
    std::vector<std::string> transactions;

public:
    int get_balance();
    std::string get_name() const;
    std::string get_password() const;
    void set_status(bool status);
    BankAccount(const std::string& n, const std::string& p);
    void deposit(const int& cash);
    void withdraw(const int& cash);
    void transfer();
    void receive_transfer(const int& cash);
    void display_transactions();
    void add_interest();
    void manage_money();
};