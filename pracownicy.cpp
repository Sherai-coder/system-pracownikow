#include <iostream>
#include "pracownicy.h"
#include <fstream>
#include <sstream>
#include <utility>

std::unique_ptr<Pracownik> Pracownicy::createWorker(int id,const std::string& name, TypPracownika p, double s, int h)
{
    switch(p)
    {
    case TypPracownika::Ksiegowy:
    {
        return std::make_unique<Ksiegowy>(id,name,p,s,h);
    }
    case TypPracownika::Manager:
    {
        return std::make_unique<Manager>(id,name,p,s,h);
    }
    case TypPracownika::Programista:
    {
        return std::make_unique<Programista>(id,name,p,s,h);
    }
    default:
    {
        return nullptr;
    }
    }
}

void Pracownicy::addWorker(const std::string& name, TypPracownika p, double s, int h)
{
    pracownicy.push_back(createWorker(nextId,name,p,s,h));
    nextId++;
}

bool Pracownicy::setNextId(int id)
{
    for(const auto& worker : pracownicy)
    {
        if(worker->getId()==id)
        {
            return false;
        }
    }
    nextId=id;
    return true;
}
int Pracownicy::getNextId() const
{
    return nextId;
}

void Pracownicy::showAllWorkersWork() const
{
    for (const auto& worker : pracownicy)
    {
        worker->wykonajPrace();
    }
}



///////////////REMOVE WORKER/////////////
bool Pracownicy::removeWorker(Pracownik* worker)
{
    auto it = find_if(pracownicy.begin(), pracownicy.end(),[&worker](const auto& a)
    {
        return a.get()==worker;
    });
    if(it!=pracownicy.end())
    {
        pracownicy.erase(it);
        return true;
    }
    return false;
}




void Pracownicy::showAllWorkersDetails() const
{
    for (const auto& worker : pracownicy)
    {
        worker->showWorkerDetails();
    }
}



////////////////////////// Count Workers/////////////////////////////////
int Pracownicy::countWorkersByName(const std::string& name) const
{
    return countWorkers([&name] (const auto& a)
    {
        return a->getName()==name;
    });
}
int Pracownicy::countWorkersByType(TypPracownika p) const
{
    return countWorkers([&p](const auto&a)
    {
        return a->getType()==p;
    });
}
int Pracownicy::countWorkersBySalary(double salary)const
{
    return countWorkers([&salary](const auto&a)
    {
        return a->getSalary()==salary;
    });
}
int Pracownicy::countWorkersByHours(int hours) const
{
    return countWorkers([&hours](const auto&a)
    {
        return a->getHours()==hours;
    });
}



//////////////////////////////////////////////////////////////////////////



//////////// sort workers////////////////
std::vector<const Pracownik*> Pracownicy::sortWorkersByName() const
{
    return sortedBy([] (const auto&a, const auto& b)
    {
        return a->getName()<b->getName();
    });
}

std::vector<const Pracownik*> Pracownicy::sortWorkersBySalary() const
{
    return sortedBy([] (const auto& a, const auto& b)
    {
        return a->getSalary()<b->getSalary();
    });
}

std::vector<const Pracownik*> Pracownicy::sortWorkersByHours() const
{
    return sortedBy([](const auto&a, const auto&b)
    {
        return a->getHours()<b->getHours();
    });
}
std::vector<const Pracownik*> Pracownicy::sortWorkersById() const
{
    return sortedBy([] (const auto& a, const auto& b)
    {
        return a->getId()<b->getId();
    });
}
std::vector<const Pracownik*> Pracownicy::sortWorkersByType() const
{
    return sortedBy([] (const auto& a, const auto& b)
    {
        return a->getType()<b->getType();
    });
}

///////////////////////////////////////////



///////////////////FindBest//////////////////////

const Pracownik* Pracownicy::findBestPaidWorker() const
{
    return findBest([] (const auto& a, const auto&b)
    {
        return a->getSalary()>b->getSalary();
    });
}

const Pracownik* Pracownicy::findWorkerWithLongestHours() const
{
    return findBest([] (const auto& a, const auto& b)
    {
        return a->getHours()>b->getHours();
    });
}

/////////////////////////////////////////////



/////////////////////FindWorker////////////////////////////

Pracownik* Pracownicy::findWorkerByName(const std::string& name)
{
    return findWorkerBy([&name](const auto& worker)
    {
        return worker->getName()==name;
    });
}

Pracownik* Pracownicy::findWorkerById(int id)
{
    return findWorkerBy([&id](const auto& worker)
    {
        return worker->getId()==id;
    });
}

Pracownik* Pracownicy::findWorkerBySalary(double salary)
{
    return findWorkerBy([&salary](const auto& worker)
    {
        return worker->getSalary()==salary;
    });
}

Pracownik* Pracownicy::findWorkerByHours(int hours)
{
    return findWorkerBy([&hours](const auto& worker)
    {
        return worker->getHours()==hours;
    });
}

Pracownik* Pracownicy::findWorkerByType(TypPracownika p)
{
    return findWorkerBy([&p](const auto& worker)
    {
        return worker->getType()==p;
    });
}

////////////////////////////////////////////






const Pracownik* Pracownicy::findBestPaidWorkerByType(TypPracownika typ) const
{
    double maksSalary=0;
    const Pracownik* szukany=nullptr;
    for(const auto& i : pracownicy)
    {
        if(i->getType()==typ && maksSalary<i->getSalary())
        {
            szukany = i.get();
            maksSalary = i->getSalary();
        }
    }
    return szukany;
}

///////////////// changewORKER DETAILS/ //////////////////

bool Pracownicy::changeWorkerName(Pracownik* worker,const std::string& name)
{
    return changeDetail(worker, [&name] (Pracownik* worker)
    {
        worker->setName(name);
    });
}
bool Pracownicy::changeWorkerHours(Pracownik* worker, int hours)
{
    return changeDetail(worker,[&hours] (Pracownik* worker)
    {
        worker->setHours(hours);
    });
}
bool Pracownicy::changeWorkerSalary(Pracownik* worker,double salary)
{
    if(worker!=nullptr)
    {
        worker->setSalary(salary);
        return true;
    }
    return false;
}

bool Pracownicy::changeWorkerId(Pracownik* worker,int id)
{
    if(worker==nullptr)
    {
        return false;
    }
    auto it  = find_if(pracownicy.begin(), pracownicy.end(),[&id,&worker] (const auto& a)
    {
        return a->getId()==id;
    });
    if(it!=pracownicy.end())
    {
        return false;
    }
    worker->setId(id);
    return true;
}
bool Pracownicy::changeWorkerTypeCheck(Pracownik* worker,TypPracownika typ)
{
    return changeDetail(worker,[&typ](Pracownik* worker)
    {
        return worker->setType(typ);
    });
}

//////////////////////////// Show INVALID RECORDS//////////////////////////

void Pracownicy::showInvalidRecords()
{
    for(const auto& worker : invalidRecords)
    {
        std::cout<<worker.data<<" | "<<worker.reason<<std::endl;
    }
}



//////////////////// Above what ///////////////////////////
std::vector<const Pracownik*> Pracownicy::getWorkersAboveSalary(double salary) const
{
    return getWorkers([&salary](const auto& worker)
    {
        return worker->getSalary()>salary;
    });
}

std::vector<const Pracownik*> Pracownicy::getWorkersAboveHours(int hours) const
{
    return getWorkers([&hours] (const auto& worker)
    {
        return worker->getHours()>hours;
    });
}
std::vector<const Pracownik*> Pracownicy::getWorkersWithSpecificType(TypPracownika typ) const
{
    return getWorkers([&typ] (const auto& worker)
    {
        return worker->getType()==typ;
    });
}

std::vector<const Pracownik*> Pracownicy::getWorkersWithName(const std::string& name) const
{
    return getWorkers([&name](const auto& worker)
    {
        return worker->getName()==name;
    });
}
std::vector<const Pracownik*> Pracownicy::getWorkersWithSalaryBetween(double low, double high) const
{
    return getWorkers([&low,&high](const auto& worker)
    {
        return (worker->getSalary()>low && worker->getSalary()<high);
    });
}


////////////////////////////////////////////////////////////////////////

/////////////////// Change all workers ///////////////////
void Pracownicy::changeAllWorkersSalary(double salary)
{
    changeAllWorkers([&salary](const auto& worker)
    {
        worker->setSalary(worker->getSalary()+salary);
    });
}
void Pracownicy::changeAllWorkersHours(int hours)
{
    changeAllWorkers([&hours](const auto& worker)
    {
        worker->setHours(hours);
    });
}

/////////////////////////////////////// Sprwadzam////////////////////

bool Pracownicy::changeSpecificWorkersSalary(TypPracownika type,double salary)
{
    changeWorkers(([&type] (const auto& worker)
    {
        return worker->getType()==type;
    }),
    ([&salary](const auto& workerr)
    {
        return workerr->setSalary(workerr->getSalary()+salary);
    }));
}

//////////////////////////////// Dobule ////////////////////////
double Pracownicy::getHighestEarningsPerHour() const
{
    if(pracownicy.empty())
    {
        return 0.0;
    }
    double najwieksza = 0.0;
    for (const auto& worker : pracownicy)
    {
        if(worker->getEarningsPerHour()>najwieksza)
        {
            najwieksza=worker->getEarningsPerHour();
        }
    }
    return najwieksza;
}
double Pracownicy::calculateAverageSalary() const
{
    if(pracownicy.empty())
    {
        return 0.0;
    }
    double wholeAmount= accumulateWholeSalary();
    return wholeAmount/pracownicy.size();
}
double Pracownicy::accumulateWholeSalary() const
{
    if(pracownicy.empty())
    {
        return 0.0;
    }
    double amount=accumulate(pracownicy.begin(), pracownicy.end(), 0.0, [] (double amount, const auto& worker)
    {
        return amount+worker->getSalary();
    });
    return amount;
}


//////////////////////////////////////////////////


bool Pracownicy::saveToFile()
{
    std::ofstream plik;
    plik.open("dane.txt");
    bool done = false;
    plik<<nextId<<std::endl;
    done = true;
    for (const auto& worker : pracownicy)
    {
        plik<<worker->getId()<<"|"<<
            worker->getName()<<"|"<<
            typNaString(worker->getType())<<"|"<<
            worker->getSalary()<<"|"<<
            worker->getHours()<<"|"<<std::endl;
    }
    for (const auto& invalidDate : invalidRecords)
    {
        plik<<invalidDate.data<<std::endl;
    }
    return done;
}

bool Pracownicy::isValidName(const std::string& name) const
{
    return !name.empty();
}

ParseResultInt Pracownicy::tryParseId(const std::string& idStr)
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
bool Pracownicy::isValidId(int id) const
{
    if(id<0 || id>10000)
    {
        return false;
    }
    return true;
}
ParseStatus Pracownicy::isValidTypPracownika(TypPracownika type) const
{
    if(type==TypPracownika::Nieznany)
    {
        return ParseStatus::InvalidFormat;
    }
    return ParseStatus::Success;
}

ParseResultDouble Pracownicy::tryParseSalary(const std::string& salaryStr)
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

bool Pracownicy::isVectorEmpty()
{
    if(invalidRecords.empty())
    {
        std::cout<<"Pusty."<<std::endl;
        return true;
    }
    else
    {
        std::cout<<"Sa dane."<<std::endl;
        return false;
    }
}

bool Pracownicy::isValidSalary(double salary) const
{
    if(salary<1000 || salary>100000)
    {
        return false;
    }
    return true;
}

ParseWorkerResult Pracownicy::parseWorkerRecord(const std::string& line)
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


ParseResultInt Pracownicy::tryParseHours(const std::string& hoursStr)
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
bool Pracownicy::isValidHours(int hours) const
{
    if(hours<1 || hours>200)
    {
        return false;
    }
    return true;
}



bool Pracownicy::loadFromFile()
{
    std::ifstream plik;
    plik.open("dane.txt");
    bool done = false;
    std::string line;
    std::string nextIdStr;
    getline(plik,nextIdStr);
    setNextId(stoi(nextIdStr));
    while(getline(plik,line))
    {
        invalidWorkerRecord record;
        ParseWorkerResult result = parseWorkerRecord(line);
        std::cout<<statusNaString(result.status)<<std::endl;
        if(result.status!=ParseStatus::Success)
        {
            record.setDate(line);
            record.setReason(statusNaString(result.status));
            invalidRecords.push_back(record);
        }
        else
        {
            auto worker = createWorker(result.id,result.name,result.type,result.salary,result.hours);
            pracownicy.push_back(std::move(worker));
            done=true;
        }
    }
    return done;
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
