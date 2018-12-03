#include "utils.h"
#include <QString>
#include <QDebug>

//Adding Destrutor log to understand auto-deletion of pointers.

static QString DESTRUCTOR_MSG = QStringLiteral("Running the %1 destructor.");
//Avoiding using the default constructor.
//Utils::Utils()
//{
//}

void Utils::DestructorMsg(const QString value)
{
    qDebug()<< DESTRUCTOR_MSG.arg(value);
}

void Utils::DestructorMsg(const QObject *object)
{
    DestructorMsg(object->metaObject()->className());
    //Feature of the moc compiler as a QObject, using reflection as a metaobject call to get
    //the className and use it as a string parameter to the above function.
}
