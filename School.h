#ifndef SCHOOL_H
#define SCHOOL_H

#include <QObject>
#include <QPixmap>
#include <QColor>
#include <QImage>
#include "Profile.h"

class School
{
public:
    School();
    School(QString name, QColor primaryColor, QColor secondaryColor, QPixmap logo);
    School(Profile p, QImage swatch, QPixmap logo);

//    QString getName() const;
//    void setName(const QString &value);

    QColor getPrimaryColor() const;
    void setPrimaryColor(const QColor &value);

    QColor getSecondaryColor() const;
    void setSecondaryColor(const QColor &value);

    QPixmap getLogo() const;
    void setLogo(const QPixmap &value);

    QColor getPrimaryLogoBg() const;
    void setPrimaryLogoBg(const QColor &value);

    QColor getSecondaryLogoBg() const;
    void setSecondaryLogoBg(const QColor &value);

    //static void createSchools(QStringList schoolNames);
    static School getSwatchFromESPN(QString imsName);
    static School getSchoolFromESPN(QString imsName);

    QString getSwatchPath() const;
    void setSwatchPath(const QString &value);

    QString getLogoPath() const;
    void setLogoPath(const QString &value);

    QString getShortName() const;
    void setShortName(const QString &value);

    QString getFullName() const;
    void setFullName(const QString &value);

    QString getNickname() const;
    void setNickname(const QString &value);

    QString getTitle() const;
    void setTitle(const QString &value);

private:
    //QString name;
    QColor primaryColor, secondaryColor, primaryLogoBg, secondaryLogoBg;
    QPixmap *logo;
    QString title, nickname, fullName, shortName, logoPath, swatchPath;
};

#endif // SCHOOL_H
