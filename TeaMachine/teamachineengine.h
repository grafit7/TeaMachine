#ifndef TEAMACHINEENGINE_H
#define TEAMACHINEENGINE_H

#include <QSystemTrayIcon>
#include <QObject>
#include <QVector>
#include <QMenu>

class QSystemTrayIcon;
class CreateTeaDialog;
class Tea;

class TeaMachineEngine : public QObject
{
    Q_OBJECT
public:
    explicit TeaMachineEngine(const QIcon &icon, QObject *parent = nullptr);
    ~TeaMachineEngine() override;
    void run();

private slots:
    void pushTea(Tea *tea);
    void makeTea(QAction * action);
    void processTrayIconClick(QSystemTrayIcon::ActivationReason reason);

private:
    CreateTeaDialog *mCreateTeaDialog;
    QSystemTrayIcon *mTrayIcon;
    QAction *mAddTeaAction;
    QMenu *mTeaMenu;
    QVector<Tea*> mTeas;
};

#endif // TEAMACHINEENGINE_H
