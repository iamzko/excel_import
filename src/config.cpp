#include "config.h"
#include "myglobal.h"

Config::Config()
    :have_read_config_file(false)
{

}

bool Config::make_config_xml(QString &config_file_path)
{
    //DomDocument类代表整个的XML文件。概念上讲：它是文档树的根节点，并提供了文档数据的基本访问方法。
    QDomDocument doc;
    QDomProcessingInstruction instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    QStringList temp_header_data;

    QDomElement root,element,attr_nodes;
    QDomText temp_text;
    QString col_name = "col";

    //根节点
    root = doc.createElement("headers");
    root.setAttribute("version", MyGlobal::the_config_version);
    doc.appendChild(root);

    //普通子节点
    QDomElement excel_header = doc.createElement("excel_header");
    root.appendChild(excel_header);

    temp_header_data << QString::fromLocal8Bit("序号")
                     << QString::fromLocal8Bit("出版者")
                     << QString::fromLocal8Bit("书名")
                     << QString::fromLocal8Bit("副书名")
                     << QString::fromLocal8Bit("分辑")
                     << QString::fromLocal8Bit("丛书名")
                     << QString::fromLocal8Bit("副丛书名")
                     << QString::fromLocal8Bit("丛书卷号")
                     << QString::fromLocal8Bit("ISBN")
                     << QString::fromLocal8Bit("作者")
                     << QString::fromLocal8Bit("丛书作者")
                     << QString::fromLocal8Bit("出版日期")
                     << QString::fromLocal8Bit("版本说明")
                     << QString::fromLocal8Bit("定价")
                     << QString::fromLocal8Bit("格式")
                     << QString::fromLocal8Bit("版权页")
                     << QString::fromLocal8Bit("封面")
                     << QString::fromLocal8Bit("其他")
                     << QString::fromLocal8Bit("备注")
                     << QString::fromLocal8Bit("语种")
                     << QString::fromLocal8Bit("授权起始时间")
                     << QString::fromLocal8Bit("授权结束时间")
                     << QString::fromLocal8Bit("授权方")
                     << QString::fromLocal8Bit("被授权方")
                     << QString::fromLocal8Bit("文件名")
                     << QString::fromLocal8Bit("载体类型")
                     << QString::fromLocal8Bit("著作类型")
                     << QString::fromLocal8Bit("适用读者")
                     << QString::fromLocal8Bit("用途")
                     << QString::fromLocal8Bit("经典图书")
                     << QString::fromLocal8Bit("核心图书")
                     << QString::fromLocal8Bit("高被引图书")
                     << QString::fromLocal8Bit("订单年");
    for(int i = 0; i < temp_header_data.size(); ++i)
    {
        QString temp = col_name + QString::number(i);
        element = doc.createElement(temp.toUtf8().data());
        excel_header.appendChild(element);
        temp_text = doc.createTextNode(temp_header_data[i]);
        element.appendChild(temp_text);
    }


    QDomElement upload_header = doc.createElement("upload_header");
    root.appendChild(upload_header);

    temp_header_data.clear();

    temp_header_data << QString::fromLocal8Bit("序号")
                     << QString::fromLocal8Bit("编号")
                     << QString::fromLocal8Bit("书名")
                     << QString::fromLocal8Bit("分辑")
                     << QString::fromLocal8Bit("上传数量")
                     << QString::fromLocal8Bit("是否上传成功")
                     << QString::fromLocal8Bit("提交结果");
    for(int i = 0; i < temp_header_data.size(); ++i)
    {
        QString temp = col_name + QString::number(i);
        element = doc.createElement(temp.toUtf8().data());
        upload_header.appendChild(element);
        temp_text = doc.createTextNode(temp_header_data[i]);
        element.appendChild(temp_text);
    }

    QDomElement error_show_header = doc.createElement("error_header");
    root.appendChild(error_show_header);
    temp_header_data.clear();
    temp_header_data << QString::fromLocal8Bit("行号")
                     << QString::fromLocal8Bit("列号")
                     << QString::fromLocal8Bit("字段名")
                     << QString::fromLocal8Bit("标准格式")
                     << QString::fromLocal8Bit("错误值")
                     << QString::fromLocal8Bit("错误说明");
    for(int i = 0; i < temp_header_data.size(); ++i)
    {
        QString temp = col_name + QString::number(i);
        element = doc.createElement(temp.toUtf8().data());
        error_show_header.appendChild(element);
        temp_text = doc.createTextNode(temp_header_data[i]);
        element.appendChild(temp_text);
    }



    QFile file(config_file_path);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    doc.save(out,4,QDomNode::EncodingFromTextStream);
    return true;

}
bool Config::read_config_xml(QString &config_file_path)
{
    if (config_file_path.isEmpty())
    {
        qDebug() << "empty";
        return false;
    }

    if (config_file_path.right(3).toUpper() != "XML")
    {
        qDebug() << "xml";
        return false;
    }

    QFile file(config_file_path);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "open";
        return false;
    }

    QDomDocument doc;	//如果前面没加root这里就无法读出file的内容
    if (!doc.setContent(&file))
    {
        qDebug() << "xml error";
        return false;
    }

    QDomElement root = doc.documentElement();
    QString config_version = root.attribute("version");
    if(config_version == MyGlobal::the_config_version)
    {
        QDomNode node,element;
        node = root.firstChild();
        node = node.firstChild();

        the_excel_header.clear();
        while (!node.isNull())
        {
            the_excel_header << node.toElement().text();
            node = node.nextSiblingElement();
        }
        node = root.firstChild();
        node = node.nextSiblingElement();
        node = node.firstChild();
        the_upload_header.clear();
        while(!node.isNull())
        {
            the_upload_header << node.toElement().text();
            node = node.nextSiblingElement();
        }
        node = root.firstChild();
        node = node.nextSiblingElement();
        node = node.nextSiblingElement();
        node = node.firstChild();
        the_check_state_header.clear();
        while(!node.isNull())
        {
            the_check_state_header << node.toElement().text();
            node = node.nextSiblingElement();
        }
        qDebug() << "the_upload_header size is :" << the_upload_header.size();
        qDebug() << "the_check_state_header size is :" << the_check_state_header.size();
    }
    have_read_config_file = true;
    return true;
}

QStringList Config::get_check_state_header() const
{
    return the_check_state_header;
}
QStringList Config::get_excel_header() const
{
    return the_excel_header;
}
QStringList Config::get_upload_header() const
{
    return the_upload_header;
}
