#define KX_KXSLIP_CREATE_MAIN_VERSION 1
#define KX_KXSLIP_CREATE_SUB_VERSION 1
#define KX_KXSLIP_CREATE_VERSION ((KX_KXSLIP_CREATE_MAIN_VERSION << 16) + KX_KXSLIP_CREATE_SUB_VERSION)
#pragma once
#include <QObject>
#include "opencv2/opencv.hpp"
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
	virtual void GetLastMsg(int type, QString Msg) = 0;
	virtual void SetPath(QString model_path,QString print_path)=0;
	virtual void GetPath(QString& model_path, QString& print_path)=0;
	virtual bool GenerateQRcode(QString QRtempstr, cv::Mat& img)=0;
	virtual int GenerateSlipInfo(SLIP_PRINT_INFO slip_info, cv::Mat& img)=0;
	virtual bool PrePrint(cv::Mat& img)=0;
	virtual bool Print()=0;
};
CODE_LIB_EXPORT QKXSlipCreate * _stdcall QKXSlipCreateInstance(int version = KX_KXSLIP_CREATE_VERSION);