#include "../include/core_todo.h"

namespace ToDo
{
    Task::Task()
    {
        if(!state)
        {
            std::shared_ptr<IDatabase> tmp(new IDatabase());
            idatabase = tmp;
            state = true;
        }
    }

    bool Task::add(std::string task)
    {
        bool state = false;
        state = idatabase->SQL_add_task(task);
        return state;
    }

    bool Task::remove(int position)
    {
        bool state = false;
        state = idatabase->SQL_remove_task(position);
        return state;
    }

    bool Task::att(std::string task, int position)
    {
        bool state = false;
        state = idatabase->SQL_update_task(task, position);
        return state;
    }

    bool Task::swapPosition(int position1, int position2)
    {
        bool state = false;
        state = idatabase->SQL_swapPosition(position1, position2);
        return state;
    }

    Log::Log()
    {
        std::shared_ptr<ODatabase> tmp(new ODatabase());
        odatabase = tmp;
    }

    void Log::print_tasks()
    {
        std::vector<std::string> tmp = odatabase->SQL_getTasks();

        for(auto it = tmp.begin(); it != tmp.end(); it++)
            std::cout << *it << std::endl;
    }

    void Log::print_task(int position)
    {
        std::string task;
        task = odatabase->SQL_getTaskByPostion(position);

        std::cout << task << std::endl;
    }
}
