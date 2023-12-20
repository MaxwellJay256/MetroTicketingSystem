#include "mainwindow.h"
#include "ui_mainwindow.h"

#define IMAGE_MB_LIMIT 250

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
    ui->tBtnHome_StationQuery->setDefaultAction(ui->actReturnHome);

    connect(ui->radioLine1, &QRadioButton::clicked, this, &MainWindow::on_radioLine_clicked);
    connect(ui->radioLine2, &QRadioButton::clicked, this, &MainWindow::on_radioLine_clicked);
    connect(ui->radioLine3, &QRadioButton::clicked, this, &MainWindow::on_radioLine_clicked);
    connect(ui->radioLine4, &QRadioButton::clicked, this, &MainWindow::on_radioLine_clicked);
    connect(ui->radioLine5, &QRadioButton::clicked, this, &MainWindow::on_radioLine_clicked);
    connect(ui->radioLine6, &QRadioButton::clicked, this, &MainWindow::on_radioLine_clicked);
    connect(ui->radioLine61, &QRadioButton::clicked, this, &MainWindow::on_radioLine_clicked);
    connect(ui->radioLine7, &QRadioButton::clicked, this, &MainWindow::on_radioLine_clicked);
    connect(ui->radioLine8, &QRadioButton::clicked, this, &MainWindow::on_radioLine_clicked);
    connect(ui->radioLine9, &QRadioButton::clicked, this, &MainWindow::on_radioLine_clicked);
    connect(ui->radioLine10, &QRadioButton::clicked, this, &MainWindow::on_radioLine_clicked);
    connect(ui->radioLine11, &QRadioButton::clicked, this, &MainWindow::on_radioLine_clicked);
    connect(ui->radioLine12, &QRadioButton::clicked, this, &MainWindow::on_radioLine_clicked);
    connect(ui->radioLine14, &QRadioButton::clicked, this, &MainWindow::on_radioLine_clicked);
    connect(ui->radioLine16, &QRadioButton::clicked, this, &MainWindow::on_radioLine_clicked);
    connect(ui->radioLine20, &QRadioButton::clicked, this, &MainWindow::on_radioLine_clicked);
    
    frameSize_RouteSelect = ui->scrollArea_Map_RouteSelect->size();
    qDebug() << frameSize_RouteSelect;

    //stationList = readStation(stationListName); //读取 StationList.csv，保存所有地铁站
    ReadStationInfo(stationListName);
    ReadFareData(fareListName, fareMap);
    order = nullptr;

    //状态栏显示日期时间
    lbDateTimeDisplay = new QLabel(this);
    QTimer* timer = new QTimer(this);
    timer->setTimerType(Qt::VeryCoarseTimer);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateDateTime);
    timer->start(1000);
    ui->statusbar->addPermanentWidget(lbDateTimeDisplay);

    // 状态栏添加信息标签
    InfoBarSetUp();

    //页面初始化
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
    ui->stackedWidget_Payments->setCurrentWidget(ui->page_WaitAction);
    QImageReader::setAllocationLimit(IMAGE_MB_LIMIT);

    // 选择购票张数按钮
    connect(ui->btn_1t, &QPushButton::clicked, this, &MainWindow::SetNumOfTickets_btn);
    connect(ui->btn_2t, &QPushButton::clicked, this, &MainWindow::SetNumOfTickets_btn);
    connect(ui->btn_3t, &QPushButton::clicked, this, &MainWindow::SetNumOfTickets_btn);
    connect(ui->btn_4t, &QPushButton::clicked, this, &MainWindow::SetNumOfTickets_btn);
    connect(ui->btn_5t, &QPushButton::clicked, this, &MainWindow::SetNumOfTickets_btn);
    connect(ui->btn_6t, &QPushButton::clicked, this, &MainWindow::SetNumOfTickets_btn);
    connect(ui->btn_7t, &QPushButton::clicked, this, &MainWindow::SetNumOfTickets_btn);
    connect(ui->btn_8t, &QPushButton::clicked, this, &MainWindow::SetNumOfTickets_btn);

    // 投币按钮
    connect(ui->btn_01yuan, &QPushButton::clicked, this, &MainWindow::InsertCash);
    connect(ui->btn_05yuan, &QPushButton::clicked, this, &MainWindow::InsertCash);
    connect(ui->btn_10yuan, &QPushButton::clicked, this, &MainWindow::InsertCash);
    connect(ui->btn_20yuan, &QPushButton::clicked, this, &MainWindow::InsertCash);

    // 选择支付方式
    connect(ui->spinBox_TotalPrice_Cash, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::on_price_or_cash_changed);
    connect(ui->spinBox_CashInserted, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::on_price_or_cash_changed);

    connect(ui->btn_FinishPay_Cash, &QPushButton::clicked, this, &MainWindow::on_btn_FinishPay_clicked);
    connect(ui->btnFinishPay_EPayment, &QPushButton::clicked, this, &MainWindow::on_btn_FinishPay_clicked);
    // 完成支付页面的倒计时
    countDownTimer = new QTimer(this);
    countDownTimer->setTimerType(Qt::VeryCoarseTimer);
    connect(countDownTimer, &QTimer::timeout, this, &MainWindow::CountDown_FinishPay);
    countDownSeconds = 10;
    ui->label_AutoHomeCountDown->setText(QString::number(countDownSeconds) + "s 后自动返回主菜单");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btnStart_Welcome_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->pageMainMenu);
    DisplayMap(mainMapFileName, &map_MainMenu, ui->scrollArea_Map_MainMenu, ui->label_Map_MainMenu);
    InfoBarClear();
}
void MainWindow::DisplayMap(QString mapFileName, QPixmap* pixmap, QScrollArea* scrollArea, QLabel* lbMap)
{
    pixmap->load(mapFileName);
    *pixmap = pixmap->scaled(scrollArea->width()-30, scrollArea->height()-30,  Qt::KeepAspectRatio);
    lbMap->setPixmap(*pixmap);
}

void MainWindow::updateDateTime() {
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateTimeString = dateTime.toString("yyyy/MM/dd hh:mm:ss"); //格式化日期时间字符串
    lbDateTimeDisplay->setText(dateTimeString); //更新标签文本
}

void MainWindow::on_btnReturn_MainMenu_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->pageWelcome);
    InfoBarClear();
}

void MainWindow::on_actReturnHome_triggered() {
    ui->stackedWidget->setCurrentWidget(ui->pageMainMenu);
    ui->spinBox_CashInserted->setValue(0);
    if (order != nullptr) {
        delete order;
        order = nullptr;
    }
    InfoBarClear();
}

void MainWindow::on_btnNext_RouteSelect_clicked() {
    if (ui->lineEdit_Start_RouteSelect->text().isEmpty() || ui->lineEdit_Destination_RouteSelect->text().isEmpty()) {
        qDebug() << "Error: Start or destination not selected yet.";
        UpdateInfo("错误：起点站或终点站未选择", error);
        return;
    }

    QList<Station*> startStationList = FindStationsByName(ui->lineEdit_Start_RouteSelect->text());
    QList<Station*> destinationStationList = FindStationsByName(ui->lineEdit_Destination_RouteSelect->text());
    if (startStationList.isEmpty()) {
        qDebug() << "Error: Start station not found.";
        UpdateInfo("错误：起点站不存在，请检查起点站输入是否正确", error);
        return;
    }
    if (destinationStationList.isEmpty()) {
        qDebug() << "Error: Destination station not found.";
        UpdateInfo("错误：终点站不存在，请检查终点站输入是否正确", error);
        return;
    }

    order = new Order();
    order->SetStartStation(startStationList.first());
    order->SetDestinationStation(destinationStationList.first());
    order->GetUnitPrice(fareMap);
    ui->stackedWidget->setCurrentWidget(ui->pageCheckout);
    ui->spinBox_UnitPrice->setValue(order->unitPrice);
    order->GetTotalPrice();
    UpdateTotalPrice();
    InfoBarClear();
}

void MainWindow::on_btnReturn_Checkout_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageRouteSelect);
}

void MainWindow::on_btnGoToPurchase_StationQuery_clicked()
{
    on_btnGoToPurchase_MainMenu_clicked();
}

void MainWindow::on_radioLine_clicked()
{
    int lineNo = qobject_cast<QRadioButton*>(QObject::sender())->
        objectName().mid(QString("radioLine").length()).toInt();
    Line* line = FindLineByNumber(lineNo);
    DisplayMap(line->mapFileName, &map_RouteSelect, ui->scrollArea_Map_RouteSelect, ui->label_Map_RouteSelect);

    // 为 listView_Start_RouteSelect 和 listView_Destination_RouteSelect 添加 line 下的地铁站
	ui->listView_Start_RouteSelect->setModel(line->model_Stations);
	ui->listView_Destination_RouteSelect->setModel(line->model_Stations);
}
void MainWindow::on_radioMap_clicked()
{
    // 更新QLabel的内容为地图
    map_RouteSelect.load(mainMapFileName);
    map_RouteSelect = map_RouteSelect.scaled(ui->scrollArea_Map_RouteSelect->width()-30, 
											 ui->scrollArea_Map_RouteSelect->height()-30, 
										Qt::KeepAspectRatio);
    ui->label_Map_RouteSelect->setPixmap(map_RouteSelect);

    // 清空 listView_Start_RouteSelect 和 listView_Destination_RouteSelect
    QStringListModel emptyModel;
    ui->listView_Start_RouteSelect->setModel(&emptyModel);
    ui->listView_Destination_RouteSelect->setModel(&emptyModel);
}

void MainWindow::on_listView_Start_RouteSelect_clicked(const QModelIndex &index)
{
    ui->lineEdit_Start_RouteSelect->setText(index.data().toString());
}
void MainWindow::on_listView_Destination_RouteSelect_clicked(const QModelIndex &index)
{
    ui->lineEdit_Destination_RouteSelect->setText(index.data().toString());
}

// InfoBar
void MainWindow::InfoBarSetUp()
{
    lbInfo = new QLabel(this);
    ui->statusbar->addWidget(lbInfo);
}
void MainWindow::SetInfoType(infoType type)
{
    QString styleSheet;
    switch (type) {
    case MainWindow::info:
        styleSheet = "color: green";
        break;
    case MainWindow::warning:
        styleSheet = "color: orange";
        break;
    case MainWindow::error:
        styleSheet = "color: red";
        break;
    default:
        styleSheet = "color: black";
        break;
    }
    lbInfo->setStyleSheet(styleSheet);
}
void MainWindow::InfoBarClear()
{
    lbInfo->clear();
}
void MainWindow::UpdateInfo(QString info, infoType type)
{
    lbInfo->setText(info);
    SetInfoType(type);
}

void MainWindow::on_lineEdit_Start_RouteSelect_textChanged(const QString &arg1)
{
    ui->lineEdit_Start_Checkout->setText(arg1);
}
void MainWindow::on_lineEdit_Destination_RouteSelect_textChanged(const QString &arg1)
{
    ui->lineEdit_Destination_Checkout->setText(arg1);
}

void MainWindow::SetNumOfTickets_btn()
{
    QChar ch = qobject_cast<QPushButton*>(QObject::sender())->
		objectName().at(QString("btn_").length());
    if (!ch.isDigit()) {
        qDebug() << "Error: btn name error.";
        return;
    }
    uint num = ch.digitValue();
    ui->spinBox_NumOfTickets->setValue(num);
    if (num != order->numOfTickets) {
        order->SetNumOfTickets(num);
        order->GetTotalPrice();
        UpdateTotalPrice();
    }
}
void MainWindow::on_spinBox_NumOfTickets_valueChanged(int arg1)
{
    if (arg1 != order->numOfTickets) {
        order->SetNumOfTickets(arg1);
        order->GetTotalPrice();
        UpdateTotalPrice();
    }
    if (1 <= arg1 && arg1 <= 8) {
        // 将对应按钮设置为选中状态
        QString btnName = QString("btn_%1t").arg(arg1);
        qobject_cast<QPushButton*>(ui->groupBox_SelectNumOfTickets->
            findChild<QPushButton*>(btnName))->setChecked(true);
    } else {
        // 将所有按钮设置为未选中状态
        for (int i = 1; i <= 8; i++) {
			QString btnName = QString("btn_%1t").arg(i);
			qobject_cast<QPushButton*>(ui->groupBox_SelectNumOfTickets->
            	findChild<QPushButton*>(btnName))->setChecked(false);
		}
    }
}
void MainWindow::UpdateTotalPrice()
{
    ui->spinBox_TotalPrice_Cash->setValue(order->totalPrice);
    ui->spinBox_TotalPrice_EPayment->setValue(order->totalPrice);
}

void MainWindow::on_btn_Cash_clicked()
{
    ui->stackedWidget_Payments->setCurrentWidget(ui->page_Cash);
}
void MainWindow::on_btn_WeChatPay_clicked()
{
    ui->stackedWidget_Payments->setCurrentWidget(ui->page_EPayment);
}
void MainWindow::on_btn_AliPay_clicked()
{
    ui->stackedWidget_Payments->setCurrentWidget(ui->page_EPayment);
}
void MainWindow::on_btn_DCEP_clicked()
{
    ui->stackedWidget_Payments->setCurrentWidget(ui->page_EPayment);
}

void MainWindow::InsertCash()
{
    uint cash = qobject_cast<QPushButton*>(QObject::sender())->
        objectName().mid(QString("btn_").length(), 2).toInt();
    ui->spinBox_CashInserted->setValue(ui->spinBox_CashInserted->value() + cash);
}

void MainWindow::on_price_or_cash_changed()
{
    if ((uint)ui->spinBox_CashInserted->value() >= order->totalPrice) {
        ui->spinBox_Change->setValue(ui->spinBox_CashInserted->value() - order->totalPrice);
		ui->btn_FinishPay_Cash->setEnabled(true);
        UpdateInfo("已投入足额现金，点击“完成支付”以继续", infoType::info);
    } else {
        ui->spinBox_Change->setValue(0);
		ui->btn_FinishPay_Cash->setEnabled(false);
        InfoBarClear();
	}
}

void MainWindow::on_btn_FinishPay_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFinishPurchase);
    countDownTimer->start(1000);
}

void MainWindow::CountDown_FinishPay()
{
    countDownSeconds--;

    if (countDownSeconds >= 0) {
        QString text = QString::number(countDownSeconds) + "s 后自动返回主菜单";
        ui->label_AutoHomeCountDown->setText(text);
    } else {
        countDownTimer->stop();
        ui->actReturnHome->trigger();
    }

}

void MainWindow::on_btnGoToMap_clicked() {
    ClearStationQuery();
    ui->stackedWidget->setCurrentWidget(ui->pageStationQuery);
    UpdateInfo("请在站点名和站点编号中输入其中一个进行查找", info);
}

void MainWindow::ClearStationQuery()
{
    ui->lineEdit_StationName_Input->clear();
    ui->lineEdit_StationID_Input->clear();
    QStringListModel emptyModel;
    ui->listView_StationLines->setModel(&emptyModel);
}
void MainWindow::on_btnGoToPurchase_MainMenu_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageRouteSelect);

    // 初始化站点选择界面
    if (map_RouteSelect.isNull())
        on_radioMap_clicked();
    UpdateInfo("请选择起点和终点", info);
}

void MainWindow::on_btnStartQuery_clicked()
{
    uint8_t count = 0;
    if (!ui->lineEdit_StationName_Input->text().isEmpty())
        count += 1;
    if (!ui->lineEdit_StationID_Input->text().isEmpty())
        count += 2;

    switch (count)
    {
    case 0:
        UpdateInfo("错误：未输入任何信息，请在站点名和站点编号中输入其中一个进行查找", error);
        return;
    case 3:
        UpdateInfo("错误：只允许输入站点名和站点编号中的一个，请重试", error);
        return;
    case 1: { // 通过站点名查询
        Query_Name query(ui->lineEdit_StationName_Input->text());
        QStringListModel* model = query.StartQuery();
        ui->listView_StationLines->setModel(query.StartQuery());
        if (model->rowCount() == 0) {
           	UpdateInfo("错误：未找到站点，请检查站点名输入是否正确", warning);
			return;
        }
        UpdateInfo("请在站点名和站点编号中输入其中一个进行查找", info);
    }
        break;
    case 2: { // 通过站点编号查询
        Query_ID query(ui->lineEdit_StationID_Input->text());
        QStringListModel* model = query.StartQuery();
        ui->listView_StationLines->setModel(query.StartQuery());
        // 如果 model 项数不为 0 ，则说明找到了站点
        if (model->rowCount() == 0) {
            UpdateInfo("错误：未找到站点，请检查站点编号输入是否正确", warning);
            return;
        }
        UpdateInfo("请在站点名和站点编号中输入其中一个进行查找", info);
    }
        break;
    default:
        break;
    }
}

void MainWindow::on_listView_StationLines_clicked(const QModelIndex &index)
{
    QString displayString = index.data().toString();
    // listView 显示格式为 “XXXX - X 号线”，需要提取出站点编号，编号可能是 1 位数也可能是 2 位数
    QString lineID = displayString.mid(displayString.length() - 5, 2);
    // qDebug() << "Select line: " << lineID;
    Line* line = FindLineByNumber(lineID.toInt());
    DisplayMap(line->mapFileName, &map_StationQuery, ui->scrollArea_Map_StationQuery, ui->label_Map_StationQuery);
}

