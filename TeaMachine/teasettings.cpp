#include "teasettings.h"

#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardPaths>

#include "tea.h"

//{
//    "teas": [
//        {
//            "name": "tea",
//            "description": "Veeery tasty!",
//            "time": 3
//        },
//        {
//            "name": "tea2",
//            "description": "Veeery tasty!",
//            "time": 3
//        }
//    ]
//}

static const QString cKeyTeaName{"name"};
static const QString cKeyTeaDescription{"description"};
static const QString cKeyTeaTime{"time"}; // minutes
static const QString cKeyListTeas{"teas"};

TeaSettings::TeaSettings()
    : mSettings{new QJsonObject()}
{
    load();
}

TeaSettings::~TeaSettings()
{
    delete mSettings;
}

QVector<Tea *> TeaSettings::listOfTeas() const
{
    QVector<Tea *> rResult;

    auto teasArrayJson = mSettings->value(cKeyListTeas).toArray();

    for (int teaIndex = 0; teaIndex < teasArrayJson.size(); ++teaIndex)
    {
        const auto nextTeaObject = teasArrayJson[teaIndex].toObject();

        const auto title = nextTeaObject.value(cKeyTeaName).toString();
        const auto description = nextTeaObject.value(cKeyTeaDescription).toString();
        const auto timeInMunutes = nextTeaObject.value(cKeyTeaTime).toInt();

        Tea *tea = new Tea(title, description, timeInMunutes);
        rResult << tea;
    }

    return rResult;
}

void TeaSettings::saveListOfTeas(const QVector<Tea *> &listOfTeas)
{
    QJsonArray teasJsonArray;

    for (auto tea: listOfTeas)
    {
        if (!tea)
        {
            continue;
        }

        QJsonObject teaJsonObject;
        teaJsonObject.insert(cKeyTeaName, tea->title());
        teaJsonObject.insert(cKeyTeaDescription, tea->description());
        teaJsonObject.insert(cKeyTeaTime, tea->timeInMinutes());

        teasJsonArray.append(teaJsonObject);
    }

    mSettings->insert(cKeyListTeas, teasJsonArray);

    save();
}

QString TeaSettings::settingsFilePath() const
{
    return QString("%1/settings.json")
            .arg(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
}

void TeaSettings::load()
{
    const QString settingsPath = settingsFilePath();
    qDebug()<<settingsPath;
    QFile settingsFile(settingsPath);

    if (!settingsFile.open(QIODevice::ReadOnly))
    {
        qWarning("Could not read settings file.");
        return;
    }

    const QByteArray settingsData = settingsFile.readAll();
    settingsFile.close();

    QJsonDocument json = QJsonDocument::fromJson(settingsData);
    if (json.isObject())
    {
        *mSettings = json.object();
    }
    else
    {
        qWarning("Cannot read settings data.");
    }
}

void TeaSettings::save()
{
    const QString settingsPath = settingsFilePath();

    QFile settingsFile(settingsPath);

    if (!settingsFile.open(QIODevice::WriteOnly))
    {
        qWarning("Could not write to settings file.");
        return;
    }

    QJsonDocument json;
    json.setObject(*mSettings);

    const QByteArray settingsData = json.toJson(QJsonDocument::Indented);
    settingsFile.write(settingsData);
    settingsFile.close();
}
