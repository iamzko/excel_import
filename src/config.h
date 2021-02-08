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
private:
    QStringList the_excel_header;
    QStringList the_upload_header;
    QStringList the_check_state_header;
    bool have_read_config_file;

};

#endif // CONFIG_H
