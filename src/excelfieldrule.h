#ifndef EXCELFIELDRULE_H
#define EXCELFIELDRULE_H
#include <QRegExp>
#include <QString>


class ExcelFieldRule
{
public:
    enum FIELD_CONTENT
    {
        CONTENT_EMPTY_ALLOWD,
        CONTENT_EMPTY_NOT_ALLOWD,
    };
    enum FIELD_FORMAT
    {
        FORMATED_TRUE,
        FORMATED_FALSE,
    };
    ExcelFieldRule(QString field_name,
                   FIELD_CONTENT content_state,
                   FIELD_FORMAT format_state,
                   QString standar_format="",
                   QString format="");
    QString get_standard_format() const
    {
        return m_str_foramt;
    }
    FIELD_CONTENT get_content_state() const
    {
        return m_content_state;
    }
    FIELD_FORMAT get_format_state() const
    {
        return m_format_state;
    }
    QRegExp get_format() const
    {
        return m_format;
    }
    QString get_field_name() const
    {
        return m_field_name;
    }

private:
    FIELD_CONTENT m_content_state;
    FIELD_FORMAT m_format_state;
    QRegExp m_format;
    QString m_str_foramt;
    QString m_field_name;
};

#endif // EXCELFIELDRULE_H
