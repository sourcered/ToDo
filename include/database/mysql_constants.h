#ifndef MYSQL_CONSTANTS_H
#define MYSQL_CONSTANTS_H

#include "../preprocessor.h"

#if 1

const std::string SQL_CREATE_DATABASE = "CREATE DATABASE IF NOT EXISTS DB_ToDo";
const std::string SQL_CREATE_TABLE = "CREATE TABLE IF NOT EXISTS todo (order INT NOT NULL UNIQUE, task VARCHAR(60) NOT NULL DEFAULT \'No task...\')";
const std::string SQL_ADD_TASK = "INSET INTO todo (task) VALUES (?)";
const std::string SQL_ADD_TASK_ORDER = "INSET INTO todo (task,order) VALUES (?,?)";
const std::string SQL_REMOVE_TASK = "DELETE FROM TABLE todo WHERE order=?";
const std::string SQL_UPDATE_TASK = "UPDATE todo SET task=? WHERE order=?";
const std::string SQL_UPDATE_ORDER = "UPDATE todo SET order=? WHERE order=?";
const std::string SQL_UPDATE_TASK_ORDER = "UPDATE todo SET task=?, order=? WHERE order=?";
const std::string SQL_GET_TASKS_ASC = "SELECT task FROM todo ORDER BY order ASC";
const std::string SQL_GET_TASKS_DESC = "SELECT task FROM todo ORDER BY order ASC";

#else
const std::string SQL_CREATE_DATABASE = "CREATE DATABASE IF NOT EXISTS DB_ToDo"
const std::string SQL_CREATE_TABLE = "CREATE TABLE IF NOT EXISTS todo (order INT NOT NULL UNIQUE, task VARCHAR(60) NOT NULL DEFAULT \'No task...\')";
const std::string SQL_GET_TASKS = "SELECT task FROM todo ORDER BY order ASC";
#endif

#endif
