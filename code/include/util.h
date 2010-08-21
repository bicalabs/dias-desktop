#ifndef UTIL__INCLUDED
#define UTIL__INCLUDED

#pragma once

class CDiasApp;

int		aimGetSelListItem (CListCtrl& ctrlList, BOOL blFocus);
void	aimSetSelListItem (CListCtrl& ctrlList, int no);

void	aimRotate2D (uvar32_64 no, rtbyte *pPointsX, rtbyte *pPointsY, rtbyte rAngle, CPoint pntCenter);
ubyte	*aimCompressZip (ubyte *pbIn, uvar32_64 nLen, uvar32_64 &nOutLen);
ubyte	*aimDecompressZip (ubyte *pbIn, uvar32_64 nLen, uvar32_64 &nOutLen);
void*	aimMemoryReserve (DWORD dwSize, CString strProc = "Unknown", CString strMater = "Unknown", CString strTitle = AfxGetApp()->m_pszAppName, CString strFile = __FILE__, UINT nLine = __LINE__);
void*	aimMemoryCommit (DWORD dwSize, CString strProc = "Unknown", CString strMater = "Unknown", CString strTitle = AfxGetApp()->m_pszAppName, CString strFile = __FILE__, UINT nLine = __LINE__);
bool	aimMemoryDecommit (void* lpAddress, DWORD dwSize, CString strProc = "Unknown", CString strMater = "Unknown", CString strTitle = AfxGetApp()->m_pszAppName, CString strFile = __FILE__, UINT nLine = __LINE__);
bool	aimMemoryRelease (void* lpAddress, CString strProc = "Unknown", CString strMater = "Unknown", CString strTitle = AfxGetApp()->m_pszAppName, CString strFile = __FILE__, UINT nLine = __LINE__);

#endif
