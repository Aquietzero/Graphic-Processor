#include <QApplication>
#include "ui/SimpleDIP.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    SimpleDIP *dip = new SimpleDIP;
    dip->show();

    return app.exec();
}
