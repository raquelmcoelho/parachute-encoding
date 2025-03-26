#include <view/parachutewidget.h>

ParachuteWidget::ParachuteWidget(QString msg, int sec, int trk, QWidget *parent)
    : QWidget(parent), message(msg), sectors(sec), tracks(trk)
{
    this->encoded_bits = encodeMessage();
}

QString ParachuteWidget::encodeMessage()
{
    QString binary_sequence;
    for (QChar c : message)
    {
        binary_sequence += QString::number(c.unicode() - 64, 2).rightJustified(7, '0');
    }
    return binary_sequence;
}

void ParachuteWidget::setBitOneColor(QColor color)
{
    bitOneColor = color;
    update();
}

void ParachuteWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int width = this->width();
    int height = this->height();
    QPointF center(width / 2, height / 2);
    double radius = std::min(width, height) / 2 - 10;

    double angle_step = 360.0 / sectors;
    double track_height = radius / tracks;

    for (int i = 0; i < std::min(sectors * tracks, static_cast<int>(encoded_bits.size())); ++i)
    {
        int track = i / sectors;
        int sector = i % sectors;
        double inner_radius = track * track_height;
        double outer_radius = (track + 1) * track_height;
        double start_angle = sector * angle_step;
        double end_angle = (sector + 1) * angle_step;

        QColor color = (encoded_bits[i] == '1') ? bitOneColor : Qt::white;
        painter.setBrush(color);
        painter.setPen(Qt::black);

        QPolygonF polygon;
        polygon << polarToCartesian(center, inner_radius, start_angle)
                << polarToCartesian(center, inner_radius, end_angle)
                << polarToCartesian(center, outer_radius, end_angle)
                << polarToCartesian(center, outer_radius, start_angle);

        painter.drawPolygon(polygon);
    }
}

QPointF ParachuteWidget::polarToCartesian(QPointF center, double radius, double angle)
{
    double rad = qDegreesToRadians(angle);
    return QPointF(center.x() + radius * cos(rad), center.y() - radius * sin(rad));
}
