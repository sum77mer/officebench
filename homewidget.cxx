#include "homewidget.h"
#include <QGridLayout>
#include <QGroupBox>
#include <QGuiApplication>
#include <QScreen>
#include <algorithm> //min
#include <iostream>
#include <QPushButton>
#include <QDir>
#include <QComboBox>
#include <QFileDialog>
#include <QLabel>

HomeWidget::HomeWidget(QWidget *parent) : QWidget(parent)
{
    QPushButton* startbenchmark_button = new QPushButton(tr("Start"),this);
    connect(startbenchmark_button,SIGNAL(clicked(bool)),this,SLOT(start_clicked()));

    option_writer = new QCheckBox(tr("Writing BenchMark"),this);
    option_calc = new QCheckBox(tr("Spreadsheets BenchMark"),this);
    option_impress = new QCheckBox(tr("Presentation BenchMark"),this);
    option_bigfile = new QCheckBox(tr("Big File Loading BenchMark"),this);

    QLabel* testFilePageLabel= new QLabel(tr("Test File"));

    QPushButton *browseButton = new QPushButton(tr("&Browse..."), this);
    connect(browseButton, SIGNAL(clicked(bool)), this, SLOT(browse()));

    directoryComboBox = createComboBox(QDir::toNativeSeparators(QDir::currentPath()+default_path));

    int desktopWidth,desktopHeight;
    getDesktopScreenResolution(desktopWidth,desktopHeight);
    max_width = desktopWidth;
    max_height = desktopHeight;

    min_width = std::min(int(desktopWidth*0.4),min_width);
    min_height = std::min(int(desktopHeight*0.4),min_height);

    setMinimumWidth(min_width);
    setMinimumHeight(min_height);
    setMaximumWidth(max_width);
    setMaximumHeight(max_height);

    QGroupBox* testoptions = new QGroupBox(tr("Benchmark Options"),this);
    QVBoxLayout* testoptions_vbox = new QVBoxLayout;
    testoptions_vbox->addWidget(option_writer);
    testoptions_vbox->addWidget(option_calc);
    testoptions_vbox->addWidget(option_impress);
    testoptions_vbox->addWidget(option_bigfile);

    testoptions_vbox->addStretch(1);
    testoptions->setLayout(testoptions_vbox);


    option_log = new QCheckBox(tr("log"),this);
    QGroupBox* troubleshooting_options = new QGroupBox(tr("Troubleshooting"),this);
    QVBoxLayout* troubleshootingoptions_vbox = new QVBoxLayout;
    troubleshootingoptions_vbox->addWidget(option_log);
    troubleshooting_options->setLayout(troubleshootingoptions_vbox);

    QGridLayout* layout = new QGridLayout;

    //row0: empty
    //row1: testoptions
    layout->addWidget(testoptions,1,1,1,4,Qt::AlignTop);
    //row2: empty
    //row3: troubleshooting options
    layout->addWidget(troubleshooting_options,2,1,1,4,Qt::AlignTop);
    //row4: empty
    //row5: start and stop buttons
    layout->addWidget(testFilePageLabel,4,1,1,1,Qt::AlignTop);
    layout->addWidget(directoryComboBox,4,2,1,2,Qt::AlignTop);
    layout->addWidget(browseButton,4,4,1,1,Qt::AlignTop);
    //
    layout->addWidget(startbenchmark_button,6,4,1,1,Qt::AlignCenter);
    //row6: empty

    //col0: empty,10
    //col1: testoptions & troubleshooting options
    //col2: empty,10
    //col3: startbutton
    //col4: empty,10
    //col5: stop button
    //col6: empty,10

    layout->setRowMinimumHeight(0,10);
    layout->setRowStretch(0,0);
    layout->setRowStretch(1,55);
    layout->setRowMinimumHeight(2,10);
    layout->setRowStretch(2,0);
    layout->setRowStretch(3,30);
    layout->setRowMinimumHeight(4,10);
    layout->setRowStretch(4,0);
    layout->setRowStretch(5,15);
    layout->setRowMinimumHeight(6,10);
    layout->setRowStretch(6,0);
    layout->setRowStretch(7,10);

    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,10);
    layout->setColumnStretch(2,80);
    layout->setColumnStretch(3,10);
    layout->setColumnStretch(4,0);

    this->setLayout(layout);
}
QComboBox *HomeWidget::createComboBox(const QString &text)
{
    QComboBox *comboBox = new QComboBox;
    comboBox->setEditable(true);
    comboBox->addItem(text);
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    return comboBox;
}
void HomeWidget::browse()
{
    QString directory =
    QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath()));

    if (!directory.isEmpty()) {
        if (directoryComboBox->findText(directory) == -1)
            directoryComboBox->addItem(directory);
        directoryComboBox->setCurrentIndex(directoryComboBox->findText(directory));
    }
}
void HomeWidget::getDesktopScreenResolution(int &width,int &height)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    height = screenGeometry.height();
    width = screenGeometry.width();
    //if(DEBUG)
        std::cout<<"Width: "<<width<<" Height:"<<height<<std::endl;
}
void HomeWidget::start_clicked()
{
    qDebug("HomeWidget: slot start_clicked() triggered");
    //option_writer->isChecked();
    //inform mainwindow
    int flag = 0;
    if(option_writer->isChecked())
        flag+=0x1;
    if(option_calc->isChecked())
        flag += 0x2;
    if(option_impress->isChecked())
        flag += 0x4;
    if(option_bigfile->isChecked())
        flag += 0x8;
    std::cout<<"flag:"<<flag<<std::endl;
    QString path = directoryComboBox->currentText();
    emit benchmark_start(flag,path);
}
