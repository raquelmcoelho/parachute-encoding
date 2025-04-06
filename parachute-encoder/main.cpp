#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "view/view.h"
#include "model/model.h"
#include "presenter/presenter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model* model = new Model();
    View* view = new View();
    Presenter* presenter = new Presenter(model, view);

    view->show();
    return a.exec();
}
