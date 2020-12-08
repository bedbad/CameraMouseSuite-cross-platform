#ifndef APPCONFIG_H
#define APPCONFIG_H
#include <QObject> // Included to have the OS defines

#ifdef Q_OS_LINUX
#elif defined Q_OS_WIN
#include <Shlwapi.h>
#include <windows.h>
#include "stdio.h"
#include<wchar.h>
#pragma comment(lib, "Shlwapi.lib")
#elif defined Q_OS_MAC
#endif
#include <iostream>
namespace CMS{
void setAutoStart(bool);
}
#endif // APPCONFIG_H
