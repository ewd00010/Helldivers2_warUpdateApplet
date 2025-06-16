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
    MainWindow(QWidget *parent = nullptr, std::shared_ptr<DisplayInfoHandler> *DIH = nullptr, std::shared_ptr<API_Caller> *apiCaller = nullptr);
    ~MainWindow();
    std::shared_ptr<DisplayInfoHandler> myDIH;
    std::shared_ptr<API_Caller> myApiCaller;

private slots:
    void on_actionClear_all_planets_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
