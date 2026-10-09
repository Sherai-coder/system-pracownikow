#pragma once
#include <iostream>
#include "pracownik.h"
#include "pracownicy.h"
#include "input.h"
#include "typPracownika.h"

using namespace std;

enum class MainMenuOption
{
    ShowAllWorkers=1,
    AddWorker,
    FindWorkerBy,
    RemoveWorkerBy,
    SortWorkersBy,
    ChangeWorkerDetail,
    CountWorkersBy,
    FindBestBy,
    ShowWorkersBy,
    ChangeAllWorkers,
    ChangeAllSpecificWorkers,
    ShowWhat,
    ShowInvalidRecords,
    Exit
};

enum class FindWorkerBy
{
    Name=1,
    Id,
    Salary,
    Hours,
    Type,
    Exit
};
enum class SortWorkersBy
{
    Name=1,
    Id,
    Salary,
    Hours,
    Type,
    Exit
};

enum class ChangeWorkerWhat
{
    Name=1,
    Hours,
    Salary,
    Type,
    Exit
};
enum class CountWorkersBy
{
    Type=1,
    Name,
    Salary,
    Hours,
    Exit
};

enum class ShowWorkersBy
{
    AboveSalary=1,
    AboveHours,
    WithSpecificType,
    WithName,
    WithSalaryBeetwen,
    Exit
};

enum class ShowWhat
{
    AverageSalary=1,
    WholeSalary,
    HighestEarningsPerHour,
    Exit
};


class Menu
{
    Pracownicy& workers;
    void addWorkerMenu();
    void workerMenu();
    void mainMenu();
    void findWorkerByMenu(Pracownik* worker);
    void removeWorkerByMenu(Pracownik* worker);
    Pracownik* whichWorkerMenu();
    void sortWorkersByMenu();
    void changeWorkerDetailMenu();
    void countWorkersByMenu();
    void findBestMenu();
    void showWorkersByMenu();
    void changeAllWorkersDetailMenu();
    void changeAllSpecificWorkersSalaryMenu();
    void showWhatMenu();
    void showInvalidRecordsMenu();
    void exit();
public:
    Menu(Pracownicy& workers) : workers(workers)
    {

    }
    void menuRun();


};
