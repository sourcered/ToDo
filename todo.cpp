#include "include/core_todo.h"

int main()
{
    ToDo::Task * c = new ToDo::Task();
    c->remove(5);
    delete c;

    return 0;
}

//Add tasks
//View Tasks
