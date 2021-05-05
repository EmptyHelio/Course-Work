#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    window = new Menu_window();
       // подключаем к слоту запуска главного окна по кнопке во втором окне
    connect(window, &Menu_window::firstWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    window->show();
    this->close();
}
