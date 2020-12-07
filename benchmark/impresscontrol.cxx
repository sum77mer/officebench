#include "officecontrol.h"

OfficeControl::ImpressControl::ImpressControl(int width,int height)
{
    desktopWidth = width;
    desktopHeight = height;
}
void OfficeControl::ImpressControl::set_blank()
{
    file = OUString::createFromAscii("./testfile/blank.odp");
}
void OfficeControl::ImpressControl::set_2M()
{
    file = OUString::createFromAscii("./testfile/2M.odp");
}
void OfficeControl::ImpressControl::set_5M()
{
    file = OUString::createFromAscii("./testfile/5M.odp");
}
void OfficeControl::ImpressControl::set_10M()
{
    file = OUString::createFromAscii("./testfile/10M.odp");
}
void OfficeControl::ImpressControl::set_50M()
{
    file = OUString::createFromAscii("./testfile/50M.odp");
}
void OfficeControl::ImpressControl::set_500K()
{
    file = OUString::createFromAscii("./testfile/500k.odp");
}
double OfficeControl::ImpressControl::start_app()
{
    auto begintime = std::chrono::high_resolution_clock::now();
    Reference <XComponentContext> theContext(::cppu::bootstrap());
    if(!theContext.is())
    {
        std::cout<<"xComponentContext NULL:"<<std::strerror(errno)<<std::endl;
        //return 1;
    }
    xComponentContext = theContext;
    Reference <XMultiComponentFactory> xServiceManager(xComponentContext->getServiceManager());
    if(!xServiceManager.is())
    {
        std::cout<<"xServiceManager NULL:"<<std::strerror(errno)<<std::endl;
        //return 1;
    }
    xInterface = xServiceManager->createInstanceWithContext(OUString::createFromAscii("com.sun.star.frame.Desktop"),xComponentContext);
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
    OUString appname = OUString::createFromAscii("private:factory/simpress");
    xComponent = xComponentLoader->loadComponentFromURL(appname,
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
        //auto currenttime = std::chrono::high_resolution_clock::now();
        //double duration =  std::chrono::duration_cast<std::chrono::microseconds>(currenttime-begintime).count();
        //std::cout<<duration/1000000<<" | "<<"Going to resize ..."<<std::endl;
    }
    xWindow->setPosSize(0,0,desktopWidth*0.6,desktopHeight*0.6,12);
    auto endtime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
double OfficeControl::ImpressControl::open_doc()
{
    auto begintime = std::chrono::high_resolution_clock::now();
    Reference <XComponentContext> theContext(::cppu::bootstrap());
    if(!theContext.is())
    {
        std::cout<<"xComponentContext NULL:"<<std::strerror(errno)<<std::endl;
        //return 1;
    }
    xComponentContext = theContext;
    Reference <XMultiComponentFactory> xServiceManager(xComponentContext->getServiceManager());
    if(!xServiceManager.is())
    {
        std::cout<<"xServiceManager NULL:"<<std::strerror(errno)<<std::endl;
        //return 1;
    }
    xInterface = xServiceManager->createInstanceWithContext(OUString::createFromAscii("com.sun.star.frame.Desktop"),xComponentContext);
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
    
    OUString sAbsoluteDocUrl,sWorkingDir,sDocPathUrl,sDocUrl;
    sDocUrl = file;
    sal_Int32 nCount = (sal_Int32)rtl_getAppCommandArgCount();
    if(nCount == 1)
    {
        rtl_getAppCommandArg(0,&sDocUrl.pData);
        //auto currenttime = std::chrono::high_resolution_clock::now();
        //double duration =  std::chrono::duration_cast<std::chrono::microseconds>(currenttime-begintime).count();
        //std::cout<<duration/1000000<<" | "<<"User specify File ..."<<std::endl;
    }
    osl_getProcessWorkingDir(&sWorkingDir.pData);
    osl::FileBase::getFileURLFromSystemPath(sDocUrl,sDocPathUrl);
    osl::FileBase::getAbsoluteFileURL(sWorkingDir,sDocPathUrl,sAbsoluteDocUrl);
    xComponent = xComponentLoader->loadComponentFromURL(sAbsoluteDocUrl,
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
        //auto currenttime = std::chrono::high_resolution_clock::now();
        //double duration =  std::chrono::duration_cast<std::chrono::microseconds>(currenttime-begintime).count();
        //std::cout<<duration/1000000<<" | "<<"Going to resize ..."<<std::endl;
    }
    xWindow->setPosSize(0,0,desktopWidth*0.6,desktopHeight*0.6,12);
    auto endtime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
double OfficeControl::ImpressControl::resize()
{
    auto begintime = std::chrono::high_resolution_clock::now();
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
        //auto currenttime = std::chrono::high_resolution_clock::now();
        //double duration =  std::chrono::duration_cast<std::chrono::microseconds>(currenttime-begintime).count();
        //std::cout<<duration/1000000<<" | "<<"Going to resize ..."<<std::endl;
    }
    auto posSize = xWindow->getPosSize();
    std::cout<<"before resize Width*Height:"<<posSize.Width<<"*"<<posSize.Height<<std::endl;
    auto current_posSize = xWindow->getPosSize();
    int wait_loop = 0;
    for(;;)
    {
        //sleep(1);
        std::this_thread::sleep_for(std::chrono::nanoseconds(10000000));
        current_posSize = xWindow->getPosSize();
        std::cout<<"wait loop:"<<wait_loop<<std::endl;
        std::cout<<"lastWidth:"<<posSize.Width<<" lastHeight:"<<posSize.Height<<std::endl;
        std::cout<<" currentWidth:"<<current_posSize.Width<<" currentHeight:"<<current_posSize.Height<<std::endl;
        if(posSize.Width == current_posSize.Width and posSize.Height == current_posSize.Height)
            break;
        posSize = current_posSize;
        wait_loop++;
    }
    std::cout<<"going to resize ... "<<std::endl;
    auto size = xWindow->getPosSize();
    Rectangle curSize;
    curSize.Width = 100;
    curSize.Height = 100;
    xWindow->setPosSize(0,0,curSize.Width,curSize.Height,15);
    std::this_thread::sleep_for(std::chrono::nanoseconds(500));
    while(curSize.Width<size.Width or curSize.Height<size.Height)
    {
        curSize.Width+=10;
        curSize.Height+=10;
        xWindow->setPosSize(0,0,curSize.Width,curSize.Height,12);
        std::this_thread::sleep_for(std::chrono::nanoseconds(300));
    }
    curSize = xWindow->getPosSize();
    std::cout<<"after resize Width*Height:"<<curSize.Width<<"*"<<curSize.Height<<std::endl;
    auto endtime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
double OfficeControl::ImpressControl::goto_slide()
{
    auto begintime = std::chrono::high_resolution_clock::now();
    Reference <XDrawPagesSupplier> xDrawPagesSupplier(xComponent, UNO_QUERY_THROW);
    if(!xDrawPagesSupplier.is())
    {
        std::cout<<"xDrawPagesSupplier Null ... "<<std::strerror(errno)<<std::endl;
        return 0;
    }

    Reference<XDrawPages > xDrawPages = xDrawPagesSupplier->getDrawPages();
    if(!xDrawPages.is())
    {
        std::cout<<"xDrawPages NULL ... "<<std::strerror(errno)<<std::endl;
        return 0;
    }
    auto count = xDrawPages->getCount();
    std::cout<<"slides count:"<<count<<std::endl;

    dispatchCmd(".uno:FirstPage");
    for(int i=0;i<5;i++)
    {
        dispatchCmd(".uno:NextPage");
        //std::this_thread::sleep_for(std::chrono::nanoseconds(600));
        sleep(1);
    }

    auto endtime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
void OfficeControl::ImpressControl::setFile(std::string name)
{
    
    int length = name.size();
    const char* c = name.c_str();
    sal_Unicode sal_uni[length];// = malloc(sizeof(sal_Unicode*)*length);
    std::copy(c,c+length,sal_uni);
    std::cout<<"bug not happen yet ..."<<std::endl;
    file = OUString(sal_uni,length);

    rtl::OString o = OUStringToOString(file,RTL_TEXTENCODING_ASCII_US);
	char *a_char = o.pData->buffer;

    std::cout<<"ImpressControl::setFile, filename:"<<std::string(a_char)<<std::endl;
}
double OfficeControl::ImpressControl::dispatchCmd(OUString cmd)
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
    Reference <XMultiServiceFactory> xMSF(xComponent,UNO_QUERY);
    //

    Reference <XMultiComponentFactory> xServiceManager(xComponentContext->getServiceManager());
    if(!xServiceManager.is())
    {
        std::cout<<"xServiceManager NULL:"<<std::strerror(errno)<<std::endl;
        //return 1;
    }
    Reference <XInterface> theInterface = xServiceManager->createInstanceWithContext(OUString::createFromAscii("com.sun.star.frame.DispatchHelper"),xComponentContext);
    Reference <XDispatchHelper> helper(theInterface,UNO_QUERY_THROW);

    Reference <XDispatchProvider> provider(xFrame,UNO_QUERY_THROW);
    Sequence<PropertyValue> props;
    helper->executeDispatch(provider,cmd,"",0,props);
}
double OfficeControl::ImpressControl::dispatchCmd(OUString cmd, Sequence<PropertyValue> props)
{
    auto begintime = std::chrono::high_resolution_clock::now();
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
    Reference <XMultiServiceFactory> xMSF(xComponent,UNO_QUERY);
    //
    std::cout<<"bug not happen yet ... "<<std::endl;
    Reference <XMultiComponentFactory> xServiceManager(xComponentContext->getServiceManager());
    if(!xServiceManager.is())
    {
        std::cout<<"xServiceManager NULL:"<<std::strerror(errno)<<std::endl;
        //return 1;
    }
    Reference <XInterface> theInterface = xServiceManager->createInstanceWithContext(OUString::createFromAscii("com.sun.star.frame.DispatchHelper"),xComponentContext);
    Reference <XDispatchHelper> helper(theInterface,UNO_QUERY_THROW);
    Reference <XDispatchProvider> provider(xFrame,UNO_QUERY_THROW);
    helper->executeDispatch(provider,cmd,"",0,props);
    auto endtime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
double OfficeControl::ImpressControl::create_new_slide()
{
    auto begintime = std::chrono::high_resolution_clock::now();
    Reference <XDrawPagesSupplier> xDrawPagesSupplier(xComponent, UNO_QUERY_THROW);
    if(!xDrawPagesSupplier.is())
    {
        std::cout<<"xDrawPagesSupplier Null ... "<<std::strerror(errno)<<std::endl;
        return 0;
    }

    Reference<XDrawPages > xDrawPages = xDrawPagesSupplier->getDrawPages();
    if(!xDrawPages.is())
    {
        std::cout<<"xDrawPages NULL ... "<<std::strerror(errno)<<std::endl;
        return 0;
    }
    Reference <XDrawPage > xDrawPage = xDrawPages->insertNewByIndex(0); 
    auto endtime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
//bug: fileURL, x,y, width,height
double OfficeControl::ImpressControl::insert_image()
{
    auto begintime = std::chrono::high_resolution_clock::now();
    dispatchCmd(".uno:FirstPage");
    dispatchCmd(".uno:NextPage");

    //get second page, to insert image into.
    Reference <XDrawPagesSupplier> xDrawPagesSupplier(xComponent, UNO_QUERY_THROW);
    if(!xDrawPagesSupplier.is())
    {
        std::cout<<"xDrawPagesSupplier Null ... "<<std::strerror(errno)<<std::endl;
        return 0;
    }

    Reference<XDrawPages > xDrawPages = xDrawPagesSupplier->getDrawPages();
    if(!xDrawPages.is())
    {
        std::cout<<"xDrawPages NULL ... "<<std::strerror(errno)<<std::endl;
        return 0;
    }
    Reference <XDrawPage > xDrawPage(xDrawPages->getByIndex(1), UNO_QUERY_THROW); 
    if(!xDrawPage.is())
    {
        std::cout<<"xDrawPage NULL ... "<<std::strerror(errno)<<std::endl;
        return 0;
    }
    Reference <XPropertySet > xSlideProps(xDrawPage,UNO_QUERY_THROW);
    long width;
    xSlideProps->getPropertyValue("Width") >>= width;
    long height;
    xSlideProps->getPropertyValue("Height") >>= height;
    std::cout<<"slide's Width*Height: "<<width<<"*"<<height<<std::endl;

    //create shape
    Reference < XMultiServiceFactory > xFactory(xComponent, UNO_QUERY);
    Reference < XShape > xGraphicShape(xFactory->createInstance("com.sun.star.drawing.GraphicObjectShape"), UNO_QUERY_THROW);
    xGraphicShape->setPosition(Point(width*0.5, height*0.6));
    xGraphicShape->setSize(Size(width-width*0.5, height-height*0.6));
    
    if(!xGraphicShape.is())
    {
        std::cout<<"xGraphicShape NULL ... "<<std::strerror(errno)<<std::endl;
        //return;
    }
    //get bitmap
    OUString sAbsoluteDocUrl,sWorkingDir,sDocPathUrl,sDocUrl;
    sDocUrl = OUString::createFromAscii("./image/skinner.png");
    osl_getProcessWorkingDir(&sWorkingDir.pData);
    osl::FileBase::getFileURLFromSystemPath(sDocUrl,sDocPathUrl);
    osl::FileBase::getAbsoluteFileURL(sWorkingDir,sDocPathUrl,sAbsoluteDocUrl);

    //set bitmap as shape's property
    Reference < XPropertySet > xPropertySet(xGraphicShape,UNO_QUERY);
    xPropertySet->setPropertyValue(OUString::createFromAscii("GraphicURL"),makeAny(sAbsoluteDocUrl));

    //add shape
    xDrawPage->add(xGraphicShape);
    
    //set shape
    /*

    */
    auto endtime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}

double OfficeControl::ImpressControl::cut_image()
{
    auto begintime = std::chrono::high_resolution_clock::now();
    /*
    Any bitmapMode = xPropertySet->getPropertyValue(OUString::createFromAscii("FillBitmapMode"));
    BitmapMode mode;
    bitmapMode >>= mode;
    if(mode == BitmapMode_REPEAT)
    {
        std::cout<<"FillBitmapMode: REPEAT"<<std::endl;
    }        
    else if(mode == BitmapMode_STRETCH)
    {
        std::cout<<"FillBitmapMode: REPEAT"<<std::endl;
    }
    else if(mode == BitmapMode_NO_REPEAT)
    {
        std::cout<<"FillBitmapMode: REPEAT"<<std::endl;
    }
    else{
       std::cout<<"FillBitmapMode: UNKNOWN"<<std::endl;
    }
    
    GraphicCrop cropImage;
    xPropertySet->getPropertyValue(OUString::createFromAscii("GraphicCrop")) >>= cropImage;
    std::cout<<"GraphicCrop Top:"<<cropImage.Top
    <<" Bottom:"<<cropImage.Bottom
    <<" Left:"<<cropImage.Left
    <<" Right:"<<cropImage.Right<<std::endl;
    cropImage.Top = (height-height*0.6)*0.5;
    cropImage.Right = (width-width*0.5)*0.5;
    std::cout<<"GraphicCrop Top:"<<cropImage.Top
    <<" Bottom:"<<cropImage.Bottom
    <<" Left:"<<cropImage.Left
    <<" Right:"<<cropImage.Right<<std::endl;
    xPropertySet->setPropertyValue(OUString::createFromAscii("cvvfdsvda"),makeAny(cropImage.Top));
    */
    auto endtime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
double OfficeControl::ImpressControl::insert_text()
{
    auto begintime = std::chrono::high_resolution_clock::now();
    Reference <XDrawPagesSupplier> xDrawPagesSupplier(xComponent, UNO_QUERY_THROW);
    if(!xDrawPagesSupplier.is())
    {
        std::cout<<"xDrawPagesSupplier Null ... "<<std::strerror(errno)<<std::endl;
        return 0;
    }

    Reference<XDrawPages > xDrawPages = xDrawPagesSupplier->getDrawPages();
    if(!xDrawPages.is())
    {
        std::cout<<"xDrawPages NULL ... "<<std::strerror(errno)<<std::endl;
        return 0;
    }
    Reference <XDrawPage > xDrawPage(xDrawPages->getByIndex(1), UNO_QUERY_THROW); 
    if(!xDrawPage.is())
    {
        std::cout<<"xDrawPage NULL ... "<<std::strerror(errno)<<std::endl;
        return 0;
    }
    Reference < XMultiServiceFactory > xFactory(xComponent, UNO_QUERY);
    Reference < XShape > titleShape(xFactory->createInstance("com.sun.star.presentation.TitleTextShape"), UNO_QUERY_THROW);

    xDrawPage->add(titleShape);

    Reference < XText > titleText(titleShape,UNO_QUERY_THROW);
    titleText->setString(OUString::createFromAscii("Agenda"));

    auto endtime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}

double OfficeControl::ImpressControl::save()
{
    auto begintime = std::chrono::high_resolution_clock::now();
    Reference <XStorable> xStorable(xComponent, UNO_QUERY_THROW);
	if(!xStorable.is())
	{
		std::cout<<"xStorable NULL:"<<std::strerror(errno)<<std::endl;
		//return 1;
	}
	else
	{
        xStorable->store();
    }
    auto endtime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}

double OfficeControl::ImpressControl::save_with_new_name()
{
    auto begintime = std::chrono::high_resolution_clock::now();
    Reference <XStorable> xStorable(xComponent, UNO_QUERY_THROW);
	if(!xStorable.is())
	{
		std::cout<<"xStorable NULL:"<<std::strerror(errno)<<std::endl;
		//return 1;
	}
	else
	{
        OUString sAbsoluteDocUrl,sWorkingDir,sDocPathUrl,sDocUrl;
        sDocUrl = OUString::createFromAscii("./save_as/impress_save_as");
        osl_getProcessWorkingDir(&sWorkingDir.pData);
		osl::FileBase::getFileURLFromSystemPath(sDocUrl,sDocPathUrl);
		osl::FileBase::getAbsoluteFileURL(sWorkingDir,sDocPathUrl,sAbsoluteDocUrl);
		Sequence<PropertyValue> storeProps(1);
		storeProps[0].Name = OUString::createFromAscii("FilterName");
        storeProps[0].Value <<= OUString::createFromAscii("impress8");
		xStorable->storeAsURL(sAbsoluteDocUrl,storeProps);
		
		rtl::OString o = OUStringToOString(sDocUrl,RTL_TEXTENCODING_ASCII_US);
		char *c = o.pData->buffer;
		std::cout<<"New Location: "<<std::string(c)<<std::endl;
	}
    auto endtime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}

double OfficeControl::ImpressControl::save_as_PDF()
{
    auto begintime = std::chrono::high_resolution_clock::now();
    Reference <XStorable> xStorable(xComponent, UNO_QUERY_THROW);
    std::cout<<"bug not happended yet ..."<<std::endl;
	if(!xStorable.is())
	{
		std::cout<<"xStorable NULL:"<<std::strerror(errno)<<std::endl;
		//return 1;
	}
	else
	{
        OUString sWorkingDir,sDocPathUrl,sAbsoluteDocUrl;
        OUString storeUrl = OUString::createFromAscii("./save_as/save_as_PDF");
		osl::FileBase::getFileURLFromSystemPath(storeUrl,sDocPathUrl);
		osl::FileBase::getAbsoluteFileURL(sWorkingDir,sDocPathUrl,sAbsoluteDocUrl);
		Sequence<PropertyValue> storeProps(1);
		storeProps[0].Name = OUString::createFromAscii("FilterName");
        storeProps[0].Value <<= OUString::createFromAscii("impress8_draw");//impress_pdf_Export
            std::cout<<"bug not happended yet ..."<<std::endl;
		xStorable->storeAsURL(sAbsoluteDocUrl,storeProps);
		
		storeUrl = xStorable->getLocation();
		rtl::OString o = OUStringToOString(storeUrl,RTL_TEXTENCODING_ASCII_US);
		char *c = o.pData->buffer;
		std::cout<<"New Location: "<<std::string(c)<<std::endl;
		
		//auto currenttime = std::chrono::high_resolution_clock::now();
		//double duration = std::chrono::duration_cast<std::chrono::microseconds>(currenttime-begintime).count();
		//std::cout<<duration/1000000<<" | "<<"Store as finish ..."<<std::endl;
	}
    //
    auto endtime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
void OfficeControl::ImpressControl::getFilterName()
{
    std::cout<<"bug not happen yet ... "<<std::endl;
    Reference <XMultiComponentFactory> xServiceManager(xComponentContext->getServiceManager());
    if(!xServiceManager.is())
    {
        std::cout<<"xServiceManager NULL:"<<std::strerror(errno)<<std::endl;
        //return 1;
    }
    std::cout<<"bug not happen yet ... "<<std::endl;
    Reference <XNameAccess> na(xServiceManager->createInstanceWithContext(OUString::createFromAscii("com.sun.star.document.FilterFactory"),xComponentContext),UNO_QUERY_THROW);
    auto names = na->getElementNames();            
    for(int i=0;i<names.getLength();i++)
    {
        rtl::OString o = OUStringToOString(names[i],RTL_TEXTENCODING_ASCII_US);
		char *c = o.pData->buffer;
        std::cout<<std::string(c)<<std::endl;
    }
}
double OfficeControl::ImpressControl::close()
{
    auto begintime = std::chrono::high_resolution_clock::now();
    Reference <XCloseable> xCloseable(xComponent,UNO_QUERY_THROW);
    if(!xCloseable.is())
    {
        std::cout<<"xCloseable NULL:"<<std::strerror(errno)<<std::endl;
        //return 1;
    }
    else{
        //auto currenttime = std::chrono::high_resolution_clock::now();
        //double duration =  std::chrono::duration_cast<std::chrono::microseconds>(currenttime-begintime).count();
        //std::cout<<duration/1000000<<" | "<<"Going to close ..."<<std::endl;
    }
    xCloseable->close(true);

    auto endtime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
