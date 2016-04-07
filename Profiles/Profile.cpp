#include "Profile.h"
Profile::Profile()
{

}

Profile::Profile(QString title, QString nickname, QString fullName, QString shortName, QString logoPath, QString swatchPath):
    title(title), fullName(fullName), shortName(shortName), logoPath(logoPath), nickname(nickname), swatchPath(swatchPath)
{

}

Profile::~Profile()
{

}
QString Profile::getTitle() const
{
    return title;
}

void Profile::setTitle(const QString &value)
{
    title = value;
}
QString Profile::getFullName() const
{
    return fullName;
}

void Profile::setFullName(const QString &value)
{
    fullName = value;
}
QString Profile::getShortName() const
{
    return shortName;
}

void Profile::setShortName(const QString &value)
{
    shortName = value;
}
QString Profile::getLogoPath() const
{
    return logoPath;
}

void Profile::setLogoPath(const QString &value)
{
    logoPath = value;
}
QColor Profile::getColor() const
{
    return color;
}

void Profile::setColor(const QColor &value)
{
    color = value;
}

QString Profile::toString()
{
    return fullName +"|" + fullName+"|"+shortName+"|"+QString::number(color.red())+","+QString::number(color.green())+
            ","+QString::number(color.blue())+"|"+logoPath;
}
QString Profile::getNickname() const
{
    return nickname;
}

void Profile::setNickname(const QString &value)
{
    nickname = value;
}
QString Profile::getSwatchPath() const
{
    return swatchPath;
}

void Profile::setSwatchPath(const QString &value)
{
    swatchPath = value;
}








