#include "provider.h"
#include "settings.h"
#include <QString>
#include "utils.h"

static QString SETTINGS_FILE = QStringLiteral("settings.json");
std::unique_ptr<Settings> Provider::m_instanceSettings = nullptr;

Settings& Provider::GetSettingsAsSingleton()
{
    if(m_instanceSettings==nullptr)
    {
        m_instanceSettings = Utils::make_unique<Settings>(nullptr,SETTINGS_FILE);
    }
    //dereferencing the unique pointer.

       return *m_instanceSettings;
}
