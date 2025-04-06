#include "model.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

Model::Model(){
}

Model::~Model(){
}


QJsonObject Model::toJson() const {
    QJsonObject obj;
    obj["sectors"] = this->sectors;
    obj["tracks"] = this->tracks;
    obj["message"] = this->clearMessage;
    obj["startChar"] = QString(this->offsetChar);
    obj["bitOneColor"] = this->bitOneColor.name(); // Ex: "#ff0000"
    return obj;
}

void Model::fromJson(const QJsonObject& obj) {
    if (obj.contains("sectors")) sectors = obj["sectors"].toInt();
    if (obj.contains("tracks")) tracks = obj["tracks"].toInt();
    if (obj.contains("message")) clearMessage = obj["message"].toString();
    if (obj.contains("startChar")) offsetChar = obj["startChar"].toString().at(0);
    if (obj.contains("bitOneColor")) bitOneColor = QColor(obj["bitOneColor"].toString());

    emit modelChanged();
}

bool Model::saveToFile(const QString& filename) {
    QFile file(filename + ".json");
    if (!file.open(QIODevice::WriteOnly)) return false;
    QJsonDocument doc(toJson());
    file.write(doc.toJson());
    file.close();
    return true;
}

bool Model::loadFromFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) return false;
    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    fromJson(doc.object());
    file.close();
    return true;
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


QVector<QString> Model::getEncodedMessage() {
    QVector<QString> binary_sequence;

    for (QChar c : this->clearMessage)
    {
        binary_sequence.append(QString::number(c.unicode() - this->offsetChar.unicode(), 2)
                               .rightJustified(this->size, '0'));
    }
    return binary_sequence;
}

void Model::setSize(int value){
    if(this->size == value) {
        return;
    }

    if(value == 7 || value == 10) {
        this->size = value;
        setSectors(this->sectors);
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
    int adjusted = (value / this->size) * this->size;
    if (adjusted < this->size) adjusted = this->size;
    this->sectors = adjusted;
    emit modelChanged();
}

int Model::getSectors(){
    return this->sectors;
}

void Model::setClearMessage(QString value) {
    if(this->clearMessage == value) {
        return;
    }
    this->clearMessage = value;
    emit modelChanged();
}

QString Model::getClearMessage() {
    return this->clearMessage;
}

void Model::setOffsetChar(QChar value) {
    if(this->offsetChar == value) {
        return;
    }
    this->offsetChar = value;
    emit modelChanged();
}

QChar Model::getOffsetChar() {
    return this->offsetChar;
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
