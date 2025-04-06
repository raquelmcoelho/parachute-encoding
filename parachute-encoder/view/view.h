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
#include <QCheckBox>
#include "view/parachutewidget.h"
#include "view/pointswidget.h"

class View : public QMainWindow
{
    Q_OBJECT
public:
    View(QWidget *parent=nullptr);
    ~View();

    void updateOutput(QVector<QString> encoded_bits, int tracks, int sectors, QColor colorOneBit, QColor colorZeroBit, bool randomColor);
    void updateLanguage(QString locale);

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
    QAction *exportAction;
    QAction *importAction;
    QMenu *languageMenu;
    QAction *englishAction;
    QAction *portugueseAction;
    QAction *frenchAction;
    QMenu *helpMenu;
    QAction *aboutAction;
    QCheckBox* sizeBitCheck;
    QCheckBox* randomColorCheck;


signals:
    void sizeChanged(int);
    void tracksChanged(int);
    void sectorsChanged(int);
    void clearMessageChanged(const QString &);
    void offsetCharChanged(QChar);
    void languageChanged(QString);
    void bitOneColorChanged(QColor);
    void bitZeroColorChanged(QColor);
    void addPatternChanged(bool);
    void addRandomColorChanged(bool);
    void exportJson(const QString& path);
    void importJson(const QString& path);
    void toggleSizeRequested(int value);  // 7 or 10
    void randomColorToggled(bool enabled);
};

#endif // VIEW_H
