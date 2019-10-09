#define KX_KXSLIP_CREATE_MAIN_VERSION 1
#define KX_KXSLIP_CREATE_SUB_VERSION 1
#define KX_KXSLIP_CREATE_VERSION ((KX_KXSLIP_CREATE_MAIN_VERSION << 16) + KX_KXSLIP_CREATE_SUB_VERSION)
#pragma once
#include <QObject>
#include "opencv2/opencv.hpp"

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
	Load_ModelImg_failed =-4,      //����ģ��ͼ��ʧ��
	Create_FQimg_failed =-5        //���ɷ�ǩͼ��ʧ��
};
struct SLIP_PRINT_INFO
{
	QString QRStr;
	QString QBInfo;
	QString date;
	QString FHInfo;
	QString FQInfo;
};
#define CODE_LIB_SOLUTION
#ifdef CODE_LIB_SOLUTION
#define CODE_LIB_EXPORT __declspec(dllexport)
#else
#define CODE_LIB_EXPORT __declspec(dllimport)
#endif

class   QKXSlipCreate : public QObject
{
	Q_OBJECT
public:
	virtual void SetPath(QString model_path,QString print_path)=0;
	virtual void GetPath(QString& model_path, QString& print_path)=0;
	virtual bool GenerateQRcode(QString QRtempstr, cv::Mat& img)=0;
	virtual int GenerateSlipInfo(SLIP_PRINT_INFO slip_info, cv::Mat& img)=0;
	virtual bool PrePrint(cv::Mat& img)=0;
	virtual bool Print()=0;
};
CODE_LIB_EXPORT QKXSlipCreate * _stdcall QKXSlipCreateInstance(int version = KX_KXSLIP_CREATE_VERSION);