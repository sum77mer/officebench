#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QDebug>
#include <QComboBox>
class HomeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HomeWidget(QWidget *parent = nullptr);

signals:
    void benchmark_start(int flag,QString path);

private slots:
    void start_clicked();
    void browse();

private:
    void getDesktopScreenResolution(int &width,int &height);
    QComboBox *createComboBox(const QString &text);
private:
    int min_width = 1200;
    int min_height = 400;
    int max_width = 0;
    int max_height = 0;

    QCheckBox* option_writer = NULL;
    QCheckBox* option_calc = NULL;
    QCheckBox* option_impress = NULL;
    QCheckBox* option_bigfile = NULL;
    QCheckBox* option_startup = NULL;
    QCheckBox* option_log = NULL;
    QPushButton* startbenchmark_button = NULL;
    QComboBox *directoryComboBox;
    QString default_path = "/testfile";
    std::vector<std::string> testFilesPath;
};

#endif // HOMEWIDGET_H
