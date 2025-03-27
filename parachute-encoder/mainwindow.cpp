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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("Parachute Encoder"));
    resize(800, 600);

    QHBoxLayout* imageLayout = new QHBoxLayout;


    QWidget* code_container = new QWidget();
    QHBoxLayout* containerLayout = new QHBoxLayout(code_container);

    // Adicionar o parachute_widget primeiro
    parachute_widget = new ParachuteWidget();
    parachute_widget->setMinimumSize(300, 300); // Garante que ele tenha um tamanho fixo
    containerLayout->addWidget(parachute_widget);

    // Criar a área de rolagem e adicionar o PointsWidget
    points_widget = new PointsWidget();
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidget(points_widget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setMinimumWidth(300); // Evita que ele tome todo o espaço
    containerLayout->addWidget(scrollArea);

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
        }
    });

    connect(encodeButton, &QPushButton::clicked, this, [this]() {
        QString message = messageInput->text();
        parachute_widget->setMessage(message);
    });

    connect(applyCharButton, &QPushButton::clicked, this, [this]() {
        QString ch = startCharInput->text();
        if (!ch.isEmpty()) {
            parachute_widget->setStartChar(ch.at(0));
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
        QMessageBox::about(nullptr, tr("Sobre"), tr("Parachute Encoder v1.0\nDesenvolvido por Vinicius."));
    });
    helpMenu->addAction(aboutAction);
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
