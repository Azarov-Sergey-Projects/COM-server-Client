#include <objbase.h>
#include <iostream>


#include "CSystemInfoFactory.h"


int main()
{
    HRESULT hr;
    CoInitialize( NULL );
    CSystemInfo* cSystem = NULL;
    CLSID clsid;
    hr = CLSIDFromProgID( L"Server.Inproc.1" , &clsid );
    if( FAILED( hr ) )
    {
        std::cout << "Cant get CLSID " << std::endl;
    }
    hr = CoCreateInstance( clsid,NULL, CLSCTX_INPROC_SERVER, IID_ISystemInfo, ( void** )&cSystem );
    if( FAILED( hr ) )
    {
        std::cout << "Cant Create Instance" << std::endl;
    }
    CString tmp;
    hr = cSystem->GetOS( &tmp );
    std::wcout << "OS Info: \t" ;
    std::wcout << tmp.GetString() << std::endl;
    tmp.Delete( 0, tmp.GetLength() );
    std::wcout << "Motherboard info: \t";
    hr = cSystem->GetMBoardCreator( &tmp );
    std::wcout << tmp.GetString() << std::endl;
    tmp.Delete( 0, tmp.GetLength() );
    std::wcout << "Monitor Info: \t";
    hr = cSystem->MonitorInfo( &tmp );
    std::wcout << tmp.GetString() << std::endl;
    uint32_t clocks;
    uint32_t frequency;
    hr = cSystem->GetCPUINFO( &clocks,&frequency );
    std::wcout << "CPU info " << std::endl;
    std::wcout <<"Clocks:\t"<< clocks<<"\t"<<"Max frequency of clocks in MHz:\t"<<frequency << std::endl;
    CoUninitialize();
    return 0;
}
