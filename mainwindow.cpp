#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    addDockWidget(Qt::BottomDockWidgetArea, &dockWidget);

    connect(&timer, &QTimer::timeout, this, [&](){
        static int i=0;
        dockWidget.widget()->markEvent("event 1", std::chrono::system_clock::now());
        dockWidget.widget()->markEvent("event 2", std::chrono::system_clock::now());
        dockWidget.widget()->markEvent("event 3", std::chrono::system_clock::now());

    });

    timer.start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actiontimeline_triggered()
{

}

