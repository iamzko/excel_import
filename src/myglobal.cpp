#include "myglobal.h"

MyGlobal::MyGlobal()
{

}

QString MyGlobal::the_config_file_path = QString::fromUtf8(u8"./config.xml");

QString MyGlobal::the_config_version = QString::fromUtf8(u8"1.0");
