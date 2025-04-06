#ifndef PRESENTER_H
#define PRESENTER_H

#include <QObject>
#include "model/model.h"
#include "view/view.h"


class Presenter : public QObject {
    Q_OBJECT

public:
    Presenter(Model* model, View* view);

private slots:
    void onSizeChanged(int value);
    void onTracksChanged(int value);
    void onSectorsChanged(int value);

    // TODO: change all QStrings to reference const
    void onClearMessageChanged(QString value);
    void onOffsetCharChanged(QChar value);
    void onLanguageChanged(QString value);
    void onBitOneColorChanged(QColor value);
    void onBitZeroColorChanged(QColor value);
    void onAddPatternChanged(bool value);
    void onAddRandomColorChanged(bool value);
    
private:
    Model* model;
    View* view;
};


#endif // PRESENTER_H
