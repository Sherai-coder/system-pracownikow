#include <iostream>
#include "pracownik.h"

Pracownik::Pracownik(int identificationNumber,const std::string& name,TypPracownika typ, double s, int h): id(identificationNumber), name(name), p(typ), salary(s), hours(h)
{
    if(hours<1)
    {
        throw std::invalid_argument("Hours must be greater than 0.");
    }
}
int Pracownik::getId() const
{
    return id;
}
std::string Pracownik::getName() const
{
    return name;
}
TypPracownika Pracownik::getType () const
{
    return p;
}
void Pracownik::setType(TypPracownika typ)
{
    p = typ;
}
int Pracownik::getHours() const
{
    return hours;
}
bool Pracownik::setHours(int h)
{
    if(h>=1)
    {
        hours=h;
        return true;
    }
    return false;

}
void Pracownik::setName(const std::string& newName)
{
    name=newName;
}
double Pracownik::getSalary() const
{
    return salary;
}
void Pracownik::setSalary(double s)
{
    salary=s;
}
double Pracownik::getEarningsPerHour() const
{
    return salary/hours;
}
void Pracownik::showWorkerDetails() const
{
    std::string typ=typNaString(getType());
    std::cout<<"Id:" <<id<<std::endl;
    std::cout<<"Name: "<<name<<std::endl;
    std::cout<<"Typ Pracownika: "<<typ<<std::endl;
    std::cout<<"Wynagrodzenie: "<<salary<<std::endl;
    std::cout<<"Ilosc godzin: "<<hours<<std::endl;
    std::cout<<"Earnings perhour: "<<getEarningsPerHour()<<std::endl;
}
////////////Programista/////////////
Programista::Programista(int id,const std::string& name, TypPracownika t, double s, int h) : Pracownik(id,name,t,s,h)
{

}
void Programista::wykonajPrace() const
{
    std::cout<<"Pisze kod."<<std::endl;
}



//////////////Manager//////////////////
Manager::Manager(int id,const std::string& name, TypPracownika t, double s, int h) : Pracownik(id,name,t,s,h)
{

}
void Manager::wykonajPrace() const
    {
        std::cout<<"Porzadkuje papiery."<<std::endl;
    }

//////////////Ksiegowy///////////////

Ksiegowy::Ksiegowy(int id,const std::string& name, TypPracownika t, double s, int h) : Pracownik(id,name,t,s,h)
{

}

void Ksiegowy::wykonajPrace() const
{
    std::cout<<"Zliczam rachunki."<<std::endl;
}
