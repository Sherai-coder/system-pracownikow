#include <iostream>
#include "parser.h"
#include <sstream>

ParseResultDouble tryParseSalary(const std::string& salaryStr)
{
    std::size_t pos = 0;
    try
    {
        double salary=stod(salaryStr,&pos);
        if(pos!=salaryStr.length())
        {
            return {ParseStatus::InvalidFormat,0.0};
        }
        return {ParseStatus::Success,salary};
    }
    catch(const std::invalid_argument&)
    {
        return {ParseStatus::InvalidArgument,0.0};
    }
    catch(const std::out_of_range&)
    {
        return {ParseStatus::OutOfRange,0.0};
    }
}


ParseWorkerResult parseWorkerRecord(const std::string& line)
{
    ParseWorkerResult result;
    std::stringstream ss(line);
    std::string idStr,name,typPracownikaStr,hoursStr,salaryStr;
    ParseStatus status = ParseStatus::Success;
    getline(ss,idStr,'|');
    getline(ss,name,'|');
    getline(ss,typPracownikaStr,'|');
    getline(ss,salaryStr,'|');
    getline(ss,hoursStr,'|');
    ParseResultInt idResult = tryParseId(idStr);
    if(idResult.status!=ParseStatus::Success)
    {
        status= idResult.status;
    }
    bool isNameCorrect = isValidName(name);
    if(!isNameCorrect)
    {
        if(status==ParseStatus::Success)
        {
            status=ParseStatus::InvalidFormat;
        }
    }
    TypPracownika type = stringNaTyp(typPracownikaStr);
    if(type==TypPracownika::Nieznany && status==ParseStatus::Success)
    {
        status = ParseStatus::InvalidArgument;
    }
    ParseResultDouble salaryResult=tryParseSalary(salaryStr);
    if(salaryResult.status!=ParseStatus::Success && status==ParseStatus::Success)
    {
        status = salaryResult.status;
    }
    ParseResultInt hoursResult=tryParseHours(hoursStr);
    if(hoursResult.status!=ParseStatus::Success && status==ParseStatus::Success)
    {
        status = hoursResult.status;
    }
    result.status = status;
    result.id = idResult.value;
    result.name = name;
    result.type= type;
    result.salary = salaryResult.value;
    result.hours = hoursResult.value;
    return result;
}

ParseResultInt tryParseHours(const std::string& hoursStr)
{
    std::size_t pos = 0;
    try
    {
        int hours = stoi(hoursStr,&pos);
        if(pos!=hoursStr.length())
        {
            return {ParseStatus::InvalidFormat,0};
        }
        if(!isValidHours(hours))
        {
            return {ParseStatus::InvalidArgument,0};
        }
        else return {ParseStatus::Success,hours};
    }
    catch(std::invalid_argument&)
    {
        return {ParseStatus::InvalidArgument,0};
    }
    catch(std::out_of_range&)
    {
        return {ParseStatus::OutOfRange,0};
    }
}


ParseResultInt tryParseId(const std::string& idStr)
{
    std::size_t pos = 0;
    try
    {
        int id = stoi(idStr,&pos);
        if(pos!=idStr.length())
        {
            return {ParseStatus::InvalidFormat,0};
        }
        if(isValidId(id))
        {
            return {ParseStatus::Success,id};
        }
        else return {ParseStatus::InvalidArgument,0};
    }
    catch(const std::invalid_argument&)
    {
        return {ParseStatus::InvalidArgument,0};
    }
    catch(const std::out_of_range&)
    {
        return {ParseStatus::OutOfRange,0};
    }
}
std::string statusNaString(ParseStatus status)
{
    if(status==ParseStatus::Success)
    {
        return "Success";
    }
    if(status==ParseStatus::InvalidArgument)
    {
        return "Invalid Argument";
    }
    if(status==ParseStatus::InvalidFormat)
    {
        return "Invalid Format";
    }
    if(status==ParseStatus::OutOfRange)
    {
        return "Out of range";
    }
    return "Unknown";
}

bool isValidName(const std::string& name)
{
    return !name.empty();
}

bool isValidId(int id)
{
    if(id<0 || id>10000)
    {
        return false;
    }
    return true;
}

bool isValidSalary(double salary)
{
    if(salary<1000 || salary>100000)
    {
        return false;
    }
    return true;
}
bool isValidHours(int hours)
{
    if(hours<1 || hours>200)
    {
        return false;
    }
    return true;
}
