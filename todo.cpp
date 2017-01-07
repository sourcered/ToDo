#include "include/core_todo.h"

int main()
{
    std::unique_ptr<ToDo::Task> c(new ToDo::Task());
    // std::cout << c->add("Polir os pratos.") << std::endl;
    // std::cout << "Remove: " << c->remove(18) << std::endl;
    // std::cout << c->att("Comprar danone.",3) << std::endl;
    // std::cout << c->swapPosition(16,22) << std::endl;

    std::unique_ptr<ToDo::Log> l(new ToDo::Log());
    l->print_tasks();

    return 0;
}
