#include <objbase.h>
#include <iostream>
#include <vector>

#include "CSystemInfoFactory.h"


int main()
{
    HRESULT hr;
    CString InfoAboutSystem;
    CSystemInfo* cSystem = NULL;
    int MonitorCount;
    CLSID clsid;
    std::vector<uint32_t>* ResolutionX=new std::vector<uint32_t>;
    std::vector<uint32_t>* ResolutionY=new std::vector<uint32_t>;
    hr=CoInitialize( NULL );
    if( FAILED( hr ) )
    {
        std::cout << "Cant CoInitialize() " << std::endl;
        return 0;
    }
    
    hr = CLSIDFromProgID( L"Server.Inproc.1" , &clsid );
    if( FAILED( hr ) )
    {
        std::cout << "Cant get CLSID " << std::endl;
        return 0;
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
    hr = cSystem->MonitorInfo( &InfoAboutSystem, &MonitorCount, ResolutionX, ResolutionY );

    std::wcout << "monitor count with virtual: " << MonitorCount << std::endl << "Monitor name: " << InfoAboutSystem.GetString() << std::endl;
    for( int i = 0; i <ResolutionX->size(); i++ )
    {
        std::cout << "For monitor " << i << "\tResolution is " << ResolutionX->at(i) << "\tOn\t" << ResolutionY->at(i) << std::endl;
    }
    uint32_t clocks;
    uint32_t frequency;
    hr = cSystem->GetCPUINFO( &clocks,&frequency );
    std::wcout <<"Clocks:\t"<< clocks<<"\t"<<"Max frequency of clocks in MHz:\t"<<frequency << std::endl;
    CoUninitialize();
    return 0;
}
