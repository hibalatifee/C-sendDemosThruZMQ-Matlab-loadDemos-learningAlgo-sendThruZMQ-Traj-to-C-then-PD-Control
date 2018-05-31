#include <afxwin.h>      //MFC core and standard components
#include "resource.h"    //main symbols

#include "Phantom_omni.h" // Phantom headerfile (containing all callbacks and functions)

#define _AFXDLL
#include<conio.h>

//-----------------------------------------------------------------------------------------
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
	afx_msg void OnBnClickedstop();

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


void Phantom::OnBnClickedcamera()
{
		//double PX [20000]={};
		//double PY [20000]={};
		//double PZ [20000]={};
	
		//AllocConsole();
		//freopen("CONOUT$", "w", stdout);
		//comm();
		//double PX [20000]={};
		//double PY [20000]={};
		//double PZ [20000]={};
		
		//int i=0;

    //  Connect our subscriber socket
	/*void *subscriber = zmq_socket(context1, ZMQ_SUB);
	
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
*/
}


void Phantom::OnBnClickedstop()
{

		//stopComm();
}


void Phantom::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	omni_init();

	AllocConsole();
	freopen("CONOUT$", "w", stdout);  //reopen stream with different file or mode 
	//freopen("CONIN$", "r", stdout); //reading from console window  
	
	openFile();
	
	//p_init = (CButton *)GetDlgItem(IDC_BUTTON2);
	//p_init->EnableWindow(FALSE);
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
