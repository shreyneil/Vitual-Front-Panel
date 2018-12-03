#pragma once
#include <QObject>

class SetupTab;
class Instrument;
class Settings;

class setupviewmangaer : public QObject
{
    Q_OBJECT
public:
    explicit setupviewmangaer(QObject *parent, SetupTab& tab, Instrument& inst, Settings& config);
    ~setupviewmangaer();
signals:
    void NotifyStatusUpdated(const QString& vlaue);
    void NotifyConnectEnabled(bool value);
    void NotifyDisconnectEnabled(bool value);
    void NotifyDirectCommandsEnabled(bool value);
    void NotifyControlTabEnabled(bool value);
private slots:
    void onConnected();
    void onDisconnected();
private:
    SetupTab& m_setup;
    Instrument& m_instrument;
    void WireSettings(Settings &config);
    void WireHostandPort();
    void WireMessages();
    void WireButtons();
    void WireDisplayUpdate();
    explicit setupviewmangaer(const setupviewmangaer& rhs) = delete;
    setupviewmangaer& operator= (const setupviewmangaer& rhs) = delete;
};



