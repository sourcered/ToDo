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
        return idatabase->SQL_add_task(task);
    }

    bool Task::remove(int position)
    {
        return idatabase->SQL_remove_task(position);;
    }

    bool Task::att(std::string task, int position)
    {
        return idatabase->SQL_update_task(task, position);
    }

    bool Task::swapPosition(int position1, int position2)
    {
        return idatabase->SQL_swapPosition(position1, position2);
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
        std::cout << odatabase->SQL_getTaskByPosition(position) << std::endl;
    }
}
