#include <objbase.h>
#include <iostream>


#include "CSystemInfoFactory.h"


int main()
{
    HRESULT hr;
    CString InfoAboutSystem;
    CSystemInfo* cSystem = NULL;
    int MonitorCount;
    CLSID clsid;
    hr=CoInitialize( NULL );
    if( FAILED( hr ) )
    {
        std::cout << "Cant CoInitialize() " << std::endl;
    }
    
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
   
    hr = cSystem->GetOS( &InfoAboutSystem );
    std::wcout << "OS Version: \t" ;
    std::wcout << InfoAboutSystem.GetString() << std::endl;
    InfoAboutSystem.Delete( 0, InfoAboutSystem.GetLength() );
    std::wcout << "Motherboard creator: \t";
    hr = cSystem->GetMBoardCreator( &InfoAboutSystem );
    std::wcout << InfoAboutSystem.GetString() << std::endl;
    InfoAboutSystem.Delete( 0, InfoAboutSystem.GetLength() );
    hr = cSystem->MonitorInfo( &InfoAboutSystem,&MonitorCount );
    std::wcout << "Monitor count: " << MonitorCount << std::endl << "Monitor name: " << InfoAboutSystem.GetString() << std::endl;
    uint32_t clocks;
    uint32_t frequency;
    hr = cSystem->GetCPUINFO( &clocks,&frequency );
    std::wcout <<"Clocks:\t"<< clocks<<"\t"<<"Max frequency of clocks in MHz:\t"<<frequency << std::endl;
    CoUninitialize();
    return 0;
}
