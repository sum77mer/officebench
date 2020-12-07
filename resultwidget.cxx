#include "resultwidget.h"
#include <QGridLayout>
#include <QLabel>
#include <iostream>
#include <QFileSystemModel>
#include <QTreeView>
#include <QStringList>
ResultWidget::ResultWidget(QWidget *parent) : QWidget(parent)
{
    model = new TreeModel(QString(""),this);
    treeView = new QTreeView(this);
    treeView->setModel(model);

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(treeView);
    setLayout(layout);
}
void ResultWidget::displayresult()
{

}
void ResultWidget::getData(std::vector<std::string> name,std::vector<double> value)
{
    QString string;
    for(auto i=0;i<name.size();i++)
    {
        QString s(name[i].data());
        s+=QString(":");
        s+=QString("%1").arg(value[i],3,'f',-1,QLatin1Char('0'));
        s+=QString("\n");
        string+=s;
    }
    model = new TreeModel(string,this);
    treeView->setModel(model);

    update();
}
void ResultWidget::updateResult()
{

}
void ResultWidget::display_writerBench(std::map<std::string,double> result)
{
    QGridLayout* layout = new QGridLayout;
    int row = 0;
    for(auto r:result)
    {
        QLabel* title = new QLabel(this);
        title->setText(QString(r.first.data()));
        QLabel* value = new QLabel(this);
        std::cout<<r.first<<":"<<r.second<<std::endl;
        value->setText(QString("%1").arg(r.second,3,'f',-1,QLatin1Char('0')));
        layout->addWidget(title,row,0,Qt::AlignLeft);
        layout->addWidget(value,row,2,Qt::AlignRight);
        row++;
    }
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(2,1);
    layout->setColumnStretch(1,6);
    layout->setColumnMinimumWidth(1,20);
    this->setLayout(layout);

    update();
}
void ResultWidget::display_calcBench(std::map<std::string,double> result)
{
    QGridLayout* layout = new QGridLayout;
    int row = 0;
    for(auto r:result)
    {
        QLabel* title = new QLabel(this);
        title->setText(QString(r.first.data()));
        QLabel* value = new QLabel(this);
        std::cout<<r.first<<":"<<r.second<<std::endl;
        value->setText(QString("%1").arg(r.second,3,'f',-1,QLatin1Char('0')));
        layout->addWidget(title,row,0,Qt::AlignLeft);
        layout->addWidget(value,row,2,Qt::AlignRight);
        row++;
    }
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(2,1);
    layout->setColumnStretch(1,6);
    layout->setColumnMinimumWidth(1,20);
    this->setLayout(layout);

    update();
}
void ResultWidget::display_impressBench(std::map<std::string,double> result)
{
    QGridLayout* layout = new QGridLayout;
    int row = 0;
    for(auto r:result)
    {
        QLabel* title = new QLabel(this);
        title->setText(QString(r.first.data()));
        QLabel* value = new QLabel(this);
        std::cout<<r.first<<":"<<r.second<<std::endl;
        value->setText(QString("%1").arg(r.second,3,'f',-1,QLatin1Char('0')));
        layout->addWidget(title,row,0,Qt::AlignLeft);
        layout->addWidget(value,row,2,Qt::AlignRight);
        row++;
    }
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(2,1);
    layout->setColumnStretch(1,6);
    layout->setColumnMinimumWidth(1,20);
    this->setLayout(layout);

    update();
}
void ResultWidget::display_bigFileBench(std::map<std::string,double> result)
{

}
void ResultWidget::display_startUpBench(std::map<std::string,double> result)
{

}