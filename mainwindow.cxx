#include "mainwindow.h"
#include "homewidget.h"
#include "resultwidget.h"
#include "helpwidget.h"

#include <QGridLayout>
#include <QPushButton>
#include <QGuiApplication>
#include <QScreen>

#include <thread>//sleep
#include <chrono>//nanosecond

#include <algorithm> //min
#include <iostream>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    int desktopWidth,desktopHeight;
    getDesktopScreenResolution(desktopWidth,desktopHeight);

    initial_width = desktopWidth*0.6;
    initial_height = desktopHeight*0.6;

    max_width = desktopWidth;
    max_height = desktopHeight;

    min_width = std::min(int(desktopWidth*0.4),min_width);
    min_height = std::min(int(desktopHeight*0.4),min_height);
    std::cout<<min_width<<"*"<<min_height<<std::endl;

    setWindowFlags(Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint|Qt::WindowCloseButtonHint);
    
    setMinimumHeight(min_height);
    setMinimumWidth(min_width);

    initial_posX = (desktopWidth-width())/2;
    initial_posY = 0;

    setMaximumHeight(max_height);
    setMaximumWidth(max_width);

    move(initial_posX,initial_posY);

    homepage = new HomeWidget(this);
    resultpage = new ResultWidget(this);
    helppage = new HelpWidget(this);

    tabwidget = new TabWidget(this);
    tabwidget->addTab(homepage,tr("Home"));
    tabwidget->addTab(resultpage,tr("Result"));
    tabwidget->addTab(helppage,tr("Help"));
    connect(homepage,SIGNAL(benchmark_start(int,QString)),this,SLOT(benchmark_start(int,QString)));
    connect(this,SIGNAL(displayresult()),resultpage,SLOT(displayresult()));
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(tabwidget,0,0,Qt::AlignCenter);
    layout->setContentsMargins(10,10,10,10);
    layout->setRowStretch(0,1);
    layout->setColumnStretch(0,1);
    this->setLayout(layout);
}
Dialog::~Dialog()
{
}
void Dialog::getDesktopScreenResolution(int &width,int &height)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    height = screenGeometry.height();
    width = screenGeometry.width();
    //if(DEBUG)
        std::cout<<"Width: "<<width<<" Height:"<<height<<std::endl;
}
void Dialog::benchmark_start(int flag,QString path)
{
    bench_flag = flag;
    qDebug("mainwidow: slot benchmark_start() triggered");
    //create test status widget
    teststatuswidget = new TestStatusWidget();
    teststatuswidget->setTestFilePath(path);
    //connect signal
    connect(teststatuswidget,SIGNAL(testfinished()),this,SLOT(testfinished()));
    //lock inpiut, mainwindow not available for user interaction
    //display teststatuswidget
    teststatuswidget->show();
    teststatuswidget->start_test(flag);
}
void Dialog::testfinished()
{
    qDebug("mainwindow: slot testfinished() triggered");
    //depend on testfinished result flag,
    //if no error:
    //change tab to resultpage
    //inform resultpage to display results
    //if error:
    //pop up a message window to inform user
    std::this_thread::sleep_for(std::chrono::nanoseconds(6000));
    teststatuswidget->close();
    std::vector<std::string> names;
    std::vector<double> values;
    teststatuswidget->getData(names,values);
    for(int i=0;i<names.size();i++)
        std::cout<<names[i]<<":"<<values[i]<<std::endl;
    resultpage->getData(names,values);

    tabwidget->setCurrentWidget(resultpage);
}
