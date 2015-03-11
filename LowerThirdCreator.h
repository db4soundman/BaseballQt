#ifndef LOWERTHIRDCREATOR_H
#define LOWERTHIRDCREATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QString>
#include <QList>
#include <QCheckBox>
#include "LowerThird.h"

class LowerThirdCreator : public QWidget {
    Q_OBJECT

public:
    LowerThirdCreator(LowerThird* lt);

signals:
    void makeCustomLt(QString name, QString number, QString year, QList<QString> header,
                      QList<QString> text, bool homeTeam);
private slots:
    void clearFields();
    void submitLt();

private:
    QLineEdit name, num, yr, header;
    QTextEdit text;
    QCheckBox home;

};

#endif // LOWERTHIRDCREATOR_H
