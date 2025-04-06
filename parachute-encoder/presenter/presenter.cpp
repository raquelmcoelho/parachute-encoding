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
    connect(view, &View::exportJson, this, &Presenter::onExportJson);
    connect(view, &View::importJson, this, &Presenter::onImportJson);
    connect(view, &View::toggleSizeRequested, this, &Presenter::onToggleSizeRequested);
    connect(view, &View::randomColorToggled, this, &Presenter::onRandomColorToggled);

    connect(model, &Model::modelChanged, this, [this]() {
        this->view->updateOutput(
            this->model->getEncodedMessage(),
            this->model->getTracks(),
            this->model->getSectors(),
            this->model->getBitOneColor(),
            this->model->getBitZeroColor(),
            this->model->getAddRandomColor()
            );
    });

    connect(model, &Model::modelLanguageChanged, this, [this]() {
        this->view->updateLanguage(this->model->getLanguage());
    });


    this->model->loadFromDefaultValues();
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
void Presenter::onClearMessageChanged(const QString &value){
    model->setClearMessage(value);
}
void Presenter::onOffsetCharChanged(QChar value){
    model->setOffsetChar(value);
}
void Presenter::onLanguageChanged(QString value){
    model->setLanguage(value);
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

void Presenter::onExportJson(const QString& path){
    model->saveToFile(path);
}
void Presenter::onImportJson(const QString& path){
    model->loadFromFile(path);
}
void Presenter::onToggleSizeRequested(int value){
    model->setSize(value);
}
void Presenter::onRandomColorToggled(bool enabled){
    model->setAddRandomColor(enabled);
}

