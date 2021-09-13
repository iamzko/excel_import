#include "mainwindow.h"
#include <QFileDialog>
#include <QApplication>
#include <QtSingleApplication>
#include <QTableView>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QCommandLineOption>
#include <QMutex>
#include <qapplication.h>
#include <QFile>
#include <QTextStream>

#include "xlsxdocument.h"
#include "xlsxworksheet.h"
#include "xlsxcellrange.h"
#include "sheetmodel.h"
//#include "ExcelFormat/ExcelFormat.h"


#include <string>
#include <iostream>
#include <bitset>

#include "config.h"
#include "myglobal.h"

static const QString log_dir = QString::fromUtf8(u8"./log/");

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


//void test_excelformat()
//{
//    namespace Xls = ExcelFormat;
//    QString filePath = QFileDialog::getOpenFileName(0, "Open xlsx file", QString(), "*.xlsx *.xls");
//    if (filePath.isEmpty())
//        return;

//    Xls::BasicExcel xls(filePath.toLocal8Bit().data());
//    Xls::XLSFormatManager fmt_mgr(xls);

//    Xls::BasicExcelWorksheet* sheet = xls.GetWorksheet(0);

//    Xls::CellFormat fmt_general(fmt_mgr);

//    fmt_general.set_format_string("0.000");

//    Xls::BasicExcelCell *cell = sheet->Cell(0,0);
//    Xls::CellFormat fmt(fmt_mgr,cell);
//    qDebug("-xf_idx:%d",cell->GetXFormatIdx());

//    const Xls::Workbook::Font& font = fmt_mgr.get_font(fmt);
//    qDebug("font:%s",Xls::stringFromSmallString(font.name_).c_str());

//    const std::wstring& fmt_string = fmt.get_format_string();
//    qDebug("format:%s",narrow_string(fmt_string).c_str());
//    qDebug("content:%s",cell->GetString());
//    qDebug("Content:%f",cell->GetDouble());
//    qDebug("Content:%d",cell->GetInteger());
//    qDebug("Content:%s",cell->GetWString());


//    xls.Close();


//}

void my_message_output(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray local_msg = msg.toLocal8Bit();
    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text+=QString::fromUtf8(u8"DEBUG:");
        break;
    case QtInfoMsg:
        text+=QString::fromUtf8(u8"INFO:");
        break;
    case QtWarningMsg:
        text+=QString::fromUtf8(u8"WARNING:");
        break;
    case QtCriticalMsg:
        text+=QString::fromUtf8(u8"CRITICAL:");
        break;
    case QtFatalMsg:
        text+=QString::fromUtf8(u8"FATAL:");
        break;

    }
    QString context_info = QString::fromUtf8(u8"FILE[%1:%2]").arg(QString(context.file)).arg(context.line);
    QString cur_time = QDateTime::currentDateTime().toString("[yyyy/MM/dd hh:mm:ss.zzz]");


    if(type == QtInfoMsg )
    {
        static QMutex mutex;
        mutex.lock();

        QString log_content = text + "\t" +cur_time + "\t" + msg;

        QString log_file_path = log_dir + QDate().currentDate().toString("yyyy_MM_dd.log");
        QDir temp;
        if(!temp.exists(log_dir))
        {
            temp.mkdir(log_dir);
        }
        QFile f(log_file_path);
        f.open(QIODevice::ReadWrite | QIODevice::Append);
        QTextStream f_stream(&f);
        f_stream.setCodec(u8"UTF-8");
        f_stream << log_content << "\r\n";
        f.flush();
        f.close();
        mutex.unlock();
    }
    else
    {
        QString log_content = text + "\t" +cur_time +"\t"  + context_info + "\t" +msg;
        fprintf(stderr,"%s\n", log_content.toLocal8Bit().constData());
    }

}

void test_qt_log()
{
    qInstallMessageHandler(my_message_output);
}

bool set_tdmp_reg()
{
    QString cur_exe_path = QCoreApplication::applicationFilePath().replace("/", "\\");
    QSettings reg(u8"HKEY_CLASSES_ROOT\\TDMP",QSettings::NativeFormat);
    reg.setValue("URL Protocol",cur_exe_path);
    reg.setValue(".",u8"URL:TDMP Protocol");
    QString command = QString::fromUtf8(u8"\"%1\" ").arg(cur_exe_path) + QString::fromUtf8(u8"\"%1\"");
    QSettings reg_command(u8"HKEY_CLASSES_ROOT\\TDMP\\shell\\open\\command",QSettings::NativeFormat);
    reg_command.setValue(".",command);

    return true;

}


int main(int argc, char *argv[])
{
    //test_qt_log();
    //    QApplication a(argc, argv);
    QtSingleApplication a(argc,argv);
    qInstallMessageHandler(my_message_output);
    set_tdmp_reg();
//    qSetMessagePattern( "[%{time yyyyMMdd h:mm:ss.zzz t} %{if-debug}D%{endif}%{if-info}I%{endif}%{if-warning}W%{endif}%{if-critical}C%{endif}%{if-fatal}F%{endif}] %{file}:%{line} - %{message}" );

    if(a.isRunning())
    {
        QMessageBox::information(nullptr,QString::fromUtf8(u8"提示"),QString::fromUtf8(u8"已经有一个实例在运行了！"));
            a.sendMessage(QString::fromUtf8(u8"raise_window_noop"));
        return EXIT_SUCCESS;
    }
    QString commandline_option_config_str = QString::fromUtf8(u8"make-config");

    QCommandLineOption op_make_config(commandline_option_config_str,QString::fromUtf8(u8"生成默认的配置文件。"));
    QCommandLineParser op_parser;
    op_parser.addOption(op_make_config);
    QCommandLineOption op_help = op_parser.addHelpOption();
    op_parser.process(a);
    bool should_set_batch_bum = false;
    if(op_parser.isSet(op_help))
    {
        op_parser.showHelp();
        return EXIT_SUCCESS;
    } else if (op_parser.isSet(commandline_option_config_str)) {
        Config temp_config;
        if(temp_config.make_config_xml(const_cast<QString&>(MyGlobal::CONFIG_FILE_PATH)))
        {
            std::cout << "make config successfully!\nPlease check "<< MyGlobal::CONFIG_FILE_PATH.toUtf8().data() << std::endl;
        }
        else
        {
            std::cout << "make config failed!" << std::endl;
        }

    } else {
        if (argc > 1) {
            should_set_batch_bum = true;
        }
    }
    MainWindow w(should_set_batch_bum);
    w.setWindowTitle(MyGlobal::APP_NAME);
    w.setWindowIcon(QIcon(":/Icon/Resource/title.ico"));
    w.show();
    if (should_set_batch_bum) {
        w.setCommandline_invoke(should_set_batch_bum);
        auto tdmp_str = QString(argv[1]);
        QRegExp r_batch_num("tdmp://(.*)/");
        if (r_batch_num.indexIn(tdmp_str) != -1) {
            w.set_batch_num(r_batch_num.cap(1));
        }
    }

    //    test_excelformat();
    //    test_qtxlsx();

    return a.exec();
}
