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
#include "view/parachutewidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Parachute Encoder");
    resize(800, 600);

    parachute_widget = new ParachuteWidget();
    sector_slider = new QSlider(Qt::Horizontal);
    sector_slider->setMinimum(7);
    sector_slider->setMaximum(35);
    sector_slider->setValue(21);
    connect(sector_slider, &QSlider::valueChanged, this, &MainWindow::updateSectors);;

    QLabel* trapezoidLabel = new QLabel("Trapezoides");
    trapezoidLabel->setMinimumSize(300, 300);
    trapezoidLabel->setFrameShape(QFrame::Box);
    trapezoidLabel->setAlignment(Qt::AlignCenter);

    QHBoxLayout* imageLayout = new QHBoxLayout;
    imageLayout->addWidget(parachute_widget);
    imageLayout->addWidget(trapezoidLabel);

    // Sliders
    sector_slider = new QSlider(Qt::Horizontal);
    sector_slider->setRange(7, 35);
    sector_slider->setValue(21);
    connect(sector_slider, &QSlider::valueChanged, this, &MainWindow::updateSectors);

    track_slider = new QSlider(Qt::Horizontal);
    track_slider->setRange(2, 10);
    track_slider->setValue(5);
    connect(track_slider, &QSlider::valueChanged, this, &MainWindow::updateTracks);

    // Down-site controls
    QLineEdit* messageInput = new QLineEdit;
    messageInput->setPlaceholderText("Insira a mensagem binária (ex: 010101)");

    QPushButton* colorButton = new QPushButton("Escolher Cor do Bit 1");
    QPushButton* encodeButton = new QPushButton("Codificar");

    connect(colorButton, &QPushButton::clicked, this, [this]() {
        QColor chosen = QColorDialog::getColor(bitOneColor, this, "Escolha a cor para o bit 1");
        if (chosen.isValid()) {
            bitOneColor = chosen;
            parachute_widget->setBitOneColor(chosen);
        }
    });

    connect(encodeButton, &QPushButton::clicked, this, [messageInput]() {
        QString message = messageInput->text();
        QMessageBox::information(nullptr, "Mensagem", "Mensagem binária: " + message);
    });

    QHBoxLayout* controlsLayout = new QHBoxLayout;
    controlsLayout->addWidget(messageInput);
    controlsLayout->addWidget(colorButton);
    controlsLayout->addWidget(encodeButton);

    // Layout final
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(imageLayout);
    layout->addWidget(new QLabel("Setores"));
    layout->addWidget(sector_slider);
    layout->addWidget(new QLabel("Pistas"));
    layout->addWidget(track_slider);
    layout->addLayout(controlsLayout);

    QWidget* container = new QWidget;
    container->setLayout(layout);
    setCentralWidget(container);

    // Menu
    QMenu* fileMenu = menuBar()->addMenu("Arquivo");
    QAction* exitAction = new QAction("Sair", this);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    fileMenu->addAction(exitAction);

    QMenu* helpMenu = menuBar()->addMenu("Ajuda");
    QAction* aboutAction = new QAction("Sobre", this);
    connect(aboutAction, &QAction::triggered, this, []() {
        QMessageBox::about(nullptr, "Sobre", "Parachute Encoder v1.0\nDesenvolvido por Vinicius.");
    });
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

