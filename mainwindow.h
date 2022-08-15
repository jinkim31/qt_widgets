#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDockWidget>
#include <QTimer>
#include "widget/timeline/timeline.h"
#include "widget/dockwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actiontimeline_triggered();

private:
    Ui::MainWindow *ui;
    QLabel label;
    QTimer timer;
    DockWidget<Timeline> dockWidget;
};
#endif // MAINWINDOW_H
