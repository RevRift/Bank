#include "Home.h"

std::vector<BankAccount*> Home::accounts;

void Home::main_menu() 
{
    while(in_bank)
    {
        std::cout<<"\n1 - create account\n";
        std::cout<<"2 - Log in\n";
        std::cout<<"3 - exit\n";

        do {
        std::cout<<"Option(1-3): ";
        std::getline(std::cin, user_input);
        } while(!validate_option(user_input));

        switch(stoi(user_input))
        {
            case 1: create_account(); break;

            case 2: log_in(); break;

            case 3: in_bank = false; break;

            default: std::cout<<"\nNot a valid option\n"; break;
        }
    }
}

void Home::create_account()
{
    std::cout<<"\nCreate an account\n";

    do {
        std::cout<<"Enter name(only letters): ";
        std::getline(std::cin, new_name);
    } while(!validate_username(new_name));

    do {
        std::cout<<"Enter safe password (must have a number, a letter and 5 characters): ";
        std::getline(std::cin, new_password);
    } while(!validate_password(new_password));

    BankAccount* new_account = new BankAccount(new_name, new_password);
    accounts.push_back(new_account);
}

void Home::log_in()
{
    if(accounts.empty()) {
        std::cout<<"\nCreate an account first\n";
        return;
    }

    do {
        std::cout<<"\nEnter username: ";
        std::getline(std::cin, user_input);
    } while(find_account(user_input) == -1);
    slot = find_account(user_input);

    for(int i = 0; i <= 3; i++) 
    { 
        if(i == 3) {
            std::cout<<"\nToo many attempts\n";
            return;
        }

        std::cout<<"\nEnter password: ";
        std::getline(std::cin, user_input);

        if(accounts[slot]->get_password() == user_input) {
            std::cout<<"\nYou've successfully logged in\n";
            accounts[slot]->set_status(true);
            accounts[slot]->manage_money(); // should a pass the vector here??
            break;
        } else {
            std::cout<<"\nIncorrect password";
        }
    }
}

int Home::find_account(const std::string& input) 
{
    for(int i = 0; i < accounts.size(); i++) {
        if(accounts[i]->get_name() == input) {
            return i;
        }
    }
    return -1;
}

Home::~Home() 
{
    for(BankAccount* account : accounts) {
        delete account;
    }
}

bool Home::validate_option(const std::string& input)
{
    return (user_input.length() == 1 && isdigit(user_input[0]));
}

bool Home::validate_username(const std::string& username)
{
    for(char c : username) {
        if(!isalpha(c)){
            return false;
        }
    }
    
    for(BankAccount* account : accounts) {
        if(account->get_name() == username) {
            std::cout<<"\nUsername taken\n";
            return false;
        }
    }
    return true;
}

bool Home::validate_password(const std::string& password)
{
    if(password == "password") {
        return false;
    }
    if(password.length() < 5) {
        return false;
    }
    for(int i = 0; i < password.length()-1; i++) {
        if(isdigit(password[i]) && isalpha(password[i+1]) ||
           isalpha(password[i]) && isdigit(password[i+1])) {
            return true;
        }        
    }
    return false;
}

