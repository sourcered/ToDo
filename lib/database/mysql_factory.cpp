#include "../../include/database/mysql_factory.h"

namespace ToDo
{
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

    bool Factory::init()
    {
        try
        {
            sql::Driver * driver;
            sql::Connection * con;

            driver =  get_driver_instance();
            con = driver->connect("tcp://127.0.0.1:3306", "root", "1234");

            sql::Statement * stm;
            stm = con->createStatement();
            stm->execute(SQL_CREATE_DATABASE);
            con->setSchema("DB_ToDo");
            stm->execute(SQL_CREATE_TABLE);

            closeStatement(stm);
            closeConnection(con);
            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    std::vector<std::string> ODatabase::SQL_getTasks()
    {
        std::vector<std::string> tmp;
        try
        {
            sql::Connection * con;
            sql::Statement * stm;
            sql::ResultSet * rs;

            con = getConnection();
            stm = con->createStatement();
            rs = stm->executeQuery(SQL_GET_TASKS_ASC);

            for (size_t i = 0; rs->next(); i++)
                tmp.push_back(rs->getString("task"));

            closeResultSet(rs);
            closeStatement(stm);
            closeConnection(con);
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
                    sql::Connection * con;
                    sql::Statement * stm;
                    sql::ResultSet * rs;

                    con = getConnection();
                    stm = con->createStatement();
                    rs = stm->executeQuery(SQL_GET_TASKS_DESC);

                    for (size_t i = 0; rs->next(); i++)
                        tmp.push_back(rs->getString("task"));

                    closeResultSet(rs);
                    closeStatement(stm);
                    closeConnection(con);
                }
                catch(sql::SQLException & ex) { }
                break;
            default:
                std::cout << "Erro get Order..." << std::endl;
                break;
        }

        return tmp;
    }

    std::vector<int> ODatabase::SQL_getPostions()
    {
        std::vector<int> tmp;
        try
        {
            sql::Connection * con;
            sql::Statement * stm;
            sql::ResultSet * rs;

            con = getConnection();
            stm = con->createStatement();
            rs = stm->executeQuery(SQL_GET_POSTIONS_ASC);

            for (size_t i = 0; rs->next(); i++)
                tmp.at(i) = rs->getInt("position");

            closeResultSet(rs);
            closeStatement(stm);
            closeConnection(con);
        }
        catch(sql::SQLException & ex) { }

        return tmp;
    }

    std::string ODatabase::SQL_getTaskByPostion(int position)
    {
        sql::Connection * con;
        sql::PreparedStatement * pstm;
        sql::ResultSet * rs;

        std::string tmp = "";

        try
        {
            con = getConnection();
            pstm = con->prepareStatement(SQL_GET_TASK);
            pstm->setInt(1, position);

            rs = pstm->executeQuery();
            rs->first();
            tmp = rs->getString("task");
        }
        catch(sql::SQLException & ex) { std::cout << "Error..." << std::endl; }

        closeResultSet(rs);
        closePreparedStatement(pstm);
        closeConnection(con);

        return tmp;
    }

    int IODatabse::SQL_getLastOrder()
    {
        int tmp = -1;
        try
        {
            sql::Connection * con;
            sql::Statement * stm;
            sql::ResultSet * rs;

            con = getConnection();
            stm = con->createStatement();

            rs = stm->executeQuery(SQL_GET_LAST_POSITION);

            tmp = rs->getInt("position");

            closeResultSet(rs);
            closeStatement(stm);
            closeConnection(con);
        }
        catch(sql::SQLException & ex) {  }

        return tmp;
    }

    bool IDatabase::SQL_add_task(std::string task)
    {
        try
        {
            sql::Connection * con;
            con = getConnection();

            sql::PreparedStatement * pstm;
            pstm = con->prepareStatement(SQL_ADD_TASK);
            pstm->setString(1,task);  //New Task

            // ----------GET LAST ORDER------------------
            int order = SQL_getLastOrder() + 1;          //Get order
            pstm->setInt(2,order);                       //Add to the last element Order
            // ------------------------------------------
            pstm->executeUpdate();

            closePreparedStatement(pstm);
            closeConnection(con);

            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool IDatabase::SQL_add_task_order(std::string task, int order)
    {
        try
        {
            sql::Connection * con;
            sql::PreparedStatement * pstm;

            con = getConnection();
            pstm = con->prepareStatement(SQL_ADD_TASK_ORDER);

            pstm->setString(1,task);    //Task
            pstm->setInt(2, order);     //Order

            pstm->executeUpdate();

            closePreparedStatement(pstm);
            closeConnection(con);
            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool IDatabase::SQL_remove_task(int position)
    {
        try
        {
            sql::Connection * con;
            sql::PreparedStatement * pstm;

            con = getConnection();
            pstm = con->prepareStatement(SQL_REMOVE_TASK);
            pstm->setInt(1, position);

            pstm->executeUpdate();

            closePreparedStatement(pstm);
            closeConnection(con);
            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool IDatabase::SQL_update_task(std::string task, int order)
    {
        try
        {
            sql::Connection * con;
            sql::PreparedStatement * pstm;

            con = getConnection();
            pstm = con->prepareStatement(SQL_UPDATE_TASK);

            pstm->setString(1,task);
            pstm->setInt(2,order);

            pstm->executeUpdate();

            closePreparedStatement(pstm);
            closeConnection(con);
            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool IDatabase::SQL_update_order(int order,int new_order)
    {
        try
        {
            sql::Connection * con;
            sql::PreparedStatement * pstm;

            con = getConnection();
            pstm = con->prepareStatement(SQL_UPDATE_ORDER);

            pstm->setInt(1,new_order);
            pstm->setInt(2,order);
            pstm->executeUpdate();

            closePreparedStatement(pstm);
            closeConnection(con);
            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool IDatabase::SQL_update_task_order(std::string task, int newOrder, int order)
    {
        try
        {
            sql::Connection * con;
            sql::PreparedStatement * pstm;

            con = getConnection();
            pstm = con->prepareStatement(SQL_UPDATE_TASK_ORDER);

            pstm->setString(1,task);
            pstm->setInt(2, newOrder);
            pstm->setInt(3,order);

            pstm->executeUpdate();

            closePreparedStatement(pstm);
            closeConnection(con);
            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool IDatabase::SQL_swapPosition(int position1, int position2)
    {
        ODatabase * odatabase = new ODatabase();
        bool state = false;

        std::string tmp = odatabase->SQL_getTaskByPostion(position1);
        if(SQL_update_task(odatabase->SQL_getTaskByPostion(position2), position1)
                                              && SQL_update_task(tmp, position2))
                                                                    state = true;

        delete odatabase;
        odatabase = nullptr;
        return state;
    }

}
