#include "include/core_todo.h"

int main()
{
    std::unique_ptr<ToDo::Task> c(new ToDo::Task());
    std::cout << c->add("Aguardar o sinal.") << std::endl;
    std::cout << "Remove: " << c->remove(12) << std::endl;
    std::cout << c->att("Cha.",4) << std::endl;
    std::cout << c->swapPosition(1,22) << std::endl;

    std::unique_ptr<ToDo::Log> l(new ToDo::Log());
    l->print_tasks();

    return 0;
}
