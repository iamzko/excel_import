#ifndef MYGLOBAL_H
#define MYGLOBAL_H
#include <QString>

#define _IN_
#define _OUT_
#define _IN_OUT_

struct book_info
{
    QString publisher;
    QString bookname;
    QString vicebookname;
    QString bookpart;
    QString bookparentname;
    QString isbn;
    QString author;
    QString publishdate;
    QString price;
    QString format;
    QString copyrightpage;
    QString cover;
    QString other;
    QString remark;
    QString language;
    QString filestate;
    QString processstate;
    QString filenums;
    QString serialnum;
    QString arrivaltime;
    QString franchisor;
    QString authorizedparty;
    QString authorizationstarttime;
    QString authorizationendtime;
    QString filename;
    QString vicebookparentname;
    QString bookparentnum;
    QString bookparentauthor;
    QString versionnote;
    QString carriertype;
    QString booktype;
    QString applicablereader;
    QString purpose;
    QString ordersyear;
};

class MyGlobal
{
public:
    MyGlobal();
    static const QString CONFIG_FILE_PATH;
    static const QString CONFIG_VERSION;
    static const QString APP_NAME;
    static const QString DZ_PREFIX;
    static const QString XK_PREFIX;
    static const int LINE_TYPE;
};

#endif // MYGLOBAL_H
