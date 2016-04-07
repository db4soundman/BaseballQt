#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>
#include <QColor>
class Profile
{
public:
    Profile();
    Profile(QString title, QString nickname, QString fullName, QString shortName, QString logoPath, QString swatchPath);
    ~Profile();


    QString getTitle() const;
    void setTitle(const QString &value);

    QString getFullName() const;
    void setFullName(const QString &value);

    QString getShortName() const;
    void setShortName(const QString &value);

    QString getLogoPath() const;
    void setLogoPath(const QString &value);

    QColor getColor() const;
    void setColor(const QColor &value);

    QString toString();

    inline bool operator<(const Profile& rhs) {return getTitle() < rhs.getTitle();}

    QString getNickname() const;
    void setNickname(const QString &value);

    QString getSwatchPath() const;
    void setSwatchPath(const QString &value);

private:
    QString title, nickname, fullName, shortName, logoPath, swatchPath;
    QColor color;
};

#endif // PROFILE_H
