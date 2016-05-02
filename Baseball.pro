#-------------------------------------------------
#
# Project created by QtCreator 2014-06-21T11:33:23
#
#-------------------------------------------------

QT       += core gui network
QT += xml
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Graphics
TEMPLATE = app
INCLUDEPATH += GUI \
               Wizard \
            Standings \
            NCHCScoreboard \
            GameStatEditors \
            Profiles

SOURCES += main.cpp\
        MainWindow.cpp \
    Scoreboard.cpp \
    LowerThird.cpp \
    Clock.cpp \
    SeasonXMLHandler.cpp \
    GameXmlHandler.cpp \
    MiamiAllAccessBaseball.cpp \
    GUI/ControlPanel.cpp \
    GUI/DisplayControls.cpp \
    GUI/ScoreControl.cpp \
    GUI/GameInfo.cpp \
    GUI/ClockControls.cpp \
    GUI/StatDisplayControls.cpp \
    GUI/ClockDialog.cpp \
    Wizard/SetupWizard.cpp \
    Wizard/SetupPage.cpp \
    CommercialGraphic.cpp \
    GameStatEditors/PlayerEditor.cpp \
    GameStatEditors/TeamEditor.cpp \
    LowerThirdCreator.cpp \
    GameXmlUpdater.cpp \
    StatCrewScanner.cpp \
    TricasterHandler.cpp \
    BaseballGame.cpp \
    BaseballPlayer.cpp \
    BaseballTeam.cpp \
    GUI/Pitchers.cpp \
    GUI/CountControl.cpp \
    GUI/TeamStatControl.cpp \
    GUI/BatterStatControl.cpp \
    GUI/AtBatResults.cpp \
    GUI/Lineups.cpp \
    GUI/BaseControlls.cpp \
    DefenseGraphic.cpp \
    BattingOrder.cpp \
    PitcherGraphic.cpp \
    GUI/PreGame.cpp \
    Profiles/Profile.cpp \
    Params.cpp

HEADERS  += MainWindow.h \
    Scoreboard.h \
    LowerThird.h \
    Clock.h \
    BaseballTeam.h \
    SeasonXMLHandler.h \
    GameXmlHandler.h \
    MiamiAllAccessBaseball.h \
    GUI/ControlPanel.h \
    GUI/DisplayControls.h \
    GUI/ScoreControl.h \
    GUI/GameInfo.h \
    GUI/ClockControls.h \
    GUI/StatDisplayControls.h \
    GUI/ClockDialog.h \
    Wizard/SetupWizard.h \
    Wizard/SetupPage.h \
    CommercialGraphic.h \
    GameStatEditors/PlayerEditor.h \
    GameStatEditors/TeamEditor.h \
    LowerThirdCreator.h \
    GameXmlUpdater.h \
    StatCrewScanner.h \
    TricasterHandler.h \
    AirSend_api.h \
    BaseballGame.h \
    BaseballPlayer.h \
    GUI/Pitchers.h \
    GUI/CountControl.h \
    GUI/TeamStatControl.h \
    GUI/BatterStatControl.h \
    GUI/AtBatResults.h \
    GUI/Lineups.h \
    GUI/BaseControlls.h \
    DefenseGraphic.h \
    BattingOrder.h \
    PitcherGraphic.h \
    GUI/PreGame.h \
    Profiles/Profile.h \
    Params.h



RESOURCES += \
    graphics.qrc

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
unix|win32: LIBS += -L$$PWD/ -lProcessingAirSendx86
