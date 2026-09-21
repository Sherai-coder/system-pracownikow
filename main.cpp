#include <iostream>
#include "pracownik.h"
#include "pracownicy.h"
#include "menu.h"
using namespace std;
Pracownicy pracownicy;
Menu menu(pracownicy);
int main()
{
    menu.menuRun();
    return 0;
}
