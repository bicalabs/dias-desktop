
#include "stdafx.h"
#include <aimapi/aimapi.h>
#include "../include/util.h"
#include "../DIAS/resource.h"

int aimGetSelListItem (CListCtrl& ctrlList, BOOL blFocus) {
	int state;
	int count = ctrlList.GetItemCount ();
	for (int i = 0 ; i < count ; ++i) {
		state = ctrlList.GetItemState (i, LVIS_SELECTED);
		if (state)	return (i);
	}
	return (-1);
}

void aimSetSelListItem (CListCtrl& ctrlList, int no) {
	ctrlList.SetItemState (no, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	ctrlList.EnsureVisible (no, FALSE);
}

void aimRotate2D (uvar32_64 no, rtbyte *pPointsX, rtbyte *pPointsY, rtbyte rAngle, CPoint pntCenter) {
	rtbyte x, y;
	rtbyte sa = sinl (rAngle), ca = cosl (rAngle);
	for (uvar32_64 n = 0; n < no; ++n) {
		x = (pPointsX[n] - pntCenter.x) * ca - (pPointsY[n] - pntCenter.y) * sa;
		y = (pPointsX[n] - pntCenter.x) * sa + (pPointsY[n] - pntCenter.y) * ca;
		pPointsX[n] = x + pntCenter.x; pPointsY[n] = y + pntCenter.y;
	}
}

ubyte *aimCompressZip (ubyte *pbIn, uvar32_64 nLen, uvar32_64 &nOutLen) {
	ubyte *pbData;
	char psTempPath[1024], psTempFileIn[1024], psTempFileOut[1024];
	GetTempPath (1024, psTempPath);
	GetTempFileName (psTempPath, "~aim", 1, psTempFileIn);
	GetTempFileName (psTempPath, "~aim", 2, psTempFileOut);
	DeleteFile (psTempFileIn);
	DeleteFile (psTempFileOut);
	CFile fIn (psTempFileIn, CFile::typeBinary | CFile::modeCreate | CFile::modeWrite);
	fIn.Write (pbIn, nLen);
	fIn.Close ();
	CZip zip (psTempFileIn);
	zip.SwapSize (psTempFileOut);
	CFile fOut (psTempFileOut, CFile::typeBinary | CFile::modeRead);
	pbData = (ubyte *)aimMemoryCommit (fOut.GetLength (), "aimCompressZip", "pbData");
	fOut.Read (pbData, nOutLen = fOut.GetLength ());
	fOut.Close ();
	DeleteFile (psTempFileIn);
	DeleteFile (psTempFileOut);
	return (pbData);
}

ubyte *aimDecompressZip (ubyte *pbIn, uvar32_64 nLen, uvar32_64 &nOutLen) {
	ubyte *pbData;
	char psTempPath[1024], psTempFileIn[1024], psTempFileOut[1024];
	GetTempPath (1024, psTempPath);
	GetTempFileName (psTempPath, "~aim", 1, psTempFileIn);
	GetTempFileName (psTempPath, "~aim", 2, psTempFileOut);
	DeleteFile (psTempFileOut);
	DeleteFile (psTempFileOut);
	CFile fIn (psTempFileIn, CFile::typeBinary | CFile::modeCreate | CFile::modeWrite);
	fIn.Write (pbIn, nLen);
	fIn.Close ();
	CUnzip unzip (psTempFileIn);
	unzip.SwapSize (psTempFileOut);
	CFile fOut (psTempFileOut, CFile::typeBinary | CFile::modeRead);
	pbData = (ubyte *)aimMemoryCommit (fOut.GetLength (), "aimCompressZip", "pbData");
	fOut.Read (pbData, nOutLen = fOut.GetLength ());
	fOut.Close ();
	DeleteFile (psTempFileIn);
	DeleteFile (psTempFileOut);
	return (pbData);
}

void* aimMemoryReserve (DWORD dwSize, CString strProc, CString strMater, CString strTitle, CString strFile, UINT nLine) {
	if ( dwSize == 0 )
		return ( NULL );
	void* lpAddress = VirtualAlloc (NULL, dwSize, MEM_RESERVE, PAGE_READWRITE);
	if (!lpAddress) {
		void*	lpMessage;
		char	pcFormat [1024];
		CString	strMessage;
		FormatMessage (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		               NULL, GetLastError (), MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMessage, 0, NULL);
		LoadString (AfxGetApp()->m_hInstance, IDS_ERR_SYS_MEMRES, pcFormat, 1024);
		strMessage.Format (pcFormat, strProc, strFile, nLine, strMater, lpMessage);
		MessageBox (NULL, strMessage, strTitle, MB_OK | MB_ICONSTOP | MB_TASKMODAL);
		return (NULL);
	}
	return (lpAddress);
}

void* aimMemoryCommit (DWORD dwSize, CString strProc, CString strMater, CString strTitle, CString strFile, UINT nLine) {
	if (dwSize == 0)
		return (NULL);
	void* lpAddress = VirtualAlloc (NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
	if (!lpAddress) {
		void*	lpMessage;
		char	pcFormat [1024];
		CString strMessage;
		FormatMessage (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		               NULL, GetLastError (), MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMessage, 0, NULL);
		LoadString (AfxGetApp()->m_hInstance, IDS_ERR_SYS_MEMCOM, pcFormat, 1024);
		strMessage.Format (pcFormat, strProc, strFile, nLine, strMater, lpMessage);
		MessageBox (NULL, strMessage, strTitle, MB_OK | MB_ICONSTOP | MB_TASKMODAL);
		return (NULL);
	}
	return (lpAddress);
}

bool aimMemoryDecommit (void* lpAddress, DWORD dwSize, CString strProc, CString strMater, CString strTitle, CString strFile, UINT nLine) {
	if (dwSize == 0 || !lpAddress)
		return (true);
	if (!VirtualFree ( lpAddress, dwSize, MEM_DECOMMIT)) {
		void*	lpMessage;
		char	pcFormat [1024];
		CString strMessage;
		FormatMessage (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		               NULL, GetLastError (), MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMessage, 0, NULL);
		LoadString (AfxGetApp()->m_hInstance, IDS_ERR_SYS_MEMDECOM, pcFormat, 1024);
		strMessage.Format (pcFormat, strProc, strFile, nLine, strMater, lpMessage);
		MessageBox (NULL, strMessage, strTitle, MB_OK | MB_ICONSTOP | MB_TASKMODAL);
		return (false);
	}
	return (true);
}

bool aimMemoryRelease (void* lpAddress, CString strProc, CString strMater, CString strTitle, CString strFile, UINT nLine) {
	if (!lpAddress)
		return (true);
	if (!VirtualFree (lpAddress, 0, MEM_RELEASE)) {
		void*	lpMessage;
		char	pcFormat [1024];
		CString strMessage;
		FormatMessage (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		               NULL, GetLastError (), MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMessage, 0, NULL);
		LoadString (AfxGetApp()->m_hInstance, IDS_ERR_SYS_MEMREL, pcFormat, 1024);
		strMessage.Format (pcFormat, strProc, strFile, nLine, strMater, lpMessage);
		MessageBox (NULL, strMessage, strTitle, MB_OK | MB_ICONSTOP | MB_TASKMODAL);
		return (false);
	}
	return (true);
}
