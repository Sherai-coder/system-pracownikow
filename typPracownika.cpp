#include <iostream>
#include "typPracownika.h"
std::string typNaString(TypPracownika typ)
{
    switch(typ)
    {
    case TypPracownika::Ksiegowy:
    {
        return "Ksiegowy";
        break;
    }
    case TypPracownika::Programista:
    {
        return "Programista";
        break;
    }
    case TypPracownika::Manager:
    {
        return "Manager";
        break;
    }
    }
    return "nieznany";
}

TypPracownika stringNaTyp(const std::string& type)
{
    if(type=="Programista")
        {
            return TypPracownika::Programista;
        }
    else if(type=="Ksiegowy")
        {
            return TypPracownika::Ksiegowy;
        }
    else if(type=="Manager")
        {
            return TypPracownika::Manager;
        }
    else return TypPracownika::Nieznany;
}
