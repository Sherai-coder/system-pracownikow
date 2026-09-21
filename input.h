#pragma once
#include <iostream>
#include "menu.h"
#include <conio.h>


int getInt(const std::string& message, const int& minRange, const int& maxRange);
void pause();
std::string getWord(const std::string& message);
double getDouble(const std::string& message,const double& minRange, const double& maxRange);
TypPracownika getWorkerType(const std::string& message);
