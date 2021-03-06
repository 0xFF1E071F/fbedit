
include windows.inc
include comctl32.inc
include kernel32.inc
include user32.inc
include gdi32.inc

includelib comctl32.lib
includelib kernel32.lib
includelib user32.lib
includelib gdi32.lib

include ..\radasm.inc

;#########################################################################
;		VKim's Debug

include \masm32\include\masm32.inc
include \masm32\include\debug.inc
includelib \masm32\lib\debug.lib

DBGWIN_DEBUG_ON = 1		; include debug info into the program
DBGWIN_EXT_INFO = 0		; include extra debug info into the program

;#########################################################################

DLLProc					PROTO :DWORD, :DWORD, :DWORD, :DWORD
InstallDLL				PROTO :DWORD, :DWORD

ADDINOPT struct
	lpStr			dd ?
	nAnd			dd ?
	nOr				dd ?
ADDINOPT ends

IDM_FILE_NEWPROJECT				equ 40001
IDM_FILE_OPENPROJECT			equ 40002
IDM_FILE_CLOSEPROJECT			equ 40003
IDM_FILE_DELETEPROJECT			equ 40013
IDM_FILE_NEWFILE				equ 40004
IDM_FILE_OPENFILE				equ 40005
IDM_FILE_OPENHEX				equ 40014
IDM_FILE_REOPENFILE				equ 41021
IDM_FILE_CLOSEFILE				equ 40006
IDM_FILE_SAVEFILE				equ 40007
IDM_FILE_SAVEFILEAS				equ 40008
IDM_FILE_SAVEALLFILES			equ 40009
IDM_FILE_RECENT					equ 40990
IDM_FILE_PAGESETUP				equ 40010
IDM_FILE_PRINT					equ 40011
IDM_FILE_EXIT					equ 40012

IDM_EDIT_UNDO					equ 41001
IDM_EDIT_REDO					equ 41002
IDM_EDIT_EMPTY_UNDO				equ 41022
IDM_EDIT_CUT					equ 41003
IDM_EDIT_COPY					equ 41004
IDM_EDIT_PASTE					equ 41005
IDM_EDIT_DELETE					equ 41006
IDM_EDIT_SELECTALL				equ 41007
IDM_EDIT_FIND					equ 41008
IDM_EDIT_FINDNEXT				equ 41009
IDM_EDIT_FINDPREVIOUS			equ 41010
IDM_EDIT_REPLACE				equ 41011
IDM_EDIT_GOTOLINE				equ 41012
IDM_EDIT_EXPANDBLOCK			equ 41018
IDM_EDIT_FINDWORD				equ 41101
IDM_EDIT_FIND_NEXT_WORD			equ 41020
IDM_EDIT_FINDPROC				equ 41102
IDM_EDIT_RETURN					equ 41103
IDM_EDIT_NEXTBM					equ 41105
IDM_EDIT_PREVIOUSBM				equ 41106
IDM_EDIT_TOGGLEBM				equ 41104
IDM_EDIT_CLEARBM				equ 41107

IDM_VIEW_TOOLBOX				equ 42002
IDM_VIEW_OUTPUTWINDOW			equ 42003
IDM_VIEW_PROJECTBROWSER			equ 42004
IDM_VIEW_PROPERTIES				equ 42005

IDM_PROJECT_ADDNEWASM			equ 44101
IDM_PROJECT_ADDNEWINC			equ 44102
IDM_PROJECT_ADDNEWRC			equ 44103
IDM_PROJECT_ADDNEWTXT			equ 44104
IDM_PROJECT_ADDNEWDIALOG		equ 44105
IDM_PROJECT_ADDNEWMENU			equ 44106
IDM_PROJECT_ADDNEWMODULE		equ 44107
IDM_PROJECT_ADDNEWFILE			equ 44108
IDM_PROJECT_ADDEXISTINGFILE		equ 44201
IDM_PROJECT_ADDEXISTINGDIALOG	equ 44202
IDM_PROJECT_ADDEXISTINGMENU		equ 44203
IDM_PROJECT_ADDEXISTINGMODULE	equ 44206

IDM_MAKE_ASSEMBLE				equ 20002
IDM_MAKE_BUILD					equ 20004
IDM_MAKE_GO						equ 20005
IDM_MAKE_RUN					equ 20006

IDM_WINDOW_SPLIT				equ 47009
IDM_WINDOW_CLOSE				equ 47001
IDM_WINDOW_CLOSEALL				equ 47002
IDM_WINDOW_NEXTWINDOW			equ 47003
IDM_WINDOW_PREVIOUS				equ 47004
IDM_WINDOW_EDIT					equ 47013
IDM_WINDOW_PROJECT				equ 47014
IDM_WINDOW_PROPERTY				equ 47015
IDM_WINDOW_OUTPUT				equ 47016
IDM_WINDOW_TILEHOR				equ 47005
IDM_WINDOW_TILEVER				equ 47006
IDM_WINDOW_CASCADE				equ 47007
IDM_WINDOW_ARRANGEICONS			equ 47008
IDM_WINDOW_MAXIMIZE				equ 47010
IDM_WINDOW_RESTORE				equ 47011
IDM_WINDOW_MINIMIZE				equ 47012

IDM_OUTPUT_OPEN					equ 50005
IDM_OUTPUT_SAVE					equ 50006
IDM_OUTPUT_UNDO					equ 50007
IDM_OUTPUT_REDO					equ 50008
IDM_OUTPUT_CUT					equ 50101
IDM_OUTPUT_COPY					equ 50102
IDM_OUTPUT_PASTE				equ 50103
IDM_OUTPUT_DELETE				equ 50104
IDM_OUTPUT_CLEAR				equ 50105
IDM_OUTPUT_COPYALL				equ 50106
IDM_OUTPUT_CUTALL				equ 50107

IDM_FILE_CUT					equ 50009
IDM_FILE_COPY					equ 50010
IDM_FILE_PASTE					equ 50011
IDM_FILE_DELETE					equ 50012
;IDM_FILE_RENAME					equ 50013
;IDM_FILE_COPYNAME				equ 50015
;IDM_FILE_EXPLORE				equ 50023

IDM_PROPERTY_FIND				equ 50018

IDB_CHECKMARK					equ 100

MNUDATA struct
	hMnu		dd ?
	nID			dd ?
	nPos		dd ?
	szString	dw 96 dup(?)
	szAccel		dw 32 dup(?)
	iImage		dd ?
	wt			dd ?
MNUDATA ends

;MENUINFO STRUCT
;	cbSize			DWORD	?
;	fmask			DWORD	?
;	dwstyle			DWORD	?
;	cyMax			DWORD	?
;	hbrBack			DWORD	?
;	dwContextHelpID	DWORD	?
;	dwMenuData		DWORD	?
;MENUINFO ends

.data

MnuBmp				dw IDM_FILE_DELETEPROJECT,IDM_EDIT_DELETE
					dw IDM_FILE_NEWFILE,IDM_FILE_NEWFILE
					dw IDM_FILE_OPENFILE,IDM_FILE_OPENFILE
					dw IDM_FILE_CLOSEFILE,68
					dw IDM_FILE_SAVEFILE,IDM_FILE_SAVEFILE
					dw IDM_FILE_SAVEALLFILES,IDM_FILE_SAVEALLFILES
					dw IDM_FILE_PRINT,IDM_FILE_PRINT
					dw IDM_EDIT_UNDO,IDM_EDIT_UNDO
					dw IDM_EDIT_REDO,IDM_EDIT_REDO
					dw IDM_EDIT_CUT,IDM_EDIT_CUT
					dw IDM_EDIT_COPY,IDM_EDIT_COPY
					dw IDM_EDIT_PASTE,IDM_EDIT_PASTE
					dw IDM_EDIT_DELETE,IDM_EDIT_DELETE
					dw IDM_EDIT_FIND,IDM_EDIT_FIND
					dw IDM_EDIT_REPLACE,IDM_EDIT_REPLACE
					dw IDM_EDIT_NEXTBM,IDM_EDIT_NEXTBM
					dw IDM_EDIT_PREVIOUSBM,IDM_EDIT_PREVIOUSBM
					dw IDM_EDIT_TOGGLEBM,IDM_EDIT_TOGGLEBM
					dw IDM_EDIT_CLEARBM,IDM_EDIT_CLEARBM
					dw IDM_VIEW_TOOLBOX,IDM_VIEW_TOOLBOX
					dw IDM_VIEW_OUTPUTWINDOW,IDM_VIEW_OUTPUTWINDOW
					dw IDM_VIEW_PROJECTBROWSER,IDM_VIEW_PROJECTBROWSER
					dw IDM_VIEW_PROPERTIES,IDM_VIEW_PROPERTIES
					dw IDM_PROJECT_ADDNEWASM,49
					dw IDM_PROJECT_ADDNEWINC,48
					dw IDM_PROJECT_ADDNEWRC,50
					dw IDM_PROJECT_ADDNEWTXT,54
					dw IDM_PROJECT_ADDNEWDIALOG,51
					dw IDM_PROJECT_ADDNEWMENU,52
					dw IDM_PROJECT_ADDNEWMODULE,49
					dw IDM_PROJECT_ADDNEWFILE,53
					dw IDM_PROJECT_ADDEXISTINGFILE,53
					dw IDM_PROJECT_ADDEXISTINGDIALOG,51
					dw IDM_PROJECT_ADDEXISTINGMENU,52
					dw IDM_PROJECT_ADDEXISTINGMODULE,49
					dw IDM_MAKE_ASSEMBLE,IDM_MAKE_ASSEMBLE
					dw IDM_MAKE_BUILD,IDM_MAKE_BUILD
					dw IDM_MAKE_GO,IDM_MAKE_GO
					dw IDM_MAKE_RUN,IDM_MAKE_RUN
					dw IDM_WINDOW_CLOSE,68
					dw IDM_WINDOW_TILEHOR,69
					dw IDM_WINDOW_TILEVER,70
					dw IDM_WINDOW_CASCADE,71
					dw IDM_OUTPUT_OPEN,IDM_FILE_OPENFILE
					dw IDM_OUTPUT_SAVE,IDM_FILE_SAVEFILE
					dw IDM_OUTPUT_UNDO,IDM_EDIT_UNDO
					dw IDM_OUTPUT_REDO,IDM_EDIT_REDO
					dw IDM_OUTPUT_CUT,IDM_EDIT_CUT
					dw IDM_OUTPUT_COPY,IDM_EDIT_COPY
					dw IDM_OUTPUT_PASTE,IDM_EDIT_PASTE
					dw IDM_OUTPUT_DELETE,IDM_EDIT_DELETE
					dw IDM_FILE_CUT,IDM_EDIT_CUT
					dw IDM_FILE_COPY,IDM_EDIT_COPY
					dw IDM_FILE_PASTE,IDM_EDIT_PASTE
					dw IDM_FILE_DELETE,IDM_EDIT_DELETE
					dw IDM_PROPERTY_FIND,IDM_EDIT_FIND
					dw 0

szUserLib			db "User32.DLL",0
szSetMenuInfo		db "SetMenuInfo",0

AddInString0		db 'Default Menu',0
AddInString1		db 'Cool menu',0
;AddInString2		db 'Office XP',0
AddInString4		db "Cool bar white",0
AddInString5		db "Cool bar blue",0
AddInString6		db "Cool bar green",0
AddInString7		db "Cool bar red",0
AddInString8		db "Cool body white",0
AddInString9		db "Cool body blue",0
AddInString10		db "Cool body green",0
AddInString11		db "Cool body red",0

AddinOpt			ADDINOPT <offset AddInString0,03h,00h>
					ADDINOPT <offset AddInString1,03h,01h>
;					ADDINOPT <offset AddInString2,03h,02h>
					ADDINOPT <offset AddInString4,01Ch,004h>
					ADDINOPT <offset AddInString5,01Ch,008h>
					ADDINOPT <offset AddInString6,01Ch,00Ch>
					ADDINOPT <offset AddInString7,01Ch,010h>
					ADDINOPT <offset AddInString8,0E0h,020h>
					ADDINOPT <offset AddInString9,0E0h,040h>
					ADDINOPT <offset AddInString10,0E0h,060h>
					ADDINOPT <offset AddInString11,0E0h,080h>
					ADDINOPT <0,0,0>

.data?

hInstance			dd ?	;Dll's module handle
lpHandles			dd ?	;Pointer to handles struct
lpProcs				dd ?	;Pointer to procs struct
lpData				dd ?	;Pointer to data struct
fOptions			dd ?
hMenuBmp			dd ?
hMenuBrush			dd ?
StyleMenu			dd ?
lpOldWndProc		dd ?
hIml				dd ?
hImlGray			dd ?
pSetMenuInfo		dd ?
mnudata				MNUDATA 512 dup(<>)
fNT					dd ?
hMnuFont			dd ?
MnuFontHt			dd ?
