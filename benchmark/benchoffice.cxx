#include "benchmark.h"
#include "officecontrol.h"

#include <QRect>
#include <QScreen>
#include <QGuiApplication>

#include <dirent.h>
#include <vector>
#include <fstream>
#include <QDir>

BenchMark::BenchOffice::BenchOffice(QObject *parent,int flag) : QObject(parent)
{
    flag = 0;
    getDesktopScreenResolution(resolution_width,resolution_height);
}
void BenchMark::BenchOffice::getDesktopScreenResolution(int &width,int &height)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    height = screenGeometry.height();
    width = screenGeometry.width();
    //if(DEBUG)
        std::cout<<"Width: "<<width<<" Height:"<<height<<std::endl;
}
void BenchMark::BenchOffice::start_bench(int flag)
{
    std::vector<std::string> filelist;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (testFilePath.c_str())) != NULL) {
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL) {
        printf ("%s\n", ent->d_name);
        std::string fullname = testFilePath+"/"+std::string(ent->d_name);
        filelist.push_back(fullname);
    }
    closedir (dir);
    } else {
    /* could not open directory */
    perror ("");
    //return EXIT_FAILURE;
    }
    for(auto s:filelist)
    {
        if(s.find(".odt") != std::string::npos)
        {
            writerFileList.push_back(s);
            bigFileList.push_back(s);
        }
        else if(s.find(".doc") != std::string::npos)
        {
            writerFileList.push_back(s);
            bigFileList.push_back(s);
        }
        else if(s.find(".wps")!= std::string::npos)
        {
            writerFileList.push_back(s);
            bigFileList.push_back(s);
        }
        else if(s.find(".ods")!=std::string::npos)
        {
            calcFileList.push_back(s);
            bigFileList.push_back(s);
        }
        else if(s.find(".xlsx")!=std::string::npos)
        {
            calcFileList.push_back(s);
            bigFileList.push_back(s);
        }
        else if(s.find(".et")!=std::string::npos)
        {
            calcFileList.push_back(s);
            bigFileList.push_back(s);
        }
        else if(s.find(".ppt")!= std::string::npos)
        {
            impressFileList.push_back(s);
            bigFileList.push_back(s);
        }
        else if(s.find(".odp")!=std::string::npos)
        {
            impressFileList.push_back(s);
            bigFileList.push_back(s);
        }
        else if(s.find(".dps")!=std::string::npos)
        {
            impressFileList.push_back(s);
            bigFileList.push_back(s);
        }
    }
    std::cout<<"going to start bench..."<<std::endl;
    std::cout<<"writer file:"<<std::endl;
    for(auto s:writerFileList)
        std::cout<<s<<std::endl;
    std::cout<<"calc file:"<<std::endl;
    for(auto s:calcFileList)
        std::cout<<s<<std::endl;
    std::cout<<"impress file:"<<std::endl;
    for(auto s:impressFileList)
        std::cout<<s<<std::endl;

    if(flag&0x1)
    {
        int count = writerFileList.size();
        //test each file
        for(int i=0;i<count;i++)
        {
            WriterTime thetime = writer_bench(writerFileList[i]);
            WriterResult result;
            result.name = writerFileList[i];
            result.time = thetime;
            _result.writer.push_back(result);
        }
    }
    if(flag&0x2)
    {
        int count = calcFileList.size();
        for(int i=0;i<count;i++)
        {
            CalcTime thetime = calc_bench(calcFileList[i]);
            CalcResult result;
            result.name = calcFileList[i];
            result.time = thetime;
            _result.calc.push_back(result);
        }
    }
    if(flag&0x4)
    {
        int count = calcFileList.size();
        for(int i=0;i<count;i++)
        {
            ImpressTime thetime = impress_bench(impressFileList[i]);
            ImpressResult result;
            result.name = impressFileList[i];
            result.time = thetime;
            _result.impress.push_back(result);
        }
    }
    if(flag&0x8)
    {
        int count = bigFileList.size();
        for(int i=0;i<count;i++)
        {
            BigFileTime thetime = bigfile_bench(bigFileList[i]);
            BigFileResult result;
            result.name = bigFileList[i];
            result.time = thetime;
            _result.bigFile.push_back(result);
        }
    }
}
void BenchMark::BenchOffice::setTestFilePath(QString path)
{
    testFilePath = path.toUtf8().constData();
    std::cout<<"benchoffice test file path:"<<testFilePath<<std::endl;
}
void BenchMark::BenchOffice::getResult(std::vector<std::string> &itemList,std::vector<double> &scoreList)
{
    if(_result.writer.size()>0)
    {
        double startupScore = 0;
        double resizeScore = 0;
        double changeFontSizeScore = 0;
        double changeFontScore = 0;
        double insertTextScore = 0;
        double copyTextScore = 0;
        double drawLineScore = 0;
        double drawRectangleScore = 0;
        double saveScore = 0;
        double closeScore = 0;
        double totalScore = 0;
        for(auto data:_result.writer)
        {
            for(int i=0;i<TESTTIME;i++)
            {
                startupScore+=data.time.startUp[i];
                resizeScore+=data.time.resize[i];
                changeFontSizeScore+=data.time.changeFontSize[i];
                changeFontScore+=data.time.changeFont[i];
                insertTextScore+=data.time.insertCharacters[i];
                copyTextScore+=data.time.copyText[i];
                drawLineScore+=data.time.drawLine[i];
                drawRectangleScore+=data.time.drawRectangle[i];
                saveScore+=data.time.startUp[i];
                closeScore+=data.time.close[i];
            }
        }
        startupScore /= _result.writer.size()*TESTTIME;
        resizeScore /= _result.writer.size()*TESTTIME;
        changeFontSizeScore /= _result.writer.size()*TESTTIME;
        changeFontScore /= _result.writer.size()*TESTTIME;
        insertTextScore /= _result.writer.size()*TESTTIME;
        copyTextScore /= _result.writer.size()*TESTTIME;
        drawLineScore /= _result.writer.size()*TESTTIME;
        drawRectangleScore /= _result.writer.size()*TESTTIME;
        saveScore /= _result.writer.size()*TESTTIME;
        closeScore /= _result.writer.size()*TESTTIME;
        totalScore = startupScore
                    +resizeScore
                    +changeFontSizeScore
                    +changeFontScore
                    +insertTextScore
                    +copyTextScore
                    +drawLineScore
                    +drawRectangleScore
                    +saveScore
                    +closeScore;
        itemList.push_back(std::string("Writing"));
        scoreList.push_back(totalScore);

        itemList.push_back(std::string("    StartUp"));
        scoreList.push_back(startupScore);

        itemList.push_back(std::string("    Resize"));
        scoreList.push_back(resizeScore);

        itemList.push_back(std::string("    Change Font"));
        scoreList.push_back(changeFontScore);

        itemList.push_back(std::string("    Change Font Size"));
        scoreList.push_back(changeFontSizeScore);

        itemList.push_back(std::string("    Insert Text"));
        scoreList.push_back(insertTextScore);

        itemList.push_back(std::string("    Copy Text"));
        scoreList.push_back(copyTextScore);

        itemList.push_back(std::string("    Draw Line"));
        scoreList.push_back(drawLineScore);

        itemList.push_back(std::string("    Draw Rectangle"));
        scoreList.push_back(drawRectangleScore);

        itemList.push_back(std::string("    Save"));
        scoreList.push_back(saveScore);

        itemList.push_back(std::string("    Close"));
        scoreList.push_back(closeScore);
    }
    if(_result.calc.size()>0)
    {
        double totalScore = 0;
        double startupScore = 0;
        double inputDataScore = 0;
        double computeDataScore = 0;
        double saveScore = 0;
        double closeScore = 0;
        for(auto data:_result.calc)
        {
            for(int i=0;i<TESTTIME;i++)
            {
                startupScore+=data.time.startUp[i];
                inputDataScore+=data.time.inputData[i];
                computeDataScore+=data.time.computeData[i];
                saveScore+=data.time.save[i];
                closeScore+=data.time.close[i];
            }
        }
        startupScore /= _result.calc.size()*TESTTIME;
        inputDataScore /= _result.calc.size()*TESTTIME;
        computeDataScore /= _result.calc.size()*TESTTIME;
        saveScore /= _result.calc.size()*TESTTIME;
        closeScore /= _result.calc.size()*TESTTIME;
        totalScore = startupScore
                    +inputDataScore
                    +computeDataScore
                    +saveScore
                    +closeScore;
        itemList.push_back(std::string("Calc"));
        scoreList.push_back(totalScore);
        itemList.push_back(std::string("    StartUp"));
        scoreList.push_back(startupScore); 
        itemList.push_back(std::string("    Input Data"));
        scoreList.push_back(inputDataScore);
        itemList.push_back(std::string("    Compute"));
        scoreList.push_back(computeDataScore);
        itemList.push_back(std::string("    Save"));
        scoreList.push_back(saveScore);
        itemList.push_back(std::string("    Close"));
        scoreList.push_back(closeScore);
       
    }
    if(_result.impress.size()>0)
    {
        double totalScore = 0;
        double startupScore = 0;
        double resizeScore = 0;
        double browseSlideScore = 0;
        double createSlideScore = 0;
        double insertImageScore = 0;
        double cutImageScore = 0;
        double insertTextScore = 0;
        double saveScore = 0;
        double closeScore = 0;
        for(auto data:_result.impress)
        {
            for(int i=0;i<TESTTIME;i++)
            {
                startupScore+=data.time.startUp[i];
                resizeScore+=data.time.resize[i];
                browseSlideScore+=data.time.gotoSlide[i];
                createSlideScore+=data.time.createSlide[i];
                insertImageScore+=data.time.insertImage[i];
                cutImageScore+=data.time.cutImage[i];
                insertTextScore+=data.time.insertText[i];
                saveScore+=data.time.save[i];
                closeScore+=data.time.close[i];
            }
        }
        startupScore /= _result.impress.size()*TESTTIME;
        resizeScore /= _result.impress.size()*TESTTIME;
        browseSlideScore /= _result.impress.size()*TESTTIME;
        createSlideScore /= _result.impress.size()*TESTTIME;
        insertImageScore /= _result.impress.size()*TESTTIME;
        cutImageScore /= _result.impress.size()*TESTTIME;
        insertTextScore /= _result.impress.size()*TESTTIME;                
        saveScore /= _result.impress.size()*TESTTIME;
        closeScore /= _result.impress.size()*TESTTIME;
        totalScore = startupScore
                    +resizeScore
                    +browseSlideScore
                    +createSlideScore
                    +insertImageScore
                    +cutImageScore
                    +insertTextScore                                
                    +saveScore
                    +closeScore;
        itemList.push_back(std::string("Impress"));
        scoreList.push_back(totalScore);

        itemList.push_back(std::string("    StartUp"));
        scoreList.push_back(startupScore); 

        itemList.push_back(std::string("    Resize"));
        scoreList.push_back(resizeScore); 

        itemList.push_back(std::string("    Browse Slides"));
        scoreList.push_back(browseSlideScore);

        itemList.push_back(std::string("    Create Slide"));
        scoreList.push_back(createSlideScore);

        itemList.push_back(std::string("    Insert Image"));
        scoreList.push_back(insertImageScore);

        itemList.push_back(std::string("    Cut Image"));
        scoreList.push_back(cutImageScore);

        itemList.push_back(std::string("    Insert Text"));
        scoreList.push_back(insertTextScore);

        itemList.push_back(std::string("    Save"));
        scoreList.push_back(saveScore);

        itemList.push_back(std::string("    Close"));
        scoreList.push_back(closeScore);
    }

    if(_result.bigFile.size()>0)
    {
        double totalScore = 0;
        double startupScore = 0;
        double closeScore = 0;
        itemList.push_back(std::string("BigFile"));
        scoreList.push_back(totalScore);
        for(auto data:_result.bigFile)
        {
            for(int i=0;i<TESTTIME;i++)
            {
                startupScore+=data.time.open[i];
                closeScore+=data.time.close[i];
            }
            startupScore/=TESTTIME;
            totalScore+=startupScore;
            itemList.push_back(std::string("    ")+data.name);
            scoreList.push_back(startupScore);
        }
        scoreList[0] = totalScore;
    }
    std::string path = QDir::currentPath().toUtf8().constData();
    path+=std::string("/officebenchmark_result.txt");

    std::ofstream outfile;
    outfile.open(path.data());
    for(int i=0;i<itemList.size();i++)
    {
        outfile<<itemList[i]<<":"<<scoreList[i]<<std::endl;
    }
    outfile.close();
}
BenchMark::BigFileTime BenchMark::BenchOffice::bigfile_bench(std::string file)
{
    if(isWriterFile(file))
        return writer_bigfile(file);
    if(isCalcFile(file))
        return calc_bigfile(file);
    if(isImpressFile(file))
        return impress_bigfile(file);
}
bool BenchMark::BenchOffice::isWriterFile(std::string file)
{
    if(file.find(".odt") != std::string::npos)
        return true;
    if(file.find(".wps") != std::string::npos)
        return true;
    if(file.find(".doc") != std::string::npos)
        return true;
    if(file.find(".docx") != std::string::npos)
        return true;
    return false;
}

bool BenchMark::BenchOffice::isCalcFile(std::string file)
{
    if(file.find(".ods") != std::string::npos)
        return true;
    if(file.find(".et") != std::string::npos)
        return true;
    if(file.find(".xlsx") != std::string::npos)
        return true;
    return false;
}

bool BenchMark::BenchOffice::isImpressFile(std::string file)
{
    if(file.find(".odp") != std::string::npos)
        return true;
    if(file.find(".dps") != std::string::npos)
        return true;
    if(file.find(".ppt") != std::string::npos)
        return true;
    return false;
}
BenchMark::BigFileTime BenchMark::BenchOffice::writer_bigfile(std::string file)
{
    BigFileTime time;
    for(int i=0;i<TESTTIME;i++)
    {
        OfficeControl::WriterControl librewriter(resolution_width,resolution_height);
        librewriter.setFile(file);

        auto duration = librewriter.open_doc();
        time.open[i] = duration/1000000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = librewriter.close();
        time.close[i] = duration/1000000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));
    }
    return time;
}
BenchMark::BigFileTime BenchMark::BenchOffice::calc_bigfile(std::string file)
{
    BigFileTime time;
    for(int i=0;i<TESTTIME;i++)
    {
        OfficeControl::CalcControl librecalc(resolution_width,resolution_height);
        librecalc.setFile(file);
        auto duration = librecalc.open_doc();
        time.open[i] = duration/1000000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = librecalc.close();
        time.close[i] = duration/1000000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));
    }
    return time;
}
BenchMark::BigFileTime BenchMark::BenchOffice::impress_bigfile(std::string file)
{
    BigFileTime time;
    for(int i=0;i<TESTTIME;i++)
    {
        OfficeControl::ImpressControl libreimpress(resolution_width,resolution_height);
        libreimpress.setFile(file);
        auto duration = libreimpress.open_doc();
        time.open[i] = duration/1000000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration =libreimpress.close();
        time.close[i]=duration/1000000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));
    }
    return time;
}

BenchMark::WriterTime BenchMark::BenchOffice::writer_bench(std::string file)
{
    WriterTime time;
    for(int i=0;i<TESTTIME;i++)
    {
        OfficeControl::WriterControl librewriter(resolution_width,resolution_height);
        librewriter.setFile(file);

        auto duration = librewriter.open_doc();
        time.startUp[i] = duration/1000000;
        std::cout<<"startup: "<<duration/1000000<<std::endl;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = librewriter.resize();
        time.resize[i] = duration/1000000;
        std::cout<<"resize: "<<duration/1000000<<std::endl;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = librewriter.change_font_type();
        time.changeFont[i] = duration/1000000;
        std::cout<<"change_font_type: "<<duration/1000000<<std::endl;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = librewriter.change_font_size();
        time.changeFontSize[i] = duration/1000000;
        std::cout<<"change_font_size: "<<duration/1000000<<std::endl;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = librewriter.insert_characters();
        time.insertCharacters[i] = duration/1000000;
        std::cout<<"insert_characters: "<<duration/1000000<<std::endl;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = librewriter.copy_text();
        time.copyText[i] = duration/1000000;
        std::cout<<"copy_text: "<<duration/1000000<<std::endl;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        //begintime = std::chrono::high_resolution_clock::now();
        //librewriter.copy_content();
        //endtime = std::chrono::high_resolution_clock::now();
    // duration = std::chrono::duration_cast<std::chrono::microseconds>(endtime-begintime).count();
    // time.copyContent = duration;
    // std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = librewriter.draw_line();
        time.drawLine[i] = duration/1000000;
        std::cout<<"draw Line:"<<duration/1000000<<std::endl;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = librewriter.draw_rectangle();
        time.drawRectangle[i] = duration/1000000;
        std::cout<<"draw_rectangle: "<<duration/1000000<<std::endl;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = librewriter.save_with_new_name();
        time.save[i] = duration/1000000;
        std::cout<<"save_with_new_name: "<<duration/1000000<<std::endl;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        //librewriter.save_as_PDF();//this still a bug
        //std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = librewriter.close();
        time.close[i] = duration/1000000;
        std::cout<<"close: "<<duration/1000000<<std::endl;
    }
    return time;
}
BenchMark::CalcTime BenchMark::BenchOffice::calc_bench(std::string file)
{
    CalcTime time;
    for(int i=0;i<TESTTIME;i++)
    {
        OfficeControl::CalcControl librecalc(resolution_width,resolution_height);
        librecalc.setFile(file);

        auto duration = librecalc.open_doc();
        time.startUp[i] = duration/1000000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = librecalc.input_data();
        time.inputData[i] = duration/1000000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = librecalc.compute_data();
        time.computeData[i] = duration/1000000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        //librecalc.generate_chart();//still a bug
        //std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = librecalc.save_with_new_name();
        time.save[i] = duration/1000000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = librecalc.close();
        time.close[i] = duration/1000000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));
    }
    return time;
}
BenchMark::ImpressTime BenchMark::BenchOffice::impress_bench(std::string file)
{
    ImpressTime time;
    for(int i=0;i<TESTTIME;i++)
    {
        OfficeControl::ImpressControl libreimpress(resolution_width,resolution_height);
        libreimpress.setFile(file);

        auto duration = libreimpress.open_doc();
        time.startUp[i] = duration/1000000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = libreimpress.goto_slide();
        time.gotoSlide[i] = duration/1000000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = libreimpress.create_new_slide();
        time.createSlide[i] = duration/1000000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = libreimpress.insert_image();
        time.insertImage[i] = duration/1000000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = libreimpress.cut_image();
        time.cutImage[i] = duration/1000000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = libreimpress.insert_text();
        time.insertText[i] = duration/1000000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = libreimpress.save_with_new_name();
        time.save[i] = duration/1000000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        //libreimpress.getFilterName();
        //libreimpress.save_as_PDF();//this still a bug
        //std::this_thread::sleep_for(std::chrono::nanoseconds(600));

        duration = libreimpress.close();
        time.close[i] = duration/1000000;
        std::this_thread::sleep_for(std::chrono::nanoseconds(600));
    }
    return time;
}