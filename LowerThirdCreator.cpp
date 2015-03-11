#include "LowerThirdCreator.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

LowerThirdCreator::LowerThirdCreator(LowerThird* lt) {
    QVBoxLayout* mainLayout = new QVBoxLayout();
    home.setText("Home Team");
    mainLayout->addWidget(&home);
    QFormLayout* details = new QFormLayout();

    details->addRow("Name", &name);
    details->addRow("Number", &num);
    details->addRow("Year", &yr);
    details->addRow("Header", &header);
    details->addRow("Text", &text);

    mainLayout->addLayout(details);

    QHBoxLayout* buttons = new QHBoxLayout();

    QPushButton* clear = new QPushButton("Clear Fields");
    connect(clear, SIGNAL(clicked()), this, SLOT(clearFields()));
    buttons->addWidget(clear);

    QPushButton* show = new QPushButton("Show");
    connect(show, SIGNAL(clicked()), this, SLOT(submitLt()));
    connect(show, SIGNAL(clicked()), this, SLOT(hide()));
    buttons->addWidget(show);

    mainLayout->addLayout(buttons);
    setLayout(mainLayout);
    connect(this, SIGNAL(makeCustomLt(QString,QString,QString,QList<QString>,QList<QString>,bool)),
            lt, SLOT(prepareForCustomLt(QString,QString,QString,QList<QString>,QList<QString>,bool)));
}

void LowerThirdCreator::clearFields()
{
    name.setText("");
    num.setText("");
    yr.setText("");
    header.setText("");
    text.clear();
}

void LowerThirdCreator::submitLt()
{
    QList<QString> headerText, statText;
    headerText.append(header.text());
    statText.append(text.toPlainText());
    emit makeCustomLt(name.text(), num.text(), yr.text(), headerText, statText,
                      home.isChecked());
}
