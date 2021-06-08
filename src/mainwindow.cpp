#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTableView>
#include <QMessageBox>
#include <QDebug>
#include <QColor>
#include <QtXml/QtXml>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QPushButton>
#include <QMouseEvent>
#include <QCheckBox>
#include <QStylePainter>
#include <QtConcurrent/QtConcurrentRun>
#include <QProgressDialog>

#include <string>
#include <iostream>
#include <chrono>
#include <sstream>
#include <time.h>
#include <stdlib.h>

#include "webserviceallin/Service1Soap.nsmap"




#include "xlsxdocument.h"
#include "sheetmodel.h"
#include "myglobal.h"
#include "myqheaderview.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,ui(new Ui::MainWindow)
    ,m_excel_reader(new ExcelReader)
    ,m_cur_tabview_state(tableview_show_type::SHOW_NULL)
    ,m_file_transports(nullptr)
    ,m_select_all_button_state(false)
{
    ui->setupUi(this);
    ui->pushButtonTest->hide();
    m_statusbar_label = new QLabel(QString::fromUtf8(u8""),this);
    m_statusbar_label_cur_batch_num= new QLabel(QString::fromUtf8(u8"当前批次号：null"),this);
    ui->statusbar->addWidget(m_statusbar_label);
    ui->statusbar->addPermanentWidget(m_statusbar_label_cur_batch_num);
    m_msg_box.reset(new QMessageBox(QMessageBox::Warning,QString::fromUtf8(u8"警告"),QString(u8"服务器连接失败，请稍后再试！"),QMessageBox::Ok,this));

    connect(&m_timer_watch_err_msg,SIGNAL(timeout()),this,SLOT(on_err_msg_show()));
    m_timer_watch_err_msg.start(1000);
    //生成xml配置文件
    //    m_config.make_config_xml(MyGlobal::the_config_file_path);

    if(!m_config.read_config_xml(const_cast<QString&>(MyGlobal::CONFIG_FILE_PATH)))
    {
        QMessageBox::critical(this,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"读取配置文件失败，请检查配置文件！"));
        exit(EXIT_FAILURE);
    }
    //初始化日志窗口
    m_log_dock.reset(new QDockWidget(QString::fromUtf8(u8"日志"),this));
    auto log_edit = new QTextEdit(m_log_dock.get());
    log_edit->setReadOnly(true);
    //    m_log_edit.reset(new QTextEdit(m_log_dock.get()));
    //    m_log_edit->setReadOnly(true);
    //    m_log_dock->setWidget(m_log_edit.get());
    m_log_dock->setWidget(log_edit);
    m_log_dock->setFeatures(QDockWidget::AllDockWidgetFeatures);
    setDockNestingEnabled(true);
    //    m_log_dock->setFeatures(QDockWidget::DockWidgetVerticalTitleBar);

    addDockWidget(Qt::RightDockWidgetArea,m_log_dock.get());



    m_excel_header = m_config.get_excel_header();
    m_upload_header = m_config.get_upload_header();
    m_check_state_header = m_config.get_check_state_header();
    m_db_key = m_config.get_db_key();
    qDebug() << "db_key:" << m_db_key;

    //初始化view和mode
    m_model_excel_data = new QStandardItemModel(0,m_excel_header.size()+1,this);
    m_selection_excel_data = new QItemSelectionModel(m_model_excel_data);
    m_model_excel_data->setHorizontalHeaderLabels(m_excel_header);
    m_model_excel_data->setHorizontalHeaderItem(m_model_excel_data->columnCount()-1,new QStandardItem(QString::fromUtf8(u8"图书状态")));
    connect(m_selection_excel_data,SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));
    ui->tableView->setModel(m_model_excel_data);
    ui->tableView->setSelectionModel(m_selection_excel_data);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    //    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:#55ffff; color: black;padding-left: 4px;border: 1px solid ;}");
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->verticalHeader()->setHidden(true);

    m_model_upload_data = new QStandardItemModel(0,m_upload_header.size(),this);
    m_selection_upload_data = new QItemSelectionModel(m_model_upload_data);

    m_model_excel_check_state = new QStandardItemModel(0,m_check_state_header.size(),this);
    m_model_excel_check_state->setHorizontalHeaderLabels(m_check_state_header);

    ui->splitter->setOpaqueResize(false);
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setCollapsible(0,false);
    ui->splitter->setCollapsible(1,false);

    m_model_upload_data->setColumnCount(m_upload_header.size());
    m_upload_header.append(" ");
    m_model_upload_data->setHorizontalHeaderLabels(m_upload_header);
    //    m_model_upload_data->insertColumn(m_model_upload_data->columnCount());
    //    m_model_upload_data->setHorizontalHeaderItem(m_model_upload_data->columnCount()-1,new QStandardItem(QString::fromUtf8(u8" ")));
    ui->tableViewUpload->setModel(m_model_upload_data);
    ui->tableViewUpload->setSelectionModel(m_selection_upload_data);
    ui->tableViewUpload->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewUpload->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewUpload->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:#55ffff; color: black;padding-left: 4px;border: 1px solid ;}");
    ui->tableViewUpload->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewUpload->resizeColumnsToContents();
    //    ui->tableViewUpload->verticalHeader()->setHidden(true);
    //    ui->tableViewUpload->setVerticalHeader()
    MyQHeaderView* my_header = new MyQHeaderView(Qt::Vertical,ui->tableViewUpload);
    m_upload_vheadeview = my_header;
    connect(my_header,SIGNAL(select_index(int)),ui->tableViewUpload,SLOT(selectRow(int)));
    connect(ui->tableViewUpload,SIGNAL(clicked(const QModelIndex &)),this,SLOT(on_select_rows(const QModelIndex &)));
    connect(this,SIGNAL(press_row(int)),my_header,SLOT(on_process_row_state(int)));

    ui->tableViewUpload->setVerticalHeader(my_header);
    ui->tableViewUpload->verticalHeader()->setStyleSheet("QHeaderView::section {background-color:#ffffff; color: black;padding-left: 4px;border: 1px solid ;}");
    ui->tableViewUpload->verticalHeader()->setFixedWidth(35);
    //    ui->tableViewUpload->setCornerWidget(new QCheckBox(QString::fromUtf8(u8"全选"),ui->tableViewUpload));
    QAbstractButton *corner_button = ui->tableViewUpload->findChild<QAbstractButton*>();
    if(corner_button)
    {
        corner_button->setText(QString::fromUtf8(u8"全选"));
        //        connect(corner_button,SIGNAL(clicked()),this,SLOT([](){qDebug() << "push";}));
        connect(corner_button,SIGNAL(clicked()),this,SLOT(on_select_all_rows()));
        corner_button->installEventFilter(this);
        QStyleOptionHeader opt;
        opt.text = corner_button->text();
        QSize s = (corner_button->style()->sizeFromContents(QStyle::CT_HeaderSection,&opt,QSize(),corner_button).expandedTo(QApplication::globalStrut()));
        if(s.isValid())
        {
            ui->tableViewUpload->verticalHeader()->setMidLineWidth(s.width());
        }
        qDebug() << "ok";
    }

    m_excel_reader->set_excel_header(m_excel_header);


    //设置webservice
    soap_init(&m_web_service);
    soap_set_mode(&m_web_service, SOAP_C_UTFSTRING);

    //设置文件传输
    //0是下载，1是上传
    m_file_transports = CTransmitFile::CreateInstance(1);
    if(m_file_transports == NULL)
    {
        qDebug() << "createInstance file transports failed!";
    }
    else
    {
        m_file_transports->SetDataChunkSize(327680);
        qDebug() << "createInstance file transports successfully!";
    }
}

MainWindow::~MainWindow()
{
    if(m_file_transports)
    {
        CTransmitFile::DestroyInstance(m_file_transports);
    }
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QMainWindow::mousePressEvent(event);
}

bool MainWindow::eventFilter(QObject *o, QEvent *e)
{
    if (e->type() == QEvent::Paint)
    {
        //此处为了解决tableview左上角cornerbutton的样式设置
        QAbstractButton* btn = qobject_cast<QAbstractButton*>(o);
        if (btn)
        {
            // paint by hand (borrowed from QTableCornerButton)
            QStyleOptionHeader opt;
            opt.init(btn);
            QStyle::State state = QStyle::State_None;
            if (btn->isEnabled())
                state |= QStyle::State_Enabled;
            if (btn->isActiveWindow())
                state |= QStyle::State_Active;
            if (btn->isDown())
                state |= QStyle::State_Sunken;
            opt.state = state;
            opt.rect = btn->rect();
            opt.text = btn->text(); // this line is the only difference to QTableCornerButton
            opt.position = QStyleOptionHeader::OnlyOneSection;
            QStylePainter painter(btn);
            painter.drawControl(QStyle::CE_Header, opt);
            return true; // eat event
        }
    }
    return false;
}

void MainWindow::on_pushButtonSearch_clicked()
{
    //检查批次号输入
    if(!check_batch_num_input())
    {
        QMessageBox::critical(this,QString::fromUtf8(u8"错误"),QString::fromUtf8(u8"请输入批次号！"));
        return;
    }
    //查询数据库，检查该批次号的状态
    //    QString server_info = QString::fromUtf8(u8"192.168.3.61@sa@xwline_2012@图书论文2016@");
    //    QString sql_search_batch_num = QString::fromUtf8(u8"select 出版者,书名,副书名,分辑,丛书名,ISBN,作者,出版日期,定价,格式,版权页,封面,其它,备注,作品语种,文件状态,处理状态,文件个数,编号,到岗时间,授权方,被授权方,授权起始时,授权结束时,文件名,副丛书名,丛书卷号,丛书作者,版本说明,载体类型,著作类型,适用读者,用途,订单年 from dbo.V_接收登记_详细信息  where 批次号 = 'DZ210122'");
    //    QtSoapMessage web_service_request_message;
    //    web_service_request_message.setMethod("executeSql","http://Fantasy/WebServiceDemo/");
    //    web_service_request_message.addMethodArgument("serverInfo","",server_info);
    //    web_service_request_message.addMethodArgument("sSql","",sql_search_batch_num);
    //    QString web_service_request_xml = web_service_request_message.toXmlString();
    //    qDebug() << web_service_request_xml;
    //    qDebug() << "11";
    //    m_web_service->setAction("http://Fantasy/WebServiceDemo/executeSql");
    //    m_web_service->setHost("218.26.30.70");
    //    m_web_service->submitRequest(web_service_request_message,"/WebServiceDemo/Service1.asmx");
    // 使用qtsoap失败

    //    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    //    QNetworkRequest req;
    //    req.setHeader(QNetworkRequest::UserAgentHeader,NULL);
    //    req.setUrl(QUrl("http://218.26.30.70:81/WebServiceDemo/Service1.asmx"));
    //    req.setHeader(QNetworkRequest::ContentTypeHeader,("text/xml;charst=utf-8"));
    //    req.setRawHeader("SOAPAction","http://Fantasy/WebServiceDemo/executeSql");
    //    QString req_body = QString::fromUtf8(u8"<?xml version='1.0' encoding='utf-8'?>\r\n<soap:Envelope xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xmlns:xsd='http://www.w3.org/2001/XMLSchema' xmlns:soapenc='http://schemas.xmlsoap.org/soap/encoding/' xmlns:tns='http://Fantasy/WebServiceDemo/' xmlns:types='http://Fantasy/WebServiceDemo/encodedTypes' xmlns:soap='http://schemas.xmlsoap.org/soap/envelope/'> <soap:Body soap:encodingStyle='http://schemas.xmlsoap.org/soap/encoding/'><tns:executeSql><serverInfo xsi:type='xsd:string'>192.168.3.61@sa@xwline_2012@图书论文2016@</serverInfo><sSql xsi:type='xsd:string'>select 出版者,书名,副书名,分辑,丛书名,ISBN,作者,出版日期,定价,格式,版权页,封面,其它,备注,作品语种,文件状态,处理状态,文件个数,编号,到岗时间,授权方,被授权方,授权起始时,授权结束时,文件名,副丛书名,丛书卷号,丛书作者,版本说明,载体类型,著作类型,适用读者,用途,订单年 from dbo.V_接收登记_详细信息  where 批次号 = 'DZ210122'</sSql></tns:executeSql></soap:Body></soap:Envelope>");
    ////    QString req_body = QString::fromUtf8(u8"<?xml version='1.0' encoding='utf-8'?>\r\n<soap:Envelope xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xmlns:xsd='http://www.w3.org/2001/XMLSchema' xmlns:soapenc='http://schemas.xmlsoap.org/soap/encoding/' xmlns:tns='http://Fantasy/WebServiceDemo/' xmlns:types='http://Fantasy/WebServiceDemo/encodedTypes' xmlns:soap='http://schemas.xmlsoap.org/soap/envelope/'> <soap:Body soap:encodingStyle='http://schemas.xmlsoap.org/soap/encoding/'><tns:executeSql><serverInfo xsi:type='xsd:string'>%1</serverInfo><sSql xsi:type='xsd:string'>%2</sSql></tns:executeSql></soap:Body></soap:Envelope>").arg(server_info).arg(sql_search_batch_num);
    //    qDebug() << req_body;
    //    QNetworkReply *rep = manager->post(req,req_body.toUtf8());
    //    QAbstractSocket::connect(rep,&QNetworkReply::finished,[=](){
    //        QString data = rep->readAll();
    //        qDebug() << data;
    //    });
    //使用qnetworkaccessmanager失败

    //    std::wstring web_info = std::wstring(L"192.168.3.61@sa@xwline_2012@图书论文2016@");
    std::wstring web_info = m_db_key.toStdWString();
    auto sql_content = QString::fromStdWString(std::wstring(LR"(select 出版者 as publisher,
                                                   书名		as bookname,
                                                   副书名 	as vicebookname,
                                                   分辑		as bookpart,
                                                   丛书名 	as bookparentname,
                                                   ISBN 	as isbn,
                                                   作者  	as author,
                                                   出版日期	as publishdate,
                                                   定价  	as price,
                                                   格式  	as format,
                                                   版权页	as copyrightpage,
                                                   封面 		as cover,
                                                   其它   	as other,
                                                   备注   	as remark,
                                                   作品语种 	as language,
                                                   文件状态 	as filestate,
                                                   处理状态 	as processstate,
                                                   文件个数 	as filenums,
                                                   编号   	as serialnum,
                                                   到岗时间 	as arrivaltime,
                                                   授权方  	as franchisor,
                                                   被授权方 	as authorizedparty,
                                                   授权起始时 as authorizationstarttime,
                                                   授权结束时 as authorizationendtime,
                                                   文件名 	as filename,
                                                   副丛书名 	as vicebookparentname,
                                                   丛书卷号 	as bookparentnum,
                                                   丛书作者 	as bookparentauthor,
                                                   版本说明	as versionnote,
                                                   载体类型	as carriertype,
                                                   著作类型	as booktype,
                                                   适用读者	as applicablereader,
                                                   用途   	as purpose,
                                                   订单年  	as ordersyear from dbo.V_接收登记_详细信息  where 批次号 = '%1')")).arg(ui->lineEditBatchNum->text());
    std::wstring web_result;
    qDebug() << sql_content;
    int ret = soap_call_SER__executeSql(&m_web_service, NULL, NULL, web_info, sql_content.toStdWString(), web_result);
    //    int ret = soap_call_SER__executeSql(&m_web_service, "http://192.168.1.200:81/WebServiceDemo/Service1.asmx", NULL, web_info, sql_content.toStdWString(), web_result);
    //    int ret = soap_call_ns1__executeSql(&m_web_service, NULL, NULL, web_info, sql_content.toStdWString(), web_result);
    if (ret == SOAP_OK)
    {
        //        std::wcout.imbue(std::locale("chs"));
        //        std::wcout << web_result.size() << std::endl;
        //        std::wcout << web_result << std::endl;
        QString msg_data;
        ret = check_web_service_query_result(web_result,msg_data,web_service_type::SER_SQL_QUERY);
        if(ret != -1)
        {
            if(ret  == 0)
            {
                QMessageBox::warning(this,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"没有历史上传记录。"));
            }
            else
            {
                qDebug() << "there are " << ret << " records.";
                qDebug() << "the xml data is: " << msg_data;
                QMessageBox::about(this,QString::fromUtf8(u8"提示"),QString::fromUtf8(u8"查询到%1条记录，%2曾进行过导入。").arg(ret).arg(ui->lineEditBatchNum->text()));
                reset_data_model();

                //处理xml数据到表格model
                auto temp_thread = new MyProcessXmlDataThread(this,msg_data);
//                connect(temp_thread,SIGNAL(data_update(int)),this,SLOT(on_thread_data_update(int )));
                connect(temp_thread,SIGNAL(finished()),this,SLOT(on_thread_data_finish()));
                m_upload_vheadeview->clearAllStates();
                temp_thread->start();


                // process_xml_data_to_model(msg_data);
                m_cur_tabview_state = tableview_show_type::SHOW_QUERY_DATA;
            }
            write_to_log_dock(QString::fromUtf8(u8"批次号[<span style=\"color:#F00\">%1</span>]查询到[<span style=\"color:#F00\">%2</span>]条记录。").arg(m_cur_batch_number).arg(ret));
        }
        else
        {
            qDebug() << "ret " << ret;
            write_to_log_dock(QString::fromUtf8(u8"批次号[<span style=\"color:#F00\">%1</span>]查询错误，错误原因：<b>%2</b>").arg(m_cur_batch_number).arg(msg_data));
        }
    }
    else
    {
        QMessageBox::warning(this,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"服务器连接失败，请稍后再试！"));
    }
    get_data_from_db_to_upload_data();
    //    m_statusbar_label->setText(ui->lineEditBatchNum->text());
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
void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if(current.isValid())
    {
        //        m_statusbar_label->setText(QString::fromUtf8(u8"当前单元格：")+QString::number(current.row())+QString::fromUtf8(u8"行，")+QString::number(current.column())+QString::fromUtf8(u8"列"));
    }
}





bool MainWindow::check_excel_header(QStringList &target_header)
{
    if(m_excel_header.size() != target_header.size())
    {
        QMessageBox::critical(this,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"模板文件表头长度异常！"));
        return false;
    }
    else
    {
        for(int i = 0 ; i < m_excel_header.size(); ++i)
        {
            if(m_excel_header[i] != target_header[i])
            {
                QMessageBox::critical(this,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"模板文件表头内容异常,[")+QString::number(i+1)+QString::fromUtf8(u8"]列,配置内容为:")+m_excel_header[i] +QString::fromUtf8(u8",实际内容为:")+target_header[i]);
                return false;
            }
        }
    }
    return true;
}

int MainWindow::check_web_service_query_result(_IN_ std::wstring &web_result,_OUT_ QString &msg_data, _IN_ web_service_type type)
{
    auto split_tag = QString::fromUtf8(u8"★");
    int ret = -1;
    bool is_ok = false;
    auto result_str = QString::fromStdWString(web_result);
    ret = result_str.indexOf(split_tag);
    if(ret == -1)
    {
        msg_data = result_str;
        return ret;
    }
    auto result_splited = result_str.split(split_tag);
    switch(type)
    {
    case web_service_type::SER_SQL_QUERY:
    {
        ret = result_splited[0].toInt(&is_ok);
        if(!is_ok)
        {
            return -1;
        }
        msg_data = result_splited[1];
    }
    break;
    case web_service_type::SER_STORE_PROCESS:
    {
        auto result_data_splited = result_splited[1].split(QString::fromUtf8(u8"$"));
        foreach(auto data,result_data_splited)
        {
            auto data_split = data.split(QString::fromUtf8(u8"="));
            if(data_split[0] == QString::fromUtf8(u8"@nRet"))
            {
                ret = data_split[1].toInt(&is_ok);
                if(!is_ok)
                {
                    return -1;
                }
            }
            else if(data_split[0] == QString::fromUtf8(u8"@cError"))
            {
                msg_data = data_split[1];
            }
            else if(data_split[0] == QString::fromUtf8(u8"@cErrMsg"))
            {
                msg_data = data_split[1];
            }
        }
    }
    break;
    }
    return  ret;
}


void MainWindow::process_xml_data_to_model(QString &xml_data)
{
    QDomDocument doc;
    doc.setContent(xml_data);
    auto root = doc.firstChildElement(QString::fromUtf8(u8"NewDataSet"));
    auto node = root.firstChild();
    int count = 0;
    int model_row = 0;
    int model_col = 0;
    reset_data_model();

    while(!node.isNull())
    {
        model_col = 0;
        //        qDebug()<< count << ":" << node.toElement().text();
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(QString::number(count+1)));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("publisher").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("bookname").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("vicebookname").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("bookpart").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("bookparentname").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("vicebookparentname").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("bookparentnum").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("isbn").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("author").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("bookparentauthor").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("publishdate").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("versionnote").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("price").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("format").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("copyrightpage").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("cover").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("other").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("remark").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("language").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("authorizationstarttime").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("authorizationendtime").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("franchisor").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("authorizedparty").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("filename").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("carriertype").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("booktype").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("applicablereader").text()));
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("purpose").text()));
        model_col += 3;
        m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("ordersyear").text()));
        if(node.firstChildElement("processstate").text() == QString::fromUtf8(u8"已处理"))
        {
            m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(QString::fromUtf8(u8"已提交")));
            /*            if (v == BookState.Imported)
                return "已导入,未上传";
            else if (v == BookState.Uploaded)
                return "已上传,未提交";
            else if (v == BookState.Submited)
                return "已提交";
            else
                return null;*/
        }
        else if(node.firstChildElement("filestate").text() == QString::fromUtf8(u8"True"))
        {
            m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(QString::fromUtf8(u8"已上传,未提交")));
        }
        else
        {
            m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(QString::fromUtf8(u8"已导入,未上传")));
        }
        ui->tableView->resizeColumnsToContents();
        model_col = 0;
        m_model_upload_data->setItem(model_row,model_col++,new QStandardItem(QString::number(count+1)));
        m_model_upload_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("serialnum").text()));
        m_model_upload_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("bookname").text()));
        m_model_upload_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("bookpart").text()));
        m_model_upload_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("filenums").text()));
        m_model_upload_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("filenums").text() == QString::fromUtf8(u8"0")?QString::fromUtf8(u8"否，未上传"):QString::fromUtf8(u8"是")));
        m_model_upload_data->setItem(model_row,model_col++,new QStandardItem(node.firstChildElement("processstate").text() == QString::fromUtf8(u8"已处理")?QString::fromUtf8(u8"已提交"):QString::fromUtf8(u8"未提交")));




        //                auto temp_item = new QStandardItem(temp_str);
        //                m_model_excel_check_state.setItem(model_i,model_j,temp_item);
        count++;
        model_row++;
        node = node.nextSibling();
    }
    //    m_model_upload_data->insertRows(0,m_model_upload_data->rowCount());
    add_button_to_upload_model();

    ui->tableViewUpload->resizeColumnsToContents();
    qDebug() << "count :" << count;

}


void MainWindow::on_thread_data_finish()
{
    //    ui->tableViewUpload->show();
    //    ui->tableView->show();
//    QMessageBox::information(this,QString::fromUtf8(u8"提示"),QString::fromUtf8(u8"处理完毕。"));
    for(auto i = 0; i < m_book_info_map.size(); ++i)
    {
        int model_col = 0;
        auto book = m_book_info_map[i];
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(QString::number(i+1)));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.publisher));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.bookname));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.vicebookname));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.bookpart));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.bookparentname));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.vicebookparentname));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.bookparentnum));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.isbn));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.author));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.bookparentauthor));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.publishdate));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.versionnote));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.price));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.format));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.copyrightpage));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.cover));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.other));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.remark));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.language));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.authorizationstarttime));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.authorizationendtime));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.franchisor));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.authorizedparty));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.filename));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.carriertype));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.booktype));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.applicablereader));
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.purpose));
        model_col += 3;
        m_model_excel_data->setItem(i,model_col++,new QStandardItem(book.ordersyear));
        if(book.processstate == QString::fromUtf8(u8"已处理"))
        {
            m_model_excel_data->setItem(i,model_col++,new QStandardItem(QString::fromUtf8(u8"已提交")));
            /*            if (v == BookState.Imported)
                return "已导入,未上传";
            else if (v == BookState.Uploaded)
                return "已上传,未提交";
            else if (v == BookState.Submited)
                return "已提交";
            else
                return null;*/
        }
        else if(book.filestate == QString::fromUtf8(u8"True"))
        {
            m_model_excel_data->setItem(i,model_col++,new QStandardItem(QString::fromUtf8(u8"已上传,未提交")));
        }
        else
        {
            m_model_excel_data->setItem(i,model_col++,new QStandardItem(QString::fromUtf8(u8"已导入,未上传")));
        }

        model_col = 0;
        m_model_upload_data->setItem(i,model_col++,new QStandardItem(QString::number(i+1)));
        m_model_upload_data->setItem(i,model_col++,new QStandardItem(book.serialnum));
        m_model_upload_data->setItem(i,model_col++,new QStandardItem(book.bookname));
        m_model_upload_data->setItem(i,model_col++,new QStandardItem(book.bookpart));
        m_model_upload_data->setItem(i,model_col++,new QStandardItem(book.filenums));
        m_model_upload_data->setItem(i,model_col++,new QStandardItem(book.filenums == QString::fromUtf8(u8"0")?QString::fromUtf8(u8"否，未上传"):QString::fromUtf8(u8"是")));
        m_model_upload_data->setItem(i,model_col++,new QStandardItem(book.processstate == QString::fromUtf8(u8"已处理")?QString::fromUtf8(u8"已提交"):QString::fromUtf8(u8"未提交")));
        m_upload_vheadeview->SetState(i,false);
        m_model_upload_data->setHeaderData(i,Qt::Vertical," ");
    }
    add_button_to_upload_model();
    ui->tableView->resizeColumnsToContents();
    ui->tableViewUpload->resizeColumnsToContents();
}

void MainWindow::resizeEvent(QResizeEvent *size)
{
    Q_UNUSED(size)
    QList<int> t;
    t << height()/2;
    t << height()/2;
    ui->splitter->setSizes(t);

}

int MainWindow::submit(int row)
{
    //TODO
    QString sql_content;
    sql_content += QString::fromUtf8(u8"@cPostName#接收登记#VarChar#in#$");
    sql_content += QString::fromUtf8(u8"@cSN#%1#VarChar#in#$").arg(m_model_upload_data->item(row,1)->text());
    sql_content += QString::fromUtf8(u8"@dtRechTime#%1#VarChar#in#$").arg(m_arrival_time_map[m_model_upload_data->item(row,1)->text()]);
    sql_content += QString::fromUtf8(u8"@nRet##int#out#$@cErrMsg##VarChar#out#$");
    qDebug() << sql_content;
    //        QMessageBox::information(this,QString::fromUtf8(u8"提示"),sql_content);
    QString err_msg;
    std::wstring web_result;
    int ret = soap_call_SER__executeStorageProcess(&m_web_service,
                                                   NULL,
                                                   NULL,
                                                   m_db_key.toStdWString(),
                                                   QString::fromUtf8(u8"Proc_接收登记_SubmitTask").toStdWString(),
                                                   sql_content.toStdWString(),
                                                   web_result);
    if (ret == SOAP_OK)
    {
        QString msg_data;
        ret = check_web_service_query_result(web_result,msg_data,web_service_type::SER_STORE_PROCESS);
        qDebug() << "ret ::: " << ret;
       if(ret != 0)
        {
            //成功
            qDebug() << "execute storage process for upload book infos successfully!";
            qDebug() << QString::fromStdWString(web_result);
            m_model_upload_data->setItem(row,m_model_upload_data->columnCount()-2,new QStandardItem(QString::fromUtf8(u8"已提交")));
            if(m_model_excel_data->hasIndex(row,m_model_excel_data->columnCount()-1))
            {
                m_model_excel_data->setItem(row,m_model_excel_data->columnCount()-1,new QStandardItem(QString::fromUtf8(u8"已提交")));
            }
            write_to_log_dock(QString::fromUtf8(u8"[<span style=\"color:#F00\">%1</span>]-《<span style=\"color:#F00\">%2</span>》篇提交成功！").arg(m_model_upload_data->item(row,1)->text()).arg(m_model_upload_data->item(row,2)->text()));
        }
        else
        {
            //失败
            //TODO
            qDebug() << "execute storage process for upload book infos failed!";
            err_msg += QString::fromUtf8(u8"%1:%2.\n").arg(m_model_upload_data->item(row,2)->text()).arg(msg_data);
            m_model_upload_data->setItem(row,m_model_upload_data->columnCount()-2,new QStandardItem(QString::fromUtf8(u8"提交失败")));
            write_to_log_dock(QString::fromUtf8(u8"[<span style=\"color:#F00\">%1</span>]-《<span style=\"color:#F00\">%2</span>》篇提交失败，原因：<b>%3</b>").arg(m_model_upload_data->item(row,1)->text()).arg(m_model_upload_data->item(row,2)->text()).arg(msg_data));
            return -1;
        }
    }
    else
    {
        m_model_upload_data->setItem(row,m_model_upload_data->columnCount()-2,new QStandardItem(QString::fromUtf8(u8"提交失败")));
        return -2;
    }
    return 0;
}


void MainWindow::process_json_data_from_web(_IN_ QString &json_data,
                                            _OUT_ QString &server_id,
                                            _OUT_ QString &file_server_ip,
                                            _OUT_ QString &file_server_port,
                                            _OUT_ QString &file_server_root)
{
    QJsonParseError temp_err;
    QJsonDocument web_result_json = QJsonDocument::fromJson(json_data.toUtf8().data(),&temp_err);
    qDebug() << temp_err.error;
    if(temp_err.error != QJsonParseError::NoError)
    {
        qDebug() << temp_err.errorString();
    }
    else
    {
        foreach(auto one,web_result_json.array())
        {
            auto one_object = one.toObject();
            if(!one_object.isEmpty())
            {
                if(one_object.value("LineType").toInt() != MyGlobal::LINE_TYPE)
                {
                    continue;
                }
                auto post_list = one_object.value("PostList");
                qDebug() << one_object.value("ServerIp").toString();

                if(post_list.isArray())
                {
                    bool found = false;
                    QJsonObject target;
                    foreach(auto post_one,post_list.toArray())
                    {
                        auto post_one_object = post_one.toObject();
                        if(post_one_object.value("PostName").toString() != QString::fromUtf8(u8"接收登记"))
                        {
                            continue;
                        }
                        found = true;
                        target = post_one_object;
                        break;
                    }
                    auto get_target = [&](QJsonObject& a){
                        server_id = QString::number(a.value("ServerId").toInt());
                        file_server_ip = a.value("ServerIp").toString();
                        file_server_port = QString::number(a.value("ServerPort").toInt());
                        file_server_root = a.value("RootDir").toString();
                    };
                    qDebug() << "have:"<<target.value("ServerIp").toString();
                    qDebug() << "have:"<<target.value("ServerPort").toInt();
                    if(found == false || target.value("ServerIp").isNull())
                    {
                        get_target(one_object);
                    }
                    else
                    {
                        get_target(target);
                    }
                    break;
                }
            }
        }
    }
}

void MainWindow::reset_data_model()
{
    m_model_excel_data->clear();
    m_model_excel_data->setHorizontalHeaderLabels(m_excel_header);
    m_model_excel_data->setHorizontalHeaderItem(m_model_excel_data->columnCount(),new QStandardItem(QString::fromUtf8(u8"图书状态")));
    m_model_upload_data->clear();
    m_model_upload_data->setHorizontalHeaderLabels(m_upload_header);
    ui->tableViewUpload->resizeColumnsToContents();

}

void MainWindow::reset_error_show_model()
{
    m_model_excel_check_state->clear();
    m_model_excel_check_state->setHorizontalHeaderLabels(m_check_state_header);

}

void MainWindow::add_button_to_upload_model()
{
    for(int i = 0; i< m_model_upload_data->rowCount(); ++i)
    {
        QPushButton* button = new QPushButton(QString::fromUtf8(u8"篇提交"));
        button->setProperty("row",i);
        connect(button,SIGNAL(clicked()),this,SLOT(on_pushButtonIndividualBookSubmit()));
        ui->tableViewUpload->setIndexWidget(m_model_upload_data->index(i,m_model_upload_data->columnCount()-1),button);
    }
}

QStringList MainWindow::get_all_file_path(file_process_type type,QString &dir_name, quint64 total_size, QString &err_msg)
{
    QStringList result;
    //    QQueue<QString> dir_queue;
    //    dir_queue.push_back(dir_name);
    //    while(!dir_queue.isEmpty())
    //    {
    //        QDir temp_dir(dir_queue.front());
    //        dir_queue.pop_front();
    //        QFileInfoList file_info = temp_dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    //    }
    QDir root_dir(dir_name);
    QDirIterator dir_iter(dir_name,QDir::Files | QDir::NoDotAndDotDot,QDirIterator::Subdirectories);
    QRegExp file_rule(QString::fromUtf8(u8".+\\.\\d{4}\\.[tT][iI][fF]"));
    QSet<QString> code_check;
    while(dir_iter.hasNext())
    {
        dir_iter.next();
        QFileInfo file_info = dir_iter.fileInfo();
        QString file_name = file_info.fileName();
        qDebug() << "file_name:" << file_name;
        QString file_suffix = file_info.suffix();
        if(file_name == QString::fromUtf8(u8"Thumbs.db") || file_name.startsWith(QString::fromUtf8(u8"~$")))
        {
            dir_iter.next();
            continue;
        }
        if(file_suffix.toLower() == QString::fromUtf8(u8"zip") || file_suffix.toLower() == QString::fromUtf8(u8"rar"))
        {
            //处理压缩文件，从zip和rar中拿出文件名
            //目前没有好的方法处理压缩文件
            //TODO 处理压缩文件
            //QStringList file_names_in_compress = get_name_from_compress(file_info.fullname);
            switch(type) {
            case file_process_type::PROC_SPECIAL:
            {
                auto compressed_filepath = file_info.absoluteFilePath();
                auto filenames_in_compressed = get_all_filename_from_compressed(compressed_filepath);
                if(!filenames_in_compressed.isEmpty())
                {
                    foreach(auto filename_inside,filenames_in_compressed)
                    {
                        if(file_rule.exactMatch(filename_inside))
                        {
                            code_check.insert(filename_inside.split(".").first());
                        }
                        else
                        {
                            err_msg += QString::fromUtf8(u8"[%1]不符合tif命名格式。\n").arg(filename_inside);
                        }

                    }
                    result.append(compressed_filepath);
                    total_size += file_info.size();
                }
                else
                {
                    err_msg += QString::fromUtf8(u8"[%1]压缩文件内容为空！\n").arg(compressed_filepath);
                }
            }
            break;
            case file_process_type::PROC_NORMAL:
            {
                result.append(file_info.absoluteFilePath());
                total_size += file_info.size();
            }
            break;
            }
        }
        else
        {
            //处理普通文件
            switch(type) {
            case file_process_type::PROC_SPECIAL:
            {
                if(file_rule.exactMatch(file_name))
                {
                    code_check.insert(file_name.split(".").first());
                    result.append(file_info.absoluteFilePath());
                    total_size += file_info.size();
                }
                else
                {
                    err_msg += QString::fromUtf8(u8"[%1]不符合tif命名格式。\n").arg(file_name);
                }
            }
            break;
            case file_process_type::PROC_NORMAL:
            {
                result.append(file_info.absoluteFilePath());
                total_size += file_info.size();
            }
            break;
            }
        }
    }
    switch(type)
    {
    case file_process_type::PROC_SPECIAL:
    {
        if(code_check.count()>1)
        {
            err_msg += QString::fromUtf8(u8"tif文件中存在多个编号：");
            foreach(auto code,code_check)
            {
                err_msg += QString::fromUtf8(u8"%1;").arg(code);
            }
        }
    }
    break;
    case file_process_type::PROC_NORMAL:
    {
    }
    break;
    }
    return result;
}

void MainWindow::write_to_log_dock(QString msg)
{
    auto time = QDateTime::currentDateTime();
    QString content = QString::fromUtf8(u8"%1:%2").arg(time.time().toString()).arg(msg);
    auto temp = dynamic_cast<QTextEdit*>(m_log_dock->widget());
    temp->append(content);
    QTextDocument doc;
    doc.setHtml(msg);
    qInfo() << doc.toPlainText();
    //    m_log_edit->append(content);
}

QStringList MainWindow::get_all_filename_from_compressed(QString compressed_filepath)
{
    QString cmd = QString::fromUtf8(u8"./7-Zip/7z.exe");
    //    QStringList arguments({QString::fromUtf8(u8"l"),QString::fromUtf8(u8"E:\\code\\3690009-图文编审调整存储过程db.rar")});
    QStringList arguments({QString::fromUtf8(u8"l"),compressed_filepath});
    QStringList result;
    //    qDebug() << cmd;
    QProcess p;
    p.start(cmd,arguments);
    p.waitForStarted();
    p.waitForFinished();
    auto cmd_out = QString::fromLocal8Bit(p.readAllStandardOutput());
    //    qDebug()<< cmd_out;
    auto cmd_out_lines = cmd_out.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
    foreach(auto line,cmd_out_lines)
    {
        //        qDebug() << line;
    }
    auto main_body = cmd_out_lines.filter(QRegExp(".* .* [^ ]{5} \\d* \\d* .*"));
    //    qDebug() << "main_body:";
    foreach(auto line,main_body)
    {
        if(line.indexOf(QString::fromUtf8(u8"....A")) != -1)
        {
            //            qDebug() << line;
            line.remove(0,line.lastIndexOf(" ")+1);
            //            qDebug() << "after process: " << line;
            line.remove(0,line.lastIndexOf("\\")+1);
            //            qDebug() << "file name: " << line;
            result.push_back(line);
        }
    }
    //    qDebug()<<QString::fromLocal8Bit(p.readAllStandardError());
    return result;
}

void MainWindow::init_excel_checker()
{
    QVector<ExcelFieldRule> excel_check_rules;
    int i = 0;
    if(m_cur_batch_number.toLower().startsWith(MyGlobal::XK_PREFIX))
    {
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromUtf8(u8"必须为数字"),QString::fromUtf8(u8"\\d*")));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromUtf8(u8"YYYYmm"),QString::fromUtf8(u8"\\d{4}(0|1)\\d")));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromUtf8(u8"只能为两位小数的数字"),QString::fromUtf8(u8"\\d*\\.?\\d\\d$")));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromUtf8(u8"YYYYmmdd"),QString::fromUtf8(u8"\\d{4}(0|1)\\d\\d\\d")));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromUtf8(u8"YYYYmmdd"),QString::fromUtf8(u8"\\d{4}(0|1)\\d\\d\\d")));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromUtf8(u8"只能为是或否"),QString::fromUtf8(u8"(\u662f|\u5426)")));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromUtf8(u8"只能为是或否"),QString::fromUtf8(u8"(\u662f|\u5426)")));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromUtf8(u8"只能为是或否"),QString::fromUtf8(u8"(\u662f|\u5426)")));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromUtf8(u8"YYYY"),QString::fromUtf8(u8"\\d{4}$")));
    }
//    else if(m_cur_batch_number.toLower().startsWith(MyGlobal::DZ_PREFIX))
    else
    {
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromUtf8(u8"必须为数字"),QString::fromUtf8(u8"\\d*")));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromUtf8(u8"YYYYmm"),QString::fromUtf8(u8"\\d{4}(0|1)\\d")));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromUtf8(u8"只能为两位小数的数字"),QString::fromUtf8(u8"\\d*\\.?\\d?\\d?$")));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromUtf8(u8"YYYYmmdd"),QString::fromUtf8(u8"\\d{4}(0|1)\\d\\d\\d")));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromUtf8(u8"YYYYmmdd"),QString::fromUtf8(u8"\\d{4}(0|1)\\d\\d\\d")));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_NOT_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_FALSE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_TRUE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_TRUE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_TRUE));
        excel_check_rules.push_back(ExcelFieldRule(m_excel_header.at(i++),ExcelFieldRule::CONTENT_EMPTY_ALLOWD,ExcelFieldRule::FORMATED_TRUE,QString::fromUtf8(u8"YYYY"),QString::fromUtf8(u8"\\d{4}$")));

    }
    ExcelChecker *temp_checker = new ExcelChecker();
    temp_checker->set_rules(excel_check_rules);
    m_excel_reader->set_checker(temp_checker);

}

bool MainWindow::get_data_from_db_to_upload_data()
{
    std::wstring web_ret;
    QString sql_content;
    //更新下方表格，显示那些未上传文件的记录
    sql_content = QString::fromUtf8(u8"select 书名 as bookname,编号 as code,到岗时间 as arrivetime,分辑 as bookpart,文件个数 as filenum from FLOW_岗位信息表_接收登记 where 批次号='%1' and 处理状态='正处理' ").arg(m_cur_batch_number);
    //    sql_content = QString::fromUtf8(u8"select * from FLOW_岗位信息表_接收登记 where 批次号='%1' and 处理状态='正处理' and 有文件否='否'").arg(m_cur_batch_number);
    int ret = soap_call_SER__executeSql(&m_web_service,NULL,NULL,m_db_key.toStdWString(),sql_content.toStdWString(),web_ret);
    if(ret == SOAP_OK)
    {
        QString ret_data;
        ret = check_web_service_query_result(web_ret,ret_data,web_service_type::SER_SQL_QUERY);
        if(ret != -1)
        {
            if(ret  == 0)
            {
                QMessageBox::warning(this,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"查询到%1条记录，没有需要上传或者提交的记录。").arg(ret));
                m_model_upload_data->clear();
                m_model_upload_data->setHorizontalHeaderLabels(m_upload_header);
                ui->tableViewUpload->resizeColumnsToContents();
                return false;
            }
            else
            {
                qDebug() << "there are " << ret << " records.";
                qDebug() << "the xml data is: " << ret_data;
                //QMessageBox::about(this,QString::fromUtf8(u8"提示"),QString::fromUtf8(u8"查询到%1条记录，%2曾进行过导入。").arg(ret).arg(ui->lineEditBatchNum->text()));
                QDomDocument doc;
                doc.setContent(ret_data);
                auto node = doc.firstChild();
                node = node.firstChild();
                int row = 0;
                m_model_upload_data->clear();
                m_model_upload_data->setHorizontalHeaderLabels(m_upload_header);
                while(!node.isNull())
                {
                    auto element = node.toElement();
                    int col = 0;
                    m_model_upload_data->setItem(row,col++,new QStandardItem(QString::number(row + 1)));
                    m_model_upload_data->setItem(row,col++,new QStandardItem(element.firstChildElement(QString::fromUtf8(u8"code")).text()));
                    m_model_upload_data->setItem(row,col++,new QStandardItem(element.firstChildElement(QString::fromUtf8(u8"bookname")).text()));
                    m_model_upload_data->setItem(row,col++,new QStandardItem(element.firstChildElement(QString::fromUtf8(u8"bookpart")).text()));
                    m_model_upload_data->setItem(row,col++,new QStandardItem(element.firstChildElement(QString::fromUtf8(u8"filenum")).text()));
                    m_model_upload_data->setItem(row,col++,new QStandardItem(element.firstChildElement(QString::fromUtf8(u8"filenum")).text()==QString::fromUtf8(u8"0")?QString::fromUtf8(u8"否"):QString::fromUtf8(u8"是")));
                    m_model_upload_data->setItem(row,col++,new QStandardItem(QString::fromUtf8(u8"未提交")));
                    m_model_upload_data->setHeaderData(row,Qt::Vertical," ");
                    m_arrival_time_map[element.firstChildElement(QString::fromUtf8(u8"code")).text()] = element.firstChildElement(QString::fromUtf8(u8"arrivetime")).text();
                    row += 1;
                    node = node.nextSibling();
                }
                add_button_to_upload_model();
                ui->tableViewUpload->resizeColumnsToContents();
                if(row == 0)
                {
                    QMessageBox::warning(this,QString::fromUtf8(u8"提示"),QString::fromUtf8(u8"批次[%1]没有需要上传文件的图书。").arg(m_cur_batch_number));
                    return false;
                }
            }
        }
    }
    else
    {
        QMessageBox::warning(this,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"连接服务器失败，请稍后再试。"));
        write_to_log_dock(QString::fromUtf8(u8"查询需要上传或者提交的记录失败，原因：<b>%1</b>。").arg(web_ret));
        return false;

    }
    return true;
}

void MainWindow::lock_all_input(bool is_lock)
{
    ui->pushButtonBatchCommit->setEnabled(!is_lock);
    ui->pushButtonBulkBookCommit->setEnabled(!is_lock);
    ui->pushButtonChooseFile->setEnabled(!is_lock);
    ui->pushButtonOpenDir->setEnabled(!is_lock);
    ui->pushButtonSearch->setEnabled(!is_lock);
    ui->pushButtonUploadDB->setEnabled(!is_lock);
    ui->lineEditBatchNum->setEnabled(!is_lock);
    for(int i = 0; i < m_model_upload_data->rowCount(); ++i)
    {
        ui->tableViewUpload->indexWidget(m_model_upload_data->index(i,m_model_upload_data->columnCount()-1))->setEnabled(!is_lock);
    }
}

void MainWindow::on_pushButtonOpenDir_clicked()
{
    if(m_cur_batch_number.isEmpty())
    {
        QMessageBox::warning(this,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"请输入批次号！"));
        return;
    }

    if(get_data_from_db_to_upload_data())
    {
        if(m_model_upload_data->rowCount() == 0)
        {
            return;
        }
        m_cur_open_dir = QFileDialog::getExistingDirectory(this,QString::fromUtf8(u8"选择上传文件夹"),QString::fromUtf8(u8"./"));
        if(m_cur_open_dir.isEmpty())
        {
            return;
        }
        //    ui->labelCurrentDir->setText(m_cur_open_dir);
        //    ui->statusbar->showMessage(QString::fromUtf8(u8"打开文件夹[%1]").arg(m_cur_open_dir),5000);
        m_statusbar_label->setText(QString::fromUtf8(u8"当前打开文件夹：[%1]").arg(m_cur_open_dir));
        write_to_log_dock(QString::fromUtf8(u8"打开文件夹夹[<span style=\"color:#F00\">%1</span>]").arg(m_cur_open_dir));
        if(m_model_upload_data->rowCount() == 0)
        {
            QMessageBox::warning(this,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8""));
            return;
        }
        QString server_id;
        QString file_server_ip;
        QString file_server_port;
        QString file_server_root;
        MAC__GetLineServerList server_info;
        server_info.outUse = m_config.get_server_type();
        MAC__GetLineServerListResponse web_result;
        int ret = soap_call___MAC__GetLineServerList(&m_web_service,NULL,NULL,&server_info,web_result);
        if(ret == SOAP_OK)
        {
            qDebug() << "execute mac webservice successfully!";
            //        qDebug() << QString::fromStdWString(std::wstring(web_result.return_));
            auto json_data = QString::fromStdWString(std::wstring(web_result.return_));
            process_json_data_from_web(json_data,server_id,file_server_ip,file_server_port,file_server_root);
            qDebug() << "-->get all:" << server_id << ";" << file_server_ip << ";" << file_server_port << ";" << file_server_root;
        }
        else
        {
            qDebug() << QString::fromUtf8(u8"execute mac webservice failed,code[%1]!").arg(ret);
            qDebug() << QString::fromStdWString(std::wstring(web_result.return_));
            write_to_log_dock(QString::fromUtf8(u8"调用getlineserverlist服务失败，原因：[<b>%1</b>]").arg(QString::fromStdWString(std::wstring(web_result.return_))));
        }
        //判读是否需要特殊处理
        bool need_special_process = false;
        QString sql_content = QString::fromUtf8(u8"select 接收类型 as recvtype, 制作方式 as productionmethod from TS_接收登记表 where 批次号='%1'").arg(m_cur_batch_number);
        std::wstring web_ret;
        ret = soap_call_SER__executeSql(&m_web_service,NULL,NULL,m_db_key.toStdWString(),sql_content.toStdWString(),web_ret);
        if(ret == SOAP_OK)
        {
            qDebug() << "execute ser webservice successfully!";
            QString ret_data;
            ret = check_web_service_query_result(web_ret,ret_data,web_service_type::SER_SQL_QUERY);
            if(ret != -1)
            {
                if(ret  == 0)
                {
                    //QMessageBox::warning(this,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"查询到%1条记录。").arg(ret));
                    write_to_log_dock(QString::fromUtf8(u8"[<span style=\"color:#F00\">%1</span>]不需要特殊处理。").arg(m_cur_batch_number));
                }
                else
                {
                    qDebug() << "there are " << ret << " records.";
                    qDebug() << "the xml data is: " << ret_data;
                    QDomDocument doc;
                    doc.setContent(ret_data);
                    auto node = doc.firstChild();
                    auto xml_content = node.firstChildElement(QString::fromUtf8(u8"a"));
                    auto recv_type = xml_content.firstChildElement(QString::fromUtf8(u8"recvtype")).text();
                    auto production_method = xml_content.firstChildElement(QString::fromUtf8(u8"productionmethod")).text();
                    if(recv_type == QString::fromUtf8(u8"盘") && production_method == QString::fromUtf8(u8"纯刊"))
                    {
                        qDebug() << m_cur_batch_number << " need special process!";
                        write_to_log_dock(QString::fromUtf8(u8"[<span style=\"color:#F00\">%1</span>]需要特殊处理。").arg(m_cur_batch_number));
                        need_special_process = true;
                    }
                }
            }
        }
        else
        {
            QMessageBox::warning(this,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"连接服务器失败，请稍后再试。").arg(ret));
            write_to_log_dock(QString::fromUtf8(u8"查询[TS_接收登记表]是否特殊处理失败，原因：<b>%1</b>。").arg(web_ret));
            return;

        }
        //冻结所有输入
        lock_all_input(true);

        //            std::wstring web_ret;
        //            int ret;
        bool any_err = false;
        QString err_msg;
        QProgressDialog progress_upload(this);
        progress_upload.setWindowModality(Qt::WindowModal);
        progress_upload.setWindowTitle(QString::fromUtf8(u8"文件上传中..."));
        progress_upload.setCancelButtonText(QString::fromUtf8(u8"取消也不会停"));
        progress_upload.show();


        for(int row = 0; row < m_model_upload_data->rowCount(); ++row)
        {
            QString folder_name;
            progress_upload.setLabelText(QString::fromUtf8(u8"正在传输\t") + folder_name);
            if(!m_model_upload_data->item(row,3)->text().isEmpty())
            {
                folder_name = m_model_upload_data->item(row,2)->text() +QString::fromUtf8(u8"♂") + m_model_upload_data->item(row,3)->text();
            }
            else
            {
                folder_name = m_model_upload_data->item(row,2)->text();
            }
            qDebug() << "***folder:" << folder_name;

            QString full_path = m_cur_open_dir+QString::fromUtf8(u8"/")+folder_name;
            QDir book_dir(full_path);
            if(!book_dir.exists())
            {
                m_model_upload_data->setItem(row,5,new QStandardItem(QString::fromUtf8(u8"否,找不到匹配的文件夹")));
            }
            else
            {
                QString store_proc_del = QString::fromUtf8("@cPost#%1#VarChar#in#$@cSN#%2#VarChar#in#$@dtRechTime#%3#VarChar#in#$@fileDirection#%4#VarChar#in#$@nRet##int#out#$@cError##VarChar#out#$")
                                             .arg(QString::fromUtf8(u8"接收登记"))
                                             .arg(m_model_upload_data->item(row,1)->text())
                                             .arg(m_arrival_time_map[m_model_upload_data->item(row,1)->text()])
                                             .arg(QString::fromUtf8(u8"输出"));
                web_ret.clear();
                //            ret = soap_call_SER__executeStorageProcess(&m_web_service,NULL,NULL,m_db_key.toStdWString(),QString::fromUtf8(u8"").toStdWString(),store_proc_del.toStdWString(),web_ret);
                ret = soap_call_SER__executeStorageProcess(&m_web_service,
                                                           NULL,
                                                           NULL,
                                                           m_db_key.toStdWString(),
                                                           QString::fromUtf8(u8"Proc_文件_DeleteFile").toStdWString(),
                                                           store_proc_del.toStdWString(),
                                                           web_ret);
                if (ret == SOAP_OK)
                {
                    QString ret_data;
                    ret = check_web_service_query_result(web_ret,ret_data,web_service_type::SER_STORE_PROCESS);
                    if(ret == 1)
                    {
                        //成功
                        qDebug() << "execute storage process for delete book infos successfully!";
                        qDebug() << QString::fromStdWString(web_ret);
                        qInfo() << QString::fromUtf8(u8"[%1]执行存储过程[Proc_文件_DeleteFile]成功！").arg(m_model_upload_data->item(row,1)->text());
                    }
                    if(ret == 0)
                    {
                        any_err = true;
                        //失败
                        qDebug() << "execute storage process for delete book infos failed!";
                        qDebug() << ret_data;
                        err_msg += QString::fromUtf8(u8"%1:%2.\n").arg(m_model_excel_data->item(row,1)->text()).arg(ret_data);
                        write_to_log_dock(QString::fromUtf8(u8"[%1]执行存储过程[Proc_文件_DeleteFile]失败，原因：<b>%2</b>。").arg(m_model_upload_data->item(row,1)->text()).arg(ret_data));
                        continue;//TODO 存疑

                    }

                    QStringList file_paths;
                    QString err_msg;
                    quint64 total_file_size = 0;
                    if(need_special_process)
                    {
                        file_paths = get_all_file_path(file_process_type::PROC_SPECIAL,full_path,total_file_size,err_msg);
                    }
                    else
                    {
                        file_paths = get_all_file_path(file_process_type::PROC_NORMAL,full_path,total_file_size,err_msg);
                    }
                    progress_upload.setRange(0,file_paths.size());
                    progress_upload.hide();
                    //开始文件上传
                    bool server_ret;
                    QFuture<int> future_connect_server= QtConcurrent::run([&](){return m_file_transports->ConnectServer(file_server_ip.toStdWString().c_str(),file_server_port.toInt(),1);});
                    QMessageBox temp(this);
                    QString temp_text = QString::fromUtf8(u8"正在连接文件服务器...");
                    temp.setText(temp_text);
                    temp.setWindowTitle(QString::fromUtf8(u8"提示"));
                    temp.setWindowModality(Qt::WindowModal);
//                    temp.setWindowFlags(Qt::WindowContextHelpButtonHint| Qt::WindowCloseButtonHint| Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
                    temp.addButton(QMessageBox::Ok);
                    temp.button(QMessageBox::Ok)->hide();
                    temp.show();
                    QTime s_time,s_time_1;
                    s_time.start();
                    s_time_1.start();
                    while(future_connect_server.isRunning())
                    {
                        if(s_time.elapsed() > 1000)
                        {
                            temp_text.append(u8".");
                            temp.setText(temp_text);
                            s_time.start();
                        }
                        if(s_time_1.elapsed()>5000)
                        {
                            future_connect_server.cancel();
                            break;
                        }
                        qApp->processEvents();
                    }
                    temp.hide();
                    progress_upload.show();
                    if(!future_connect_server.isCanceled())
                    {
                        server_ret = future_connect_server.result();
                    }
                    else
                    {
                        server_ret = 0;
                    }
//                    bool server_ret = m_file_transports->ConnectServer(file_server_ip.toStdWString().c_str(),file_server_port.toInt(),1);
                    if(server_ret)
                    {
                        qDebug() << QString::fromUtf8(u8"connect file server successfully!");
                        qInfo() << QString::fromUtf8(u8"连接文件服务器[%1]成功！").arg(file_server_ip);
                    }
                    else
                    {
                        //连接失败
                        wchar_t buf[512] = {0};
                        m_file_transports->GetLastErrorMessage(reinterpret_cast<wchar_t*>(&buf),512);
                        qDebug() << QString::fromStdWString(std::wstring(buf));
                        this->m_err_msg.push_back(QString::fromUtf8(u8"服务器连接失败，请稍后再试！"));
                        write_to_log_dock(QString::fromUtf8(u8"连接文件服务器[%1]失败，原因：<b>%2</b>").arg(file_server_ip).arg(std::wstring(buf).empty() && future_connect_server.isCanceled()?QString::fromUtf8(u8"连接超时。"):QString::fromStdWString(std::wstring(buf))));
                        this->lock_all_input(false);
                        return;
                    }
                    //遍历list逐个上传文件
                    auto cur_code = m_model_upload_data->item(row,1)->text();
                    QString server_file_path = QString::fromUtf8(u8"%1\\%2\\%3\\%4\\%5\\%6\\%7\\")
                                                   .arg(file_server_root)
                                                   .arg(cur_code.left(4))
                                                   .arg(cur_code.right(1))
                                                   .arg(cur_code.mid(cur_code.size()-2,1))
                                                   .arg(cur_code.mid(cur_code.size()-3,1))
                                                   .arg(cur_code)
                                                   .arg(QDateTime::currentMSecsSinceEpoch());
                    qDebug() << server_file_path;
                    QString final_remote_path;
                    bool any_err_when_upload = false;
                    int file_num_have_uploaded = 0;
                    foreach(auto file_path,file_paths)
                    {
                        QFileInfo temp_dir(file_path);
                        QString file_name  = temp_dir.fileName();
                        progress_upload.setLabelText(QString::fromUtf8(u8"正在传输\t") + folder_name+":"+file_name);
                        write_to_log_dock(QString::fromUtf8(u8"[<span style=\"color:#F00\">%1</span> <span style=\"color:#F00\">%2</span>]开始上传到文件服务器！").arg(folder_name).arg(file_name));
                        QString file_dir = temp_dir.path();
                        if(need_special_process)
                        {
                            //特殊处理，修改文件名
                            file_name.remove(0,file_name.indexOf("."));
                            file_name = cur_code + file_name;
                        }
                        qDebug() << file_name;
                        auto temp_path_parts = file_dir.split(folder_name);
                        QString sub_path;
                        if(temp_path_parts.last().isEmpty())
                        {
                            final_remote_path = server_file_path;
                        }
                        else
                        {
                            sub_path = temp_path_parts.last().right(temp_path_parts.last().size()-1);
                            final_remote_path = server_file_path + sub_path + QString::fromUtf8(u8"\\");
                        }
                        qDebug() << "^^^^final remote path: " << final_remote_path;
                        m_file_transports->Clear();
                        m_file_transports->AddFile(file_path.toStdWString().c_str(),(final_remote_path+file_name).toStdWString().c_str());
                        QFuture<int> future_upload = QtConcurrent::run([&](){return m_file_transports->Execute();});
                        while(future_upload.isRunning())
                        {
                            qApp->processEvents();
                        }
                        server_ret = future_upload.result();
                        //                            server_ret = m_file_transports->Execute();
                        if(server_ret)
                        {
                            qDebug() << "upload to file server successfully!";
                            write_to_log_dock(QString::fromUtf8(u8"[<span style=\"color:#F00\">%1</span> <span style=\"color:#F00\">%2</span>]上传到文件服务器成功！").arg(folder_name).arg(file_name));
                            //更新数据库
                            QString store_proc_update = QString::fromUtf8(u8"@cPost#%1#VarChar#in#$@cSN#%2#VarChar#in#$@dtRechTime#%3#VarChar#in#$@cFileName#%4#VarChar#in#$@dwSize#%5#VarChar#in#$@cMTime#%6#VarChar#in#$@cPath#%7#VarChar#in#$@cRelateDir#%8#VarChar#in#$@fileDirection#%9#VarChar#in#$@cExt#%10#VarChar#in#$@serverId#%11#Int#in#$@nRet##int#out#$@cError##VarChar#out#$")
                                                            .arg(QString::fromUtf8(u8"接收登记"))
                                                            .arg(cur_code)
                                                            .arg(m_arrival_time_map[cur_code])
//                                                            .arg(QString::fromUtf8(file_name.toUtf8()))
                                                            .arg(QString::fromUtf8(file_name.toUtf8()))
                                                            .arg(temp_dir.size())
                                                            .arg(temp_dir.lastModified().toString("yyyy-MM-dd HH:mm:ss"))
                                                            .arg(final_remote_path.split(file_server_root).last())
                                                            .arg(sub_path)
                                                            .arg(QString::fromUtf8(u8"输出"))
                                                            .arg(temp_dir.suffix().toLower())
                                                            .arg(server_id);
                            web_ret.clear();
                            qDebug() << "updata_proc:" << store_proc_update;
                            //            ret = soap_call_SER__executeStorageProcess(&m_web_service,NULL,NULL,m_db_key.toStdWString(),QString::fromUtf8(u8"").toStdWString(),store_proc_del.toStdWString(),web_ret);
                            ret = soap_call_SER__executeStorageProcess(&m_web_service,
                                                                       NULL,
                                                                       NULL,
                                                                       m_db_key.toStdWString(),
                                                                       QString::fromUtf8(u8"Proc_文件_InsertOneFile").toStdWString(),
                                                                       store_proc_update.toStdWString(),
                                                                       web_ret);
#if 0
                           //service test
                            QString update_sql = QString::fromUtf8(u8"EXEC	[dbo].[Proc_文件_InsertOneFile_V1] \
                                                            @cPost = N'%1', \
                                                            @cSN = N'%2', \
                                                            @dtRechTime = N'%3',\
                                                            @cFileName = N'%4',\
                                                            @dwSize = %5,\
                                                            @cMTime = N'%6',\
                                                            @cPath = N'%7,\
                                                            @cRelateDir = N'%8',\
                                                            @fileDirection = N'%9',\
                                                            @cExt = N'%10',\
                                                            @serverId = %11,\
                                                            @cArtSN = N'%12',\
                                                            @nRet = @nRet OUTPUT,\
                                                            @cError = @cError OUTPUT")
                                                            .arg(QString::fromUtf8(u8"接收登记"))
                                                            .arg(cur_code)
                                                            .arg(m_arrival_time_map[cur_code])
                                                            .arg(QString::fromUtf8(u8"\u00d6"))
                                                            .arg(temp_dir.size())
                                                            .arg(temp_dir.lastModified().toString("yyyy-MM-dd HH:mm:ss"))
                                                            .arg(final_remote_path.split(file_server_root).last())
                                                            .arg(sub_path)
                                                            .arg(QString::fromUtf8(u8"输出"))
                                                            .arg(temp_dir.suffix().toLower())
                                                            .arg(server_id)
                                                            .arg(cur_code);
                            qDebug() << "updata_sql:" << update_sql;
                            qInfo() << update_sql;

                            ret = soap_call_SER__executeSql(&m_web_service,
                                                                         NULL,
                                                                         NULL,
                                                                         m_db_key.toStdWString(),
                                                                         update_sql.toStdWString(),
                                                                         web_ret);
#endif
                            if (ret == SOAP_OK)
                            {

                                qDebug() << "soap store process insert one file successfully!";
                                QString ret_data;
                                ret = check_web_service_query_result(web_ret,ret_data,web_service_type::SER_STORE_PROCESS);
                                if(ret == 1)
                                {
                                    m_model_upload_data->setItem(row,4,new QStandardItem(QString::number(++file_num_have_uploaded)));
                                    progress_upload.setValue(file_num_have_uploaded);
                                    //成功
                                    qDebug() << "execute storage process for insert one successfully!";
                                    //                                    write_to_log_dock(QString::fromUtf8(u8"执行Proc_文件_InsertOneFile成功！"));
                                    qDebug() << QString::fromStdWString(web_ret);
                                    qInfo() << QString::fromUtf8(u8"[%1]执行[Proc_文件_InsertOneFile]成功！").arg(file_name);
                                }
                                if(ret == 0)
                                {
                                    any_err_when_upload = true;
                                    //失败
                                    qDebug() << "execute storage process for insert one failed!";
                                    write_to_log_dock(QString::fromUtf8(u8"[<span style=\"color:#F00\">%1</span>]执行[Proc_文件_InsertOneFile]失败！").arg(file_name));
                                    qDebug() << ret_data;
                                }
                            }
                            else
                            {
                                qDebug() << ret ;
                                qDebug() << "web_ret when soap failed:" << web_ret;
                                this->m_err_msg.push_back(QString::fromUtf8(u8"[Proc_文件_InsertOneFile]服务器连接失败，请稍后再试！"));
                                write_to_log_dock(QString::fromUtf8(u8"[Proc_文件_InsertOneFile]服务器连接失败，请稍后再试！"));
                                this->lock_all_input(false);
                                return;
                            }
                        }
                        else
                        {
                            this->m_err_msg.push_back(QString::fromUtf8(u8"执行文件传输失败，请稍后再试！"));
                            write_to_log_dock(QString::fromUtf8(u8"[<span style=\"color:#F00\">%1</span> <span style=\"color:#F00\">%2</span>]上传到文件服务器失败！").arg(folder_name).arg(file_name));
                            this->lock_all_input(false);
                            return;
                        }
                        qApp->processEvents();
                    }//foreach
                    m_file_transports->CloseConnection();
                    if(any_err_when_upload == false)
                    {
                        //all success
                        //提交部分
                        QString store_proc_post = QString::fromUtf8(u8"@cCode#%1#VarChar#in#$@nSize#%2#VarChar#in#$@cDirName#%3#VarChar#in#$@nFileCount#%4#Int#in#$@nRet##int#out#$@cError##VarChar#out#$")
                                                      .arg(cur_code)
                                                      .arg(total_file_size)
                                                      .arg(m_model_upload_data->item(row,2)->text())
                                                      .arg(file_paths.size());
                        web_ret.clear();
                        qDebug() << "updata_proc:" << store_proc_post;
                        //            ret = soap_call_SER__executeStorageProcess(&m_web_service,NULL,NULL,m_db_key.toStdWString(),QString::fromUtf8(u8"").toStdWString(),store_proc_del.toStdWString(),web_ret);
                        ret = soap_call_SER__executeStorageProcess(&m_web_service,
                                                                   NULL,
                                                                   NULL,
                                                                   m_db_key.toStdWString(),
                                                                   QString::fromUtf8(u8"Proc_接收登记_UpdateInfo").toStdWString(),
                                                                   store_proc_post.toStdWString(),
                                                                   web_ret);
                        if (ret == SOAP_OK)
                        {
                            qDebug() << "soap store process post successfully!";
                            QString ret_data;
                            ret = check_web_service_query_result(web_ret,ret_data,web_service_type::SER_STORE_PROCESS);
                            if(ret == 1)
                            {
                                //成功
                                qDebug() << "execute storage process post successfully!";
                                qDebug() << QString::fromStdWString(web_ret);
                                m_model_upload_data->setItem(row,5,new QStandardItem(QString::fromUtf8(u8"是")));
                                m_model_upload_data->setItem(row,6,new QStandardItem(QString::fromUtf8(u8"否，未提交")));
                                //                                write_to_log_dock(QString::fromUtf8(u8"执行Proc_接收登记_UpdateInfo成功！"));
                                //更新表1的图书状态
                                write_to_log_dock(QString::fromUtf8(u8"[<span style=\"color:#F00\">%1</span>]执行[Proc_接收登记_UpdateInfo]成功！").arg(cur_code));
                            }
                            if(ret == 0)
                            {
                                any_err_when_upload = true;
                                //失败
                                qDebug() << "execute storage process post failed!";
                                qDebug() << ret_data;
                                m_model_upload_data->setItem(row,6,new QStandardItem(QString::fromUtf8(u8"否：提交任务失败。")));
                                write_to_log_dock(QString::fromUtf8(u8"[<span style=\"color:#F00\">%1</span>]执行[Proc_接收登记_UpdateInfo]失败！").arg(cur_code));
                            }
                        }
                        else
                        {
                            this->m_err_msg.push_back(QString::fromUtf8(u8"[Proc_接收登记_UpdateInfo]服务器连接失败，请稍后再试！"));
                            this->lock_all_input(false);
                            break;
                            qDebug() << "execute storage process post failed!";
                        }
                    }
                    else
                    {
                        m_model_upload_data->setItem(row,5,new QStandardItem(QString::fromUtf8(u8"否：有文件上传失败。")));
                    }
                }
                else
                {
                    this->m_err_msg.push_back(QString::fromUtf8(u8"服务器连接失败，请稍后再试！"));
                    this->lock_all_input(false);
                    break;
                }
            }
            m_model_upload_data->setHeaderData(row,Qt::Vertical," ");
            qApp->processEvents();
            //                this->m_model_upload_data->appendRow(new QStandardItem(""));
            //                this->m_model_upload_data->removeRow(this->m_model_upload_data->rowCount()-1);
        }
        this->ui->tableViewUpload->resizeColumnsToContents();
        this->lock_all_input(false);



    }


}

void MainWindow::on_pushButtonUploadDB_clicked()
{
    if(m_cur_batch_number.isEmpty())
    {
        QMessageBox::warning(this,QString::fromUtf8(u8"提示"),QString::fromUtf8(u8"请先进行批次号查询。"));
        return;
    }
    if(m_cur_excel_file_path.isEmpty())
    {
        QMessageBox::warning(this,QString::fromUtf8(u8"提示"),QString::fromUtf8(u8"请先打开excel文件。"));
        return;
    }
    bool any_err = false;
    if(m_cur_tabview_state == tableview_show_type::SHOW_EXCEL_DATA)
    {
        QString err_msg;

        //开始上传
        for(int row = 0; row < m_model_excel_data->rowCount();++row)
        {
            int col = 1;
            QString sql_content;
            sql_content += QString::fromUtf8("@cPici#%1#VarChar#in#$").arg(m_cur_batch_number);
            sql_content += QString::fromUtf8("@cPublish#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cBookName#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cFBookName#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cFj#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cCBookName#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cFCBookName#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cCBookNum#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cISBN#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cAuthor#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cCBookAuthor#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cPublishDate#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cInstruction#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cPrice#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cFormat#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cCopyRight#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cCover#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cOther#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cMemo#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cLanguage#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cStartTime#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cEndTime#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cAuthorizer#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cLicensor#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cFileName#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cCarrerType#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cBookType#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cReader#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@cUseType#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());
            sql_content += QString::fromUtf8("@classics#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());//2019.12.17LXQ添加
            sql_content += QString::fromUtf8("@kernel#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());//2020.06.12LXQ添加
            sql_content += QString::fromUtf8("@highcited#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());//2020.06.12LXQ添加
            sql_content += QString::fromUtf8("@year#%1#VarChar#in#$").arg(m_model_excel_data->item(row,col++)->text());//2020.12.14LXQ添加
            sql_content += QString::fromUtf8("@nRet##int#out#$");
            sql_content += QString::fromUtf8("@cError##VarChar#out#$");

            qDebug() << sql_content;

            std::wstring web_result;
            //            int ret = soap_call_ns1__executeStorageProcess(&m_web_service,
            //                                                           NULL,
            //                                                           NULL,
            //                                                           m_db_key.toStdWString(),
            //                                                           QString::fromUtf8(u8"Proc_接收登记_SvaeInfo_V6").toStdWString(),
            //                                                           sql_content.toStdWString(),
            //                                                           web_result);
            int ret = soap_call_SER__executeStorageProcess(&m_web_service,
                                                           NULL,
                                                           NULL,
                                                           m_db_key.toStdWString(),
                                                           QString::fromUtf8(u8"Proc_接收登记_SvaeInfo_V6").toStdWString(),
                                                           sql_content.toStdWString(),
                                                           web_result);
            if (ret == SOAP_OK)
            {
                QString msg_data;
                ret = check_web_service_query_result(web_result,msg_data,web_service_type::SER_STORE_PROCESS);
                if(ret == 1)
                {
                    //成功
                    qDebug() << "execute storage process for upload book infos successfully!";
                    qDebug() << QString::fromStdWString(web_result);
                    m_model_excel_data->setItem(row,m_model_excel_data->columnCount()-1,new QStandardItem(QString::fromUtf8(u8"否，未上传")));
                    write_to_log_dock(QString::fromUtf8(u8"[<span style=\"color:#F00\">%1</span>-<span style=\"color:#F00\">%2</span>]导入成功！").arg(m_model_excel_data->item(row,0)->text()).arg(m_model_excel_data->item(row,2)->text()));
                }
                if(ret == 0)
                {
                    any_err = true;
                    //失败
                    //TODO
                    qDebug() << "execute storage process for upload book infos failed!";
                    err_msg += QString::fromUtf8(u8"%1:%2.\n").arg(m_model_excel_data->item(row,2)->text()).arg(msg_data);
                    write_to_log_dock(QString::fromUtf8(u8"[<span style=\"color:#F00\">%1</span>-<span style=\"color:#F00\">%2</span>]导入失败，原因：<b>%3</b>").arg(m_model_excel_data->item(row,0)->text()).arg(m_model_excel_data->item(row,2)->text()).arg(msg_data));
                }
            }
            else
            {
                any_err = true;
                qDebug() << "execute storage process for upload book infos failed!";
                qDebug() << QString::fromStdWString(web_result);
                err_msg += QString::fromUtf8(u8"%1:%2.\n").arg(m_model_excel_data->item(row,2)->text()).arg(QString::fromStdWString(web_result));
                write_to_log_dock(QString::fromUtf8(u8"[<span style=\"color:#F00\">%1</span>-<span style=\"color:#F00\">%2</span>]调用服务失败，原因：<b>%3</b>").arg(m_model_excel_data->item(row,0)->text()).arg(m_model_excel_data->item(row,2)->text()).arg(web_result));
            }
        }
        if(any_err)
        {
            QMessageBox::critical(this,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"导入数据失败\n%1").arg(err_msg));
        }
        else
        {
            QMessageBox::information(this,QString::fromUtf8(u8"成功"),QString::fromUtf8(u8"导入数据成功！"));
        }
    }
    if(m_cur_tabview_state == tableview_show_type::SHOW_ERROR_DATA)
    {
        QMessageBox::critical(this,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"模板中存在错误，请修正错误后再尝试导入！"));
    }
}

void MainWindow::on_pushButtonChooseFile_clicked()
{
    if(m_cur_batch_number.isEmpty())
    {
        QMessageBox::warning(this,QString::fromUtf8(u8"提示"),QString::fromUtf8(u8"请先进行批次号查询。"));
        return;
    }
    m_cur_excel_file_path.clear();
    //打开模板文件，读取excel内容
    m_cur_excel_file_path = QFileDialog::getOpenFileName(this, QString::fromUtf8(u8"打开输入文件"), QString::fromUtf8(u8"./"), "*.xlsx");
    if (m_cur_excel_file_path .isEmpty())
    {
        QMessageBox::warning(this,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"未选择文件！"));
        return ;
    }
    //初始化excel检查
    init_excel_checker();
    write_to_log_dock(QString::fromUtf8(u8"打开文件[<span style=\"color:#F00\">%1</span>]").arg(m_cur_excel_file_path));
    if(!read_excel_model_file())
    {
        return;
    }

    this->setWindowTitle(MyGlobal::APP_NAME +QString::fromUtf8("-[%1]").arg(m_cur_excel_file_path));
}

void MainWindow::on_pushButtonShowLog_clicked()
{
    if(m_log_dock->isHidden())
    {
        m_log_dock->show();
    }
    //    auto temp_content = m_log_edit->toPlainText();
    auto temp = dynamic_cast<QTextEdit*>(m_log_dock->widget());
    auto old_content = temp->toHtml();
    m_log_dock.reset(new QDockWidget(QString::fromUtf8(u8"日志"),this));
    //    m_log_edit.reset(new QTextEdit(m_log_dock.get()));
    //    m_log_edit->setReadOnly(true);
    //    m_log_edit->setText(temp_content);
    auto temp_log_edit = new QTextEdit(m_log_dock.get());
    temp_log_edit->setReadOnly(true);
    temp_log_edit->setText(old_content);
    m_log_dock->setWidget(temp_log_edit);
    m_log_dock->setFeatures(QDockWidget::AllDockWidgetFeatures);
    addDockWidget(Qt::RightDockWidgetArea,m_log_dock.get());


    //    addDockWidget(Qt::RightDockWidgetArea,m_log_dock);

}

void MainWindow::on_pushButtonTest_clicked()
{
#if 0
    auto temp_dir= QFileDialog::getExistingDirectory(this,QString::fromUtf8(u8"选择上传文件夹"),QString::fromUtf8(u8"./"));
    if(temp_dir.isEmpty())
    {
        return;
    }

    QStringList file_paths;
    quint64 total_file_size = 0;
    QString err_msg;
    file_paths = get_all_file_path(file_process_type::PROC_NORMAL,temp_dir,total_file_size,err_msg);
    foreach(auto it,file_paths)
    {
        qDebug() << it;
        QDir temp_dir(it);
        qDebug() << temp_dir.dirName();
        qDebug() << temp_dir.currentPath();
    }
#endif
#if 0
    //test wchar_t sizeof
    wchar_t a[10] = {0};
    qDebug() << sizeof(a);
    //test qstring mid
    QString b = "12345";
    qDebug() << b.mid(b.size()-1);
    qDebug() << b.mid(b.size()-2,1);
    qDebug() << b.mid(b.size()-3,1);
    //test qt time
    QDateTime c = QDateTime::currentDateTime();
    QDateTime d = QDateTime::fromString(QString::fromUtf8(u8"00010101 00:00:00.000"),QString::fromUtf8(u8"yyyyMMdd hh:mm:ss.zzz"));
    QDateTime e = QDateTime::fromString(QString::fromUtf8(u8"19700101 00:00:00.000"),QString::fromUtf8(u8"yyyyMMdd hh:mm:ss.zzz"));

    qDebug() << c.toMSecsSinceEpoch();
    qDebug() << c.toTime_t();
    qDebug() << d.msecsTo(e);
    qDebug() << d.daysTo(e);

    std::chrono::duration<long long,std::ratio<1,1000>> day(0-d.msecsTo(e));

    std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<long long,std::ratio<1,10000000>>> tp(day);
    qDebug() << -tp.time_since_epoch().count();
    qDebug() << std::chrono::steady_clock::now().time_since_epoch().count()/100;
    qDebug() << (std::chrono::steady_clock::now().time_since_epoch().count()/100-tp.time_since_epoch().count());
#endif
#if 0
    QString test = "E:\\12345\\67890\\xxxx";
    auto test_split = test.split("67890");
    qDebug() << "split size:"  << test_split.size();
    foreach(auto each, test_split)
    {
        qDebug() << each;
    }
    QThread *th = QThread::create([=](){
        QThread::sleep(10);
        this->m_err_msg.push_back(QString::fromUtf8(u8"服务器连接失败，请稍后再试！"));
        qDebug() << "hello from thread!";
    });
    //connect(th,SIGNAL(finished()),this,SLOT(on_pthread_finished()));
    th->start();
#endif
#if 0
    //    ui->tableView->verticalHeader()->setHidden(true);
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,1);
    QList<int> temp_list;
    temp_list << height()/2;
    temp_list << height()/2;
    ui->splitter->setSizes(temp_list);
#endif
#if 0
    if(m_log_dock->isHidden())
    {
        qDebug() << "hide";
    }
#endif
#if 0
    QString file_name(u8"test.001.tif");
    QString cur_code(u8"2021001100");
    file_name.remove(0,file_name.indexOf("."));
    file_name = cur_code + file_name;
    qDebug() << file_name;
#endif
    QString cmd = QString::fromUtf8(u8"./7-Zip/7z.exe");
    QStringList arguments({QString::fromUtf8(u8"l"),QString::fromUtf8(u8"E:\\code\\3690009-图文编审调整存储过程db.rar")});
    //            the_cmd_for_trans_tif_to_pdf += target;
    //            the_cmd_for_trans_tif_to_pdf += " ";
    //            the_cmd_for_trans_tif_to_pdf += full_sub_sub_pdf_name;
    qDebug() << cmd;
    QProcess p;
    p.start(cmd,arguments);
    p.waitForStarted();
    p.waitForFinished();
    auto cmd_out = QString::fromLocal8Bit(p.readAllStandardOutput());
    qDebug()<< cmd_out;
    //            auto cmd_out_lines = cmd_out.split(QString::fromUtf8(u8"\r\n"));
    auto cmd_out_lines = cmd_out.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
    qDebug() << "all lines:" << cmd_out_lines.size();
    foreach(auto line,cmd_out_lines)
    {
        qDebug() << line;
    }
    auto main_body = cmd_out_lines.filter(QRegExp(".* .* [^ ]{5} \\d* \\d* .*"));
    qDebug() << "main_body:";
    foreach(auto line,main_body)
    {
        qDebug() << line;
        line.remove(0,line.lastIndexOf(" ")+1);
        qDebug() << "after process: " << line;
        line.remove(0,line.lastIndexOf("\\")+1);
        qDebug() << "file name: " << line;
    }
    qDebug()<<QString::fromLocal8Bit(p.readAllStandardError());

}

void MainWindow::on_pushButtonBulkBookCommit_clicked()
{
    auto all_selected_rows = m_upload_vheadeview->getAllSelected();
    if(all_selected_rows.empty())
    {
        QMessageBox::warning(this,QString::fromUtf8(u8"提示"),QString::fromUtf8(u8"没有勾选任何图书！"));
        return;
    }
    for(auto it = all_selected_rows.begin();it != all_selected_rows.end(); ++it)
    {
        if(m_model_upload_data->item(*it,5)->text() != QString::fromUtf8(u8"是"))
        {
            QMessageBox::warning(this,QString::fromUtf8(u8"提示"),QString::fromUtf8(u8"[%1]尚未上传文件！").arg(m_model_upload_data->item(*it,1)->text()));
            continue;;
        }
        qDebug() << "slect " << *it;
        if(m_model_upload_data->item(*it,6)->text() == QString::fromUtf8(u8"已提交"))
        {
            //            QMessageBox::information(this,QString::fromUtf8(u8"提示"),QString::fromUtf8(u8"该记录已提交！"));
            write_to_log_dock(QString::fromUtf8(u8"[<span style=\"color:#F00\">%1</span>]-《<span style=\"color:#F00\">%2</span>》已提交，自动忽略！").arg(m_model_upload_data->item(*it,1)->text()).arg(m_model_upload_data->item(*it,2)->text()));
        }
        else
        {
            submit(*it);
        }
    }
}

void MainWindow::on_pushButtonBatchCommit_clicked()
{
    if(m_cur_batch_number.isEmpty())
    {
        QMessageBox::warning(this,QString::fromUtf8(u8"提示"),QString::fromUtf8(u8"请输入批次号。"));
        return;
    }
    QString sql_content;
    sql_content += QString::fromUtf8(u8"@cPici#%1#VarChar#in#$").arg(m_cur_batch_number);
    sql_content += QString::fromUtf8(u8"@nRet##int#out#$@cErrMsg##VarChar#out#$");
    QString err_msg;
    std::wstring web_result;
    int ret = soap_call_SER__executeStorageProcess(&m_web_service,
                                                   NULL,
                                                   NULL,
                                                   m_db_key.toStdWString(),
                                                   QString::fromUtf8(u8"Proc_接收登记_SubmitTask_批").toStdWString(),
                                                   sql_content.toStdWString(),
                                                   web_result);
    if (ret == SOAP_OK)
    {
        QString msg_data;
        ret = check_web_service_query_result(web_result,msg_data,web_service_type::SER_STORE_PROCESS);
        if(ret == 1)
        {
            //成功
            qDebug() << "execute storage process for upload book infos successfully!";
            qDebug() << QString::fromStdWString(web_result);
            write_to_log_dock(QString::fromUtf8(u8"[<span style=\"color:#F00\">%1</span>]-批提交成功！").arg(m_cur_batch_number));
            QMessageBox::warning(this,QString::fromUtf8(u8"提示"),QString::fromUtf8(u8"[%1]-批提交成功！").arg(m_cur_batch_number));

        }
        if(ret == 0)
        {
            //失败
            //TODO
            qDebug() << "execute storage process for upload book infos failed!";
            err_msg += QString::fromUtf8(u8"%1:%2.\n").arg(m_cur_batch_number).arg(msg_data);
            write_to_log_dock(QString::fromUtf8(u8"[<span style=\"color:#F00\">%1</span>]-批提交失败，原因：<b>%2</b>").arg(m_cur_batch_number).arg(msg_data));
            QMessageBox::warning(this,QString::fromUtf8(u8"提示"),QString::fromUtf8(u8"[%1]-批提交失败！").arg(m_cur_batch_number));
        }
    }
    else
    {
        QMessageBox::warning(this,QString::fromUtf8(u8"提示"),QString::fromUtf8(u8"[%1]-批提交失败，服务器连接失败！").arg(m_cur_batch_number));
    }

}

void MainWindow::on_lineEditBatchNum_textEdited(const QString &text)
{
    if(text.size()>20)
    {
        m_statusbar_label_cur_batch_num->setText(QString::fromUtf8(u8"当前批次号：")+QString::fromUtf8(u8"太长了"));
    }
    else if(text.isEmpty())
    {
        m_statusbar_label_cur_batch_num->setText(QString::fromUtf8(u8"当前批次号：null"));
    }
    else
    {
        m_statusbar_label_cur_batch_num->setText(QString::fromUtf8(u8"当前批次号：")+text);
    }
    m_cur_batch_number = text;
}

void MainWindow::on_pushButtonIndividualBookSubmit()
{
    QPushButton* senderObj = qobject_cast<QPushButton*>(sender());
    if(senderObj == nullptr)
    {
        return;
    }
    int cur_row = senderObj->property("row").toUInt();
    //QMessageBox::information(this,"test",QString("cur row:") + QString::number(cur_row));
    if(m_model_upload_data->item(cur_row,5))
    {
        if(m_model_upload_data->item(cur_row,5)->text() != QString::fromUtf8(u8"是"))
        {
            QMessageBox::warning(this,QString::fromUtf8(u8"提示"),QString::fromUtf8(u8"[%1]尚未上传文件！").arg(m_model_upload_data->item(cur_row,1)->text()));
            return;
        }
        if(m_model_upload_data->item(cur_row,6)->text() == QString::fromUtf8(u8"已提交"))
        {
            QMessageBox::information(this,QString::fromUtf8(u8"提示"),QString::fromUtf8(u8"该记录已提交！"));
        }
        else
        {
            submit(cur_row);
        }

    }

}

void MainWindow::on_err_msg_show()
{
    if(!m_err_msg.isEmpty())
    {
        auto err = m_err_msg.front();
        m_err_msg.pop_front();
        QMessageBox::warning(this,QString::fromUtf8(u8"警告"),err);
    }
    //    this->m_msg_box->exec();

}

void MainWindow::on_select_rows(const QModelIndex & index)
{
    emit press_row(index.row());
}

void MainWindow::on_select_all_rows()
{
    qDebug() << "push";
    if(m_select_all_button_state)
    {
        m_upload_vheadeview->setAllNotSlected();
        m_select_all_button_state = false;
    }
    else
    {
        m_upload_vheadeview->setAllSlected();
        m_select_all_button_state = true;
    }
}


bool MainWindow::read_excel_model_file()
{
    if(m_cur_excel_file_path.isEmpty())
    {
        QMessageBox::warning(this,QString::fromUtf8(u8"警告"),QString::fromUtf8(u8"请先选择输入文件！"));
        return false;
    }
    if(!m_excel_reader->open(m_cur_excel_file_path))
    {
        return false;
    }
    reset_data_model();
    if(!m_excel_reader->read(*m_model_excel_data))
    {
        QVector<ErrorToShow> temp_errs = m_excel_reader->get_excel_errs();
        if(temp_errs.size()>0)
        {
            reset_error_show_model();

            for(int i = 0; i < temp_errs.size(); ++i)
            {
                int j = 0;
                auto temp_err_data = temp_errs[i].get_error_content();
                m_model_excel_check_state->setItem(i,j++,new QStandardItem(std::get<0>(temp_err_data)));
                m_model_excel_check_state->setItem(i,j++,new QStandardItem(std::get<1>(temp_err_data)));
                m_model_excel_check_state->setItem(i,j++,new QStandardItem(std::get<2>(temp_err_data)));
                m_model_excel_check_state->setItem(i,j++,new QStandardItem(std::get<3>(temp_err_data)));
                m_model_excel_check_state->setItem(i,j++,new QStandardItem(std::get<4>(temp_err_data)));
                m_model_excel_check_state->setItem(i,j++,new QStandardItem(std::get<5>(temp_err_data)));
            }
            ui->tableView->setModel(m_model_excel_check_state);
            ui->tableView->resizeColumnsToContents();
            m_cur_tabview_state = tableview_show_type::SHOW_ERROR_DATA;
        }
        return false;
    }
    m_model_excel_data->setHorizontalHeaderLabels(m_excel_header);
    ui->tableView->setModel(m_model_excel_data);
    ui->tableView->resizeColumnsToContents();
    m_cur_tabview_state = tableview_show_type::SHOW_EXCEL_DATA;
    return true;
}
