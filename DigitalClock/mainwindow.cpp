#include "mainwindow.h"
#include <QTime>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    m_digitalClock{new QLabel},
    m_timer{new QTimer},
    m_switchButton{new QPushButton("toggleClock")},
    m_stopwatchButton{new QPushButton("Start Stopwatch")},
    flag{true},
    stopwatchRunning{false},
    m_stopwatchStartTime{},
    mainLayout{new QVBoxLayout(this)}
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

    mainLayout->addWidget(m_digitalClock, Qt::AlignCenter);
    mainLayout->addWidget(m_switchButton, Qt::AlignCenter);
    mainLayout->addWidget(m_stopwatchButton, Qt::AlignCenter);

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

        QString str = "total time:  " + m_digitalClock->text();
        m_stopwatchButton->setText(str);

        QLabel* stopTime = new QLabel(str, this);
        QFont font = stopTime->font();
        font.setPointSize(15);
        stopTime->setFont(font);
        stopTime->setAlignment(Qt::AlignCenter);

        QPushButton* DeletestopTimeLayout = new QPushButton("Delete",this);
        connect(DeletestopTimeLayout, &QPushButton::clicked, this, &MainWindow::deleteStopTimeLayout);

        QHBoxLayout* stopTimeLayout = new QHBoxLayout(this);
        stopTimeLayout->addWidget(stopTime);
        stopTimeLayout->addWidget(DeletestopTimeLayout);
        stopTimeLayout->setAlignment(DeletestopTimeLayout, Qt::AlignRight);

        mainLayout->insertLayout(1, stopTimeLayout);

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

void MainWindow::deleteStopTimeLayout()
{
    QPushButton *senderButton = qobject_cast<QPushButton*>(sender());
    if (!senderButton)
    {
        return;
    }

    QLayout *parentLayout = nullptr;
    for (auto item : mainLayout->children()) {
        if (QHBoxLayout *layoutItem = qobject_cast<QHBoxLayout*>(item)) {
            if (layoutItem->indexOf(senderButton) != -1) {
                parentLayout = layoutItem;
                break;
            }
        }
    }

    if (!parentLayout)
    {
        return;
    }

    mainLayout->removeItem(parentLayout);

    QLayoutItem *child;
    while ((child = parentLayout->takeAt(0)) != nullptr) {
        if (QWidget *widget = child->widget())
        {
            widget->deleteLater();
        }
        delete child;
    }

    delete parentLayout;
}



