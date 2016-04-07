#include "ProfileWidget.h"
#include <QTextStream>
#include <QFile>
#include "MiamiAllAccessHockey.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
ProfileWidget::ProfileWidget()
{
    QFile file(MiamiAllAccessHockey::getProfilesFilePath()+"/profiles.txt");
    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::information(0, "ERROR", file.errorString());
    }
    else {
        QVBoxLayout* parentLayout = new QVBoxLayout();
        QTextStream in(&file);
        while(!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split("|");
            QStringList rgb = fields.at(3).split(",");
            QColor col(rgb.at(0).toInt(), rgb.at(1).toInt(), rgb.at(2).toInt());
            QString fp = MiamiAllAccessHockey::getProfilesFilePath()+"/"+fields.at(4);
            Profile p(fields.at(0),fields.at(1), fields.at(2),col, fp);
            profiles.append(p);
            QRadioButton* button = new QRadioButton(fields.at(0));
            group.addButton(button);
            buttonList.append(button);
            QHBoxLayout* subLayout = new QHBoxLayout();
            subLayout->addWidget(button);
            parentLayout->addLayout(subLayout);
        }
        QPushButton* ok = new QPushButton("OK");
        parentLayout->addWidget(ok);
        connect(ok, SIGNAL(clicked()), this, SLOT(applySettings()));
        file.close();
        setLayout(parentLayout);
    }
}

ProfileWidget::~ProfileWidget()
{

}

void ProfileWidget::applySettings()
{
    for (int i = 0; i < buttonList.length(); i++) {
        if (buttonList.at(i)->isChecked()){
            emit closed(profiles.at(i));
            break;
        }
    }
    this->accept();
}

