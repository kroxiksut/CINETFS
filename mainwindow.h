#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QImage>

#include <vector>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    vector <QString> pth;
    QImage *myimg;
    unsigned int MyRand;
    unsigned int cinTrue;
    unsigned int cinFalse;
    unsigned int cnt;
    unsigned int getNumberFPath(unsigned int V);
    void traverse(const QString &pattern, const QString &dirname, int level);

};

#endif // MAINWINDOW_H
