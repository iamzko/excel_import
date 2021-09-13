#include "helpdialog.h"
#include "ui_helpdialog.h"

HelpDialog* HelpDialog::help_handle = nullptr;
HelpDialog::HelpDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
}

HelpDialog* HelpDialog::instance(QWidget* parent)
{
    if (help_handle == nullptr) {
        help_handle = new HelpDialog(parent);
        help_handle->set_help_info();
        help_handle->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
        help_handle->setWindowTitle(QString::fromUtf8(u8"帮助文档"));
    }
    return help_handle;
}

HelpDialog::~HelpDialog()
{
    delete ui;
}

void HelpDialog::set_help_info()
{
    ui->textBrowser->setText(QString::fromStdWString(LR"(接收登记工具帮助说明：

1.双击“excel_import.exe”，打开工具；
或在web页面中创建批次号后点击“导入题录”按钮，调起工具。
                 （注：工具被调起的前提条件是之前被手动运行过）

2.在工具界面中，操作步骤如下：
   
           “批次号编辑框”：输入批次号
                  ｜
                  ｜
                  ↓
           “①查询批次号”按钮
                  ｜
                  ｜（工具校验批次号无误）
                  ↓
           “②选择输入文件”按钮：选择题录清单文件
                  ｜
                  ｜（题录清单经校验无误）
                  ↓
           “③开始导入”按钮
                  ｜
                  ｜（题录清单内容导入成功）
                  ↓
           “④文件上传”按钮：选择待上传图书书名文件夹的上层文件夹
                  ｜
                  ｜（全部文件上传成功且完成）
                  ↓
“批量篇提交”按钮 / 篇数据后的“提交”按钮
                  ｜
                  ｜（当前批次下的全部篇数据已全部提交）          
                  ↓
           “批提交”按钮

3.题录校验规范
    
   当产品类型=心可书馆
          出版者不为空
          书名不为空
          作者不为空
          ISBN不为空    
          授权起始时间可为空，但若不为空格式为YYYYMMDD
          授权结束时间可为空，但若不为空格式为YYYYMMDD
          版本说明不为空
          授权方不为空
          被授权方不为空
          出版日期不为空，且格式为YYYYMM
          定价不为空，且仅能填写数字，最终显示两位小数
          载体类型不为空
          经典图书不为空，且仅能填写是/否
          核心图书不为空，且仅能填写是/否
          高被引图书不为空，且仅能填写是/否
          订单年不为空，格式为YYYY

    当产品类型=大众阅读/非心可书馆
          出版者不为空
          书名不为空
          作者不为空
          ISBN不为空  
            授权起始时间不为空，且格式为YYYYMMDD——大众阅读
            授权结束时间不为空，且格式为YYYYMMDD——大众阅读
            授权起始时间可为空，但若不为空格式为YYYYMMDD——非大众阅读
            授权结束时间可为空，但若不为空格式为YYYYMMDD——非大众阅读
          授权方不为空
          被授权方不为空
          出版日期不为空
          定价不为空，且仅能填写数字，最终显示两位小数
          订单年可为空，但若不为空格式为YYYY

4.文件命名规范

    对于有分辑的数据，书名文件夹命名格式为：

             “书名”+ “♂”+“分辑”

    当一书中包含多个文件时:
        接收类型=盘，制作方式=纯盘，文件命名格式如下：
           
              1_封面，2_目录，3_版权页，4_正文，5_封底

        
        接收类型=盘，制作方式=纯刊，格式如下：

              1.上传的文件格式，仅支持“TIF”类型
              2.文件命名格式如下：xxxxx.0001.tif，xxxxx.0002.tif，xxxxx.0003.tif
)"));
}
