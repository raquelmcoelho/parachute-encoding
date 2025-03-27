#ifndef POINTSWIDGET_H
#define POINTSWIDGET_H

#include <QWidget>
#include <QColor>

class PointsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PointsWidget(QWidget *parent = nullptr);
    void setMessage(const QString &msg);
    void setBitOneColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString message;
    QColor bitOneColor;
};

#endif // POINTSWIDGET_H
