#ifndef EXCELREADER_H
#define EXCELREADER_H
#include <QString>
#include <QScopedPointer>
#include <QStandardItemModel>
#include "xlsxdocument.h"
#include "excelchecker.h"
#include "errortoshow.h"



class ExcelReader
{
public:
    ExcelReader();
    void set_checker(ExcelChecker* checker);
    void set_excel_header(QStringList &configured_header);
    bool read(QStandardItemModel &the_excel_model, QVector<ExcelFieldRule> &read_rules);
    bool check_header(QStringList &actual_header);
    bool open(QString &excel_file_path);
    QVector<ErrorToShow> get_excel_errs() const;

private:
    QScopedPointer<ExcelChecker> m_checker;
    QScopedPointer<QXlsx::Document> m_xlsx_file;
    QString m_file_path;
    QStringList m_configured_header;
    QVector<ErrorToShow> m_excel_errs;
    int m_cur_row;
    int m_cur_col;
};

#endif // EXCELREADER_H
