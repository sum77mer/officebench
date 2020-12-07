#include "officecontrol.h"

#include <stdio.h>
#include <wchar.h>

#include <sal/main.h>
#include <cppuhelper/bootstrap.hxx>

#include <osl/file.hxx>
#include <osl/process.h>
#include <rtl/process.h>

#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/bridge/XUnoUrlResolver.hpp>
#include <com/sun/star/frame/Desktop.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/registry/XSimpleRegistry.hpp>

#include <string.h>

using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::bridge;
using namespace com::sun::star::frame;
using namespace com::sun::star::registry;

using ::rtl::OUString;
using ::rtl::OUStringToOString;

//edit

#include <iostream>	//std::cout
#include <cstring>	//strerror
#include <errno.h>	//errno
using namespace com::sun::star::util;//XCloseable
#include <com/sun/star/util/XCloseable.hpp>
using namespace com::sun::star::awt;//XWindow
#include <com/sun/star/awt/XWindow.hpp>
#include <thread>//sleep
#include <chrono>//nanosecond
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/times.h>

OfficeControl::GeneralControl::GeneralControl()
{

}

//launch libreoffice(soffice?), not libreoffice writer or anything else.
//inherite class can implemente themself to launch corresponding app
//can be writer, Calc, Impress, Draw, Math, or Base(if it's installed).
void OfficeControl::GeneralControl::start_app()
{
    Reference <XComponentContext> xComponentContext(::cppu::bootstrap());
    if(!xComponentContext.is())
    {
        std::cout<<"xComponentContext NULL:"<<std::strerror(errno)<<std::endl;
        //return 1;
    }
    Reference <XMultiComponentFactory> xServiceManager(xComponentContext->getServiceManager());
    if(!xServiceManager.is())
    {
        std::cout<<"xServiceManager NULL:"<<std::strerror(errno)<<std::endl;
        //return 1;
    }
    Reference <XInterface> xInterface = xServiceManager->createInstanceWithContext(OUString::createFromAscii("com.sun.star.frame.Desktop"),xComponentContext);
    if(!xInterface.is())
    {
        std::cout<<"xInterface NULL:"<<std::strerror(errno)<<std::endl;
        //return 1;
    }
    Reference <XDesktop2> desktop = Desktop::create(xComponentContext);
    if(!desktop.is())
    {
        std::cout<<"desktop NULL:"<<std::strerror(errno)<<std::endl;
        //return 1;
    }
    Reference <XComponentLoader> xComponentLoader(desktop,UNO_QUERY_THROW);
    if(!xComponentLoader.is())
    {
        std::cout<<"xComponetLoader NULL:"<<std::strerror(errno)<<std::endl;
        //return 1;
    }
    else{
        auto currenttime = std::chrono::high_resolution_clock::now();
        //double duration =  std::chrono::duration_cast<std::chrono::microseconds>(currenttime-begintime).count();
        //std::cout<<duration/1000000<<" | "<<"Going to open file ..."<<std::endl;
    }
    OUString application;
    application = OUString::createFromAscii("private:factory/soffice");

    xComponent = xComponentLoader->loadComponentFromURL(application,
            OUString::createFromAscii("_blank"),
            0,
            Sequence<::com::sun::star::beans::PropertyValue>());
    if(!xComponent.is())
    {
        std::cout<<"xComponent NULL:"<<std::strerror(errno)<<std::endl;
        //return 1;
    }
    else{
        auto currenttime = std::chrono::high_resolution_clock::now();
        //double duration =  std::chrono::duration_cast<std::chrono::microseconds>(currenttime-begintime).count();
        //std::cout<<duration/1000000<<" | "<<"File Opened ..."<<std::endl;
    }
    return;
}
//create a new document
//can be text document, spreadsheet, presentation, drawing, formula,
//HTML document, XML form document, labels, business cards, master document, templates.
void OfficeControl::GeneralControl::new_doc()
{

}
//open old file
//file type can be opened are same with new_doc()
void OfficeControl::GeneralControl::open_doc()
{

}
//cloase document without save
void OfficeControl::GeneralControl::close_doc()
{

}
//resize window size
void OfficeControl::GeneralControl::resize()
{
    Reference <XModel> xModel(xComponent,UNO_QUERY_THROW);
    if(!xModel.is())
    {
        std::cout<<"xModel NULL:"<<std::strerror(errno)<<std::endl;
        //return 1;
    }
    Reference <XController> xController = xModel->getCurrentController();
    if(!xController.is())
    {
        std::cout<<"xController NULL:"<<std::strerror(errno)<<std::endl;
        //return 1;
    }
    Reference <XFrame> xFrame = xController->getFrame();
    if(!xFrame.is())
    {
        std::cout<<"xFrame NULL:"<<std::strerror(errno)<<std::endl;
        //return 1;
    }
    Reference <XWindow> xWindow = xFrame->getContainerWindow();
    if(!xWindow.is())
    {
        std::cout<<"xWindow NULL:"<<std::strerror(errno)<<std::endl;
        //return 0;
    }
    else{
        auto currenttime = std::chrono::high_resolution_clock::now();
        //double duration =  std::chrono::duration_cast<std::chrono::microseconds>(currenttime-begintime).count();
        //std::cout<<duration/1000000<<" | "<<"Going to resize ..."<<std::endl;
    }
    xWindow->setPosSize(0,0,100,100,15);
    std::this_thread::sleep_for(std::chrono::nanoseconds(500));
    for(int i=0;i<80;i++)
    {
        xWindow->setPosSize(0,0,100+i*10,100+i*10,12);
        std::this_thread::sleep_for(std::chrono::nanoseconds(300));
    }
}
//store file
//this will not close application window and exit.
void OfficeControl::GeneralControl::store()
{

}
//exit application without save.
void OfficeControl::GeneralControl::close_app()
{
    Reference <XCloseable> xCloseable(xComponent,UNO_QUERY_THROW);
    if(!xCloseable.is())
    {
        std::cout<<"xCloseable NULL:"<<std::strerror(errno)<<std::endl;
        //return 1;
    }
    else{
        auto currenttime = std::chrono::high_resolution_clock::now();
        //double duration =  std::chrono::duration_cast<std::chrono::microseconds>(currenttime-begintime).count();
        //std::cout<<duration/1000000<<" | "<<"Going to close ..."<<std::endl;
    }

    xCloseable->close(true);
}
