// StaticIPAutomationUtilityDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StaticIPAutomationUtility.h"
#include "StaticIPAutomationUtilityDlg.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using std::ios;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using std::string;
using std::stringstream;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CStaticIPAutomationUtilityDlg dialog




CStaticIPAutomationUtilityDlg::CStaticIPAutomationUtilityDlg(CWnd* pParent /*=NULL*/)
: CDialog(CStaticIPAutomationUtilityDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	memset(&m_AppConfig.home_config, 0, sizeof(IP_CONFIG_SET));
	memset(&m_AppConfig.office_config, 0, sizeof(IP_CONFIG_SET));

	for(int index=0; index<MAX_TEXT_LENGTH; ++index)
		m_AppConfig.lan_connection_name[index] = '\0';
}

CStaticIPAutomationUtilityDlg::~CStaticIPAutomationUtilityDlg()
{
	SaveValues();
}

void CStaticIPAutomationUtilityDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStaticIPAutomationUtilityDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	/** Home Settings */
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS_HOME_IPADDRESS, &CStaticIPAutomationUtilityDlg::OnIpnFieldchangedIpaddressHomeIpaddress)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS_HOME_SUBNET_MASK, &CStaticIPAutomationUtilityDlg::OnIpnFieldchangedIpaddressHomeSubnetMask)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS_HOME_DEFAULT_GATEWAY, &CStaticIPAutomationUtilityDlg::OnIpnFieldchangedIpaddressHomeDefaultGateway)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS_HOME_PREFERRED_DNS, &CStaticIPAutomationUtilityDlg::OnIpnFieldchangedIpaddressHomePreferredDns)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS_HOME_ALTERNATE_DNS, &CStaticIPAutomationUtilityDlg::OnIpnFieldchangedIpaddressHomeAlternateDns)

	ON_BN_CLICKED(IDC_BUTTON_ACTIVATE_HOME_IP_SETTINGS, &CStaticIPAutomationUtilityDlg::OnBnClickedButtonActivateHomeSettings)
	ON_BN_CLICKED(IDC_BUTTON_ACTIVATE_HOME_DNS_SETTINGS, &CStaticIPAutomationUtilityDlg::OnBnClickedButtonActivateHomeDNSSettings)

	/** Office Settings */
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS_OFFICE_IPADDRESS, &CStaticIPAutomationUtilityDlg::OnIpnFieldchangedIpaddressOfficeIpaddress)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS_OFFICE_SUBNET_MASK, &CStaticIPAutomationUtilityDlg::OnIpnFieldchangedIpaddressOfficeSubnetMask)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS_OFFICE_DEFAULT_GATEWAY, &CStaticIPAutomationUtilityDlg::OnIpnFieldchangedIpaddressOfficeDefaultGateway)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS_OFFICE_PREFERRED_DNS, &CStaticIPAutomationUtilityDlg::OnIpnFieldchangedIpaddressOfficePreferredDns)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS_OFFICE_ALTERNATE_DNS, &CStaticIPAutomationUtilityDlg::OnIpnFieldchangedIpaddressOfficeAlternateDns)

	ON_BN_CLICKED(IDC_BUTTON_ACTIVATE_OFFICE_IP_SETTINGS, &CStaticIPAutomationUtilityDlg::OnBnClickedButtonActivateOfficeSettings)
	ON_BN_CLICKED(IDC_BUTTON_ACTIVATE_OFFICE_DNS_SETTINGS, &CStaticIPAutomationUtilityDlg::OnBnClickedButtonActivateOfficeDNSSettings)
	ON_EN_CHANGE(IDC_EDIT_LAN_CONNECTION_NAME, &CStaticIPAutomationUtilityDlg::OnEnChangeEditLanConnectionName)
	ON_EN_SETFOCUS(IDC_EDIT_LAN_CONNECTION_NAME, &CStaticIPAutomationUtilityDlg::OnEnSetfocusEditLanConnectionName)
	ON_EN_KILLFOCUS(IDC_EDIT_LAN_CONNECTION_NAME, &CStaticIPAutomationUtilityDlg::OnEnKillfocusEditLanConnectionName)
END_MESSAGE_MAP()


// CStaticIPAutomationUtilityDlg message handlers

BOOL CStaticIPAutomationUtilityDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	ReloadValues();
	SetDlgItemTextW(IDC_STATUS_HOME,_T(READY_TEXT));
	SetDlgItemTextW(IDC_STATUS_OFFICE,_T(READY_TEXT));
	
	if(strcmp(m_AppConfig.lan_connection_name,ENTER_CONNECTION_MSG))
		strcpy(m_AppConfig.lan_connection_name,ENTER_CONNECTION_MSG);

	SetDlgItemTextA(m_hWnd, IDC_EDIT_LAN_CONNECTION_NAME, m_AppConfig.lan_connection_name);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStaticIPAutomationUtilityDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStaticIPAutomationUtilityDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStaticIPAutomationUtilityDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/** General Private Functions */

void CStaticIPAutomationUtilityDlg::AssignIPAddress(IP_ADDRESS& aStructIP, LPNMIPADDRESS aActualIP)
{
	switch(aActualIP->iField)
	{
	case FIRST_PART:
		{
			aStructIP.byte_one = aActualIP->iValue;
			break;
		}
	case SECOND_PART:
		{
			aStructIP.byte_two = aActualIP->iValue;
			break;
		}
	case THIRD_PART:
		{
			aStructIP.byte_three = aActualIP->iValue;
			break;
		}
	case FOURTH_PART:
		{
			aStructIP.byte_four = aActualIP->iValue;
			break;
		}
	}
}

/** Takes an IP_ADDRESS struct as parameter and returns the IP address it contains as a string */
string CStaticIPAutomationUtilityDlg::GetIPAsString(IP_ADDRESS& aStructIP)
{
	stringstream ipAddress;
	int temp = 0;

	ipAddress << BLANK_STRING;

	temp = static_cast<int>(aStructIP.byte_one);
	ipAddress << temp;
	ipAddress << DOT;

	temp = static_cast<int>(aStructIP.byte_two);
	ipAddress << temp;
	ipAddress << DOT;

	temp = static_cast<int>(aStructIP.byte_three);
	ipAddress << temp;
	ipAddress << DOT;

	temp = static_cast<int>(aStructIP.byte_four);
	ipAddress << temp;

	return ipAddress.str();
}

/** Saves the values to a .dat file */
void CStaticIPAutomationUtilityDlg::SaveValues()
{
	ofstream outputFile(DATA_FILE_NAME, ios::binary);
	if(outputFile.good())
	{	
		outputFile.write(reinterpret_cast<char*>(&m_AppConfig), sizeof(IP_CONFIGURATION));
	}
	outputFile.close();	
}

void CStaticIPAutomationUtilityDlg::ReloadValues()
{
	//memset(&m_AppConfig, 0, sizeof(IP_CONFIGURATION));

	ifstream inputFile(DATA_FILE_NAME, ios::binary);
	if(inputFile.good())
	{
		inputFile.read(reinterpret_cast<char*>(&m_AppConfig), sizeof(IP_CONFIGURATION));
	}
	inputFile.close();

	CIPAddressCtrl* ipAddressPtr = NULL;

	/** Connection Name */
	SetDlgItemTextA(m_hWnd, IDC_EDIT_LAN_CONNECTION_NAME, m_AppConfig.lan_connection_name);

	/** Home Configuration */

	/** Static IP Address */
	ipAddressPtr = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_HOME_IPADDRESS);
	AssignIPAddress(ipAddressPtr, m_AppConfig.home_config.static_ip_address);

	/** Subnet Mask */
	ipAddressPtr = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_HOME_SUBNET_MASK);
	AssignIPAddress(ipAddressPtr, m_AppConfig.home_config.subnet_mask);

	/** Default Gateway */
	ipAddressPtr = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_HOME_DEFAULT_GATEWAY);
	AssignIPAddress(ipAddressPtr, m_AppConfig.home_config.default_gateway);

	/** Preferred DNS */
	ipAddressPtr = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_HOME_PREFERRED_DNS);
	AssignIPAddress(ipAddressPtr, m_AppConfig.home_config.preferred_dns);

	/** Alternate DNS */
	ipAddressPtr = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_HOME_ALTERNATE_DNS);
	AssignIPAddress(ipAddressPtr, m_AppConfig.home_config.alternate_dns);

	/** Office Configuration */

	/** Static IP Address */
	ipAddressPtr = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_OFFICE_IPADDRESS);
	AssignIPAddress(ipAddressPtr, m_AppConfig.office_config.static_ip_address);

	/** Subnet Mask */
	ipAddressPtr = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_OFFICE_SUBNET_MASK);
	AssignIPAddress(ipAddressPtr, m_AppConfig.office_config.subnet_mask);

	/** Default Gateway */
	ipAddressPtr = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_OFFICE_DEFAULT_GATEWAY);
	AssignIPAddress(ipAddressPtr, m_AppConfig.office_config.default_gateway);

	/** Preferred DNS */
	ipAddressPtr = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_OFFICE_PREFERRED_DNS);
	AssignIPAddress(ipAddressPtr, m_AppConfig.office_config.preferred_dns);

	/** Alternate DNS */
	ipAddressPtr = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS_OFFICE_ALTERNATE_DNS);
	AssignIPAddress(ipAddressPtr, m_AppConfig.office_config.alternate_dns);
}

void CStaticIPAutomationUtilityDlg::AssignIPAddress(CIPAddressCtrl* aIPAddressPtr, IP_ADDRESS& aStructIP)
{
	aIPAddressPtr->SetAddress(aStructIP.byte_one, aStructIP.byte_two, aStructIP.byte_three, aStructIP.byte_four);
}

/** Home Settings */

/** Address Change Event Functions */

void CStaticIPAutomationUtilityDlg::OnIpnFieldchangedIpaddressHomeIpaddress(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	AssignIPAddress(m_AppConfig.home_config.static_ip_address, pIPAddr);
	*pResult = 0;
}

void CStaticIPAutomationUtilityDlg::OnIpnFieldchangedIpaddressHomeSubnetMask(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	AssignIPAddress(m_AppConfig.home_config.subnet_mask, pIPAddr);
	*pResult = 0;
}

void CStaticIPAutomationUtilityDlg::OnIpnFieldchangedIpaddressHomeDefaultGateway(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	AssignIPAddress(m_AppConfig.home_config.default_gateway, pIPAddr);
	*pResult = 0;
}

void CStaticIPAutomationUtilityDlg::OnIpnFieldchangedIpaddressHomePreferredDns(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	AssignIPAddress(m_AppConfig.home_config.preferred_dns, pIPAddr);
	*pResult = 0;
}

void CStaticIPAutomationUtilityDlg::OnIpnFieldchangedIpaddressHomeAlternateDns(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	AssignIPAddress(m_AppConfig.home_config.alternate_dns, pIPAddr);
	*pResult = 0;
}

/** Activate Settings button */
void CStaticIPAutomationUtilityDlg::OnBnClickedButtonActivateHomeSettings()
{
	/** Actual Command to set IP address, Subnet Mask, Default Gateway */
		// interface ip set address "Office" static 115.252.102.204 255.255.255.224 115.252.102.193 1
	
	/** Actual command  */
		// netsh interface ip set dns "Office" static 124.124.5.140

	if(strcmp(m_AppConfig.lan_connection_name, ENTER_CONNECTION_MSG))
	{
		SetDlgItemTextW(IDC_STATUS_HOME,_T(WORKING_TEXT));

		/** Retrieving the name of the LAN Connection */
		char enteredText[MAX_TEXT_LENGTH];
		GetDlgItemTextA(m_hWnd, IDC_EDIT_LAN_CONNECTION_NAME, enteredText, sizeof(enteredText));

		/** Creating the string for static IP Configuration */
		string toExecute = "interface ip set address \"";
		toExecute += enteredText;
		toExecute += "\"  static ";

		/** Creating the string for static IP Configuration */
		//string toExecute = "interface ip set address \"Office\"  static ";
		toExecute += GetIPAsString(m_AppConfig.home_config.static_ip_address);
		toExecute += " ";
		toExecute += GetIPAsString(m_AppConfig.home_config.subnet_mask);
		toExecute += " ";
		toExecute += GetIPAsString(m_AppConfig.home_config.default_gateway);
		toExecute += " 1";

		/** Forming the Wide Character string */
		int len = static_cast<int>(strlen(toExecute.c_str()) + 1);
		wchar_t *wText = new wchar_t[len];
		if ( wText == 0 )
			return;
		memset(wText,0,len);
		::MultiByteToWideChar( CP_ACP, NULL, toExecute.c_str(), -1, wText, len );

		/** Setting the static IP Configuration */
		ShellExecute(NULL, _T(APP_ACTION), _T(APP_NAME), wText, NULL, SW_HIDE);

		delete []wText;
		Sleep(DELAY_MILLI_SECONDS);

		SetDlgItemTextW(IDC_STATUS_HOME,_T(READY_TEXT));
		MessageBox(_T(MSG_BOX_TEXT_HOME_IP), _T(MSG_BOX_TITLE), MB_OK);
	}
}

/** Delete Saved Settings button */
void CStaticIPAutomationUtilityDlg::OnBnClickedButtonActivateHomeDNSSettings()
{
	if(strcmp(m_AppConfig.lan_connection_name, ENTER_CONNECTION_MSG))
	{
		SetDlgItemTextW(IDC_STATUS_HOME,_T(WORKING_TEXT));

		/** Retrieving the name of the LAN Connection */
		char enteredText[MAX_TEXT_LENGTH];
		GetDlgItemTextA(m_hWnd, IDC_EDIT_LAN_CONNECTION_NAME, enteredText, sizeof(enteredText));

		/** Creating the string for static IP Configuration */
		string toExecuteDNS = "interface ip set dns \"";
		toExecuteDNS += enteredText;
		toExecuteDNS += "\"  static ";

		/** Creating the string for DNS Configuration */
		//string toExecuteDNS = "interface ip set dns \"Office\" static ";
		toExecuteDNS += GetIPAsString(m_AppConfig.home_config.preferred_dns);

		/** Forming the Wide Character string */
		int lenDNS = static_cast<int>(strlen(toExecuteDNS.c_str()) + 1);
		wchar_t *wTextDNS = new wchar_t[lenDNS];
		if ( wTextDNS == 0 )
			return;
		memset(wTextDNS,0,lenDNS);
		::MultiByteToWideChar( CP_ACP, NULL, toExecuteDNS.c_str(), -1, wTextDNS, lenDNS );

		/** Setting the static IP Configuration */
		ShellExecute(NULL, _T(APP_ACTION), _T(APP_NAME), wTextDNS, NULL, SW_HIDE);

		delete []wTextDNS;
		Sleep(DELAY_MILLI_SECONDS);

		SetDlgItemTextW(IDC_STATUS_HOME,_T(READY_TEXT));
		MessageBox(_T(MSG_BOX_TEXT_HOME_DNS), _T(MSG_BOX_TITLE), MB_OK);
	}
}

/** Office Settings */

/** Address Change Event Functions */

void CStaticIPAutomationUtilityDlg::OnIpnFieldchangedIpaddressOfficeIpaddress(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	AssignIPAddress(m_AppConfig.office_config.static_ip_address, pIPAddr);
	*pResult = 0;
}

void CStaticIPAutomationUtilityDlg::OnIpnFieldchangedIpaddressOfficeSubnetMask(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	AssignIPAddress(m_AppConfig.office_config.subnet_mask, pIPAddr);
	*pResult = 0;
}

void CStaticIPAutomationUtilityDlg::OnIpnFieldchangedIpaddressOfficeDefaultGateway(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	AssignIPAddress(m_AppConfig.office_config.default_gateway, pIPAddr);
	*pResult = 0;
}

void CStaticIPAutomationUtilityDlg::OnIpnFieldchangedIpaddressOfficePreferredDns(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	AssignIPAddress(m_AppConfig.office_config.preferred_dns, pIPAddr);
	*pResult = 0;
}

void CStaticIPAutomationUtilityDlg::OnIpnFieldchangedIpaddressOfficeAlternateDns(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	AssignIPAddress(m_AppConfig.office_config.alternate_dns, pIPAddr);
	*pResult = 0;
}

/** Activate Settings button */
void CStaticIPAutomationUtilityDlg::OnBnClickedButtonActivateOfficeSettings()
{
	/** Actual Command to set IP address, Subnet Mask, Default Gateway */
		// interface ip set address "Office" static 115.252.102.204 255.255.255.224 115.252.102.193 1
	
	/** Actual command  */
		// netsh interface ip set dns "Office" static 124.124.5.140

	if(strcmp(m_AppConfig.lan_connection_name, ENTER_CONNECTION_MSG))
	{
		SetDlgItemTextW(IDC_STATUS_OFFICE,_T(WORKING_TEXT));

		/** Retrieving the name of the LAN Connection */
		char enteredText[MAX_TEXT_LENGTH];
		GetDlgItemTextA(m_hWnd, IDC_EDIT_LAN_CONNECTION_NAME, enteredText, sizeof(enteredText));

		/** Creating the string for static IP Configuration */
		string toExecute = "interface ip set address \"";
		toExecute += enteredText;
		toExecute += "\"  static ";

		/** Creating the string for static IP Configuration */
		//string toExecute = "interface ip set address \"Office\"  static ";
		toExecute += GetIPAsString(m_AppConfig.office_config.static_ip_address);
		toExecute += " ";
		toExecute += GetIPAsString(m_AppConfig.office_config.subnet_mask);
		toExecute += " ";
		toExecute += GetIPAsString(m_AppConfig.office_config.default_gateway);
		toExecute += " 1";

		/** Forming the Wide Character string */
		int len = static_cast<int>(strlen(toExecute.c_str()) + 1);
		wchar_t *wText = new wchar_t[len];
		if ( wText == 0 )
			return;
		memset(wText,0,len);
		::MultiByteToWideChar( CP_ACP, NULL, toExecute.c_str(), -1, wText, len );

		/** Setting the static IP Configuration */
		ShellExecute(NULL, _T(APP_ACTION), _T(APP_NAME), wText, NULL, SW_HIDE);

		delete []wText;
		Sleep(DELAY_MILLI_SECONDS);

		SetDlgItemTextW(IDC_STATUS_OFFICE,_T(READY_TEXT));
		MessageBox(_T(MSG_BOX_TEXT_OFFICE_IP), _T(MSG_BOX_TITLE), MB_OK);
	}
}

/** Delete Saved Settings button */
void CStaticIPAutomationUtilityDlg::OnBnClickedButtonActivateOfficeDNSSettings()
{
	if(strcmp(m_AppConfig.lan_connection_name, ENTER_CONNECTION_MSG))
	{
		SetDlgItemTextW(IDC_STATUS_OFFICE,_T(WORKING_TEXT));

		/** Retrieving the name of the LAN Connection */
		char enteredText[MAX_TEXT_LENGTH];
		GetDlgItemTextA(m_hWnd, IDC_EDIT_LAN_CONNECTION_NAME, enteredText, sizeof(enteredText));

		/** Creating the string for static IP Configuration */
		string toExecuteDNS = "interface ip set dns \"";
		toExecuteDNS += enteredText;
		toExecuteDNS += "\"  static ";

		/** Creating the string for DNS Configuration */
		//string toExecuteDNS = "interface ip set dns \"Office\" static ";
		toExecuteDNS += GetIPAsString(m_AppConfig.office_config.preferred_dns);

		/** Forming the Wide Character string */
		int lenDNS = static_cast<int>(strlen(toExecuteDNS.c_str()) + 1);
		wchar_t *wTextDNS = new wchar_t[lenDNS];
		if ( wTextDNS == 0 )
			return;
		memset(wTextDNS, 0, lenDNS);
		::MultiByteToWideChar( CP_ACP, NULL, toExecuteDNS.c_str(), -1, wTextDNS, lenDNS );

		/** Setting the static IP Configuration */
		ShellExecute(NULL, _T(APP_ACTION), _T(APP_NAME), wTextDNS, NULL, SW_HIDE);

		delete []wTextDNS;
		Sleep(DELAY_MILLI_SECONDS);

		SetDlgItemTextW(IDC_STATUS_OFFICE,_T(READY_TEXT));
		MessageBox(_T(MSG_BOX_TEXT_OFFICE_DNS), _T(MSG_BOX_TITLE), MB_OK);
	}
}

void CStaticIPAutomationUtilityDlg::OnEnChangeEditLanConnectionName()
{
	/** Retrieving the name of the LAN Connection */
	char enteredText[MAX_TEXT_LENGTH];
	for(int index=0 ; index< MAX_TEXT_LENGTH; ++index)
		enteredText[index] = 0;

	enteredText[0] = '\0';

	GetDlgItemTextA(m_hWnd, IDC_EDIT_LAN_CONNECTION_NAME, enteredText, sizeof(enteredText));
	int length = static_cast<int>(strlen(enteredText));

	if(!strstr(enteredText, ENTER_CONNECTION_MSG))
	{
		bool contentsValid = true;
		for(int i=0; i<length; ++i)
		{
			if( enteredText[i] == '.' || enteredText[i] == ',' || enteredText[i] == '+' || enteredText[i] == '=' || enteredText[i] == '-' || 
				enteredText[i] == '_' || enteredText[i] == '!' || enteredText[i] == '@' || enteredText[i] == '#' || enteredText[i] == '$' || 
				enteredText[i] == '%' || enteredText[i] == '^' || enteredText[i] == '&' || enteredText[i] == '*' || enteredText[i] == '(' || 
				enteredText[i] == ')' || enteredText[i] == ':' || enteredText[i] == ';' || enteredText[i] == '{' || enteredText[i] == '}' || 
				enteredText[i] == '|' || enteredText[i] == '?' || enteredText[i] == '<' || enteredText[i] == '>' || enteredText[i] == '/' || 
				enteredText[i] == '"' || enteredText[i] == ' '|| enteredText[i] == '\\' ||enteredText[i] == '\''
				)
			{
				contentsValid = false;
			}
		}

		if(!contentsValid)
		{
			SetDlgItemTextW(IDC_STATIC_INPUT_CHECK,_T(CONTENTS_NOT_VALID));
		}
		else if(contentsValid)
		{
			SetDlgItemTextW(IDC_STATIC_INPUT_CHECK,_T(CONTENTS_VALID));
		}
	}
	else
	{
		SetDlgItemTextW(IDC_STATIC_INPUT_CHECK,_T(BLANK_STRING));
	}
}

void CStaticIPAutomationUtilityDlg::OnEnSetfocusEditLanConnectionName()
{
	SetDlgItemTextW(IDC_EDIT_LAN_CONNECTION_NAME,_T(BLANK_STRING));
}

void CStaticIPAutomationUtilityDlg::OnEnKillfocusEditLanConnectionName()
{
	/** Retrieving the name of the LAN Connection */
	char enteredText[MAX_TEXT_LENGTH];
	GetDlgItemTextA(m_hWnd, IDC_EDIT_LAN_CONNECTION_NAME, enteredText, sizeof(enteredText));

	if(!strcmp(enteredText, BLANK_STRING)) /** If the user hasn't entered anything */
	{
		SetDlgItemTextW(IDC_EDIT_LAN_CONNECTION_NAME,_T(ENTER_CONNECTION_MSG));
	}
	else
	{
		strcpy(m_AppConfig.lan_connection_name, enteredText);
	}
}
