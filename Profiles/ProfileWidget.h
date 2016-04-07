#ifndef PROFILEWIDGET_H
#define PROFILEWIDGET_H

#include <QObject>
#include <QDialog>
#include <QList>
#include <QButtonGroup>
#include <QRadioButton>
#include "Profile.h"
class ProfileWidget: public QDialog
{
    Q_OBJECT
public:
    ProfileWidget();
    ~ProfileWidget();

public slots:
    void applySettings();

signals:
    void closed(Profile chosen);

private:
    QList<Profile> profiles;
    QButtonGroup group;
    QList<QRadioButton*> buttonList;
};

#endif // PROFILEWIDGET_H
