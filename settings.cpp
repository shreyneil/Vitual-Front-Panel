#include "settings.h"
#include <QString>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <utility>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QStringListModel>
#include <QMessageBox>
#include <QStandardPaths>

//adding index to know which command is which i.e. for the command array.

static const int PW_CMD_INDEX = 5;

static auto RESOURCE_PREFIX = QStringLiteral(":/json");
Settings::Settings(QObject *parent, QString fileName) :
    QObject(parent),
    m_filename(fileName),
    m_modelCommands(*new QStringListModel (this))
{
    //ReadJsonFile();
    //since it is private,calling within the constructor
    //only for testing


}

//Parsing the json data obtained from the resource file.
void Settings::ParseJsonData()
{
    QString raw_json = ReadJsonFile();
    if(raw_json.size()==0) return;

    auto json_result = GetJsonObject(raw_json);
    auto json_err = json_result.second;
    if(json_err.error != QJsonParseError::NoError)
    {
        //Show error
        ShowJsonParseError(json_err);
    }

    auto json_obj = json_result.first;
    m_applicationName = json_obj["applicationTitle"].toString();
    m_appShortName = json_obj["appShortname"].toString();
    m_hostName = json_obj["hostname"].toString();
    m_portNumber = json_obj["port"].toInt();
    m_waitMS = json_obj["tcplongWaitMs"].toInt();
    m_readWaitMS = json_obj["tcpshortWaitMs"].toInt();
    SetupCommands(json_obj);
}
//TODO we need to get the json and the error object from parser.

//Since settings in the json file cannot be modified hence we create default settings.

void Settings::SetupCommands(QJsonObject json_obj)
{
    QJsonArray cmd_array = json_obj["commands"].toArray();
    QStringList cmd_list;
    for(auto item: cmd_array)
    {
        cmd_list.append(item.toString());
    }
    m_modelCommands.setStringList(cmd_list);
    auto index = m_modelCommands.index(PW_CMD_INDEX);
    auto test_cmd = m_modelCommands.data(index,Qt::DisplayRole);//firt parameter in index we created above and the second parameter is an enumeration.
    qDebug()<<"Test command the hard way"<<test_cmd.toString();

      if(PW_CMD_INDEX < cmd_list.size())
      {
          m_pwCommand = cmd_list[PW_CMD_INDEX];
      }
      else
      {
          emit NotifyStatusMessage("Unable to get pulse");
      }
}

JsonObjErrPair Settings::GetJsonObject(const QString& rawJson)
{
    //step 1 is to create a json object from the string
    QJsonParseError json_parse_error;
    QJsonDocument json_doc = QJsonDocument::fromJson(rawJson.toUtf8(),&json_parse_error);
    QJsonObject json_obj = json_doc.object();
    return std::make_pair(json_obj,json_parse_error);

}
//creating a version of settings with both r/w access

QString Settings::ReadJsonFile()
{
    auto default_settings = ReadJsonFromInternalResource();
    //for now returning the string that comes back
    //return default_settings;
    QDir config_dir = OpenConfigDirectory();
    auto path = config_dir.filePath(m_filename);
    //QT uses the unix path seperator at all times.
    QFile std_file(path);
    if(std_file.exists())
    {
        if(!std_file.open(QFile::ReadOnly|QFile::Text))
        {
            SendErrorMessage("Could not open" + path);
            return default_settings;

        }
        QString settings = std_file.readAll();
        std_file.close();
        return settings;
    }
    else
    {
        WriteDefaultsToStdConfigFile(std_file,default_settings);
        return default_settings;
    }
}

void Settings::WriteDefaultsToStdConfigFile(QFile& stdConfigFile, const QString &settings)
{
    int length = settings.length();
    if(!stdConfigFile.open(QFile::WriteOnly|QFile::Text))
    {
        SendErrorMessage("Could not open file to write" + stdConfigFile.fileName());
    }
    auto bytes_written = stdConfigFile.write(qPrintable(settings),length);
    if(bytes_written!=length)
    {
        SendErrorMessage("Could  not write settings to" + stdConfigFile.fileName());
        if(!stdConfigFile.remove())
        {
            SendErrorMessage("Could not remove configuration file. Please delete manually" + stdConfigFile.fileName());
        }
    }

    stdConfigFile.close();
    //Qfile destructor takes care of closing the file.
}

//Method to determine specific location for a file type
QDir Settings::OpenConfigDirectory()
{
    QDir config_dir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
    if(!config_dir.exists())
    {
        QDir dir;
        dir.mkpath(config_dir.path());
        //mkpath makes all the needed folders in the path.

    }
    return config_dir;
}

//reading from internal resource using prefix as json
QString Settings::ReadJsonFromInternalResource()
{

    QDir res_dir (RESOURCE_PREFIX);

    if(!res_dir.exists())
    {
        //TODO send an error message
        SendErrorMessage("Internal resource path missing"
                         + res_dir.canonicalPath());
        return "";
    }

    //creating a platform independent path
    auto path = res_dir.filePath(m_filename);
    //creating a QFile object and passing in the path

    QFile res_file(path);
    //Since this file is read -only

    if(!res_file.open(QFile::ReadOnly|QFile::Text))
    {
        //TODO Send error message
        SendErrorMessage("Could not open Internal resource"
                         + path);
        return "";

    }
    //reading settings as a string
    QString settings  = res_file.readAll();
    return settings;
}

void Settings::SendErrorMessage(const QString& msg)
{
    emit NotifyStatusMessage(msg);
}
void Settings::ShowJsonParseError(QJsonParseError jsonError)
{
    QString msg = tr("Error Parsing Json settings file.\n");
    msg.append(jsonError.errorString());
    QMessageBox::critical(0,tr("VFP"),msg);
}
