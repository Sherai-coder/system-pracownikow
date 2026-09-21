#include <iostream>
#include "menu.h"
#include <sstream>
using namespace std;

void Menu::menuRun()
{
    if(!workers.loadFromFile())
    {
        cerr<<"There was a problem loading the date."<<endl;
        return;
    }
    mainMenu();
    if(!workers.saveToFile())
    {
        cerr<<"There was a problem saving the date."<<endl;
        return;
    }

}

void Menu::mainMenu()
{
    while (true)
    {
        MainMenuOption choice = MainMenuOption::Exit;
        cout<<"1. Show all workers: "<<endl;
        cout<<"2. Add worker: "<<endl;
        cout<<"3. Find worker by: "<<endl;
        cout<<"4. Remove worker by: "<<endl;
        cout<<"5. Sort workers by: "<<endl;
        cout<<"6. Change worker details: "<<endl;
        cout<<"7. Count workers by: "<<endl;
        cout<<"8. Find best by: "<<endl;
        cout<<"9. Show workers by: "<<endl;
        cout<<"10. Change all workers: "<<endl;
        cout<<"11. Change all specific workers."<<endl;
        cout<<"12. Change worker id."<<endl;
        cout<<"13. Show what. "<<endl;
        cout<<"14. Show invald records. "<<endl;
        cout<<"15. Exit."<<endl;
        choice=static_cast<MainMenuOption>(getInt("Choose one of option: ", 1, 15));
        switch(choice)
        {
        case MainMenuOption::ShowAllWorkers:
        {
            workers.showAllWorkersDetails();
            pause();
            break;
        }
        case MainMenuOption::AddWorker:
        {
            addWorkerMenu();
            pause();
            break;
        }
        case MainMenuOption::FindWorkerBy:
        {
            findWorkerByMenu(whichWorkerMenu());
            pause();
            break;
        }
        case MainMenuOption::RemoveWorkerBy:
        {
            removeWorkerByMenu(whichWorkerMenu());
            pause();
            break;
        }
        case MainMenuOption::SortWorkersBy:
        {
            sortWorkersByMenu();
            pause();
            break;
        }
        case MainMenuOption::ChangeWorkerDetail:
        {
            changeWorkerDetailMenu();
            pause();
            break;

        }
        case MainMenuOption::CountWorkersBy:
        {
            countWorkersByMenu();
            pause();
            break;
        }
        case MainMenuOption::FindBestBy:
        {
            findBestByMenu();
            pause();
            break;
        }
        case MainMenuOption::ShowWorkersBy:
        {
            showWorkersByMenu();
            pause();
            break;
        }
        case MainMenuOption::ChangeAllWorkers:
        {
            changeAllWorkersDetailMenu();
            pause();
            break;
        }
        case MainMenuOption::ChangeAllSpecificWorkers:
        {
            changeAllSpecificWorkersMenu();
            pause();
            break;
        }
        case MainMenuOption::ChangeWorkerId:
        {
            changeWorkerIdMenu();
            pause();
            break;
        }
        case MainMenuOption::ShowWhat:
        {
            showWhatMenu();
            pause();
            break;
        }
        case MainMenuOption::ShowInvalidRecords:
            {
                showInvalidRecordsMenu();
                pause();
                break;
            }
        case MainMenuOption::Exit:
        {
            exit();
            return;
        }
        }
    }

}

void Menu::addWorkerMenu()
{
    string name = getWord("Enter name: ");
    TypPracownika type = getWorkerType("Enter worker type: ");
    double salary = getDouble("Enter salary: ",1000, 50000);
    int hours = getInt("Work hours: ",1,120);
    workers.addWorker(name,type,salary,hours);
}


void Menu::findWorkerByMenu(Pracownik* worker)
{
    if(worker!=nullptr)
    {
        worker->showWorkerDetails();
    }
    else return;
}

void Menu::removeWorkerByMenu(Pracownik* worker)
{
    if(worker!=nullptr)
    {
        workers.removeWorker(worker);
    }

}

Pracownik* Menu::whichWorkerMenu()
{
    FindWorkerBy choice = FindWorkerBy::Exit;
    Pracownik* worker=nullptr;
    cout<<"1. By name."<<endl;
    cout<<"2. By id."<<endl;
    cout<<"3. By salary."<<endl;
    cout<<"4. By hours."<<endl;
    cout<<"5. By type."<<endl;
    cout<<"6. Exit."<<endl;
    choice = static_cast<FindWorkerBy>(getInt("Choose: ",1,6));
    switch(choice)
    {
    case FindWorkerBy::Name:
    {
        return workers.findWorkerByName(getWord("Enter name: "));
    }
    case FindWorkerBy::Id:
    {
        return workers.findWorkerById(getInt("Enter id: ",1,10000));
    }
    case FindWorkerBy::Salary:
    {
        return workers.findWorkerBySalary(getDouble("Enter amount of salary: ",1000,30000));
    }
    case FindWorkerBy::Hours:
    {
        return workers.findWorkerByHours(getInt("Enter number of hours: ",1,120));
    }
    case FindWorkerBy::Type:
    {
        return workers.findWorkerByType(stringNaTyp(getWord("Enter worker type: ")));
    }
    case FindWorkerBy::Exit:
    {
        return nullptr;
    }
    default:
        return nullptr;
    }
}

void Menu::sortWorkersByMenu()
{
    vector<const Pracownik*> result;
    SortWorkersBy choice = SortWorkersBy::Exit;
    cout<<"1. Sort by name."<<endl;
    cout<<"2. Sort by id."<<endl;
    cout<<"3. Sort by salary."<<endl;
    cout<<"4. Sort by hours."<<endl;
    cout<<"5. Sort by type."<<endl;
    cout<<"6. Exit."<<endl;
    choice = static_cast<SortWorkersBy>(getInt("Choose: ", 1, 6));
    switch(choice)
    {
    case SortWorkersBy::Name:
    {
        result = workers.sortWorkersByName();
        break;
    }
    case SortWorkersBy::Id:
    {
        result = workers.sortWorkersById();
        break;
    }
    case SortWorkersBy::Salary:
    {
        result = workers.sortWorkersBySalary();
        break;
    }
    case SortWorkersBy::Hours:
    {
        result = workers.sortWorkersByHours();
        break;
    }
    case SortWorkersBy::Type:
    {
        result = workers.sortWorkersByType();
        break;
    }
    case SortWorkersBy::Exit:
    {
        return;
    }
    }
    if(!result.empty())
    {
        for(const auto& worker : result)
        {
            worker->showWorkerDetails();
        }
    }
    else
    {
        cerr<<"There is no workers."<<endl;
        return;
    }

}

void Menu::changeWorkerDetailMenu()
{
    cout<<"Find worker by: "<<endl;
    Pracownik* worker = whichWorkerMenu();
    ChangeWorkerWhat choice = ChangeWorkerWhat::Exit;
    if(worker!=nullptr)
    {
        cout<<"1.Change name."<<endl;
        cout<<"2. Change hours."<<endl;
        cout<<"3. Change salary."<<endl;
        cout<<"4. Change id."<<endl;
        cout<<"5. Change type."<<endl;
        cout<<"6. Exit."<<endl;
        choice = static_cast<ChangeWorkerWhat>(getInt("Choose: ",1,6));
        switch(choice)
        {
        case ChangeWorkerWhat::Name:
        {
            worker->setName(getWord("Enter name: "));
            break;
        }
        case ChangeWorkerWhat::Hours:
        {
            worker->setHours(getInt("Enter numeber of hours: ",1,120));
            break;
        }
        case ChangeWorkerWhat::Salary:
        {
            worker->setSalary(getDouble("Enter amount: ",1000,30000));
            break;
        }
        case ChangeWorkerWhat::Id:
        {
            worker->setId(getInt("Enter new id: ",1, 10000));
            break;
        }
        case ChangeWorkerWhat::Type:
        {
            worker->setType(stringNaTyp(getWord("Enter type: ")));
            break;
        }
        case ChangeWorkerWhat::Exit:
        {
            return;
        }
        }
    }
    else
    {
        cerr<<"There is no such worker."<<endl;
        return;
    }
}

void Menu::countWorkersByMenu()
{
    CountWorkersBy choice = CountWorkersBy::Exit;
    int amount = 0;
    cout<<"1. By type."<<endl;
    cout<<"2. By name."<<endl;
    cout<<"3. By salary."<<endl;
    cout<<"4. By hours."<<endl;
    cout<<"5. Exit."<<endl;
    choice = static_cast<CountWorkersBy>(getInt("Choose: ",1,5));
    switch(choice)
    {
    case CountWorkersBy::Type:
    {
        amount=workers.countWorkersByType(stringNaTyp(getWord("Enter type: ")));
        break;
    }
    case CountWorkersBy::Name:
    {
        amount = workers.countWorkersByName(getWord("Enter name: "));
        break;
    }
    case CountWorkersBy::Salary:
    {
        amount=workers.countWorkersBySalary(getDouble("Enter salary: ", 1000, 40000));
        break;
    }
    case CountWorkersBy::Hours:
    {
        amount=workers.countWorkersByHours(getInt("Enter hours: ",1,120));
        break;
    }
    case CountWorkersBy::Exit:
    {
        return;
    }
    }
    cout<<"There is: "<<amount<<" amount of that workers."<<endl;
    getch();
}

void Menu::findBestByMenu()
{
    const Pracownik* worker = nullptr;
    int choice= 0;
    cout<<"1. Find best paid worker."<<endl;
    cout<<"2. Find worker with longest hours."<<endl;
    cout<<"3. Exit."<<endl;
    choice = getInt("Choose: ",1,3);
    switch(choice)
    {
    case 1:
    {
        worker = workers.findBestPaidWorker();
        break;
    }
    case 2:
    {
        worker=workers.findWorkerWithLongestHours();
        break;
    }
    case 3:
    {
        return;
    }
    }
    if(worker!=nullptr)
    {
        worker->showWorkerDetails();
    }
    else
    {
        cerr<<"There is no such Worker."<<endl;
    }

}
void Menu::showWorkersByMenu()
{
    vector<const Pracownik*> result;
    ShowWorkersBy choice = ShowWorkersBy::Exit;
    cout<<"1. Get workers above salary."<<endl;
    cout<<"2. Get workers above hours."<<endl;
    cout<<"3. Get workers with specific type."<<endl;
    cout<<"4. Get workers with name. "<<endl;
    cout<<"5. With salary beetwen."<<endl;
    cout<<"6. Exit."<<endl;;
    choice= static_cast<ShowWorkersBy>(getInt("Choose: ",1,6));
    switch(choice)
    {
    case ShowWorkersBy::AboveSalary:
    {
        result=workers.getWorkersAboveSalary(getDouble("Enter amount: ", 1, 40000));
        break;
    }
    case ShowWorkersBy::AboveHours:
    {
        result = workers.getWorkersAboveHours(getInt("Enter numeber of hours: ", 1, 120));
        break;
    }
    case ShowWorkersBy::WithSpecificType:
    {
        result = workers.getWorkersWithSpecificType(stringNaTyp(getWord("Enter Type: ")));
        break;
    }
    case ShowWorkersBy::WithName:
    {
        result = workers.getWorkersWithName(getWord("Enter name: "));
        break;
    }
    case ShowWorkersBy::WithSalaryBeetwen:
    {
        result = workers.getWorkersWithSalaryBetween(getDouble("From: ",1,40000), getDouble("To: ",1,40000));
        break;
    }
    case ShowWorkersBy::Exit:
    {
        return;
    }
    }
    if(!result.empty())
    {
        for(const auto& worker : result)
        {
            worker->showWorkerDetails();
        }
    }
    else
    {
        cerr<<"There is no such workers."<<endl;
    }
}
void Menu::changeAllWorkersDetailMenu()
{
    int choice = 0;
    cout<<"1. Change all workers salary."<<endl;
    cout<<"2. Change all workers hours."<<endl;
    cout<<"3. Exit."<<endl;
    choice=getInt("Choose:", 1,3);
    switch(choice)
    {
    case 1:
    {
        workers.changeAllWorkersSalary(getDouble("Enter amount: ",1000,40000));
        break;
    }
    case 2:
    {
        workers.changeAllWorkersHours(getInt("Enter amount: ",10,120));
        break;
    }
    case 3:
    {
        return;
    }
    }
}

void Menu::changeAllSpecificWorkersMenu()
{
    bool done = false;
    done = workers.changeSpecificWorkersSalary(stringNaTyp(getWord("Enter type: ")), getDouble("Enter Amount: ", 1000, 40000));
    if(!done)
    {
        cerr<<"There is no workers to change."<<endl;
    }
    else cout<<"The operation was successfull."<<endl;
}

void Menu::changeWorkerIdMenu()
{
    cout<<"How would you like to choose worker: "<<endl;
    Pracownik* worker = whichWorkerMenu();
    if(worker!=nullptr)
    {
        worker->showWorkerDetails();
        while(true)
        {
            int id=0;
            id=getInt("Type new id for this worker: ",1,10000);
            if(id==worker->getId())
            {
                cout<<"This is same id as worker has."<<endl;
            }
            else if (workers.changeWorkerId(worker,id))
            {
                cout<<"Id changed."<<endl;
                break;
            }
            else cout<<"This id already exist."<<endl;
        }
    }
    else if(worker==nullptr) cout<<"There is no such worker."<<endl;

}

void Menu::showWhatMenu()
{
    double amount=0.0;
    ShowWhat choice = ShowWhat::Exit;
    cout<<"1. Average salary of all workers."<<endl;
    cout<<"2. Whole salary of all."<<endl;
    cout<<"3. Highest earning per hour."<<endl;
    cout<<"4. Exit."<<endl;
    choice=static_cast<ShowWhat>(getInt("Choose: ",1,4));
    switch(choice)
    {
    case ShowWhat::AverageSalary:
    {
        amount = workers.calculateAverageSalary();
        break;
    }
    case ShowWhat::WholeSalary:
    {
        amount=workers.accumulateWholeSalary();
        break;
    }
    case ShowWhat::HighestEarningsPerHour:
    {
        amount=workers.getHighestEarningsPerHour();
        break;
    }
    }
    cout<<"Result: "<<amount<<endl;
}

void Menu::showInvalidRecordsMenu()
{
    workers.showInvalidRecords();
}
void Menu::exit()
{
    cout<<"Goodbye."<<endl;
    workers.saveToFile();
}
