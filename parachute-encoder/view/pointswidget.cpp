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

    int circleSize = 20; // Tamanho do círculo
    int spacing = 5; // Espaçamento entre círculos

    int numColumns = message.length();  // Cada caractere da mensagem é uma coluna
    int numRows = 7;  // Sempre 7 linhas

    // Ajustar tamanho do widget para suportar scroll se necessário
    int totalWidth = numColumns * (circleSize + spacing);
    int totalHeight = numRows * (circleSize + spacing);
    setMinimumSize(totalWidth, totalHeight);

    // Percorrer a mensagem e desenhar os círculos
    for (int col = 0; col < numColumns; ++col)
    {
        QChar ch = message.at(col);
        QString binStr = QString("%1").arg(ch.unicode()-startChar.unicode(), 8, 2, QChar('0')); // Binário de 8 bits

        for (int row = 0; row < 7; ++row)
        {
            QRect rect(col * (circleSize + spacing), row * (circleSize + spacing), circleSize, circleSize);

            if (binStr[7 - row] == '1')  // Bit '1' colorido
            {
                painter.setBrush(bitOneColor);
            }
            else  // Bit '0' branco
            {
                painter.setBrush(Qt::white);
            }

            painter.drawEllipse(rect); // Desenha um círculo
        }
    }
}
