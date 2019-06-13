#include "teamachineengine.h"
#include "createteadialog.h"
#include "tea.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable())
    {
        QMessageBox::critical(nullptr, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray on this system."));
        return -1000;
    }

    QIcon icon(":/tea-cup.png");
    QApplication::setWindowIcon(icon);
    QApplication::setQuitOnLastWindowClosed(false);

    TeaMachineEngine *teaMachine = new TeaMachineEngine(icon, &a);
    teaMachine->run();

    return a.exec();
}
