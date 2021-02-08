#ifndef MYGLOBAL_H
#define MYGLOBAL_H
#include <QString>


class MyGlobal
{
public:
    MyGlobal();
    static QString the_config_file_path;
    static QString the_config_version;
};

#endif // MYGLOBAL_H
