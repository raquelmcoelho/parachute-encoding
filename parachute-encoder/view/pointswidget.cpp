#include "pointswidget.h"
#include <QPainter>
#include <QRandomGenerator>

PointsWidget::PointsWidget(QWidget *parent) {
}

void PointsWidget::updateView(QVector<QString> encodedBits, QColor colorOneBit, QColor colorZeroBit, bool randomColor) {
    this->encodedBits = encodedBits;
    this->colorOneBit = colorOneBit;
    this->colorZeroBit = colorZeroBit;
    this->randomColor = randomColor;
    
    this->update();
}

void PointsWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int circleSize = 20; // Circle size
    int spacing = 5; // Beetween circles

    int numColumns = encodedBits.length();  // Each char is a column
    int numRows = 7;

    int totalWidth = numColumns * (circleSize + spacing);
    int totalHeight = numRows * (circleSize + spacing);

    // Warn scroll if it's not fitting
    setMinimumSize(totalWidth, totalHeight);

    // Draw each column
    for (int col = 0; col < numColumns; ++col)
    {
        QString binStr = QString("%1").arg(encodedBits.at(col), 8, QChar('0')); // Letter as 8 bits

        // TODO: verify its exactly eight bits
        qDebug() << "poins widget char " << binStr;
        for (int row = 0; row < 7; ++row)
        {
            QRect rect(col * (circleSize + spacing), (row) * (circleSize +
            spacing), circleSize, circleSize);

            if (binStr[row+1] == '1')  // Bit '1'
            {
                if(this->randomColor) {
                    int r = QRandomGenerator::global()->bounded(256);
                    int g = QRandomGenerator::global()->bounded(256);
                    int b = QRandomGenerator::global()->bounded(256);
                    painter.setBrush(QColor(r, g, b));
                } else {
                    painter.setBrush(this->colorOneBit);
                }
            }
            else  // Bit '0'
            {
                painter.setBrush(this->colorZeroBit);
            }

            painter.drawEllipse(rect);
        }
    }
}
