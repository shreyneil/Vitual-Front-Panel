#pragma once
#include <QObject>

class SetupTab;
class MainView;
class Instrument;
class setupviewmangaer;
class ControlTab;
class ctviewmanager;

class StartUp final : public QObject
{
    Q_OBJECT

public:
    explicit StartUp();
    void show() const;
    ~StartUp();
private:
    SetupTab& m_setupTab;
    ControlTab& m_controlTab;
    MainView& m_mainView;
    Instrument* m_instrument;
    setupviewmangaer* m_setupvm;
    ctviewmanager* m_controlvm;
    explicit StartUp(const StartUp& rhs) = delete;
    StartUp& operator= (const StartUp& rhs) = delete;
};




