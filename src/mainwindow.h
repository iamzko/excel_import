#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDockWidget>
#include <QElapsedTimer>
#include <QItemSelectionModel>
#include <QLabel>
#include <QMainWindow>
#include <QMap>
#include <QMessageBox>
#include <QModelIndex>
#include <QQueue>
#include <QScopedPointer>
#include <QSplitter>
#include <QStandardItemModel>
#include <QTextEdit>
#include <QThread>
#include <QTimer>
#include <QVector>

//webservice相关
//#include "webservice/soapH.h"
#include "webserviceallin/soapH.h"

//fileserver相关
#include "NeoFileClientU/include/NeoFileClientUAPI.h"

#include "config.h"
#include "excelfieldrule.h"
#include "excelreader.h"
#include "helpdialog.h"
#include "myglobal.h"
#include "myprocessxmldatathread.h"
#include "myqheaderview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum class web_service_type {
        SER_SQL_QUERY, /*执行sql请求*/
        SER_STORE_PROCESS, /*执行存储过程*/
    };
    enum class tableview_show_type {
        SHOW_EXCEL_DATA, /*显示excel内容*/
        SHOW_QUERY_DATA, /*显示服务器数据*/
        SHOW_ERROR_DATA, /*显示错误提示数据*/
        SHOW_NULL, /*啥都不显示*/
    };
    enum class file_process_type {
        PROC_NORMAL, /*正常处理*/
        PROC_SPECIAL, /*特殊处理*/
    };
    enum class product_type {
        TYPE_XK, /*心可图书*/
        TYPE_DZ, /*大众图书*/
        TYPE_OTHER, /*其他*/
    };

    friend class MyProcessXmlDataThread; //处理服务器返回数据的线程

public:
    MainWindow(QWidget* parent = nullptr);
    MainWindow(bool command_line = false, QWidget* parent = nullptr);

    void set_batch_num(QString batch_num);
    ~MainWindow();
    //设置命令行启动标志
    void setCommandline_invoke(bool commandline_invoke)
    {
        m_commandline_invoke = commandline_invoke;
    }

protected:
    void mousePressEvent(QMouseEvent *event);
    bool eventFilter(QObject* o,QEvent *e);
public slots:
    //查询按钮点击响应函数
    void on_pushButtonSearch_clicked();
    //文件上传按钮点击响应函数
    void on_pushButtonFileUpload_clicked();
    //开始导入按钮点击响应函数
    void on_pushButtonUploadDB_clicked();
    //选择输入文件按钮点击响应函数
    void on_pushButtonChooseFile_clicked();
    //显示日志按钮点击响应函数
    void on_pushButtonShowLog_clicked();
    //测试按钮点击响应函数
    void on_pushButtonTest_clicked();
    //批量篇提交按钮点击响应函数
    void on_pushButtonBulkBookSubmit_clicked();
    //批提交按钮点击响应函数
    void on_pushButtonBatchSubmit_clicked();
    //输入框变动响应函数
    void on_lineEditBatchNum_textEdited(const QString& text);
    //单篇提交按钮点击响应函数
    void on_pushButtonIndividualBookSubmit();
    //错误消息响应函数
    void on_err_msg_show();
    //下方表格选中行响应函数
    void on_select_rows(const QModelIndex&);
    //下方表格全选响应函数
    void on_select_all_rows();
private slots:
    void on_currentChanged(const QModelIndex &current,const QModelIndex &previous);
    void on_thread_data_finish();
    void on_pushButtonHelp_clicked();

signals:
    void press_row(int row);

private:
    void resizeEvent(QResizeEvent* size);
    int submit(int row);

    bool read_excel_file_to_model();
    bool check_batch_num_input();
    bool check_excel_header(QStringList &target_header);
    int check_web_service_query_result(_IN_ std::wstring &web_result,_OUT_ QString &msg_data, _IN_ web_service_type type);
    void process_json_data_from_web(_IN_ QString& json_data, /*服务器返回的数据*/
        _OUT_ QString& server_id, /*服务器id*/
        _OUT_ QString& file_server_ip, /*文件服务器ip*/
        _OUT_ QString& file_server_port, /*文件服务器端口*/
        _OUT_ QString& file_server_root) /*文件服务器根路径*/;
    void reset_data_model();

    void reset_error_show_model();
    void add_button_and_progressbar_to_upload_model();
    QStringList get_all_file_path(_IN_ file_process_type type, _IN_ QString &dir_name,_OUT_ quint64 total_size, _OUT_ QString &err_msg);
    void write_to_log_dock(_IN_ QString msg);
    QStringList get_all_filename_from_compressed(QString compressed_filepath);
    void init_excel_checker();
    bool get_data_from_db_to_upload_data();
    bool get_if_need_special_process(bool& need);
    bool get_server_list(QString& id, QString& ip, QString& port, QString& dir_root);
    void lock_all_input(bool is_lock);
private:
    Ui::MainWindow *ui;
    //状态栏显示1
    QLabel *m_statusbar_label_cur_open_folder;/*状态栏-当前打开文件夹*/
    QLabel *m_statusbar_label_cur_batch_num;/*状态栏-当前批次号*/
    QMap<QString,QVector<QString>> m_excel_data; /*excel数据*/
    QMap<QString,QString>m_arrival_time_map;
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
    QString m_db_key; /*webservice接口查库入参*/
    QString m_cur_batch_number;/*当前批次号*/
    QString m_cur_excel_file_path;/*当前excel文件*/
    QString m_cur_open_dir;/*当前打开的文件夹*/
    struct soap m_web_service;/*webservice调用*/
    tableview_show_type m_cur_tabview_state;
    CTransmitFile* m_file_transports;/*文件传输服务，目前只适用于Windows*/
    QTimer m_timer_watch_err_msg;
    QScopedPointer<QMessageBox> m_msg_box;
    QQueue<QString> m_err_msg;/*存放其他线程的错误消息*/
    QScopedPointer<QDockWidget> m_log_dock; /*日志子窗口*/
    QMap<int, book_info> m_book_info_map; /*从服务器获取的图书信息*/
    MyQHeaderView* m_upload_vheadeview;/*上传结果视图垂直表头指针*/
    bool m_select_all_button_state; /*全选状态*/
    bool m_commandline_invoke; /*命令行调用状态*/
    //    QScopedPointer<QTextEdit> m_log_edit;
    HelpDialog* m_help_dialog; /*帮助文档对话框*/
};
#endif // MAINWINDOW_H
