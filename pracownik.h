#pragma once
#include <iostream>
#include "typPracownika.h"
#include <stdexcept>

class Pracownik
{
protected:
    int id;
    std::string name;
    TypPracownika p;
    double salary;
    int hours;
    double earningsPerHour();
public:
    Pracownik(int id,const std::string& name,TypPracownika typ, double s, int h);
    virtual void wykonajPrace() const = 0;
    int getId() const;
    void setId(int i);
    std::string getName() const;
    TypPracownika getType() const;
    void setType(TypPracownika typ);
    int getHours() const;
    bool setHours(int h);
    void setName(const std::string& newName);
    double getSalary() const;
    void setSalary(double s);
    void showWorkerDetails() const;
    double getEarningsPerHour() const;
};


class Programista :public Pracownik
{
public:
    Programista(int id,const std::string& name, TypPracownika t, double s, int h);
    void wykonajPrace() const override;
};

class Manager :public Pracownik
{
public:
    Manager(int id,const std::string& name, TypPracownika t, double s, int h);
    void wykonajPrace() const override;
};
class Ksiegowy :public Pracownik
{
public:
    Ksiegowy(int id,const std::string& name, TypPracownika t, double s, int h);
    void wykonajPrace() const override;
};

