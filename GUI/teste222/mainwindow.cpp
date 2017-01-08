#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(330,500);

    ui->mainToolBar->setMovable(false);

    std::shared_ptr<ToDo::Task> tmp(new ToDo::Task());
    core = tmp;

    std::shared_ptr<ToDo::Factory> tmp2(new ToDo::Factory());
    factory = tmp2;

    std::shared_ptr<ToDo::ODatabase> tmp3(new ToDo::ODatabase());
    odatabase = tmp3;

    update_widgetList();
    showTasks();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_save_clicked()
{
    ui->listWidget_main->addItem(ui->lineEdit_main->text());
    if(core->add(ui->lineEdit_main->text().toStdString()))
        ui->statusBar->showMessage("Save Sucess.", 5000);
    else
        ui->statusBar->showMessage("Save Error.", 5000);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this,"About","Version: 0.0.2\nAuthor: Igor\nState: BETA");
}

//Show a new Window, Just with text Box and Save Button
void MainWindow::on_actionAdd_triggered()
{
    ui->listWidget_main->addItem(ui->lineEdit_main->text());
    if(core->add(ui->lineEdit_main->text().toStdString()))
        ui->statusBar->showMessage("Added Sucess.", 5000);
    else
        ui->statusBar->showMessage("Added Error.", 5000);
}

void MainWindow::on_actionRemove_triggered()
{
    update_widgetList();
    int row = ui->listWidget_main->currentRow()+1;
    delete ui->listWidget_main->currentItem();

    if(core->remove(row))
        ui->statusBar->showMessage("Removed Sucess.", 5000);
    else
        ui->statusBar->showMessage("Removed Error.", 5000);
    update_widgetList();
}

void MainWindow::on_actionEdit_2_triggered()
{
    QString txt = ui->lineEdit_main->text();
    ui->listWidget_main->currentItem()->setText(txt);
    if(core->att(txt.toStdString(), ui->listWidget_main->currentRow()))
        ui->statusBar->showMessage("Edited Sucess.", 5000);
    else
        ui->statusBar->showMessage("Edited Error.", 5000);
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::update_widgetList()
{
    factory->update_positions();
}

void MainWindow::showTasks()
{
    //Clear all tasks
    ui->listWidget_main->clear();

    //Add tasks to Widget List
    std::vector<std::string> task = odatabase->SQL_getTasks();

    for(size_t i = 0; i < task.size(); i++)
        ui->listWidget_main->addItem(QString::fromUtf8(task.at(i).c_str()));
}
