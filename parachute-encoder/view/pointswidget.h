#ifndef POINTSWIDGET_H
#define POINTSWIDGET_H

#include <QWidget>
#include <QColor>

class PointsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PointsWidget(QWidget *parent = nullptr);
    void updateView(QVector<QString> encodedBits, QColor colorOneBit, QColor colorZeroBit, bool randomColor);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QString> encodedBits;
    QColor colorOneBit;
    QColor colorZeroBit;
    bool randomColor;

};

#endif // POINTSWIDGET_H
