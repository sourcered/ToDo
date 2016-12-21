#include "include/core_todo.h"

int main()
{
    ToDo::Task * c = new ToDo::Task();
    std::cout << c->add("Subir a escada.") << std::endl;
    delete c;
    c = nullptr;

    ToDo::Log * l = new ToDo::Log();
    l->print_task(5);
    delete l;
    l = nullptr;

    return 0;
}
