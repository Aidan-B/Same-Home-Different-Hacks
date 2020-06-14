#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPushButton;
class QProgressBar;
class QTimer;
class QLabel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void slotIncrementTimer();
    void slotStartButtonHanlder(bool checked);
    void slotResetButtonHanlder();

private:
    QPushButton *startButton;
    QPushButton *resetButton;
    QProgressBar *progressBar;
    QLabel *status;
    QTimer *timer;

    void updateProgressBar();
    void startTimer();
    void stopTimer();

    int timeRemaining;
    int totalTime;

    unsigned int period;
    QString periodType;

    const int BREAK_LENGTH = 300; //5 minutes
    const int LONG_BREAK_LENGTH = 900; //15 mintues
    const int FOCUS_LENGTH = 1500; //25 minutes
};
#endif // MAINWINDOW_H
//“Sound effects obtained from https://www.zapsplat.com“
