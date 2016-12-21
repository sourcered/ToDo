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
        IODatabse io;
        bool state = false;
    public:
        explicit Task();
        bool add(std::string);                          //Add task & auto increment position
        bool remove(int);                               //Remove task By Positon
        bool att(std::string, int);                     //Update Task set Task get Postion
        bool swapPosition(int,int);
    };

    class Log
    {
    private:
    public:
        void print_tasks();
        void print_task(int);
    };
}

#endif
