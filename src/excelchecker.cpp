#include "excelchecker.h"
#include <QRegExp>
#include <QDebug>

ExcelChecker::ExcelChecker()
{
    m_error_reason_not_null = QString::fromUtf8(u8"此处不能为空");
    m_error_reason_must_null = QString::fromUtf8(u8"此处必须为空");
    m_error_reason_format_not_match = QString::fromUtf8(u8"格式不匹配");
}
void ExcelChecker::set_rules(QVector<ExcelFieldRule> &rules)
{
    m_rules.clear();
    m_rules = rules;
}

ExcelChecker::CHECK_RESULT ExcelChecker::check_cell(int row, int col, QXlsx::Cell *xlsx_cell,QVector<ErrorToShow> &errs)
{
    bool err =false;
    if(col > m_rules.size())
    {
        return ExcelChecker::CELL_ERROR_INVALID_INDEX;
    }
    const ExcelFieldRule &cur_rule = m_rules[col];

    switch (cur_rule.get_content_state())
    {
    case ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD:
        if(xlsx_cell == nullptr)
        {
            errs.append(ErrorToShow(row,col,cur_rule.get_field_name(),cur_rule.get_standard_format(),"",m_error_reason_not_null));
            err = true;
        }
        else
        {
            if(xlsx_cell->value().isNull())
            {
                errs.append(ErrorToShow(row,col,cur_rule.get_field_name(),cur_rule.get_standard_format(),"",m_error_reason_not_null));
                err = true;
            }
            else
            {
                switch (cur_rule.get_format_state()) {
                case ExcelFieldRule::FORMATED_FALSE:
                    break;
                case ExcelFieldRule::FORMATED_TRUE:
                    if(!cur_rule.get_format().exactMatch(xlsx_cell->value().toString()))
                    {
                        errs.append(ErrorToShow(row,col,cur_rule.get_field_name(),cur_rule.get_standard_format(),xlsx_cell->value().toString(),m_error_reason_not_null));
                        err = true;
                    }
                    break;
                default:
                    break;
                }

            }
        }
        break;
    case ExcelFieldRule::CONTENT_EMPTY_ALLOWD:
        if(xlsx_cell != nullptr)
        {
            switch (cur_rule.get_format_state()) {
            case ExcelFieldRule::FORMATED_FALSE:
                break;
            case ExcelFieldRule::FORMATED_TRUE:
               if(!cur_rule.get_format().exactMatch(xlsx_cell->value().toString()))
                {
                    errs.append(ErrorToShow(row,col,cur_rule.get_field_name(),cur_rule.get_standard_format(),xlsx_cell->value().toString(),m_error_reason_format_not_match));
                    err = true;
                }
                break;
            default:
                break;
            }
        }
        else
        {
            switch (cur_rule.get_format_state()) {
            case ExcelFieldRule::FORMATED_FALSE:
                break;
            case ExcelFieldRule::FORMATED_TRUE:
//                if(!cur_rule.get_format().exactMatch(xlsx_cell->value().toString()))
//                {
//                    errs.append(ErrorToShow(row,col,cur_rule.get_field_name(),cur_rule.get_standard_format(),xlsx_cell->value().toString(),m_error_reason_not_null));
//                    err = true;
//                }
                break;
            default:
                break;
            }

        }
        break;
    default:
        break;
    }
    return err?ExcelChecker::CHECK_ERR:ExcelChecker::CHECK_OK;

}
