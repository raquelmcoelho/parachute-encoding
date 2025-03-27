#include "pointswidget.h"
#include <QPainter>

PointsWidget::PointsWidget(QString msg, QWidget *parent) : QWidget(parent), message(msg), bitOneColor(Qt::black)
{
}

void PointsWidget::setMessage(const QString &msg)
{
    message = msg;
    update();
}

void PointsWidget::setBitOneColor(const QColor &color)
{
    bitOneColor = color;
    update();
}

void PointsWidget::setStartChar(QChar c)
{
    startChar = c;
    update();
}

void PointsWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int circleSize = 20; // Circle size
    int spacing = 5; // Beetween circles

    int numColumns = message.length();  // Each char is a column
    int numRows = 7;

    int totalWidth = numColumns * (circleSize + spacing);
    int totalHeight = numRows * (circleSize + spacing);

    // Warn scroll if it's not fitting
    setMinimumSize(totalWidth, totalHeight);

    // Draw each column
    for (int col = 0; col < numColumns; ++col)
    {
        QChar ch = message.at(col);
        QString binStr = QString("%1").arg(ch.unicode()-startChar.unicode(), 8, 2, QChar('0')); // Letter as 8 bits

        for (int row = 0; row < 7; ++row)
        {
            QRect rect(col * (circleSize + spacing), (row) * (circleSize + spacing), circleSize, circleSize);

            if (binStr[row+1] == '1')  // Bit '1'
            {
                painter.setBrush(bitOneColor);
            }
            else  // Bit '0'
            {
                painter.setBrush(Qt::white);
            }

            painter.drawEllipse(rect);
        }
    }
}
