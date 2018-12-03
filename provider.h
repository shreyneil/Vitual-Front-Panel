#pragma once
#include <memory>
//for the use of pointer.
class Settings;
class Provider final
{
public:
    Provider();
    static Settings& GetSettingsAsSingleton();

private:

    //unique pointer to hold the settings pointer gained from the above method.
    static std::unique_ptr<Settings> m_instanceSettings;
    explicit Provider(const Provider& rhs) = delete;
    Provider& operator= (const Provider& rhs) = delete;
};



