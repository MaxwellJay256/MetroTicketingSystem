#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QTimer>
#include <QLabel>
#include <QScrollArea>
#include <QRadioButton>
#include <QStringListModel>
#include <QImageReader>
#include <QPalette>
#include "Station.h"
#include "Line.h"
#include "Order.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QLabel* lbDateTimeDisplay;
    QPixmap map_RouteSelect;
    QSize frameSize_RouteSelect;
    QPixmap map_MainMenu;
    QSize frameSize_MainMenu;
    void DisplayMap(QString mapFileName, QPixmap* pixmap, QScrollArea* scrollArea, QLabel* lbMap);

    // InfoBar
    enum infoType {
        info = 1,
        warning = 2,
        error = 3,
    };
    QLabel* lbInfo;
    void InfoBarSetUp();
    void SetInfoType(infoType type);
    void InfoBarClear();
    void UpdateInfo(QString info, infoType type);

    void UpdateTotalPrice();

    QTimer *countDownTimer;
    int countDownSeconds;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString stationListName = ":docs/resources/StationList.csv";
    QString fareListName = ":docs/resources/FareList.csv";
    QString mainMapFileName = ":/maps/resources/maps/MetroMap.jpg";

    Order *order;

private slots:
    void on_btnStart_Welcome_clicked();
    void on_actReturnHome_triggered();
    /// @brief 更新日期时间
    void updateDateTime();

    void on_btnReturn_MainMenu_clicked();
    void on_btnGoToMap_clicked();
    void on_btnGoToPurchase_MainMenu_clicked();
    void on_btnNext_RouteSelect_clicked();
    void on_btnReturn_Checkout_clicked();
    void on_btnGoToPurchase_StationQuery_clicked();

    void on_radioLine_clicked();
    void on_radioMap_clicked();

    void on_listView_Start_RouteSelect_clicked(const QModelIndex &index);
    void on_listView_Destination_RouteSelect_clicked(const QModelIndex &index);

    void on_lineEdit_Start_RouteSelect_textChanged(const QString &arg1);
    void on_lineEdit_Destination_RouteSelect_textChanged(const QString &arg1);

    void SetNumOfTickets_btn();
    void on_spinBox_NumOfTickets_valueChanged(int arg1);

    void on_btn_Cash_clicked();
    void on_btn_WeChatPay_clicked();
    void on_btn_AliPay_clicked();
    void on_btn_DCEP_clicked();

    void InsertCash();
    void on_price_or_cash_changed();

    void on_btn_FinishPay_clicked();
    void CountDown_FinishPay();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
