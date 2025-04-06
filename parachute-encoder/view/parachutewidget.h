#ifndef PARACHUTEWIDGET_H
#define PARACHUTEWIDGET_H

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QPolygonF>
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>
#include <cmath>
#include <QString>
#include <QColor>

class ParachuteWidget : public QWidget
{
    Q_OBJECT

public:
    ParachuteWidget(QWidget *parent = nullptr);
    void updateView(QVector<QString> encodedBits, int tracks, int sectors, QColor colorOneBit, QColor colorZeroBit, bool randomColor);


protected:
    void paintEvent(QPaintEvent *event) override;
    QPointF polarToCartesian(QPointF center, double radius, double angle);

private:
    int sectors;
    int tracks;
    QString encodedBits;
    QColor colorOneBit;
    QColor colorZeroBit;
    bool randomColor;

};

#endif // PARACHUTEWIDGET_H
