#ifndef VREPORTWINDOW_H
#define VREPORTWINDOW_H

#include <QWidget>

namespace Ui {
class VReportWindow;
}

class VReportWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit VReportWindow(QWidget *parent = 0);
    ~VReportWindow();
    
private:
    Ui::VReportWindow *ui;
};

#endif // VREPORTWINDOW_H
