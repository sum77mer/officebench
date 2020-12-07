#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QDebug>

#include "tabwidget.h"
#include "homewidget.h"
#include "resultwidget.h"
#include "helpwidget.h"
#include "teststatuswidget.h"

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();



signals:
    void displayresult();
private slots:
    void benchmark_start(int flag,QString path);
public slots:
    void testfinished();
private:
    void getDesktopScreenResolution(int &width,int &height);
private:
    int initial_posX = 0;
    int initial_posY = 0;
    int min_width = 1200;
    int min_height = 400;
    int max_width = 0;
    int max_height = 0;
    int initial_width = 1800;
    int initial_height = 1200;

    HomeWidget* homepage = NULL;
    ResultWidget* resultpage = NULL;
    HelpWidget* helppage = NULL;

    TabWidget* tabwidget;
    TestStatusWidget* teststatuswidget = NULL;

    int bench_flag;
};
#endif // MAINWINDOW_H
