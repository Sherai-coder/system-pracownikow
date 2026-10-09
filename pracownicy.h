#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include "pracownik.h"
#include "typPracownika.h"
#include <numeric>
#include <string>
#include "typPracownika.h"
#include <fstream>

struct invalidWorkerRecord
{
    std::string data;
    std::string reason;

    void setData(const std::string& information)
    {
        data = information;
    }
    void setReason(const std::string& information)
    {
        reason = information;
    }
};



class Pracownicy
{
    std::vector<std::unique_ptr<Pracownik>> pracownicy;
    std::vector<invalidWorkerRecord> invalidRecords;
    int nextId=1;
    int highestUsedId=0;
    int highestUsedIdFromFile=0;



public:
    int saveHighestUsedId();
    std::unique_ptr<Pracownik> createWorker(int id,const std::string& name, TypPracownika p, double s, int h);


    void showAllWorkersWork() const;
    void showAllWorkersDetails() const;
    void addWorker(const std::string& name, TypPracownika p, double s, int h);

    template <typename Findworker>
    Pracownik* findWorkerBy(Findworker findworker);
    Pracownik* findWorkerByName(const std::string& name);
    Pracownik* findWorkerById(int id);
    Pracownik* findWorkerBySalary(double salary);
    Pracownik* findWorkerByHours(int hours);
    Pracownik* findWorkerByType(TypPracownika p);


    bool removeWorker(Pracownik* worker);



    template<typename Howtosort>
    std::vector<const Pracownik*> sortedBy(Howtosort howtosort) const;
    std::vector<const Pracownik*> sortWorkersByName() const;
    std::vector<const Pracownik*> sortWorkersById() const;
    std::vector<const Pracownik*> sortWorkersBySalary() const;
    std::vector<const Pracownik*> sortWorkersByHours() const;
    std::vector<const Pracownik*> sortWorkersByType() const;

    template <typename Changewhat>
    bool changeDetail(Pracownik* worker, Changewhat changewhat);
    bool changeWorkerName(Pracownik* worker,const std::string& name);
    bool changeWorkerSalary(Pracownik* worker, double salary);
    bool changeWorkerHours(Pracownik* worker, int hours);
    bool changeWorkerTypeCheck(Pracownik* worker,TypPracownika typ);


    template <typename Howtocount>
    int countWorkers(Howtocount howtocount) const;
    int countWorkersByType(TypPracownika p) const;
    int countWorkersByName(const std::string& name) const;
    int countWorkersBySalary(double salary) const;
    int countWorkersByHours(int hours) const;


    template <typename Findwho>
    const Pracownik* findBest(Findwho findwho) const;
    const Pracownik* findBestPaidWorker() const;
    const Pracownik* findWorkerWithLongestHours() const;


    template <typename Predicate>
    std::vector<const Pracownik*> getWorkers(Predicate predicate) const;
    std::vector<const Pracownik*> getWorkersAboveSalary(double salary) const;
    std::vector<const Pracownik*> getWorkersAboveHours(int hours) const;
    std::vector<const Pracownik*> getWorkersWithSpecificType(TypPracownika typ) const;
    std::vector<const Pracownik*> getWorkersWithName(const std::string& name) const;
    std::vector<const Pracownik*> getWorkersWithSalaryBetween(double low, double high) const;

    template <typename Modification>
    void changeAllWorkers(Modification modification);
    void changeAllWorkersSalary(double salary);
    void changeAllWorkersHours(int hours);

    template <typename Condition, typename Modification>
    bool changeWorkers(Condition condition, Modification modification);
    bool changeSpecificWorkersSalary(TypPracownika p, double salary);

    double calculateAverageSalary() const;
    double accumulateWholeSalary() const;
    double getHighestEarningsPerHour() const;

    const Pracownik* findBestPaidWorkerByType(TypPracownika typ) const;

    void showInvalidRecords();

    bool saveToFile();
    bool loadFromFile();

};


template <typename Howtosort>
std::vector<const Pracownik*> Pracownicy::sortedBy(Howtosort howtosort) const
{
    std::vector<const Pracownik*> result;
    if(pracownicy.empty())
    {
        return result;
    }
    for(const auto& worker : pracownicy)
    {
        result.push_back(worker.get());
    }
    sort(result.begin(), result.end(), howtosort);
    return result;
}

template <typename Findwho>
const Pracownik* Pracownicy::findBest(Findwho findwho) const
{
    auto it = max_element(pracownicy.begin(), pracownicy.end(), findwho);
    if(it==pracownicy.end())
    {
        return nullptr;
    }
    return it->get();
}

template <typename Findworker>
Pracownik* Pracownicy::findWorkerBy(Findworker findworker)
{
    auto it = find_if(pracownicy.begin(), pracownicy.end(), findworker);
    if(it==pracownicy.end())
    {
        return nullptr;
    }
    return it->get();
}

template <typename Changewhat>
bool Pracownicy::changeDetail(Pracownik* worker, Changewhat changewhat)
{
    if(worker==nullptr)
    {
        std::cerr<<"There is no such worker."<<std::endl;
        return false;
    }
    changewhat(worker);
    return true;
}
template <typename Predicate>
std::vector<const Pracownik*> Pracownicy::getWorkers(Predicate predicate) const
{
    if(pracownicy.empty())
    {
        return{};
    }
    std::vector<const Pracownik*> result;
    for (const auto& worker : pracownicy)
    {
        if(predicate(worker))
            result.push_back(worker.get());
    }

    return result;
}

template <typename Modification>
void Pracownicy::changeAllWorkers(Modification modification)
{
    for_each(pracownicy.begin(), pracownicy.end(), modification);
}

template <typename Condition, typename Modification>
bool Pracownicy::changeWorkers(Condition condition, Modification modification)
{
    bool done=false;
    for (const auto& worker : pracownicy)
    {
        if(condition(worker))
        {
            (modification(worker));
            done=true;
        }
    }
    return done;
}


template <typename Howtocount>
int Pracownicy::countWorkers(Howtocount howtocount) const
{
    if(pracownicy.empty())
    {
        return 0;
    }
    return count_if(pracownicy.begin(), pracownicy.end(), howtocount);
}



