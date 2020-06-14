#include "mainwindow.h"
#include <QPushButton>
#include <QProgressBar>
#include <QTimer>
#include <QLabel>
#include <QString>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    /* Set up UI */
    setFixedSize(250,100);
    int padding = 5;
    startButton = new QPushButton("Start", this);
    startButton->setCheckable(true);
    startButton->move(
                this->width() - (startButton->width() + padding),
                this->height() - (startButton->height() + padding)
                );
    resetButton = new QPushButton("Reset", this);
    resetButton->move(
                this->width() - (startButton->width() + resetButton->width() + 2*padding),
                this->height() - (resetButton->height() + padding)
                );
    progressBar = new QProgressBar(this);
    progressBar->setGeometry(padding, 20 + padding, this->width() - 2*padding, 15);

    status = new QLabel("Paused", this);
    status->setText("Press start to begin");
    status->setGeometry(padding, padding, this->width()-2*padding, 20);

    /* Set up timers and connect slots */
    timer = new QTimer(this);
    period = 1;
    periodType = "Focus";
    timeRemaining = FOCUS_LENGTH;
    progressBar->setRange(0, timeRemaining);

    connect(timer, SIGNAL (timeout()), this, SLOT (slotIncrementTimer()));
    connect(startButton, SIGNAL (clicked(bool)), this, SLOT (slotStartButtonHanlder(bool)));
    connect(resetButton, SIGNAL (clicked()), this, SLOT (slotResetButtonHanlder()));
}

void MainWindow::slotIncrementTimer() {
    timeRemaining--;
    status->setText(periodType + " - " + QString::number(timeRemaining) + "s remaining");

    if (timeRemaining <= 0) {
        period++;
        if (period % 2 == 0) {
            if (period % 8 == 0) {
                timeRemaining = LONG_BREAK_LENGTH;
                periodType = "Long Break";
            } else {
                timeRemaining = BREAK_LENGTH;
                periodType = "Short Break";
            }
        } else {
            timeRemaining = FOCUS_LENGTH;
            periodType = "Focus";
        }
        progressBar->setRange(0, timeRemaining);
    }
    updateProgressBar();
    return;
}

void MainWindow::startTimer() {
    timer->start(10);
}

void MainWindow::stopTimer() {
    timer->stop();
    status->setText("Paused - " + QString::number(timeRemaining) + "s remaining");
}

void MainWindow::slotStartButtonHanlder(bool checked) {

    if (checked) {
        startButton->setText("Pause");
        startTimer();
    } else {
        startButton->setText("Start");
        stopTimer();
    }

}

void MainWindow::slotResetButtonHanlder( ){
    period = 1;
    periodType = "Focus";
    timeRemaining = FOCUS_LENGTH;
    startButton->setChecked(false);
    progressBar->setRange(0, timeRemaining);
    updateProgressBar();
    slotStartButtonHanlder(false);
    status->setText("Press start to begin");

}

void MainWindow::updateProgressBar() {
    progressBar->setValue(timeRemaining);
}
