#ifndef CORE_TODO_H
#define CORE_TODO_H

#include "database/mysql_factory.h"

namespace ToDo
{

    struct data
    {
        std::vector<std::string> task;
        std::vector<int> order;
    };

    class Task
    {
    public:
        bool add(std::string);                          //Add task & auto increment position
        bool remove(int);                               //Remove task By Positon
        bool att(std::string, int);                     //Update Task set Task get Postion
    };
}

#endif
