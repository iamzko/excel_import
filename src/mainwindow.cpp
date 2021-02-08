#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTableView>
#include <QMessageBox>
#include <QDebug>
#include <QColor>
#include <QtXml/QtXml>

#include "xlsxdocument.h"
#include "sheetmodel.h"
#include "myglobal.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_excel_reader(new ExcelReader)
{
    ui->setupUi(this);
    m_statusbar_label = new QLabel(QString::fromLocal8Bit("当前状态"),this);
    ui->statusbar->addWidget(m_statusbar_label);
    //生成xml配置文件
//    m_config.make_config_xml(MyGlobal::the_config_file_path);

    if(!m_config.read_config_xml(MyGlobal::the_config_file_path))
    {
        QMessageBox::critical(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("读取配置文件失败，请检查配置文件！"));
        exit(EXIT_FAILURE);
    }

    m_excel_header = m_config.get_excel_header();
    m_upload_header = m_config.get_upload_header();
    m_check_state_header = m_config.get_check_state_header();

    //初始化view和mode
    m_model_excel_data = new QStandardItemModel(0,m_excel_header.size()+1,this);
    m_selection_excel_data = new QItemSelectionModel(m_model_excel_data);
    m_model_excel_data->setHorizontalHeaderLabels(m_excel_header);
    m_model_excel_data->setHorizontalHeaderItem(m_model_excel_data->columnCount()-1,new QStandardItem(QString::fromLocal8Bit("图书状态")));
    connect(m_selection_excel_data,SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));
    ui->tableView->setModel(m_model_excel_data);
    ui->tableView->setSelectionModel(m_selection_excel_data);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:#55ffff; color: black;padding-left: 4px;border: 1px solid ;}");
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->resizeColumnsToContents();

    m_model_upload_data = new QStandardItemModel(0,m_upload_header.size(),this);
    m_selection_upload_data = new QItemSelectionModel(m_model_upload_data);

    m_model_excel_check_state = new QStandardItemModel(0,m_check_state_header.size(),this);
    m_model_excel_check_state->setHorizontalHeaderLabels(m_check_state_header);


    ui->splitter->setOpaqueResize(false);
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setCollapsible(0,false);
    ui->splitter->setCollapsible(1,false);

    m_model_upload_data->setColumnCount(m_upload_header.size());
    m_model_upload_data->setHorizontalHeaderLabels(m_upload_header);
    ui->tableViewUpload->setModel(m_model_upload_data);
    ui->tableViewUpload->setSelectionModel(m_selection_upload_data);
    ui->tableViewUpload->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableViewUpload->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableViewUpload->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:#55ffff; color: black;padding-left: 4px;border: 1px solid ;}");
    ui->tableViewUpload->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewUpload->resizeColumnsToContents();

    int i = 0;
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromLocal8Bit("必须为数字"),QString::fromLocal8Bit("\\d*")));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromLocal8Bit("YYYYmm"),QString::fromLocal8Bit("\\d{4}(0|1)\\d")));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromLocal8Bit("合理的数字"),QString::fromLocal8Bit("\\d*\\.?\\d*")));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromLocal8Bit("YYYYmmdd"),QString::fromLocal8Bit("\\d{4}(0|1)\\d\\d\\d")));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromLocal8Bit("YYYYmmdd"),QString::fromLocal8Bit("\\d{4}(0|1)\\d\\d\\d")));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromLocal8Bit("只能为是或否"),QString::fromLocal8Bit("(\u662f|\u5426)")));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromLocal8Bit("只能为是或否"),QString::fromLocal8Bit("(\u662f|\u5426)")));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromLocal8Bit("只能为是或否"),QString::fromLocal8Bit("(\u662f|\u5426)")));
    m_xinke_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromLocal8Bit("YYYY"),QString::fromLocal8Bit("\\d{4}")));
    ExcelChecker *temp_checker = new ExcelChecker();
    temp_checker->set_rules(m_xinke_rules);

    m_excel_reader->set_excel_header(m_excel_header);
    m_excel_reader->set_checker(temp_checker);





}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSearch_clicked()
{
    //检查批次号输入
    if(!check_batch_num_input())
    {
        QMessageBox::critical(this,QString::fromLocal8Bit("错误"),QString::fromLocal8Bit("请输入批次号！"));
        return;
    }
    //查询数据库，检查该批次号的状态
    //TODO
    m_statusbar_label->setText(ui->lineEditBatchNum->text());
    ui->labelCurrentBatch->setText(ui->lineEditBatchNum->text());

    if(!read_excel_model_file())
    {
        return;
    }


//    ui->tabWidgetExcel->show();
}
bool MainWindow::check_batch_num_input()
{
    if(ui->lineEditBatchNum->text().size()==0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

#if 0
bool MainWindow::read_excel_model_file()
{
    //打开模板文件，读取excel内容
    QString file_path = QFileDialog::getOpenFileName(0, "Open xlsx file", QString(), "*.xlsx *.xls");
    if (file_path.isEmpty())
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("未选择文件！"));
        return false;
    }
    if(file_path.toLower().endsWith(".xls"))
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("目前不支持xls文件，请打开xlsx文件！"));
        return false;
    }
    if(!file_path.toLower().endsWith(".xlsx"))
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("请打开xlsx文件！"));
    }
    ui->labelCurrentFileName->setText(file_path);

    QXlsx::Document xlsx(file_path);
    auto model_sheet_names = xlsx.sheetNames();
    if(model_sheet_names.size()>1 || model_sheet_names.size() == 0)
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("模板文件应该只有一个sheet！"));
        return false;
    }
    QMessageBox::warning(this,QString::fromLocal8Bit("警告"),model_sheet_names.first());

    QXlsx::Worksheet *model_sheet = dynamic_cast<QXlsx::Worksheet *>(xlsx.sheet(model_sheet_names.first()));

    m_model_excel_data->setColumnCount(model_sheet->dimension().columnCount());
    qDebug() << model_sheet->dimension().rowCount();
    QString cell_value;
    QXlsx::Cell *cur_cell = nullptr;
    int start_row = 0;
    for(int i = 0; i < model_sheet->dimension().rowCount(); ++i)
    {
        cur_cell = model_sheet->cellAt(i,1);
        if(cur_cell == nullptr || cur_cell->isDateTime() || cur_cell->isRichString())
        {
            continue;
        }
        cell_value = cur_cell->value().toString();
        if(cell_value == QString::fromLocal8Bit("序号"))
        {
            QMessageBox::about(this,QString::fromLocal8Bit("成功"),QString::fromLocal8Bit("序号在:")+QString::number(i)+QString::fromLocal8Bit("行,")+QString::number(1) +QString::fromLocal8Bit("列"));
            start_row = i;
            break;
        }
    }
    //处理表头
    QStringList table_header;
    for(int j = 1; j <= model_sheet->dimension().columnCount(); ++j)
    {
        cur_cell = model_sheet->cellAt(start_row,j);
        table_header << cur_cell->value().toString();
    }
//    qDebug() << table_header.size() << ";" << the_excel_header.size();
//    for(int i = 0; i < table_header.size()>the_excel_header.size()?the_excel_header.size():table_header.size();++i)
//    {
//        qDebug("table_header:%s,the_excel_header:%s",table_header.at(i).toUtf8().data(),the_excel_header.at(i).toUtf8().data());
//    }
//    if(table_header == the_excel_header)
//    {
//        the_model->setHorizontalHeaderLabels(table_header);

//    }
//    else
//    {
//        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("表头有错误！"));
//        return false;
//    }
    if(!check_excel_header(table_header))
    {
        return false;
    }
    m_model_excel_data->setHorizontalHeaderLabels(table_header);


    QStandardItem* temp_item = new QStandardItem(QString::fromLocal8Bit("图书状态"));
    m_model_excel_data->setHorizontalHeaderItem(m_model_excel_data->columnCount()-1,temp_item);
//    the_model->headerData(the_model->columnCount()-1,Qt::Horizontal,Qt::BackgroundRole);
    //处理数据
    start_row += 1;
    for(int i = start_row,model_i = 0; ; ++i,++model_i)
    {
        bool break_flag = false;
        for(int j = 1,model_j = 0; j < model_sheet->dimension().columnCount(); ++j,++model_j)
        {
            cur_cell = model_sheet->cellAt(i,j);
            //处理序号
            if(j == 1)
            {
                if(cur_cell->value().isNull())
                {
                    QMessageBox::critical(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("序号缺失，在")+QString::number(i)+QString::fromLocal8Bit("行,")+QString::number(j)+QString::fromLocal8Bit("列"));
                    return false;
                }
                if(cur_cell->isDateTime() || cur_cell->isRichString())
                {
                    QMessageBox::critical(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("序号内容错误，在")+QString::number(i)+QString::fromLocal8Bit("行,")+QString::number(j)+QString::fromLocal8Bit("列"));
                    return false;
                }
                auto temp_str =cur_cell->value().toString();
                bool trans_ret = false;
                int num = temp_str.toUInt(&trans_ret);
                Q_UNUSED(num);
                if(!trans_ret)
                {
                    QMessageBox::critical(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("序号内容错误，在")+QString::number(i)+QString::fromLocal8Bit("行,")+QString::number(j)+QString::fromLocal8Bit("列"));
                    break_flag = true;
                    break;
                }
                temp_item = new QStandardItem(temp_str);
                m_model_excel_data->setItem(model_i,model_j,temp_item);

            }
            else
            {
                auto temp_str =cur_cell->value().toString();
                temp_item = new QStandardItem(temp_str);
                m_model_excel_data->setItem(model_i,model_j,temp_item);
            }

        }
        if(break_flag)
        {
            break;
        }
    }
    ui->tableView->resizeColumnsToContents();




    xlsx.destroyed();
    return true;
}
#endif
void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if(current.isValid())
    {
        m_statusbar_label->setText(QString::fromLocal8Bit("当前单元格：")+QString::number(current.row())+QString::fromLocal8Bit("行，")+QString::number(current.column())+QString::fromLocal8Bit("列"));

    }

}





bool MainWindow::check_excel_header(QStringList &target_header)
{
    if(m_excel_header.size() != target_header.size())
    {
        QMessageBox::critical(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("模板文件表头长度异常！"));
        return false;
    }
    else
    {
        for(int i = 0 ; i < m_excel_header.size(); ++i)
        {
            if(m_excel_header[i] != target_header[i])
            {
                QMessageBox::critical(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("模板文件表头内容异常,[")+QString::number(i+1)+QString::fromLocal8Bit("]列,配置内容为:")+m_excel_header[i] +QString::fromLocal8Bit(",实际内容为:")+target_header[i]);
                return false;

            }
        }
    }
    return true;
}

void MainWindow::on_pushButtonOpenDir_clicked()
{
    auto the_current_dir = QFileDialog::getExistingDirectory(this,QString::fromLocal8Bit("选择上传文件夹"),QString::fromLocal8Bit("./"));
    if(the_current_dir.isEmpty())
    {
        return;
    }
    ui->labelCurrentDir->setText(the_current_dir);




}

void MainWindow::on_pushButtonUploadDB_clicked()
{
    m_model_upload_data->insertRows(0,10);
    for(int i = 0; i< m_model_upload_data->rowCount(); ++i)
    {
        QPushButton* button = new QPushButton(QString::fromLocal8Bit("提交"));
        button->setProperty("row",i);
        ui->tableViewUpload->setIndexWidget(m_model_upload_data->index(i,6),button);
    }

}

bool MainWindow::read_excel_model_file()
{
    //打开模板文件，读取excel内容
    QString file_path = QFileDialog::getOpenFileName(0, "Open xlsx file", QString(), "*.xlsx *.xls");
    if (file_path.isEmpty())
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("未选择文件！"));
        return false;
    }
    ui->labelCurrentFileName->setText(file_path);
    if(!m_excel_reader->open(file_path))
    {
        return false;
    }
    if(!m_excel_reader->read(*m_model_excel_data,m_xinke_rules))
    {
        QVector<ErrorToShow> temp_errs = m_excel_reader->get_excel_errs();
        if(temp_errs.size()>0)
        {
            m_model_excel_check_state->clear();
            m_model_excel_check_state->setHorizontalHeaderLabels(m_check_state_header);

            for(int i = 0; i < temp_errs.size(); ++i)
            {
                auto temp_err_data = temp_errs[i].get_error_content();
                m_model_excel_check_state->setItem(i,0,new QStandardItem(std::get<0>(temp_err_data)));
                m_model_excel_check_state->setItem(i,1,new QStandardItem(std::get<1>(temp_err_data)));
                m_model_excel_check_state->setItem(i,2,new QStandardItem(std::get<2>(temp_err_data)));
                m_model_excel_check_state->setItem(i,3,new QStandardItem(std::get<3>(temp_err_data)));
                m_model_excel_check_state->setItem(i,4,new QStandardItem(std::get<4>(temp_err_data)));
                m_model_excel_check_state->setItem(i,5,new QStandardItem(std::get<5>(temp_err_data)));
            }
            ui->tableView->setModel(m_model_excel_check_state);
            ui->tableView->resizeColumnsToContents();

        }


        return false;
    }
    m_model_excel_data->setHorizontalHeaderLabels(m_excel_header);
    ui->tableView->setModel(m_model_excel_data);
    ui->tableView->resizeColumnsToContents();

    return true;
}
