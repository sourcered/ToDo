#ifndef MYSQL_CONSTANTS_H
#define MYSQL_CONSTANTS_H

#include "../preprocessor.h"

#if 1

const std::string SQL_CREATE_DATABASE   = "CREATE DATABASE IF NOT EXISTS DB_ToDo";
const std::string SQL_CREATE_TABLE      = "CREATE TABLE IF NOT EXISTS todo (position INT NOT NULL UNIQUE, task VARCHAR(60) NOT NULL DEFAULT \'No task...\')";
const std::string SQL_ADD_TASK          = "INSERT INTO todo (task) VALUES (?)";
const std::string SQL_ADD_TASK_ORDER    = "INSERT INTO todo (task, position) VALUES (?,?)";
const std::string SQL_REMOVE_TASK       = "DELETE FROM todo WHERE position=?";
const std::string SQL_UPDATE_TASK       = "UPDATE todo SET task=? WHERE position=?";
const std::string SQL_UPDATE_ORDER      = "UPDATE todo SET position=? WHERE position=?";
const std::string SQL_UPDATE_TASK_ORDER = "UPDATE todo SET task=?, position=? WHERE position=?";
const std::string SQL_GET_TASKS_ASC     = "SELECT task FROM todo ORDER BY position ASC";
const std::string SQL_GET_TASKS_DESC    = "SELECT task FROM todo ORDER BY position DESC";
const std::string SQL_GET_POSTIONS_ASC  = "SELECT position FROM todo ORDER BY position ASC";
const std::string SQL_GET_POSTIONS_DESC = "SELECT position FROM todo ORDER BY position DESC";
const std::string SQL_GET_TASK          = "SELECT task FROM todo WHERE position=? LIMIT 1";
const std::string SQL_GET_LAST_POSITION    = "SELECT position FROM todo ORDER BY DESC LIMIT 1";

#else
const std::string SQL_CREATE_DATABASE = "CREATE DATABASE IF NOT EXISTS DB_ToDo"
const std::string SQL_CREATE_TABLE = "CREATE TABLE IF NOT EXISTS todo (position INT NOT NULL UNIQUE, task VARCHAR(60) NOT NULL DEFAULT \'No task...\')";
const std::string SQL_GET_TASKS = "SELECT task FROM todo ORDER BY position ASC";
#endif

#endif
