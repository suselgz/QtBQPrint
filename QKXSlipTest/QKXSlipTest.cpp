#include "QKXSlipTest.h"
#pragma execution_character_set("utf-8")
QKXSlipTest::QKXSlipTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_KXSlip = QKXSlipCreateInstance();
	ui.dateEdit_date->setDisplayFormat("yyyy-MM-dd");
	ui.dateEdit_date->setDateTime(QDateTime::currentDateTime());
	ui.dateEdit_date->setCalendarPopup(true);
	ui.lineEdit_QRcode->setText("�й���abc123");
	ui.lineEdit_QBInfo->setText("100");
	ui.lineEdit_FHInfo->setText("������");
	ui.lineEdit_FQInfo->setText("������");
}

void QKXSlipTest::on_pushButton_CreateQR_clicked()
{
	QString tempStr = ui.lineEdit_QRcode->text();
	cv::Mat img;
	if (m_KXSlip->GenerateQRcode(tempStr, img))
	{
		cv::imshow("��ά��", img);
	}
	else
	{
		QMessageBox::information(NULL, "INFO", "GenerateQRcode Failed");
	}
}

void QKXSlipTest::on_pushButton_PrePrint_clicked()
{
	cv::Mat img;
	if (m_KXSlip->PrePrint(img))
	{
		cv::imshow("��ӡԤ��", img);
	}
	else
	{
		QMessageBox::information(NULL, "INFO", "PrePrint Failed");
	}
}

void QKXSlipTest::on_pushButton_Print_clicked()
{
	if (m_KXSlip->Print())
	{
		QMessageBox::information(NULL, "INFO", "Link to DLL is OK!");
	}
	else
	{
		QMessageBox::information(NULL, "INFO", "Link to DLL is NOT!");
	}
}

void QKXSlipTest::on_pushButton_CreateFQ_clicked()
{
	SLIP_PRINT_INFO print_info;
	print_info.QRStr = ui.lineEdit_QRcode->text();
	print_info.QBInfo = ui.lineEdit_QBInfo->text();
	QString str = ui.dateEdit_date->text();
	QString date = QString("%1��%2��%3��").arg(str.mid(0, 4)).arg(str.mid(5, 2)).arg(str.mid(8, 2));
	print_info.date = date;
	print_info.FHInfo = ui.lineEdit_FHInfo->text();
	print_info.FQInfo = ui.lineEdit_FQInfo->text();

	QString modelPath = "E:/FD_SHLIU/QtBQPrint/params/model.bmp";
	QString printPath = "E:/FD_SHLIU/QtBQPrint/params/print.bmp";
	m_KXSlip->SetPath(modelPath, printPath);
	cv::Mat img;
	int bRet = m_KXSlip->GenerateSlipInfo(print_info, img);
	if (bRet < 0)
	{
		switch (bRet)
		{
		case GENERATE_ERR_::GenerateQRcode_failed:
			QMessageBox::information(NULL, "INFO", "��ά������ʧ��!");
			break;
		case GENERATE_ERR_::CreateSlipInfo_failed:
			QMessageBox::information(NULL, "INFO", "��ǩ��Ϣ����ʧ��!");
			break;
		case GENERATE_ERR_::Save_image_failed:
			QMessageBox::information(NULL, "INFO", "�洢ʧ��!");
			break;
		case GENERATE_ERR_::Load_ModelImg_failed:
			QMessageBox::information(NULL, "INFO", "����ģ��ͼ��ʧ��!");
			break;
		case GENERATE_ERR_::Create_FQimg_failed:
			QMessageBox::information(NULL, "INFO", "���ɷ�ǩͼ��ʧ��!");
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