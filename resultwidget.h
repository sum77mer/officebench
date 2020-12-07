#ifndef RESULTWIDGET_H
#define RESULTWIDGET_H

#include <QWidget>
#include "treemodel.h"
#include "treeitem.h"
#include <QTreeView>

class ResultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ResultWidget(QWidget *parent = nullptr);

    void getData(std::vector<std::string> name,std::vector<double> value);
    void display_writerBench(std::map<std::string,double> result);
    void display_calcBench(std::map<std::string,double> result);
    void display_impressBench(std::map<std::string,double> result);
    void display_bigFileBench(std::map<std::string,double> result);
    void display_startUpBench(std::map<std::string,double> result);
    void updateResult();
signals:
public slots:
    void displayresult();

private:

    QTreeView* treeView = NULL;
    TreeModel* model = NULL;
};

#endif // RESULTWIDGET_H
