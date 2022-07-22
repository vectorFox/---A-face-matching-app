
// test2Dlg.cpp: 实现文件
//
#include <io.h>  
#include <fcntl.h>  
#include< ctime>
#include "pch.h"
#include "framework.h"
#include "test2.h"
#include "test2Dlg.h"
#include "afxdialogex.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <highgui/highgui_c.h>
#include "test2.h"

using namespace cv;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CascadeClassifier cascade;
double similarityValue;//相似度
std::string path1;//pic 1 path
CString strFolderPath;// folder path 
string folderPath;
int ai;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Ctest2Dlg 对话框



Ctest2Dlg::Ctest2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctest2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Ctest2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Ctest2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &Ctest2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Ctest2Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &Ctest2Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDOK, &Ctest2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON6, &Ctest2Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDCANCEL, &Ctest2Dlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// Ctest2Dlg 消息处理程序

BOOL Ctest2Dlg::OnInitDialog()
{
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Ctest2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Ctest2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Ctest2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Ctest2Dlg::OnBnClickedButton1()
{
	CFileDialog dlg(TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		_T("image files(*.jpg)|*.jpg|Worksheet Files|*.xls|All Files(*.*)|*.*||"),
		NULL);                            // 构造文件打开对话框  
	dlg.m_ofn.lpstrTitle = _T("Open Image");  // 文件打开对话框标题  
	if (IDOK != dlg.DoModal())                 // 判断是否成功选中文件  
		return;
	CString path = dlg.GetPathName();         // 获取文件路径  
	// TODO: 在此添加控件通知处理程序代码
	CPaintDC dc(this); // device context for painting

	IPicture* ppic = NULL;
	HRESULT  hr;
	hr = OleLoadPicturePath((CComBSTR)path.GetBuffer(), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&ppic);
	if (SUCCEEDED(hr))
	{
		ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
		CDC* pdc = GetDC();

		OLE_XPOS_HIMETRIC xSrc = 50;  // 图片中当前显示区域的x
		OLE_YPOS_HIMETRIC ySrc = 0;  // 图片中当前显示区域的y
		OLE_XSIZE_HIMETRIC cxSrc = 178; // 图片中当前显示区域的宽度
		OLE_YSIZE_HIMETRIC cySrc = 218; // 图片中当前显示区域的高度
		ppic->get_Width(&cxSrc);
		ppic->get_Height(&cySrc);
		ppic->Render(*pdc, 10, 10, 178, 218, 0, cySrc, cxSrc, -cySrc, NULL);
		ppic->Release();
		ReleaseDC(pdc);
		ppic = NULL;
		
	}
	USES_CONVERSION;
	path1 = W2A(path.GetBuffer());
	path.ReleaseBuffer();
	Mat src = imread(path1,1);//path1 is the path of the picture1 and needed to be analysised
	//imshow("123", src);//show the picture1
	//1 读取训练器 这里用的是haar  路径在你下载的 opencv中 
	CascadeClassifier cascade;
	String haarfile = "C:\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml";

	Mat originImage, grayImage, blurImage,cannyImage, diaImage , erodeImage ,hsvImage ;
	Mat tempImage;
	// 【2】读取图片
	originImage = imread(path1);
	hsvImage = imread(path1);
	cvtColor(originImage, hsvImage, COLOR_BGR2HSV);
	//imshow("hsv", hsvImage);
	cvtColor(originImage, grayImage, COLOR_BGR2GRAY); // 生成灰度图，提高检测效率 
	GaussianBlur(grayImage, blurImage, Size(5, 5), 3, 0);//高斯模糊
	Canny(blurImage, cannyImage, 75, 100);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));//kernel used with dilation
	dilate(cannyImage , diaImage, kernel);//扩张
	erode(diaImage, erodeImage, kernel); //腐蚀

}

double compareFacesByHist(string tmppath1,string tmpfolder)
{	
	Mat img = imread(tmppath1);
	Mat orgImg = imread(tmpfolder);
	Mat tmpImg;
	resize(img, tmpImg, Size(orgImg.cols, orgImg.rows));
	//imshow("orgImg", orgImg);
	//waitKey(1000);
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
	return similarityValue;
}



void Ctest2Dlg::OnBnClickedButton3()
{
	TCHAR szFolderPath[MAX_PATH] = { 0 };
	CString strFolderPath;
	BROWSEINFO sInfo;
	ZeroMemory(&sInfo, sizeof(BROWSEINFO));

	sInfo.pidlRoot = 0;
	sInfo.lpszTitle = _T("请选择一个文件夹：");
	sInfo.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_EDITBOX;
	sInfo.lpfn = NULL;

	// 显示文件夹选择对话框
	LPITEMIDLIST lpidlBrowse = SHBrowseForFolder(&sInfo);
	if (lpidlBrowse != NULL)
	{
		// 取得文件夹名
		if (SHGetPathFromIDList(lpidlBrowse, szFolderPath))
		{
			strFolderPath = szFolderPath;
		}
	}
	if (lpidlBrowse != NULL)
	{
		CoTaskMemFree(lpidlBrowse);
		USES_CONVERSION;
		folderPath = W2A(strFolderPath.GetBuffer());
		strFolderPath.ReleaseBuffer();
	}

	//GetDlgItem(IDC_EDIT1)->SetWindowTextW(strFolderPath);
}


void Ctest2Dlg::OnBnClickedButton4()

{
	CString path ;     
	path = folderPath.c_str();// 获取文件路径  
	// TODO: 在此添加控件通知处理程序代码
	CPaintDC dc(this); // device context for painting

	IPicture* ppic = NULL;
	HRESULT  hr;
	hr = OleLoadPicturePath((CComBSTR)path.GetBuffer(), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&ppic);
	if (SUCCEEDED(hr))
	{
		ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
		CDC* pdc = GetDC();

		OLE_XPOS_HIMETRIC xSrc = 0;  // 图片中当前显示区域的x
		OLE_YPOS_HIMETRIC ySrc = 0;  // 图片中当前显示区域的y
		OLE_XSIZE_HIMETRIC cxSrc = 178; // 图片中当前显示区域的宽度
		OLE_YSIZE_HIMETRIC cySrc = 218; // 图片中当前显示区域的高度
		ppic->get_Width(&cxSrc);
		ppic->get_Height(&cySrc);

		ppic->Render(*pdc, 410, 10, 178, 218, 0, cySrc, cxSrc, -cySrc, NULL);//显示图片

		ppic->Release();
		ReleaseDC(pdc);
		ppic = NULL;

	}
	// TODO: 在此添加控件通知处理程序代码
	int iffind=0;
	string tmppath = folderPath;
	double val;
	srand((unsigned)time(NULL));
	int rands = rand();
	rands = rands % 150; 
	for (ai = rands; ai < 160; ai++) {
		folderPath = folderPath + format("\\pic (%d).jpg", ai);
		//string folderPath = format("C:\\Users\\vector\\Desktop\\pic\\male\\pic (%d).jpg", ai);
		val = compareFacesByHist(path1, folderPath);
		if (val >= 0.21)
		{
			Mat output;
			output = imread(folderPath);
		//	imshow(" final ",output);
			// TODO:  在此添加控件通知处理程序代码
			iffind = 1;
			CString str;
			str.Format(_T("匹配度：%lf"), val);
			MessageBox(str);
			break;
		}
		//waitKey(10000);
		folderPath = tmppath;
	}
	if (iffind == 0)
	{
		CString path;
		path = "C:\\Users\\vector\\Desktop\\pic\\resource\\error.jpg";// 获取文件路径  
		// TODO: 在此添加控件通知处理程序代码
		CPaintDC dc(this); // device context for painting

		IPicture* ppic = NULL;
		HRESULT  hr;
		hr = OleLoadPicturePath((CComBSTR)path.GetBuffer(), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&ppic);
		if (SUCCEEDED(hr))
		{
			ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
			CDC* pdc = GetDC();

			OLE_XPOS_HIMETRIC xSrc = 0;  // 图片中当前显示区域的x
			OLE_YPOS_HIMETRIC ySrc = 0;  // 图片中当前显示区域的y
			OLE_XSIZE_HIMETRIC cxSrc = 178; // 图片中当前显示区域的宽度
			OLE_YSIZE_HIMETRIC cySrc = 218; // 图片中当前显示区域的高度
			ppic->get_Width(&cxSrc);
			ppic->get_Height(&cySrc);

			ppic->Render(*pdc, 410, 10, 178, 218, 0, cySrc, cxSrc, -cySrc, NULL);//显示图片

			ppic->Release();
			ReleaseDC(pdc);
			ppic = NULL;

		}
	}
	
}




void Ctest2Dlg::OnEnChangeMfceditbrowse1()
{
	
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	CFileDialog dlg(TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		_T("image files(*.jpg)|*.jpg|Worksheet Files|*.xls|All Files(*.*)|*.*||"),
		NULL);                            // 构造文件打开对话框  
	dlg.m_ofn.lpstrTitle = _T("Open Image");  // 文件打开对话框标题  
	if (IDOK != dlg.DoModal())                 // 判断是否成功选中文件  
		return;
	CString path = dlg.GetPathName();         // 获取文件路径  
	// TODO: 在此添加控件通知处理程序代码
	CPaintDC dc(this); // device context for painting

	IPicture* ppic = NULL;
	HRESULT  hr;
	hr = OleLoadPicturePath((CComBSTR)path.GetBuffer(), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&ppic);
	if (SUCCEEDED(hr))
	{
		ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
		CDC* pdc = GetDC();

		OLE_XPOS_HIMETRIC xSrc = 0;  // 图片中当前显示区域的x
		OLE_YPOS_HIMETRIC ySrc = 0;  // 图片中当前显示区域的y
		OLE_XSIZE_HIMETRIC cxSrc = 178; // 图片中当前显示区域的宽度
		OLE_YSIZE_HIMETRIC cySrc = 218; // 图片中当前显示区域的高度
		ppic->get_Width(&cxSrc);
		ppic->get_Height(&cySrc);

		ppic->Render(*pdc, 10, 10, 178, 218, 0, cySrc, cxSrc, -cySrc, NULL);

		ppic->Release();
		ReleaseDC(pdc);
		ppic = NULL;
	}
	// TODO:  在此添加控件通知处理程序代码
}

void Ctest2Dlg::OnEnChangeMfceditbrowse2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void Ctest2Dlg::OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	*pResult = 0;
}

int calc()
{

}

void Ctest2Dlg::OnBnClickedButton2()
{


}


void Ctest2Dlg::OnBnClickedButton5()
{
	/*CImage m_img; //对象创建一定要加在这里，因为每次双击打开图片时，都是一个新的对象，否则会出现EXPRESSION:m_hBitmap == 0的错误。
	CString m_filename;
	CString m_pathFolder;
	CString strPicPath;
	folderPath= format("C:\\Users\\vector\\Desktop\\pic\\male\\pic (%d).jpg", ai);
	strPicPath = folderPath.c_str();//文件名
	m_img.Load(strPicPath);
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_STATIC);//拖入Static Text控件，ID为IDC_STATIC,
	CDC* pc = pWnd->GetDC(); //获取控件DC
	CRect rctWindowSize;//矩形类对象 rctWindowSize
	pWnd->GetClientRect(&rctWindowSize);//获取控件矩形区域
	m_img.StretchBlt(pc->m_hDC, 500, 0, rctWindowSize.Width(), rctWindowSize.Height(), SRCCOPY); //显示图片
	
	CFileDialog dlg(TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		_T("image files(*.jpg)|*.jpg|Worksheet Files|*.xls|All Files(*.*)|*.*||"),
		NULL);                            // 构造文件打开对话框  
	dlg.m_ofn.lpstrTitle = _T("Open Image");  // 文件打开对话框标题  
	if (IDOK != dlg.DoModal())                 // 判断是否成功选中文件  
		return;
	*/
	
	CString path ;     
	path = folderPath.c_str();// 获取文件路径  
	// TODO: 在此添加控件通知处理程序代码
	CPaintDC dc(this); // device context for painting

	IPicture* ppic = NULL;
	HRESULT  hr;
	hr = OleLoadPicturePath((CComBSTR)path.GetBuffer(), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&ppic);
	if (SUCCEEDED(hr))
	{
		ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
		CDC* pdc = GetDC();

		OLE_XPOS_HIMETRIC xSrc = 0;  // 图片中当前显示区域的x
		OLE_YPOS_HIMETRIC ySrc = 0;  // 图片中当前显示区域的y
		OLE_XSIZE_HIMETRIC cxSrc = 178; // 图片中当前显示区域的宽度
		OLE_YSIZE_HIMETRIC cySrc = 218; // 图片中当前显示区域的高度
		ppic->get_Width(&cxSrc);
		ppic->get_Height(&cySrc);

		ppic->Render(*pdc, 410, 10, 178, 218, 0, cySrc, cxSrc, -cySrc, NULL);//显示图片

		ppic->Release();
		ReleaseDC(pdc);
		ppic = NULL;

	}
}


void Ctest2Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


String haarfile = "C:\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml";

void Ctest2Dlg::OnBnClickedButton6()
{
	if (!cascade.load(haarfile)) {
		printf("coulud not load image...\n");

	}
	Mat srcImage, grayImage, dstImage;
	// 【2】读取图片
	srcImage = imread(path1);
	dstImage = srcImage.clone();
	//imshow("原图", srcImage);
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY); // 生成灰度图，提高检测效率
	Scalar colors[] =
	{
		
		CV_RGB(0, 255, 0),
		
	};
	// 【3】检测
	vector<Rect> rect;
	cascade.detectMultiScale(grayImage, rect, 1.1, 3, 0);  // 分类器对象调用
	printf("检测到人脸个数：%d\n", rect.size()); // 将识别的人脸的数量显示在控制台中
	// 【4】标记--在脸部画圆
	for (int i = 0; i < rect.size(); i++)
	{
		Point  center;
		int radius;
		center.x = cvRound((rect[i].x + rect[i].width * 0.5));
		center.y = cvRound((rect[i].y + rect[i].height * 0.5));
		radius = cvRound((rect[i].width + rect[i].height) * 0.25);
		circle(dstImage, center, radius, colors[i % 7], 2);

		// 【5】显示
		imshow("【人脸识别detectMultiScale】", dstImage);

		waitKey(0);
	
	}

}


void Ctest2Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
