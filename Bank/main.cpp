#include "Home.h"

/*

COMPLETE - Dynamic way to creating accounts and logging into them.
COMPLETE - not allowing the same username
DISCARDED (apparently iterators are outdated so my solution is fine + when i learn data structures i'll cover that then) - 
    saying "user not found" when failed username entry, also using iterators instead of a dodgy for loop
COMPLETE - money transfers between accounts
COMPLETE - understand why the rounding balance works the way it does
DISCARDED (unnecessary, if having trouble remember your username, just restart honestly) 
    - when in main menu (e.g. at username entery) option to go back to main menu

*/



int main() 
{
    std::cout<<"Welcome to RevRift Banking\n";

    Home home;
    home.main_menu();

    system("pause");

    return 0;
}
