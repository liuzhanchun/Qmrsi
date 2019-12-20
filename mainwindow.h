#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QSignalMapper>
#include <QToolButton>
#include "Desktop.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void NetConnect();
    void NetDisconnect();
    void OnActDesktop();

private:
    Ui::MainWindow *ui;


private:
    void SetStatusBar(QString status);
    void InitWindowObj();
    void CreateDesktopWindow();
    QMdiSubWindow* CreateSubWindow(QWidget* pWidget );
    void CreateActions();       // 工具栏按钮
    void CreateToolBar();       // 工具栏
    void CreateMenusBar();

    QMdiArea* m_pMdiArea;
    QSignalMapper* m_pWindowMapper;
    CDesktop* m_pDesktop;                    // 桌面对象
    QMdiSubWindow* m_pDesktopWindow;    // 桌面子窗口

    //工具栏
    QToolBar*  m_pToolBar;
    QToolButton* m_pActDesktop;        // 回桌面
    QToolButton* m_pActFullScreen;     // 全屏幕
    QToolButton*  m_pActSnapShot;     // 截屏
    QToolButton* m_pActSave;              // 文件保存
    QToolButton* m_pActLoad;             // 文件加载

    QToolBar*  m_pStatusToolBar;

};

#endif // MAINWINDOW_H
