#include "presenter.h"

Presenter::Presenter(Model* model, View* view) : model(model), view(view) {
    connect(view, &View::sizeChanged, this, &Presenter::onSizeChanged);
    connect(view, &View::tracksChanged, this, &Presenter::onTracksChanged);
    connect(view, &View::sectorsChanged, this, &Presenter::onSectorsChanged);
    connect(view, &View::clearMessageChanged, this, &Presenter::onClearMessageChanged);
    connect(view, &View::offsetCharChanged, this, &Presenter::onOffsetCharChanged);
    connect(view, &View::languageChanged, this, &Presenter::onLanguageChanged);
    connect(view, &View::bitOneColorChanged, this, &Presenter::onBitOneColorChanged);
    connect(view, &View::bitZeroColorChanged, this, &Presenter::onBitZeroColorChanged);
    connect(view, &View::addPatternChanged, this, &Presenter::onAddPatternChanged);
    connect(view, &View::addRandomColorChanged, this, &Presenter::onAddRandomColorChanged);

    connect(model, &Model::modelChanged, this, [this]() {
        // TODO: thing about update view
        // this->view->updateView();
    });
}

void Presenter::onSizeChanged(int value){
    model->setSize(value);
}
void Presenter::onTracksChanged(int value){
    model->setTracks(value);
}
void Presenter::onSectorsChanged(int value){
    model->setSectors(value);
}

// TODO: change all QStrings to reference const
void Presenter::onClearMessageChanged(QString value){
    model->setClearMessage(value);
}
void Presenter::onOffsetCharChanged(QChar value){
    model->setOffsetChar(value);
}
void Presenter::onLanguageChanged(QString value){
    model->setLanguage(value);

    // QString path(qApp->applicationDirPath() + "/.qm");
    // qApp->removeTranslator(translator);
    // if (translator->load("parachute_encoder_" + locale + ".qm", path)) {
    //     qApp->installTranslator(translator);
    // }

    // emit languageChanged();
}
void Presenter::onBitOneColorChanged(QColor value){
    model->setBitOneColor(value);
}
void Presenter::onBitZeroColorChanged(QColor value){
    model->setBitZeroColor(value);
}
void Presenter::onAddPatternChanged(bool value){
    model->setAddPattern(value);
}
void Presenter::onAddRandomColorChanged(bool value){
    model->setAddRandomColor(value);
}

