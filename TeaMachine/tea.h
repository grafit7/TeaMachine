#ifndef TEA_H
#define TEA_H

#include <QSystemTrayIcon>
#include <QObject>

class Tea : public QObject
{
    Q_OBJECT
public:
    explicit Tea(const QString &title, const QString &description, int minutes = 0,
                 int timerIdentifier = 0,
                 QObject *parent = nullptr);

    QString title() const;
    void setTitle(const QString &title);

    QString description() const;
    void setDescription(const QString &description);

    int timeInMinutes() const;
    void setTimeInMinutes(int timeInMinutes);

    int timerIdentifier() const;
    void makeTea();

protected:
     void timerEvent(QTimerEvent *event) override;

signals:
     void teaCreated(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::Information, int millisecondsTimeoutHint = 10000);

private:
    QString mTitle;
    QString mDescription;
    int mTimeInMinutes;
    int mTimerIdentifier;
};

#endif // TEA_H
