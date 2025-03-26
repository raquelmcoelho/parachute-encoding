#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QPolygonF>
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>
#include <cmath>
#include <QString>
#include <view/parachutewidget.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    ParachuteWidget *parachute_widget;
    QSlider *sector_slider;
    QSlider *track_slider;

public:
    MainWindow(QWidget *parent = nullptr);
public slots:
    void updateSectors(int value);

    void updateTracks(int value);
};
#endif // MAINWINDOW_H
