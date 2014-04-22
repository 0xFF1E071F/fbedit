
include	windows.inc
include	kernel32.inc
include	user32.inc
include	comctl32.inc
include gdi32.inc
include wsock32.inc
include ws2_32.inc

includelib kernel32.lib
includelib user32.lib
includelib comctl32.lib
includelib gdi32.lib
includelib wsock32.lib
includelib ws2_32.lib

;#########################################################################
;VKim's Debug

include masm32.inc
include \RadASM30\masm\inc\debug.inc
includelib masm32.lib
includelib \RadASM30\masm\lib\debug.lib

;#########################################################################

IDD_MAIN						equ 101
IDC_TABFUNCTION					equ 102
IDC_IMGCONNECTED				equ 103

IDD_DLGLCMETER					equ 1000
IDC_UDCLCM						equ 1001
IDC_BTNLCMCAL					equ 1002
IDC_BTNLCMMODE					equ 1003

IDD_DLGHSC						equ 1100
IDC_UDCHSC						equ 1101
IDC_BTNHSCDN					equ 1102
IDC_BTNHSCUP					equ 1103
IDC_EDTHSCFRQ					equ 1104

IDD_DLGSCP						equ 1200
IDC_UDCSCP						equ 1201
IDC_TRBADCCLOCK					equ 1202
IDC_TRBADCDELAY					equ 1203
IDC_STCADCSAMPLERATE			equ 1204
IDC_TRBTIMEDIV					equ 1205
IDC_TRBVOLTDIV					equ 1206
IDC_RBNTRIGGERNONE				equ 1207
IDC_RBNTRIGGERRISING			equ 1208
IDC_RBNTRIGGERFALLING			equ 1209
IDC_TRBTRIGGERLEVEL				equ 1210
IDC_CHKSUBSAMPLING				equ 1211
IDC_CHKHOLDSAMPLING				equ 1212
IDC_TRBVPOS						equ 1213
IDC_BTNSRD						equ 1214
IDC_BTNSRU						equ 1215
IDC_BTNADU						equ 1216
IDC_BTNADD						equ 1217
IDC_BTNTDU						equ 1218
IDC_BTNTDD						equ 1219
IDC_BTNVDU						equ 1220
IDC_BTNVDD						equ 1221
IDC_BTNVPU						equ 1222
IDC_BTNVPD						equ 1223
IDC_BTNTLU						equ 1224
IDC_BTNTLD						equ 1225
IDC_CHKTRIPLE					equ 1226
IDC_BTNAUTO						equ 1227

IDD_DLGDDS						equ 1300
IDC_BTNDDSFRQUP					equ 1304
IDC_BTNDDSFRQDN					equ 1302
IDC_EDTDDSFRQ					equ 1303
IDC_UDCDDSFRQ					equ 1301
IDC_BTNDDSWAVEUP        		equ 1307
IDC_BTNDDSWAVEDN        		equ 1305
IDC_STCDDSWAVE          		equ 1306
IDC_BTNDDSAMPUP         		equ 1308
IDC_BTNDDSAMPDN         		equ 1309
IDC_TRBDDSAMP           		equ 1310
IDC_BTNDDSOFSUP         		equ 1311
IDC_TRBDDSOFS           		equ 1312
IDC_BTNDDSOFSDN         		equ 1313

IDD_DLGLGA						equ 1400
IDC_BTNSRUP						equ 1401
IDC_TRBSR						equ 1402
IDC_BTNSRDN						equ 1403
IDC_BTNBSUP						equ 1404
IDC_STCSR						equ 1410
IDC_TRBBS						equ 1405
IDC_BTNBSDN						equ 1406
IDC_STCBS						equ 1415
IDC_CHKLGATRIGALL				equ 1429
IDC_CHKLGATRIGD0				equ 1420
IDC_CHKLGATRIGD1				equ 1421
IDC_CHKLGATRIGD2				equ 1422
IDC_CHKLGATRIGD3				equ 1423
IDC_CHKLGATRIGD4				equ 1424
IDC_CHKLGATRIGD5				equ 1425
IDC_CHKLGATRIGD6				equ 1426
IDC_CHKLGATRIGD7				equ 1427
IDC_CHKLGAMASKALL				equ 1439
IDC_CHKLGAMASKD0				equ 1430
IDC_CHKLGAMASKD1				equ 1431
IDC_CHKLGAMASKD2				equ 1432
IDC_CHKLGAMASKD3				equ 1433
IDC_CHKLGAMASKD4				equ 1434
IDC_CHKLGAMASKD5				equ 1435
IDC_CHKLGAMASKD6				equ 1436
IDC_CHKLGAMASKD7				equ 1437
IDC_BTNLGASAMPLE				equ 1407
IDC_BTNTRGPREVIOUS				equ 1409
IDC_BTNTRGNEXT					equ 1408

IDD_DLGSCPSCRNCLD				equ 2000
IDC_UDCSCPSCRN					equ 2001

IDD_DLGDDSCLD					equ 3000
IDC_UDCDDSSCRN					equ 3001

IDD_DLGLGACLD					equ 4000
IDC_UDCLGASCRN					equ 4001

CMD_DONE						equ 0
CMD_LCMCAL						equ 1
CMD_LCMCAP						equ 2
CMD_LCMIND						equ 3
CMD_FRQCH1						equ 4
CMD_FRQCH2						equ 5
CMD_FRQCH3						equ 6
CMD_SCPSET                      equ 7
CMD_HSCSET						equ 8
CMD_DDSSET						equ 9
CMD_LGASET						equ 10

STM32_CLOCK						equ 200000000
ADCSAMPLESIZE					equ 10000h
ADCSAMPLESTART					equ 64
ADCMAX							equ 4096
ADCMAXMV						equ 2990
ADCDIVMV						equ 500
TEXTHIGHT						equ 64
GRIDSIZE						equ 64
GRIDX							equ 10
GRIDY							equ 8
SCOPEWT							equ GRIDSIZE*GRIDX
SCOPEHT							equ GRIDSIZE*GRIDY

MAXSCPTIMEDIV					equ 21
MAXSCPVOLTDIV					equ 8

LGASAMPLESIZE					equ 32768
MAXLGASAMPLE					equ 15
MAXLGABUFFER					equ 32

DACMAX							equ 4095

;DDS Waveforms
DDS_ModeSinWave					equ 0
DDS_ModeTriWave					equ 1
DDS_ModeSqrWave					equ 2
DDS_ModeSawWave					equ 3
DDS_ModeRevSawWave				equ 4

;DDS SWEEP SubModes
SWEEP_SubModeOff				equ 1
SWEEP_SubModeUp					equ 2
SWEEP_SubModeDown				equ 3
SWEEP_SubModeUpDown				equ 4
SWEEP_SubModePeak				equ 5

DDS_PHASESET					equ 1
DDS_WAVESET						equ 2

BTH_ADDR						equ QWORD ?

SOCKADDR_BTH struct
	addressFamily				WORD ?
	btAddr						BTH_ADDR
	serviceClassId				GUID <>
	port						DWORD ?
SOCKADDR_BTH ends

SCOPERANGE struct
	ydiv						DWORD ?
	ymag						DWORD ?
	range						BYTE 32 dup(?)	
SCOPERANGE ends

SCOPETIME struct
	time						DWORD ?
	range						BYTE 32 dup(?)	
SCOPETIME ends

LGASAMPLE struct
	clockdiv					DWORD ?
	rate						BYTE 32 dup(?)
LGASAMPLE ends

STM32_HSC struct
	HSCSet						DWORD ?
	HSCDiv						DWORD ?
STM32_HSC ends

STM32_FRQ struct
	Frequency					DWORD ?
	FrequencySCP				DWORD ?
STM32_FRQ ends

STM32_LCM struct
	FrequencyCal0				DWORD ?
	FrequencyCal1				DWORD ?
STM32_LCM ends

STM32_SCP struct
	ADC_Prescaler				DWORD ?
	ADC_TwoSamplingDelay		DWORD ?
	ScopeTrigger				DWORD ?
	ScopeTriggerLevel			DWORD ?
	ScopeTimeDiv				DWORD ?
	ScopeVoltDiv				DWORD ?
	ScopeVPos					DWORD ?
	ADC_TripleMode              DWORD ?
	ADC_SampleTime              DWORD ?
	ADC_SampleSize				DWORD ?
	fSubSampling				DWORD ?
STM32_SCP ends

STM32_DDS struct
	DDS_Cmd						WORD ?
	DDS_Wave					WORD ?
	DDS__PhaseAdd				DWORD ?
	DDS_Amplitude				DWORD ?
	DDS_DCOffset				DWORD ?
STM32_DDS ends

STM32_LGA struct
	DataBlocks					BYTE ?
	TriggerValue				BYTE ?
	TriggerMask					BYTE ?
	TriggerWait					BYTE ?
	LGASampleRateDiv			WORD ?
	LGASampleRate				WORD ?
STM32_LGA ends

STM32_CMD struct
	Cmd							DWORD ?
	STM32_Hsc					STM32_HSC <>
	STM32_Frq 					STM32_FRQ <>
	STM32_Lcm					STM32_LCM <>
	STM32_Scp					STM32_SCP <>
	STM32_Dds					STM32_DDS <>
	STM32_Lga					STM32_LGA <>
	TickCount					DWORD ?
	PreviousCountTIM2			DWORD ?
	ThisCountTIM2				DWORD ?
	PreviousCountTIM5			DWORD ?
	ThisCountTIM5				DWORD ?
STM32_CMD ends

DDSSWEEP struct
	SWEEP_UpDovn				DWORD ?
	SWEEP_Min					DWORD ?
	SWEEP_Max					DWORD ?
	SWEEP_Add					DWORD ?
DDSSWEEP ends

DDSWAVEDATA struct
	DDS_WaveForm				DWORD ?
	DDS_Amplitude				DWORD ?
	DDS_DCOffset				DWORD ?
	DDS_Frequency				DWORD ?
	DDS_PhaseFrq				DWORD ?
	SWEEP_SubMode				DWORD ?
	SWEEP_StepCount				DWORD ?
	SWEEP_StepSize				DWORD ?
	SWEEP_StepTime				DWORD ?
	DDS_VMin					DWORD ?
	DDS_VMax					DWORD ?
	DDS_Sweep					DDSSWEEP <>
	DDS_WaveData				WORD 4098 dup(?)
	DDS_PeakFMin				DWORD ?
	DDS_PeakFMax				DWORD ?
	DDS_PeakVMin				DWORD ?
	DDS_PeakVMax				DWORD ?
	DDS_PeakData				WORD 1536 dup(?)
DDSWAVEDATA ends

FP_EQUALTO						equ	40h

.const

szFREQUENCYCLASS				BYTE 'FREQUENCYCLASS',0
szSCOPECLASS					BYTE 'SCOPECLASS',0
szDDSCLASS						BYTE 'DDSCLASS',0
szLGACLASS						BYTE 'LGACLASS',0
Tahoma_36						LOGFONT <-36,0,0,0,400,0,0,0,0,3,2,1,34,"Tahoma">

szLCMeter						BYTE 'LC Meter - ',0
szLCM							BYTE 'LC Meter',0
szCalibrate						BYTE 'Calibrate',0
szCapacitance					BYTE 'Capacitance',0
szInductance					BYTE 'Inductance',0
szFerquencyCH1					BYTE 'HS Clock',0
szFerquencyCH2					BYTE 'Ferquency CH2',0
szFerquencyCH3					BYTE 'Ferquency CH3',0
szScope							BYTE 'Scope',0
szDDS							BYTE 'DDS Wave',0
szLGA							BYTE 'Logic Analyser',0

szSampleRate					BYTE 'Sample Rate ',0
szBufferSize					BYTE 'Buffer Size %dKb',0

szFmtHz							BYTE '%dHz',0
szFmtKHz						BYTE '%dKHz',0
szFmtMHz						BYTE '%dMHz',0
szHz							BYTE 'Hz',0

szFmtLGA						BYTE ' Hex: %02X  Bin: %s  Bytenbr: %u Transitions: %u Time: %s',0
szFmtLGATimens					BYTE '%02uns',0
szFmtLGATimeus					BYTE '%uus',0
szFmtLGATimems					BYTE '%ums',0
szFmtLGATimeDiv					BYTE '%s / Div',0

szPF							BYTE 'pF',0
szNF							BYTE 'nF',0
szUF							BYTE 'uF',0

szNH							BYTE 'nH',0
szUH							BYTE 'uH',0
szMH							BYTE 'mH',0
szH								BYTE 'H',0

sznS							BYTE 'ns',0
szuS							BYTE 'us',0
szmS							BYTE 'ms',0

CCal							REAL10 1.015e-9
two								REAL10 2.0

ten16							REAL8 1.0e16
ten								REAL8 10.0
ten_1							REAL10 1.0e1
								REAL10 1.0e2
ten_3							REAL10 1.0e3
								REAL10 1.0e4
								REAL10 1.0e5
ten_6							REAL10 1.0e6
								REAL10 1.0e7
								REAL10 1.0e8
ten_9							REAL10 1.0e9
								REAL10 1.0e10
								REAL10 1.0e11
ten_12							REAL10 1.0e12
								REAL10 1.0e13
								REAL10 1.0e14
								REAL10 1.0e15
ten_16							REAL10 1.0e16
								REAL10 1.0e32
								REAL10 1.0e48
								REAL10 1.0e64
								REAL10 1.0e80
								REAL10 1.0e96
								REAL10 1.0e112
								REAL10 1.0e128
								REAL10 1.0e144
								REAL10 1.0e160
								REAL10 1.0e176
								REAL10 1.0e192
								REAL10 1.0e208
								REAL10 1.0e224
								REAL10 1.0e240
ten_256							REAL10 1.0e256
								REAL10 1.0e512
								REAL10 1.0e768
								REAL10 1.0e1024
								REAL10 1.0e1280
								REAL10 1.0e1536
								REAL10 1.0e1792
								REAL10 1.0e2048
								REAL10 1.0e2304
								REAL10 1.0e2560
								REAL10 1.0e2816
								REAL10 1.0e3072
								REAL10 1.0e3328
								REAL10 1.0e3584
								REAL10 1.0e4096
								REAL10 1.0e4352
								REAL10 1.0e4608
								REAL10 1.0e4864

ScopeTime						SCOPETIME <10,'10nS / Div'>,<20,'20nS / Div'>,<50,'50nS / Div'>,<100,'100nS / Div'>,<200,'200nS / Div'>,<500,'500nS / Div'>,<1000,'1uS / Div'>,<2000,'2uS / Div'>,<5000,'5uS / Div'>,<10000,'10uS / Div'>,<20000,'20uS / Div'>,<50000,'50uS / Div'>
								SCOPETIME <100000,'100uS / Div'>,<200000,'200uS / Div'>,<500000,'500uS / Div'>,<1000000,'1mS / Div'>,<2000000,'2mS / Div'>,<5000000,'5mS / Div'>,<10000000,'10mS / Div'>,<20000000,'20mS / Div'>,<50000000,'50mS / Div'>,<100000000,'100mS / Div'>
ScopeRange						SCOPERANGE <15,0,'1mV/Div'>,<30,0,'2mV/Div'>,<76,0,'5mV/Div'>,<152,0,'10mV/Div'>,<305,0,'20mV/Div'>,<762,0,'50mV / Div'>,<1525,0,'100mV / Div'>,<3050,0,'200mV / Div'>,<7625,0,'500mV / Div'>

LgaSample						LGASAMPLE <199999,'1KHz'>,<99999,'2KHz'>,<39999,'5KHz'>,<19999,'10KHz'>,<9999,'20KHz'>,<3999,'50KHz'>,<1999,'100KHz'>,<999,'200KHz'>,<399,'500KHz'>,<199,'1MHz'>,<99,'2MHz'>,<39,'5MHz'>,<19,'10MHz'>,<9,'20MHz'>,<4,'40MHz'>

szFmtVPP						BYTE 'Vpp: ',0
szFmtPPV						BYTE '%.04uV',0
szFmtPER						BYTE 'Per: ',0
ADCSingle_SampleClocks			DWORD 3,15,28,56,84,112,144,480

;#########################################################################

.data?

hInstance						HINSTANCE ?
wc								WNDCLASSEX <>
hWnd							HWND ?
msg								MSG <>

hLcmCld							HWND ?
hLcm							HWND ?

hHscCld							HWND ?
hHsc							HWND ?

hScpScrnCld						HWND ?
hScpScrn						HWND ?
hScpCld							HWND ?
hScp							HWND ?

hDDSScrnCld						HWND ?
hDDSScrn						HWND ?
hDDSCld							HWND ?
hDDS							HWND ?

hLGACld							HWND ?
hLGAScrnCld						HWND ?
hLGAScrn						HWND ?

hFont							HFONT ?
hIml							HIMAGELIST ?
hGrayIcon						HICON ?
hGreenIcon						HICON ?
hRedIcon						HICON ?

fSampleDone						DWORD ?
fHoldSampling					DWORD ?
fNoFrequency					DWORD ?
fExitThread						DWORD ?
fThreadDone						DWORD ?

mode							DWORD ?
LCx								REAL10 ?
lpOldButtonProc					DWORD ?
nBtnCount						DWORD ?

STM32_Cmd						STM32_CMD <>

SampleRate						REAL10 ?
SampleTime						REAL10 ?
SignalPeriod					DWORD ?
SamplesPrPeriod					DWORD ?
STM32_Scp						STM32_SCP <>
scopexofs						DWORD ?
scopeyofs						DWORD ?
ADC_Data						WORD ADCSAMPLESIZE dup(?)
SubSample						DWORD 2048 dup(?)
SubSampleCount					WORD 2048 dup(?)

ddswavedata						DDSWAVEDATA <>

LGA_Data						BYTE LGASAMPLESIZE dup(?)
lgaxofs							DWORD ?
transcurpos						DWORD ?
transstart						DWORD ?
transend						DWORD ?
LGA_Text						BYTE 128 dup(?)
transbit						DWORD ?
transrisingedge					DWORD ?
transcount						DWORD ?

wsdata							WSADATA <>
serveraddress					SOCKADDR_BTH <>
client_socket					SOCKET ?
fBluetooth						DWORD ?

;#########################################################################