#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <QChar>
#include <QObject>
#include <QColor>

class Model: public QObject{
    Q_OBJECT
    Q_PROPERTY(int base READ getBase WRITE setBase NOTIFY baseChanged FINAL)
    Q_PROPERTY(int tracks READ getTracks WRITE setTracks NOTIFY tracksChanged FINAL)
    Q_PROPERTY(int sectors READ getSectors WRITE setSectors NOTIFY sectorsChanged FINAL)
    Q_PROPERTY(QString clearMessage READ getClearMessage WRITE setClearMessage NOTIFY clearMessageChanged FINAL)
    Q_PROPERTY(QChar offsetChar READ getOffsetChar WRITE setOffsetChar NOTIFY offsetCharChanged FINAL)
    Q_PROPERTY(QString language READ getLanguage WRITE setLanguage NOTIFY languageChanged FINAL)
    Q_PROPERTY(QColor bitOneColor READ getBitOneColor WRITE setBitOneColor NOTIFY bitOneColorChanged FINAL)
    Q_PROPERTY(QColor bitZeroColor READ getBitZeroColor WRITE setBitZeroColor NOTIFY bitZeroColorChanged FINAL)
    Q_PROPERTY(bool addPattern READ getAddPattern WRITE setAddPattern NOTIFY addPatternChanged FINAL)
    Q_PROPERTY(bool addRandomColor READ getAddRandomColor WRITE setAddRandomColor NOTIFY addRandomColorChanged FINAL)
    

public:
    ~Model();
    Model *getInstance();
    // TODO
    void loadFromConfigFile();
    void exportConfigFile();
    void loadFromDefaultValues();

    void setBase(int value);
    int getBase();
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
    Model();
    int base;
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
    void baseChanged();
    void tracksChanged();
    void sectorsChanged();
    void clearMessageChanged();
    void offsetCharChanged();
    void languageChanged();
    void bitOneColorChanged();
    void bitZeroColorChanged();
    void addPatternChanged();
    void addRandomColorChanged();

};

#endif // MODEL_H
