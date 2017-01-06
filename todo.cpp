#include "include/core_todo.h"

int main()
{
    std::unique_ptr<ToDo::Task> c(new ToDo::Task());
    std::cout << c->add("Sacar dinheiro.") << std::endl;

    std::unique_ptr<ToDo::Log> l(new ToDo::Log());
    l->print_tasks();

    return 0;
}
