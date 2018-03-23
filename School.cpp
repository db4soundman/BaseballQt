#include "School.h"
#include "Profile.h"
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include "MiamiAllAccessBaseball.h"

School::School()
{
    primaryColor = QColor(40,40,40);
}

School::School(QString name, QColor primaryColor, QColor secondaryColor, QPixmap logo)
{
    this->title=name;
    this->primaryColor=primaryColor;
    this->secondaryColor=secondaryColor;
    this->logo=new QPixmap(logo);
}

School::School(Profile p, QImage swatch, QPixmap logo)
{
    title = p.getTitle();
    fullName=p.getFullName();
    shortName=p.getShortName();
    nickname=p.getNickname();

    this->primaryLogoBg = swatch.pixel(0,2);
    this->secondaryLogoBg= swatch.pixel(0,14);
    this->primaryColor=swatch.pixel(0,5);
    this->secondaryColor=swatch.pixel(6,5);
    this->logo=new QPixmap(logo);

}

//QString School::getName() const
//{
//    return name;
//}

//void School::setName(const QString &value)
//{
//    name = value;
//}

QColor School::getPrimaryColor() const
{
    return primaryColor;
}

void School::setPrimaryColor(const QColor &value)
{
    primaryColor = value;
}

QColor School::getSecondaryColor() const
{
    return secondaryColor;
}

void School::setSecondaryColor(const QColor &value)
{
    secondaryColor = value;
}

QPixmap School::getLogo() const
{
    return *logo;
}

void School::setLogo(const QPixmap &value)
{
    logo = new QPixmap(value);
}

QColor School::getPrimaryLogoBg() const
{
    return primaryLogoBg;
}

void School::setPrimaryLogoBg(const QColor &value)
{
    primaryLogoBg = value;
}

QColor School::getSecondaryLogoBg() const
{
    return secondaryLogoBg;
}

void School::setSecondaryLogoBg(const QColor &value)
{
    secondaryLogoBg = value;
}

School
School::getSchoolFromESPN(QString imsName)
{
     QFile csv(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)+"/IMS Images/Profiles.csv");
     Profile activeProfile;
     csv.open(QIODevice::ReadOnly);
     QTextStream stream(&csv);
     while (!stream.atEnd()) {
         QStringList data = stream.readLine().split(',');
         if (data[4] == imsName) {
             Profile p(data[1], data[2], data[3], data[0], QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)+"/IMS Images/Logos_Keyable/"+data[4]+".PNG",
                     QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)+"/IMS Images/Swatches/"+data[4]+".PNG");
             activeProfile = p;
             csv.close();
             break;
         }
     }
     if (!activeProfile.getLogoPath().isEmpty()) {
         QImage swatch(activeProfile.getSwatchPath());
         return School(activeProfile,swatch,QPixmap::fromImage(MiamiAllAccessBaseball::getTrimmedLogo(activeProfile.getLogoPath())));
     }
     return School();
}

QString School::getSwatchPath() const
{
    return swatchPath;
}

void School::setSwatchPath(const QString &value)
{
    swatchPath = value;
}

QString School::getLogoPath() const
{
    return logoPath;
}

void School::setLogoPath(const QString &value)
{
    logoPath = value;
}

QString School::getShortName() const
{
    return shortName;
}

void School::setShortName(const QString &value)
{
    shortName = value;
}

QString School::getFullName() const
{
    return fullName;
}

void School::setFullName(const QString &value)
{
    fullName = value;
}

QString School::getNickname() const
{
    return nickname;
}

void School::setNickname(const QString &value)
{
    nickname = value;
}

QString School::getTitle() const
{
    return title;
}

void School::setTitle(const QString &value)
{
    title = value;
}

School
School::getSwatchFromESPN(QString imsName)
{
    QImage swatch(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)+"/IMS Images/Swatches/"+imsName+".PNG");
    return School("Not a School",swatch.pixel(0,10),swatch.pixel(0,14),
                  QPixmap::fromImage(MiamiAllAccessBaseball::getTrimmedLogo(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)+"/IMS Images/Logos_Keyable/"+imsName+".PNG")));
}

//void
//School::createSchools(QStringList schoolNames)
//{
//    QList<School*> schools;
//    QFile csv(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)+"/IMS Images/Profiles.csv");
//    Profile activeProfile;
//    for (int i=0; i < schoolNames.length(); i++) {
//        QString name = schoolNames[i];
//        csv.open(QIODevice::ReadOnly);
//        QTextStream stream(&csv);
//        while (!stream.atEnd()) {
//            QStringList data = stream.readLine().split(',');
//            if (data[4] == name) {
//                Profile p(data[1], data[2], data[3], data[0], QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)+"/IMS Images/Logos_Keyable/"+data[4]+".PNG",
//                        QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)+"/IMS Images/Swatches/"+data[4]+".PNG");
//                activeProfile = p;
//                csv.close();
//                break;
//            }
//        }
//        if (!activeProfile.getLogoPath().isEmpty()) {
//            QImage swatch(activeProfile.getSwatchPath());
//            schools.append(new School(activeProfile.getFullName(),swatch,QPixmap::fromImage(getTrimmedLogo(activeProfile.getLogoPath()))));
//        }
//    }
//    meet.setSchools(schools);
//}

