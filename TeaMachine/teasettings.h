#ifndef TEASETTINGS_H
#define TEASETTINGS_H

#include <QVector>

#include <memory>

class Tea;
class QJsonObject;

class TeaSettings
{
public:
    TeaSettings();
    virtual ~TeaSettings();

    QVector<Tea*> listOfTeas() const;
    void saveListOfTeas(const QVector<Tea*> &listOfTeas);

private:
    QString settingsFilePath() const;

    void load();
    void save();

private:
    QJsonObject* mSettings;
};

#endif // TEASETTINGS_H
