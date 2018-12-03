    #pragma once
#include <QObject>

class QString;
class QStringListModel;
class QJsonParseError;
class QJsonObject;
class QFile;
class QDir;


//creating a typedef for returning json object and parse error
typedef std::pair<QJsonObject, QJsonParseError> JsonObjErrPair;

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent, QString fileName);
    void ParseJsonData();
    QString getApplicationName() const{return m_applicationName;}
    QString getAppShortName() const{return m_appShortName;}
    QString getHostName() const{return m_hostName;}
    quint16 getPortNumber() const{return m_portNumber;}
    int getShortWait() {return m_readWaitMS;}
    int getLongWait() {return m_waitMS;}
    QStringListModel& getCommandsAsModel() const {return m_modelCommands;}
    QString getPwCommand()const{return m_pwCommand;}
signals:
     void NotifyStatusMessage(QString message);


private:
    QString m_filename;
    QString m_applicationName;
    QString m_appShortName;
    QString m_hostName;
    quint16 m_portNumber;
    quint16 m_waitMS;
    quint16 m_readWaitMS;
    QStringListModel& m_modelCommands;
    QString m_pwCommand;

    //member variable name for reading the file
    QString ReadJsonFile();
    QString ReadJsonFromInternalResource();
    void SendErrorMessage(const QString &msg);
    JsonObjErrPair GetJsonObject(const QString &rawJson);
    void SetupCommands(QJsonObject json_obj);
    void ShowJsonParseError(QJsonParseError jsonError);
    QDir OpenConfigDirectory();
    void WriteDefaultsToStdConfigFile(QFile &stdConfigFile, const QString &settings);

    explicit Settings(const Settings& rhs) = delete;
    Settings& operator= (const Settings& rhs) = delete;

};



