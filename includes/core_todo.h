#ifndef CORE_TODO_H
#define CORE_TODO_H

#include "preprocessor.h"

#ifndef MYSQL_INCLUDES
#define MYSQL_INCLUDES
  #include "mysql_connection.h"

  #include <cppconn/driver.h>
  #include <cppconn/exception.h>
  #include <cppconn/resultset.h>
  #include <cppconn/statement.h>
  #include <cppconn/prepared_statement.h>
#endif

#if 1

const std::string SQL_CREATE_TABLE = "CREATE TABLE IF NOT EXISTS todo (order INT NOT NULL UNIQUE, task VARCHAR(60) NOT NULL DEFAULT \'No task...\')";
const std::string SQL_ADD_TASK = "INSET INTO todo (task) VALUES (?)";
const std::string SQL_ADD_TASK_ORDER = "INSET INTO todo (task,order) VALUES (?,?)";
const std::string SQL_REMOVE_TASK = "DELETE FROM TABLE todo WHERE order=?";
const std::string SQL_UPDATE_TASK = "UPDATE todo SET task=? WHERE order=?";
const std::string SQL_UPDATE_ORDER = "UPDATE todo SET order=? WHERE order=?";
const std::string SQL_UPDATE_TASK_ORDER = "UPDATE todo SET task=?, order=? WHERE order=?";

#else
const std::string SQL_UPDATE_TASK_ORDER = "UPDATE TABLE todo SET task=?, order=? WHERE order=?";
#endif

namespace ToDo
{
    enum order
    {
        asc,
        desc
    };

    struct data
    {
        std::vector<std::string> task;
        std::vector<int> order;
    };

    class Factory
    {
    public:
        sql::Connection * getConnection();
        bool closeConnection(sql::Connection *);
        bool closePreparedStatement(sql::PreparedStatement *);
        bool init(sql::Connection *);
        bool SQL_add_task(std::string);
        bool SQL_add_task_order(std::string, int);
        bool SQL_remove_task(int);
        bool SQL_update_task(std::string, int);                   //Update just task
        bool SQL_update_order(int);                               //Update just order
        bool SQL_update_task_order(std::string, int, int);        //Update task &  order
    };

    class Task
    {
    public:
        bool add(std::string);    //Add task & increment position
        bool remove(int);         //By Positon
    };

    class View
    {
    public:
        std::vector<std::string> getTasks();
        std::vector<std::string> getTasks(order);
        std::vector<int> getPostions();
        std::string getTasksByPostion(int);
    };


}

#endif
