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
        IDatabase * tmp = new IDatabase();
        tmp->SQL_add_task(task);
        delete tmp;
        tmp = nullptr;
        return false;
    }

    bool Task::remove(int position)
    {
        IDatabase * tmp = new IDatabase();
        tmp->SQL_remove_task(position);
        delete tmp;
        tmp = nullptr;
        return false;
    }

    bool Task::att(std::string task, int position)
    {
        
        return false;
    }
}
