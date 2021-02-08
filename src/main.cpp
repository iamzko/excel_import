#include "mainwindow.h"
#include <QFileDialog>
#include <QApplication>
#include <QtSingleApplication>
#include <QTableView>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QCommandLineOption>

#include "xlsxdocument.h"
#include "xlsxworksheet.h"
#include "xlsxcellrange.h"
#include "sheetmodel.h"
#include "ExcelFormat/ExcelFormat.h"

#include <string>
#include <iostream>
#include <bitset>

#include "config.h"
#include "myglobal.h"

void test_qtxlsx()
{
    //    QXlsx::Document xlsx;
    //    xlsx.write("A1","hello qt!");
    //    xlsx.saveAs("Text.xlsx");
        QString filePath = QFileDialog::getOpenFileName(0, "Open xlsx file", QString(), "*.xlsx *.xls");
        if (filePath.isEmpty())
            return;
        QTabWidget tabWidget;
        tabWidget.setWindowTitle(filePath + " - Qt Xlsx Demo");
        tabWidget.setTabPosition(QTabWidget::South);
        QXlsx::Document xlsx2(filePath);
        foreach (QString sheetName, xlsx2.sheetNames()) {
            QXlsx::Worksheet *sheet = dynamic_cast<QXlsx::Worksheet *>(xlsx2.sheet(sheetName));
            if (sheet) {
                QTableView *view = new QTableView(&tabWidget);
                view->setModel(new SheetModel(sheet, view));
                foreach (QXlsx::CellRange range, sheet->mergedCells())
                    view->setSpan(range.firstRow() - 1, range.firstColumn() - 1, range.rowCount(),
                                  range.columnCount());
                tabWidget.addTab(view, sheetName);
            }
        }
        tabWidget.show();
}


void test_excelformat()
{
    namespace Xls = ExcelFormat;
    QString filePath = QFileDialog::getOpenFileName(0, "Open xlsx file", QString(), "*.xlsx *.xls");
    if (filePath.isEmpty())
        return;

    Xls::BasicExcel xls(filePath.toLocal8Bit().data());
    Xls::XLSFormatManager fmt_mgr(xls);

    Xls::BasicExcelWorksheet* sheet = xls.GetWorksheet(0);

    Xls::CellFormat fmt_general(fmt_mgr);

    fmt_general.set_format_string("0.000");

    Xls::BasicExcelCell *cell = sheet->Cell(0,0);
    Xls::CellFormat fmt(fmt_mgr,cell);
    qDebug("-xf_idx:%d",cell->GetXFormatIdx());

    const Xls::Workbook::Font& font = fmt_mgr.get_font(fmt);
    qDebug("font:%s",Xls::stringFromSmallString(font.name_).c_str());

    const std::wstring& fmt_string = fmt.get_format_string();
    qDebug("format:%s",narrow_string(fmt_string).c_str());
    qDebug("content:%s",cell->GetString());
    qDebug("Content:%f",cell->GetDouble());
    qDebug("Content:%d",cell->GetInteger());
    qDebug("Content:%s",cell->GetWString());


    xls.Close();


}


int main(int argc, char *argv[])
{
    //    QApplication a(argc, argv);
    QtSingleApplication a(argc,argv);

    if(a.isRunning())
    {
        QMessageBox::information(nullptr,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("已经有一个实例在运行了！"));
            a.sendMessage(QString::fromLocal8Bit("raise_window_noop"));
        return EXIT_SUCCESS;
    }
    QString commandline_option_config_str = QString::fromLocal8Bit("make-config");

    QCommandLineOption op_make_config(commandline_option_config_str,QString::fromLocal8Bit("生成默认的配置文件。"));
    QCommandLineParser op_parser;
    op_parser.addOption(op_make_config);
    QCommandLineOption op_help = op_parser.addHelpOption();
    op_parser.process(a);
    if(op_parser.isSet(op_help))
    {
        op_parser.showHelp();
        return EXIT_SUCCESS;
    }

    if(op_parser.isSet(commandline_option_config_str))
    {
        Config temp_config;
        if(temp_config.make_config_xml(MyGlobal::the_config_file_path))
        {
            std::cout << "make config successfully!\nPlease check "<< MyGlobal::the_config_file_path.toLocal8Bit().data() << std::endl;
        }
        else
        {
            std::cout << "make config failed!" << std::endl;
        }


    }
    MainWindow w;
    w.setWindowTitle(QString::fromLocal8Bit("接收登记"));
    w.setWindowIcon(QIcon(":/Icon/Resource/title.ico"));
    w.show();

    //    test_excelformat();
    //    test_qtxlsx();

    return a.exec();
}
