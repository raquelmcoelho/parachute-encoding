QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    model/model.cpp \
    presenter/presenter.cpp \
    view/parachutewidget.cpp \
    view/pointswidget.cpp \
    view/view.cpp

HEADERS += \
    mainwindow.h \
    model/model.h \
    presenter/presenter.h \
    view/parachutewidget.h \
    view/pointswidget.h \
    view/view.h

FORMS +=

TRANSLATIONS += \
    translations/parachute_encoder_en.ts \
    translations/parachute_encoder_fr.ts \
    translations/parachute_encoder_pt.ts


CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
