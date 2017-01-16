#include "vreportwindow.h"
#include "ui_vreportwindow.h"

VReportWindow::VReportWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VReportWindow)
{
    ui->setupUi(this);
}

VReportWindow::~VReportWindow()
{
    delete ui;
}
