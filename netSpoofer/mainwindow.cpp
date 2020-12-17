#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    process_nmap = new QProcess();
    nmap_scan_result = "";
    process_ifconfig = new QProcess();
    localIpAddress = "";
    process_router = new QProcess();
    routerIpAddress = "";

    process_arpspoof = new QProcess();

    connect(ui->buttonScan, SIGNAL(clicked()), this, SLOT(scanNetwork()));
    connect(ui->buttonCut, SIGNAL(clicked()), this, SLOT(cutNetwork()));

    connect(process_nmap, SIGNAL(readyReadStandardOutput()), this, SLOT(getNmapResult()));
    connect(process_nmap, SIGNAL(readyReadStandardError()), this, SLOT(getNmapResult_error()));
    connect(process_nmap, SIGNAL(started()), this, SLOT(nmap_process_started()));
    connect(process_nmap, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(nmap_process_finished()));

    connect(process_ifconfig, SIGNAL(readyReadStandardOutput()), this, SLOT(getIfconfigResult()));
    connect(process_ifconfig, SIGNAL(started()), this, SLOT(ifconfig_process_started()));
    connect(process_ifconfig, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(ifconfig_process_finished()));

    connect(process_router, SIGNAL(readyReadStandardOutput()), this, SLOT(getRouterResult()));
    connect(process_router, SIGNAL(started()), this, SLOT(router_process_started()));
    connect(process_router, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(router_process_finished()));

    getLocalIp();
    getRouterIp();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete process_nmap;
    delete process_ifconfig;
    delete process_arpspoof;
}

void MainWindow::scanNetwork()
{
    ui->list_ip->clear();
    QStringList _args;
    process_nmap->start(NMAP_CALLER_PATH, _args);
}

void MainWindow::cutNetwork()
{
    QList<QListWidgetItem*> selected = ui->list_ip->selectedItems();
    if(selected.isEmpty())
        QMessageBox::critical(this, "Error", "You must select an address.");
    else
    {
        QListIterator<QListWidgetItem*> i(selected);
        while(i.hasNext())
        {
            qDebug() << (QString)i.next()->text();
        }
    }
}



void MainWindow::getNmapResult()
{
    QByteArray strdata = process_nmap->readAllStandardOutput();
    nmap_scan_result += strdata;
}
void MainWindow::getNmapResult_error()
{
    QByteArray strdata = process_nmap->readAllStandardError();
    ui->statusbar->showMessage("ERROR while scanning : " + strdata);
}
void MainWindow::nmap_process_started() { ui->statusbar->showMessage("Scanning network..."); }
void MainWindow::nmap_process_finished()
{
    QStringList ipList = nmap_scan_result.split("\n");
    ipList.removeLast();
    ui->list_ip->addItems(ipList);
    nmap_scan_result = "";
    ui->statusbar->showMessage("Finished", 3000);
}

void MainWindow::getLocalIp()
{
    QStringList _args;
    process_ifconfig->start(LOCALIP_SCRIPT_PATH, _args);
}
void MainWindow::getIfconfigResult()
{
    QByteArray strdata = process_ifconfig->readAllStandardOutput();
    localIpAddress += strdata;
}
void MainWindow::ifconfig_process_started() { ui->statusbar->showMessage("Retrieving current IP address..."); }
void MainWindow::ifconfig_process_finished()
{
    if(localIpAddress.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Current IP address not found.");
        ui->labelLocalIp->setText(LABEL_LOCAL_IP_DEFAULT_TEXT);
    }
    else
    {
        ui->labelLocalIp->setText(LABEL_LOCAL_IP_DEFAULT_TEXT + localIpAddress);
        ui->statusbar->showMessage("Current IP address found", 3000);
    }
}

void MainWindow::getRouterIp()
{
    QStringList _args;
    process_router->start(ROUTERIP_SCRIPT_PATH, _args);
}
void MainWindow::getRouterResult()
{
    QByteArray strdata = process_router->readAllStandardOutput();
    routerIpAddress += strdata;
}
void MainWindow::router_process_started() { ui->statusbar->showMessage("Retrieving router IP address..."); }
void MainWindow::router_process_finished()
{
    if(routerIpAddress.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Router IP address not found.");
        ui->labelRouterIp->setText(LABEL_ROUTER_IP_DEFAULT_TEXT);
    }
    else
    {
        ui->labelRouterIp->setText(LABEL_ROUTER_IP_DEFAULT_TEXT + routerIpAddress);
        ui->statusbar->showMessage("Router IP address found", 3000);
    }
}
