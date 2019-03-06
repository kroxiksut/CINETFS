#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"
#include "ui_about.h"
#include <QDir>
#include <QFileInfoList>
#include <QString>
#include <QDebug>
#include <vector>
#include <random>
#include <time.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);

}

void MainWindow::traverse(const QString &pattern, const QString &dirname, int level)
{
    QDir dir(dirname);
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);

    static const QStringList stringList = pattern.split('/');
    foreach (QFileInfo fileInfo, dir.entryInfoList(stringList.mid(level, 1))) {
        if (fileInfo.isDir() && fileInfo.isReadable())
            traverse(pattern, fileInfo.filePath(), level+1);
        else if (stringList.size() == (level + 1)) {
//            pth
            pth.push_back(fileInfo.filePath());


//            qDebug() << fileInfo.filePath();
        }
    }

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    ui->lbl_descr->clear();
    //qsrand(qrand());
    srand (time(NULL));
    MyRand = rand() % ((pth.size() - 1));
    //qDebug() << pth.at(MyRand) << " - " << MyRand;
    QImage *img;
    img = new QImage();
    img->load(pth.at(MyRand));
    ui->ImgLabel->setPixmap(QPixmap::fromImage(img->scaled(
                                                   ui->ImgLabel->geometry().width(),
                                                   ui->ImgLabel->geometry().height(), Qt::IgnoreAspectRatio)));
    delete img;
    ui->pushButton_2->setEnabled(true);




}

unsigned int MainWindow::getNumberFPath(unsigned int V)
{
    QString str = pth.at(V);
    return str.split('/').at(1).toInt();
}

void MainWindow::on_pushButton_2_clicked()
{
    unsigned int var = getNumberFPath(MyRand);
    unsigned int rb;
    if (ui->radioButton->isChecked()) {
        rb = 1;
    } else if (ui->radioButton_2->isChecked()) {
        rb =2;
    } else  {
        rb = 3;
    }

    if (rb == var) {
        cinTrue+=1;
        ui->lbl_true->setText("Правильных ответов - " + QString::number(cinTrue));
    } else {
        cinFalse +=1;
        ui->lbl_false->setText("Неправильных ответов - " + QString::number(cinFalse));
    }
    ui->lbl_descr->setText("<<<----- это CIN"+QString::number(var));
    ui->pushButton_2->setEnabled(false);

}

void MainWindow::on_pushButton_3_clicked()
{
    pth.clear();
    traverse("*/*", "cin", 0);
    ui->pushButton->setEnabled(true);
    ui->pushButton->click();
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
    cinTrue = 0;
    cinFalse = 0;
    cnt=0;

}

void MainWindow::on_pushButton_4_clicked()
{
    About* ab = new About();
    ab->show();
}
