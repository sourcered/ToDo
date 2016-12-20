#include "../include/core_todo.h"

namespace ToDo
{
    Task::Task()
    {
        if(!state)
        {
            io.init();
            state = true;
        }
    }

    bool Task::add(std::string task)
    {
        bool state = false;
        IDatabase * tmp = new IDatabase();
        state = tmp->SQL_add_task(task);
        delete tmp;
        tmp = nullptr;
        return state;
    }

    bool Task::remove(int position)
    {
        bool state = false;
        IDatabase * tmp = new IDatabase();
        state = tmp->SQL_remove_task(position);
        delete tmp;
        tmp = nullptr;
        return state;
    }

    bool Task::att(std::string task, int position)
    {
        bool state = false;
        IDatabase * tmp = new IDatabase();
        state = tmp->SQL_update_task(task, position);
        delete tmp;
        tmp = nullptr;
        return state;
    }

    void Log::print_tasks()
    {
        ODatabase * odatabase = new ODatabase();
        std::vector<std::string> tmp = odatabase->SQL_getTasks();

        for(auto it = tmp.begin(); it != tmp.end(); it++)
            cout << *it << endl;

        delete odatabase;
        odatabase = nullptr;
    }

    void Log::print_task(int position)
    {
        ODatabase * odatabase = new ODatabase();
        std::string task = odatabase->SQL_getTaskByPostion(position);

        cout << task << endl;

        delete odatabase;
        odatabase = nullptr;
    }
}
