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

#include "config.h"
#include "excelreader.h"
#include "excelfieldrule.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void on_pushButtonSearch_clicked();
    void on_pushButtonOpenDir_clicked();
    void on_pushButtonUploadDB_clicked();
private slots:
    void on_currentChanged(const QModelIndex &current,const QModelIndex &previous);

private:

    bool read_excel_model_file();
    bool check_batch_num_input();
    bool check_excel_header(QStringList &target_header);
private:
    Ui::MainWindow *ui;
    //状态栏显示1
    QLabel *m_statusbar_label;
    QMap<QString,QVector<QString>> m_excel_data; /*excel数据*/
    QStandardItemModel *m_model_excel_data; /*excel内容数据模型*/
    QItemSelectionModel *m_selection_excel_data; /*选择模型*/
    QStandardItemModel *m_model_upload_data; /*上传状态数据模型*/
    QItemSelectionModel *m_selection_upload_data; /*选择模型*/
    QStandardItemModel *m_model_excel_check_state; /*excel检查状态数据模型*/
    QStringList m_excel_header; /*excel数据的表头*/
    QStringList m_upload_header;/*上传状态数据的表头*/
    QStringList m_check_state_header;/*excel检查错误的表头*/
    Config m_config;
    QScopedPointer<ExcelReader> m_excel_reader;
    QVector<ExcelFieldRule> m_xinke_rules;
    QVector<ExcelFieldRule> m_public_xinke_rules;

};
#endif // MAINWINDOW_H
