#pragma once
#include <QObject>

class Instrument;
class ControlTab;
class ctviewmanager : public QObject
{
    Q_OBJECT
public:
    explicit ctviewmanager(QObject *parent, ControlTab& ctrlTab,
                           Instrument& inst);
    ~ctviewmanager();
public slots:
    void OnConnected();
    void OnDisconnected();
    //since our viewmanager needs to know when our instrument is connected or disconneced.
    //slots should be defined above the private methods ,otherwise we get parse error which us difficult to debug.
private:
    ControlTab& m_controlTab;
    Instrument& m_instrument;
    void WireControls();
    void WireConnected();

    explicit ctviewmanager(const ctviewmanager& rhs) = delete;
    ctviewmanager& operator= (const ctviewmanager& rhs) = delete;
};



