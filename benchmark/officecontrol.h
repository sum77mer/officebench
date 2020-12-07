#ifndef OFFICECONTROL_H
#define OFFICECONTROL_H

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
#include <com/sun/star/frame/XStorable.hpp>
#include <com/sun/star/text/XTextDocument.hpp>
#include <com/sun/star/text/XText.hpp>
#include <com/sun/star/text/XTextCursor.hpp>
#include <com/sun/star/text/XWordCursor.hpp>

//draw line/rectangle in text
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/drawing/XShape.hpp>
#include <com/sun/star/drawing/XDrawPagesSupplier.hpp>
#include <com/sun/star/drawing/XDrawPage.hpp>
using namespace com::sun::star::drawing;

// copy & paste
using namespace com::sun::star::text;
#include <com/sun/star/text/XTextContent.hpp>
#include <com/sun/star/text/XParagraphCursor.hpp>

// copy & paste text content
#include <com/sun/star/text/XTextField.hpp>
#include <com/sun/star/text/XTextTable.hpp>
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

#include <com/sun/star/awt/FontWeight.hpp>
using namespace com::sun::star::awt::FontWeight;
#include <com/sun/star/awt/XWindow.hpp>
#include <thread>//sleep
#include <chrono>//nanosecond
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/times.h>
//impressControl
#include <com/sun/star/container/XNameContainer.hpp>
using namespace com::sun::star::container;

//cut image
#include <com/sun/star/text/GraphicCrop.hpp>
#include <com/sun/star/drawing/BitmapMode.hpp>


//excel
#include <com/sun/star/sheet/XSpreadsheetDocument.hpp>
using namespace com::sun::star::sheet;
#include <com/sun/star/sheet/XSpreadsheets.hpp>
#include <com/sun/star/sheet/XSpreadsheet.hpp>
#include <com/sun/star/container/XIndexAccess.hpp>
#include <com/sun/star/sheet/XCellRangeData.hpp>
#include <com/sun/star/table/XCellRange.hpp>
using namespace com::sun::star::table;
#include <com/sun/star/sheet/XFunctionAccess.hpp>
#include <com/sun/star/table/XTableChartsSupplier.hpp>
#include <com/sun/star/table/XTableCharts.hpp>
#include <com/sun/star/sheet/XCellRangeAddressable.hpp>
#include <com/sun/star/table/XTableChart.hpp>
#include <com/sun/star/chart2/XChartTypeManager.hpp>
using namespace com::sun::star::chart2;
#include <com/sun/star/document/XEmbeddedObjectSupplier.hpp>
using namespace com::sun::star::document;
#include <com/sun/star/chart2/XChartDocument.hpp>
#include <com/sun/star/chart2/XDiagram.hpp>
#include <com/sun/star/chart2/XChartTypeTemplate.hpp>

#include <com/sun/star/chart2/data/XDataProvider.hpp>
using namespace com::sun::star::chart2::data;
#include <com/sun/star/chart2/data/XDataSource.hpp>
//dispatchcmd
#include <com/sun/star/frame/XDispatchHelper.hpp>
#include <com/sun/star/frame/XDispatchProvider.hpp>

namespace OfficeControl{
    //std::string get_version();
    class GeneralControl
    {
    public:
        GeneralControl();

        //launch libreoffice(soffice?), not libreoffice writer or anything else.
        //inherite class can implemente themself to launch corresponding app
        //can be writer, Calc, Impress, Draw, Math, and Base(if it's installed).
        void start_app();

        //create a new document in an already launched libreoffice
        //can be text document, spreadsheet, presentation, drawing, formula,
        //HTML document, XML form document, labels, business cards, master document, templates.
        void new_doc();

        //open old file in an already launched libreoffice
        //file type can be opened are same with new_doc()
        void open_doc();

        //cloase document without save
        void close_doc();

        //resize window size
        void resize();

        //store file
        //this will not close application window and exit.
        void store();

        //exit application without save.
        void close_app();
        private:
        Reference <XComponent> xComponent = NULL;
    };
    class WriterControl
    {
    public:
        WriterControl(int width,int height);

        void set_blank();
        void set_500K();
        void set_2M();
        void set_5M();
        void set_10M();
        void set_50M();
        //start libreoffice writer
        double start_app();
        //open document
        double open_doc();
        //
        double resize();
        //
        double insert_characters();
        //
        double insert_table();
        //
        double change_font_type();
        //
        double change_font_size();
        //copy
        double copy_text();
        double paste_text();

        //copy text content, contain picture or something,
        //other than just string
        double copy_content();

        double draw_line();
        double draw_rectangle();
        double save();
        double save_as_PDF();//empty
        double save_with_new_name();
        double close();
        void setFile(std::string);
        private:
        void dispatchCmd(OUString cmd);

    private:
        Reference <XComponent> xComponent = NULL;
        Reference <XInterface> xInterface = NULL;
        Reference <XComponentContext> xComponentContext = NULL;
        OUString file;
        int desktopWidth;
        int desktopHeight;
    };
    class CalcControl
    {
    public:
        CalcControl(int width,int height);

        void set_blank();
        void set_500K();
        void set_2M();
        void set_5M();
        void set_10M();
        void set_50M();

        double start_app();
        double open_doc();
        double input_data();//empty
        double compute_data();//empty
        double generate_chart();//empty
        double save();
        double save_with_new_name();

        double close();
        void setFile(std::string);
        private:
        //OUString columnNumberStr(int nColumn);
        //private data
        Reference <XComponent> xComponent = NULL;
        Reference <XInterface> xInterface = NULL;
        Reference <XComponentContext> xComponentContext = NULL;
        OUString file;
        int desktopWidth;
        int desktopHeight;
    };
    class ImpressControl
    {
    public:
        ImpressControl(int width,int height);

        void set_blank();
        void set_500K();
        void set_2M();
        void set_5M();
        void set_10M();
        void set_50M();

        double start_app();
        double open_doc();
        double resize();
        double goto_slide();
        double create_new_slide();
        double insert_image();
        double cut_image();//empty
        double insert_text();
        double save_with_new_name();
        double save_as_PDF();
        double save();
        double close();
        void setFile(std::string);
        void getFilterName();
        private:
        double dispatchCmd(OUString cmd);
        double dispatchCmd(OUString cmd, Sequence<PropertyValue> props);
        //.uno:LeftPaneImpress
    private:
        Reference <XComponent> xComponent = NULL;
        Reference <XInterface> xInterface = NULL;
        Reference <XComponentContext> xComponentContext = NULL;
        OUString file;
        int desktopWidth;
        int desktopHeight;
    };

}
#endif
/*
writer_globaldocument_StarOffice_XML_Writer_GlobalDocument
impress_StarOffice_XML_Impress_Template
Impress MS PowerPoint 2007 XML AutoPlay
OpenDocument Presentation Flat XML
Impress MS PowerPoint 2007 XML VBA
draw_StarOffice_XML_Draw_Template
OpenDocument Spreadsheet Flat XML
writer_web_StarOffice_XML_Writer
writer_globaldocument_pdf_Export
Impress Office Open XML Template
CGM - Computer Graphics Metafile
Impress MS PowerPoint 2007 XML
Office Open XML Text Template
MS Excel 4.0 Vorlage/Template
EPS - Encapsulated PostScript
calc_StarOffice_XML_Calc_Template
MS Excel 95 Vorlage/Template
Text - txt - csv (StarCalc)
Rich Text Format (StarCalc)
Corel Presentation Exchange
writerweb8_writer_template
OpenDocument Text Flat XML
GIF - Graphics Interchange
Calc MS Excel 2007 VBA XML
calc_pdf_addstream_import
WMF - MS Windows Metafile
MS Word 2007 XML Template
MS PowerPoint 97 AutoPlay
EMF - MS Windows Metafile
draw_PCD_Photo_CD_Base16
StarOffice XML (Impress)
MS PowerPoint 97 Vorlage
StarOffice_Presentation
StarOffice XML (Writer)
MS Excel 2003 XML Orcus
Impress Office Open XML
writerglobal8_template
draw_PCD_Photo_CD_Base
TGA - Truevision TARGA
StarOffice_Spreadsheet
writer_pdf_addstream_import
PCX - Zsoft Paintbrush
writer_web_png_Export
writer_web_pdf_Export
Text (StarWriter/Web)
StarOffice XML (Draw)
PSD - Adobe Photoshop
PBM - Portable Bitmap
impress_flash_Export
TIF - Tag Image File
RAS - Sun Rasterfile
DXF - AutoCAD Interchange
MS Word 2007 XML VBA
Calc Office Open XML
Impress Office Open XML AutoPlay
Gnumeric Spreadsheet
Claris_Resolve_Calc
writerglobal8_HTML
Text (encoded) (StarWriter/Web)
writer_layout_dump
impress_wmf_Export
OpenDocument Drawing Flat XML
impress_tif_Export
impress_svg_Export
impress_pdf_Export
SVG - Scalable Vector Graphics Draw
Mac_Works_Calc
WordPerfect
SVG - Scalable Vector Graphics
Office Open XML Text
ADO Rowset XML
SVM - StarView Metafile
PCT - Mac Pict
XPM
PGM - Portable Graymap
WPS_QPro_Calc
MS_Works_Calc
impress_pdf_addstream_import
JPG - JPEG
UOF presentation
StarOffice XML (Calc)
impress8
QXP Document
PowerPoint 3
draw_tif_Export
math_pdf_Export
XHTML Writer File
DocBook File
Freehand Document
MS Excel 4.0
MS Excel 97
impress_gif_Export
writer_web_HTML_help
MacWrite
Lotus
ClarisWorks
draw8
Apple Keynote
Plucker eBook
UOF text
MS Word 95
writer_MIZI_Hwp_97
MS WinWord 6.0
MET - OS/2 Metafile
MathML XML (Math)
impress_StarOffice_XML_Draw
MWAW_Drawing
MWAW_Bitmap
Microsoft Multiplan
EPUB
writerglobal8
Mariner_Write
draw_flash_Export
HTML
math8
impress8_draw
MWAW_Presentation
Palm_Text_Document
MS WinWord 5
HTML (StarCalc)
WriteNow
Text
DosWord
MS Excel 5.0/95 Vorlage/Template
writer8
writer_web_StarOffice_XML_Writer_Web_Template
MS_Works
AbiWord
impress_html_Export
MS Word 97
writerglobal8_writer
Mac_Word
MS Excel 95
MS Word 2007 XML
SYLK
writer_web_jpg_Export
StarOffice XML (Math)
T602Document
MS_Write
chart8
writerweb8_writer
MathType 3.x
ZMF Document
MWAW_Spreadsheet
MOV - MOV
impress_emf_Export
dBase
Calc MS Excel 2007 XML Template
Mac_Works
Calc MS Excel 2007 XML
Text (encoded)
ClarisWorks_Impress
impress_jpg_Export
MWAW_Database
Apple Pages
calc_HTML_WebQuery
Visio Document
impress_png_Export
XHTML Impress File
PalmDoc
draw_gif_Export
WPS_Lotus_Calc
PNG - Portable Network Graphic
ClarisWorks_Draw
Calc MS Excel 2007 Binary
calc8_template
WordPerfect Graphics
StarOffice_Drawing
StarOffice XML (Chart)
draw8_template
BroadBand eBook
Quattro Pro 6.0
draw_eps_Export
UOF spreadsheet
ClarisWorks_Calc
XHTML Calc File
calc_jpg_Export
calc_pdf_Export
draw_PCD_Photo_CD_Base4
FictionBook 2
calc_svg_Export
draw_bmp_Export
writer_globaldocument_StarOffice_XML_Writer
draw_emf_Export
draw_jpg_Export
draw_pdf_Export
draw_pdf_addstream_import
draw_png_Export
draw_pdf_import
writer_jpg_Export
writer_pdf_Export
MS Excel 5.0/95
draw_svg_Export
draw_wmf_Export
writer_StarOffice_XML_Writer_Template
BMP - MS Windows
MS PowerPoint 97
MS Word 2003 XML
Rich Text Format
draw_html_Export
Calc Office Open XML Template
writer8_template
calc_png_Export
HTML (StarWriter)
Impress MS PowerPoint 2007 XML Template
DIF
MS Excel 2003 XML
calc8
StarOffice_Writer
LotusWordPro
impress8_template
Corel Draw Document
Apple Numbers
writer_pdf_import
PPM - Portable Pixelmap
writer_png_Export
MWAW_Text_Document
writer_svg_Export
MS Word 97 Vorlage
MS Excel 97 Vorlage/Template
impress_pdf_import
XHTML Draw File
Publisher Document
PageMaker Document
MS Word 95 Vorlage
impress_bmp_Export
Text (encoded) (StarWriter/GlobalDocument)
XBM - X-Consortium
impress_eps_Export
*/