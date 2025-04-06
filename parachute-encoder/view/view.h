#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QColor>

#include <QMainWindow>
#include <QSlider>
#include <QColor>
#include <QLineEdit>
#include <QTranslator>
#include <QPushButton>
#include "view/parachutewidget.h"
#include "view/pointswidget.h"

class View : public QMainWindow
{
    Q_OBJECT
public:
    View(QWidget *parent=nullptr);
    ~View();
    void createView();

private:
    // TODO: decide where to put the translator
    QTranslator *translator;

    ParachuteWidget* parachute_widget;
    PointsWidget* points_widget;
    QSlider* sector_slider;
    QSlider* track_slider;
    QPushButton *colorButton;
    QPushButton *encodeButton;
    QPushButton *applyCharButton;
    QLabel *sectors_label;
    QLabel *tracks_label;
    QLineEdit* messageInput;
    QLineEdit* startCharInput;
    QMenu *fileMenu;
    QAction *exitAction;
    QMenu *languageMenu;
    QAction *englishAction;
    QAction *portugueseAction;
    QAction *frenchAction;
    QMenu *helpMenu;
    QAction *aboutAction;


signals:
    void sizeChanged(int);
    void tracksChanged(int);
    void sectorsChanged(int);
    void clearMessageChanged(QString);
    void offsetCharChanged(QChar);
    void languageChanged(QString);
    void bitOneColorChanged(QColor);
    void bitZeroColorChanged(QColor);
    void addPatternChanged(bool);
    void addRandomColorChanged(bool);
};

#endif // VIEW_H
