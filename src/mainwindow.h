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
#include <QThread>
#include <QTimer>
#include <QMessageBox>
#include <QQueue>
#include <QDockWidget>
#include <QTextEdit>

//webservice相关
//#include "webservice/soapH.h"
#include "webserviceallin/soapH.h"

//fileserver相关
#include "NeoFileClientU/include/NeoFileClientUAPI.h"


#include "config.h"
#include "excelreader.h"
#include "excelfieldrule.h"
#include "myglobal.h"
#include "myprocessxmldatathread.h"
#include "myqheaderview.h"



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
    enum class product_type
    {
        TYPE_XK,
        TYPE_DZ,
        TYPE_OTHER,
    };

    friend class MyProcessXmlDataThread;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void mousePressEvent(QMouseEvent *event);
    bool eventFilter(QObject* o,QEvent *e);
public slots:
    void on_pushButtonSearch_clicked();
    void on_pushButtonOpenDir_clicked();
    void on_pushButtonUploadDB_clicked();
    void on_pushButtonChooseFile_clicked();
    void on_pushButtonShowLog_clicked();
    void on_pushButtonTest_clicked();
    void on_pushButtonBulkBookCommit_clicked();
    void on_pushButtonBatchCommit_clicked();
    void on_lineEditBatchNum_textEdited(const QString &text);
    void on_pushButtonIndividualBookSubmit();
    void on_err_msg_show();
    void on_select_rows(const QModelIndex&);
    void on_select_all_rows();
private slots:
    void on_currentChanged(const QModelIndex &current,const QModelIndex &previous);
    void on_thread_data_finish();
signals:
    void press_row(int row);

private:
    void resizeEvent(QResizeEvent* size);
    int submit(int row);


    bool read_excel_model_file();
    bool check_batch_num_input();
    bool check_excel_header(QStringList &target_header);
    int check_web_service_query_result(_IN_ std::wstring &web_result,_OUT_ QString &msg_data, _IN_ web_service_type type);
    void process_json_data_from_web(_IN_ QString &json_data,
                                    _OUT_ QString &server_ip,
                                    _OUT_ QString &file_server_ip,
                                    _OUT_ QString &file_server_port,
                                    _OUT_ QString &file_server_root);
    void reset_data_model();
    void reset_error_show_model();
    void add_button_and_progressbar_to_upload_model();
    QStringList get_all_file_path(_IN_ file_process_type type, _IN_ QString &dir_name,_OUT_ quint64 total_size, _OUT_ QString &err_msg);
    void write_to_log_dock(_IN_ QString msg);
    QStringList get_all_filename_from_compressed(QString compressed_filepath);
    void init_excel_checker();
    bool get_data_from_db_to_upload_data();
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
    QScopedPointer<QDockWidget> m_log_dock;
    QMap<int,book_info> m_book_info_map;
    MyQHeaderView* m_upload_vheadeview;/*上传结果视图垂直表头指针*/
    bool m_select_all_button_state;
//    QScopedPointer<QTextEdit> m_log_edit;
};
#endif // MAINWINDOW_H
