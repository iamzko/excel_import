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
private:
    QStringList m_the_excel_header;
    QStringList m_the_upload_header;
    QStringList m_the_check_state_header;
    QString m_the_db_key;
    bool m_have_read_config_file;

};

#endif // CONFIG_H
