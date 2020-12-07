#ifndef TESTSTATUSWIDGET_H
#define TESTSTATUSWIDGET_H

#include <QWidget>

class TestStatusWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TestStatusWidget(QWidget *parent = nullptr);
    void start_test(int flag);

    std::map<std::string,double> writerBench_result(){return writerResult;};
    std::map<std::string,double> calcBench_result(){return calcResult;};
    std::map<std::string,double> impressBench_result(){return impressResult;};
    std::map<std::string,double> bigFileBench_result(){return startUpResult;};
    std::map<std::string,double> startUpBench_result(){return bigFileResult;};
    void getData(std::vector<std::string>& name,std::vector<double>& value);
    void setTestFilePath(QString path){testFilePath = path;};
signals:
    void testfinished();//used to inform main window

//public slots:

private slots:
    void cancel_test();

private:
    std::map<std::string,double> writerResult;
    std::map<std::string,double> calcResult;
    std::map<std::string,double> impressResult;
    std::map<std::string,double> startUpResult;
    std::map<std::string,double> bigFileResult;

    std::vector<std::string> itemList;
    std::vector<double> valueList;
    
    QString testFilePath;
};

#endif // TESTSTATUSWIDGET_H
