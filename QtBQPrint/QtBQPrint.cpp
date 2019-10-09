#include "QtBQPrint.h"
#include <QDateTime>
#include <QMessageBox>
#pragma execution_character_set("utf-8")

// typedef QKXSlipCreate * _stdcall QKXSlipCreateInstance(int version);
// static HMODULE hNetDLL;
QtBQPrint::QtBQPrint(QWidget *parent)
: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.dateEdit_date->setDisplayFormat("yyyy-MM-dd");
	ui.dateEdit_date->setDateTime(QDateTime::currentDateTime());
	ui.dateEdit_date->setCalendarPopup(true);
	ui.lineEdit_QRcode->setText("中国人abc123");
	ui.lineEdit_QBInfo->setText("100");
	ui.lineEdit_FHInfo->setText("张三三");
	ui.lineEdit_FQInfo->setText("李四四");
	m_Slip = QKXSlipCreateInstance();
}

void QtBQPrint::on_pushButton_CreateQR_clicked()
{
	QString tempStr = ui.lineEdit_QRcode->text();
	cv::Mat img;
	if (m_Slip->GenerateQRcode(tempStr, img))
	{
		cv::imshow("二维码", img);
	}
	else
	{
		QMessageBox::information(NULL, "INFO", "GenerateQRcode Failed");
	}

}

void QtBQPrint::on_pushButton_PrePrint_clicked()
{
	cv::Mat img;
	if (m_Slip->PrePrint(img))
	{
		cv::imshow("打印预览", img);
	}
	else
	{
		QMessageBox::information(NULL, "INFO", "PrePrint Failed");
	}

}

void QtBQPrint::on_pushButton_Print_clicked()
{
	if (m_Slip->Print())
	{
		QMessageBox::information(NULL, "INFO", "Link to DLL is OK!");
	}
	else
	{
		QMessageBox::information(NULL, "INFO", "Link to DLL is NOT!");
	}
}

void QtBQPrint::on_pushButton_CreateFQ_clicked()
{
	SLIP_PRINT_INFO print_info;
	print_info.QRStr = ui.lineEdit_QRcode->text();
	print_info.QBInfo = ui.lineEdit_QBInfo->text();
	QString str = ui.dateEdit_date->text();
	QString date = QString("%1年%2月%3日").arg(str.mid(0, 4)).arg(str.mid(5, 2)).arg(str.mid(8, 2));
	print_info.date = date;
	print_info.FHInfo = ui.lineEdit_FHInfo->text();
	print_info.FQInfo = ui.lineEdit_FQInfo->text();

	QString modelPath = "E:/FD_SHLIU/QtBQPrint/params/model.bmp";
	QString printPath = "E:/FD_SHLIU/QtBQPrint/params/print.bmp";
	m_Slip->SetPath(modelPath, printPath);
	cv::Mat img;
	int bRet = m_Slip->GenerateSlipInfo(print_info, img);
	if (bRet < 0)
	{
		switch (bRet)
		{
		case GENERATE_ERR_::GenerateQRcode_failed:
			QMessageBox::information(NULL, "INFO", "二维码生成失败!");
			break;
		case GENERATE_ERR_::CreateSlipInfo_failed:
			QMessageBox::information(NULL, "INFO", "封签信息生成失败!");
			break;
		case GENERATE_ERR_::Save_image_failed:
			QMessageBox::information(NULL, "INFO", "存储失败!");
			break;
		case GENERATE_ERR_::Load_ModelImg_failed:
			QMessageBox::information(NULL, "INFO", "加载模板图像失败!");
			break;
		case GENERATE_ERR_::Create_FQimg_failed:
			QMessageBox::information(NULL, "INFO", "生成封签图像失败!");
			break;
		default:
			break;
		}
	}
	else
	{
		cv::imshow("SlipImg", img);
	}

}

void QtBQPrint::on_pushButton_Test_clicked()
{

}
