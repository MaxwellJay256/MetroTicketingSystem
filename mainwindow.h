#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QTimer>
#include <QLabel>
#include "Station.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QLabel* lbDateTimeDisplay;
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString fareListName = ":/docs/resources/FareList.csv";
    QList<Station> stations;

private slots:
    void on_btnStart_Welcome_clicked();

    /// @brief 更新状态栏时间
    void updateDateTime();

    void on_btnReturn_MainMenu_clicked();

    void on_btnGoToPurchase_clicked();

    void on_btnGoToMap_clicked();

    void on_actReturnHome_triggered();

    void on_btnNext_RouteSelect_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
