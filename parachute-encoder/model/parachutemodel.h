#ifndef PARACHUTEMODEL_H
#define PARACHUTEMODEL_H

#include <QString>
#include <QChar>
#include <QObject>

class ParachuteModel: public QObject{
    Q_OBJECT
    Q_PROPERTY(int base READ getBase WRITE setBase NOTIFY baseChanged FINAL)
    Q_PROPERTY(int tracks READ getTracks WRITE setTracks NOTIFY tracksChanged FINAL)
    Q_PROPERTY(int sectors READ getSectors WRITE setSectors NOTIFY sectorsChanged FINAL)
    Q_PROPERTY(QString clearMessage READ getClearMessage WRITE setClearMessage NOTIFY clearMessageChanged FINAL)
    Q_PROPERTY(QChar offsetChar READ getOffsetChar WRITE setOffsetChar NOTIFY offsetCharChanged FINAL)

public:
    ~ParachuteModel();
    ParachuteModel *getInstance();
    void setBase(int value);
    int getBase();
    void setTracks(int value);
    int getTracks();
    void setSectors(int value);
    int getSectors();
    QString getClearMessage();
    void setClearMessage(QString value);
    QChar getOffsetChar();
    void setOffsetChar(QChar value);

    // TODO
    void loadFromConfigFile();
    void exportConfigFile();
    void loadFromDefaultValues();

private:
    ParachuteModel();
    int base;
    int tracks;
    int sectors;
    QString clear_message;
    QChar offset_char;

signals:
    void baseChanged();
    void tracksChanged();
    void sectorsChanged();
    void clearMessageChanged();
    void offsetCharChanged();
};

#endif // PARACHUTEMODEL_H
