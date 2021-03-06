#include "excelreader.h"
#include <QMessageBox>
#include <QDebug>

ExcelReader::ExcelReader()
    :m_checker(nullptr)
    ,m_xlsx_file(nullptr)
    ,m_cur_row(0)
    ,m_cur_col(0)
    ,m_has_checker(false)
{



}

bool ExcelReader::read(QStandardItemModel &the_excel_model)
{
    if(m_checker.isNull() && !m_has_checker)
        return false;

    m_excel_errs.clear();
    auto model_sheet_names = m_xlsx_file->sheetNames();
    if(model_sheet_names.size()>1 || model_sheet_names.size() == 0)
    {
        QMessageBox::warning(nullptr,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"模板文件应该只有一个sheet！"));
        return false;
    }
    QXlsx::Worksheet *model_sheet = dynamic_cast<QXlsx::Worksheet *>(m_xlsx_file->sheet(model_sheet_names.first()));

    QString cell_value;
    QXlsx::Cell *cur_cell = nullptr;
    //寻找序号
    int start_row = 0;
    int start_col = 0;
    bool found = false;
    for(int i = 0; i < model_sheet->dimension().rowCount(); ++i)
    {
        for(int j = 0; j < model_sheet->dimension().columnCount(); ++j)
        {
            cur_cell = model_sheet->cellAt(i,j);
            if(cur_cell == nullptr || cur_cell->isDateTime() || cur_cell->isRichString())
            {
                continue;
            }
            cell_value = cur_cell->value().toString();
            if(cell_value == m_configured_header.first())
            {
                found = true;
                start_row = i;
                start_col = j;
                break;
            }

        }
        if(found)
        {
            break;
        }
    }
    if(found)
    {
//    QMessageBox(Icon icon, const QString &title, const QString &text,
//                StandardButtons buttons = NoButton, QWidget *parent = nullptr,
//                Qt::WindowFlags flags = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHinyt);
QMessageBox(QMessageBox::Information,
            QString::fromUtf8(u8"成功"),
            QString::fromUtf8(u8"序号在:")+QString::number(start_row)+QString::fromUtf8(u8"行,")+QString::number(start_col) +QString::fromUtf8(u8"列"),
            QMessageBox::Ok,
            nullptr,
            Qt::Dialog| Qt::MSWindowsFixedSizeDialogHint ).exec();
        //QMessageBox::about(nullptr,QString::fromUtf8(u8"成功"),QString::fromUtf8(u8"序号在:")+QString::number(start_row)+QString::fromUtf8(u8"行,")+QString::number(start_col) +QString::fromUtf8(u8"列"));
    }
    else
    {
        QMessageBox::warning(nullptr,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"输入文件有错误，未找到数据区域！"));
        return false;
    }
    m_cur_row = start_row;
    m_cur_col = start_col;
    //处理表头
    QStringList table_header;
    int count =  0;
    if(model_sheet->dimension().columnCount() - start_col+1 > m_configured_header.size())
    {
        count = m_configured_header.size();
    }
    else
    {
        count = model_sheet->dimension().columnCount() - start_col+1;
    }
    for(int j = start_col; j < count+start_col; ++j)
    {
        cur_cell = model_sheet->cellAt(start_row,j);
        if(cur_cell!=nullptr)
        {
            table_header << cur_cell->value().toString();
        }
        else
        {
            table_header << QString::fromUtf8(u8"");
        }
    }
    if(!check_header(table_header))
    {
        QMessageBox::warning(nullptr,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"表头有错误，请按照检查结果显示修正文件！"));
        return false;
    }
    QStandardItem* temp_item;
    //处理数据
    start_row += 1;
    int model_i = 0;
    bool any_err = false;
    for(m_cur_row = start_row ; ; ++m_cur_row,++model_i)
    {
        bool break_flag = false;
        int model_j = 0;
        for(m_cur_col = start_col; m_cur_col < count+start_col; ++m_cur_col,++model_j)
        {
            cur_cell = model_sheet->cellAt(m_cur_row,m_cur_col);
            auto ret = m_checker->check_cell(m_cur_row,m_cur_col,m_cur_col-start_col,cur_cell,m_excel_errs);

            //处理序号
            if(m_cur_col == start_col && ret == ExcelChecker::CHECK_ERR)
            {
                    m_excel_errs.removeLast();
                    break_flag = true;
                    break;
            }
            if(ret == ExcelChecker::CHECK_ERR)
            {
                any_err = true;
            }

            if(!any_err)
            {
                if (cur_cell != nullptr) {
                    auto temp_str = cur_cell->value().toString();
                    if (m_configured_header[m_cur_col - start_col] == QString::fromUtf8(u8"定价")) {
                        if (!temp_str.contains(QChar('.'))) {
                            temp_str.append(QString::fromUtf8(u8".00"));
                        } else {
                            if (temp_str.mid(temp_str.indexOf(QChar('.')), temp_str.length()).size() < 3) {
                                temp_str.append(QString::fromUtf8(u8"0"));
                            } else if (temp_str.mid(temp_str.indexOf(QChar('.')), temp_str.length()).size() > 3) {
                                temp_str = temp_str.mid(0, temp_str.indexOf(QChar('.')) + 2);
                            }
                        }
                        qDebug() << "定价：" << temp_str;
                    }
                    temp_item = new QStandardItem(temp_str);
                    the_excel_model.setItem(model_i, model_j, temp_item);

                } else {
                    the_excel_model.setItem(model_i, model_j, new QStandardItem(QString("")));
                }
            }

        }
//        if(!any_err)
//        {
//            the_excel_model.setItem(model_i,model_j+1,new QStandardItem(QString::fromUtf8(u8"已导入，未上传")));
//        }
        if(break_flag)
        {
            break;
        }
    }
    if(any_err)
    {
        QMessageBox::warning(nullptr,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"数据内容有错误，请按照检查结果修正输入文件！"));
        the_excel_model.clear();
    }
    else
    {

        QMessageBox::about(nullptr,QString::fromUtf8(u8"结果"),QString::fromUtf8(u8"输入文件检查完毕，一共读入[")+QString::number(m_cur_row - start_row)+QString::fromUtf8(u8"]行有效数据."));
    }
    return any_err?false:true;

}

bool ExcelReader::check_header(QStringList &actual_header)
{
    if(m_configured_header.size() != actual_header.size())
    {
        m_excel_errs.append(ErrorToShow(m_cur_row,m_cur_col,QString::fromUtf8(u8"表头"),QString::number(m_configured_header.size()),QString::number(actual_header.size()),QString::fromUtf8(u8"表头长度不符")));
        return false;
    }
    bool err = false;
    for(int col = 0;col<m_configured_header.size();++col)
    {
        if(m_configured_header[col] != actual_header[col])
        {
            err = true;
            m_excel_errs.append(ErrorToShow(m_cur_row,m_cur_col+col,QString::fromUtf8(u8"表头"),m_configured_header[col],actual_header[col],QString::fromUtf8(u8"表头内容有误")));
        }
    }
    return err?false:true;

}

bool ExcelReader::open(QString &excel_file_path)
{
    if(excel_file_path.toLower().endsWith(".xls"))
    {
        QMessageBox::warning(nullptr,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"目前不支持xls文件，请打开xlsx文件！"));
        return false;
    }
    if(!excel_file_path.toLower().endsWith(".xlsx"))
    {
        QMessageBox::warning(nullptr,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"请打开xlsx文件！"));
        return false;
    }

    m_xlsx_file.reset(new QXlsx::Document(excel_file_path));
    if(m_xlsx_file.isNull())
    {
        QMessageBox::warning(nullptr,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"打开输入文件失败！"));
        return false;
    }
    return true;
}

QVector<ErrorToShow> ExcelReader::get_excel_errs() const
{
    return m_excel_errs;
}
void ExcelReader::set_checker(ExcelChecker *checker)
{
    if(!m_has_checker)
    {
        m_has_checker = true;
    }
    m_checker.reset(checker);
}

void ExcelReader::set_excel_header(QStringList &configured_header)
{
    m_configured_header = configured_header;

}

