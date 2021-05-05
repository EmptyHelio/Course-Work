#ifndef MENU_WINDOW_H
#define MENU_WINDOW_H

#include <QDialog>
namespace Ui {
class Menu_window;
}

class Menu_window : public QDialog
{
    Q_OBJECT

public:
    explicit Menu_window(QWidget *parent = nullptr);
    ~Menu_window();
    //Ui::Menu_window *ui;

signals:
    void firstWindow();

private slots:


    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::Menu_window *ui;
};

#endif // MENU_WINDOW_H
