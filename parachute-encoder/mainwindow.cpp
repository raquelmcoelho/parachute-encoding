#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QColorDialog>
#include <QMessageBox>
#include <QTranslator>
#include <QLocale>
#include <QApplication>
#include <QScrollArea>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("Parachute Encoder"));
    resize(800, 600);

    QHBoxLayout* imageLayout = new QHBoxLayout;

    // Criar um layout horizontal para os widgets
    QWidget* code_container = new QWidget();
    QHBoxLayout* containerLayout = new QHBoxLayout(code_container);

    // Criar um splitter para dividir os widgets em partes iguais
    QSplitter* splitter = new QSplitter(Qt::Horizontal);
    splitter->setChildrenCollapsible(false); // Evita que um suma completamente

    // Adicionar o parachute_widget primeiro
    parachute_widget = new ParachuteWidget();
    parachute_widget->setMinimumSize(300, 300); // Garante que tenha tamanho mínimo

    // Criar a área de rolagem e adicionar o PointsWidget
    points_widget = new PointsWidget();
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidget(points_widget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setMinimumWidth(300); // Evita que tome todo o espaço

    // Adicionar ambos ao splitter
    splitter->addWidget(parachute_widget);
    splitter->addWidget(scrollArea);

    // Definir pesos para garantir a divisão 50/50
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);

    // Adicionar o splitter ao layout principal
    containerLayout->addWidget(splitter);

    // Adicionar esse container ao layout principal
    imageLayout->addWidget(code_container);

    // Sliders
    sector_slider = new QSlider(Qt::Horizontal);
    sector_slider->setRange(7, 35);
    sector_slider->setValue(21);
    connect(sector_slider, &QSlider::valueChanged, this, &MainWindow::updateSectors);

    track_slider = new QSlider(Qt::Horizontal);
    track_slider->setRange(2, 10);
    track_slider->setValue(5);
    connect(track_slider, &QSlider::valueChanged, this, &MainWindow::updateTracks);

    // Entrada de mensagem
    messageInput = new QLineEdit;
    messageInput->setPlaceholderText(tr("Insira a mensagem (ex: ENSICAEN)"));

    // Entrada de caractere inicial
    startCharInput = new QLineEdit;
    startCharInput->setPlaceholderText(tr("Caractere inicial (padrão: @)"));
    startCharInput->setMaxLength(1);

    // Botões
    QPushButton* colorButton = new QPushButton(tr("Escolher Cor do Bit 1"));
    QPushButton* encodeButton = new QPushButton(tr("Codificar"));
    QPushButton* applyCharButton = new QPushButton(tr("Aplicar caractere"));

    // Conexões
    connect(colorButton, &QPushButton::clicked, this, [this]() {
        QColor chosen = QColorDialog::getColor(bitOneColor, this, tr("Escolha a cor para o bit 1"));
        if (chosen.isValid()) {
            bitOneColor = chosen;
            parachute_widget->setBitOneColor(chosen);
            points_widget->setBitOneColor(bitOneColor);
        }
    });

    connect(encodeButton, &QPushButton::clicked, this, [this]() {
        QString message = messageInput->text();
        parachute_widget->setMessage(message);
        points_widget->setMessage(message);
    });

    connect(applyCharButton, &QPushButton::clicked, this, [this]() {
        QString ch = startCharInput->text();
        if (!ch.isEmpty()) {
            parachute_widget->setStartChar(ch.at(0));
            points_widget->setStartChar(ch.at(0));
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


    // Layout final
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(imageLayout);
    layout->addWidget(new QLabel(tr("Setores")));
    layout->addWidget(sector_slider);
    layout->addWidget(new QLabel(tr("Pistas")));
    layout->addWidget(track_slider);
    layout->addLayout(controlsLayout);
    layout->addLayout(charLayout);

    QWidget* container = new QWidget;
    container->setLayout(layout);
    setCentralWidget(container);

    // Menu
    QMenu* fileMenu = menuBar()->addMenu(tr("Arquivo"));
    QAction* exitAction = new QAction(tr("Sair"), this);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    fileMenu->addAction(exitAction);

    QMenu* languageMenu = menuBar()->addMenu(tr("Idioma"));
    QAction* englishAction = new QAction("English", this);
    QAction* portugueseAction = new QAction("Português", this);
    QAction* frenchAction = new QAction("Français", this);

    connect(englishAction, &QAction::triggered, this, [this]() { changeLanguage("en"); });
    connect(portugueseAction, &QAction::triggered, this, [this]() { changeLanguage("pt"); });
    connect(frenchAction, &QAction::triggered, this, [this]() { changeLanguage("fr"); });

    languageMenu->addAction(englishAction);
    languageMenu->addAction(portugueseAction);
    languageMenu->addAction(frenchAction);

    QMenu* helpMenu = menuBar()->addMenu(tr("Ajuda"));
    QAction* aboutAction = new QAction(tr("Sobre"), this);
    connect(aboutAction, &QAction::triggered, this, []() {
        QMessageBox::about(nullptr, tr("Sobre"), tr("Parachute Encoder v1.0\nDesenvolvido por Raquel e Vinicius."));
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

    QString mainWindowStyle = R"(
        QWidget {
            background: qlineargradient(
                spread:pad, x1:0, y1:0, x2:1, y2:1,
                stop:0 #FFE4E1, stop:1 #FFB6C1
            ); /* Gradiente de rosa claro */
        }
    )";
    this->setStyleSheet(mainWindowStyle);


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


}

void MainWindow::updateSectors(int value)
{
    int adjusted = (value / 7) * 7;
    if (adjusted < 7) adjusted = 7;

    sector_slider->blockSignals(true);
    sector_slider->setValue(adjusted);
    sector_slider->blockSignals(false);

    parachute_widget->sectors = adjusted;
    parachute_widget->update();
}

void MainWindow::updateTracks(int value)
{
    parachute_widget->tracks = value;
    parachute_widget->update();
}

void MainWindow::changeLanguage(const QString& locale)
{
    static QTranslator translator;
    qApp->removeTranslator(&translator);
    if (translator.load(":/translations/parachute_" + locale + ".ts")) {
        qApp->installTranslator(&translator);
    }
    setWindowTitle(tr("Parachute Encoder"));
}
