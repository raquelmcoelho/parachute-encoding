#include <view/parachutewidget.h>
#include <QRandomGenerator>

#define OFFSET 10

ParachuteWidget::ParachuteWidget(QWidget *parent)
    : QWidget(parent)
{
}

void ParachuteWidget::updateView(QVector<QString> encodedBits, int tracks, int sectors, QColor colorOneBit, QColor colorZeroBit, bool randomColor) {
    QString joined;
    for (const auto& str : encodedBits)
        joined += str;
    this->encodedBits = joined;
    this->tracks = tracks;
    this->sectors = sectors;
    this->colorOneBit = colorOneBit;
    this->colorZeroBit = colorZeroBit;
    this->randomColor = randomColor;

    this->update();
}

void ParachuteWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int width = this->width();
    int height = this->height();
    QPointF center(width / 2, height / 2);
    double radius = std::min(width, height) / 2 - OFFSET;

    // sector - triangular division which resembles a slice of pizza
    // tracks- amount of circles
    double angle_step = -360.0 / this->sectors;
    double track_height = radius / this->tracks;

    int total_segments = this->sectors * this->tracks;

    for (int i = 0; i < total_segments; ++i)
    {
        int track = i / this->sectors;
        int sector = i % this->sectors;
        double inner_radius = track * track_height;
        double outer_radius = (track + 1) * track_height;
        double start_angle = sector * angle_step;
        double end_angle = (sector + 1) * angle_step;

        QColor color = this->colorZeroBit;

        if (i < this->encodedBits.size() && this->encodedBits[i] == '1') {
            if(this->randomColor) {
                int r = QRandomGenerator::global()->bounded(256);
                int g = QRandomGenerator::global()->bounded(256);
                int b = QRandomGenerator::global()->bounded(256);
                color = QColor(r, g, b);
            } else {
                color = this->colorOneBit;
            }
        }

        painter.setBrush(color);
        painter.setPen(Qt::black);

        QPolygonF polygon;
        polygon << polarToCartesian(center, outer_radius, start_angle)
                << polarToCartesian(center, outer_radius, end_angle)
                << polarToCartesian(center, inner_radius, end_angle)
                << polarToCartesian(center, inner_radius, start_angle);

        painter.drawPolygon(polygon);
    }
}

QPointF ParachuteWidget::polarToCartesian(QPointF center, double radius, double angle)
{
    double rad = qDegreesToRadians(angle);
    return QPointF(center.x() + radius * cos(rad), center.y() - radius * sin(rad));
}
