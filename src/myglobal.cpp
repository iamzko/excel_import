#include "myglobal.h"

MyGlobal::MyGlobal()
{

}

QString MyGlobal::the_config_file_path = QString::fromLocal8Bit("./config.xml");

QString MyGlobal::the_config_version = QString::fromLocal8Bit("1.0");
