#include "startup.h"
#include "setuptab.h"
#include "mainview.h"
#include "utils.h"
#include "settings.h"
#include "provider.h"
#include "intsocket.h"
#include "instrument.h"
#include "setupviewmangaer.h"
#include "controltab.h"
#include "ctviewmanager.h"

StartUp::StartUp() :
    QObject(nullptr),
    m_setupTab(*new SetupTab(nullptr)),
    m_controlTab(*new ControlTab(nullptr)),
    m_mainView(*new MainView(nullptr,m_setupTab,m_controlTab)),
    m_instrument(new Instrument(this, *new IntSocket(this))),
    m_setupvm(new setupviewmangaer(this,m_setupTab,*m_instrument, Provider::GetSettingsAsSingleton())),
    m_controlvm(new ctviewmanager(this,m_controlTab,*m_instrument))
{
    //Settings my_settings(this,"settings.json");
    //using provider class for the above function
    //Settings& my_settings = Provider::GetSettingsAsSingleton();
    //my_settings.ParseJsonData();
     m_instrument->DisConnect();
}


StartUp::~StartUp(){
 Utils::DestructorMsg(this);
 delete &m_mainView;
}

void StartUp::show() const
{
  m_mainView.show();
}
