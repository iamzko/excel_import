#include "myglobal.h"

MyGlobal::MyGlobal()
{

}

QString MyGlobal::CONFIG_FILE_PATH = QString::fromUtf8(u8"./config.xml");

QString MyGlobal::CONFIG_VERSION = QString::fromUtf8(u8"1.0");

QString MyGlobal::APP_NAME = QString::fromUtf8(u8"接收登记");

int MyGlobal::LINE_TYPE = 2;
