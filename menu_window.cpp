#include "menu_window.h"
#include "ui_menu_window.h"
#include "QMessageBox"
#include <QDebug>
#include <QTableWidget>
#include <cmath>
#include <QProcess>
#include <QDir>

Menu_window::Menu_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu_window)
{
    ui->setupUi(this);
    //Задаем картинку в качестве фона главного меню
    QPixmap pix(":/1.jpg");
    ui->label->setPixmap(pix);

    //Настраиваем стиль кнопок главного меню
    QString my_btn = "QPushButton{"
                                    "border: 1px solid transparent;text-align: center;"
                                    "color:rgba(255,255,255,255);"
                                    "border-radius: 8px;"
                                    "border-width: 3px;"
                                    "border-image: 9,2,5,2; "
                                    "background-position: top left;"
                                    "background-origin: content;"
                                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(200, 110, 100, 200), stop:1 rgba(130, 148, 130, 200));}"
                                    "QPushButton::chunk {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgba(255,200,0,255), stop: 1 rgba(255,0,0,255));}"
                                    "QPushButton{border-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 200, 200, 200), stop:1 rgba(255, 200, 200, 200));}";

    //Применяем стиль к кнопкам и задаем фиксированный размер
    ui->pushButton->setStyleSheet(my_btn);
    ui->pushButton_2->setStyleSheet(my_btn);
    ui->pushButton_3->setStyleSheet(my_btn);
    ui->pushButton_4->setStyleSheet(my_btn);
    ui->pushButton_5->setStyleSheet(my_btn);
    ui->pushButton_6->setStyleSheet(my_btn);
    ui->pushButton_7->setStyleSheet(my_btn);

    const QSize btnSize = QSize(70, 30);
    ui->pushButton->setFixedSize(btnSize);
    ui->pushButton_2->setFixedSize(btnSize);
    ui->pushButton_3->setFixedSize(btnSize);
    ui->pushButton_4->setFixedSize(btnSize);
    ui->pushButton_5->setFixedSize(btnSize);
    ui->pushButton_6->setFixedSize(95, 30);
    ui->pushButton_7->setFixedSize(80, 30);
}
Menu_window::~Menu_window()
{
    delete ui;
}
/*
Для корректного отображения данных на одном фрейме
На нужно после каждой нажатой кнопки удалять предыдущий слой
*/
void clearLayout(QLayout *layout) {
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}

void Menu_window::on_pushButton_clicked()
{
    //Подготовка слоя для отображения данных
    clearLayout(ui->horizontalLayout_3);
    ui->horizontalLayoutWidget->hide();
    ui->gridLayoutWidget->hide();
    ui->label_2->setAlignment(Qt::AlignCenter);
    ui->label_2->setStyleSheet("background-color: rgb(50, 0, 75);"
                               "color: rgb(255, 255, 255);"
                               "font: 12pt \"Roboto\";"
                               "font:bold;");
    ui->label_2->setText("Shalaiev Mykola\nstudent of 124 group\nperformed");
    this->setWindowTitle("AUTHOR");

    //При нажатии, кнопка блокируется, а другие становятся активными активны
    ui->pushButton->setDisabled(1);
    ui->pushButton_2->setDisabled(0);
    ui->pushButton_3->setDisabled(0);
    ui->pushButton_7->setDisabled(0);

    clearLayout(ui->horizontalLayout_2);
    clearLayout(ui->horizontalLayout_3);
}


void Menu_window::on_pushButton_5_clicked()
{
    this->close();      // Закрываем окно
    emit firstWindow();
}

void Menu_window::on_pushButton_4_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Exit", "Do you want to exit the program?",
                           QMessageBox::Yes | QMessageBox::No);

     if (reply == QMessageBox::Yes){
            this->close();
     }else{
            qDebug() << "Button Don't Clicked";
     }
}


//Создаем MessageBox для Матрицы, Вектора и Функции.
void MsgBox_matrix(){
    QMessageBox msgBox;
    msgBox.setWindowTitle("MATRIX");
    msgBox.setText("Matrix A[i][j], elements of which\n"
                    "are calculated by the formula: \n"
                    "\nA[i][j] = 3.5^2i*abs(i-3j) + ((2+j) / (i+j))\n"
                    "where i = 0...5; j = 0...6");

    msgBox.exec();

}

void MsgBox_vector(){
    QMessageBox msgBox;
    msgBox.setWindowTitle("VECTOR");
    msgBox.setText("VECTOR X[i] is a the sum of the squares\n"
                    "of those elements in the i-th row of the matrix\n"
                    "that have a paired friend index.");
    msgBox.exec();
}

void MsgBox_function(){
    QMessageBox msgBox;
    msgBox.setWindowTitle("FUNCTION");
    msgBox.setText("Calculate the function 'G' by the formula.");
    msgBox.exec();
}
///////////////////////////////////////////////////////////
//Создадим глобальные переменные для хранения  матрицы и вектора
double expression;
QString matrix_a[6][7] = {{ 0 }};
double vector[6] = {0};
///////////////////////////////////////////////////////////
void matrix_calculate(int numRows, int numCols){
    //Функция для расчета матрицы по формуле
    for (int row = 0; row < numRows; ++row) {
         for (int col = 0; col < numCols; ++col) {
             if (row == 0 and col == 0){
                 /*
                 /В формуле была ошибка. При посдстанновке нулевого индекса первого столбца и первого ряда,
                 /Было явное деление на 0, что приводило к ошибке.
                 /Поэтому пришлось присвоить этому элементу значение 0.
                */
                 matrix_a[0][0] = "0";
                 continue;
             }
                expression = pow(3.5, 2 * row) * std::abs(row - 3 * col) + ((2 + col) / (row + col));
                QString s = QString::number(expression);
                matrix_a[row][col] = s;
            }
     }
}

void vector_calculate(){
    //Функция для расчета вектора по заданой матрицы
    double res = 0;
    matrix_calculate(6, 7);
        for(int i = 0; i < 6; ++i){
            for(int j = 0; j < 7; ++j){
                if(j % 2 == 0){

                    res += pow(matrix_a[i][j].toDouble(), 2);
                    vector[i] = res;
                }
            }
        }

}

long double func_calculate(const double vec[6]){
    //Функция расчета функции по заданному вектору
    double G = 0;
    double sig = 0;

    for(int i = 0; i < 6; i++){
        double temp1 = 0;
        double temp2 = 0;

        for(int j = 0; j < i; j++){
            temp1 *= i + vec[j];
        }
        temp2 = temp1 / (1 + vec[i]);
        sig = pow(temp2, 2);
    }
    G = log(fabs(5-sig));
    return G;
}

void Menu_window::on_pushButton_2_clicked()
{
    //Подготовка слоя для отображения данных
    this->setWindowTitle("MATRIX");
    clearLayout(ui->horizontalLayout_3);
    ui->horizontalLayoutWidget->close();
    ui->gridLayoutWidget->show();
    ui->label_2->setStyleSheet("background-color: rgb(50, 0, 75);");
    ui->label_2->setText("");

    MsgBox_matrix();
    //Задаем размер матрицы
    const int numRows = 6;
    const int numCols = 7;

    matrix_calculate(6, 7);

    //Вывод матрицы на экран
     for (int i=0; i<numRows; ++i) {
       for (int j=0; j<numCols; ++j) {

         QPushButton *btn = new QPushButton(matrix_a[i][j], this);
         btn->setStyleSheet("border: 1px solid transparent;text-align: center;"
                            "color:rgba(255,255,255,255);"
                            "border-radius: 8px;"
                            "border-width: 3px;"
                            "border-image: 9,2,5,2; "
                            "background-position: top left;"
                            "background-origin: content;"
                            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(200, 110, 100, 200), stop:1 rgba(130, 148, 130, 200));}"
                            "QPushButton::chunk {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgba(255,200,0,255), stop: 1 rgba(255,0,0,255));}"
                            "QPushButton{border-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 200, 200, 200), stop:1 rgba(255, 200, 200, 200));}");

         btn->setFixedSize(85, 40);
         ui->gridLayout->addWidget(btn, i, j);
       }
      }

    clearLayout(ui->horizontalLayout_2);
    ui->pushButton_2->setDisabled(1);
    ui->pushButton_3->setDisabled(0);
    ui->pushButton->setDisabled(0);
    ui->pushButton_7->setDisabled(0);
}

void Menu_window::on_pushButton_3_clicked()
{
    //Подготовка слоя для отображения данных
    this->setWindowTitle("VECTOR");
    ui->label_2->setText("");
    ui->gridLayoutWidget->close();
    ui->horizontalLayoutWidget->show();
    ui->label_2->setStyleSheet("background-color: rgb(50, 0, 75);");

    MsgBox_vector();

    vector_calculate();
    //Вывод вектора на экран
    for(int vec = 0; vec < 6; vec++){
        QPushButton *btn = new QPushButton(QString::number(vector[vec]) + "\nX[" + QString::number(vec) + "]", this);

        btn->setStyleSheet("border: 1px solid transparent;text-align: center;"
                            "color:rgba(255,255,255,255);"
                            "border-radius: 8px;"
                            "border-width: 3px;"
                            "border-image: 9,2,5,2; "
                            "background-position: top left;"
                            "background-origin: content;"
                            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(200, 110, 100, 200), stop:1 rgba(130, 148, 130, 200));}"
                            "QPushButton::chunk {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgba(255,200,0,255), stop: 1 rgba(255,0,0,255));}"
                            "QPushButton{border-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 200, 200, 200), stop:1 rgba(255, 200, 200, 200));}");


        btn->setFixedSize(85, 40);
        ui->horizontalLayout_2->addWidget(btn);
    }
    ui->pushButton_3->setDisabled(1);
    ui->pushButton_2->setDisabled(0);
    ui->pushButton->setDisabled(0);
    ui->pushButton_7->setDisabled(0);
    clearLayout(ui->gridLayout);
    clearLayout(ui->horizontalLayout_3);

}

void Menu_window::on_pushButton_7_clicked()
{
    //Подготовка слоя для отображения данных
    this->setWindowTitle("FUNCTION");
    ui->label_2->setText("");
    ui->label_2->setStyleSheet("background-color: rgb(50, 0, 75);");
    ui->gridLayoutWidget->close();
    ui->horizontalLayoutWidget->close();
    MsgBox_function();

    double G = func_calculate(vector);

    QPushButton *btn = new QPushButton(QString::number(G), this);
    //Вывод функции на экран
    btn->setStyleSheet("border: 1px solid transparent;text-align: center;"
                        "color:rgba(255,255,255,255);"
                        "border-radius: 8px;"
                        "border-width: 3px;"
                        "border-image: 9,2,5,2; "
                        "background-position: top left;"
                        "background-origin: content;"
                        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(200, 110, 100, 200), stop:1 rgba(130, 148, 130, 200));}"
                        "QPushButton::chunk {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgba(255,200,0,255), stop: 1 rgba(255,0,0,255));}"
                        "QPushButton{border-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 200, 200, 200), stop:1 rgba(255, 200, 200, 200));}");


    btn->setFixedSize(85, 40);
    ui->horizontalLayout_3->addWidget(btn);
    ui->pushButton_3->setDisabled(0);
    ui->pushButton_2->setDisabled(0);
    ui->pushButton->setDisabled(0);
    ui->pushButton_7->setDisabled(1);
    clearLayout(ui->gridLayout);
    clearLayout(ui->horizontalLayout_2);


}

void Menu_window::on_pushButton_6_clicked()
{
    //Запуск внешней программы
    QProcess* process;
    QDir directory;
    QString path = directory.currentPath();

    process->QProcess::startDetached(path + "\\rdr3.exe");
}
