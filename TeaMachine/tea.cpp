#include "tea.h"

#include <QTimerEvent>

#ifdef QT_DEBUG
const int cMilisecondsInMinute = 10000;
#else
const int cMilisecondsInMinute = 60000;
#endif

Tea::Tea(const QString &title, const QString &description, int minutes, int timerIdentifier,
         QObject *parent)
    :QObject(parent)
    ,mTitle{title}
    ,mDescription{description}
    ,mTimeInMinutes{minutes}
    ,mTimerIdentifier{timerIdentifier}
{
}

QString Tea::title() const
{
    return mTitle;
}

void Tea::setTitle(const QString &title)
{
    if (!title.isEmpty() && mTitle != title)
    {
        mTitle = title;
    }
}

QString Tea::description() const
{
    return mDescription;
}

void Tea::setDescription(const QString &description)
{
    if (!description.isEmpty() && mDescription != description)
    {
        mDescription = description;
    }
}

int Tea::timeInMinutes() const
{
    return mTimeInMinutes;
}

void Tea::setTimeInMinutes(int timeInMinutes)
{
    if (mTimeInMinutes != timeInMinutes)
    {
        mTimeInMinutes = timeInMinutes;
    }
}

int Tea::timerIdentifier() const
{
    return mTimerIdentifier;
}

void Tea::makeTea()
{
    mTimerIdentifier = startTimer(mTimeInMinutes * cMilisecondsInMinute);
}

void Tea::timerEvent(QTimerEvent *event)
{
   if(event->timerId() == mTimerIdentifier)
   {
       killTimer(mTimerIdentifier);
       mTimerIdentifier = 0;
       emit teaCreated(mTitle, mDescription);
   }
   QObject::timerEvent(event);
}
