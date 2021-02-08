#include "excelfieldrule.h"

ExcelFieldRule::ExcelFieldRule(QString field_name,
                               FIELD_CONTENT content_state,
                               FIELD_FORMAT format_state,
                               QString standar_format,
                               QString format)
    :m_content_state(content_state)
    ,m_format_state(format_state)
    ,m_format(format)
    ,m_str_foramt(standar_format)
    ,m_field_name(field_name)
{


}
