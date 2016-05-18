
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "MySplitterWnd.h"
class CMarkdownEditorView;

class CMainFrame : public CFrameWnd
{
private:
	bool _bInited;
	bool _bShowLeft;
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
protected:
	CMySplitterWnd m_wndSplitter;
public:

// ����
public:

// ��д
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
	CMarkdownEditorView* GetRightPane();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CStatusBar        m_wndStatusBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSwitch();
	afx_msg void OnAbout();
	afx_msg void OnExample();
};


