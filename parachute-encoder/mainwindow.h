#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QColor>

class ParachuteWidget; // Se você usar um personalizado

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void updateSectors(int value);
    void updateTracks(int value);

private:
    ParachuteWidget* parachute_widget;
    QSlider* sector_slider;
    QSlider* track_slider;
    QColor bitOneColor = Qt::red;
};

#endif // MAINWINDOW_H
