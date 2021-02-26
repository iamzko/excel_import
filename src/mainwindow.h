#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QMap>
#include <QVector>
#include <QSplitter>
#include <QScopedPointer>

//webservice相关
//#include "webservice/soapH.h"
#include "webserviceallin/soapH.h"

//fileserver相关
#include "NeoFileClientU/include/NeoFileClientUAPI.h"


#include "config.h"
#include "excelreader.h"
#include "excelfieldrule.h"
#include "myglobal.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum class web_service_type{
        SER_SQL_QUERY,
        SER_STORE_PROCESS,
    };
    enum class tableview_show_type{
        SHOW_EXCEL_DATA,
        SHOW_QUERY_DATA,
        SHOW_ERROR_DATA,
        SHOW_NULL,
    };
    enum class file_process_type
    {
        PROC_NORMAL,
        PROC_SPECIAL,
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void on_pushButtonSearch_clicked();
    void on_pushButtonOpenDir_clicked();
    void on_pushButtonUploadDB_clicked();
    void on_pushButtonChooseFile_clicked();
    void on_pushButtonTest_clicked();
private slots:
    void on_currentChanged(const QModelIndex &current,const QModelIndex &previous);

private:

    bool read_excel_model_file();
    bool check_batch_num_input();
    bool check_excel_header(QStringList &target_header);
    int check_web_service_query_result(_IN_ std::wstring &web_result,_OUT_ QString &msg_data, _IN_ web_service_type type);
    void process_xml_data_to_model(_IN_ QString &xml_data);
    void process_json_data_from_web(_IN_ QString &json_data,
                                    _OUT_ QString &server_ip,
                                    _OUT_ QString &file_server_ip,
                                    _OUT_ QString &file_server_port,
                                    _OUT_ QString &file_server_root);
    void reset_data_model();
    void reset_error_show_model();
    void add_button_to_upload_model();
    QStringList get_all_file_path(_IN_ file_process_type type, _IN_ QString &dir_name,_OUT_ quint64 total_size, _OUT_ QString &err_msg);
private:
    Ui::MainWindow *ui;
    //状态栏显示1
    QLabel *m_statusbar_label;
    QLabel *m_statusbar_label_cur_batch_num;
    QMap<QString,QVector<QString>> m_excel_data; /*excel数据*/
    QStandardItemModel *m_model_excel_data; /*excel内容数据模型*/
    QItemSelectionModel *m_selection_excel_data; /*选择模型*/
    QStandardItemModel *m_model_upload_data; /*上传状态数据模型*/
    QItemSelectionModel *m_selection_upload_data; /*选择模型*/
    QStandardItemModel *m_model_excel_check_state; /*excel检查状态数据模型*/
    QStringList m_excel_header; /*excel数据的表头*/
    QStringList m_upload_header;/*上传状态数据的表头*/
    QStringList m_check_state_header;/*excel检查错误的表头*/
    Config m_config;/*程序配置*/
    QScopedPointer<ExcelReader> m_excel_reader; /*excel读取器*/
    QVector<ExcelFieldRule> m_xinke_rules;
    QVector<ExcelFieldRule> m_public_xinke_rules;
    QString m_db_key; /*webservice接口查库入参*/
    QString m_cur_batch_number;/*当前批次号*/
    QString m_cur_excel_file_path;/*当前excel文件*/
    QString m_cur_open_dir;/*当前打开的文件夹*/
    struct soap m_web_service;/*webservice调用*/
    tableview_show_type m_cur_tabview_state;
    CTransmitFile* m_file_transports;/*文件传输服务，目前只适用于Windows*/
};
#endif // MAINWINDOW_H
