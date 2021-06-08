#ifndef CONFIG_H
#define CONFIG_H
#include <QString>
#include <QStringList>
#include <QtXml>


class Config
{
public:
    Config();
    bool make_config_xml(QString &config_file_path);
    bool read_config_xml(QString &config_file_path);
    QStringList get_excel_header() const;
    QStringList get_upload_header() const;
    QStringList get_check_state_header() const;
    QString get_db_key() const;
    bool get_server_type() const;
private:
    QStringList m_the_excel_header;
    QStringList m_the_upload_header;
    QStringList m_the_check_state_header;
    QString m_the_db_key;
    QString m_the_server_type;//调用的服务类型，内网为0，外网为1
    bool m_have_read_config_file;

};

#endif // CONFIG_H
