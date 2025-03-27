#ifndef POINTSWIDGET_H
#define POINTSWIDGET_H

#include <QWidget>
#include <QColor>

class PointsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PointsWidget(QString msg = "ENSICAEN_RULES", QWidget *parent = nullptr);
    void setMessage(const QString &msg);
    void setBitOneColor(const QColor &color);
    void setStartChar(QChar c);
    QString encodeMessage();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString message;
    QColor bitOneColor = Qt::black;
    QChar startChar = '@';

};

#endif // POINTSWIDGET_H
