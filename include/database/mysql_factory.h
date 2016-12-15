#ifndef MYSQL_FACTORY_H
#define MYSQL_FACTORY_H

#include "mysql_constants.h"

#ifndef MYSQL_INCLUDES
#define MYSQL_INCLUDES
  #include "mysql_connection.h"                                //Improve build time
  #include <cppconn/driver.h>
  #include <cppconn/exception.h>
  #include <cppconn/resultset.h>
  #include <cppconn/statement.h>
  #include <cppconn/prepared_statement.h>
#endif

namespace ToDo
{
    class Factory
    {
    public:
        sql::Connection * getConnection();
        bool closeConnection(sql::Connection *);
        bool closeStatement(sql::Statement *);
        bool closePreparedStatement(sql::PreparedStatement *);
        bool init(sql::Connection *);
    };

    class IODatabse : public Factory                            //Abstract class
    {
    public:
    };

    class IDatabase : public IODatabse
    {
    public:
        bool SQL_add_task(std::string);
        bool SQL_add_task_order(std::string, int);
        bool SQL_remove_task(int);
        bool SQL_update_task(std::string, int);                   //Update just task     || (new string, order)
        bool SQL_update_order(int, int);                          //Update just order    || (new Order, old order)
        bool SQL_update_task_order(std::string, int, int);        //Update task &  order || (new string, new order, old order)
    };

    class ODatabase : public IODatabse
    {
    public:
        std::vector<std::string> SQL_getTasks();
        std::vector<std::string> SQL_getTasks(order);             //Get task by Order
        std::vector<int> SQL_getPostions();
        std::string SQL_getTasksByPostion(int);
    };

}

#endif