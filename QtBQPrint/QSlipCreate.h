#pragma once
//#include <QObject>
#include "qrcode/qrencode.h"
#include <QDebug>
#include <QPainter>
#include <QColor>
#include <QRectF>
#include <QImage>
#include <QPixmap>
#include <QLibrary>
#include "QKXSlipCreate.h"
#pragma comment(lib,"winmm.lib")
#include <windows.h>
#include<fstream>
#include<iostream>

enum PRODECT_COUPONS_
{
	One_yuan = 1,
	Five_yuan = 5,
	Ten_yuan = 10,
	Twenty_yuan = 20,
	Fifty_yuan = 50,
	One_hundred_yuan = 100
};
enum GENERATE_ERR_
{
	GenerateSlip_OK = 0,           //�����ɹ�
	GenerateQRcode_failed = -1,    //���ɶ�ά��ʧ��
	CreateSlipInfo_failed = -2,    //���ɷ�ǩ����Ϣʧ��
	Save_image_failed = -3,        //���ɵķ�ǩ���浽����ʧ��
	Load_ModelImg_failed = -4,      //����ģ��ͼ��ʧ��
	Create_FQimg_failed = -5        //���ɷ�ǩͼ��ʧ��
};
class QSlipCreate : public QKXSlipCreate
{
	Q_OBJECT

public:
	QSlipCreate();
	~QSlipCreate();
	void GetLastMsg(int type, QString& Msg);
	void SetPath(QString model_path, QString print_path);
	void GetPath(QString& model_path, QString& print_path);
	bool GenerateQRcode(QString QRtempstr,cv::Mat& img);
	int GenerateSlipInfo(SLIP_PRINT_INFO slip_info, cv::Mat& img);
	bool PrePrint(cv::Mat& img);
	bool Print();

private:
	void putTextZH(cv::Mat &dst, const char* str, cv::Point org, cv::Scalar color, int fontSize,
		const char *fn = "Arial", bool italic = false, bool underline = false);
	bool save_bmp_image(const  cv::Mat img, std::string dst);
	int  mat_to_binary(const  cv::Mat img, int  line_byte, char * data);
	QString m_modelPath;
	QString m_printPath;
	cv::Mat m_modelImg;
	cv::Mat m_QRmat;
	cv::Mat m_SlipImg;
	QLibrary *m_tscdll;
};
