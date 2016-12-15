#include "../../include/database/mysql_factory.h"

namespace ToDo
{
    sql::Connection * Factory::getConnection()
    {
        sql::Driver * driver;
        sql::Connection * con;

        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "1234");
        con->setSchema("DB_ToDo");

        return con;
    }

    bool Factory::closeConnection(sql::Connection * con)
    {
      try
      {
          con->close();
          delete con;
          return true;
      }
      catch(sql::SQLException & ex) { return false; }
    }

    bool Factory::closeStatement(sql::Statement * stm)
    {
        try
        {
            stm->close();
            delete stm;
            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool Factory::closePreparedStatement(sql::PreparedStatement * pstm)
    {
        try
        {
            pstm->close();
            delete pstm;
            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool Factory::init(sql::Connection * con)
    {
        try
        {
            sql::Statement * stm;
            stm = con->createStatement();
            stm->execute(SQL_CREATE_DATABASE);
            stm->execute(SQL_CREATE_TABLE);
            stm->close();
            delete stm;
            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool IDatabase::SQL_add_task(std::string task)
    {
        try
        {
            sql::Connection * con;
            con = getConnection();

            sql::PreparedStatement * pstm;
            pstm = con->prepareStatement(SQL_ADD_TASK);
            pstm->setString(1,task);  //Task

            // ----------GET LAST ORDER------------------
            int order = 1;  //Get order
            pstm->setInt(2,order);  //Add to the last element Order
            // ------------------------------------------
            pstm->executeUpdate();

            if(closePreparedStatement(pstm)) delete pstm;
            if(closeConnection(con)) delete con;

            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool IDatabase::SQL_add_task_order(std::string task, int order)
    {
        try
        {
            sql::Connection * con;
            con = getConnection();
            sql::PreparedStatement * pstm;
            pstm = con->prepareStatement(SQL_ADD_TASK_ORDER);
            pstm->setString(1,task);  //Task
            pstm->setInt(2, order);     //Order
            pstm->executeUpdate();
            if(closePreparedStatement(pstm)) delete pstm;
            if(closeConnection(con)) delete con;
            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool IDatabase::SQL_remove_task(int order)
    {
        try
        {
            sql::Connection * con;
            con = getConnection();
            sql::PreparedStatement pstm;
            pstm = con->prepareStatement(SQL_REMOVE_TASK);
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
            con = getConnection();
            sql::PreparedStatement pstm;
            pstm = con->prepareStatement(SQL_UPDATE_TASK);
            pstm->setString(1,task);
            pstm->setInt(2,order);
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
            con = getConnection();
            sql::PreparedStatement pstm;
            pstm = con->prepareStatement(SQL_UPDATE_ORDER);
            pstm->setInt(1,new_order);
            pstm->setInt(2,order);
            closePreparedStatement(pstm);
            closeConnection(con);
            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    bool IDatabase::SQL_update_task_order(std::string task, int order, int newOrder)
    {
        try
        {
            return true;
        }
        catch(sql::SQLException & ex) { return false; }
    }

    std::vector<std::string> ODatabase::SQL_getTasks()
    {
        std::vector<std::string> tmp;
        return tmp;
    }

    std::vector<std::string> ODatabase::SQL_getTasks(order ord)
    {
        std::vector<std::string> tmp;
        switch (ord)
        {
            case asc:
                break;
            case desc:
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
        return tmp;
    }

    std::string ODatabase::SQL_getTasksByPostion(int)
    {
        std::string tmp;
        return tmp;
    }
}