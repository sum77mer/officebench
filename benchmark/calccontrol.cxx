#include "officecontrol.h"

OfficeControl::CalcControl::CalcControl(int width,int height)
{
    desktopWidth = width;
    desktopHeight = height;
}
void OfficeControl::CalcControl::set_blank()
{
    file = OUString::createFromAscii("./testfile/blank.ods");
}
void OfficeControl::CalcControl::set_2M()
{
    file = OUString::createFromAscii("./testfile/2M.ods");
}
void OfficeControl::CalcControl::set_5M()
{
    file = OUString::createFromAscii("./testfile/5M.ods");
}
void OfficeControl::CalcControl::set_10M()
{
    file = OUString::createFromAscii("./testfile/10M.ods");
}
void OfficeControl::CalcControl::set_50M()
{
    file = OUString::createFromAscii("./testfile/50M.ods");
}
void OfficeControl::CalcControl::set_500K()
{
    file = OUString::createFromAscii("./testfile/500k.ods");
}
double OfficeControl::CalcControl::start_app()
{
    auto begintime = std::chrono::high_resolution_clock::now();
    Reference <XComponentContext> theContext(::cppu::bootstrap());
    if(!xComponentContext.is())
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
    OUString appname = OUString::createFromAscii("private:factory/scalc");
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
double OfficeControl::CalcControl::open_doc()
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
void OfficeControl::CalcControl::setFile(std::string name)
{
    
    int length = name.size();
    const char* c = name.c_str();
    sal_Unicode sal_uni[length];// = malloc(sizeof(sal_Unicode*)*length);
    std::copy(c,c+length,sal_uni);
    std::cout<<"bug not happen yet ..."<<std::endl;
    file = OUString(sal_uni,length);

    rtl::OString o = OUStringToOString(file,RTL_TEXTENCODING_ASCII_US);
	char *a_char = o.pData->buffer;

    std::cout<<"CalcControl::setFile, filename:"<<std::string(a_char)<<std::endl;
}
double OfficeControl::CalcControl::input_data()
{
    auto begintime = std::chrono::high_resolution_clock::now();

    Reference < XSpreadsheetDocument > xSpreadSheetDocument(xComponent,UNO_QUERY_THROW);
    Reference < XSpreadsheets > xSheets = xSpreadSheetDocument->getSheets();
    Reference <XIndexAccess> xSheetsIA(xSheets,UNO_QUERY_THROW);
    long nIndex = 0;
    Reference <XSpreadsheet> xSheet(xSheetsIA->getByIndex(nIndex),UNO_QUERY_THROW);
    //
    OUString rangeName = OUString::createFromAscii("A1:E8");
    Reference <XCellRange> xCellRange = xSheet->getCellRangeByName(rangeName);
    //
    
    Sequence<Sequence < Any > > data;
    data.realloc(8);
    for (sal_Int32 i = 0; i < 8; ++i)
    {
        data[i].realloc(5);
        for (sal_Int32 j = 0; j < 5; ++j)
        {
            Any& aAny = data[i][j];
            double nValue = i + j;
            aAny <<= nValue;
        }
    }
    Reference <XCellRangeData> xCellRangeData(xCellRange,UNO_QUERY_THROW);
    xCellRangeData->setDataArray(data);

    auto endtime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
double OfficeControl::CalcControl::compute_data()
{
    auto begintime = std::chrono::high_resolution_clock::now();
    //Reference < XMultiServiceFactory > xFactory(xComponent, UNO_QUERY);
    Reference <XMultiComponentFactory> xServiceManager(xComponentContext->getServiceManager());
    if(!xServiceManager.is())
    {
        std::cout<<"xServiceManager NULL:"<<std::strerror(errno)<<std::endl;
        //return 1;
    }
    Reference < XInterface > xInterface_function = xServiceManager->createInstanceWithContext(OUString::createFromAscii("com.sun.star.sheet.FunctionAccess"),xComponentContext);
    std::cout<<"bug not happening yet ..."<<std::endl;
    Reference < XFunctionAccess > xFunctionAccess(xInterface_function,UNO_QUERY_THROW);
    
    Reference < XSpreadsheetDocument > xSpreadSheetDocument(xComponent,UNO_QUERY_THROW);
    Reference < XSpreadsheets > xSheets = xSpreadSheetDocument->getSheets();
    Reference <XIndexAccess> xSheetsIA(xSheets,UNO_QUERY_THROW);
    long nIndex = 0;
    
    Reference <XSpreadsheet> xSheet(xSheetsIA->getByIndex(nIndex),UNO_QUERY_THROW);
    OUString rangeName = OUString::createFromAscii("A1:E8");
    Reference <XCellRange> xCellRange = xSheet->getCellRangeByName(rangeName);
    Reference <XCellRangeData> xCellRangeData(xCellRange,UNO_QUERY_THROW);
    auto data = xCellRangeData->getDataArray();
    Sequence<Sequence < Any > > result;
    
    result.realloc(1);
    result[0].realloc(5);
    sal_Int32 i = 0;
    Sequence<Sequence<Any>> transfer;
    transfer.realloc(5);
    for(sal_Int32 i=0;i<5;i++)
        transfer[i].realloc(8);

    for(sal_Int32 i=0;i<8;i++)
    {
        for(sal_Int32 j=0;j<5;j++)
        {
            transfer[j][i] = data[i][j];
        }
    }
    for(sal_Int32 i=0;i<5;i++)
    {
        Sequence<Any> args = transfer[i];
        Any val = xFunctionAccess->callFunction(OUString::createFromAscii("AVERAGE"),args);
        result[0][i] = val;
    }
    OUString result_rangeName = OUString::createFromAscii("A9:E9");
    xCellRange = xSheet->getCellRangeByName(result_rangeName);
    Reference <XCellRangeData> xCellRangeData_result(xCellRange,UNO_QUERY_THROW);
    xCellRangeData_result->setDataArray(result);
    auto endtime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
double OfficeControl::CalcControl::generate_chart()
{
    auto begintime = std::chrono::high_resolution_clock::now();
    //1. get the sheet
    Reference < XSpreadsheetDocument > xSpreadSheetDocument(xComponent,UNO_QUERY_THROW);
    Reference < XSpreadsheets > xSheets = xSpreadSheetDocument->getSheets();
    Reference <XIndexAccess> xIndexAccess(xSheets,UNO_QUERY_THROW);
    long nIndex = 0;
    Reference <XSpreadsheet> xSheet(xIndexAccess->getByIndex(nIndex),UNO_QUERY_THROW);
    //2. query for XTableChartsSupplier
    Reference <XTableChartsSupplier> xTableChartsSupplier(xSheet,UNO_QUERY_THROW);
    Reference <XTableCharts> xTableCharts = xTableChartsSupplier->getCharts();
    OUString chartName = OUString::createFromAscii("theChart");
    //rectangle
    Rectangle rect;
    rect.X = 1000;
    rect.Y = 1000;
    rect.Width = 15000;
    rect.Height = 9271;
    //get the data to transfer into chart
    CellRangeAddress address;
    OUString rangeName = OUString::createFromAscii("A9:E9");
    Reference <XCellRange> xCellRange = xSheet->getCellRangeByName(rangeName);
    Sequence <CellRangeAddress> addrs;

    //3. add chart to sheet
    xTableCharts->addNewByName(chartName,rect,addrs,true,true);
    //get chartdoc
    Reference <XTableChart> xTableChart;
    Reference <XNameAccess> xNameAccess(xTableCharts,UNO_QUERY_THROW);
    xNameAccess->getByName(chartName) >>= xTableChart;
    Reference <XEmbeddedObjectSupplier> eos(xTableChart,UNO_QUERY_THROW);
    Reference <XChartDocument> xChartDoc(eos,UNO_QUERY_THROW);
    auto endtime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}

double OfficeControl::CalcControl::save()
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
double OfficeControl::CalcControl::save_with_new_name()
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
        sDocUrl = OUString::createFromAscii("./save_as/calc_save_as");
        osl_getProcessWorkingDir(&sWorkingDir.pData);
		osl::FileBase::getFileURLFromSystemPath(sDocUrl,sDocPathUrl);
		osl::FileBase::getAbsoluteFileURL(sWorkingDir,sDocPathUrl,sAbsoluteDocUrl);

		Sequence<PropertyValue> storeProps(1);
		storeProps[0].Name = OUString::createFromAscii("FilterName");
		storeProps[0].Value <<= OUString::createFromAscii("calc8");
		xStorable->storeAsURL(sAbsoluteDocUrl,storeProps);

		rtl::OString o = OUStringToOString(sDocUrl,RTL_TEXTENCODING_ASCII_US);
		char *c = o.pData->buffer;
		std::cout<<"New Location: "<<std::string(c)<<std::endl;
		
		//auto currenttime = std::chrono::high_resolution_clock::now();
		//double duration = std::chrono::duration_cast<std::chrono::microseconds>(currenttime-begintime).count();
		//std::cout<<duration/1000000<<" | "<<"Store as finish ..."<<std::endl;
	}
    auto endtime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
}
double OfficeControl::CalcControl::close()
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
