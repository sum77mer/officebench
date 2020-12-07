#include "officecontrol.h"

OfficeControl::WriterControl::WriterControl(int width,int height)
{
    desktopWidth = width;
    desktopHeight = height;
}
void OfficeControl::WriterControl::setFile(std::string name)
{
    
    int length = name.size();
    const char* c = name.c_str();
    sal_Unicode sal_uni[length];// = malloc(sizeof(sal_Unicode*)*length);
    std::copy(c,c+length,sal_uni);
    std::cout<<"bug not happen yet ..."<<std::endl;
    file = OUString(sal_uni,length);

    rtl::OString o = OUStringToOString(file,RTL_TEXTENCODING_ASCII_US);
	char *a_char = o.pData->buffer;

    std::cout<<"WriterControl::setFile, filename:"<<std::string(a_char)<<std::endl;
}
void OfficeControl::WriterControl::set_blank()
{
    file = OUString::createFromAscii("./testfile/blank.odt");
}
void OfficeControl::WriterControl::set_2M()
{
    file = OUString::createFromAscii("./testfile/2M.odt");
}
void OfficeControl::WriterControl::set_5M()
{
    file = OUString::createFromAscii("./testfile/5M.odt");
}
void OfficeControl::WriterControl::set_10M()
{
    file = OUString::createFromAscii("./testfile/10M.odt");
}
void OfficeControl::WriterControl::set_50M()
{
    file = OUString::createFromAscii("./testfile/50M.odt");
}
void OfficeControl::WriterControl::set_500K()
{
    file = OUString::createFromAscii("./testfile/500k.odt");
}
double OfficeControl::WriterControl::start_app()
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
    OUString appname = OUString::createFromAscii("private:factory/swriter");
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
    std::cout<<"Writer Startup: "<<xWindow->getPosSize().Width<<" * "<<xWindow->getPosSize().Height<<std::endl;
    auto endtime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
double OfficeControl::WriterControl::open_doc()
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

double OfficeControl::WriterControl::resize()
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
            auto endtime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
double OfficeControl::WriterControl::insert_characters()
{//bug: it won't auto scroll when inserting.
auto begintime = std::chrono::high_resolution_clock::now();
    Reference <XTextDocument> xTextDocument(xComponent,UNO_QUERY);
	Reference <XText> xText = xTextDocument->getText();
	Reference <XTextCursor> xTextCursor = xText->createTextCursor();
	Reference <XWordCursor> xWordCursor(xTextCursor,UNO_QUERY_THROW);
    xTextCursor->gotoStart(0);
	for(int i=0;i<100;i++)
	{
		xWordCursor->gotoEndOfWord(0);
		xWordCursor->setString(OUString::createFromAscii("What are you going to do this afternoon? "));
		std::this_thread::sleep_for(std::chrono::nanoseconds(300));
        xTextCursor->gotoStart(0);
	}
        auto endtime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
double OfficeControl::WriterControl::change_font_type()
{
    auto begintime = std::chrono::high_resolution_clock::now();
    Reference <XTextDocument> xTextDocument(xComponent,UNO_QUERY);
	Reference <XText> xText = xTextDocument->getText();
	Reference <XTextCursor> xTextCursor = xText->createTextCursor();
    xTextCursor->gotoStart(0);

	Reference <XWordCursor> xWordCursor(xTextCursor,UNO_QUERY_THROW);
    Reference < XPropertySet > xPropertySet(xWordCursor,UNO_QUERY);
    Any cw;
    cw <<= OUString::createFromAscii("Arial");
    xPropertySet->setPropertyValue(OUString::createFromAscii("CharFontName"),cw);
    xWordCursor->setString(OUString::createFromAscii("This sentence 's font should be Arial. "));

    
	for(int i=0;i<1;i++)
	{
		xWordCursor->setString(OUString::createFromAscii("This sentence 's font should be Arial. "));
		std::this_thread::sleep_for(std::chrono::nanoseconds(300));
        xTextCursor->gotoStart(0);
	}
    auto endtime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
double OfficeControl::WriterControl::change_font_size()
{
    auto begintime = std::chrono::high_resolution_clock::now();
    Reference <XTextDocument> xTextDocument(xComponent,UNO_QUERY);
	Reference <XText> xText = xTextDocument->getText();
	Reference <XTextCursor> xTextCursor = xText->createTextCursor();
    xTextCursor->gotoStart(0);
	Reference <XWordCursor> xWordCursor(xTextCursor,UNO_QUERY_THROW);
    Reference < XPropertySet > xPropertySet(xWordCursor,UNO_QUERY);
    Any cw;
    cw <<= 25;
    xPropertySet->setPropertyValue(OUString::createFromAscii("CharHeight"),cw);
    xWordCursor->setString(OUString::createFromAscii("This sentence's font size should be 25. "));
    
    for(int i=0;i<1;i++)
	{
		xWordCursor->setString(OUString::createFromAscii("This sentence's font size should be 25. "));
		std::this_thread::sleep_for(std::chrono::nanoseconds(300));
        xTextCursor->gotoStart(0);
	}
        auto endtime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}

double OfficeControl::WriterControl::copy_text()
{
    auto begintime = std::chrono::high_resolution_clock::now();
    Reference <XTextDocument> xTextDocument(xComponent,UNO_QUERY_THROW);
    if(!xTextDocument.is())
    {
        std::cout<<"xTextDocument NULL ... "<<std::strerror(errno)<<std::endl;
        return 0;
    }
    Reference <XText> xText = xTextDocument->getText();
        if(!xText.is())
    {
        std::cout<<"xText NULL ... "<<std::strerror(errno)<<std::endl;
        return 0;
    }
    Reference < XTextCursor > xTextCursor = xText->createTextCursor();
        if(!xTextCursor.is())
    {
        std::cout<<"xTextCursor NULL ... "<<std::strerror(errno)<<std::endl;
        return 0;
    }
    xTextCursor->gotoStart(0);
    Reference < XParagraphCursor > xParagraphCursor(xTextCursor,UNO_QUERY);
        if(!xParagraphCursor.is())
    {
        std::cout<<"xParagraphCursor NULL ... "<<std::strerror(errno)<<std::endl;
        return 0;
    }
	for(int i=0;i<2;i++)
		xParagraphCursor->gotoNextParagraph(0);
	for(int i=0;i<4;i++)
		xParagraphCursor->gotoNextParagraph(1);

    Reference < XTextRange > xTextRange(xParagraphCursor,UNO_QUERY);
        if(!xTextRange.is())
    {
        std::cout<<"xParagraphCursor NULL ... "<<std::strerror(errno)<<std::endl;
        return 0;
    }
	OUString content = xTextRange->getString();

    xTextCursor->gotoStart(0);
    xParagraphCursor->setString(content);
        auto endtime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
double OfficeControl::WriterControl::copy_content()
{
    auto begintime = std::chrono::high_resolution_clock::now();
        auto endtime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
//vlck,sse,c5l,powertest1.6,
double OfficeControl::WriterControl::insert_table()
{
    auto begintime = std::chrono::high_resolution_clock::now();
    Reference <XTextDocument> xTextDocument(xComponent,UNO_QUERY_THROW);
    if(!xTextDocument.is())
    {
        std::cout<<"xTextDocument NULL ... "<<std::strerror(errno)<<std::endl;
        return 0;
    }
    Reference <XText> xText = xTextDocument->getText();
        if(!xText.is())
    {
        std::cout<<"xText NULL ... "<<std::strerror(errno)<<std::endl;
        return 0;
    }
    Reference <XMultiServiceFactory> xMSF(xComponent,UNO_QUERY);
    Reference<XTextTable> xTable(xMSF->createInstance("com.sun.star.text.TextTable"),
                                       UNO_QUERY_THROW);
    xTable->initialize(4, 3);
    xText->insertTextContent(xText->getEnd(), xTable, false);
        auto endtime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
double OfficeControl::WriterControl::draw_line()
{
    auto begintime = std::chrono::high_resolution_clock::now();
    //Reference <XTextDocument> xTextDocument(xComponent,UNO_QUERY);
	//Reference <XText> xText = xTextDocument->getText();
    Reference<XMultiServiceFactory> xFactory(xComponent, UNO_QUERY);
    Reference <XShape> xLineShape(xFactory->createInstance("com.sun.star.drawing.LineShape"), UNO_QUERY_THROW);
    xLineShape->setSize(Size(10000, 10000));
    xLineShape->setPosition(Point(1000, 1000));

    Reference<XDrawPagesSupplier> xDrawPagesSupplier(xComponent, UNO_QUERY_THROW);
    Reference<XDrawPage> xDrawPage(xDrawPagesSupplier->getDrawPages()->getByIndex(0),
                                                 UNO_QUERY_THROW);
    xDrawPage->add(xLineShape);

    //Reference <XTextContent> xShapeContent();
    //xText->insertTextContent(xText->getEnd(),xShapeContent, 0);
    auto endtime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
double OfficeControl::WriterControl::draw_rectangle()
{
    auto begintime = std::chrono::high_resolution_clock::now();
    Reference<XMultiServiceFactory> xFactory(xComponent, UNO_QUERY);
    Reference <XShape> xRectShape(xFactory->createInstance("com.sun.star.drawing.RectangleShape"), UNO_QUERY_THROW);
    xRectShape->setSize(Size(10000, 10000));
    xRectShape->setPosition(Point(1000, 1000));
    if(!xRectShape.is())
    {
         std::cout<<"xRectShape NULL ... "<<std::strerror(errno)<<std::endl;
    }
    Reference<XDrawPagesSupplier> xDrawPagesSupplier(xComponent, UNO_QUERY_THROW);
    Reference<XDrawPage> xDrawPage(xDrawPagesSupplier->getDrawPages()->getByIndex(0),
                                                 UNO_QUERY_THROW);
    xDrawPage->add(xRectShape);
        auto endtime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
double OfficeControl::WriterControl::save()
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
double OfficeControl::WriterControl::save_as_PDF()
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
        OUString sWorkingDir,sDocPathUrl,sAbsoluteDocUrl;
        OUString storeUrl = OUString::createFromAscii("./exportPDF/writer_save_as_PDF");
		osl::FileBase::getFileURLFromSystemPath(storeUrl,sDocPathUrl);
		osl::FileBase::getAbsoluteFileURL(sWorkingDir,sDocPathUrl,sAbsoluteDocUrl);

        Sequence<PropertyValue> storeProps(1);
		storeProps[0].Name = OUString::createFromAscii("FilterName");
        storeProps[0].Value <<= Any(OUString::createFromAscii("writer_pdf_Export"));
		xStorable->storeAsURL(sAbsoluteDocUrl,storeProps);
        //xStorable->storeAsURL(sAbsoluteDocUrl,aMediaDescriptor.getAsConstPropertyValueList());
		
		storeUrl = xStorable->getLocation();
		rtl::OString o = OUStringToOString(storeUrl,RTL_TEXTENCODING_ASCII_US);
		char *c = o.pData->buffer;
		std::cout<<"New Location: "<<std::string(c)<<std::endl;
	}
        auto endtime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
void OfficeControl::WriterControl::dispatchCmd(OUString cmd)
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
    Sequence<PropertyValue> props;
    helper->executeDispatch(provider,cmd,"",0,props);
}
double OfficeControl::WriterControl::save_with_new_name()
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
        sDocUrl = OUString::createFromAscii("./save_as/writer_save_as");
        osl_getProcessWorkingDir(&sWorkingDir.pData);
		osl::FileBase::getFileURLFromSystemPath(sDocUrl,sDocPathUrl);
		osl::FileBase::getAbsoluteFileURL(sWorkingDir,sDocPathUrl,sAbsoluteDocUrl);

		Sequence<PropertyValue> storeProps(1);
		storeProps[0].Name = OUString::createFromAscii("FilterName");
        storeProps[0].Value <<= OUString::createFromAscii("MS Word 97");
		xStorable->storeAsURL(sAbsoluteDocUrl,storeProps);
		
		rtl::OString o = OUStringToOString(sDocUrl,RTL_TEXTENCODING_ASCII_US);
		char *c = o.pData->buffer;
		std::cout<<"New Location: "<<std::string(c)<<std::endl;
	}
        auto endtime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
double OfficeControl::WriterControl::close()
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
