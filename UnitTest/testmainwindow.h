#ifndef TESTMAINWINDOW_H
#define TESTMAINWINDOW_H

#include <QObject>
#include "mainwindow.h"

class TestMainWindow : public QObject
{
    Q_OBJECT
public:
    explicit TestMainWindow(QObject *parent = nullptr);

signals:
private slots:

};

#endif // TESTMAINWINDOW_H
