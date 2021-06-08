#include "myprocessxmldatathread.h"

MyProcessXmlDataThread::MyProcessXmlDataThread()
{
    m_main_widget = nullptr;
}

MyProcessXmlDataThread::MyProcessXmlDataThread(MainWindow *main_widget,QString data)
{
    m_main_widget = main_widget;
    m_xml_data = data;
}

void MyProcessXmlDataThread::run()
{
    QDomDocument doc;
    doc.setContent(m_xml_data);
    auto root = doc.firstChildElement(QString::fromUtf8(u8"NewDataSet"));
    auto node = root.firstChild();
    int count = 0;
    int model_row = 0;
    int model_col = 0;
    m_main_widget->m_book_info_map.clear();

    while(!node.isNull())
    {
        model_col = 0;
        book_info book;
        //        qDebug()<< count << ":" << node.toElement().text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(QString::number(count+1)));
        book.publisher = node.firstChildElement("publisher").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.publisher));
        book.bookname = node.firstChildElement("bookname").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.bookname));
        book.vicebookname = node.firstChildElement("vicebookname").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.vicebookname));
        book.bookpart = node.firstChildElement("bookpart").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.bookpart));
        book.bookparentname = node.firstChildElement("bookparentname").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.bookparentname));
        book.vicebookparentname = node.firstChildElement("vicebookparentname").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.vicebookparentname));
        book.bookparentnum = node.firstChildElement("bookparentnum").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.bookparentnum));
        book.isbn = node.firstChildElement("isbn").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.isbn));
        book.author = node.firstChildElement("author").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.author));
        book.bookparentauthor = node.firstChildElement("bookparentauthor").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.bookparentauthor));
        book.publishdate = node.firstChildElement("publishdate").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.publishdate));
        book.versionnote = node.firstChildElement("versionnote").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.versionnote));
        book.price = node.firstChildElement("price").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.price));
        book.format = node.firstChildElement("format").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.format));
        book.copyrightpage = node.firstChildElement("copyrightpage").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.copyrightpage));
        book.cover = node.firstChildElement("cover").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.cover));
        book.other = node.firstChildElement("other").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.other));
        book.remark = node.firstChildElement("remark").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.remark));
        book.language = node.firstChildElement("language").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.language));
        book.authorizationstarttime = node.firstChildElement("authorizationstarttime").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.authorizationstarttime));
        book.authorizationendtime = node.firstChildElement("authorizationendtime").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.authorizationendtime));
        book.franchisor = node.firstChildElement("franchisor").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.franchisor));
        book.authorizedparty = node.firstChildElement("authorizedparty").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.authorizedparty));
        book.filename = node.firstChildElement("filename").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.filename));
        book.carriertype = node.firstChildElement("carriertype").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.carriertype));
        book.booktype = node.firstChildElement("booktype").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.booktype));
        book.applicablereader = node.firstChildElement("applicablereader").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.applicablereader));
        book.purpose = node.firstChildElement("purpose").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.purpose));
        model_col += 3;
        book.ordersyear = node.firstChildElement("ordersyear").text();
//        m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(book.ordersyear));
        book.processstate = node.firstChildElement("processstate").text();
        qDebug() << book.processstate;
        book.filestate = node.firstChildElement("filestate").text();
//        if(book.processstate == QString::fromUtf8(u8"已处理"))
//        {
//            m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(QString::fromUtf8(u8"已提交")));
//            /*            if (v == BookState.Imported)
//                return "已导入,未上传";
//            else if (v == BookState.Uploaded)
//                return "已上传,未提交";
//            else if (v == BookState.Submited)
//                return "已提交";
//            else
//                return null;*/
//        }
//        else if(book.filestate == QString::fromUtf8(u8"True"))
//        {
//            m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(QString::fromUtf8(u8"已上传,未提交")));
//        }
//        else
//        {
//            m_main_widget->m_model_excel_data->setItem(model_row,model_col++,new QStandardItem(QString::fromUtf8(u8"已导入,未上传")));
//        }
        book.arrivaltime = node.firstChildElement("arrivaltime").text();
        book.serialnum = node.firstChildElement("serialnum").text();
        book.filenums = node.firstChildElement("filenums").text();

        m_main_widget->m_book_info_map.insert(count,book);
//        model_col = 0;
//        m_main_widget->m_model_upload_data->setItem(model_row,model_col++,new QStandardItem(QString::number(count+1)));
//        m_main_widget->m_model_upload_data->setItem(model_row,model_col++,new QStandardItem(book.serialnum));
//        m_main_widget->m_model_upload_data->setItem(model_row,model_col++,new QStandardItem(book.bookname));
//        m_main_widget->m_model_upload_data->setItem(model_row,model_col++,new QStandardItem(book.bookpart));
//        m_main_widget->m_model_upload_data->setItem(model_row,model_col++,new QStandardItem(book.filenums));
//        m_main_widget->m_model_upload_data->setItem(model_row,model_col++,new QStandardItem(book.filenums == QString::fromUtf8(u8"0")?QString::fromUtf8(u8"否，未上传"):QString::fromUtf8(u8"是")));
//        m_main_widget->m_model_upload_data->setItem(model_row,model_col++,new QStandardItem(book.processstate == QString::fromUtf8(u8"已处理")?QString::fromUtf8(u8"已提交"):QString::fromUtf8(u8"未提交")));
//        emit data_update(model_row);
        qDebug() << "thread cur_row:" << model_row;
        //                auto temp_item = new QStandardItem(temp_str);
        //                m_model_excel_check_state.setItem(model_i,model_j,temp_item);
        count++;
        model_row++;
        node = node.nextSibling();
//        QThread::msleep(10);
    }
    //    m_model_upload_data->insertRows(0,m_model_upload_data->rowCount());

    qDebug() << "count :" << count;


}
