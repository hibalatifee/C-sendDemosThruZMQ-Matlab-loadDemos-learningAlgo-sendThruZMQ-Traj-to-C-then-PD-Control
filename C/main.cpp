//#ifdef __windows__
//#undef __windows__
//#endif

#define _AFXDLL

#include<conio.h>
#include "Phantom_omni.h" // Phantom headerfile (containing all callbacks and functions)

using namespace std;
#pragma warning(disable:4996)
//-----------------------------------------------------------------------------------------
#include <afxwin.h>      //MFC core and standard components
#include "resource.h"    //main symbols
//-----------------------------------------------------------------------------------------

#include <zmq.h>

//Globals
CButton * p_start;
CButton * p_init;
CButton * p_calib;
CButton * phan_stop;

CButton * bring_Traj;
CButton * p_stop;

CEdit   * p_edit;

CStatic * p_disp;
CStatic * p_mf;
CStatic * p_sv;

		double px=0;
		double py=0;
		double pz=0;
		double val=0;
		char message [20000]={};
		void *context1 = zmq_ctx_new();

class Phantom : public CDialog
{
public:
	Phantom(CWnd* pParent = NULL) : CDialog(Phantom::IDD, pParent)
	{}
	// Dialog Data, name of dialog form
	enum { IDD = IDD_DIALOG1};
protected:
	virtual void DoDataExchange(CDataExchange* pDX) 
	
	{ CDialog::DoDataExchange(pDX); }
	//Called right after constructor. Initialize things here.

	virtual BOOL OnInitDialog()
	{
		CDialog::OnInitDialog();
	
		p_start = (CButton *)GetDlgItem(IDC_BUTTON4);
		p_calib = (CButton *)GetDlgItem(IDC_BUTTON3);
		p_init =  (CButton *)GetDlgItem(IDC_BUTTON2);
		phan_stop = (CButton *)GetDlgItem(IDC_BUTTON5);

		bring_Traj = (CButton *)GetDlgItem(CB_camera);
		p_stop =(CButton *)GetDlgItem(CB_stop);
		
			return true;
	}
public:


	DECLARE_MESSAGE_MAP()
	//afx_msg void OnBnClickedstart();
	//afx_msg void OnBnClickedinitiliaze();
	//afx_msg void OnBnClickedcalibarate();
	afx_msg void OnBnClickedstop();
	//afx_msg void OnPaint();

	afx_msg void OnBnClickedcamera();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
//---------------------------------------------------------------------
class Phantom_winapp : public CWinApp
{
public:
	Phantom_winapp() {  }
public:
	virtual BOOL InitInstance()
	{
		CWinApp::InitInstance();
		Phantom dlg;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		return FALSE;
	} //close function

};
//-----------------------For Message Handlers, identifiers and macros---------------------------
//Need a Message Map Macro for both CDialog and CWinApp
BEGIN_MESSAGE_MAP(Phantom, CDialog)   // phantom is owner class name, CDialog is a base class name

	//ON_BN_CLICKED(CB_start, &Phantom::OnBnClickedstart)
	//ON_BN_CLICKED(CB_initiliaze, &Phantom::OnBnClickedinitiliaze)
	//ON_BN_CLICKED(CB_calibarate, &Phantom::OnBnClickedcalibarate)
	


	ON_BN_CLICKED(CB_camera, &Phantom::OnBnClickedcamera)
	ON_BN_CLICKED(CB_stop, &Phantom::OnBnClickedstop)
	ON_BN_CLICKED(IDCANCEL, &Phantom::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &Phantom::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Phantom::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Phantom::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &Phantom::OnBnClickedButton5)
END_MESSAGE_MAP()
//-----------------------------------------------------------------------------------------


Phantom_winapp  theApp;  //Starts the Application

/*

void Phantom::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	char str[50];
	double time = 0;
	int x1 = 40;
	int y1 = 150;

	int x2 = 220;
	int y2 = 150;

	int x3 = 40;
	int y3 = 370;

	int x4 = 220;
	int y4 = 370;

	//if (Phantom_Started)
	{
		//master 1
		dc.TextOut(x1 - 20, y1, "Position [mm]:");
		sprintf(str, "X %3.1f", mst.position[0]);
		dc.TextOut(x1, y1 + 20, str);
		sprintf(str, "Y %3.1f", mst.position[1]);
		dc.TextOut(x1, y1 + 40, str);
		sprintf(str, "Z %3.1f", mst.position[2]);
		dc.TextOut(x1, y1 + 60, str);
	
	}
	CDialog::OnPaint();
}
*/


//void Phantom::OnBnClickedstart()
//{
	// TODO: Add your control notification handler code here
	//p_disp = (CStatic *)GetDlgItem(CS_disp);
	//p_disp->SetWindowText(L" You pressed Start Button");
	//omni_start();
	//sprintf(publish, "%0.5f %0.5f %0.5f", slv.position[0] , slv.position[1] , slv.position[2]);
	//zmq_send(publisher, publish, 50, 0);
//}

//void Phantom::OnBnClickedinitiliaze()
//{
	// TODO: Add your control notification handler code here
	//omni_init();
	
	//zmq_bind(publisher, "tcp://*:5556");

	//AllocConsole();
	//freopen("CONOUT$", "w", stdout);  //reopen stream with different file or mode 
	//freopen("CONIN$", "r", stdout); //reading from console window  
	
	//p_init = (CButton *)GetDlgItem(CB_initiliaze);
	//p_init->EnableWindow(FALSE);
//}


//void Phantom::OnBnClickedcalibarate()
//{
	// TODO: Add your control notification handler code here
	//omni_calibarate();

	//p_calib = (CButton *)GetDlgItem(CB_calibarate);
	//p_calib->EnableWindow(FALSE);

	
//}

void Phantom::OnBnClickedcamera()
{
		//double PX [20000]={};
		//double PY [20000]={};
		//double PZ [20000]={};
	
		AllocConsole();
		freopen("CONOUT$", "w", stdout);

		//double PX [20000]={};
		//double PY [20000]={};
		//double PZ [20000]={};
		
		//int i=0;

    //  Connect our subscriber socket
	void *subscriber = zmq_socket(context1, ZMQ_SUB);
	
	cout <<"Connecting to the publisher"<< endl;
	zmq_connect(subscriber, "tcp://localhost:5581");
	zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE,"",0);

    while (1) {
		
		cout <<"Message:"<< endl;
		zmq_recv (subscriber, message, 20000, 0);
		cout << message<< endl;
		if (strncmp("EN", message, 2) == 0) 
            break;

		char *token;
		char *rest=message;

		token=strtok_s(rest, " ", &rest);
		px=atof(token);
		

		token=strtok_s(rest, " ", &rest);
		py=atof(token);
	    
		token=strtok_s(rest, " ", &rest);
		pz=atof(token);

		cout<<"Recieved Position Px="<<px<<" Py="<<py<<" Pz="<<pz<<  endl;
		PX[i]=px;
		PY[i]=py; 
		PZ[i]=pz; 

	i++;
    }
		zmq_disconnect(subscriber,"tcp://localhost:5581");
		zmq_close (subscriber);
}


void Phantom::OnBnClickedstop()
{

		//close();
		zmq_ctx_destroy (context1);
		zmq_ctx_term (context1);
		FreeConsole();
}


void Phantom::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	omni_init();
	

	AllocConsole();
	freopen("CONOUT$", "w", stdout);  //reopen stream with different file or mode 
	//freopen("CONIN$", "r", stdout); //reading from console window  
	
	p_init = (CButton *)GetDlgItem(IDC_BUTTON2);
	p_init->EnableWindow(FALSE);
}


void Phantom::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	omni_calibarate();

	p_calib = (CButton *)GetDlgItem(IDC_BUTTON3);
	p_calib->EnableWindow(FALSE);

}


void Phantom::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	omni_start();
}


void Phantom::OnBnClickedButton5()
{
	close();
	FreeConsole();
}


void Phantom::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
