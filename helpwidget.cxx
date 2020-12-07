#include "helpwidget.h"
#include <QGridLayout>
HelpWidget::HelpWidget(QWidget *parent) : QWidget(parent)
{
    QLabel* version_title = new QLabel(QString("Version"),this);
    QLabel* version_content = new QLabel(this);
    QLabel* help_title = new QLabel(tr("User Help"),this);
    QLabel* introduce_title = new QLabel(tr("Introduce"),this);
    QLabel* help_content = new QLabel(this);
    QLabel* introduce_content = new QLabel(this);

    version_content->setText(tr("version: 0.0.0\nRelease Date: 2020/11/13"));
    help_content->setText(tr("..."));
    introduce_content->setText(tr("..."));

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(version_title);
    layout->addWidget(version_content);
    layout->addWidget(help_title);
    layout->addWidget(help_content);
    layout->addWidget(introduce_title);
    layout->addWidget(introduce_content);

    this->setLayout(layout);
}
