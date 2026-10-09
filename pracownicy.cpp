#include <iostream>
#include "pracownicy.h"
#include <fstream>
#include <sstream>
#include <utility>
#include "parser.h"

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
        return a->getSalary()<b->getSalary();
    });
}

const Pracownik* Pracownicy::findWorkerWithLongestHours() const
{
    return findBest([] (const auto& a, const auto& b)
    {
        return a->getHours()<b->getHours();
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
    const Pracownik* wanted=nullptr;
    for(const auto& worker : pracownicy)
    {
        if(worker->getType()==typ && maksSalary<worker->getSalary())
        {
            wanted = worker.get();
            maksSalary = worker->getSalary();
        }
    }
    return wanted;
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
    return changeDetail(worker,[&salary](Pracownik* worker)
    {
        worker->setSalary(salary);
    });
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
    return changeWorkers(([&type] (const auto& worker)
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
    auto it = max_element(pracownicy.begin(), pracownicy.end(), [] (const auto& a, const auto& b)
    {
        return a->getEarningsPerHour()<b->getEarningsPerHour();
    });
    return (*it)->getEarningsPerHour();
}
double Pracownicy::calculateAverageSalary() const
{
    if(pracownicy.empty())
    {
        return 0.0;
    }
    return accumulateWholeSalary()/pracownicy.size();
}
double Pracownicy::accumulateWholeSalary() const
{
    if(pracownicy.empty())
    {
        return 0.0;
    }
    return accumulate(pracownicy.begin(), pracownicy.end(), 0.0, [] (double amount, const auto& worker)
    {
        return amount+worker->getSalary();
    });
}


//////////////////////////////////////////////////


bool Pracownicy::saveToFile()
{
    std::ofstream plik;
    plik.open("dane.txt");
    if(!plik)
    {
        return false;
    }
    plik<<saveHighestUsedId()<<std::endl;
    for (const auto& worker : pracownicy)
    {
        plik<<worker->getId()<<"|"<<
            worker->getName()<<"|"<<
            typNaString(worker->getType())<<"|"<<
            worker->getSalary()<<"|"<<
            worker->getHours()<<"|"<<std::endl;
    }
    if(plik.bad())
    {
        return false;
    }
    return true;
}



int Pracownicy::saveHighestUsedId()
{
    if(pracownicy.empty())
    {
        return highestUsedIdFromFile;
    }
    auto it = max_element(pracownicy.begin(), pracownicy.end(), [] (const auto& a, const auto& b)
    {
        return a->getId()<b->getId();
    });
    if(highestUsedIdFromFile < (*it)->getId())
    {
        return (*it)->getId();
    }
    else return highestUsedIdFromFile;

}

bool Pracownicy::loadFromFile()
{
    std::ifstream plik;
    pracownicy.clear();
    invalidRecords.clear();
    plik.open("dane.txt");
    if(!plik)
    {
        return false;
    }
    std::string line;
    std::string highestUsedIdStr;
    getline(plik,highestUsedIdStr);
    ParseResultInt outcome = tryParseId(highestUsedIdStr);
    if(outcome.status == ParseStatus::Success)
    {
        highestUsedIdFromFile = outcome.value;
        nextId = outcome.value + 1;
    }
    while(getline(plik,line))
    {
        invalidWorkerRecord record;
        ParseWorkerResult result = parseWorkerRecord(line);
        if(result.status!=ParseStatus::Success)
        {
            record.setData(line);
            record.setReason(statusNaString(result.status));
            invalidRecords.push_back(record);
        }
        else
        {
            auto it = find_if(pracownicy.begin(), pracownicy.end(), [&result] (const auto& a)
            {
                return result.id==a->getId();
            });
            if(it!=pracownicy.end())
            {
                record.setData(line);
                record.setReason("Duplicate ID");
                invalidRecords.push_back(record);
            }
            else
            {
                auto worker = createWorker(result.id,result.name,result.type,result.salary,result.hours);
                pracownicy.push_back(std::move(worker));
            }

        }
    }
    if(plik.bad())
    {
        return false;
    }
    return true;
}
