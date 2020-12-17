#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>

#include <QDebug>

#define NMAP_CALLER_PATH "/Users/benjaminscarrone/Desktop/test/exec"
#define LOCALIP_SCRIPT_PATH "/Users/benjaminscarrone/Desktop/test/getLocalIp.sh"
#define ROUTERIP_SCRIPT_PATH "/Users/benjaminscarrone/Desktop/test/getRouterIp.sh"
#define LABEL_LOCAL_IP_DEFAULT_TEXT "Current IP address : "
#define LABEL_ROUTER_IP_DEFAULT_TEXT "Router IP : "


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void getLocalIp();
    void getRouterIp();

public slots:
    void scanNetwork();
    void cutNetwork();

    // nmap process slots
    void getNmapResult();
    void getNmapResult_error();
    void nmap_process_started();
    void nmap_process_finished();

    // ifconfig slots
    void getIfconfigResult();
    void ifconfig_process_started();
    void ifconfig_process_finished();

    // router slots
    void getRouterResult();
    void router_process_started();
    void router_process_finished();

private:
    Ui::MainWindow *ui;
    QProcess *process_nmap, *process_ifconfig, *process_router, *process_arpspoof;
    QString nmap_scan_result, localIpAddress, routerIpAddress;
};
#endif // MAINWINDOW_H
