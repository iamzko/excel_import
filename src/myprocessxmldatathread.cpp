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
        book.publisher = node.firstChildElement("publisher").text();
        book.bookname = node.firstChildElement("bookname").text();
        book.vicebookname = node.firstChildElement("vicebookname").text();
        book.bookpart = node.firstChildElement("bookpart").text();
        book.bookparentname = node.firstChildElement("bookparentname").text();
        book.vicebookparentname = node.firstChildElement("vicebookparentname").text();
        book.bookparentnum = node.firstChildElement("bookparentnum").text();
        book.isbn = node.firstChildElement("isbn").text();
        book.author = node.firstChildElement("author").text();
        book.bookparentauthor = node.firstChildElement("bookparentauthor").text();
        book.publishdate = node.firstChildElement("publishdate").text();
        book.versionnote = node.firstChildElement("versionnote").text();
        book.price = node.firstChildElement("price").text();
        book.format = node.firstChildElement("format").text();
        book.copyrightpage = node.firstChildElement("copyrightpage").text();
        book.cover = node.firstChildElement("cover").text();
        book.other = node.firstChildElement("other").text();
        book.remark = node.firstChildElement("remark").text();
        book.language = node.firstChildElement("language").text();
        book.authorizationstarttime = node.firstChildElement("authorizationstarttime").text();
        book.authorizationendtime = node.firstChildElement("authorizationendtime").text();
        book.franchisor = node.firstChildElement("franchisor").text();
        book.authorizedparty = node.firstChildElement("authorizedparty").text();
        book.filename = node.firstChildElement("filename").text();
        book.carriertype = node.firstChildElement("carriertype").text();
        book.booktype = node.firstChildElement("booktype").text();
        book.applicablereader = node.firstChildElement("applicablereader").text();
        book.purpose = node.firstChildElement("purpose").text();
        model_col += 3;
        book.ordersyear = node.firstChildElement("ordersyear").text();
        book.processstate = node.firstChildElement("processstate").text();
        qDebug() << book.processstate;
        book.filestate = node.firstChildElement("filestate").text();
        book.arrivaltime = node.firstChildElement("arrivaltime").text();
        book.serialnum = node.firstChildElement("serialnum").text();
        book.filenums = node.firstChildElement("filenums").text();
        book.usertype = node.firstChildElement("usertype").text();

        m_main_widget->m_book_info_map.insert(count,book);
        qDebug() << "thread cur_row:" << model_row;
        count++;
        model_row++;
        node = node.nextSibling();
    }

    qDebug() << "count :" << count;


}
