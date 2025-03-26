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

private:
    QString encoded_bits;
    QColor bitOneColor = Qt::black;
    QChar startChar = '@';

public:
    QString message;
    int sectors;
    int tracks;

    ParachuteWidget(QString msg = "ENSICAEN_RULES", int sec = 21, int trk = 5, QWidget *parent = nullptr);

    QString encodeMessage();
    void setBitOneColor(QColor color);

    void setMessage(const QString& newMessage);
    void setStartChar(QChar c);

protected:
    void paintEvent(QPaintEvent *event) override;
    QPointF polarToCartesian(QPointF center, double radius, double angle);
};

#endif // PARACHUTEWIDGET_H
