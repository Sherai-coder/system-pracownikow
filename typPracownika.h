#pragma once
#include <iostream>

enum class TypPracownika
{
    Programista,
    Ksiegowy,
    Manager,
    Nieznany
};

std::string typNaString(TypPracownika typ);
TypPracownika stringNaTyp(const std::string& type);
