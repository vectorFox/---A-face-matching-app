/*ע����������ǰ�뽫�ļ��С��з����ϡ��͡�Ů�����ϡ�������D��*/


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
class data {               //����һ���������ࣻ
public:
    data();
    void set_data(string n, string a, string w);
    void put_data();//�������
    void catch_photo2();//����
    void catch_photo1();//����
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
    string name;//��������
    string age;//��������
    string work;//���幤��
    string writePath;//���屣���ַ
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
    string writePath = "D:\\��" + get_name();
    void set_man(string n, string a, string w);
};
void man::set_man(string n, string a, string w)
{
    set_data(n, a, w);
    writePath = "D:\\�з�����\\" + get_name();
    ofstream outfile(writePath + ".txt");
    if (!outfile)
    {
        cout << "�ļ�����ʧ��" << endl;
    }
    outfile << "������  " << get_name() << endl;
    outfile << "���䣺  " << get_age() << endl;
    outfile << "������  " << get_work() << endl;
    outfile.close();
}
class woman :public data {
public:
    string writePath = "D:\\Ů������\\" + get_name();
    void set_woman(string n, string a, string w);
};
void woman::set_woman(string n, string a, string w)
{
    set_data(n, a, w);
    writePath = "D:\\Ů������\\" + get_name();
    ofstream outfile(writePath + ".txt");
    if (!outfile)
    {
        cout << "�ļ�����ʧ��" << endl;
    }
    outfile << "������  " << get_name() << endl;
    outfile << "���䣺  " << get_age() << endl;
    outfile << "������  " << get_work() << endl;
    outfile.close();
}
void data::put_data()
{
    ifstream infile(writePath);
    if (!infile)
    {
        cout << "�ļ���ʧ��" << endl;
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
    //������ͷ������Ƶ
    VideoCapture capture(0);//VideoCapture��һ������ͷ�࣬���Զ�ȡ����ͷ���߱��ص���Ƶ�ļ�
    while (1)
    {
        Mat frame;//����һ��Mat���������ڴ洢ÿһ֡��ͼ��
                    //Mat��OpenCv�ľ����࣬һ�������洢ͼ��
        capture >> frame;//��ȡ��ǰ֡
        resize(frame, frame, Size(360, 240));//�ı�ͼ���С
        imshow("aa", frame);
        waitKey(30);//��ʱ30ms
    }
}*/
void data::catch_photo2()
{
    VideoCapture capture(0);
    string s;
  //  namedWindow("���Ѵ�����ͷ�����ո����գ���1�ر�����ͷ", CV_WINDOW_AUTOSIZE);//����һ���Ի���
    int i = 1;
    while (1) {
        Mat frame;
        capture >> frame;
        if (32 == waitKey(20)) {			//�ո�����
            s = "D:\\�з�����\\" + name + ".jpg";
            imwrite(s, frame);
            cout << s << endl;
            i++;
        }
        if ('1' == waitKey(10)) {			//'1'�˳�
            break;
        }
        imshow("���Ѵ�����ͷ�����ո����գ���1�ر�����ͷ", frame);//��ʾ����ͷ

    }
    //waitKey(0);
}
void data::catch_photo1()
{
    VideoCapture capture(0);
    string s;
  //  namedWindow("���Ѵ�����ͷ�����ո����գ���1�ر�����ͷ", CV_WINDOW_AUTOSIZE);//����һ���Ի���
    int i = 1;
    while (1) {
        Mat frame;
        capture >> frame;
        if (32 == waitKey(20)) {			//�ո�����
            s = "D:\\Ů������\\" + name + ".jpg";
            imwrite(s, frame);
            cout << s << endl;
            i++;
        }
        if ('1' == waitKey(10)) {			//'1'�˳�
            break;
        }
        imshow("���Ѵ�����ͷ�����ո����գ���1�ر�����ͷ", frame);//��ʾ����ͷ

    }
    //waitKey(0);
}
void put_photo1(string writePath)
{
    ifstream infile(writePath + ".txt");//���ݶ�ȡ
    if (!infile)
    {
        cout << "�ļ���ʧ��" << endl;
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
    ifstream infile(writePath + ".txt");//���ݶ�ȡ
    if (!infile)
    {
        cout << "�ļ���ʧ��" << endl;
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
    IplImage* img = cvLoadImage(writePath + ".jpg", -1);//��ͼ���ļ����ص��ڴ棬cvloadImage()������һ���߲���ýӿڣ��ù��ļ���ȷ���������ļ��ĸ�ʽ���ú������Զ�ȡ����������͵�ͼ���ļ�������ִ����֮�󷵻�һ��ָ�룬��ָ��ָ��һ��Ϊ������ͼ���ļ������ݽṹ��IplImage����������ڴ��
    cvNamedWindow("test",0);//cvNamedWindow()����Ҳ��һ���߲���ýӿڣ��ú�����HighGUI���ṩ���ú�����������Ļ�ϴ���һ�����ڣ�����ʾ��ͼ������ڸô����У���һ������"test"ָ���˸ô��ڵĴ��ڱ��⣬����������ô��ڽ��н��������Ǿ��øò���ֵ������������һ���������Ǹ���������������ڶ����������崰�ڵ����ԣ��ò���ֵΪ0ʱ�����ڵĴ�С������Ϊͼ��Ĵ�С���ı䣬Ҳ����ͼ��Ҫ���ݴ��ڵĴ�С��������������ֵΪ��CV_WINDOW_AUTOSIZE����Ȼ���ڻ����ͼ��Ĵ�С���ı䡣
    cvShowImage("test", img);
    cvWaitKey(0);//������ʹ������ͣ���ȴ��û�����һ��������������������ú���������Ϊһ���������������ͣһ��ʱ�䣬ʱ�䳤Ϊ������ֵ�����뵥λ��Ȼ�����ִ�г��򣬼�ʹ�û�û�а����κμ��������øú�������ΪO����ʱ������һֱ�ȴ��û���������������
    cvReleaseImage(&img);
    cvDestroyWindow("test");
}*/
double compareFacesByHist(Mat img, Mat orgImg)
{
    Mat tmpImg;
    resize(img, tmpImg, Size(orgImg.cols, orgImg.rows));
    imshow("orgImg", orgImg);
    waitKey(1000);
    //HSV��ɫ����ģ��(ɫ��H,���Ͷ�S������V)
    cvtColor(tmpImg, tmpImg, COLOR_BGR2HSV);
    cvtColor(orgImg, orgImg, COLOR_BGR2HSV);
    //ֱ��ͼ�ߴ�����
    //һ���Ҷ�ֵ�����趨һ��bins��256���Ҷ�ֵ�Ϳ����趨256��bins
    //��ӦHSV��ʽ,������άֱ��ͼ
    //ÿ��ά�ȵ�ֱ��ͼ�Ҷ�ֵ����Ϊ256�����ͳ�ƣ�Ҳ����ʹ������ֵ
    int hBins = 256, sBins = 256;
    int histSize[] = { hBins,sBins };
    //H:0~180, S:0~255,V:0~255
    //Hɫ��ȡֵ��Χ
    float hRanges[] = { 0,180 };
    //S���Ͷ�ȡֵ��Χ
    float sRanges[] = { 0,255 };
    const float* ranges[] = { hRanges,sRanges };
    int channels[] = { 0,1 };//��άֱ��ͼ
    MatND hist1, hist2;
    calcHist(&tmpImg, 1, channels, Mat(), hist1, 2, histSize, ranges, true, false);
    normalize(hist1, hist1, 0, 1, NORM_MINMAX, -1, Mat());
    calcHist(&orgImg, 1, channels, Mat(), hist2, 2, histSize, ranges, true, false);
    normalize(hist2, hist2, 0, 1, NORM_MINMAX, -1, Mat());
    double similarityValue = compareHist(hist1, hist2, 0);
    cout << "���ƶȣ�" << similarityValue << endl;
    return similarityValue;
}
Mat readimage1(Mat img)
{
    std::string pattern_jpg;
    std::vector<cv::String> image_files;
    pattern_jpg = "D:\\Ů������\\*.jpg";
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
    pattern_jpg = "D:\\�з�����\\*.jpg";
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
    cout << "��ѡ����Ĳ�����" << endl;
    cout << "1.ͼ�����ƶȱȽ�" << endl;
    cout << "2.ͼ�����ݴ�����ͷ����(��)" << endl;
    cout << "3.ͼ�����ݴ�����ͷ����(Ů)" << endl;
    cout << "4.ͼƬ��ʾ���з�ͼƬ)����ʾ����" << endl;
    cout << "5.ͼƬ��ʾ��Ů��ͼƬ)����ʾ����" << endl;
    cin >> a;
    if (a == 1)
    {
        int sex = 0;
        cout << "��Ҫ��Ů���ѣ�����1��" << endl;
        cout << "��Ҫ�������ѣ�����2��" << endl;
        cin >> sex;
        if (sex == 1)
        {
            double n = 0; Mat M; Mat s;
            cout << "���������ĵ�������";
            string a;
            cin >> a;
            string writePath = "D:\\�з�����\\" + a;
            Mat img = imread(writePath + ".jpg");
            s = readimage1(img);
            imshow("ƥ��ֵ���", s);
            waitKey(0);
        }
        if (sex == 2)
        {
            double n = 0; Mat M; Mat s;
            cout << "����������������";
            string a;
            cin >> a;
            string writePath = "D:\\Ů������\\" + a;
            Mat img = imread(writePath + ".jpg");
            s = readimage2(img);
            imshow("ƥ��ֵ���", s);
            waitKey(0);
        }
    }
    if (a == 2)
    {
        cout << "������ɼ��������Ϣ" << endl;
        cout << "������ɼ������������" << endl;
        string n;
        string a;
        string w;
        cin >> n;
        cout << "������ɼ���������䣺" << endl;
        cin >> a;
        cout << "������ɼ������ְҵ��" << endl;
        cin >> w;
        man s;
        s.set_man(n, a, w);
        s.catch_photo2();//���գ�
    }
    if (a == 3)
    {
        cout << "������ɼ��������Ϣ" << endl;
        cout << "������ɼ������������" << endl;
        string n;
        string a;
        string w;
        cin >> n;
        cout << "������ɼ���������䣺" << endl;
        cin >> a;
        cout << "������ɼ������ְҵ��" << endl;
        cin >> w;
        woman s;
        s.set_woman(n, a, w);
        s.catch_photo1();//���գ�
    }
    if (a == 4)
    {
        cout << "������Ҫչ�ֵ���Ƭ���˵�����" << endl;
        string a;
        cin >> a;
        string writePath = "D:\\�з�����\\" + a;
        put_photo1(writePath);
    }
    if (a == 5)
    {
        cout << "������Ҫչ�ֵ���Ƭ���˵�����" << endl;
        string a;
        cin >> a;
        string writePath = "D:\\Ů������\\" + a;
        put_photo2(writePath);
    }
}
