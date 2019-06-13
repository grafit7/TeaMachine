#include "teamachineengine.h"
#include "createteadialog.h"
#include "tea.h"

#include <QSystemTrayIcon>
#include <QApplication>
#include <QIcon>

TeaMachineEngine::TeaMachineEngine(const QIcon &icon, QObject *parent)
    : QObject(parent)
    ,mCreateTeaDialog{new CreateTeaDialog()}
    ,mTrayIcon{new QSystemTrayIcon(icon, this)}
    ,mAddTeaAction{new QAction(QObject::tr("&Add Tea"), this)}
    ,mTeaMenu{new QMenu(QObject::tr("&Teas"), nullptr)}
{
    connect(mTeaMenu, &QMenu::triggered,this,&TeaMachineEngine::makeTea);
    connect(mAddTeaAction, &QAction::triggered, mCreateTeaDialog, &CreateTeaDialog::show);
    connect(mCreateTeaDialog, &CreateTeaDialog::teaCreated, this, &TeaMachineEngine::pushTea);
}

TeaMachineEngine::~TeaMachineEngine()
{
    qDeleteAll(mTeas);
}

void TeaMachineEngine::run()
{
    QAction *quitAction = new QAction(QObject::tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    QMenu *trayIconMenu = new QMenu();
    trayIconMenu->addMenu(mTeaMenu);
    trayIconMenu->addAction(mAddTeaAction);
    trayIconMenu->addAction(quitAction);
    connect(mTrayIcon, &QSystemTrayIcon::activated, this, &TeaMachineEngine::processTrayIconClick);

    if (mTrayIcon)
    {
        mTrayIcon->setContextMenu(trayIconMenu);
        mTrayIcon->show();
    }
}

void TeaMachineEngine::pushTea(Tea *tea)
{
    if (tea)
    {
        mTeas.push_back(tea);
        connect(tea, &Tea::teaCreated, mTrayIcon,
                static_cast<void (QSystemTrayIcon::*)(const QString&, const QString&,
                                                      QSystemTrayIcon::MessageIcon, int)>(&QSystemTrayIcon::showMessage));
        mTeaMenu->addAction(new QAction(tea->title(), this));
    }
}

void TeaMachineEngine::makeTea(QAction *action)
{
    if (action)
    {
        foreach (Tea *temp, mTeas)
        {
            if(temp->title() == action->text())
            {
                temp->makeTea();
            }
        }
    }
}

void TeaMachineEngine::processTrayIconClick(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Context)
    {
        mTeaMenu->setEnabled(mTeas.size() >= 1);
    }
}
