#include <objbase.h>
#include <iostream>


#include "CSystemInfoFactory.h"


int main()
{
    HRESULT hr;
    CoInitialize( NULL );
    CSystemInfoFactory* cSystem = NULL;
    CLSID clsid;
    hr = CLSIDFromProgID( L"Server.Inproc.1" , &clsid );
    if( SUCCEEDED( hr ) )
    {
        std::cout << "Hello" << std::endl;
    }
    hr = CoCreateInstance( clsid,NULL, CLSCTX_INPROC_SERVER, IID_ISystemInfo, ( void** )&cSystem );
    if( SUCCEEDED( hr ) )
    {
        std::cout << "Instanse created" << std::endl;
    }
   /* CSystemInfo* info=NULL;
  //  cSystem->CreateInstance( NULL, IID_ISystemInfo, ( void** )&info );
    CString* tmp = new CString;
    info->GetCPUINFO( tmp );
    std::wcout << tmp->GetString() << std::endl;*/
    return 0;
}
