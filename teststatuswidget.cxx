#include "teststatuswidget.h"
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include "benchmark.h"
#include <thread>//sleep
#include <chrono>//nanosecond

#include <iostream>

TestStatusWidget::TestStatusWidget(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint);
    QLabel* tips = new QLabel(tr("Please do not using this computer when testing. Otherwise the score may be affected"),this);
    QLabel* status = new QLabel(this);
    QPushButton* cancel_button = new QPushButton(tr("Cancel"),this);
    connect(cancel_button,SIGNAL(clicked(bool)),this,SLOT(cancel_test()));
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(tips);
    layout->addWidget(status);
    layout->addWidget(cancel_button);

    setLayout(layout);
    show();
    raise();
    //connect to benchmarklib,
    //accept test status message from benchmarklib
    //keep update test status message to UI
    //when test finish,
    //send testfinished SIGNAL(to mainwindow)
    //sleep(10);
    //emit testfinished();
}
void TestStatusWidget::cancel_test()
{
    //inform benchmarklib to stop test,
    //get information about stop status,
    //send testfinished SIGNAL.
    emit testfinished();
}
void TestStatusWidget::start_test(int flag)
{
    BenchMark::BenchOffice benchoffice;
    benchoffice.setTestFilePath(testFilePath);
    //BenchMark::initialize_benchoffice(dbgflag);//if dbgflag set, benchoffice will save more log for debug.
    benchoffice.start_bench(flag);//option for writer/calc/impress
    benchoffice.getResult(itemList,valueList);
    emit testfinished();
}
void TestStatusWidget::getData(std::vector<std::string>& name,std::vector<double>& value)
{
    name = itemList;
    value = valueList;
}
