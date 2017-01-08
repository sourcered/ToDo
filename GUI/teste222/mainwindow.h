#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <thread>

#include "include/core_todo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void update_widgetList();
    void showTasks();

private slots:
    void on_btn_save_clicked();

    void on_actionAbout_triggered();

    void on_actionAdd_triggered();

    void on_actionRemove_triggered();

    void on_actionEdit_2_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<ToDo::Task> core;
    std::shared_ptr<ToDo::Factory> factory;
    std::shared_ptr<ToDo::ODatabase> odatabase;
};

#endif // MAINWINDOW_H
