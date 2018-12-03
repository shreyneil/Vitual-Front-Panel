#include "ctviewmanager.h"
#include "instrument.h"
#include "controltab.h"
#include "utils.h"

ctviewmanager::ctviewmanager(QObject *parent, ControlTab &ctrlTab, Instrument &inst) :
    QObject(parent),
    m_controlTab(ctrlTab),
    m_instrument(inst)
{
    WireControls();
    WireConnected();
    //OnDisconnected();
    //alternative way is to use the startup to invoke this.
}

ctviewmanager::~ctviewmanager()
{
    Utils::DestructorMsg(this);
}
//Wireup controls of the control tab to the instrument.

void ctviewmanager::WireControls()
{
   connect(&m_controlTab,&ControlTab::NotifyPulseWidthChanged,
           &m_instrument,&Instrument::onPulseWidthChange);
}

void ctviewmanager::WireConnected()
{
    connect(&m_instrument,&Instrument::NotifyConnected,
            this,&ctviewmanager::OnConnected);
    connect(&m_instrument,&Instrument::NotifyDisConnected,
            this,&ctviewmanager::OnDisconnected);
}
//directly using method instead of signal slot interaction as an alternative approach.
void ctviewmanager::OnConnected()
{
   m_controlTab.EnablePanel(true);

}

void ctviewmanager::OnDisconnected()
{
  m_controlTab.EnablePanel(false);
}

