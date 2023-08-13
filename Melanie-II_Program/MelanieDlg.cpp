// Melanie v2.0
// by Alejandro Alonso Puig
// April 2004
// mundobot.com
//
// MelanieDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Melanie.h"
#include "MelanieDlg.h"
#include <fstream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define LEG1	0
#define LEG2	1
#define LEG3	2
#define LEG4	3
#define LEG5	4
#define LEG6	5

#define LEGS	6

#define LENGTH	0
#define ANGLE	1
#define COORD	1
#define X		0
#define Y		1
#define Z		2
#define COXA	0
#define FEMUR	1
#define TIBIA	2


#define PI	3.141592653589793238

/////////////////////////////////////////////////////////////////////////////
// CMelanieDlg dialog

CMelanieDlg::CMelanieDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMelanieDlg::IDD, pParent)
{

	//I2C addresses for the different modules
	cAD1Add		= 144;		//Address of the I2C A/D Converter 1
	cAD2Add		= 146;		//Address of the I2C A/D Converter 2
	cAD3Add		= 148;		//Address of the I2C A/D Converter 3
	cAD4Add		= 150;		//Address of the I2C A/D Converter 4
	cAD5Add		= 152;		//Address of the I2C A/D Converter 5
	cAD6Add		= 154;		//Address of the I2C A/D Converter 6
	cAD7Add		= 156;		//Address of the I2C A/D Converter 7
	cPORTAdd	=  64;		//I2C address Digital Ports module

	cPortVal	=0;			//Value of 8 bit digital port module

//Servo hexadecimal references as connected in MSCC20 module


	cServo[ 1]="0C";	// A2
	cServo[ 2]="06";	// B6
	cServo[ 3]="11";	// A4
	cServo[ 4]="0D";	// A5
	cServo[ 5]="04";	// B4
	cServo[ 6]="0B";	// C5
	cServo[ 7]="08";	// C0
	cServo[ 8]="02";	// B2
	cServo[ 9]="10";	// A3
	cServo[10]="12";	// C3
	cServo[11]="0F";	// A1
	cServo[12]="05";	// B5
	cServo[13]="0E";	// A0
	cServo[14]="00";	// B0
	cServo[15]="03";	// B3
	cServo[16]="0A";	// C2
	cServo[17]="09";	// C1
	cServo[18]="01";	// B1
	cServo[19]="07";	//B7
//	cServo[20]="13";

	//Values of position code for 0 and 45 degrees of each servo.
	//Used to make a relationship between degrees and position codes
	//sent to the servo control card.

	//Leg-1
	cPosConv[ 1][0]=203;	cPosConv[ 1][1]=140;
	cPosConv[ 2][0]= 77;	cPosConv[ 2][1]=136;
	cPosConv[ 3][0]=103;	cPosConv[ 3][1]=160;

	//Leg-2
	cPosConv[ 4][0]=195;	cPosConv[ 4][1]=139;
	cPosConv[ 5][0]= 85;	cPosConv[ 5][1]=143;
	cPosConv[ 6][0]= 85;	cPosConv[ 6][1]=143;

	//Leg-3
	cPosConv[ 7][0]=193;	cPosConv[ 7][1]=140;
	cPosConv[ 8][0]= 95;	cPosConv[ 8][1]=152;
	cPosConv[ 9][0]=118;	cPosConv[ 9][1]=178;

	//Leg-4
	cPosConv[11][0]= 25;	cPosConv[11][1]= 81;
	cPosConv[12][0]=168;	cPosConv[12][1]=109;
	cPosConv[13][0]= 80;	cPosConv[13][1]= 22;

	//Leg-5
	cPosConv[14][0]= 32;	cPosConv[14][1]= 91;
	cPosConv[15][0]=133;	cPosConv[15][1]= 73;
	cPosConv[16][0]= 95;	cPosConv[16][1]= 37;

	//Leg-6
	cPosConv[17][0]= 17;	cPosConv[17][1]= 79;
	cPosConv[18][0]=155;	cPosConv[18][1]= 99;
	cPosConv[19][0]= 77;	cPosConv[19][1]= 20;

	//{{AFX_DATA_INIT(CMelanieDlg)
	m_SliderServo01 = 0;
	m_SliderServo02 = 0;
	m_SliderServo03 = 0;
	m_SliderServo04 = 0;
	m_SliderServo05 = 0;
	m_SliderServo06 = 0;
	m_SliderServo07 = 0;
	m_SliderServo08 = 0;
	m_SliderServo09 = 0;
	m_SliderServo10 = 0;
	m_SliderServo11 = 0;
	m_SliderServo12 = 0;
	m_SliderServo13 = 0;
	m_SliderServo14 = 0;
	m_SliderServo15 = 0;
	m_SliderServo16 = 0;
	m_SliderServo17 = 0;
	m_SliderServo18 = 0;
	m_SliderServo19 = 0;
	m_ad01 = 0;
	m_ad02 = 0;
	m_ad03 = 0;
	m_ad04 = 0;
	m_ad05 = 0;
	m_ad06 = 0;
	m_ad07 = 0;
	m_ad08 = 0;
	m_ad09 = 0;
	m_ad11 = 0;
	m_ad12 = 0;
	m_ad13 = 0;
	m_ad14 = 0;
	m_ad15 = 0;
	m_ad16 = 0;
	m_ad17 = 0;
	m_ad18 = 0;
	m_ad19 = 0;
	m_pos01 = 0;
	m_pos02 = 0;
	m_pos03 = 0;
	m_pos04 = 0;
	m_pos05 = 0;
	m_pos06 = 0;
	m_pos07 = 0;
	m_pos08 = 0;
	m_pos09 = 0;
	m_pos10 = 0;
	m_pos11 = 0;
	m_pos12 = 0;
	m_pos13 = 0;
	m_pos14 = 0;
	m_pos15 = 0;
	m_pos16 = 0;
	m_pos17 = 0;
	m_pos18 = 0;
	m_pos19 = 0;
	m_pause = 80;
	m_seqname = _T("seqfile.txt");
	m_switch = FALSE;
	m_servo1 = FALSE;
	m_servo10 = FALSE;
	m_servo11 = FALSE;
	m_servo12 = FALSE;
	m_servo13 = FALSE;
	m_servo14 = FALSE;
	m_servo15 = FALSE;
	m_servo16 = FALSE;
	m_servo17 = FALSE;
	m_servo18 = FALSE;
	m_servo19 = FALSE;
	m_servo2 = FALSE;
	m_servo3 = FALSE;
	m_servo4 = FALSE;
	m_servo5 = FALSE;
	m_servo6 = FALSE;
	m_servo7 = FALSE;
	m_servo8 = FALSE;
	m_servo9 = FALSE;
	m_curr02 = 0;
	m_curr05 = 0;
	m_curr08 = 0;
	m_curr12 = 0;
	m_curr15 = 0;
	m_curr18 = 0;
	m_wave1 = TRUE;
	m_wave2 = FALSE;
	m_ObstaclesChk = TRUE;
	m_voltlog = 0;
	m_voltpow = 0;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//Initialize sequence of positions
	CreateSequence();

	//Open serial port
	port.Open(1, 9600, CSerialPort::NoParity, 8, CSerialPort::OneStopBit, CSerialPort::NoFlowControl);	

}

CMelanieDlg::~CMelanieDlg()
// Destructor
{
	delete(pstFirstPos);	//Free memory previously used
	port.Close();			//Close Serial Port

}

void CMelanieDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMelanieDlg)
	DDX_Slider(pDX, IDC_SLIDERSERVO01, m_SliderServo01);
	DDX_Slider(pDX, IDC_SLIDERSERVO02, m_SliderServo02);
	DDX_Slider(pDX, IDC_SLIDERSERVO03, m_SliderServo03);
	DDX_Slider(pDX, IDC_SLIDERSERVO04, m_SliderServo04);
	DDX_Slider(pDX, IDC_SLIDERSERVO05, m_SliderServo05);
	DDX_Slider(pDX, IDC_SLIDERSERVO06, m_SliderServo06);
	DDX_Slider(pDX, IDC_SLIDERSERVO07, m_SliderServo07);
	DDX_Slider(pDX, IDC_SLIDERSERVO08, m_SliderServo08);
	DDX_Slider(pDX, IDC_SLIDERSERVO09, m_SliderServo09);
	DDX_Slider(pDX, IDC_SLIDERSERVO10, m_SliderServo10);
	DDX_Slider(pDX, IDC_SLIDERSERVO11, m_SliderServo11);
	DDX_Slider(pDX, IDC_SLIDERSERVO12, m_SliderServo12);
	DDX_Slider(pDX, IDC_SLIDERSERVO13, m_SliderServo13);
	DDX_Slider(pDX, IDC_SLIDERSERVO14, m_SliderServo14);
	DDX_Slider(pDX, IDC_SLIDERSERVO15, m_SliderServo15);
	DDX_Slider(pDX, IDC_SLIDERSERVO16, m_SliderServo16);
	DDX_Slider(pDX, IDC_SLIDERSERVO17, m_SliderServo17);
	DDX_Slider(pDX, IDC_SLIDERSERVO18, m_SliderServo18);
	DDX_Slider(pDX, IDC_SLIDERSERVO19, m_SliderServo19);
	DDX_Text(pDX, IDC_AD01, m_ad01);
	DDX_Text(pDX, IDC_AD02, m_ad02);
	DDX_Text(pDX, IDC_AD03, m_ad03);
	DDX_Text(pDX, IDC_AD04, m_ad04);
	DDX_Text(pDX, IDC_AD05, m_ad05);
	DDX_Text(pDX, IDC_AD06, m_ad06);
	DDX_Text(pDX, IDC_AD07, m_ad07);
	DDX_Text(pDX, IDC_AD08, m_ad08);
	DDX_Text(pDX, IDC_AD09, m_ad09);
	DDX_Text(pDX, IDC_AD11, m_ad11);
	DDX_Text(pDX, IDC_AD12, m_ad12);
	DDX_Text(pDX, IDC_AD13, m_ad13);
	DDX_Text(pDX, IDC_AD14, m_ad14);
	DDX_Text(pDX, IDC_AD15, m_ad15);
	DDX_Text(pDX, IDC_AD16, m_ad16);
	DDX_Text(pDX, IDC_AD17, m_ad17);
	DDX_Text(pDX, IDC_AD18, m_ad18);
	DDX_Text(pDX, IDC_AD19, m_ad19);
	DDX_Text(pDX, IDC_POS01, m_pos01);
	DDX_Text(pDX, IDC_POS02, m_pos02);
	DDX_Text(pDX, IDC_POS03, m_pos03);
	DDX_Text(pDX, IDC_POS04, m_pos04);
	DDX_Text(pDX, IDC_POS05, m_pos05);
	DDX_Text(pDX, IDC_POS06, m_pos06);
	DDX_Text(pDX, IDC_POS07, m_pos07);
	DDX_Text(pDX, IDC_POS08, m_pos08);
	DDX_Text(pDX, IDC_POS09, m_pos09);
	DDX_Text(pDX, IDC_POS10, m_pos10);
	DDX_Text(pDX, IDC_POS11, m_pos11);
	DDX_Text(pDX, IDC_POS12, m_pos12);
	DDX_Text(pDX, IDC_POS13, m_pos13);
	DDX_Text(pDX, IDC_POS14, m_pos14);
	DDX_Text(pDX, IDC_POS15, m_pos15);
	DDX_Text(pDX, IDC_POS16, m_pos16);
	DDX_Text(pDX, IDC_POS17, m_pos17);
	DDX_Text(pDX, IDC_POS18, m_pos18);
	DDX_Text(pDX, IDC_POS19, m_pos19);
	DDX_Text(pDX, IDC_PAUSE, m_pause);
	DDX_Text(pDX, IDC_SEQNAME, m_seqname);
	DDX_Check(pDX, IDC_SWITCH, m_switch);
	DDX_Check(pDX, IDC_SERVO1, m_servo1);
	DDX_Check(pDX, IDC_SERVO10, m_servo10);
	DDX_Check(pDX, IDC_SERVO11, m_servo11);
	DDX_Check(pDX, IDC_SERVO12, m_servo12);
	DDX_Check(pDX, IDC_SERVO13, m_servo13);
	DDX_Check(pDX, IDC_SERVO14, m_servo14);
	DDX_Check(pDX, IDC_SERVO15, m_servo15);
	DDX_Check(pDX, IDC_SERVO16, m_servo16);
	DDX_Check(pDX, IDC_SERVO17, m_servo17);
	DDX_Check(pDX, IDC_SERVO18, m_servo18);
	DDX_Check(pDX, IDC_SERVO19, m_servo19);
	DDX_Check(pDX, IDC_SERVO2, m_servo2);
	DDX_Check(pDX, IDC_SERVO3, m_servo3);
	DDX_Check(pDX, IDC_SERVO4, m_servo4);
	DDX_Check(pDX, IDC_SERVO5, m_servo5);
	DDX_Check(pDX, IDC_SERVO6, m_servo6);
	DDX_Check(pDX, IDC_SERVO7, m_servo7);
	DDX_Check(pDX, IDC_SERVO8, m_servo8);
	DDX_Check(pDX, IDC_SERVO9, m_servo9);
	DDX_Text(pDX, IDC_CURR02, m_curr02);
	DDX_Text(pDX, IDC_CURR05, m_curr05);
	DDX_Text(pDX, IDC_CURR08, m_curr08);
	DDX_Text(pDX, IDC_CURR12, m_curr12);
	DDX_Text(pDX, IDC_CURR15, m_curr15);
	DDX_Text(pDX, IDC_CURR18, m_curr18);
	DDX_Check(pDX, IDC_Wave1, m_wave1);
	DDX_Check(pDX, IDC_Wave2, m_wave2);
	DDX_Check(pDX, IDC_OBSTACLESCHK, m_ObstaclesChk);
	DDX_Text(pDX, IDC_VoltLog, m_voltlog);
	DDX_Text(pDX, IDC_VoltPow, m_voltpow);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMelanieDlg, CDialog)
	//{{AFX_MSG_MAP(CMelanieDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_AD, OnAD)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO01, OnCustomdrawSliderservo01)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO02, OnCustomdrawSliderservo02)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO03, OnCustomdrawSliderservo03)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO04, OnCustomdrawSliderservo04)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO05, OnCustomdrawSliderservo05)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO06, OnCustomdrawSliderservo06)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO07, OnCustomdrawSliderservo07)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO08, OnCustomdrawSliderservo08)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO09, OnCustomdrawSliderservo09)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO10, OnCustomdrawSliderservo10)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO11, OnCustomdrawSliderservo11)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO12, OnCustomdrawSliderservo12)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO13, OnCustomdrawSliderservo13)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO14, OnCustomdrawSliderservo14)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO15, OnCustomdrawSliderservo15)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO16, OnCustomdrawSliderservo16)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO17, OnCustomdrawSliderservo17)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO18, OnCustomdrawSliderservo18)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERSERVO19, OnCustomdrawSliderservo19)
	ON_BN_CLICKED(IDC_SAVEPOS, OnSavepos)
	ON_BN_CLICKED(IDC_SAVESEQ, OnSaveseq)
	ON_BN_CLICKED(IDC_TOPBACK, OnTopback)
	ON_BN_CLICKED(IDC_TOPFORWARD, OnTopforward)
	ON_BN_CLICKED(IDC_STEPFORWARD, OnStepforward)
	ON_BN_CLICKED(IDC_ALLFORWARD, OnAllforward)
	ON_BN_CLICKED(IDC_CLEARSEQ, OnClearseq)
	ON_BN_CLICKED(IDC_STEPBACK, OnStepback)
	ON_BN_CLICKED(IDC_ALLBACK, OnAllback)
	ON_BN_CLICKED(IDC_LOADSEQ, OnLoadseq)
	ON_BN_CLICKED(IDC_LOADOVERSEQ, OnLoadOverSeq)
	ON_BN_CLICKED(IDC_SWITCH, OnSwitch)
	ON_BN_CLICKED(IDC_SAVEINVSEQ, OnSaveinvseq)
	ON_BN_CLICKED(IDC_PRESET1, OnPreset1)
	ON_BN_CLICKED(IDC_PRESET2, OnPreset2)
	ON_BN_CLICKED(IDC_PRESET6, OnPreset6)
	ON_BN_CLICKED(IDC_PRESET3, OnPreset3)
	ON_BN_CLICKED(IDC_PRESET10, OnPreset10)
	ON_BN_CLICKED(IDC_PRESET4, OnPreset4)
	ON_BN_CLICKED(IDC_PRESET8, OnPreset8)
	ON_BN_CLICKED(IDC_PRESET9, OnPreset9)
	ON_BN_CLICKED(IDC_PRESET7, OnPreset7)
	ON_BN_CLICKED(IDC_PRESET11, OnPreset11)
	ON_BN_CLICKED(IDC_PRESETSET1, OnPresetset1)
	ON_BN_CLICKED(IDC_PRESET12, OnPreset12)
	ON_BN_CLICKED(IDC_PRESETSET2, OnPresetset2)
	ON_BN_CLICKED(IDC_PRESET13, OnPreset13)
	ON_BN_CLICKED(IDC_SERVO1, OnServo1)
	ON_BN_CLICKED(IDC_SERVO2, OnServo2)
	ON_BN_CLICKED(IDC_SERVO3, OnServo3)
	ON_BN_CLICKED(IDC_SERVO10, OnServo10)
	ON_BN_CLICKED(IDC_SERVO11, OnServo11)
	ON_BN_CLICKED(IDC_SERVO12, OnServo12)
	ON_BN_CLICKED(IDC_SERVO13, OnServo13)
	ON_BN_CLICKED(IDC_SERVO14, OnServo14)
	ON_BN_CLICKED(IDC_SERVO15, OnServo15)
	ON_BN_CLICKED(IDC_SERVO16, OnServo16)
	ON_BN_CLICKED(IDC_SERVO17, OnServo17)
	ON_BN_CLICKED(IDC_SERVO18, OnServo18)
	ON_BN_CLICKED(IDC_SERVO19, OnServo19)
	ON_BN_CLICKED(IDC_SERVO4, OnServo4)
	ON_BN_CLICKED(IDC_SERVO5, OnServo5)
	ON_BN_CLICKED(IDC_SERVO6, OnServo6)
	ON_BN_CLICKED(IDC_SERVO7, OnServo7)
	ON_BN_CLICKED(IDC_SERVO8, OnServo8)
	ON_BN_CLICKED(IDC_SERVO9, OnServo9)
	ON_BN_CLICKED(IDC_CURRCHK, OnChkCurr)
	ON_BN_CLICKED(IDC_ALLON, OnAllServosOn)
	ON_BN_CLICKED(IDC_ALLOFF, OnAllServosOff)
	ON_BN_CLICKED(IDC_WAVE_UP, OnWaveUp)
	ON_BN_CLICKED(IDC_WAVE_FWD, OnWaveFwd)
	ON_BN_CLICKED(IDC_WAVE_DOWN, OnWaveDown)
	ON_BN_CLICKED(IDC_BATTSTATUS, OnChkBattStatus)
	ON_BN_CLICKED(IDC_WAVE_PRESET, OnWavePreset)
	ON_BN_CLICKED(IDC_WAVE_FWDSHORT, OnWaveFwdShort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMelanieDlg message handlers

BOOL CMelanieDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMelanieDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

HCURSOR CMelanieDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CMelanieDlg::DecToHex(int DecNumber, char *Hex)
//	Conversion of decimal number (0...255) to hexadecimal string (2 digits).
{
	itoa(DecNumber / 16, Hex, 16);			//MSD = dec. number / 16
	itoa(DecNumber % 16, Hex+1, 16);		//LSD = remainder dec number / 16
}

void CMelanieDlg::SendCommand(CString sCommand)
{
	CString	cr=13, lf=10;	//Carriage Return, Line Feed
	port.Write(sCommand, strlen(sCommand));
	port.Write(cr, 1);
	port.Write(lf, 1);
	port.Flush();
//	Sleep(10);
}

void CMelanieDlg::OnAD() 
//Read A/D Conversion
{

	unsigned char cPos[20];
	unsigned char cAD[20];
	ChkPos(cPos, cAD);

	m_ad01	= cAD[ 1];
	m_ad02	= cAD[ 2];
	m_ad03	= cAD[ 3];
	m_ad04	= cAD[ 4];
	m_ad05	= cAD[ 5];
	m_ad06	= cAD[ 6];
	m_ad07	= cAD[ 7];
	m_ad08	= cAD[ 8];
	m_ad09	= cAD[ 9];
	m_ad11	= cAD[11];
	m_ad12	= cAD[12];
	m_ad13	= cAD[13];
	m_ad14	= cAD[14];
	m_ad15	= cAD[15];
	m_ad16	= cAD[16];
	m_ad17	= cAD[17];
	m_ad18	= cAD[18];
	m_ad19	= cAD[19];

	m_pos01	= cPos[ 1];
	m_pos02	= cPos[ 2];
	m_pos03	= cPos[ 3];
	m_pos04	= cPos[ 4];
	m_pos05	= cPos[ 5];
	m_pos06	= cPos[ 6];
	m_pos07	= cPos[ 7];
	m_pos08	= cPos[ 8];
	m_pos09	= cPos[ 9];
	m_pos11	= cPos[11];
	m_pos12	= cPos[12];
	m_pos13	= cPos[13];
	m_pos14	= cPos[14];
	m_pos15	= cPos[15];
	m_pos16	= cPos[16];
	m_pos17	= cPos[17];
	m_pos18	= cPos[18];
	m_pos19	= cPos[19];


	UpdateData(FALSE);						//Update Form	
	UpdateSliders();	//Update form sliders as per the values especified
/*	SetServoPos(cServo[ 1],m_pos01,10);
	SetServoPos(cServo[ 2],m_pos02,10);
	SetServoPos(cServo[ 3],m_pos03,10);
*/
}




void CMelanieDlg::SetServoPos(CString cServo, int iPosition, int iSpeed=2)
// Move a servo to a specified position at a specified speed  
// by sending the adecuate information via RS232 to MSCC20 module
{
	if (m_switch) 
	{
		if (iSpeed==0) iSpeed=1;
	 	DecToHex(iPosition, cHex);
		port.Write("M", 1);
		port.Write(cServo, 2);
		port.Write(cHex, 2);
	 	DecToHex(iSpeed, cHex);
		SendCommand(cHex);
	}
}

void CMelanieDlg::ActivateServo(CString cServo, unsigned char cPos)
// Activate a servo by sending the 
// adecuate information via RS232 to MSCC20 module
{
	port.Write("SE", 2);
	SendCommand(cServo);
	SetServoPos(cServo,cPos,255);
}


void CMelanieDlg::OnCustomdrawSliderservo01(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos01=250-(m_SliderServo01*250/100);
	SetServoPos(cServo[ 1],m_pos01);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo02(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos02=(m_SliderServo02*250/100);
	SetServoPos(cServo[ 2],m_pos02);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo03(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos03=250-(m_SliderServo03*250/100);
	SetServoPos(cServo[ 3],m_pos03);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo04(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos04=250-(m_SliderServo04*250/100);
	SetServoPos(cServo[ 4],m_pos04);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo05(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos05=(m_SliderServo05*250/100);
	SetServoPos(cServo[ 5],m_pos05);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo06(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos06=250-(m_SliderServo06*250/100);
	SetServoPos(cServo[ 6],m_pos06);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo07(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos07=250-(m_SliderServo07*250/100);
	SetServoPos(cServo[ 7],m_pos07);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo08(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos08=(m_SliderServo08*250/100);
	SetServoPos(cServo[ 8],m_pos08);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo09(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos09=250-(m_SliderServo09*250/100);
	SetServoPos(cServo[ 9],m_pos09);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo10(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos10=(m_SliderServo10*250/100);
	SetServoPos(cServo[10],m_pos10);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo11(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos11=(m_SliderServo11*250/100);
	SetServoPos(cServo[11],m_pos11);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo12(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos12=250-(m_SliderServo12*250/100);
	SetServoPos(cServo[12],m_pos12);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo13(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos13=(m_SliderServo13*250/100);
	SetServoPos(cServo[13],m_pos13);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo14(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos14=(m_SliderServo14*250/100);
	SetServoPos(cServo[14],m_pos14);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo15(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos15=250-(m_SliderServo15*250/100);
	SetServoPos(cServo[15],m_pos15);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo16(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos16=(m_SliderServo16*250/100);
	SetServoPos(cServo[16],m_pos16);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo17(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos17=(m_SliderServo17*250/100);
	SetServoPos(cServo[17],m_pos17);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo18(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos18=250-(m_SliderServo18*250/100);
	SetServoPos(cServo[18],m_pos18);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}

void CMelanieDlg::OnCustomdrawSliderservo19(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);				//Read Form	
	m_pos19=(m_SliderServo19*250/100);
	SetServoPos(cServo[19],m_pos19);
	UpdateData(FALSE);				//Update Form	
	*pResult = 0;
}


void CMelanieDlg::OnSavepos() 
// Save the position of all servos in the sequence in memory
{
	UpdateData(TRUE);				//Read Form	

	pstActualPos->cServoPos[ 1]=	m_pos01;
	pstActualPos->cServoPos[ 2]=	m_pos02;
	pstActualPos->cServoPos[ 3]=	m_pos03;
	pstActualPos->cServoPos[ 4]=	m_pos04;
	pstActualPos->cServoPos[ 5]=	m_pos05;
	pstActualPos->cServoPos[ 6]=	m_pos06;
	pstActualPos->cServoPos[ 7]=	m_pos07;
	pstActualPos->cServoPos[ 8]=	m_pos08;
	pstActualPos->cServoPos[ 9]=	m_pos09;
	pstActualPos->cServoPos[10]=	m_pos10;
	pstActualPos->cServoPos[11]=	m_pos11;
	pstActualPos->cServoPos[12]=	m_pos12;
	pstActualPos->cServoPos[13]=	m_pos13;
	pstActualPos->cServoPos[14]=	m_pos14;
	pstActualPos->cServoPos[15]=	m_pos15;
	pstActualPos->cServoPos[16]=	m_pos16;
	pstActualPos->cServoPos[17]=	m_pos17;
	pstActualPos->cServoPos[18]=	m_pos18;
	pstActualPos->cServoPos[19]=	m_pos19;
	pstActualPos->cServoPos[20]=	0;
	pstActualPos->cPause=			m_pause;

	if (pstActualPos->nextpos==NULL)
	{
		pstActualPos->nextpos=	new(struct	stPosition);
		pstPrevPos=pstActualPos;
		pstActualPos=pstActualPos->nextpos;
		pstActualPos->nextpos=NULL;
		pstActualPos->prevpos=pstPrevPos;
	}
	else
	{
		pstActualPos=pstActualPos->nextpos;
	}

}


void CMelanieDlg::OnSaveseq() 
// Save sequence in file
{
//	ofstream seqfile("seqfile.txt",ios::out);
	UpdateData(TRUE);				//Read Form	
	ofstream seqfile(m_seqname,ios::out);
	if(!seqfile) 
		MessageBox("Sequence file could not be opened","Error Message",MB_ICONEXCLAMATION);
	else 
	{
		pstActualPos=pstFirstPos;
		while (pstActualPos->nextpos!=NULL)
		{
			seqfile.put(pstActualPos->cPause);
			for (temp=1;temp<=20;temp++)
				seqfile.put(pstActualPos->cServoPos[temp]);
			seqfile.put((unsigned char)10);
			pstActualPos=pstActualPos->nextpos;
		}
		seqfile.close();
	}
}

void CMelanieDlg::SetGlobalPos()
// Set all servo positions as specified by the actual pointer
// from the sequence
{

	//Move servos to specified positions
	SetServoPos(cServo[ 1],pstActualPos->cServoPos[ 1], cSpeed( 1));
	SetServoPos(cServo[ 2],pstActualPos->cServoPos[ 2], cSpeed( 2));
	SetServoPos(cServo[ 3],pstActualPos->cServoPos[ 3], cSpeed( 3));
	SetServoPos(cServo[ 4],pstActualPos->cServoPos[ 4], cSpeed( 4));
	SetServoPos(cServo[ 5],pstActualPos->cServoPos[ 5], cSpeed( 5));
	SetServoPos(cServo[ 6],pstActualPos->cServoPos[ 6], cSpeed( 6));
	SetServoPos(cServo[ 7],pstActualPos->cServoPos[ 7], cSpeed( 7));
	SetServoPos(cServo[ 8],pstActualPos->cServoPos[ 8], cSpeed( 8));
	SetServoPos(cServo[ 9],pstActualPos->cServoPos[ 9], cSpeed( 9));
	SetServoPos(cServo[10],pstActualPos->cServoPos[10], cSpeed(10));
	SetServoPos(cServo[11],pstActualPos->cServoPos[11], cSpeed(11));
	SetServoPos(cServo[12],pstActualPos->cServoPos[12], cSpeed(12));
	SetServoPos(cServo[13],pstActualPos->cServoPos[13], cSpeed(13));
	SetServoPos(cServo[14],pstActualPos->cServoPos[14], cSpeed(14));
	SetServoPos(cServo[15],pstActualPos->cServoPos[15], cSpeed(15));
	SetServoPos(cServo[16],pstActualPos->cServoPos[16], cSpeed(16));
	SetServoPos(cServo[17],pstActualPos->cServoPos[17], cSpeed(17));
	SetServoPos(cServo[18],pstActualPos->cServoPos[18], cSpeed(18));
	SetServoPos(cServo[19],pstActualPos->cServoPos[19], cSpeed(19));

	//Update form values as per the values especified
	m_pos01=pstActualPos->cServoPos[ 1];
	m_pos02=pstActualPos->cServoPos[ 2];
	m_pos03=pstActualPos->cServoPos[ 3];
	m_pos04=pstActualPos->cServoPos[ 4];
	m_pos05=pstActualPos->cServoPos[ 5];
	m_pos06=pstActualPos->cServoPos[ 6];
	m_pos07=pstActualPos->cServoPos[ 7];
	m_pos08=pstActualPos->cServoPos[ 8];
	m_pos09=pstActualPos->cServoPos[ 9];
	m_pos10=pstActualPos->cServoPos[10];
	m_pos11=pstActualPos->cServoPos[11];
	m_pos12=pstActualPos->cServoPos[12];
	m_pos13=pstActualPos->cServoPos[13];
	m_pos14=pstActualPos->cServoPos[14];
	m_pos15=pstActualPos->cServoPos[15];
	m_pos16=pstActualPos->cServoPos[16];
	m_pos17=pstActualPos->cServoPos[17];
	m_pos18=pstActualPos->cServoPos[18];
	m_pos19=pstActualPos->cServoPos[19];
	UpdateData(FALSE);				//Update Form	

	UpdateSliders();	//Update form sliders as per the values especified
	m_pause=pstActualPos->cPause;
	UpdateData(FALSE);				//Update Form	
	Sleep((pstActualPos->cPause)*5);
	
}

void CMelanieDlg::OnTopback()
//Set actual pointer position to first one in sequence 
{
	pstActualPos=pstFirstPos;
	if (pstActualPos->nextpos!=NULL) SetGlobalPos();
}

void CMelanieDlg::OnTopforward() 
//Set actual pointer position to last one in sequence 
{
	while (pstActualPos->nextpos!=NULL)
	{
		pstActualPos=pstActualPos->nextpos;
	}
	if (pstActualPos->prevpos!=NULL)
	{
		pstActualPos=pstActualPos->prevpos;
		SetGlobalPos();
	}
	
}

void CMelanieDlg::OnStepforward() 
//Make one movement from the sequence in forward mode
{
	if (pstActualPos->nextpos!=NULL)
	{
		pstActualPos=pstActualPos->nextpos;
		if (pstActualPos->nextpos==NULL)
		{
			pstActualPos=pstActualPos->prevpos;
			SetGlobalPos();
		}
		else
			SetGlobalPos();
	}
}

void CMelanieDlg::OnAllforward() 
//Make all the sequence of movements from actual position 
//of pointer in forward mode
{
	while (pstActualPos->nextpos!=NULL)
	{
		pstActualPos=pstActualPos->nextpos;
		if (pstActualPos->nextpos!=NULL) SetGlobalPos();
	}
	if ((pstActualPos->nextpos==NULL) && 
		(pstActualPos->prevpos!=NULL))
		{
			pstActualPos=pstActualPos->prevpos;
		}
	
}


void CMelanieDlg::OnStepback() 
//Make one movement from the sequence in reverse mode
{
	if (pstActualPos->prevpos!=NULL)
	{
		pstActualPos=pstActualPos->prevpos;
		SetGlobalPos();
	}
	
}

void CMelanieDlg::OnClearseq() 
//Clear Sequence in memory
{
	delete(pstFirstPos);	//Free memory previously used
	CreateSequence();
}

void CMelanieDlg::CreateSequence()
//Create the sequence, so could be used here and there
{
	pstFirstPos=new (struct	stPosition);
	pstActualPos=pstFirstPos;
	pstActualPos->nextpos=NULL;
	pstActualPos->prevpos=NULL;
	for (temp=1;temp<=20;temp++)
		pstActualPos->cServoPos[temp]=0;
	pstActualPos->cPause=0;

}

void CMelanieDlg::OnAllback() 
//Make all the sequence of movements from actual position 
//of pointer in reverse mode
{
	while (pstActualPos->prevpos!=NULL)
	{
		pstActualPos=pstActualPos->prevpos;
		SetGlobalPos();
	}
}

void CMelanieDlg::OnLoadseq() 
//Load sequence from file
{
	delete(pstFirstPos);	//Free memory previously used
	CreateSequence();
	UpdateData(TRUE);				//Read Form	
	LoadSequence(m_seqname);	
}


void CMelanieDlg::LoadSequence(CString FileName)
//Load sequence from file storing from actual pointer
//position
{
	unsigned char c;		

	UpdateData(TRUE);				//Read Form	
	ifstream seqfile(FileName,ios::in|ios::nocreate);
	if(!seqfile) 
		MessageBox("Sequence file could not be opened","Error Message",MB_ICONEXCLAMATION);
	else 
	{
		while (seqfile.get(c))
		{
			pstActualPos->cPause=c;
			for (temp=1;temp<=20;temp++)
				seqfile.get(pstActualPos->cServoPos[temp]);
			seqfile.get(c);		//Carriage return
			if (pstActualPos->nextpos==NULL)
			{
				pstActualPos->nextpos=	new(struct	stPosition);
				pstPrevPos=pstActualPos;
				pstActualPos=pstActualPos->nextpos;
				pstActualPos->nextpos=NULL;
				pstActualPos->prevpos=pstPrevPos;
			}
			else
			{
				pstActualPos=pstActualPos->nextpos;
			}
		}
		seqfile.close();
		OnTopback();
	}
}

void CMelanieDlg::OnLoadOverSeq() 
//Load a sequence overwriting actual secuence in memory
//from the actual pointer position onwards
{
	UpdateData(TRUE);				//Read Form	
	LoadSequence(m_seqname);	
}

void CMelanieDlg::OnSwitch() 
//Switch ON/OFF Robot
{
	//Prepare Digital ports chip for output
	SetDPort(0);

	unsigned char cPos[20];		// Used to call ChkPos function
	unsigned char cAD[20];		// Used to call ChkPos function
	int		iServo;				// Servo index


	UpdateData(TRUE);				//Read Form	
	if (m_switch) 
	{
		SendCommand("SO");
		SendCommand("SX1F9D");

		ChkPos(cPos, cAD);	//Check actual position of servos

		for(iServo=1;iServo<=9;iServo++) ActivateServo(cServo[iServo],cPos[iServo]);
		ActivateServo(cServo[10],67);
		for(iServo=11;iServo<=19;iServo++) ActivateServo(cServo[iServo],cPos[iServo]);

		OnChkBattStatus(); //Show batery status
/*
		//Left Leg - 1
		ActivateServo(cServo[ 1],18);
		ActivateServo(cServo[ 2],55);
		ActivateServo(cServo[ 3],103);

		//Left Leg - 2
		ActivateServo(cServo[ 4],10);
		ActivateServo(cServo[ 5],35);
		ActivateServo(cServo[ 6],85);

		//Left Leg - 3
		ActivateServo(cServo[ 7],23);
		ActivateServo(cServo[ 8],65);
		ActivateServo(cServo[ 9],118);

		//Head
		ActivateServo(cServo[10],85);

		//Right Leg - 1
		ActivateServo(cServo[11],155);
		ActivateServo(cServo[12],210);
		ActivateServo(cServo[13],85);

		//Right Leg - 2
		ActivateServo(cServo[14],175);
		ActivateServo(cServo[15],180);
		ActivateServo(cServo[16],95);

		//Right Leg - 3
		ActivateServo(cServo[17],160);
		ActivateServo(cServo[18],180);
		ActivateServo(cServo[19],75);
*/

		//Update all servo form activation switches
		m_servo1  = m_servo2  = m_servo3  = TRUE;
		m_servo4  = m_servo5  = m_servo6  = TRUE;
		m_servo7  = m_servo8  = m_servo9  = TRUE;
		m_servo10 = TRUE;
		m_servo11 = m_servo12 = m_servo13 = TRUE;
		m_servo14 = m_servo15 = m_servo16 = TRUE;
		m_servo17 = m_servo18 = m_servo19 = TRUE;

//		RunPreset("start.txt");	
		m_seqname = _T("seqfile.txt");
		UpdateData(FALSE);

/*		Sleep(1000);
		OnTestt();
*/	}
	else
	{
		SendCommand("SF");	//Send command to stop signal generation
		OffOnRelay();		//Reset digital servos
		//Update all servo form activation switches
		m_servo1  = m_servo2  = m_servo3  = FALSE;
		m_servo4  = m_servo5  = m_servo6  = FALSE;
		m_servo7  = m_servo8  = m_servo9  = FALSE;
		m_servo10 = FALSE;
		m_servo11 = m_servo12 = m_servo13 = FALSE;
		m_servo14 = m_servo15 = m_servo16 = FALSE;
		m_servo17 = m_servo18 = m_servo19 = FALSE;
		UpdateData(FALSE);
	}
}

unsigned char CMelanieDlg::cSpeed(unsigned char cServo)
//Calculate the Speed for a Servo as a function of the Pause
//and de position
{
	int iSP;
	if (pstActualPos->prevpos==NULL)
		iSP=1;
	else
	{
		pstPrevPos=pstActualPos->prevpos;

		if (pstActualPos->cServoPos[cServo] > pstPrevPos->cServoPos[cServo])
			iSP=(int)((float)(pstActualPos->cServoPos[cServo] - 
				pstPrevPos->cServoPos[cServo])*(float)8/
				(float)pstActualPos->cPause);
		else
			iSP=(int)((float)(pstPrevPos->cServoPos[cServo] - 
				pstActualPos->cServoPos[cServo])*(float)8/
				(float)pstActualPos->cPause);

	}
	if (iSP>255) iSP=255;
	if (iSP==0) iSP=1;
	return (iSP);
}

void CMelanieDlg::OnSaveinvseq() 
// Save inverted sequence in file
{
	UpdateData(TRUE);				//Read Form	
	ofstream seqfile(m_seqname,ios::out);
	if(!seqfile) 
		MessageBox("Sequence file could not be opened","Error Message",MB_ICONEXCLAMATION);
	else 
	{
		while (pstActualPos->nextpos!=NULL)
		{
			pstActualPos=pstActualPos->nextpos;
		}
		if (pstActualPos->prevpos!=NULL)
		{
			pstActualPos=pstActualPos->prevpos;
		}
		do {
			seqfile.put(pstActualPos->cPause);
			for (temp=1;temp<=20;temp++)
				seqfile.put(pstActualPos->cServoPos[temp]);
			seqfile.put((unsigned char)10);
			pstActualPos=pstActualPos->prevpos;
		} while (pstActualPos->prevpos!=NULL);
		seqfile.put(pstActualPos->cPause);
		for (temp=1;temp<=20;temp++)
			seqfile.put(pstActualPos->cServoPos[temp]);
		seqfile.put((unsigned char)10);
		seqfile.close();
	}
}

void CMelanieDlg::RunPreset(CString FileName)
//Load and run a specific file of sequence
{
	m_seqname=FileName;
	UpdateData(FALSE);		//Update form
	OnLoadseq();			//Load the preset sequence
	OnAllforward();			//Run it	

}

void CMelanieDlg::OnPreset1() 
//Up
{
	RunPreset("up.txt");
}


void CMelanieDlg::OnPreset2() 
//Down
{
	RunPreset("down.txt");	
}

void CMelanieDlg::OnPreset6() 
//PreFwd
{
	RunPreset("prefwd.txt");	
}

void CMelanieDlg::OnPreset3() 
//Fwd
{
	RunPreset("fwd.txt");	
}

void CMelanieDlg::OnPreset10() 
//PosFwd
{
	RunPreset("posfwd.txt");	
}

void CMelanieDlg::OnPreset4() 
//Back
{
	RunPreset("back.txt");	
}

void CMelanieDlg::OnPreset8() 
//Left
{
	RunPreset("left.txt");	
}

void CMelanieDlg::OnPreset9() 
//Right
{
	RunPreset("right.txt");	
}

void CMelanieDlg::OnPreset5() 
//Run
{
	RunPreset("run.txt");	
}

void CMelanieDlg::OnPreset7() 
//PreRight
{
	RunPreset("preright.txt");	
}

void CMelanieDlg::OnPreset11() 
//PosRight
{
	RunPreset("posright.txt");	
}

void CMelanieDlg::OnPresetset1() 
//Preset set: up - fwd - right 45º - fwd - down
{
	RunPreset("up.txt");	
	RunPreset("prefwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("posfwd.txt");	
	RunPreset("preright.txt");	
	RunPreset("right.txt");	
	RunPreset("right.txt");	
	RunPreset("posright.txt");	
	RunPreset("prefwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("posfwd.txt");	
	RunPreset("down.txt");	
}

void CMelanieDlg::OnPreset12() 
//PreLeft
{
	RunPreset("preleft.txt");	
}

void CMelanieDlg::OnPresetset2() 
//Preset set: Up - Fwd - Left 180º - Fwd - Down
{
	RunPreset("up.txt");	
	RunPreset("prefwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("posfwd.txt");	
	RunPreset("preleft.txt");	
	RunPreset("left.txt");	
	RunPreset("left.txt");	
	RunPreset("left.txt");	
	RunPreset("left.txt");	
	RunPreset("left.txt");	
	RunPreset("left.txt");	
	RunPreset("left.txt");	
	RunPreset("left.txt");	
	RunPreset("left.txt");	
	RunPreset("posleft.txt");	
	RunPreset("prefwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("fwd.txt");	
	RunPreset("posfwd.txt");	
	RunPreset("down.txt");	
	
}

void CMelanieDlg::OnPreset13() 
//PosLeft
{
	RunPreset("posleft.txt");	
	
}

void CMelanieDlg::OnServo1() 
//Activate/deactivate a servo due to the status
//of the servo switch
{
	UpdateData(TRUE);				//Read Form	
	if (m_servo1)	ActivateServo(cServo[ 1],m_pos01);
	else			DeactivateServo(cServo[ 1]);
}

void CMelanieDlg::OnServo2() 
//Activate/deactivate a servo due to the status
//of the servo switch
{
	UpdateData(TRUE);				//Read Form	
	if (m_servo2)	ActivateServo(cServo[ 2],m_pos02);
	else			DeactivateServo(cServo[ 2]);
}

void CMelanieDlg::OnServo3() 
//Activate/deactivate a servo due to the status
//of the servo switch
{
	UpdateData(TRUE);				//Read Form	
	if (m_servo3)	ActivateServo(cServo[ 3],m_pos03);
	else			DeactivateServo(cServo[ 3]);
}

void CMelanieDlg::OnServo4() 
//Activate/deactivate a servo due to the status
//of the servo switch
{
	UpdateData(TRUE);				//Read Form	
	if (m_servo4)	ActivateServo(cServo[ 4],m_pos04);
	else			DeactivateServo(cServo[ 4]);
}

void CMelanieDlg::OnServo5() 
//Activate/deactivate a servo due to the status
//of the servo switch
{
	UpdateData(TRUE);				//Read Form	
	if (m_servo5)	ActivateServo(cServo[ 5],m_pos05);
	else			DeactivateServo(cServo[ 5]);

}

void CMelanieDlg::OnServo6() 
//Activate/deactivate a servo due to the status
//of the servo switch
{
	UpdateData(TRUE);				//Read Form	
	if (m_servo6)	ActivateServo(cServo[ 6],m_pos06);
	else			DeactivateServo(cServo[ 6]);
}

void CMelanieDlg::OnServo7() 
//Activate/deactivate a servo due to the status
//of the servo switch
{
	UpdateData(TRUE);				//Read Form	
	if (m_servo7)	ActivateServo(cServo[ 7],m_pos07);
	else			DeactivateServo(cServo[ 7]);
}

void CMelanieDlg::OnServo8() 
//Activate/deactivate a servo due to the status
//of the servo switch
{
	UpdateData(TRUE);				//Read Form	
	if (m_servo8)	ActivateServo(cServo[ 8],m_pos08);
	else			DeactivateServo(cServo[ 8]);
}

void CMelanieDlg::OnServo9() 
//Activate/deactivate a servo due to the status
//of the servo switch
{
	UpdateData(TRUE);				//Read Form	
	if (m_servo9)	ActivateServo(cServo[ 9],m_pos09);
	else			DeactivateServo(cServo[ 9]);
}
void CMelanieDlg::OnServo10() 
//Activate/deactivate a servo due to the status
//of the servo switch
{
	UpdateData(TRUE);				//Read Form	
	if (m_servo10)	ActivateServo(cServo[10],m_pos10);
	else			DeactivateServo(cServo[10]);
}

void CMelanieDlg::OnServo11() 
//Activate/deactivate a servo due to the status
//of the servo switch
{
	UpdateData(TRUE);				//Read Form	
	if (m_servo11)	ActivateServo(cServo[11],m_pos11);
	else			DeactivateServo(cServo[11]);
}

void CMelanieDlg::OnServo12() 
//Activate/deactivate a servo due to the status
//of the servo switch
{
	UpdateData(TRUE);				//Read Form	
	if (m_servo12)	ActivateServo(cServo[12],m_pos12);
	else			DeactivateServo(cServo[12]);
}

void CMelanieDlg::OnServo13() 
//Activate/deactivate a servo due to the status
//of the servo switch
{
	UpdateData(TRUE);				//Read Form	
	if (m_servo13)	ActivateServo(cServo[13],m_pos13);
	else			DeactivateServo(cServo[13]);
}

void CMelanieDlg::OnServo14() 
//Activate/deactivate a servo due to the status
//of the servo switch
{
	UpdateData(TRUE);				//Read Form	
	if (m_servo14)	ActivateServo(cServo[14],m_pos14);
	else			DeactivateServo(cServo[14]);
}

void CMelanieDlg::OnServo15() 
//Activate/deactivate a servo due to the status
//of the servo switch
{
	UpdateData(TRUE);				//Read Form	
	if (m_servo15)	ActivateServo(cServo[15],m_pos15);
	else			DeactivateServo(cServo[15]);
}

void CMelanieDlg::OnServo16() 
//Activate/deactivate a servo due to the status
//of the servo switch
{
	UpdateData(TRUE);				//Read Form	
	if (m_servo16)	ActivateServo(cServo[16],m_pos16);
	else			DeactivateServo(cServo[16]);
}

void CMelanieDlg::OnServo17() 
//Activate/deactivate a servo due to the status
//of the servo switch
{
	UpdateData(TRUE);				//Read Form	
	if (m_servo17)	ActivateServo(cServo[17],m_pos17);
	else			DeactivateServo(cServo[17]);
}

void CMelanieDlg::OnServo18() 
//Activate/deactivate a servo due to the status
//of the servo switch
{
	UpdateData(TRUE);				//Read Form	
	if (m_servo18)	ActivateServo(cServo[18],m_pos18);
	else			DeactivateServo(cServo[18]);
}

void CMelanieDlg::OnServo19() 
//Activate/deactivate a servo due to the status
//of the servo switch
{
	UpdateData(TRUE);				//Read Form	
	if (m_servo19)	ActivateServo(cServo[19],m_pos19);
	else			DeactivateServo(cServo[19]);
}


void CMelanieDlg::DeactivateServo(CString cServ)
// Deactivate a servo by sending the 
// adecuate information via RS232 to MSCC20 module
{
	port.Write("SD", 2);
	SendCommand(cServ);

	//Also Special treatment for digital servos. Should be reset
	if ((cServ==cServo[ 2]) ||
		(cServ==cServo[ 5]) ||
		(cServ==cServo[ 8]) ||
		(cServ==cServo[12]) ||
		(cServ==cServo[15]) ||
		(cServ==cServo[18])) OffOnRelay();
}

void CMelanieDlg::UpdateSliders()
//Update form sliders as per the values 
//especified in m_pos fields
{
	
	UpdateData(TRUE);				//Read Form	
	m_SliderServo01=100-(m_pos01*100/250);
	m_SliderServo02=(m_pos02*100/250);
	m_SliderServo03=100-(m_pos03*100/250);
	m_SliderServo04=100-(m_pos04*100/250);
	m_SliderServo05=(m_pos05*100/250);
	m_SliderServo06=100-(m_pos06*100/250);
	m_SliderServo07=100-(m_pos07*100/250);
	m_SliderServo08=(m_pos08*100/250);
	m_SliderServo09=100-(m_pos09*100/250);
	m_SliderServo10=(m_pos10*100/250);
	m_SliderServo11=(m_pos11*100/250);
	m_SliderServo12=100-(m_pos12*100/250);
	m_SliderServo13=(m_pos13*100/250);
	m_SliderServo14=(m_pos14*100/250);
	m_SliderServo15=100-(m_pos15*100/250);
	m_SliderServo16=(m_pos16*100/250);
	m_SliderServo17=(m_pos17*100/250);
	m_SliderServo18=100-(m_pos18*100/250);
	m_SliderServo19=(m_pos19*100/250);
	UpdateData(FALSE);				//Update Form	

}

void CMelanieDlg::SetDPort(unsigned char cValue)
//Set the value of the digital ports module 
//(I2C digital ports chip)
{
	Board.GenerateStartCondition();

	//Serial output of Chipcode for writemode
	Board.OutputByteToI2C(cPORTAdd);
	Board.GenerateAcknowledge();
//	Board.OutputByteToI2C(1);
//	Board.GenerateAcknowledge();
	Board.OutputByteToI2C(cValue);
	Board.GenerateAcknowledge();

	Board.GenerateStopCondition();

}

void CMelanieDlg::OnChkCurr() 
{
	ChkCurr();		//Check Current Values
	m_curr18=Current[LEG6];
	m_curr08=Current[LEG3];
	m_curr05=Current[LEG2];
	m_curr02=Current[LEG1];
	m_curr12=Current[LEG4];
	m_curr15=Current[LEG5];	
	UpdateData(FALSE);						//Update Form

/*	unsigned char	cValue [4][90],Lectures=90;
	long int 		ires[4];			//Acumulated results
	int				iADCh;			//A/D Channel to read

	//------ A/D CHIP 6 ----------------------------------------
	ires[0] = ires[1] = ires[2] = ires[3] = 0;
	for (temp=0; temp<Lectures; temp++)
	{
		Board.GenerateStartCondition();
		Board.OutputByteToI2C(cAD6Add);
		Board.GenerateAcknowledge();

		Board.OutputByteToI2C(0x42); 
		Board.GenerateAcknowledge();
		Board.GenerateStopCondition();
		Board.GenerateStartCondition();
		Board.OutputByteToI2C(cAD6Add+1);
		Board.GenerateAcknowledge();
		Board.InputByteFromI2C();

		iADCh=2;
		//Read 4 AD channels
//		for (iADCh=0; iADCh<=3; iADCh++)
		{
			Board.GenerateAcknowledgeFromMaster();
			cValue [iADCh][temp] = Board.InputByteFromI2C();	
			ires[iADCh] = ires[iADCh] + cValue [iADCh][temp];
		}
		Board.GenerateAcknowledge();
		Board.GenerateStopCondition();
	}
//	Current[LEG6] = ires[0]/Lectures;
//	Current[LEG3] = ires[1]/Lectures;
	Current[LEG2] = ires[2]/Lectures;

	m_curr05=Current[LEG2];
	UpdateData(FALSE);						//Update Form
*/

}

int CMelanieDlg::FwdKinematic (double value[2][3], double result[3])
//Calculate forward kinematics
//"value" is a 2x3 matrix that includes the three angles
//and the three lengths of the leg parts
//"results" will have the x,y,z values calculated
//The function gives value 0 if no error in calculations
{
	double			L1,L2,L3,
					Lx1,Lx2,Lx3,
					Ly2,Ly3,
					a1,a2,a3;				//temporary values
	int				errorcode=0;			//error code. By default no error

	//Control of limits
	if ((value[ANGLE][0]>90) || (value[ANGLE][0]<-90) ||
		(value[ANGLE][1]>80) || (value[ANGLE][1]<-90) ||
		(value[ANGLE][2]>0)  || (value[ANGLE][2]<-120))
		errorcode=1; //Error, our of range
	if (value[ANGLE][0]>  90) value[ANGLE][0]=  90;
	if (value[ANGLE][0]< -90) value[ANGLE][0]= -90;
	if (value[ANGLE][1]>  80) value[ANGLE][1]=  80;
	if (value[ANGLE][1]< -90) value[ANGLE][1]= -90;
	if (value[ANGLE][2]>   0) value[ANGLE][2]=  0;
	if (value[ANGLE][2]<-120) value[ANGLE][2]=-120;


	//Conversion of angles to radians
	a1=value[ANGLE][0]*PI/180;	
	a2=value[ANGLE][1]*PI/180;	
	a3=value[ANGLE][2]*PI/180;

	L1=value[LENGTH][COXA];
	L2=value[LENGTH][FEMUR];
	L3=value[LENGTH][TIBIA];

	Lx1=L1;
	Lx2=L2*cos(a2);
	Lx3=L3*cos(a2+a3);

	Ly2=L2*sin(a2);
	Ly3=L3*sin(a2+a3);

	result[X]=(Lx1+Lx2+Lx3)*cos(a1);
	result[Y]=Ly2+Ly3;
	result[Z]=(Lx1+Lx2+Lx3)*sin(a1);

	return(errorcode);
}


int CMelanieDlg::InvKinematic(double value[2][3], double result[3])
//Calculates inverse kinematics
//"value" is a 2x3 matrix that includes the three coordenates (x,y,z)
//and the three lengths of the leg parts
//"results" will have the angles calculated
//The function gives value 0 if no error in calculations
{
	double			xb, xbp;	//interim calculation of X proyection
	double			L1,L2,L3,
					a1,a2,a3,
					x,y,z;		//temporary values
	int				errorcode=0;			//error code. By default no error

	L1=value[LENGTH][COXA];
	L2=value[LENGTH][FEMUR];
	L3=value[LENGTH][TIBIA];

	x=value[COORD][X];
	y=value[COORD][Y];
	z=value[COORD][Z];

	xb=sqrt(pow(x,2) + pow(z,2))-L1;

	if (sqrt(pow(xb,2)+pow(y,2)) >= (L2+L3))
	{
		//The (x,y,z) point is out of the accesible region
		//this routine will approximate to a point in the
		//accesible region
		xbp= (xb==0? 0:(L2+L3)*cos(atan(y/xb)));
		x=sqrt(pow(L1+xbp,2) - pow(z,2));
		x=x<0? -x:x;
		y=sqrt(pow(L2+L3,2) - pow(xbp,2));
		y=y<0? -y:y;
		z=z;
		xb=xbp;
		errorcode=1;
	}
	else
	{	
		//The point is in the accesible region
		//nothing to do
	}

	//Inverse kinematics geometric calculation
	a1= (x==0? 0: atan(z/x));
	a3=(acos((pow(xb,2) + pow(y,2) - pow(L2,2) - pow(L3,2))/(2*L2*L3)));
	a2=asin((sin(a3)*L3)/sqrt(pow(xb,2) + pow(y,2)))+(atan2(y,xb));
	result[0]=a1*180/PI;
	result[0]=(result[0]<0.01 && result[0]>-0.01)? 0 : result[0];
	result[1]=a2*180/PI;
	result[1]=(result[1]<0.01 && result[1]>-0.01)? 0 : result[1];
	result[2]=-a3*180/PI;
	result[2]=(result[2]<0.01 && result[2]>-0.01)? 0 : result[2];

	return (errorcode);
}


unsigned char CMelanieDlg::cConvDegToPos(char cServo, double Deg)
//Convert for a specific servo from Degrees to position values 
//(0-250) as they are used by the servo control card
{
	return(	(unsigned char)
			((double)cPosConv[cServo][0]+
			(double)Deg*
			((double)cPosConv[cServo][1]-(double)cPosConv[cServo][0])/(double)(-45)));
}

double CMelanieDlg::cConvPosToDeg(char cServo, unsigned char cPos)
//Convert for a specific servo from position values 
//(0-250) as they are used by the servo control card
//to degrees
{
	return(((double)cPos - (double)cPosConv[cServo][0])*
		(double)(-45)/((double)cPosConv[cServo][1]-(double)cPosConv[cServo][0]));
}




void CMelanieDlg::MoveLeg(double dcoord[3][2][LEGS], int iMode, int iPau, int dIncDef,double yHigh, int iLeg1, int iLeg2, int iLeg3, int iLeg4, int iLeg5, int iLeg6 )
//Move a leg from one position to another 
//Mode=0 indicate movement with a wave in the Y axis 
//Mode=1 indicate linear direct movement between coordinates
//iPau is the pause between movements 
//dIncDef is the default increment for movements . 180 should be multiple of it.
//yHigh is the top value of Y on the arc when moving the leg with mode=0
//iLegx are the legs to move. At least one leg should be specified
{
	double result[3];
	double value[2][3];		//Matrix with two lines (Lenght and angle)

	int 	iServo[3];			//Temporal variable. Store numbers of servos of a leg

	
	double	dTx	=0,				//Index for periodical waves of leg
			dInc;				//Increment index for wave length variation

	int		iPos[LEGS][2][3],			//Position of each servo (new and previous)
			iSpeed[3],			//Speed to apply to each servo of a leg
			iLeg,
			iLegMatrix[6],		//Temporary matrix for legs to move
			iLegIndex,			//Index to use with the matrix
			n=0;

	//copy values of legs to move in the matrix form
	iLegMatrix[LEG1]=iLeg1;
	iLegMatrix[LEG2]=iLeg2;
	iLegMatrix[LEG3]=iLeg3;
	iLegMatrix[LEG4]=iLeg4;
	iLegMatrix[LEG5]=iLeg5;
	iLegMatrix[LEG6]=iLeg6;

	for (iLeg=LEG1;iLeg<=LEG6;iLeg++)
	{
		//Load default coordinate actual and previous position (just used in first
		//calculation of servo speeds. The same value asure max speed in the first
		//positioning.
		iPos[iLeg][1][TIBIA]=iPos[iLeg][0][TIBIA]=0; 
		iPos[iLeg][1][FEMUR]=iPos[iLeg][0][FEMUR]=0; 
		iPos[iLeg][1][COXA]	=iPos[iLeg][0][COXA]=0;
	}

	//Load default increment value
	dInc=dIncDef;
	

	//Load default lenght in mm of the different parts of the leg
	value[LENGTH][COXA]=64;
	value[LENGTH][FEMUR]=40;
	value[LENGTH][TIBIA]=74;


	for (n=0;n<=(180/dIncDef);n++)			//Main loop
	{

		for(iLegIndex=LEG1;(iLegMatrix[iLegIndex]!=-1) && (iLegIndex<=LEG6);iLegIndex++)
		{
			iLeg=iLegMatrix[iLegIndex];

			iServo[TIBIA]	= (iLeg<=LEG3)?iLeg*3+1:iLeg*3+2;
			iServo[FEMUR]	= (iLeg<=LEG3)?iLeg*3+2:iLeg*3+3;
			iServo[COXA]	= (iLeg<=LEG3)?iLeg*3+3:iLeg*3+4;


			value[COORD][X]=dcoord[X][0][iLeg]+((dcoord[X][1][iLeg]-dcoord[X][0][iLeg])/180)*(dTx);
			value[COORD][Y]=(iMode==0)?
								(dTx<90)?
									dcoord[Y][0][iLeg]+(yHigh-dcoord[Y][0][iLeg])*sin(dTx*PI/180):	
									dcoord[Y][1][iLeg]+(yHigh-dcoord[Y][1][iLeg])*sin(dTx*PI/180):
								dcoord[Y][0][iLeg]+((dcoord[Y][1][iLeg]-dcoord[Y][0][iLeg])/180)*(dTx);
			value[COORD][Z]=dcoord[Z][0][iLeg]+((dcoord[Z][1][iLeg]-dcoord[Z][0][iLeg])/180)*(dTx);
			

			temp=InvKinematic(value, result);
//			if (temp>0) MessageBox("Error. Values out of range in leg");

			iPos[iLeg][0][TIBIA]=cConvDegToPos(iServo[TIBIA],result[TIBIA]);
			iPos[iLeg][0][FEMUR]=cConvDegToPos(iServo[FEMUR],result[FEMUR]);
			iPos[iLeg][0][COXA]	=cConvDegToPos(iServo[COXA],result[COXA]);
			iSpeed[TIBIA]=iPos[iLeg][0][TIBIA]>iPos[iLeg][1][TIBIA]? 
							8*(iPos[iLeg][0][TIBIA]-iPos[iLeg][1][TIBIA])/iPau:
							8*(iPos[iLeg][1][TIBIA]-iPos[iLeg][0][TIBIA])/iPau;
			iSpeed[FEMUR]=iPos[iLeg][0][FEMUR]>iPos[iLeg][1][FEMUR]? 
							8*(iPos[iLeg][0][FEMUR]-iPos[iLeg][1][FEMUR])/iPau:
							8*(iPos[iLeg][1][FEMUR]-iPos[iLeg][0][FEMUR])/iPau;
			iSpeed[COXA]=iPos[iLeg][0][COXA]>iPos[iLeg][1][COXA]? 
							8*(iPos[iLeg][0][COXA]-iPos[iLeg][1][COXA])/iPau:
							8*(iPos[iLeg][1][COXA]-iPos[iLeg][0][COXA])/iPau;
			SetServoPos(cServo[iServo[TIBIA]]	,iPos[iLeg][0][TIBIA]	,iSpeed[TIBIA]);
			SetServoPos(cServo[iServo[FEMUR]]	,iPos[iLeg][0][FEMUR]	,iSpeed[FEMUR]);
			SetServoPos(cServo[iServo[COXA]]	,iPos[iLeg][0][COXA]	,iSpeed[COXA]);

			iPos[iLeg][1][TIBIA]=iPos[iLeg][0][TIBIA]; 
			iPos[iLeg][1][FEMUR]=iPos[iLeg][0][FEMUR]; 
			iPos[iLeg][1][COXA]	=iPos[iLeg][0][COXA];


		}

		dTx+=dInc;
		Sleep(iPau*20/iLegIndex);

	}


}



void CMelanieDlg::OffOnRelay()
//Activate, deactivate the Relay, to generate a reset to the 
//digital servos
{
		SetDPort(16);
		Sleep(10);
		SetDPort(0);
}

void CMelanieDlg::ChkCurr()
//Read A/D Conversion -->Current
//As the current value is not stable, take several measurements and calculate average
{

	unsigned char	cValue [4][10],Lectures=10;
	long int 		ires[4];			//Acumulated results
	int				iADCh;			//A/D Channel to read

	//------ A/D CHIP 6 ----------------------------------------
	ires[0] = ires[1] = ires[2] = ires[3] = 0;
	for (temp=0; temp<Lectures; temp++)
	{
		Board.GenerateStartCondition();
		Board.OutputByteToI2C(cAD6Add);
		Board.GenerateAcknowledge();

		Board.OutputByteToI2C(0x44); //Serial output of controlbyte for autoincrement
		Board.GenerateAcknowledge();
		Board.GenerateStopCondition();
		Board.GenerateStartCondition();
		Board.OutputByteToI2C(cAD6Add+1);
		Board.GenerateAcknowledge();
		Board.InputByteFromI2C();

		//Read 4 AD channels
		for (iADCh=0; iADCh<=3; iADCh++)
		{
			Board.GenerateAcknowledgeFromMaster();
			cValue [iADCh][temp] = Board.InputByteFromI2C();		
			ires[iADCh] += cValue [iADCh][temp];
		}
		Board.GenerateAcknowledge();
		Board.GenerateStopCondition();
	}
	Current[LEG6] = ires[0]/Lectures;
	Current[LEG3] = ires[1]/Lectures;
	Current[LEG2] = ires[2]/Lectures;
	Voltage[0]	  = ires[3]/Lectures;


	//------ A/D CHIP 7 ----------------------------------------
	ires[0] = ires[1] = ires[2] = ires[3] = 0;
	for (temp=0; temp<Lectures; temp++)
	{
		Board.GenerateStartCondition();
		Board.OutputByteToI2C(cAD7Add);
		Board.GenerateAcknowledge();

		Board.OutputByteToI2C(0x44); //Serial output of controlbyte for autoincrement
		Board.GenerateAcknowledge();
		Board.GenerateStopCondition();
		Board.GenerateStartCondition();
		Board.OutputByteToI2C(cAD7Add+1);
		Board.GenerateAcknowledge();
		Board.InputByteFromI2C();

		//Read 4 AD channels
		for (iADCh=0; iADCh<=3; iADCh++)
		{
			Board.GenerateAcknowledgeFromMaster();
			cValue [iADCh][temp] = Board.InputByteFromI2C();	
			ires[iADCh] += cValue [iADCh][temp];
		}
		Board.GenerateAcknowledge();
		Board.GenerateStopCondition();
	}
	Current[LEG1] = ires[0]/Lectures;
	Current[LEG4] = ires[1]/Lectures;
	Current[LEG5] = 2*ires[2]/Lectures;	//multiplied by 2 as is a special servo
	Voltage[1]	  = ires[3]/Lectures;
}

void CMelanieDlg::ChkPos(unsigned char cPos[20],unsigned char cAD[20])
//Read A/D values of legs potenciometers.
//Return through cPos the position of each servo in terms of Servo control card values
//The process reads several times (variable "Lectures") and calculate the average in
//order to avoid the variable value due to a variable signal
{

	//Empirical measurement of angles and AD measurements in two
	//positions per leg. This allow calculating the line
	//between both points and therefore the relation between
	//angles and A/D measurements
	//					AD0	An0	AD1	An1
	byte bCal[21][4]=  {  0,  0,  0,  0,	// not used
						 59, 20,195,198,	// Servo 01
						 49, 57,121,172,	// Servo 02
						 93, 58,205,198,	// Servo 03
						 61, 20,177,168,	// Servo 04
						 43, 47,128,187,	// Servo 05
						 83, 43,176,158,	// Servo 06
						 71, 30,202,193,	// Servo 07
						 39, 42,134,197,	// Servo 08
						 78, 43,174,168,	// Servo 09
						  0,  0,  0,  0,	// Servo 10 - No A/D check
						 72, 32,198,187,	// Servo 11
						 47, 58,131,203,	// Servo 12
						 48,  5,145,125,	// Servo 13
						 60, 20,187,182,	// Servo 14
						 65, 38,184,193,	// Servo 15
						 79, 42,148,130,	// Servo 16
						 52, 10,177,167,	// Servo 17
						 44, 48,134,198,	// Servo 18
						 57, 15,158,145,	// Servo 19
						  0,  0,  0,  0};	// Servo 20 (Not used)

	int				Lectures=100;
	long int 		ires[20];			//accumulated lectures (20 A/D channels)
	int				iADCh,				//A/D chip to read	
					i;					//temp variable

	for (i=0; i<=20; i++) ires[i] = 3;

	for (i=0; i<5; i++)	//Loop to read each of the 5 A/D chips
	{
		iADCh=cAD1Add+i*2;
		for (temp=0; temp<Lectures; temp++)	//Loop to read several times each A/D value
		{
			Board.GenerateStartCondition();
			Board.OutputByteToI2C(iADCh);
			Board.GenerateAcknowledge();

			Board.OutputByteToI2C(0x44); //Serial output of controlbyte for autoincrement
			Board.GenerateAcknowledge();
			Board.GenerateStopCondition();
			Board.GenerateStartCondition();
			Board.OutputByteToI2C(iADCh+1);
			Board.GenerateAcknowledge();
			Board.InputByteFromI2C();

			//Read 4 AD channels
			Board.GenerateAcknowledgeFromMaster();
			ires[i*4+0] = ires[i*4+0] + Board.InputByteFromI2C();
			Board.GenerateAcknowledgeFromMaster();
			ires[i*4+1] += Board.InputByteFromI2C();
			Board.GenerateAcknowledgeFromMaster();
			ires[i*4+2] += Board.InputByteFromI2C();
			Board.GenerateAcknowledgeFromMaster();
			ires[i*4+3] += Board.InputByteFromI2C();
			Board.GenerateAcknowledge();
			Board.GenerateStopCondition();
		}
	}
	//Correspondence between A/D chanels and servos
	cAD[ 2]=(int)((float)ires[ 0]/Lectures);
	cAD[ 4]=(int)((float)ires[ 1]/Lectures);
	cAD[ 6]=(int)((float)ires[ 2]/Lectures);
	cAD[11]=(int)((float)ires[ 3]/Lectures);
	cAD[12]=(int)((float)ires[ 4]/Lectures);
	cAD[13]=(int)((float)ires[ 5]/Lectures);
	cAD[05]=(int)((float)ires[ 6]/Lectures);
	cAD[03]=(int)((float)ires[ 7]/Lectures);
	cAD[19]=(int)((float)ires[ 8]/Lectures);
	cAD[18]=(int)((float)ires[ 9]/Lectures);
	cAD[ 8]=(int)((float)ires[10]/Lectures);
	cAD[16]=(int)((float)ires[11]/Lectures);
	cAD[15]=(int)((float)ires[12]/Lectures);
	cAD[ 7]=(int)((float)ires[13]/Lectures);
	cAD[ 9]=(int)((float)ires[14]/Lectures);
	cAD[17]=(int)((float)ires[15]/Lectures);
	cAD[14]=(int)((float)ires[17]/Lectures);
	cAD[ 1]=(int)((float)ires[18]/Lectures);


	for (i=1; i<=9; i++)
	{
		cPos[i] = bCal[i][1]-((bCal[i][0]-cAD[i])*
			(bCal[i][1]-bCal[i][3])/(bCal[i][0]-bCal[i][2]));
	}

	for (i=11; i<=19; i++)
	{
		cPos[i] = bCal[i][1]-((bCal[i][0]-cAD[i])*
			(bCal[i][1]-bCal[i][3])/(bCal[i][0]-bCal[i][2]));
	}

}

void CMelanieDlg::GetActualCoords(double dcoord[3][2][LEGS], int iSelect)
//Get the actual coords of each leg by checking the A/D values
//and store them in dcoords[][0][] not modifyind dcoords[][1][]
//"iSelect" allow to choose between getting the coords of all servos or only
//those of a specific leg. The rest of coordinates would not be altered.
//by default obtain data of all servos
{
	unsigned char cPos[20];		// Used to call ChkPos function
	unsigned char cAD[20];		// Used to call ChkPos function
	int		iLeg;				// Leg index
	double	value[2][3],		// Used to call "FwdKinematics" function
			result[3];			// Used to call "FwdKinematics" function (Coords of a leg)
	int 	iServo[3];			//Temporal variable. Store numbers of servos of a leg

	value[LENGTH][COXA]=64;
	value[LENGTH][FEMUR]=40;
	value[LENGTH][TIBIA]=74;

	ChkPos(cPos, cAD);	//Check actual position of servos

	for		(iLeg=(iSelect==-1)?LEG1:iSelect;iLeg<=((iSelect==-1)?LEG6:iSelect); iLeg++)
	{
		iServo[TIBIA]	= (iLeg<=LEG3)?iLeg*3+1:iLeg*3+2;
		iServo[FEMUR]	= (iLeg<=LEG3)?iLeg*3+2:iLeg*3+3;
		iServo[COXA]	= (iLeg<=LEG3)?iLeg*3+3:iLeg*3+4;

		value[ANGLE][TIBIA]=cConvPosToDeg(iServo[TIBIA],cPos[iServo[TIBIA]]);	
		value[ANGLE][FEMUR]=cConvPosToDeg(iServo[FEMUR],cPos[iServo[FEMUR]]);	
		value[ANGLE][COXA] =cConvPosToDeg(iServo[COXA],cPos[iServo[COXA]]);	

		temp=FwdKinematic (value, result);	//Perform Forward Kinematics
		//Actual position of leg
		dcoord[X][0][iLeg]=result[X];
		dcoord[Y][0][iLeg]=result[Y];
		dcoord[Z][0][iLeg]=result[Z];
	}
}

void CMelanieDlg::OnAllServosOn() 
//Activate All Switched off servos
{
		//Update all servo form activation switches
		m_servo1  = m_servo2  = m_servo3  = TRUE;
		m_servo4  = m_servo5  = m_servo6  = TRUE;
		m_servo7  = m_servo8  = m_servo9  = TRUE;
		m_servo10 = TRUE;
		m_servo11 = m_servo12 = m_servo13 = TRUE;
		m_servo14 = m_servo15 = m_servo16 = TRUE;
		m_servo17 = m_servo18 = m_servo19 = TRUE;
		UpdateData(FALSE);
		ActivateServo(cServo[ 1],m_pos01);
		ActivateServo(cServo[ 2],m_pos02);
		ActivateServo(cServo[ 3],m_pos03);
		ActivateServo(cServo[ 4],m_pos04);
		ActivateServo(cServo[ 5],m_pos05);
		ActivateServo(cServo[ 6],m_pos06);
		ActivateServo(cServo[ 7],m_pos07);
		ActivateServo(cServo[ 8],m_pos08);
		ActivateServo(cServo[ 9],m_pos09);
		ActivateServo(cServo[10],m_pos10);
		ActivateServo(cServo[11],m_pos11);
		ActivateServo(cServo[12],m_pos12);
		ActivateServo(cServo[13],m_pos13);
		ActivateServo(cServo[14],m_pos14);
		ActivateServo(cServo[15],m_pos15);
		ActivateServo(cServo[16],m_pos16);
		ActivateServo(cServo[17],m_pos17);
		ActivateServo(cServo[18],m_pos18);
		ActivateServo(cServo[19],m_pos19);
}

void CMelanieDlg::OnAllServosOff() 
//Deactivate All servos
{
	int i;

	//Update all servo form activation switches
	m_servo1  = m_servo2  = m_servo3  = FALSE;
	m_servo4  = m_servo5  = m_servo6  = FALSE;
	m_servo7  = m_servo8  = m_servo9  = FALSE;
	m_servo10 = FALSE;
	m_servo11 = m_servo12 = m_servo13 = FALSE;
	m_servo14 = m_servo15 = m_servo16 = FALSE;
	m_servo17 = m_servo18 = m_servo19 = FALSE;
	UpdateData(FALSE);
	for(i=1;i<=19;i++) DeactivateServo(cServo[i]);	
//	OffOnRelay();		//Reset digital servos

}

void CMelanieDlg::OnWaveUp() 
//Move up the robot with waves method
{
	double	dcoord[3][2][LEGS]; //Coordinates limits of all servos of each leg
	int		iLeg;
	double	dTx[LEGS];	//Index for periodical waves of each leg
	double	x0=  90,			//Coordinates limits
			x1=  77,
			y0=-100,
			y1= -70,
			z0= -20,
			z1=  20;


	UpdateData(TRUE);				//Read Form	
	if (m_wave1)	//Depending on the type of wave it is stablishes a different phase
	{
		dTx[LEG1]=1;
		dTx[LEG2]=181;
		dTx[LEG3]=1;
		dTx[LEG4]=181;
		dTx[LEG5]=1;
		dTx[LEG6]=181;
	}
	else
	{
		dTx[LEG1]=0;
		dTx[LEG2]=144;
		dTx[LEG3]=72;
		dTx[LEG4]=108;
		dTx[LEG5]=36;
		dTx[LEG6]=180;
	}

//Prepare position

	for (iLeg=LEG1;iLeg<=LEG6;iLeg++)
	{
		dcoord[X][1][iLeg]=90;
		dcoord[Y][1][iLeg]=-55;
	}

	dcoord[Z][1][LEG1]=-45;
	dcoord[Z][1][LEG4]=-45;
	dcoord[Z][1][LEG2]=  0;
	dcoord[Z][1][LEG5]=  0;
	dcoord[Z][1][LEG3]= 45;
	dcoord[Z][1][LEG6]= 45;

	GetActualCoords(dcoord);

	MoveLeg(dcoord,0,15,12,-60,LEG1,LEG4,LEG2,LEG5,LEG3,LEG6);

	Sleep(500);


//up
	for (iLeg=LEG1;iLeg<=LEG6;iLeg++)
	{
		dcoord[X][1][iLeg]=90;
		dcoord[Y][1][iLeg]=-100;
	}

	dcoord[Z][1][LEG1]=-45;
	dcoord[Z][1][LEG4]=-45;
	dcoord[Z][1][LEG2]=  0;
	dcoord[Z][1][LEG5]=  0;
	dcoord[Z][1][LEG3]= 45;
	dcoord[Z][1][LEG6]= 45;

	GetActualCoords(dcoord);

	MoveLeg(dcoord,1,15,12,-60,LEG1,LEG4,LEG2,LEG5,LEG3,LEG6);

	Sleep(100);

//locate
	for (iLeg=LEG1;iLeg<=LEG6;iLeg++)
	{
		dcoord[X][0][iLeg]=dcoord[X][1][iLeg];
		dcoord[Y][0][iLeg]=dcoord[Y][1][iLeg];
		dcoord[Z][0][iLeg]=dcoord[Z][1][iLeg];

		
		dcoord[X][1][iLeg]=x0;	
		dcoord[Y][1][iLeg]=(dTx[iLeg]<180)? 
							y0:
							y0-(y1-y0)*sin(dTx[iLeg]*PI/180);	
		dcoord[Z][1][iLeg]=(dTx[iLeg]<180)?
							z0-((z0-z1)/180)*dTx[iLeg]:
							(z0-(z0+z1)/2)*cos(dTx[iLeg]*PI/180);
	}

	MoveLeg(dcoord,0,15,12,-60,LEG1, LEG3, LEG5);
	MoveLeg(dcoord,0,15,12,-60,LEG2, LEG4, LEG6);
}

void CMelanieDlg::OnWaveFwd() 
//Move forward the robot with waves method
{
	double result[3];
	double value[LEGS][2][3],	//Matrix with two lines (Lenght and angle)
			val[2][3];

	int 	iServo[3];			//Temporal variable. Store numbers of servos of a leg

	double	dTx[LEGS],	//Index for periodical waves of each leg
			dIncDef1,		//Default increment for first wave half
			dIncDef2,		//Default increment for second wave half
			dInc1[LEGS],	//Especific increment for each leg for first wave half
			dInc2[LEGS],	//Especific increment for each leg for second wave half
			dInc[LEGS],		//Increment index for wave length variation
			dSens[LEGS]={27,30,25,25,32,22.5};	//Sensitivity for detecting obstacles

	int		iPos[LEGS][2][3],			//Position of each servo (new and previous)
			iSpeed[3],					//Speed to apply to each servo of a leg
			iPau,						//Pause between movements
			iLeg,						//Number of leg
			n;

	double	x0=  90,			//Coordinates limits
			x1=  77,
			y0=-100,
			y1= -60,
			z0= -20,
			z1=  20;

	double	dcoord[3][2][LEGS]; //Coordinates limits of all servos of each leg


	UpdateData(TRUE);				//Read Form	
	if (m_ObstaclesChk) iPau=20;
	else iPau=12;

	UpdateData(TRUE);				//Read Form	
	if (m_wave1)	//Depending on the type of wave it is stablishes a different phase
	{
		dTx[LEG1]=1;
		dTx[LEG2]=181;
		dTx[LEG3]=1;
		dTx[LEG4]=181;
		dTx[LEG5]=1;
		dTx[LEG6]=181;
		dIncDef1=15;		//Default increment for first wave half
		dIncDef2=15;		//Default increment for second wave half
	}
	else
	{
		dTx[LEG1]=0;
		dTx[LEG2]=144;
		dTx[LEG3]=72;
		dTx[LEG4]=108;
		dTx[LEG5]=36;
		dTx[LEG6]=180;
		dIncDef1=3;			//Default increment for first wave half
		dIncDef2=15;		//Default increment for second wave half
	}


	for (iLeg=LEG1;iLeg<=LEG6;iLeg++)
	{
		//Load default coordinate ranges
		dcoord[X][0][iLeg]=x0;
		dcoord[X][1][iLeg]=x1;
		dcoord[Y][0][iLeg]=y0;
		dcoord[Y][1][iLeg]=y1;
		dcoord[Z][0][iLeg]=z0;
		dcoord[Z][1][iLeg]=z1;

		//Load default coordinate actual and previous position (just used in first
		//calculation of servo speeds. The same value asure max speed in the first
		//positioning.
		iPos[iLeg][1][TIBIA]=iPos[iLeg][0][TIBIA]=0; 
		iPos[iLeg][1][FEMUR]=iPos[iLeg][0][FEMUR]=0; 
		iPos[iLeg][1][COXA]	=iPos[iLeg][0][COXA]=0;

		//Load default increment values
		dInc1[iLeg]=dIncDef1;
		dInc2[iLeg]=dIncDef2;

		//Load default lenght in mm of the different parts of the leg
		value[iLeg][LENGTH][COXA]	=val[LENGTH][COXA]	=64;
		value[iLeg][LENGTH][FEMUR]	=val[LENGTH][FEMUR]	=40;
		value[iLeg][LENGTH][TIBIA]	=val[LENGTH][TIBIA]	=74;
	}



	for (n=0;n<=5*(180/dIncDef1+180/dIncDef2);n++)			//Main loop
	{

		if (m_ObstaclesChk) ChkCurr();		//Check Current Values for obstacle detection
		for (iLeg=LEG1;iLeg<=LEG6;iLeg++)
		{

			//Obstacle detection
			if ((m_ObstaclesChk) && (dTx[iLeg]>=(270+2*dIncDef2)) && (Current[iLeg]>=dSens[iLeg]) /*&& (iLeg==LEG3)*/)
			{
				dcoord[Y][0][iLeg]=value[iLeg][COORD][Y];		//<<--sería mejor el valor de lectura A/D
				dcoord[Z][1][iLeg]=dcoord[Z][1][iLeg]+value[iLeg][COORD][Z]-dcoord[Z][0][iLeg];
				dcoord[Z][0][iLeg]=value[iLeg][COORD][Z];
				dInc2[iLeg]=dInc2[iLeg]*179.0/(538.0-dTx[iLeg]); //modify second wave half increment to compensate waves gap (desfase)
				dTx[iLeg]=1;
//				MessageBox("Colision");
			}
			iServo[TIBIA]	= (iLeg<=LEG3)?iLeg*3+1:iLeg*3+2;
			iServo[FEMUR]	= (iLeg<=LEG3)?iLeg*3+2:iLeg*3+3;
			iServo[COXA]	= (iLeg<=LEG3)?iLeg*3+3:iLeg*3+4;

			value[iLeg][COORD][X]=dcoord[X][0][iLeg];	
			value[iLeg][COORD][Y]=(dTx[iLeg]<180)? 
							dcoord[Y][0][iLeg]:
							dcoord[Y][0][iLeg]-(dcoord[Y][1][iLeg]-dcoord[Y][0][iLeg])*sin(dTx[iLeg]*PI/180);	
			value[iLeg][COORD][Z]=(dTx[iLeg]<180)?
							dcoord[Z][0][iLeg]-((dcoord[Z][0][iLeg]-dcoord[Z][1][iLeg])/180)*dTx[iLeg]:
							(dcoord[Z][0][iLeg]-(dcoord[Z][0][iLeg]+dcoord[Z][1][iLeg])/2)*cos(dTx[iLeg]*PI/180);
						
			val[COORD][X]=value[iLeg][COORD][X];
			val[COORD][Y]=value[iLeg][COORD][Y];
			val[COORD][Z]=value[iLeg][COORD][Z];
			temp=InvKinematic(val, result);
//			if (temp>0) MessageBox("Error. Values out of range in leg");

			iPos[iLeg][0][TIBIA]=cConvDegToPos(iServo[TIBIA],result[TIBIA]);
			iPos[iLeg][0][FEMUR]=cConvDegToPos(iServo[FEMUR],result[FEMUR]);
			iPos[iLeg][0][COXA]	=cConvDegToPos(iServo[COXA],result[COXA]);
			iSpeed[TIBIA]=iPos[iLeg][0][TIBIA]>iPos[iLeg][1][TIBIA]? 
							8*(iPos[iLeg][0][TIBIA]-iPos[iLeg][1][TIBIA])/iPau:
							8*(iPos[iLeg][1][TIBIA]-iPos[iLeg][0][TIBIA])/iPau;
			iSpeed[FEMUR]=iPos[iLeg][0][FEMUR]>iPos[iLeg][1][FEMUR]? 
							8*(iPos[iLeg][0][FEMUR]-iPos[iLeg][1][FEMUR])/iPau:
							8*(iPos[iLeg][1][FEMUR]-iPos[iLeg][0][FEMUR])/iPau;
			iSpeed[COXA]=iPos[iLeg][0][COXA]>iPos[iLeg][1][COXA]? 
							8*(iPos[iLeg][0][COXA]-iPos[iLeg][1][COXA])/iPau:
							8*(iPos[iLeg][1][COXA]-iPos[iLeg][0][COXA])/iPau;
			SetServoPos(cServo[iServo[TIBIA]]	,iPos[iLeg][0][TIBIA]	,iSpeed[TIBIA]);
			SetServoPos(cServo[iServo[FEMUR]]	,iPos[iLeg][0][FEMUR]	,iSpeed[FEMUR]);
			SetServoPos(cServo[iServo[COXA]]	,iPos[iLeg][0][COXA]	,iSpeed[COXA]);

			iPos[iLeg][1][TIBIA]=iPos[iLeg][0][TIBIA]; 
			iPos[iLeg][1][FEMUR]=iPos[iLeg][0][FEMUR]; 
			iPos[iLeg][1][COXA]	=iPos[iLeg][0][COXA];


			if (dTx[iLeg]>=180) dInc[iLeg]=dInc2[iLeg];	//Allow changing wave length
			else				dInc[iLeg]=dInc1[iLeg];
			dTx[iLeg]+=dInc[iLeg];
			if (dTx[iLeg]>=360)
			{
				dTx[iLeg]=0;
				dInc2[iLeg]=dIncDef2;	//Set second wave half increment to default (in case it was modified due to a collision)
				dcoord[Z][1][iLeg]=z1;
			}
			if (dTx[iLeg]>=270) 
			{
				dcoord[Y][0][iLeg]=y0; //Allow moving leg to default position in case of previous collision
				dcoord[Z][0][iLeg]=z0;
			}

		}
		
		
//	if (m_ObstaclesChk==FALSE) Sleep(iPau*2);

	}

}

void CMelanieDlg::OnWaveDown() 
//Move down the robot with waves method
{
	double	dcoord[3][2][LEGS]; //Coordinates limits of all servos of each leg
	int		iLeg;

//Prepare position

	for (iLeg=LEG1;iLeg<=LEG6;iLeg++)
	{
		dcoord[X][1][iLeg]=90;
		dcoord[Y][1][iLeg]=-100;
	}

	dcoord[Z][1][LEG1]=-45;
	dcoord[Z][1][LEG4]=-45;
	dcoord[Z][1][LEG2]=  0;
	dcoord[Z][1][LEG5]=  0;
	dcoord[Z][1][LEG3]= 45;
	dcoord[Z][1][LEG6]= 45;

	GetActualCoords(dcoord);

	MoveLeg(dcoord,0,15,12,-60,LEG1, LEG3, LEG5);
	MoveLeg(dcoord,0,15,12,-60,LEG2, LEG4, LEG6);

	Sleep(500);


//Down
	for (iLeg=LEG1;iLeg<=LEG6;iLeg++)
	{
		dcoord[X][1][iLeg]=90;
		dcoord[Y][1][iLeg]=-55;
	}

	dcoord[Z][1][LEG1]=-45;
	dcoord[Z][1][LEG4]=-45;
	dcoord[Z][1][LEG2]=  0;
	dcoord[Z][1][LEG5]=  0;
	dcoord[Z][1][LEG3]= 45;
	dcoord[Z][1][LEG6]= 45;

	GetActualCoords(dcoord);

	MoveLeg(dcoord,1,15,12,-60,LEG1,LEG4,LEG2,LEG5,LEG3,LEG6);
}

void CMelanieDlg::OnChkBattStatus() 
//Check Batteries Status
{
	ChkCurr();
	m_voltlog=Voltage[0];
	m_voltpow=Voltage[1];

	UpdateData(FALSE);						//Update Form	
}

void CMelanieDlg::OnWavePreset() 
//Go Up, Forward and Down
{
	OnWaveUp();
	OnWaveFwd();
	OnWaveDown();
}

void CMelanieDlg::OnWaveFwdShort() 
//Short Forward 
{
/*

  --->>> Ojo, quitar esto porque es temporal


  */
	double result[3];
	double value[LEGS][2][3],	//Matrix with two lines (Lenght and angle)
			val[2][3];

	int 	iServo[3];			//Temporal variable. Store numbers of servos of a leg

	double	dTx[LEGS],	//Index for periodical waves of each leg
			dIncDef1,		//Default increment for first wave half
			dIncDef2,		//Default increment for second wave half
			dInc1[LEGS],	//Especific increment for each leg for first wave half
			dInc2[LEGS],	//Especific increment for each leg for second wave half
			dInc[LEGS],		//Increment index for wave length variation
			dSens[LEGS]={27,30,25,25,32,22.5};	//Sensitivity for detecting obstacles

	int		iPos[LEGS][2][3],			//Position of each servo (new and previous)
			iSpeed[3],					//Speed to apply to each servo of a leg
			iPau,						//Pause between movements
			iLeg,						//Number of leg
			n;

	double	x0=  90,			//Coordinates limits
			x1=  77,
			y0=-100,
			y1= -60,
			z0= -20,
			z1=  20;

	double	dcoord[3][2][LEGS]; //Coordinates limits of all servos of each leg


	UpdateData(TRUE);				//Read Form	
	if (m_ObstaclesChk) iPau=20;
	else iPau=12;

	UpdateData(TRUE);				//Read Form	
	if (m_wave1)	//Depending on the type of wave it is stablishes a different phase
	{
		dTx[LEG1]=1;
		dTx[LEG2]=181;
		dTx[LEG3]=1;
		dTx[LEG4]=181;
		dTx[LEG5]=1;
		dTx[LEG6]=181;
		dIncDef1=15;		//Default increment for first wave half
		dIncDef2=15;		//Default increment for second wave half
	}
	else
	{
		dTx[LEG1]=0;
		dTx[LEG2]=144;
		dTx[LEG3]=72;
		dTx[LEG4]=108;
		dTx[LEG5]=36;
		dTx[LEG6]=180;
		dIncDef1=3;			//Default increment for first wave half
		dIncDef2=15;		//Default increment for second wave half
	}


	for (iLeg=LEG1;iLeg<=LEG6;iLeg++)
	{
		//Load default coordinate ranges
		dcoord[X][0][iLeg]=x0;
		dcoord[X][1][iLeg]=x1;
		dcoord[Y][0][iLeg]=y0;
		dcoord[Y][1][iLeg]=y1;
		dcoord[Z][0][iLeg]=z0;
		dcoord[Z][1][iLeg]=z1;

		//Load default coordinate actual and previous position (just used in first
		//calculation of servo speeds. The same value asure max speed in the first
		//positioning.
		iPos[iLeg][1][TIBIA]=iPos[iLeg][0][TIBIA]=0; 
		iPos[iLeg][1][FEMUR]=iPos[iLeg][0][FEMUR]=0; 
		iPos[iLeg][1][COXA]	=iPos[iLeg][0][COXA]=0;

		//Load default increment values
		dInc1[iLeg]=dIncDef1;
		dInc2[iLeg]=dIncDef2;

		//Load default lenght in mm of the different parts of the leg
		value[iLeg][LENGTH][COXA]	=val[LENGTH][COXA]	=64;
		value[iLeg][LENGTH][FEMUR]	=val[LENGTH][FEMUR]	=40;
		value[iLeg][LENGTH][TIBIA]	=val[LENGTH][TIBIA]	=74;
	}



	for (n=0;n<=2*(180/dIncDef1+180/dIncDef2);n++)			//Main loop
	{

		if (m_ObstaclesChk) ChkCurr();		//Check Current Values for obstacle detection
		for (iLeg=LEG1;iLeg<=LEG6;iLeg++)
		{

			//Obstacle detection
			if ((m_ObstaclesChk) && (dTx[iLeg]>=(270+2*dIncDef2)) && (Current[iLeg]>=dSens[iLeg]) /*&& (iLeg==LEG3)*/)
			{
				dcoord[Y][0][iLeg]=value[iLeg][COORD][Y];		//<<--sería mejor el valor de lectura A/D
				dcoord[Z][1][iLeg]=dcoord[Z][1][iLeg]+value[iLeg][COORD][Z]-dcoord[Z][0][iLeg];
				dcoord[Z][0][iLeg]=value[iLeg][COORD][Z];
				dInc2[iLeg]=dInc2[iLeg]*179.0/(538.0-dTx[iLeg]); //modify second wave half increment to compensate waves gap (desfase)
				dTx[iLeg]=1;
//				MessageBox("Colision");
			}
			iServo[TIBIA]	= (iLeg<=LEG3)?iLeg*3+1:iLeg*3+2;
			iServo[FEMUR]	= (iLeg<=LEG3)?iLeg*3+2:iLeg*3+3;
			iServo[COXA]	= (iLeg<=LEG3)?iLeg*3+3:iLeg*3+4;

			value[iLeg][COORD][X]=dcoord[X][0][iLeg];	
			value[iLeg][COORD][Y]=(dTx[iLeg]<180)? 
							dcoord[Y][0][iLeg]:
							dcoord[Y][0][iLeg]-(dcoord[Y][1][iLeg]-dcoord[Y][0][iLeg])*sin(dTx[iLeg]*PI/180);	
			value[iLeg][COORD][Z]=(dTx[iLeg]<180)?
							dcoord[Z][0][iLeg]-((dcoord[Z][0][iLeg]-dcoord[Z][1][iLeg])/180)*dTx[iLeg]:
							(dcoord[Z][0][iLeg]-(dcoord[Z][0][iLeg]+dcoord[Z][1][iLeg])/2)*cos(dTx[iLeg]*PI/180);
						
			val[COORD][X]=value[iLeg][COORD][X];
			val[COORD][Y]=value[iLeg][COORD][Y];
			val[COORD][Z]=value[iLeg][COORD][Z];
			temp=InvKinematic(val, result);
//			if (temp>0) MessageBox("Error. Values out of range in leg");

			iPos[iLeg][0][TIBIA]=cConvDegToPos(iServo[TIBIA],result[TIBIA]);
			iPos[iLeg][0][FEMUR]=cConvDegToPos(iServo[FEMUR],result[FEMUR]);
			iPos[iLeg][0][COXA]	=cConvDegToPos(iServo[COXA],result[COXA]);
			iSpeed[TIBIA]=iPos[iLeg][0][TIBIA]>iPos[iLeg][1][TIBIA]? 
							8*(iPos[iLeg][0][TIBIA]-iPos[iLeg][1][TIBIA])/iPau:
							8*(iPos[iLeg][1][TIBIA]-iPos[iLeg][0][TIBIA])/iPau;
			iSpeed[FEMUR]=iPos[iLeg][0][FEMUR]>iPos[iLeg][1][FEMUR]? 
							8*(iPos[iLeg][0][FEMUR]-iPos[iLeg][1][FEMUR])/iPau:
							8*(iPos[iLeg][1][FEMUR]-iPos[iLeg][0][FEMUR])/iPau;
			iSpeed[COXA]=iPos[iLeg][0][COXA]>iPos[iLeg][1][COXA]? 
							8*(iPos[iLeg][0][COXA]-iPos[iLeg][1][COXA])/iPau:
							8*(iPos[iLeg][1][COXA]-iPos[iLeg][0][COXA])/iPau;
			SetServoPos(cServo[iServo[TIBIA]]	,iPos[iLeg][0][TIBIA]	,iSpeed[TIBIA]);
			SetServoPos(cServo[iServo[FEMUR]]	,iPos[iLeg][0][FEMUR]	,iSpeed[FEMUR]);
			SetServoPos(cServo[iServo[COXA]]	,iPos[iLeg][0][COXA]	,iSpeed[COXA]);

			iPos[iLeg][1][TIBIA]=iPos[iLeg][0][TIBIA]; 
			iPos[iLeg][1][FEMUR]=iPos[iLeg][0][FEMUR]; 
			iPos[iLeg][1][COXA]	=iPos[iLeg][0][COXA];


			if (dTx[iLeg]>=180) dInc[iLeg]=dInc2[iLeg];	//Allow changing wave length
			else				dInc[iLeg]=dInc1[iLeg];
			dTx[iLeg]+=dInc[iLeg];
			if (dTx[iLeg]>=360)
			{
				dTx[iLeg]=0;
				dInc2[iLeg]=dIncDef2;	//Set second wave half increment to default (in case it was modified due to a collision)
				dcoord[Z][1][iLeg]=z1;
			}
			if (dTx[iLeg]>=270) 
			{
				dcoord[Y][0][iLeg]=y0; //Allow moving leg to default position in case of previous collision
				dcoord[Z][0][iLeg]=z0;
			}

		}
		
		
//	if (m_ObstaclesChk==FALSE) Sleep(iPau*2);

	}

	
}
