#include "timeline.h"
#include "ui_timeline.h"
#include <QTimer>
#include <QDebug>

Timeline::Timeline(QWidget *parent) : QWidget(parent), ui(new Ui::Timeline)
{
    ui->setupUi(this);

    isRunning = false;

    ui->chart->chart()->legend()->setReverseMarkers(true);
    xAxis.setTickType(QValueAxis::TicksDynamic);
    yAxis.setTickType(QValueAxis::TicksDynamic);
    yAxis.hide();
    ui->chart->chart()->addAxis(&xAxis, Qt::AlignBottom);
    ui->chart->chart()->addAxis(&yAxis, Qt::AlignLeft);
    ui->chart->chart()->legend()->setAlignment(Qt::AlignLeft);
}

Timeline::~Timeline()
{
    delete ui;
}

void Timeline::addEvent(const QString &name)
{
    data.insert({name, std::vector<double>()});
}

void Timeline::markEvent(const QString &eventName, const Timestamp &timestamp)
{
    if(!isRunning) return;

    // if key doesn't exist
    if(data.find(eventName) == data.end())
    {
        addEvent(eventName);
    }

    // append to series
    double duration = std::chrono::duration_cast<std::chrono::milliseconds>((timestamp - startTime)).count();
    data[eventName].push_back(duration);
}

void Timeline::on_btnTest_clicked()
{
    if(isRunning) return;

    // remove sereis
    ui->chart->chart()->removeAllSeries();

    // reset data
    data.clear();
    startTime = std::chrono::system_clock::now();

    isRunning = true;

    // plot after QTimer singleshot
    QTimer::singleShot(ui->sboxDuration->value(), [&](){
        isRunning = false;

        // set axis
        xAxis.setTickInterval(ui->sboxScale->value());
        xAxis.setRange(0, ui->sboxDuration->value());
        yAxis.setTickInterval(1);
        yAxis.setRange(0, data.size()+1);

        // add series
        int i=1;
        for (const auto & [name, vector] : data)
        {
            QScatterSeries* series = new QScatterSeries();
            for(double duration : vector)series->append(QPointF(duration, i));
            double freq = double(vector.size()) / ui->sboxDuration->value()*1000;
            series->setName(name + " (" + QString::number(freq) + "Hz)");
            series->setMarkerSize(10);

            ui->chart->chart()->addSeries(series);
            series->attachAxis(&xAxis);
            series->attachAxis(&yAxis);

            i++;
        }
    });
}

