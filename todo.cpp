#include "include/core_todo.h"

int main()
{
    ToDo::Task * c = new ToDo::Task();
    // std::cout << c->att("Sair com a bike...", 1) << endl;
    delete c;

    ToDo::Log * l = new ToDo::Log();
    l->print_task(1);
    delete l;

    return 0;
}

//Add tasks
//View Tasks
