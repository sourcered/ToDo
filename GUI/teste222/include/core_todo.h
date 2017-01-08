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
    private:
        bool state = false;
        std::shared_ptr<IDatabase> idatabase;
    public:
        explicit Task();
        bool add(std::string);                          //Add task & auto increment position
        bool remove(int);                               //Remove task By Positon
        bool att(std::string, int);                     //Update Task set Task get Postion
        bool swapPosition(int,int);                     //Swap position of 2 any elements
    };

    class Log
    {
    private:
        std::shared_ptr<ODatabase> odatabase;
    public:
        explicit Log();
        void print_tasks();
        void print_task(int);
    };
}

#endif
