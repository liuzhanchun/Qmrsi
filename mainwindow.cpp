#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "NetWork.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QCheckBox>
#include "utils.h"
#include "MeasDesktop.h"
#include "TcpClient.h"
#include "DataThread.h"
#include "MeasSwitch.h"
#include "UdpServer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // ui->setupUi(this);
    setMinimumSize(1550, 1020);
    this->setStyleSheet(Utils::getQssContent(":/qss/default.qss"));
    m_pMdiArea = new QMdiArea;
    m_pMdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_pMdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(m_pMdiArea);
    setWindowState(Qt::WindowMaximized);
    m_pWindowMapper = new QSignalMapper(this);
    connect(m_pWindowMapper, SIGNAL(mapped(QWidget*)),this, SLOT(SetActiveSubWindow(QWidget*)));

    // 各种窗口指针的初始化
    InitWindowObj();
    // 创建桌面对象
    CreateDesktopWindow();
    // 创建菜单栏
    CreateMenusBar();
    // 创建工具栏
    CreateActions();
    CreateToolBar();
    // 创建状态栏
     SetStatusBar("Unconnected Network");

    // 显示Desktop
    m_pDesktopWindow->showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::InitWindowObj()
{
    m_pDesktop = nullptr;
    m_pDesktopWindow = nullptr;
}
/**
 * @brief MainWindow::CreateSubWindow
 * 创建子窗口
 * @param pWidget
 * @return
 */
QMdiSubWindow *MainWindow::CreateSubWindow(QWidget *pWidget)
{
    QMdiSubWindow* pSubWin = new QMdiSubWindow;
    pSubWin->setWidget(pWidget);
    pSubWin->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    pSubWin->setAttribute(Qt::WA_DeleteOnClose);
    m_pMdiArea->addSubWindow(pSubWin);
    return pSubWin;
}

/**
 * @brief MainWindow::CreateDesktopWindow
 * 创建桌面窗口
 */
void MainWindow::CreateDesktopWindow()
{
    if ( (m_pDesktopWindow == nullptr) && (m_pDesktop == nullptr) ) {
        m_pDesktop = new CDesktop;
        m_pDesktopWindow = CreateSubWindow(m_pDesktop);          //CreateSubWindow   创建子窗口
    }
}
/**
 * @brief MainWindow::CreateActions
 * 创建工具条上的按钮
 */
void MainWindow::CreateActions()
{
    m_pActDesktop = new QToolButton();
    m_pActDesktop->setObjectName(QString::fromUtf8("ActDesktop"));
    connect(m_pActDesktop, SIGNAL(clicked(bool)), this, SLOT(OnActDesktop()));

    m_pActFullScreen = new QToolButton();
    m_pActFullScreen->setObjectName(QString::fromUtf8("ActFullScreen"));
    //connect(m_pActFullScreen, SIGNAL(clicked(bool)), this, SLOT(OnActFullScreen()));

    m_pActSnapShot = new QToolButton();
    m_pActSnapShot->setObjectName(QString::fromUtf8("ActSnapShot"));
    //connect(m_pActSnapShot, SIGNAL(clicked(bool)), this, SLOT(OnActSnapShot()));

    m_pActSave = new QToolButton();
    m_pActSave->setObjectName(QString::fromUtf8("ActSave"));
    //connect(m_pActSave, SIGNAL(clicked(bool)), this, SLOT(OnActSave()));

    m_pActLoad = new QToolButton();
    m_pActLoad->setObjectName(QString::fromUtf8("ActLoad"));
    //connect(m_pActLoad, SIGNAL(clicked(bool)), this, SLOT(OnActLoad()));

}

/**
 * @brief MainWindow::CreateToolBar
 * 创建工具条
 */
void MainWindow::CreateToolBar()
{
    m_pToolBar = addToolBar("ToolBar");
    m_pToolBar->setObjectName(QString::fromUtf8("ToolBar"));
    m_pToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    addToolBar(Qt::LeftToolBarArea,m_pToolBar);
    m_pToolBar->addWidget(m_pActDesktop);
    m_pToolBar->addWidget(m_pActFullScreen);
    m_pToolBar->addWidget(m_pActSnapShot);
    m_pToolBar->addWidget(m_pActSave);
    m_pToolBar->addWidget(m_pActLoad);


    m_pStatusToolBar = addToolBar("m_pStatusToolBar");
    QLabel * labelCangege=new QLabel(" 测试");
    QWidget *widgetAppearance=new QWidget();
    widgetAppearance->setFixedSize(QSize(60,60));
    QCheckBox *checkBoxWeiWu=new QCheckBox(widgetAppearance);
    checkBoxWeiWu->setGeometry(QRect(5,12,60,15));
    checkBoxWeiWu->setText("t1");
    QCheckBox *checkBoxXiongZhuang=new QCheckBox(widgetAppearance);
    checkBoxXiongZhuang->setGeometry(QRect(5,32,60,15));
    checkBoxXiongZhuang->setText("t2");
    m_pStatusToolBar->addWidget(labelCangege);
    m_pStatusToolBar->addWidget(widgetAppearance);
}

void MainWindow::CreateMenusBar()
{
    //文件
    QMenu* pMenuFile = new QMenu("&文件");
    menuBar()->addMenu(pMenuFile);
    //网络
    QMenu* pMenuNet = new QMenu("&网络");
    QAction* pActionConnect = new QAction("&Connect", this);
    pMenuNet->addAction(pActionConnect);
    connect(pActionConnect, SIGNAL(triggered()), this, SLOT(NetConnect()));
    pMenuNet->addSeparator();

    //pActionConnect ->setEnabled(false);
    QAction* pActionDisconnect = new QAction("&Disconnect", this);
    pMenuNet->addAction(pActionDisconnect);
    connect(pActionDisconnect, SIGNAL(triggered()), this, SLOT(NetDisconnect()));
    menuBar()->addMenu(pMenuNet);
    //插件
    QMenu* pMenuUnit = new QMenu("&插件");
    QAction* pActionUnit = new QAction("&Other...", this);
    pMenuUnit->addAction(pActionUnit);
    menuBar()->addMenu(pMenuUnit);
    //日志
    QMenu* pMenuLog = new QMenu("&日志");
    QAction* pActionLog = new QAction("&Other...", this);
    pMenuLog->addAction(pActionLog);
    menuBar()->addMenu(pMenuLog);
    //工具
    QMenu* pMenuTool = new QMenu("&工具");
    QAction* pActionTool = new QAction("&Other...", this);
    pMenuTool->addAction(pActionTool);
    menuBar()->addMenu(pMenuTool);
    //帮助
    QMenu* pMenuHelp = new QMenu("&帮助");
    QAction* pActionHelp = new QAction("&About...", this);
    pMenuHelp->addAction(pActionHelp);
    menuBar()->addMenu(pMenuHelp);
}

void MainWindow::SetStatusBar(QString status)
{
    statusBar()->setSizeGripEnabled(false);//去掉状态栏右下角的三角
    statusBar()->showMessage(status,2000);
}
void MainWindow::NetConnect()
{
    CNetWork dialog;
    dialog.setModal(false);
    dialog.exec();
    int nPort;
    QString receiveip,controlip;
    if(dialog.GetIPInfo(nPort,receiveip,controlip)=="OK")
         SetStatusBar("Connected Network");


    g_pTcpClient = new CTcpClient();
    g_pTcpClient ->TcpInit(5025,"192.168.0.226");
    g_pTcpClient->SendCmd(SYSTEM_ECHO_ON);
    Sleep(50);
    if(g_bIsRun == true)
    {
        //connect(g_pTcpClient,SIGNAL(msg_para()),this,SLOT(On_UI_UpdateParameters()));

        g_MeasSwitch.EnterLock();
        g_MeasSwitch.SwitchMeas(RXFFM);      /////RXFFM
        g_MeasSwitch.LeaveLock();

        g_pUdpData = new CUdpServer(6025);

        CDataThread *data=new CDataThread;
        data->start();

    }
    else
    {
        delete g_pTcpClient;
        if(g_pTcpClient!=nullptr)
        {
            g_pTcpClient = nullptr;
        }

    }


}
void MainWindow::NetDisconnect()
{

}
void MainWindow::OnActDesktop()
{
    /*Qt::NonModal 不阻塞（非模态对话框）
    Qt::WindowModal 阻塞父窗口，所有祖先窗口及其子窗口（半模态对话框）（没特殊要求的话，一般用这个）
    Qt::ApplicationModal 阻塞整个应用程序（模态对话框）*/
    CMeasDesktop *measdesktop = new CMeasDesktop();
    measdesktop->setWindowModality(Qt::ApplicationModal);
    measdesktop ->show();
    measdesktop->move(this->geometry().x()+44,this->geometry().y()+90);
    //this->hide();
}


