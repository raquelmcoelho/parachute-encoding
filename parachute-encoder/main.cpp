#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "view/view.h"
#include "model/model.h"
#include "presenter/presenter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View* view = new View();
    Model* model = new Model();
    Presenter* presenter = new Presenter(model, view);

    view->show();
    return a.exec();
}
