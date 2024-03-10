#include "mainwindow.h"
#include <QVBoxLayout>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    m_digitalClock{new QLabel},
    m_timer{new QTimer},
    m_switchButton{new QPushButton("toggleClock")},
    m_stopwatchButton{new QPushButton("Start Stopwatch")},
    flag{true},
    stopwatchRunning{false},
    m_stopwatchStartTime{}
{

    m_switchButton->setStyleSheet("QPushButton {"
                                  "   background-color: #4CAF50;"
                                  "   border: 1px solid #4CAF50;"
                                  "   color: white;"
                                  "   padding: 8px 16px;"
                                  "   text-align: center;"
                                  "   text-decoration: none;"
                                  "   display: inline-block;"
                                  "   font-size: 16px;"
                                  "   margin: 4px 2px;"
                                  "   transition-duration: 0.4s;"
                                  "   cursor: pointer;"
                                  "   border-radius: 5px;"
                                  "}"
                                  "QPushButton:hover {"
                                  "   background-color: white;"
                                  "   color: black;"
                                  "   cursor: pointer;"
                                  "}");

    m_stopwatchButton->setStyleSheet("QPushButton {"
                        "   background-color: #4CAF50;"
                        "   border: 1px solid #4CAF50;"
                        "   color: white;"
                        "   padding: 8px 16px;"
                        "   text-align: center;"
                        "   text-decoration: none;"
                        "   display: inline-block;"
                        "   font-size: 16px;"
                        "   margin: 4px 2px;"
                        "   transition-duration: 0.4s;"
                        "   cursor: pointer;"
                        "   border-radius: 5px;"
                        "}"
                        "QPushButton:hover {"
                        "   background-color: white;"
                        "   color: black;"
                        "}");


    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_digitalClock);
    mainLayout->addWidget(m_switchButton);
    mainLayout->addWidget(m_stopwatchButton);

    m_digitalClock->setAlignment(Qt::AlignCenter);

    QFont font = m_digitalClock->font();
    font.setPointSize(72);
    font.setBold(true);
    m_digitalClock->setFont(font);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(m_switchButton, &QPushButton::clicked, this,  &MainWindow::toggleClock);
    connect(m_stopwatchButton, &QPushButton::clicked, this, &MainWindow::toggleStopwatch);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::updateClockTwentyFor);


    m_timer->start(60);
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateClockTwentyFor()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString timeString = currentTime.toString("hh:mm:ss  ap");

    m_digitalClock->setText(timeString);
}

void MainWindow::updateClockTwelve()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString timeString = currentTime.toString("HH:MM:ss");

    m_digitalClock->setText(timeString);
}

void MainWindow::toggleClock()
{
    flag = !flag;
    if (flag)
    {
        connect(m_timer, &QTimer::timeout, this, &MainWindow::updateClockTwentyFor);
    }
    else
    {
        connect(m_timer, &QTimer::timeout, this, &MainWindow::updateClockTwelve);
    }
}

void MainWindow::toggleStopwatch()
{
    stopwatchRunning = !stopwatchRunning;

    if (stopwatchRunning)
    {
        m_stopwatchStartTime = QTime::currentTime();
        connect(m_timer, &QTimer::timeout, this, &MainWindow::updateStopwatch);

        m_stopwatchButton->setText("Stop Stopwatch");
        m_switchButton->setEnabled(false);
        m_stopwatchButton->setStyleSheet("QPushButton {"
                            "   background-color: #FF0000;"
                            "   border: 1px solid #FF0000;"
                            "   color: white;"
                            "   padding: 8px 16px;"
                            "   text-align: center;"
                            "   text-decoration: none;"
                            "   display: inline-block;"
                            "   font-size: 16px;"
                            "   margin: 4px 2px;"
                            "   transition-duration: 0.4s;"
                            "   cursor: pointer;"
                            "   border-radius: 5px;"
                            "}"
                            "QPushButton:hover {"
                            "   background-color: white;"
                            "   color: black;"
                            "}");
    }
    else
    {
        disconnect(m_timer, &QTimer::timeout, this, &MainWindow::updateStopwatch);
        m_switchButton->setEnabled(true);

        QString str = "Start Stopwatch";
        str += "\ntotal time:  " + m_digitalClock->text();
        m_stopwatchButton->setText(str);

        m_stopwatchButton->setStyleSheet("QPushButton {"
                            "   background-color: #4CAF50;"
                            "   border: 1px solid #4CAF50;"
                            "   color: white;"
                            "   padding: 8px 16px;"
                            "   text-align: center;"
                            "   text-decoration: none;"
                            "   display: inline-block;"
                            "   font-size: 16px;"
                            "   margin: 4px 2px;"
                            "   transition-duration: 0.4s;"
                            "   cursor: pointer;"
                            "   border-radius: 5px;"
                            "}"
                            "QPushButton:hover {"
                            "   background-color: white;"
                            "   color: black;"
                            "}");
    }
}

void MainWindow::updateStopwatch()
{
    QTime currentTime = QTime::currentTime();
    int elapsedMilliseconds = m_stopwatchStartTime.msecsTo(currentTime);

    QTime elapsedTime = QTime(0, 0).addMSecs(elapsedMilliseconds);

    QString timeString = elapsedTime.toString("hh:mm:ss:zzz");

    m_digitalClock->setText(timeString);
}

