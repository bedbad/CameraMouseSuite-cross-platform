#include "AppConfig.h"


void CMS::setAutoStart(bool val){
#ifdef Q_OS_WIN
        HMODULE hModule = GetModuleHandleW(NULL);
       WCHAR path[MAX_PATH];
       GetModuleFileNameW(hModule, path, MAX_PATH);
       PathRemoveFileSpecW(path);
       SetCurrentDirectoryA("C:/ProgramData/Microsoft/Windows/Start Menu/Programs/StartUp/");
       std::FILE *str=fopen("CMS.bat","w+");
       fseek(str,0,SEEK_SET);
       if(str){
           if(!val){
               fwprintf(str,L"::");
           }
           fwprintf(str,L"start \"\" \"%S/CameraMouseSuite.exe\"",path);
       }
       fclose(str);
#endif
}
