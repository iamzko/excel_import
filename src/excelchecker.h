#ifndef EXCELCHECKER_H
#define EXCELCHECKER_H
#include "excelfieldrule.h"
#include "xlsxdocument.h"
#include <QVector>
#include "errortoshow.h"


class ExcelChecker
{
public:
    ExcelChecker();
    void set_rules(QVector<ExcelFieldRule> &rules);
    enum CHECK_RESULT
    {
        CELL_ERROR_EMPTY,
        CELL_ERROR_FORMAT,
        CELL_ERROR_INVALID_INDEX,
        CELL_ERROR_NULLPTR,
        CHECK_OK,
        CHECK_ERR,
    };
    CHECK_RESULT check_cell(int row, int col,int rule_index,QXlsx::Cell *xlsx_cell,QVector<ErrorToShow> &errs);


private:
    QVector<ExcelFieldRule> m_rules;/*字段规则*/
    QVector<ErrorToShow> m_errs;/*检查结果*/
    QString m_error_reason_not_null;
    QString m_error_reason_must_null;
    QString m_error_reason_format_not_match;

};

#endif // EXCELCHECKER_H
