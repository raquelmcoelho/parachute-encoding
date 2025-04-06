#include "parachutemodel.h"

ParachuteModel *ParachuteModel::getInstance() {
    ParachuteModel * instance = nullptr;
    if(instance == nullptr) {
        instance = new ParachuteModel();
    }
    return instance;
}

ParachuteModel::ParachuteModel(){
    loadFromDefaultValues();
}

ParachuteModel::~ParachuteModel(){
}

void ParachuteModel::loadFromDefaultValues() {
    setBase(7);
    setSectors(21);
    setTracks(5);
    setClearMessage("ENSICAEN_RULES");
    setOffsetChar('@');
}

void ParachuteModel::loadFromConfigFile() {

}

void ParachuteModel::setBase(int value){
    if(value == 7 || value == 10) {
        this->base = value;
        emit baseChanged();
    }
}

void ParachuteModel::setTracks(int value){
    this->tracks = value;
    emit tracksChanged();
}

void ParachuteModel::setSectors(int value){
    if(!(value % this->base)) {
        this->sectors = value;
        emit sectorsChanged();
    }
}

void ParachuteModel::setClearMessage(QString value) {
    this->clear_message = value;
    emit clearMessageChanged();
}

void ParachuteModel::setOffsetChar(QChar value) {
    this->offset_char = value;
    emit offsetCharChanged();
}

int ParachuteModel::getBase(){
    return this->base;
}

int ParachuteModel::getTracks(){
    return this->tracks;
}

int ParachuteModel::getSectors(){
    return this->sectors;
}

QString ParachuteModel::getClearMessage() {
    return this->clear_message;
}

QChar ParachuteModel::getOffsetChar() {
    return this->offset_char;
}

