#include "setupviewmangaer.h"
#include "setuptab.h"
#include "instrument.h"
#include "settings.h"
#include "utils.h"

setupviewmangaer::setupviewmangaer(QObject *parent, SetupTab &tab, Instrument &inst, Settings &config) :
    QObject(parent),
    m_setup(tab),
    m_instrument(inst)
{
    //wiring up the signal and slots and then passing status messages.
    WireSettings(config);
    config.ParseJsonData();
    WireHostandPort();
    //error status and messages also need to be wired using signal and slots.
    WireMessages();
    WireButtons();
    WireDisplayUpdate();
    m_setup.SetHostName(config.getHostName());
    m_setup.SetPort(config.getPortNumber());
    m_setup.SetCommands(config.getCommandsAsModel());
    auto long_wait = config.getLongWait();
    auto short_wait = config.getShortWait();
    m_instrument.SetLongWaitMS(long_wait);
    m_instrument.SetShortWaitMS(short_wait);
    emit NotifyStatusUpdated(tr("Long wait MS: %1").arg(long_wait));
    emit NotifyStatusUpdated(tr("Short wait MS: %1").arg(short_wait));
    //onDisconnected();
}

setupviewmangaer::~setupviewmangaer()
{
    Utils::DestructorMsg(this);
}

void setupviewmangaer::onConnected()
{
    emit NotifyConnectEnabled(false);
    emit NotifyDisconnectEnabled(true);
    emit NotifyDirectCommandsEnabled(true);
    emit NotifyControlTabEnabled(true);
}

void setupviewmangaer::onDisconnected()
{

    emit NotifyConnectEnabled(true);
    emit NotifyDisconnectEnabled(false);
    emit NotifyDirectCommandsEnabled(false);
    emit NotifyControlTabEnabled(false);
}

void setupviewmangaer::WireSettings(Settings& config)
{
    connect(&config, &Settings::NotifyStatusMessage,
            &m_setup, &SetupTab::onStatusUpdated);
}

void setupviewmangaer::WireHostandPort()
{
    connect(&m_setup, &SetupTab::NotifyHostNameChanged,
            &m_instrument, &Instrument::onHostNameChanged);
    connect(&m_setup, &SetupTab::NotifyPortNameChanged,
            &m_instrument, &Instrument::onPortChanged);
}

void setupviewmangaer::WireMessages()
{
    connect(&m_instrument, &Instrument::NotifyErrorDetected,
            &m_setup, &SetupTab::onStatusUpdated);
    connect(&m_instrument, &Instrument::NotifyStatusUpdated,
            &m_setup, &SetupTab::onStatusUpdated);
    connect(this, &setupviewmangaer::NotifyStatusUpdated,
            &m_setup, &SetupTab::onStatusUpdated);

}

void setupviewmangaer::WireButtons()
{     connect(&m_setup, &SetupTab::NotifyConnectClicked,
              &m_instrument, &Instrument::Connect);
      connect(&m_instrument, &Instrument::NotifyConnected,
              &m_setup, &SetupTab::onConnected);
        connect(&m_instrument, &Instrument::NotifyConnected,
                this, &setupviewmangaer::onConnected);

          connect(&m_setup, &SetupTab::NotifyDisconnectClicked,
                  &m_instrument, &Instrument::DisConnect);
            connect(&m_instrument, &Instrument::NotifyDisConnected,
                    &m_setup, &SetupTab::onDisconnect);

              connect(&m_instrument, &Instrument::NotifyDisConnected,
                      this, &setupviewmangaer::onDisconnected);

                connect(&m_setup, &SetupTab::NotifySendClicked,
                        &m_instrument, &Instrument::onSendRequest);
                  connect(&m_setup, &SetupTab::NotifyReceivedClicked,
                          &m_instrument, &Instrument::onReceiveRequest);

                    connect(&m_instrument, &Instrument::NotifyDataReceived,
                            &m_setup, &SetupTab::onDataReceived);
                      connect(&m_instrument, &Instrument::NotifyDataSent,
                              &m_setup, &SetupTab::onDataSent);

}

void setupviewmangaer::WireDisplayUpdate()
{
    connect(this, &setupviewmangaer::NotifyConnectEnabled,
                &m_setup, &SetupTab::onConnectEnabled);
        connect(this, &setupviewmangaer::NotifyDisconnectEnabled,
                &m_setup, &SetupTab::onDisconnectEnabled);
        connect(this, &setupviewmangaer::NotifyDirectCommandsEnabled,
                &m_setup, &SetupTab::onDirectCommandsEnabled);
        connect(this, &setupviewmangaer::NotifyControlTabEnabled,
    &m_setup, &SetupTab::onControlTabEnabled);
}
