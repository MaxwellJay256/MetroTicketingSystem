#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tBtnExit_Welcome->setDefaultAction(ui->actExit);
    ui->tBtnExit_MainMenu->setDefaultAction(ui->actExit);
    ui->tBtnHome_RouteSelect->setDefaultAction(ui->actReturnHome);
    ui->tBtnHome_Checkout->setDefaultAction(ui->actReturnHome);
    ui->tBtnHome_FinishPurchase->setDefaultAction(ui->actReturnHome);

    stations = readStation(fareListName); //读取 FareList.csv，保存所有地铁站

    //状态栏显示日期时间
    lbDateTimeDisplay = new QLabel(this);
    QTimer* timer = new QTimer(this);
    timer->setTimerType(Qt::VeryCoarseTimer);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateDateTime);
    timer->start(1000);
    ui->statusbar->addPermanentWidget(lbDateTimeDisplay);

    //页面初始化
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
    ui->stackedWidget_Payments->setCurrentWidget(ui->page_WaitAction);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btnStart_Welcome_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->pageMainMenu);
}

void MainWindow::updateDateTime() {
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateTimeString = dateTime.toString("yyyy/MM/dd hh:mm:ss"); //格式化日期时间字符串
    lbDateTimeDisplay->setText(dateTimeString); //更新标签文本
}

void MainWindow::on_btnReturn_MainMenu_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
}

void MainWindow::on_btnGoToPurchase_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->pageRouteSelect);
}

void MainWindow::on_btnGoToMap_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->pageStationQuery);
}

void MainWindow::on_actReturnHome_triggered() {
    ui->stackedWidget->setCurrentWidget(ui->pageMainMenu);
}

void MainWindow::on_btnNext_RouteSelect_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->pageCheckout);
}
