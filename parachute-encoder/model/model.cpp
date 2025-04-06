#include "model.h"

Model::Model(){
}

Model::~Model(){
}

QVector<QString> Model::getEncodedMessage() {
    QVector<QString> binary_sequence;

    for (QChar c : this->clear_message)
    {
        binary_sequence.append(QString::number(c.unicode() - this->offset_char.unicode(), 2)
                               .rightJustified(this->size, '0'));
    }
    return binary_sequence;
}

void Model::loadFromDefaultValues() {
    setSize(7);
    setSectors(21);
    setTracks(5);
    setClearMessage("ENSICAEN_RULES");
    setOffsetChar('@');
    setLanguage("en");
    setBitOneColor(QColor(0,0,0));
    setBitZeroColor(QColor(255, 255, 255));
    setAddPattern(false);
    setAddRandomColor(false);
}

void Model::loadFromConfigFile() {

}

void Model::exportConfigFile() {

}


void Model::setSize(int value){
    if(this->size == value) {
        return;
    }

    if(value == 7 || value == 10) {
        this->size = value;
        emit modelChanged();
    }
}

int Model::getSize(){
    return this->size;
}

void Model::setTracks(int value){
    if(this->tracks == value) {
        return;
    }
    this->tracks = value;
    emit modelChanged();
}

int Model::getTracks(){
    return this->tracks;
}

void Model::setSectors(int value){
    if(this->sectors == value) {
        return;
    }
    // Check if the value is a multiple of the size
    if(!(value % this->size)) {
        this->sectors = value;
        emit modelChanged();
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
    emit modelChanged();
}

QString Model::getClearMessage() {
    return this->clear_message;
}

void Model::setOffsetChar(QChar value) {
    if(this->offset_char == value) {
        return;
    }
    this->offset_char = value;
    emit modelChanged();
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
    emit modelLanguageChanged();
}

QString Model::getLanguage() {
    return this->language;
}

void Model::setBitOneColor(QColor value) {
    if(this->bitOneColor == value) {
        return;
    }
    this->bitOneColor = value;
    emit modelChanged();
}
QColor Model::getBitOneColor() {
    return this->bitOneColor;
}
void Model::setBitZeroColor(QColor value) {
    if(this->bitZeroColor == value) {
        return;
    }
    this->bitZeroColor = value;
    emit modelChanged();
}
QColor Model::getBitZeroColor() {
    return this->bitZeroColor;
}
void Model::setAddPattern(bool value) {
    if(this->addPattern == value) {
        return;
    }
    this->addPattern = value;
    emit modelChanged();
}
bool Model::getAddPattern() {
    return this->addPattern;
}
void Model::setAddRandomColor(bool value) {
    if(this->addRandomColor == value) {
        return;
    }
    this->addRandomColor = value;
    emit modelChanged();
}
bool Model::getAddRandomColor() {
    return this->addRandomColor;
}
