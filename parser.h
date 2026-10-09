#pragma once
#include <iostream>
#include "typPracownika.h"



enum class ParseStatus
{
    Success,
    InvalidArgument,
    OutOfRange,
    InvalidFormat
};

struct ParseResultInt
{
    ParseStatus status;
    int value;
};
struct ParseResultDouble
{
    ParseStatus status;
    double value;
};

struct ParseWorkerResult
{
    ParseStatus status;
    int id;
    std::string name;
    TypPracownika type;
    double salary;
    int hours;
};

ParseResultInt tryParseId(const std::string& idStr);
ParseResultDouble tryParseSalary(const std::string& salaryStr);
ParseResultInt tryParseHours(const std::string& hoursStr);
ParseWorkerResult parseWorkerRecord(const std::string& line);
std::string statusNaString(ParseStatus status);

bool isValidId(int id);
bool isValidName(const std::string& name);
bool isValidSalary(double salar);
bool isValidHours(int hours) ;
