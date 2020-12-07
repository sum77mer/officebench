#include "resultloadingwidget.h"
#include <QLabel>
#include <QMovie>
#include <QGridLayout>

ResultLoadingWidget::ResultLoadingWidget(QWidget *parent) : QWidget(parent)
{
    QLabel* tip = new QLabel(tr("Result Loading..."),this);
    QMovie* movie = new QMovie("loader.gif");
    tip->setMovie(movie);
    tip->show();
    movie->start();

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(tip);

    setLayout(layout);
}
