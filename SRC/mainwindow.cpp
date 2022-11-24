#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton->setProperty("cssClass","button-test");
    ui->label->setProperty("cssClass","label-test");

    DirCSS.setPath(QDir::currentPath()+"/../css");
    L_CSS_Files = DirCSS.entryList(QStringList() << "*.css");
    for (int i = 0; i < L_CSS_Files.count(); i++)
    {
        ui->comboBox->addItem(QFileInfo(L_CSS_Files.at(i)).baseName());
    }
    on_comboBox_activated(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBox_activated(int index)
{
    QFile FileStyle(DirCSS.canonicalPath()+QDir::separator()+L_CSS_Files.at(index));
    FileStyle.open(QIODevice::ReadOnly);
    if (FileStyle.isOpen() == true)
    {
        qApp->setStyleSheet(FileStyle.readAll());
        FileStyle.close();
    }
}
