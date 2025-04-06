#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <QChar>
#include <QObject>
#include <QColor>

class Model: public QObject{
    Q_OBJECT

public:
    Model();
    ~Model();

    QVector<QString> getEncodedMessage();

    // TODO
    void loadFromConfigFile();
    void exportConfigFile();
    void loadFromDefaultValues();

    void setSize(int value);
    int getSize();
    void setTracks(int value);
    int getTracks();
    void setSectors(int value);
    int getSectors();
    void setClearMessage(QString value);
    QString getClearMessage();
    void setOffsetChar(QChar value);
    QChar getOffsetChar();
    void setLanguage(QString value);
    QString getLanguage();
    void setBitOneColor(QColor value);
    QColor getBitOneColor();
    void setBitZeroColor(QColor value);
    QColor getBitZeroColor();
    void setAddPattern(bool value);
    bool getAddPattern();
    void setAddRandomColor(bool value);
    bool getAddRandomColor();


private:
    int size;
    int tracks;
    int sectors;
    QString clear_message;
    QChar offset_char;
    QString language;
    QColor bitOneColor;
    QColor bitZeroColor;
    bool addPattern;
    bool addRandomColor;

signals:
    void modelChanged();
    void modelLanguageChanged();
};

#endif // MODEL_H
