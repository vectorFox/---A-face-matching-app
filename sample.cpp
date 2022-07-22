/*注：代码运行前请将文件夹“男方资料”和“女方资料”保存至D盘*/


#include<pch.h>

#include<iostream>
#include<string>
#include <Windows.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include<iomanip>
#include <stdlib.h>
#include<fstream>

using namespace std;
using namespace cv;
class data {               //定义一个人数据类；
public:
    data();
    void set_data(string n, string a, string w);
    void put_data();//输出数据
    void catch_photo2();//拍照
    void catch_photo1();//拍照
    string get_name()
    {
        return name;
    }
    string get_age()
    {
        return age;
    }
    string get_work()
    {
        return work;
    }
    void set_name(string n)
    {
        name = n;
    }
    void set_age(string a)
    {
        age = a;
    }
    void set_work(string w)
    {
        work = w;
    }
private:
    string name;//定义名字
    string age;//定义年龄
    string work;//定义工作
    string writePath;//定义保存地址
};
data::data()
{
}
void data::set_data(string n, string a, string w)
{
    name = n;
    age = a;
    work = w;
    writePath = "D:\\" + name;
}
class man :public data {
public:
    string writePath = "D:\\男" + get_name();
    void set_man(string n, string a, string w);
};
void man::set_man(string n, string a, string w)
{
    set_data(n, a, w);
    writePath = "D:\\男方资料\\" + get_name();
    ofstream outfile(writePath + ".txt");
    if (!outfile)
    {
        cout << "文件创建失败" << endl;
    }
    outfile << "姓名：  " << get_name() << endl;
    outfile << "年龄：  " << get_age() << endl;
    outfile << "工作：  " << get_work() << endl;
    outfile.close();
}
class woman :public data {
public:
    string writePath = "D:\\女方资料\\" + get_name();
    void set_woman(string n, string a, string w);
};
void woman::set_woman(string n, string a, string w)
{
    set_data(n, a, w);
    writePath = "D:\\女方资料\\" + get_name();
    ofstream outfile(writePath + ".txt");
    if (!outfile)
    {
        cout << "文件创建失败" << endl;
    }
    outfile << "姓名：  " << get_name() << endl;
    outfile << "年龄：  " << get_age() << endl;
    outfile << "工作：  " << get_work() << endl;
    outfile.close();
}
void data::put_data()
{
    ifstream infile(writePath);
    if (!infile)
    {
        cout << "文件打开失败" << endl;
    }
    string s;
    while (getline(infile, s))
    {
        cout << s << endl;
    }
    infile.close();

}
/*void catch_photo1()
{
    //从摄像头读入视频
    VideoCapture capture(0);//VideoCapture是一个摄像头类，可以读取摄像头或者本地的视频文件
    while (1)
    {
        Mat frame;//定义一个Mat变量，用于存储每一帧的图像
                    //Mat是OpenCv的矩阵类，一般用来存储图像。
        capture >> frame;//读取当前帧
        resize(frame, frame, Size(360, 240));//改变图像大小
        imshow("aa", frame);
        waitKey(30);//延时30ms
    }
}*/
void data::catch_photo2()
{
    VideoCapture capture(0);
    string s;
  //  namedWindow("您已打开摄像头，按空格拍照，按1关闭摄像头", CV_WINDOW_AUTOSIZE);//创建一个对话框
    int i = 1;
    while (1) {
        Mat frame;
        capture >> frame;
        if (32 == waitKey(20)) {			//空格拍照
            s = "D:\\男方资料\\" + name + ".jpg";
            imwrite(s, frame);
            cout << s << endl;
            i++;
        }
        if ('1' == waitKey(10)) {			//'1'退出
            break;
        }
        imshow("您已打开摄像头，按空格拍照，按1关闭摄像头", frame);//显示摄像头

    }
    //waitKey(0);
}
void data::catch_photo1()
{
    VideoCapture capture(0);
    string s;
  //  namedWindow("您已打开摄像头，按空格拍照，按1关闭摄像头", CV_WINDOW_AUTOSIZE);//创建一个对话框
    int i = 1;
    while (1) {
        Mat frame;
        capture >> frame;
        if (32 == waitKey(20)) {			//空格拍照
            s = "D:\\女方资料\\" + name + ".jpg";
            imwrite(s, frame);
            cout << s << endl;
            i++;
        }
        if ('1' == waitKey(10)) {			//'1'退出
            break;
        }
        imshow("您已打开摄像头，按空格拍照，按1关闭摄像头", frame);//显示摄像头

    }
    //waitKey(0);
}
void put_photo1(string writePath)
{
    ifstream infile(writePath + ".txt");//数据读取
    if (!infile)
    {
        cout << "文件打开失败" << endl;
    }
    string s;
    while (getline(infile, s))
    {
        cout << s << endl;
    }
    infile.close();


    Mat img = imread(writePath + ".jpg");
    imshow("Pic", img);
    waitKey(0);
}
void put_photo2(string writePath)
{
    ifstream infile(writePath + ".txt");//数据读取
    if (!infile)
    {
        cout << "文件打开失败" << endl;
    }
    string s;
    while (getline(infile, s))
    {
        cout << s << endl;
    }
    infile.close();

    Mat img = imread(writePath + ".jpg");
    imshow("Pic", img);
    waitKey(0);

}
/*void put_photo2()
{
    IplImage* img = cvLoadImage(writePath + ".jpg", -1);//将图像文件加载到内存，cvloadImage()函数是一个高层调用接口，用过文件名确定被加载文件的格式。该函数可以读取绝大多数类型的图像文件。函数执行完之后返回一个指针，该指针指向一块为描述改图像文件的数据结构（IplImage）而分配的内存块
    cvNamedWindow("test",0);//cvNamedWindow()函数也是一个高层调用接口，该函数有HighGUI库提供。该函数用于在屏幕上创建一个窗口，被显示的图像包含于该窗口中；第一个参数"test"指定了该窗口的窗口标题，其他函数与该窗口进行交互，我们就用该参数值来引用它。第一个参数就是给这个窗口命名。第二个参数定义窗口的属性，该参数值为0时，窗口的大小不会因为图像的大小而改变，也就是图像要根据窗口的大小来进行伸缩。数值为：CV_WINDOW_AUTOSIZE，显然窗口会根据图像的大小来改变。
    cvShowImage("test", img);
    cvWaitKey(0);//功能是使程序暂停，等待用户触发一个按键操作。但如果将该函数参数设为一个正数，则程序将暂停一段时间，时间长为该整数值个毫秒单位，然后继续执行程序，即使用户没有按下任何键。当设置该函数参数为O或负数时，程序将一直等待用户触发按键操作。
    cvReleaseImage(&img);
    cvDestroyWindow("test");
}*/
double compareFacesByHist(Mat img, Mat orgImg)
{
    Mat tmpImg;
    resize(img, tmpImg, Size(orgImg.cols, orgImg.rows));
    imshow("orgImg", orgImg);
    waitKey(1000);
    //HSV颜色特征模型(色调H,饱和度S，亮度V)
    cvtColor(tmpImg, tmpImg, COLOR_BGR2HSV);
    cvtColor(orgImg, orgImg, COLOR_BGR2HSV);
    //直方图尺寸设置
    //一个灰度值可以设定一个bins，256个灰度值就可以设定256个bins
    //对应HSV格式,构建二维直方图
    //每个维度的直方图灰度值划分为256块进行统计，也可以使用其他值
    int hBins = 256, sBins = 256;
    int histSize[] = { hBins,sBins };
    //H:0~180, S:0~255,V:0~255
    //H色调取值范围
    float hRanges[] = { 0,180 };
    //S饱和度取值范围
    float sRanges[] = { 0,255 };
    const float* ranges[] = { hRanges,sRanges };
    int channels[] = { 0,1 };//二维直方图
    MatND hist1, hist2;
    calcHist(&tmpImg, 1, channels, Mat(), hist1, 2, histSize, ranges, true, false);
    normalize(hist1, hist1, 0, 1, NORM_MINMAX, -1, Mat());
    calcHist(&orgImg, 1, channels, Mat(), hist2, 2, histSize, ranges, true, false);
    normalize(hist2, hist2, 0, 1, NORM_MINMAX, -1, Mat());
    double similarityValue = compareHist(hist1, hist2, 0);
    cout << "相似度：" << similarityValue << endl;
    return similarityValue;
}
Mat readimage1(Mat img)
{
    std::string pattern_jpg;
    std::vector<cv::String> image_files;
    pattern_jpg = "D:\\女方资料\\*.jpg";
    cv::glob(pattern_jpg, image_files);
    double a = 0, b = 0; Mat c;
    for (int ii = 0; ii < image_files.size(); ii++)
    {
        cout << image_files[ii] << endl;
        Mat dd = imread(image_files[ii]);
        Mat dd2 = imread(image_files[ii]);
        imshow("Img", img);
        a = compareFacesByHist(img, dd);
        if (b < a)
        {
            b = a;
            c = dd2;
        }
    }
    return c;
}
Mat readimage2(Mat img)
{
    std::string pattern_jpg;
    std::vector<cv::String> image_files;
    pattern_jpg = "D:\\男方资料\\*.jpg";
    cv::glob(pattern_jpg, image_files);
    double a = 0, b = 0; Mat c;
    for (int ii = 0; ii < image_files.size(); ii++)
    {
        cout << image_files[ii] << endl;
        Mat dd = imread(image_files[ii]);
        Mat dd2 = imread(image_files[ii]);
        imshow("Img", img);
        a = compareFacesByHist(img, dd);
        if (b < a)
        {
            b = a;
            c = dd2;
        }
    }
    return c;
}
int main()
{
    int a = 0;
    cout << "请选择你的操作：" << endl;
    cout << "1.图像相似度比较" << endl;
    cout << "2.图像数据从摄像头输入(男)" << endl;
    cout << "3.图像数据从摄像头输入(女)" << endl;
    cout << "4.图片显示（男方图片)并显示资料" << endl;
    cout << "5.图片显示（女方图片)并显示资料" << endl;
    cin >> a;
    if (a == 1)
    {
        int sex = 0;
        cout << "我要找女朋友：（按1）" << endl;
        cout << "我要找男朋友：（按2）" << endl;
        cin >> sex;
        if (sex == 1)
        {
            double n = 0; Mat M; Mat s;
            cout << "请输入您的的姓名：";
            string a;
            cin >> a;
            string writePath = "D:\\男方资料\\" + a;
            Mat img = imread(writePath + ".jpg");
            s = readimage1(img);
            imshow("匹配值最高", s);
            waitKey(0);
        }
        if (sex == 2)
        {
            double n = 0; Mat M; Mat s;
            cout << "请输入您的姓名：";
            string a;
            cin >> a;
            string writePath = "D:\\女方资料\\" + a;
            Mat img = imread(writePath + ".jpg");
            s = readimage2(img);
            imshow("匹配值最高", s);
            waitKey(0);
        }
    }
    if (a == 2)
    {
        cout << "请输入采集人物的信息" << endl;
        cout << "请输入采集人物的姓名：" << endl;
        string n;
        string a;
        string w;
        cin >> n;
        cout << "请输入采集人物的年龄：" << endl;
        cin >> a;
        cout << "请输入采集人物的职业：" << endl;
        cin >> w;
        man s;
        s.set_man(n, a, w);
        s.catch_photo2();//拍照；
    }
    if (a == 3)
    {
        cout << "请输入采集人物的信息" << endl;
        cout << "请输入采集人物的姓名：" << endl;
        string n;
        string a;
        string w;
        cin >> n;
        cout << "请输入采集人物的年龄：" << endl;
        cin >> a;
        cout << "请输入采集人物的职业：" << endl;
        cin >> w;
        woman s;
        s.set_woman(n, a, w);
        s.catch_photo1();//拍照；
    }
    if (a == 4)
    {
        cout << "请输入要展现的照片主人的姓名" << endl;
        string a;
        cin >> a;
        string writePath = "D:\\男方资料\\" + a;
        put_photo1(writePath);
    }
    if (a == 5)
    {
        cout << "请输入要展现的照片主人的姓名" << endl;
        string a;
        cin >> a;
        string writePath = "D:\\女方资料\\" + a;
        put_photo2(writePath);
    }
}
