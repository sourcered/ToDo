#include "../../include/database/mysql_factory.h"

namespace ToDo
{
    Factory::Factory()
    {
      sql::Driver * driver;

      driver =  get_driver_instance();
      std::shared_ptr<sql::Connection> tmp(driver->connect("tcp://127.0.0.1:3306", "root", "1234"));
      con = tmp;
      con->setSchema("DB_ToDo");
    }

    Factory::~Factory()
    {
      delete rs;
      rs = nullptr;
      delete stm;
      stm = nullptr;
      delete pstm;
      pstm = nullptr;
    }

    sql::Connection * Factory::getConnection()
    {
        sql::Driver * driver;
        sql::Connection * con;

        driver =  get_driver_instance();

        con = driver->connect("tcp://127.0.0.1:3306", "root", "1234");
        con->setSchema("DB_ToDo");

        return con;
    }

    bool Factory::closeConnection(sql::Connection *& con)
    {
      try
      {
          con->close();
          delete con;
          con = nullptr;
          return true;
      }
      catch(sql::SQLException & ex) { return false; }
    }

    bool Factory::closeStatement(sql::Statement *& stm)
    {
        try
        {
            stm->close();
            delete stm;
            stm = nullptr;
            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool Factory::closePreparedStatement(sql::PreparedStatement *& pstm)
    {
        try
        {
            pstm->close();
            delete pstm;
            pstm = nullptr;
            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool Factory::closeResultSet(sql::ResultSet *& rs)
    {
        try
        {
            rs->close();
            delete rs;
            rs = nullptr;
            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool update_positions()
    {
      try
      {
          stm = con->createStatement();
          stm->execute(SQL_DROP_POSITION);
          stm->execute(SQL_AUTOINCREMENT_1);
          stm->execute(SQL_ADD_POSITION_COLUMN);

          return true;
      }
      catch(sql::SQLException & ex) { return false; }

      return false;
    }

    bool Factory::init()
    {
        try
        {
            stm = con->createStatement();
            stm->execute(SQL_CREATE_DATABASE);
            con->setSchema("DB_ToDo");
            stm->execute(SQL_CREATE_TABLE);

            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    std::vector<std::string> ODatabase::SQL_getTasks()
    {
        std::vector<std::string> tmp;
        try
        {
            stm = con->createStatement();
            rs = stm->executeQuery(SQL_GET_TASKS_ASC);

            for (size_t i = 0; rs->next(); i++)
                tmp.push_back(rs->getString("task"));
        }
        catch(sql::SQLException & ex) { }

        return tmp;
    }

    std::vector<std::string> ODatabase::SQL_getTasks(order ord)
    {
        std::vector<std::string> tmp;
        switch (ord)
        {
            case asc:
                tmp = SQL_getTasks();
                break;
            case desc:
                try
                {
                    stm = con->createStatement();
                    rs = stm->executeQuery(SQL_GET_TASKS_DESC);

                    for (size_t i = 0; rs->next(); i++)
                        tmp.push_back(rs->getString("task"));
                }
                catch(sql::SQLException & ex) { }
                break;
            default:
                std::cout << "Erro get Order..." << std::endl;
                break;
        }

        return tmp;
    }

    std::vector<int> ODatabase::SQL_getPositions()
    {
        std::vector<int> tmp;
        try
        {
            stm = con->createStatement();
            rs = stm->executeQuery(SQL_GET_POSTIONS_ASC);

            for (size_t i = 0; rs->next(); i++)
                tmp.at(i) = rs->getInt("position");
        }
        catch(sql::SQLException & ex) { }

        return tmp;
    }

    std::string ODatabase::SQL_getTaskByPosition(int position)
    {
        std::string tmp = "";

        try
        {
            pstm = con->prepareStatement(SQL_GET_TASK);
            pstm->setInt(1, position);

            rs = pstm->executeQuery();
            rs->first();
            tmp = rs->getString("task");
        }
        catch(sql::SQLException & ex) { std::cout << "Error..." << std::endl; tmp = "404"; }

        return tmp;
    }

    int IODatabse::SQL_getLastOrder()
    {
        int tmp = -1;
        try
        {
            stm = con->createStatement();

            rs = stm->executeQuery(SQL_GET_LAST_POSITION);

            tmp = rs->getInt("position");
        }
        catch(sql::SQLException & ex) {  }

        return tmp;
    }

    bool IDatabase::SQL_add_task(std::string task)
    {
        try
        {
            pstm = con->prepareStatement(SQL_ADD_TASK);
            pstm->setString(1,task);  //New Task

            // ----------GET LAST ORDER------------------
            int order = SQL_getLastOrder() + 1;          //Get order
            pstm->setInt(2,order);                       //Add to the last element Order
            // ------------------------------------------
            pstm->executeUpdate();

            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool IDatabase::SQL_add_task_order(std::string task, int order)
    {
        try
        {
            pstm = con->prepareStatement(SQL_ADD_TASK_ORDER);

            pstm->setString(1,task);    //Task
            pstm->setInt(2, order);     //Order

            pstm->executeUpdate();

            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool IDatabase::SQL_remove_task(int position)
    {
        try
        {
            pstm = con->prepareStatement(SQL_REMOVE_TASK);
            pstm->setInt(1, position);

            pstm->executeUpdate();

            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool IDatabase::SQL_update_task(std::string task, int order)
    {
        try
        {
            pstm = con->prepareStatement(SQL_UPDATE_TASK);

            pstm->setString(1,task);
            pstm->setInt(2,order);

            pstm->executeUpdate();

            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool IDatabase::SQL_update_order(int order,int new_order)
    {
        try
        {
            pstm = con->prepareStatement(SQL_UPDATE_ORDER);

            pstm->setInt(1,new_order);
            pstm->setInt(2,order);
            pstm->executeUpdate();

            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool IDatabase::SQL_update_task_order(std::string task, int newOrder, int order)
    {
        try
        {
            pstm = con->prepareStatement(SQL_UPDATE_TASK_ORDER);

            pstm->setString(1,task);
            pstm->setInt(2, newOrder);
            pstm->setInt(3,order);

            pstm->executeUpdate();

            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool IDatabase::SQL_swapPosition(int position1, int position2)
    {
        std::unique_ptr<ODatabase> odatabase(new ODatabase());

        std::string tmp = odatabase->SQL_getTaskByPosition(position1);
        std::string tmp2 = odatabase->SQL_getTaskByPosition(position2);

        if(tmp != "404" && tmp2 != "404" && SQL_update_task(odatabase->SQL_getTaskByPosition(position2), position1)
                                               && SQL_update_task(tmp, position2))
                                                                     return true;
        return false;
    }

}
