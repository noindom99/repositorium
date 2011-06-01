// Copyright (C) 2003-2005 AbstractSpoon Software.
//
// This license applies to everything in the ToDoList package, except where
// otherwise noted.
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the
// use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software in a
// product, an acknowledgment in the product documentation would be appreciated
// but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.

//*****************************************************************************
// Modified by Elijah Zarezky aka SchweinDeBurg (elijah.zarezky@gmail.com):
// - improved compatibility with the Unicode-based builds
// - added AbstractSpoon Software copyright notice and license information
// - adjusted #include's paths
// - reformatted with using Artistic Style 2.01 and the following options:
//      --indent=tab=3
//      --indent=force-tab=3
//      --indent-switches
//      --max-instatement-indent=2
//      --brackets=break
//      --add-brackets
//      --pad-oper
//      --unpad-paren
//      --pad-header
//      --align-pointer=type
//      --lineend=windows
//      --suffix=none
// - merged with ToDoList version 6.1.2-6.2.2 sources
//*****************************************************************************

#if !defined(AFX_TDCENUM_H__5951FDE6_508A_4A9D_A55D_D16EB026AEF7__INCLUDED_)
#define AFX_TDCENUM_H__5951FDE6_508A_4A9D_A55D_D16EB026AEF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// TDCEnum.h : header file
//

#include <afxtempl.h>

// startup options
enum
{
	TDL_STARTUP,
};

// creation flags
enum
{
	TLD_FORCEVISIBLE        = 0x01,
	TLD_PASSWORDPROMPTING   = 0x02,
	TLD_LOGGING             = 0x04,
	TLD_IMPORTFILE          = 0x08,
	TLD_NEWTASK             = 0x10,
};

enum TDC_TITLERECT
{
	TDCTR_LABEL,
	TDCTR_ICON,
	TDCTR_CHECKBOX,
	TDCTR_BOUNDS,
	TDCTR_EDIT,
};

enum TDC_INSERTWHERE
{
	TDC_INSERTATTOP,
	TDC_INSERTATBOTTOM,
	TDC_INSERTATTOPOFSELTASKPARENT,
	TDC_INSERTATBOTTOMOFSELTASKPARENT,
	TDC_INSERTAFTERSELTASK,
	TDC_INSERTBEFORESELTASK,
	TDC_INSERTATTOPOFSELTASK, // subtask
	TDC_INSERTATBOTTOMOFSELTASK, // subtask
};

enum TDC_ARCHIVE
{
	TDC_REMOVENONE,
	TDC_REMOVEALL,
	TDC_REMOVEIFSIBLINGSANDSUBTASKSCOMPLETE,
};

enum TDC_STYLE
{
	TDCS_FIRST,

	TDCS_SHOWINFOTIPS = TDCS_FIRST,
	TDCS_COLORTEXTBYPRIORITY,
	TDCS_COLORTEXTBYCATEGORY,
	TDCS_COLORTEXTBYNONE,
	TDCS_SHOWCOMMENTSINLIST,
	TDCS_SHOWFIRSTCOMMENTLINEINLIST,
	TDCS_TREATSUBCOMPLETEDASDONE,
	TDCS_HIDEPERCENTFORDONETASKS,
	TDCS_CONFIRMDELETE,
	TDCS_AVERAGEPERCENTSUBCOMPLETION,
	TDCS_INCLUDEDONEINAVERAGECALC,
	TDCS_TREECHECKBOXES,
	TDCS_TREETASKICONS,
	TDCS_USEEARLIESTDUEDATE,
	TDCS_USEPERCENTDONEINTIMEEST,
	TDCS_SHOWCTRLSASCOLUMNS,
	TDCS_SHOWCOMMENTSALWAYS,
	TDCS_AUTOREPOSCTRLS,
	TDCS_HIDEZEROTIMECOST,
	TDCS_HIDESTARTDUEFORDONETASKS,
	TDCS_SHOWPERCENTASPROGRESSBAR,
	TDCS_READONLY,
	TDCS_ENABLESOURCECONTROL,
	TDCS_CHECKOUTONLOAD,
	TDCS_SHOWPATHINHEADER,
	TDCS_STRIKETHOUGHDONETASKS,
	TDCS_FULLROWSELECTION,
	TDCS_SORTVISIBLETASKSONLY,
	TDCS_SHAREDCOMMENTSHEIGHT,
	TDCS_TASKCOLORISBACKGROUND,
	TDCS_COMMENTSUSETREEFONT,
	TDCS_SHOWDATESINISO,
	TDCS_USEHIGHESTPRIORITY,
	TDCS_AUTOCALCTIMEESTIMATES,
	TDCS_SHOWWEEKDAYINDATES,
	TDCS_ROUNDTIMEFRACTIONS,
	TDCS_SHOWNONFILEREFSASTEXT,
	TDCS_INCLUDEDONEINPRIORITYCALC,
	TDCS_WEIGHTPERCENTCALCBYNUMSUB,
	TDCS_RIGHTALIGNLABELS,
	TDCS_SHOWPARENTSASFOLDERS,
	TDCS_FOCUSTREEONENTER,
	TDCS_AUTOCALCPERCENTDONE,
	TDCS_TRACKSELECTEDTASKONLY,
	TDCS_HIDEPRIORITYNUMBER,
	TDCS_PAUSETIMETRACKINGONSCRNSAVER,
	TDCS_DISPLAYHMSTIMEFORMAT,
	TDCS_SORTDONETASKSATBOTTOM,
	TDCS_VERTCOMMENTS,
	TDCS_USEHIGHESTRISK,
	TDCS_INCLUDEDONEINRISKCALC,
	TDCS_SHOWPROJECTNAME,
	TDCS_LOGTIMETRACKING,
	TDCS_LOGTASKTIMESEPARATELY,
	TDCS_WARNADDDELETEARCHIVE,
	TDCS_SHOWSUBTASKCOMPLETION,
	TDCS_ALLOWPARENTTIMETRACKING,
	TDCS_REFILTERONMODIFY,
	TDCS_AUTOADJUSTDEPENDENCYDATES,
	TDCS_RIGHTSIDECOLUMNS,
	TDCS_HIDEDUETIMEFIELD,
	TDCS_USES3RDPARTYSOURCECONTROL,
	TDCS_DUEHAVEHIGHESTPRIORITY,
	TDCS_DONEHAVELOWESTPRIORITY,
	TDCS_DONEHAVELOWESTRISK,
	TDCS_HIDESTARTTIMEFIELD,
	TDCS_NODUEDATEISDUETODAY,
	TDCS_HIDEDONETIMEFIELD,
	TDCS_CALCREMAININGTIMEBYDUEDATE,
	TDCS_CALCREMAININGTIMEBYSPENT,
	TDCS_CALCREMAININGTIMEBYPERCENT,
	TDCS_SHOWTREELISTBAR,
	TDCS_INCLUDEUSERINCHECKOUT,

	TDCS_LAST
};

enum TDC_COLUMN
{
	TDCC_CLIENT = 0xffff, // NCG_CLIENTCOLUMNID
	TDCC_FIRST = 0,

	TDCC_PRIORITY = TDCC_FIRST,
	TDCC_PERCENT,
	TDCC_TIMEEST,
	TDCC_TIMESPENT,
	TDCC_STARTDATE,
	TDCC_DUEDATE,
	TDCC_DONEDATE,
	TDCC_ALLOCTO,
	TDCC_ALLOCBY,
	TDCC_STATUS,
	TDCC_CATEGORY,
	TDCC_FILEREF,
	TDCC_POSITION,
	TDCC_ID,
	TDCC_DONE,
	TDCC_TRACKTIME,
	TDCC_FLAG,
	TDCC_CREATIONDATE,
	TDCC_CREATEDBY,
	TDCC_LASTMOD,
	TDCC_RISK,
	TDCC_EXTERNALID,
	TDCC_COST,
	TDCC_DEPENDENCY,
	TDCC_RECURRENCE,
	TDCC_VERSION,
	TDCC_RECENTEDIT,
	TDCC_REMAINING,
	TDCC_ICON,
	TDCC_REMINDER,
	TDCC_PARENTID,

	TDCC_LAST,
	TDCC_NONE = TDCC_LAST,
};

typedef CArray<TDC_COLUMN, TDC_COLUMN> CTDCColumnArray;

enum TDC_GOTO
{
	TDCG_NEXT,
	TDCG_PREV,
};

enum TDC_FILEFMT
{
	TDCFF_OLDER,
	TDCFF_SAME,
	TDCFF_NEWER
};

enum TDC_FILE
{
	TDCO_SUCCESS,
	TDCO_NOTEXIST,
	TDCO_NOTTASKLIST,
	TDCO_NOTALLOWED,
	TDCO_CANCELLED,
	TDCO_BADMSXML,
	TDCO_NOENCRYPTIONDLL,
	TDCO_UNKNOWNENCRYPTION,
	TDCO_INUSE,
	TDCO_OTHER, // always the last value
};

enum // TDL_SAVETASKLIST
{
	TDLS_INCLUDEUNSAVED     = 0x01,
	TDLS_CLOSINGTASKLISTS   = 0x02,
	TDLS_CLOSINGWINDOWS     = 0x04,
	TDLS_FLUSH              = 0x08,
	TDLS_AUTOSAVE           = 0x10,
};

enum TDC_GETTASKS
{
	TDCGT_NONE,         // not very useful except to assist coding
	TDCGT_ALL,
	TDCGT_DUE,          // due today
	TDCGT_DUETOMORROW,
	TDCGT_DUETHISWEEK,
	TDCGT_DUENEXTWEEK,
	TDCGT_DUETHISMONTH,
	TDCGT_DUENEXTMONTH,
	TDCGT_DONE,
	TDCGT_NOTDONE,
};

enum TDC_RESETIDS
{
	TDCR_YES,
	TDCR_NO,
	TDCR_CHECK
};

enum TDC_PASTE
{
	TDCP_ONSELTASK,
	TDCP_BELOWSELTASK,
	TDCP_ATBOTTOM
};

enum TDC_MOVETASK
{
	TDCM_DOWN,
	TDCM_UP,
	TDCM_LEFT,
	TDCM_RIGHT,
};

enum // TDC_GETTASKSFLAGS
{
	TDCGTF_SELECTED                 = 0x0001,
	TDCGTF_PARENTTITLECOMMENTSONLY  = 0x0002,
	TDCGTF_ISODATES                 = 0x0004,
	TDCGTF_TITLESONLY               = 0x0008,
	TDCGTF_NOTSUBTASKS              = 0x0010,
	TDCGTF_HTMLCOMMENTS             = 0x0020,
	TDCGTF_KEEPFLAGGED              = 0x0040,
	TDCGTF_TRANSFORM                = 0x0080,
	TDCGTF_CUSTOMATTRIB             = 0x0100,
	TDCGTF_FILENAME                 = 0x0200,
};

enum TDC_DATE
{
	TDCD_CREATE,
	TDCD_START,     // getting only (date+time)
	TDCD_STARTDATE, // setting or getting (date only)
	TDCD_STARTTIME, // setting or getting (time only)
	TDCD_DUE,       // getting only (date+time)
	TDCD_DUEDATE,   // setting or getting (date only)
	TDCD_DUETIME,   // setting or getting (time only)
	TDCD_DONE,      // getting only (date+time)
	TDCD_DONEDATE,  // setting or getting (date only)
	TDCD_DONETIME,  // setting or getting (time only)
	TDCD_LASTMOD,
};

// control ids
enum
{
	IDC_FIRST           = 100,

	IDC_TASKLIST,
	IDC_PROJECTLABEL,
	IDC_PROJECTNAME,
	IDC_ALLOCTOLABEL,
	IDC_ALLOCTO,
	IDC_ALLOCBYLABEL,
	IDC_ALLOCBY,
	IDC_STATUSLABEL,
	IDC_STATUS,
	IDC_CATEGORYLABEL,
	IDC_CATEGORY,
	IDC_PRIORITYLABEL,
	IDC_PRIORITY,
	IDC_STARTLABEL,
	IDC_STARTDATE,
	IDC_STARTTIMELABEL,
	IDC_STARTTIME,
	IDC_DUELABEL,
	IDC_DUEDATE,
	IDC_DUETIMELABEL,
	IDC_DUETIME,
	IDC_PERCENTLABEL,
	IDC_PERCENT,
	IDC_PERCENTSPIN,
	IDC_DONELABEL,
	IDC_DONEDATE,
	IDC_DONETIMELABEL,
	IDC_DONETIME,
	IDC_FILEPATHLABEL,
	IDC_FILEPATH,
	IDC_TIMEESTLABEL,
	IDC_TIMEEST,
	IDC_TIMESPENTLABEL,
	IDC_TIMESPENT,
	IDC_RISKLABEL,
	IDC_RISK,
	IDC_EXTERNALIDLABEL,
	IDC_EXTERNALID,
	IDC_COSTLABEL,
	IDC_COST,
	IDC_DEPENDSLABEL,
	IDC_DEPENDS,
	IDC_RECURRENCE,
	IDC_RECURRENCELABEL,
	IDC_COLOUR,
	IDC_COLOURLABEL,
	IDC_VERSION,
	IDC_VERSIONLABEL,
	IDC_COMMENTSLABEL,
	IDC_COMMENTSTYPE,
	IDC_HSPLITTER,
	IDC_COMMENTS,

	IDC_FTC_TABCTRL,
	IDC_FTC_TASKLIST,
	IDC_FTC_EDIT,

	IDC_LAST,
};

enum TDC_ATTRIBUTE
{
	TDCA_NONE = -1,
	TDCA_TASKNAME,
	TDCA_DONEDATE,
	TDCA_DUEDATE,
	TDCA_STARTDATE,
	TDCA_PRIORITY,
	TDCA_COLOR,
	TDCA_ALLOCTO,
	TDCA_ALLOCBY,
	TDCA_STATUS,
	TDCA_CATEGORY,
	TDCA_PERCENT,
	TDCA_TIMEEST,
	TDCA_TIMESPENT,
	TDCA_FILEREF,
	TDCA_COMMENTS,
	TDCA_PROJNAME,
	TDCA_FLAG,
	TDCA_CREATIONDATE,
	TDCA_CREATEDBY,
	TDCA_RISK,          // 4.6
	TDCA_EXTERNALID,    // 4.6
	TDCA_COST,          // 4.8
	TDCA_DEPENDENCY,    // 4.8
	TDCA_RECURRENCE,    // 5.1
	TDCA_VERSION,       // 5.1
	TDCA_POSITION,
	TDCA_ID,
	TDCA_LASTMOD,
	TDCA_DUETIME,
	TDCA_ICON,
	TDCA_STARTTIME,
	TDCA_DONETIME,

	// number of 'real' attributes
	TDCA_ATTRIBUTECOUNT,

	// pseudo attribute
	TDCA_PARENTID,

	// pseudo attributes for SetModified
	TDCA_NEWTASK,
	TDCA_MOVE,
	TDCA_UNDO,
	TDCA_DELETE,
	TDCA_ARCHIVE,
	TDCA_SORT,
	TDCA_ENCRYPT,
	TDCA_COPY,

	// pseudo attributes for Find Tasks dialog
	TDCA_TASKNAMEORCOMMENTS,
	TDCA_ANYTEXTATTRIBUTE,
};

typedef CArray<TDC_ATTRIBUTE, TDC_ATTRIBUTE> CTDCAttributeArray;

enum // find attribute
{
	FIND_TITLECOMMENTS  = 0,
	FIND_PRIORITY,
	FIND_PERCENTDONE,
	FIND_TIMEEST,
	FIND_TIMESPENT,
	FIND_STARTDATE,
	FIND_DUEDATE,
	FIND_DONEDATE,
	FIND_ALLOCTO,
	FIND_ALLOCBY,
	FIND_STATUS,
	FIND_CATEGORY,
	FIND_TASKID,
	FIND_FLAG,
	FIND_CREATIONDATE,
	FIND_CREATEDBY,
	FIND_LASTMOD,
	FIND_RISK,
	FIND_EXTERNALID,
	FIND_COST,
	FIND_DEPENDENCY,
	FIND_VERSION,
	FIND_PARENTID,
};

enum FIND_OPERATOR
{
	FO_NONE = -1,
	FO_EQUALS,
	FO_NOT_EQUALS,
	FO_INCLUDES,
	FO_NOT_INCLUDES,
	FO_ON_OR_BEFORE,
	FO_BEFORE,
	FO_ON_OR_AFTER,
	FO_AFTER,
	FO_GREATER_OR_EQUAL,
	FO_GREATER,
	FO_LESS_OR_EQUAL,
	FO_LESS,
	FO_SET,
	FO_NOT_SET,
};

enum FIND_ATTRIBTYPE
{
	FT_NONE = -1,
	FT_STRING,
	FT_INTEGER,
	FT_DOUBLE,
	FT_DATE,
	FT_BOOL,
	FT_TIME,
};

enum
{
	TDITU_MINS   = 'I',
	TDITU_HOURS  = 'H',
	TDITU_DAYS   = 'D',
	TDITU_WEEKS  = 'W',
	TDITU_MONTHS = 'M',
	TDITU_YEARS  = 'Y',
};

enum TDI_REGULARITY
{
	TDIR_ONCE,
	TDIR_DAILY,
	TDIR_WEEKLY,
	TDIR_MONTHLY,
	TDIR_YEARLY,
};

enum // weekdays
{
	TDIW_SUNDAY     = 0X01,
	TDIW_MONDAY     = 0X02,
	TDIW_TUESDAY    = 0X04,
	TDIW_WEDNESDAY  = 0X08,
	TDIW_THURSDAY   = 0X10,
	TDIW_FRIDAY     = 0X20,
	TDIW_SATURDAY   = 0X40,
};

enum TDC_SORTBY
{
	TDC_UNSORTED = 0,
	TDC_SORTBYNAME,
	TDC_SORTBYDONEDATE,
	TDC_SORTBYDUEDATE,
	TDC_SORTBYSTARTDATE,
	TDC_SORTBYPRIORITY,
	TDC_SORTBYCOLOR,
	TDC_SORTBYALLOCTO,
	TDC_SORTBYALLOCBY,
	TDC_SORTBYSTATUS,
	TDC_SORTBYCATEGORY,
	TDC_SORTBYPERCENT,
	TDC_SORTBYTIMEEST,
	TDC_SORTBYTIMESPENT,
	TDC_SORTBYID,
	TDC_SORTBYDONE,
	TDC_SORTBYFLAG,
	TDC_SORTBYCREATIONDATE,
	TDC_SORTBYCREATEDBY,
	TDC_SORTBYLASTMOD,
	TDC_SORTBYRISK,
	TDC_SORTBYEXTERNALID,
	TDC_SORTBYCOST,
	TDC_SORTBYVERSION,
	TDC_SORTBYRECURRENCE,
	TDC_SORTBYRECENTEDIT,
	TDC_SORTBYREMAINING,
	TDC_SORTBYICON,
	TDC_SORTBYPARENTID,
	TDC_SORTBYTIMETRACKING,
	TDC_SORTBYFILEREF,
};

enum
{
	TDCCHECKNONE        = 0x0,
	TDCCHECKPARENT      = 0x1,
	TDCCHECKCHILDREN    = 0x2,
	TDCCHECKALL         = 0x3,
};

enum
{
	SET_NOCHANGE    = -1,
	SET_FAILED      = 0,
	SET_CHANGE      = 1
};

enum
{
	MAX_TDPRIORITY = 10,
	MIN_TDPRIORITY = 0,
	MAX_TDRISK = 10,
	MIN_TDRISK = 0,
};

enum FILTER_TYPE
{
	FT_CUSTOM = -1,
	FT_ALL,
	FT_NOTDONE,
	FT_DONE,
	FT_DUETODAY,
	FT_DUETOMORROW,
	FT_DUEENDTHISWEEK,
	FT_DUEENDNEXTWEEK,
	FT_DUEENDTHISMONTH,
	FT_DUEENDNEXTMONTH,
	FT_DUEENDTHISYEAR,
	FT_DUEENDNEXTYEAR,
	FT_STARTTODAY,
	FT_STARTENDTHISWEEK,
	FT_FLAGGED,
	FT_DUENEXTSEVENDAYS,
	FT_STARTNEXTSEVENDAYS,
	FT_ACTIVE,
	FT_NOTSTARTED,

	// new items here
};

enum // RESULT_FLAGS
{
	RF_DONE         = 0x0001,
	RF_PARENT       = 0x0002,
};

enum
{
	FT_ANYCATEGORY  = 0x0001,
	FT_ANYALLOCTO   = 0x0002,
	FT_HIDEPARENTS  = 0x0004,
	FT_HIDEOVERDUE  = 0x0008,
	FT_HIDEDONE     = 0x0010,
	FT_HIDECOLLAPSED = 0x0020,
	FT_ANYPRIORITY  = -1,
	FT_ANYRISK      = -1,
	FT_NOPRIORITY   = -2,
	FT_NORISK       = -2,
};

enum
{
	FB_MULTISELCAT      = 0x01,
	FB_MULTISELALLOCTO  = 0x02,
	FB_MULTISELSTAT     = 0x04,
	FB_MULTISELALLOCBY  = 0x08,
	FB_MULTISELVER      = 0x10,
};

enum FTMATCHRESULT
{
	FTDC_MATCH,
	FTDC_NOMATCHSTATE,
	FTDC_NOMATCHCATEGORY,
	FTDC_NOMATCHALLOCTO,
	FTDC_NOMATCHPRIORITY,
	FTDC_NOMATCHALLOCBY,
	FTDC_NOMATCHSTATUS,
	FTDC_NOMATCHRISK,
};

enum TDC_SETTASKDONE
{
	TDC_SETDONE,
	TDC_SETUNDONE,
	TDC_SETLEAVE,
};

enum TDC_SELECTTASK
{
	TDC_SELECTFIRST,
	TDC_SELECTNEXT,
	TDC_SELECTNEXTINCLCURRENT,
	TDC_SELECTPREV,
	TDC_SELECTLAST,
};

enum FTC_VIEW
{
	FTCV_UNSET = -1,
	FTCV_TASKTREE,
	FTCV_TASKLIST,
};

enum TDI_RECALCATTRIB
{
	TDIR_PRIORITY       = 0x0001,
	TDIR_PRIORITYINCDUE = 0x0002,
	TDIR_PERCENT        = 0x0004,
	TDIR_RISK           = 0x0008,
	TDIR_TIMEESTIMATE   = 0x0010,
	TDIR_TIMESPENT      = 0x0020,
	TDIR_COST           = 0x0040,
	TDIR_EARLIESTDUE    = 0x0080,
	TDIR_GOODASDONE     = 0x0100,
	TDIR_SUBTASKSCOUNT  = 0x0200,
	TDIR_SUBTASKSDONE   = 0x0400,
};

enum TDC_REMINDER
{
	TDCR_STARTDATE,
	TDCR_DUEDATE,
};

enum TDCUNDOELMOP
{
	TDCUEO_EDIT,
	TDCUEO_ADD,
	TDCUEO_DELETE,
	TDCUEO_MOVE,
};

enum TDCUNDOACTIONTYPE
{
	TDCUAT_NONE = -1,
	TDCUAT_EDIT,
	TDCUAT_ADD,
	TDCUAT_DELETE,
	TDCUAT_PASTE,
	TDCUAT_COPY,
	TDCUAT_MOVE,
	TDCUAT_ARCHIVE,
};

enum TDC_MAXSTATE
{
	TDCMS_NORMAL,
	TDCMS_MAXTASKLIST,
	TDCMS_MAXCOMMENTS,
};

enum TDI_RECURREUSEOPTION
{
	TDIRO_REUSE,
	TDIRO_CREATE,
	TDIRO_ASK,
};

#endif // AFX_TDCENUM_H__5951FDE6_508A_4A9D_A55D_D16EB026AEF7__INCLUDED_
