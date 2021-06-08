#ifndef MYPROCESSXMLDATATHREAD_H
#define MYPROCESSXMLDATATHREAD_H

#include <QThread>
#include "mainwindow.h"
class MainWindow;
class MyProcessXmlDataThread : public QThread
{
    Q_OBJECT
public:
    MyProcessXmlDataThread();
    MyProcessXmlDataThread(MainWindow *main_widget, QString data);
signals:
    void data_update(int cur_row);
private:
    void run() override;
private:
    MainWindow *m_main_widget;
    QString m_xml_data;
};

#endif // MYPROCESSXMLDATATHREAD_H
