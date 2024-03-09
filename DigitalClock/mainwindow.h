#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QDateTime>
#include <QFont>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateClockTwentyFor();
    void updateClockTwelve();
    void toggleClock();
    void toggleStopwatch();
    void updateStopwatch();

private:
    QLabel      *m_digitalClock;
    QTimer      *m_timer;
    QPushButton *m_switchButton;
    QPushButton *m_stopwatchButton;
    bool        stopwatchRunning;
    bool        flag;
    QTime       m_stopwatchStartTime;
};
#endif // MAINWINDOW_H
