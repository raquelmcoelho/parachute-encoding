#ifndef POINTSWIDGET_H
#define POINTSWIDGET_H

#include <QWidget>
#include <QColor>

class PointsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PointsWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;


};

#endif // POINTSWIDGET_H
