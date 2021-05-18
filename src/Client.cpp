#include <objbase.h>
#include <iostream>
#include <vector>

#include "SystemInfoFactory.h"


int main()
{
    HRESULT hr;
    CString InfoAboutSystem;
    SystemInfo* cSystem = NULL;
    int MonitorCount;
    CLSID clsid;
    std::vector<uint32_t>* ResolutionX=new std::vector<uint32_t>;
    std::vector<uint32_t>* ResolutionY=new std::vector<uint32_t>;
    hr=CoInitialize( NULL );
    if( FAILED( hr ) )
    {
        std::cout << "Cant CoInitialize() " << std::endl;
        return 1;
    }
    
    hr = CLSIDFromProgID( L"Server.Inproc.1" , &clsid );
    if( FAILED( hr ) )
    {
        std::cout << "Cant get CLSID " << std::endl;
        return 1;
    }
    hr = CoCreateInstance( clsid,NULL, CLSCTX_INPROC_SERVER, IID_ISystemInfo, ( void** )&cSystem );
    if( FAILED( hr ) )
    {
        std::cout << "Cant Create Instance" << std::endl;
        return 1;
    }
   
    hr = cSystem->getOS( &InfoAboutSystem );
    if( FAILED( hr ) )
    {
        std::cout << "Cant Get OS info" << std::endl;
        return 1;
    }
    std::wcout << "OS Version: \t" ;
    std::wcout << InfoAboutSystem.GetString() << std::endl;
    InfoAboutSystem.Delete( 0, InfoAboutSystem.GetLength() );
    std::wcout << "Motherboard creator: \t";
    hr = cSystem->getMBoardCreator( &InfoAboutSystem );
    if( FAILED( hr ) )
    {
        std::cout << "Cant Get MotherBoard Info" << std::endl;
        return 1;
    }
    std::wcout << InfoAboutSystem.GetString() << std::endl;
    InfoAboutSystem.Delete( 0, InfoAboutSystem.GetLength() );
    hr = cSystem->monitorInfo( &InfoAboutSystem, &MonitorCount, ResolutionX, ResolutionY );
    if( FAILED( hr ) )
    {
        std::cout << "Cant Get Monitor Info" << std::endl;
        return 1;
    }
    std::wcout << "monitor count\t " << MonitorCount << std::endl << "Monitor name: " << InfoAboutSystem.GetString() << std::endl;
    for( int i = 0; i <ResolutionX->size(); i++ )
    {
        std::cout << "For monitor " << i+1 << "\tResolution is " << ResolutionX->at(i) << "\tOn\t" << ResolutionY->at(i) << std::endl;
    }
    uint32_t clocks;
    uint32_t frequency;
    hr = cSystem->getCPUINFO( &clocks,&frequency );
    if( FAILED( hr ) )
    {
        std::cout << "Cant get CPU Information" << std::endl;
        return 1;
    }
    std::wcout <<"Cores:\t"<< clocks<<"\t"<<"Max frequency of clocks in MHz:\t"<<frequency << std::endl;
    ResolutionX->clear();
    ResolutionY->clear();
    delete ResolutionX;
    delete ResolutionY;
    CoUninitialize();
    return 0;
}
