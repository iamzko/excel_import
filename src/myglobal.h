#ifndef MYGLOBAL_H
#define MYGLOBAL_H
#include <QString>

#define _IN_
#define _OUT_
#define _IN_OUT_


class MyGlobal
{
public:
    MyGlobal();
    static QString CONFIG_FILE_PATH;
    static QString CONFIG_VERSION;
    static QString APP_NAME;
    static int LINE_TYPE;
};

#endif // MYGLOBAL_H
