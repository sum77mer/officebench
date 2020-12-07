#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <QObject>
//#include <QRect.h>
//#include <QApplication.h>
#define TESTTIME 5

namespace BenchMark{
    struct WriterTime{
        double startUp[TESTTIME];
        double resize[TESTTIME];
        double changeFont[TESTTIME];
        double changeFontSize[TESTTIME];
        double insertCharacters[TESTTIME];
        double copyText[TESTTIME];
        double drawLine[TESTTIME];
        double drawRectangle[TESTTIME];
        double save[TESTTIME];
        double close[TESTTIME];
    };
    struct CalcTime{
        double startUp[TESTTIME];
        double inputData[TESTTIME];
        double computeData[TESTTIME];
        double save[TESTTIME];
        double close[TESTTIME];
    };
    struct ImpressTime{
        double startUp[TESTTIME];
        double resize[TESTTIME];
        double gotoSlide[TESTTIME];
        double createSlide[TESTTIME];
        double insertImage[TESTTIME];
        double cutImage[TESTTIME];
        double insertText[TESTTIME];
        double save[TESTTIME];
        double close[TESTTIME];
    };
    struct BigFileTime{
        double open[TESTTIME];
        double close[TESTTIME];
    };
    struct WriterResult{
        std::string name;
        float size;
        WriterTime time;
    };
    struct CalcResult{
        std::string name;
        float size;
        CalcTime time;
    };
    struct ImpressResult{
        std::string name;
        float size;
        ImpressTime time;
    };
    struct BigFileResult{
        std::string name;
        float size;
        BigFileTime time;
    };
    struct TestResult{
        std::vector<WriterResult> writer;
        std::vector<CalcResult> calc;
        std::vector<ImpressResult> impress;
        std::vector<BigFileResult> bigFile;
    };
    class BenchOffice : public QObject
    {
        Q_OBJECT
    public:
        explicit BenchOffice(QObject *parent = nullptr,int flag = 0);
        void start_bench(int flag);
    public:
        WriterTime writer_bench(std::string file);
        CalcTime calc_bench(std::string file);
        ImpressTime impress_bench(std::string file);
        BigFileTime bigfile_bench(std::string file);

        std::map<std::string,double> writerBench_result(){return writerResult;};
        std::map<std::string,double> calcBench_result(){return calcResult;};
        std::map<std::string,double> impressBench_result(){return impressResult;};
        std::map<std::string,double> bigFileBench_result(){return startUpResult;};
        std::map<std::string,double> startUpBench_result(){return bigFileResult;};

        void getResult(std::vector<std::string> &itemList,std::vector<double> &scoreList);

        void setTestFilePath(QString path);

    private:
        bool isWriterFile(std::string file);
        bool isCalcFile(std::string file);
        bool isImpressFile(std::string file);

        BigFileTime writer_bigfile(std::string file);
        BigFileTime calc_bigfile(std::string file);
        BigFileTime impress_bigfile(std::string file);
        void getDesktopScreenResolution(int &width,int &height);
        

    signals:

    private:
        bool dbg = true;
        int resolution_width = 0;
        int resolution_height = 0;

        std::map<std::string,double> writerResult;
        std::map<std::string,double> calcResult;
        std::map<std::string,double> impressResult;
        std::map<std::string,double> startUpResult;
        std::map<std::string,double> bigFileResult;

        std::string testFilePath;

        std::vector<std::string> writerFileList;
        std::vector<std::string> calcFileList;
        std::vector<std::string> impressFileList;
        std::vector<std::string> bigFileList;

        TestResult _result;
        //all test result will save here
        //after test end, will generate a file
    };
}


#endif // BENCHMARK_H
