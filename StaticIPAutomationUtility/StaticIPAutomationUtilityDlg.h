// StaticIPAutomationUtilityDlg.h : header file
//

#include <string>

using std::string;

#pragma once

#define TRUE 1
#define FALSE 0

#define FIRST_PART 0
#define SECOND_PART 1
#define THIRD_PART 2
#define FOURTH_PART 3

#define DATA_FILE_NAME "STATIC_IP_UTILITY.DAT"
#define APP_ACTION "open"
#define APP_NAME "netsh.exe"

#define MSG_BOX_TITLE "Static IP Utility"
#define MSG_BOX_TEXT_OFFICE_IP "Office IP Configuration Complete"
#define MSG_BOX_TEXT_OFFICE_DNS "Office DNS Configuration Complete"
#define MSG_BOX_TEXT_HOME_IP "Home IP Configuration Complete"
#define MSG_BOX_TEXT_HOME_DNS "Home DNS Configuration Complete"
#define READY_TEXT "Ready"
#define WORKING_TEXT "Working..."
#define CONTENTS_NOT_VALID "Invalid characters entered"
#define CONTENTS_VALID "Input valid thus far"
#define ENTER_CONNECTION_MSG "Enter Connection Name"
#define BLANK_STRING ""
#define DOT "."

#define DELAY_MILLI_SECONDS 5000
#define MAX_TEXT_LENGTH 100

/** Structure to store an IP address */
typedef struct _IP_ADDRESS_
{
	BYTE byte_one;
	BYTE byte_two;
	BYTE byte_three;
	BYTE byte_four;
}IP_ADDRESS;

/** A full set of IP addresses required for configuration */
typedef struct _IP_CONFIG_SET_
{
	IP_ADDRESS static_ip_address;
	IP_ADDRESS subnet_mask;
	IP_ADDRESS default_gateway;
	IP_ADDRESS preferred_dns;
	IP_ADDRESS alternate_dns;
}IP_CONFIG_SET;

/** Structure for storing the application's configuration */
typedef struct _IP_CONFIGURATION_
{
	IP_CONFIG_SET home_config;
	IP_CONFIG_SET office_config;
	char lan_connection_name[MAX_TEXT_LENGTH];
}IP_CONFIGURATION;

// CStaticIPAutomationUtilityDlg dialog
class CStaticIPAutomationUtilityDlg : public CDialog
{
// Construction
public:
	CStaticIPAutomationUtilityDlg(CWnd* pParent = NULL);	// standard constructor
	~CStaticIPAutomationUtilityDlg();

// Dialog Data
	enum { IDD = IDD_STATICIPAUTOMATIONUTILITY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	/** LAN Connection Name */
	afx_msg void OnEnChangeEditLanConnectionName();

	/** Home Settings */

	/** IP Address boxes kill focus call backs */
	afx_msg void OnIpnFieldchangedIpaddressHomeSubnetMask(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnIpnFieldchangedIpaddressHomeDefaultGateway(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnIpnFieldchangedIpaddressHomePreferredDns(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnIpnFieldchangedIpaddressHomeAlternateDns(NMHDR *pNMHDR, LRESULT *pResult);

	/** Activate and Delete buttons callbacks */
	afx_msg void OnBnClickedButtonActivateHomeSettings();
	afx_msg void OnBnClickedButtonActivateHomeDNSSettings();

	/** Office Settings */
	
	/** IP Address boxes kill focus call backs */
	afx_msg void OnIpnFieldchangedIpaddressOfficeIpaddress(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnIpnFieldchangedIpaddressOfficeSubnetMask(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnIpnFieldchangedIpaddressOfficeDefaultGateway(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnIpnFieldchangedIpaddressOfficePreferredDns(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnIpnFieldchangedIpaddressOfficeAlternateDns(NMHDR *pNMHDR, LRESULT *pResult);

	/** Activate and Delete buttons callbacks */
	afx_msg void OnBnClickedButtonActivateOfficeSettings();
	afx_msg void OnBnClickedButtonActivateOfficeDNSSettings();

private:
	IP_CONFIGURATION m_AppConfig;

	afx_msg void OnIpnFieldchangedIpaddressHomeIpaddress(NMHDR *pNMHDR, LRESULT *pResult);

	void AssignIPAddress(IP_ADDRESS& aStructIP, LPNMIPADDRESS aActualIP);
	void AssignIPAddress(CIPAddressCtrl* aIPAddressPtr, IP_ADDRESS& aStructIP);

	string GetIPAsString(IP_ADDRESS& aStructIP);
	void SaveValues();
	void ReloadValues();
	afx_msg void OnEnSetfocusEditLanConnectionName();
	afx_msg void OnEnKillfocusEditLanConnectionName();
};
