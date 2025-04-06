#include "model.h"

Model *Model::getInstance() {
    Model * instance = nullptr;
    if(instance == nullptr) {
        instance = new Model();
    }
    return instance;
}

Model::Model(){
    loadFromDefaultValues();
}

Model::~Model(){
}

void Model::loadFromDefaultValues() {
    setBase(7);
    setSectors(21);
    setTracks(5);
    setClearMessage("ENSICAEN_RULES");
    setOffsetChar('@');
    setLanguage("en");
    // TODO: put to be white and black
    setBitOneColor(QColor(0, 255, 0));
    setBitZeroColor(QColor(255, 0, 0));
    setAddPattern(false);
    setAddRandomColor(false);
}

void Model::loadFromConfigFile() {

}

void Model::exportConfigFile() {

}


void Model::setBase(int value){
    if(this->base == value) {
        return;
    }

    if(value == 7 || value == 10) {
        this->base = value;
        emit baseChanged();
    }
}

int Model::getBase(){
    return this->base;
}

void Model::setTracks(int value){
    if(this->tracks == value) {
        return;
    }
    this->tracks = value;
    emit tracksChanged();
}

int Model::getTracks(){
    return this->tracks;
}

void Model::setSectors(int value){
    if(this->sectors == value) {
        return;
    }
    // Check if the value is a multiple of the base
    if(!(value % this->base)) {
        this->sectors = value;
        emit sectorsChanged();
    }
}

int Model::getSectors(){
    return this->sectors;
}

void Model::setClearMessage(QString value) {
    if(this->clear_message == value) {
        return;
    }
    this->clear_message = value;
    emit clearMessageChanged();
}

QString Model::getClearMessage() {
    return this->clear_message;
}

void Model::setOffsetChar(QChar value) {
    if(this->offset_char == value) {
        return;
    }
    this->offset_char = value;
    emit offsetCharChanged();
}

QChar Model::getOffsetChar() {
    return this->offset_char;
}

void Model::setLanguage(QString value) {
    if(language == value) {
        return;
    }
    if(value == "pt" || value == "fr") {
        this->language = value;
    } else {
        this->language = "en";
    }
    emit languageChanged();
}

QString Model::getLanguage() {
    return this->language;
}

void Model::setBitOneColor(QColor value) {
    if(this->bitOneColor == value) {
        return;
    }
    this->bitOneColor = value;
    emit bitOneColorChanged();
}
QColor Model::getBitOneColor() {
    return this->bitOneColor;
}
void Model::setBitZeroColor(QColor value) {
    if(this->bitZeroColor == value) {
        return;
    }
    this->bitZeroColor = value;
    emit bitZeroColorChanged();
}
QColor Model::getBitZeroColor() {
    return this->bitZeroColor;
}
void Model::setAddPattern(bool value) {
    if(this->addPattern == value) {
        return;
    }
    this->addPattern = value;
    emit addPatternChanged();
}
bool Model::getAddPattern() {
    return this->addPattern;
}
void Model::setAddRandomColor(bool value) {
    if(this->addRandomColor == value) {
        return;
    }
    this->addRandomColor = value;
    emit addRandomColorChanged();
}
bool Model::getAddRandomColor() {
    return this->addRandomColor;
}
