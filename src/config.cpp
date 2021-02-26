#include "config.h"
#include "myglobal.h"

Config::Config()
    :m_have_read_config_file(false)
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
    root = doc.createElement(u8"headers");
    root.setAttribute(u8"version", MyGlobal::CONFIG_VERSION);
    doc.appendChild(root);

    //普通子节点
    QDomElement excel_header = doc.createElement("excel_header");
    root.appendChild(excel_header);

    temp_header_data << QString::fromUtf8(u8"序号")
                     << QString::fromUtf8(u8"出版者")
                     << QString::fromUtf8(u8"书名")
                     << QString::fromUtf8(u8"副书名")
                     << QString::fromUtf8(u8"分辑")
                     << QString::fromUtf8(u8"丛书名")
                     << QString::fromUtf8(u8"副丛书名")
                     << QString::fromUtf8(u8"丛书卷号")
                     << QString::fromUtf8(u8"ISBN")
                     << QString::fromUtf8(u8"作者")
                     << QString::fromUtf8(u8"丛书作者")
                     << QString::fromUtf8(u8"出版日期")
                     << QString::fromUtf8(u8"版本说明")
                     << QString::fromUtf8(u8"定价")
                     << QString::fromUtf8(u8"格式")
                     << QString::fromUtf8(u8"版权页")
                     << QString::fromUtf8(u8"封面")
                     << QString::fromUtf8(u8"其他")
                     << QString::fromUtf8(u8"备注")
                     << QString::fromUtf8(u8"语种")
                     << QString::fromUtf8(u8"授权起始时间")
                     << QString::fromUtf8(u8"授权结束时间")
                     << QString::fromUtf8(u8"授权方")
                     << QString::fromUtf8(u8"被授权方")
                     << QString::fromUtf8(u8"文件名")
                     << QString::fromUtf8(u8"载体类型")
                     << QString::fromUtf8(u8"著作类型")
                     << QString::fromUtf8(u8"适用读者")
                     << QString::fromUtf8(u8"用途")
                     << QString::fromUtf8(u8"经典图书")
                     << QString::fromUtf8(u8"核心图书")
                     << QString::fromUtf8(u8"高被引图书")
                     << QString::fromUtf8(u8"订单年");
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

    temp_header_data << QString::fromUtf8(u8"序号")
                     << QString::fromUtf8(u8"编号")
                     << QString::fromUtf8(u8"书名")
                     << QString::fromUtf8(u8"分辑")
                     << QString::fromUtf8(u8"上传数量")
                     << QString::fromUtf8(u8"是否上传成功")
                     << QString::fromUtf8(u8"提交结果");
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
    temp_header_data << QString::fromUtf8(u8"行号")
                     << QString::fromUtf8(u8"列号")
                     << QString::fromUtf8(u8"字段名")
                     << QString::fromUtf8(u8"标准格式")
                     << QString::fromUtf8(u8"错误值")
                     << QString::fromUtf8(u8"错误说明");
    for(int i = 0; i < temp_header_data.size(); ++i)
    {
        QString temp = col_name + QString::number(i);
        element = doc.createElement(temp.toUtf8().data());
        error_show_header.appendChild(element);
        temp_text = doc.createTextNode(temp_header_data[i]);
        element.appendChild(temp_text);
    }

    QDomElement db_key = doc.createElement("database_connection");
    root.appendChild(db_key);
    element = doc.createElement(QString::fromUtf8(u8"ip"));
    temp_text = doc.createTextNode(QString::fromUtf8(u8"192.168.3.61"));
    element.appendChild(temp_text);
    db_key.appendChild(element);

    element = doc.createElement(QString::fromUtf8(u8"username"));
    element.appendChild(doc.createTextNode(QString::fromUtf8(u8"sa")));
    db_key.appendChild(element);

    element = doc.createElement(QString::fromUtf8(u8"password"));
    element.appendChild(doc.createTextNode(QString::fromUtf8(u8"xwline_2012")));
    db_key.appendChild(element);

    element = doc.createElement(QString::fromUtf8(u8"dbname"));
    element.appendChild(doc.createTextNode(QString::fromUtf8(u8"图书论文2016")));
    db_key.appendChild(element);



    QFile file(config_file_path);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }
    QTextStream out(&file);
    out.setCodec(u8"UTF-8");
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
    if(config_version == MyGlobal::CONFIG_VERSION)
    {
        QDomNode node,element;
        node = root.firstChild();
        node = node.firstChild();

        m_the_excel_header.clear();
        while (!node.isNull())
        {
            m_the_excel_header << node.toElement().text();
            node = node.nextSiblingElement();
        }
        node = root.firstChild();
        node = node.nextSiblingElement();
        node = node.firstChild();
        m_the_upload_header.clear();
        while(!node.isNull())
        {
            m_the_upload_header << node.toElement().text();
            node = node.nextSiblingElement();
        }
        node = root.firstChild();
        node = node.nextSiblingElement();
        node = node.nextSiblingElement();
        node = node.firstChild();
        m_the_check_state_header.clear();
        while(!node.isNull())
        {
            m_the_check_state_header << node.toElement().text();
            node = node.nextSiblingElement();
        }

        auto db_config= root.firstChildElement(QString::fromUtf8(u8"database_connection"));
        if(!db_config.isNull())
        {
            auto db_config_ip = db_config.firstChildElement(QString::fromUtf8(u8"ip"));
            m_the_db_key.push_back(db_config_ip.text());
            m_the_db_key.push_back(u8"@");
            auto db_config_username = db_config.firstChildElement(QString::fromUtf8(u8"username"));
            m_the_db_key.push_back(db_config_username.text());
            m_the_db_key.push_back(u8"@");
            auto db_config_password = db_config.firstChildElement(QString::fromUtf8(u8"password"));
            m_the_db_key.push_back(db_config_password.text());
            m_the_db_key.push_back(u8"@");
            auto db_config_dbname = db_config.firstChildElement(QString::fromUtf8(u8"dbname"));
            m_the_db_key.push_back(db_config_dbname.text());
            m_the_db_key.push_back(u8"@");
        }
        else
        {
            return false;
        }


        qDebug() << "the_upload_header size is :" << m_the_upload_header.size();
        qDebug() << "the_check_state_header size is :" << m_the_check_state_header.size();
    }
    m_have_read_config_file = true;
    return true;
}

QStringList Config::get_check_state_header() const
{
    return m_the_check_state_header;
}

QString Config::get_db_key() const
{
    return m_the_db_key;
}
QStringList Config::get_excel_header() const
{
    return m_the_excel_header;
}
QStringList Config::get_upload_header() const
{
    return m_the_upload_header;
}
