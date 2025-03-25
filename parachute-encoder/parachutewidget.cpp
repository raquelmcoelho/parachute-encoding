#include "parachutewidget.h"

#include <QPainter>

ParachuteWidget::ParachuteWidget(QWidget *parent)
    : QWidget{parent}
{
    this->message = "ENSICAEN_RULES";
    this->sectors = 21;
    this->tracks = 5;
    this->encoded_bits = this->encode_message(this->message);
}

QString ParachuteWidget::encode_message(const QString &message)
{
    QString binary_sequence;
    for (const QChar &c : message)
    {
        binary_sequence.append(QString::number(c.unicode() - 64, 2).rightJustified(7, '0'));
    }
    return binary_sequence;
}

// void ParachuteWidget::paintEvent(QPaintEvent *event) {
//     QPainter painter(this);
//     painter.setRenderHint(QPainter::Antialiasing);

//     int width = this->width();
//     int height = this->height();
//     QPointF center{static_cast<qreal>(width / 2), static_cast<qreal>(height / 2)};
//     qreal radius = std::min(width, height) / 2 - 10;

//     qreal angle_step = 360 / this->sectors;
//     qreal track_height = radius / this->tracks;

//     for (int i = 0; i < this->sectors * this->tracks; i++) {
//         int track = i / this->sectors;
//         int sector = i % this->sectors;
//         qreal inner_radius = track * track_height;
//         qreal outer_radius = (track + 1) * track_height;
//         qreal start_angle = sector * angle_step;
//         qreal end_angle = (sector + 1) * angle_step;

//         QColor color = this->encoded_bits[i] == '1' ? Qt::black : Qt::white;
//         painter.setBrush(color);
//         painter.setPen(Qt::black);

//         QPolygonF polygon{
//                           this->polar_to_cartesian(center, inner_radius, start_angle),
//             this->polar_to_cartesian(center, inner_radius, end_angle),
//             this->polar_to_cartesian(center, outer_radius, end_angle),
//             this->polar_to_cartesian(center, outer_radius, start_angle)};
//         painter.drawPolygon(polygon);
//     }
// }

QPointF ParachuteWidget::polar_to_cartesian(const QPointF &center, qreal radius, qreal angle) {
    qreal rad = qDegreesToRadians(angle);
    return QPointF(center.x() + radius * qCos(rad), center.y() - radius * qSin(rad));
}

