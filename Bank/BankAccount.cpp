#include "Home.h"

int BankAccount::get_balance()  {
    balance = round( balance * 100.0 ) / 100.0; //2.d.p. but i return integer version cuz OCD don't wanna have decimals remaining if i wanan drain my bank account
    return balance;
}

std::string BankAccount::get_name() const {return name;}

std::string BankAccount::get_password() const {return password; }

void BankAccount::set_status(bool status) {is_logged_in = status; }

BankAccount::BankAccount(const std::string& n, const std::string& p) :
    name(n), password(p)
{
    std::thread th1(&BankAccount::add_interest, this);
    th1.detach();

    slot_number = Home::accounts.size();
}

void BankAccount::deposit(const int& cash)
{
    balance += cash;
    transactions.push_back("You deposited " + std::to_string(cash));
}

void BankAccount::withdraw(const int& cash)
{
    if(balance < cash) {
        std::cout<<"\nYou're withdrawing too much\n";
    } else {
        balance -= cash;
        transactions.push_back("You withdrew " + std::to_string(cash));
    }
}

void BankAccount::transfer()
{
    if(Home::accounts.size() <= 1) {
        std::cout<<"\nThere's no one to transfer to\n";
        return;
    }
    
    std::cout<<"\nWho do you want to transfer to?\n";

    for(int i = 0; i < Home::accounts.size(); i++) {
        if(i == slot_number) {
            std::cout<< "You" <<" - "<< name <<std::endl;
        } else {
            std::cout<< i+1 <<" - "<< Home::accounts[i]->get_name() <<std::endl;
        }
    }

    do {
        std::cout<<"Option(1-"<<Home::accounts.size()<<")? : ";
        std::getline(std::cin, user_input);
    } while((!validate_number(user_input)) || 
                stoi(user_input) < 1 || 
                stoi(user_input) > Home::accounts.size() || 
                stoi(user_input) - 1 == slot_number);

    chosen_user = stoi(user_input) - 1;
    
    do {
        std::cout<<"How much? ";
        std::getline(std::cin, user_input);
    } while((!validate_number(user_input)) && (stoi(user_input) <= balance));

    amount_to_transfer = stoi(user_input);

    balance -= amount_to_transfer;
    transactions.push_back("You transferred " + std::to_string(amount_to_transfer) + " to " + Home::accounts[chosen_user]->get_name());

    Home::accounts[chosen_user]->receive_transfer(amount_to_transfer);
    Home::accounts[chosen_user]->transactions.push_back(name + " transferred " + std::to_string(amount_to_transfer) + " to you");
    
}

void BankAccount::receive_transfer(const int& cash) {
    balance += cash;
}

void BankAccount::display_transactions()
{
    for(std::string transaction : transactions) {
        std::cout<<transaction<<std::endl;
    }
}

void BankAccount::add_interest()
{
    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(15));
        balance *= interest_rate;
    }
}

void BankAccount::manage_money()
{
    std::cout<<"1 - deposit cash"<<std::endl;
    std::cout<<"2 - withdraw cash"<<std::endl;
    std::cout<<"3 - check balance"<<std::endl;
    std::cout<<"4 - transfer"<<std::endl;
    std::cout<<"5 - display transactions"<<std::endl;
    std::cout<<"6 - log out"<<std::endl;

    while(is_logged_in) {
        do {
            std::cout<<"\nOption (1-6): ";
            std::getline(std::cin, user_input);
        } while(!(user_input.length() == 1 && isdigit(user_input[0])));

        switch(stoi(user_input))
        {
            case 1: // Deposit
                do {
                    std::cout<<"\nHow much?: ";
                    std::getline(std::cin, user_input);
                } while(!validate_number(user_input));
                deposit(stoi(user_input));
                break;

            case 2: // Withdraw
                do {
                    std::cout<<"\nHow much?: ";
                    std::getline(std::cin, user_input);
                } while(!validate_number(user_input));
                withdraw(stoi(user_input));
                break;

            case 3: // Check Balance
                std::cout<<name<<" has "<<this->get_balance()<<std::endl;
                break;
            
            case 4: // Transfer
                transfer();
                break;

            case 5: // Display Trnasactions
                display_transactions();
                break;

            case 6: // Log out
                is_logged_in = false;
                break;

            default:
                std::cout<<"\nNot a valid option\n";
                continue;
        }
    }   
}

bool BankAccount::validate_number(const std::string& input) {
    for(char c : input) {
        if(!isdigit(c)) {
            return false;
        }
    }
    return true;
}