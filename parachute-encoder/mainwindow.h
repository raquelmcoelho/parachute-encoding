#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QColor>
#include <QLineEdit>
#include <QTranslator>
#include <QPushButton>
#include "view/parachutewidget.h"
#include "view/pointswidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void changeLanguage(const QString& locale);

private slots:
    void updateSectors(int value);
    void updateTracks(int value);

private:
    ParachuteWidget* parachute_widget;
    PointsWidget* points_widget;
    QSlider* sector_slider;
    QSlider* track_slider;
    QColor bitOneColor = Qt::red;
    QPushButton *colorButton, *encodeButton, *applyCharButton;
    QLabel *sectors_label, *tracks_label;
    QTranslator *translator;
    QLineEdit* messageInput;
    QLineEdit* startCharInput;
    QMenu *fileMenu, *languageMenu, *helpMenu;
    QAction *exitAction, *englishAction, *portugueseAction, *frenchAction, *aboutAction;

signals:
    void languageChanged();

};

#endif // MAINWINDOW_H
