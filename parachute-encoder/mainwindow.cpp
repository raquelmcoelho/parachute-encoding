#include <mainwindow.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Parachute Encoder");
    setGeometry(100, 100, 600, 600);

    parachute_widget = new ParachuteWidget();
    sector_slider = new QSlider(Qt::Horizontal);
    sector_slider->setMinimum(7);
    sector_slider->setMaximum(35);
    sector_slider->setValue(21);
    connect(sector_slider, &QSlider::valueChanged, this, &MainWindow::updateSectors);

    track_slider = new QSlider(Qt::Horizontal);
    track_slider->setMinimum(2);
    track_slider->setMaximum(10);
    track_slider->setValue(5);
    connect(track_slider, &QSlider::valueChanged, this, &MainWindow::updateTracks);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(new QLabel("Setores"));
    layout->addWidget(sector_slider);
    layout->addWidget(new QLabel("Pistas"));
    layout->addWidget(track_slider);
    layout->addWidget(parachute_widget);

    QWidget *container = new QWidget;
    container->setLayout(layout);
    setCentralWidget(container);
}

void MainWindow::updateSectors(int value)
{
    parachute_widget->sectors = value;
    parachute_widget->update();
}

void MainWindow::updateTracks(int value)
{
    parachute_widget->tracks = value;
    parachute_widget->update();
}
