#include "view.h"

View::~View() {}

#include <QMenuBar>
// #include <QMenu>
// #include <QAction>
// #include <QLabel>
// #include <QVBoxLayout>
// #include <QHBoxLayout>
// #include <QPushButton>
// #include <QLineEdit>
#include <QColorDialog>
#include <QMessageBox>
// #include <QLocale>
// #include <QApplication>
#include <QScrollArea>
#include <QSplitter>
#include <QFileDialog>

#define STEP_SECTOR 7
#define MINIMUM_SIZE 300

View::View(QWidget *parent) : QMainWindow(parent)
{
    this->translator = new QTranslator(this);

    setWindowTitle(tr("Parachute Encoder"));
    resize(800, 600);

    QHBoxLayout* imageLayout = new QHBoxLayout;
    QWidget* code_container = new QWidget();
    QHBoxLayout* containerLayout = new QHBoxLayout(code_container);

    // Split equally both representations
    QSplitter* splitter = new QSplitter(Qt::Horizontal);
    splitter->setChildrenCollapsible(false); // Avoid hiding widgets

    parachute_widget = new ParachuteWidget();
    parachute_widget->setMinimumSize(MINIMUM_SIZE, MINIMUM_SIZE);

    // Scroll Area in case of the message being too big
    points_widget = new PointsWidget();
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidget(points_widget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setMinimumWidth(MINIMUM_SIZE);

    splitter->addWidget(parachute_widget);
    splitter->addWidget(scrollArea);

    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);

    containerLayout->addWidget(splitter);
    imageLayout->addWidget(code_container);

    // Sliders
    sector_slider = new QSlider(Qt::Horizontal);
    sector_slider->setRange(7, 35);
    sector_slider->setValue(21);
    connect(sector_slider, &QSlider::valueChanged, this, [this](int value) {
        // TODO: get from presenter the step sector
        int adjusted = (value / STEP_SECTOR) * STEP_SECTOR;
        if (adjusted < STEP_SECTOR) adjusted = STEP_SECTOR;

        sector_slider->blockSignals(true);
        sector_slider->setValue(adjusted);
        sector_slider->blockSignals(false);

        emit sectorsChanged(value);
    });

    track_slider = new QSlider(Qt::Horizontal);
    track_slider->setRange(2, 10);
    track_slider->setValue(5);
    connect(track_slider, &QSlider::valueChanged, this, [this](int value){
        emit tracksChanged(value);
    });

    messageInput = new QLineEdit;
    messageInput->setPlaceholderText(tr("Insert the message (default: ENSICAEN_RULES)"));

    // Character to be the 'offset'
    startCharInput = new QLineEdit;
    startCharInput->setPlaceholderText(tr("Offset char (default: @)"));
    startCharInput->setMaxLength(1);

    // Buttons
    colorButton = new QPushButton(tr("Choose Bit 1 color"));
    encodeButton = new QPushButton(tr("Encode"));
    applyCharButton = new QPushButton(tr("Apply char"));

    // Connections
    connect(colorButton, &QPushButton::clicked, this, [this]() {
        QColor bitOneColor;
        QColor chosen = QColorDialog::getColor(bitOneColor, this, tr("Choose Bit 1 color"));
        if (chosen.isValid()) {
            bitOneColor = chosen;
            emit bitOneColorChanged(chosen);
        }
    });

    connect(encodeButton, &QPushButton::clicked, this, [this]() {
        QString message = messageInput->text();
        emit clearMessageChanged(message);
    });

    connect(applyCharButton, &QPushButton::clicked, this, [this]() {
        QString ch = startCharInput->text();
        if (!ch.isEmpty()) {
            emit offsetCharChanged(ch.at(0));
        }
    });


    // Layouts de controle
    QHBoxLayout* controlsLayout = new QHBoxLayout;
    controlsLayout->addWidget(messageInput);
    controlsLayout->addWidget(colorButton);
    controlsLayout->addWidget(encodeButton);

    QHBoxLayout* charLayout = new QHBoxLayout;
    charLayout->addWidget(startCharInput);
    charLayout->addWidget(applyCharButton);


    randomColorCheck = new QCheckBox(tr("Random color for bits"));
    connect(randomColorCheck, &QCheckBox::toggled, this, [this](bool checked){
        emit randomColorToggled(checked);
    });

    sizeBitCheck = new QCheckBox(tr("Toggle 7/10 Tracks"));
    connect(sizeBitCheck, &QCheckBox::clicked, this, [this](bool checked){
        emit toggleTrackRequested(checked ? 10 : 7);
    });

    QHBoxLayout* checkBoxes = new QHBoxLayout;
    checkBoxes->addWidget(randomColorCheck);
    checkBoxes->addWidget(sizeBitCheck);

    // Final layout
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(imageLayout);
    sectors_label = new QLabel(tr("Sectors"));
    tracks_label = new QLabel(tr("Tracks"));
    layout->addWidget(sectors_label);
    layout->addWidget(sector_slider);
    layout->addWidget(tracks_label);
    layout->addWidget(track_slider);
    layout->addLayout(controlsLayout);
    layout->addLayout(charLayout);
    layout->addLayout(checkBoxes);

    QWidget* container = new QWidget;
    container->setLayout(layout);
    setCentralWidget(container);

    // Menu
    fileMenu = menuBar()->addMenu(tr("File"));
    exitAction = new QAction(tr("Quit"), this);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);

    exportAction = new QAction(tr("Export..."), this);

    connect(exportAction, &QAction::triggered, this, [this]() {
        QString path = QFileDialog::getSaveFileName(this, tr("Export configuration"), "", tr("JSON Files (*.json)"));
        if (!path.isEmpty()) emit exportJson(path);
    });

    importAction = new QAction(tr("Import..."), this);
    connect(importAction, &QAction::triggered, this, [this]() {
        QString path = QFileDialog::getOpenFileName(this, tr("Import configuration"), "", tr("JSON Files (*.json)"));
        if (!path.isEmpty()) emit importJson(path);
    });

    importAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    exportAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    exitAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));

    fileMenu->insertAction(exitAction, exportAction);
    fileMenu->insertAction(exitAction, importAction);
    fileMenu->addAction(exitAction);

    languageMenu = menuBar()->addMenu(tr("Language"));
    englishAction = new QAction("English", this);
    portugueseAction = new QAction("Português", this);
    frenchAction = new QAction("Français", this);


    connect(englishAction, &QAction::triggered, this, [this]() { emit languageChanged("en"); });
    connect(portugueseAction, &QAction::triggered, this, [this]() { emit languageChanged("pt"); });
    connect(frenchAction, &QAction::triggered, this, [this]() { emit languageChanged("fr"); });

    languageMenu->addAction(englishAction);
    languageMenu->addAction(portugueseAction);
    languageMenu->addAction(frenchAction);

    helpMenu = menuBar()->addMenu(tr("Help"));
    aboutAction = new QAction(tr("About"), this);
    connect(aboutAction, &QAction::triggered, this, []() {
        QMessageBox::about(nullptr, tr("About"), tr("Parachute Encoder v1.0\nDeveloped by Raquel and Vinicius."));
    });
    helpMenu->addAction(aboutAction);

    // CSS
    QString sliderStyle = R"(
        QSlider::groove:horizontal {
            border: 2px solid #FFC0CB; /* Rosa claro */
            height: 10px;
            background: #FFE4E1; /* Fundo rosa pastel */
            border-radius: 5px;
        }

        QSlider::handle:horizontal {
            background: #FF69B4; /* Rosa mais vibrante */
            border: 2px solid white;
            width: 20px;
            height: 20px;
            margin: -5px 0;
            border-radius: 10px;
        }

        QSlider::handle:horizontal:hover {
            background: #FF1493; /* Rosa ainda mais vibrante ao passar o mouse */
        }
    )";

    // Aplicar esse estilo aos sliders
    sector_slider->setStyleSheet(sliderStyle);
    track_slider->setStyleSheet(sliderStyle);

    QString inputStyle = R"(
        QLineEdit {
            background: #FFF0F5; /* Fundo rosa claro */
            border: 2px solid #FF69B4; /* Borda rosa vibrante */
            border-radius: 10px; /* Bordas arredondadas */
            padding: 5px;
            font-size: 16px;
            color: #333333; /* Texto escuro para contraste */
        }

        QLineEdit:focus {
            border: 2px solid #FF1493; /* Rosa mais forte quando focado */
            background: #FFD1DC; /* Fundo levemente mais escuro */
        }
    )";

    messageInput->setStyleSheet(inputStyle);
    startCharInput->setStyleSheet(inputStyle);

    QString buttonStyle = R"(
        QPushButton {
            background-color: #FFB6C1; /* Rosa claro */
            border: 2px solid #FF69B4; /* Borda rosa vibrante */
            border-radius: 10px; /* Cantos arredondados */
            padding: 8px 15px;
            font-size: 16px;
            font-weight: bold;
            color: white;
        }

        QPushButton:hover {
            background-color: #FF69B4; /* Rosa mais forte ao passar o mouse */
        }

        QPushButton:pressed {
            background-color: #FF1493; /* Rosa ainda mais forte ao clicar */
        }
    )";

    colorButton->setStyleSheet(buttonStyle);
    encodeButton->setStyleSheet(buttonStyle);
    applyCharButton->setStyleSheet(buttonStyle);

    QString labelStyle = R"(
        QLabel {
            font-size: 18px;
            font-weight: bold;
            color: #D63384; /* Rosa escuro elegante */
            background: transparent;
            padding: 4px;
        }
    )";

    for (QLabel* label : findChildren<QLabel*>()) {
        label->setStyleSheet(labelStyle);
    }

    QString menuBarStyle = R"(
        QMenuBar {
            background: #FFB6C1; /* Rosa clarinho */
            padding: 6px;
            font-size: 16px;
            color: #ffffff;
            border-bottom: 2px solid #D63384;
        }
        QMenuBar::item {
            padding: 6px 12px;
            spacing: 3px;
            background: transparent;
            color: white;
            border-radius: 6px;
        }
        QMenuBar::item:selected {
            background: #D63384; /* Rosa escuro */
        }
        QMenu {
            background: #FFD1DC; /* Rosa pastel */
            border: 1px solid #D63384;
            border-radius: 8px;
        }
        QMenu::item {
            padding: 8px 12px;
            font-size: 14px;
            color: #D63384;
            border-radius: 6px;
        }
        QMenu::item:selected {
            background: #D63384;
            color: white;
        }
    )";

    menuBar()->setStyleSheet(menuBarStyle);

    QString ViewStyle = R"(
        QWidget {
            background: qlineargradient(
                spread:pad, x1:0, y1:0, x2:1, y2:1,
                stop:0 #FFE4E1, stop:1 #FFB6C1
            ); /* Gradiente de rosa claro */
        }
    )";
    this->setStyleSheet(ViewStyle);


    QString scrollStyle = R"(
        QScrollBar:vertical {
            border: none;
            background: #FFD1DC;
            width: 10px;
            margin: 2px 2px 2px 2px;
            border-radius: 5px;
        }
        QScrollBar::handle:vertical {
            background: #D63384;
            min-height: 20px;
            border-radius: 5px;
        }
        QScrollBar::handle:vertical:hover {
            background: #C2185B;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            background: none;
            border: none;
        }

        QScrollBar:horizontal {
            border: none;
            background: #FFD1DC;
            height: 10px;
            margin: 2px 2px 2px 2px;
            border-radius: 5px;
        }
        QScrollBar::handle:horizontal {
            background: #D63384;
            min-width: 20px;
            border-radius: 5px;
        }
        QScrollBar::handle:horizontal:hover {
            background: #C2185B;
        }
        QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
            background: none;
            border: none;
        }
    )";

    scrollArea->setStyleSheet(scrollStyle);

    QString checkBoxStyle = R"(
    QCheckBox {
        spacing: 10px;
        font-size: 16px;
        font-weight: bold;
        color: #D63384;
    }

    QCheckBox::indicator {
        width: 20px;
        height: 20px;
        border: 2px solid #FF69B4;
        border-radius: 6px;
        background: #FFF0F5;
    }

    QCheckBox::indicator:checked {
        background-color: #FF69B4;
        image: url(:/icons/check-white.png); /* se quiser um ícone de check personalizado */
    }

    QCheckBox::indicator:hover {
        border: 2px solid #FF1493;
    }
)";
    randomColorCheck->setStyleSheet(checkBoxStyle);
    sizeBitCheck->setStyleSheet(checkBoxStyle);
}


void View::updateOutput(QVector<QString> encoded_bits, int tracks, int sectors, QColor colorOneBit, QColor colorZeroBit, bool randomColor) {
    parachute_widget->updateView(encoded_bits, tracks, sectors, colorOneBit, colorZeroBit, randomColor);
    points_widget->updateView(encoded_bits, colorOneBit, colorZeroBit, randomColor);
}

void View::updateLanguage(QString locale) {
    QString path(qApp->applicationDirPath() + "/.qm");
    qApp->removeTranslator(translator);
    if (translator->load("parachute_encoder_" + locale + ".qm", path)) {
        qApp->installTranslator(translator);
    }

    setWindowTitle(QObject::tr("Parachute Encoder"));
    messageInput->setPlaceholderText(
        QObject::tr("Insert the message (default: ENSICAEN_RULES)"));
    startCharInput->setPlaceholderText(QObject::tr("Offset char (default: @)"));
    colorButton->setText(QObject::tr("Choose Bit 1 color"));
    encodeButton->setText(QObject::tr("Encode"));
    applyCharButton->setText(QObject::tr("Apply char"));
    sectors_label->setText(QObject::tr("Sectors"));
    tracks_label->setText(QObject::tr("Tracks"));
    exitAction->setText(QObject::tr("Quit"));
    fileMenu->setTitle(QObject::tr("File"));
    languageMenu->setTitle(QObject::tr("Language"));
    helpMenu->setTitle(QObject::tr("Help"));
    aboutAction->setText(QObject::tr("About"));
}
