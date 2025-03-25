#ifndef PARACHUTEWIDGET_H
#define PARACHUTEWIDGET_H

#include <QWidget>

class ParachuteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParachuteWidget(QWidget *parent = nullptr);

// protected:
//     void paintEvent(QPaintEvent *event) override;

private:
    int sectors;
    int tracks;
    QString message;
    QString encoded_bits;
    QString encode_message(const QString &message);
    QPointF polar_to_cartesian(const QPointF &center, qreal radius, qreal angle);

signals:
};
#endif // PARACHUTEWIDGET_H
