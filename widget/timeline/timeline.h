#ifndef TIMELINE_H
#define TIMELINE_H

#include <QWidget>
#include <chrono>
#include <memory>
#include <map>
#include <QChart>
#include <QScatterSeries>
#include <QValueAxis>

namespace Ui {
class Timeline;
}

class Timeline : public QWidget
{
    Q_OBJECT

public:
    using Timestamp = std::chrono::time_point<std::chrono::system_clock>;
    explicit Timeline(QWidget *parent = nullptr);
    ~Timeline();

public slots:
    void addEvent(const QString& name);
    void markEvent(const QString& eventName,const Timestamp& timestamp);


private slots:
    void on_btnTest_clicked();


private:
    Ui::Timeline *ui;
    Timestamp startTime;
    std::map<QString, std::vector<double>> data;
    QValueAxis xAxis, yAxis;
    bool isRunning;
};

#endif // TIMELINE_H
