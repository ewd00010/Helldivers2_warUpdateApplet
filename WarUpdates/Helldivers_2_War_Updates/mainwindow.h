#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "display_info_handler.h"
#include "api_caller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::shared_ptr<DisplayInfoHandler> myDIH;
    std::shared_ptr<API_Caller> myApiCaller;

private slots:
    void on_actionClear_all_planets_triggered();

    void on_action_Automatically_add_triggered();

    void on_actionAdd_war_info_triggered();

    void on_actionClear_war_info_triggered();

private:
    Ui::MainWindow *ui;
    inline static const int BASE_WIDTH = 700;
    inline static const int BASE_HEIGHT = 500;
    inline static const int MAX_WIDTH = 1920;
    inline static const int MAX_HEIGHT = 1080;
};
#endif // MAINWINDOW_H
