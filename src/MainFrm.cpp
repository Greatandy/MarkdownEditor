
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "MarkdownEditor.h"

#include "MainFrm.h"
#include "LeftView.h"
#include "MarkdownEditorView.h"
#include "MarkdownEditorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

	BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
		ON_WM_CREATE()
		ON_WM_SIZE()
		ON_COMMAND(IDM_SWITCH, &CMainFrame::OnSwitch)
		ON_COMMAND(IDM_ABOUT, &CMainFrame::OnAbout)
		ON_COMMAND(IDM_EXAMPLE, &CMainFrame::OnExample)
	END_MESSAGE_MAP()

	static UINT indicators[] =
	{
		ID_SEPARATOR,           // ״̬��ָʾ��
		ID_INDICATOR_CAPS,
		ID_INDICATOR_NUM,
		ID_INDICATOR_SCRL,
	};

	// CMainFrame ����/����

	CMainFrame::CMainFrame()
	{
		_bInited = false;
		_bShowLeft = true;
		// TODO: �ڴ���ӳ�Ա��ʼ������
	}

	CMainFrame::~CMainFrame()
	{
	}

	int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
			return -1;

		//this->MoveWindow(0,0,800,600);
		this->CenterWindow();

		if (!m_wndStatusBar.Create(this))
		{
			TRACE0("δ�ܴ���״̬��\n");
			return -1;      // δ�ܴ���
		}
		m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
		OnSwitch();
		return 0;
	}

	BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
		CCreateContext* pContext)
	{
		// ������ִ���
		if (!m_wndSplitter.CreateStatic(this, 1, 2))
			return FALSE;

		CRect rect;
		this->GetWindowRect(&rect);
		CSize size(rect.Width() /2 , rect.Height() /2);

		if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), size, pContext) ||
			!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CMarkdownEditorView), size, pContext))
		{
			m_wndSplitter.DestroyWindow();
			return FALSE;
		}

		_bInited = true;

		return TRUE;
	}

	BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
	{
		if( !CFrameWnd::PreCreateWindow(cs) )
			return FALSE;
		// TODO: �ڴ˴�ͨ���޸�
		//  CREATESTRUCT cs ���޸Ĵ��������ʽ

		return TRUE;
	}

	// CMainFrame ���

#ifdef _DEBUG
	void CMainFrame::AssertValid() const
	{
		CFrameWnd::AssertValid();
	}

	void CMainFrame::Dump(CDumpContext& dc) const
	{
		CFrameWnd::Dump(dc);
	}
#endif //_DEBUG


	// CMainFrame ��Ϣ�������


	void CMainFrame::OnSize(UINT nType, int cx, int cy)
	{
		CFrameWnd::OnSize(nType, cx, cy);
		if(!_bInited)
			return;
		if(cx == 0 || cy == 0)
			return;
		int cxCur, cxMin;
		m_wndSplitter.GetColumnInfo(0, cxCur, cxMin); 
		if(cxCur <= 0)
			return;
		m_wndSplitter.SetColumnInfo(0,cx/2,10);
		m_wndSplitter.RecalcLayout();
	}


	void CMainFrame::OnSwitch(){
		_bShowLeft = !_bShowLeft;
		m_wndSplitter.ShowLeft(_bShowLeft);

	}


	const string STR_ABOUT = "#MarkdownEditor 1.0\nProject: <https://github.com/jijinggang/MarkdownEditor>\n##Author\njijinggang@gmail.com\n##Copyright\nFree For All";
	//ע�⣬����Ӧ�����������MainFrame�У��������MarkdownEditorView�У����MarkdownEditorViewʧȥ���㣬��˵����ܵ�
	void CMainFrame::OnAbout()
	{
		static bool s_bShowAbout = false;
		CMarkdownEditorView* pView = dynamic_cast<CMarkdownEditorView*>(m_wndSplitter.GetPane(0,1));
		if(pView == NULL)
			return;
		if(!s_bShowAbout)
			pView->UpdateMd(STR_ABOUT);
		else{
			CLeftView* pLeft = dynamic_cast<CLeftView*>(m_wndSplitter.GetPane(0,0));
			pView->GetDocument()->UpdateAllViews(pLeft, LPARAM_Update);
		}
		s_bShowAbout = !s_bShowAbout;
	}

	const string STR_EXAMPLE = " \
\r\n\
# ��ӭʹ�� MarkdownEditor �༭�Ķ���\r\n\
\r\n\
------\r\n\
\r\n\
�����������Ҫ����ݸ���Ч�Ĺ��߼�¼˼�룬����ʼǡ�֪ʶ���������г��صļ�ֵ���������ˣ� **MarkdownEditor** �����Ǹ����Ĵ� ���� ����Ϊ��¼˼��ͷ���֪ʶ�ṩ��רҵ�Ĺ��ߡ� ������ʹ�� MarkdownEditor��\r\n\
\r\n\
> * ����֪ʶ��ѧϰ�ʼ�\r\n\
> * �����ռǣ����ģ���������\r\n\
> * ׫д���������ĸ壨����֧�֣�\r\n\
> * ׫д����ѧ�����ģ�LaTeX ��ʽ֧�֣�\r\n\
\r\n\
��������ǰ��[github](https://github.com/k1988/markdowneditor)�������°汾��\r\n\
\r\n\
------\r\n\
\r\n\
## ʲô�� Markdown\r\n\
\r\n\
Markdown ��һ�ַ�����䡢��д�Ĵ��ı�������ԣ��û�����ʹ����Щ��Ƿ�������С������������ɼ������������ĵ���Ʃ���������Ķ�������ĵ�����ʹ�ü򵥵ķ��ű�ǲ�ͬ�ı��⣬�ָͬ�Ķ��䣬**����** ���� *б��* ĳЩ���֣��������ǣ���������\r\n\
\r\n\
### 1. ����һ�ݴ������� \r\n\
\r\n\
- [ ] ֧���� PDF ��ʽ�����ĸ�\r\n\
- [ ] �Ľ� Cmd ��Ⱦ�㷨��ʹ�þֲ���Ⱦ���������ȾЧ��\r\n\
- [x] ���� Todo �б���\r\n\
- [x] �޸� LaTex ��ʽ��Ⱦ����\r\n\
- [x] ���� LaTex ��ʽ��Ź���\r\n\
\r\n\
### 2. ���Ʊ��\r\n\
\r\n\
| ��Ŀ        | �۸�   |  ����  |\r\n\
| --------   | -----:  | :----:  |\r\n\
| �����     | \\$1600 |   5     |\r\n\
| �ֻ�        |  \\$12   |   12   |\r\n\
| ����        |    \\$1    |  234  |\r\n\
\r\n\
---\r\n\
\r\n\
## ʲô�� MarkdownEditor\r\n\
\r\n\
������ʹ�úܶ๤����д Markdown������ MarkdownEditor �����������������֪�ġ���õ� Markdown ���ߡ���û��֮һ ������Ϊ�������ֵ��������������Ǻ���һ������������д������˼���֪ʶ���Լ��Ķ������м��µ�׷�����ǰѶ�����Щ����Ļ�Ӧ������ MarkdownEditor������һ�Σ����Σ����Σ����������ε�����������ߵ����顣\r\n\
\r\n\
### 1. ʵʱͬ��Ԥ��\r\n\
\r\n\
���ǽ� MarkdownEditor ��������һ��Ϊ�������Ϊ**�༭��**���ұ�Ϊ**Ԥ����**���ڱ༭���Ĳ�����ʵʱ����Ⱦ��Ԥ��������鿴���յİ���Ч�������ᣡ\r\n\
\r\n\
### 3. �༭ģʽ\r\n\
\r\n\
��ȫ��������ķ�ʽ�༭���֣�����˵� **�鿴/�༭** �л��������ı༭ģʽ������һ�����ȼ���д�����������п��ܻ�������ĵ�Ԫ�ض��Ѿ���Ų��������ˬ��\r\n\
\r\n\
\r\n\
���� [@k1988](https://github.com/k1988)    \r\n\
2016 �� 05�� 18��    \r\n\
		";

	
	void CMainFrame::OnExample()
	{
		static bool s_bShowExmaple = false;
		static CString s_lastText;
		CMarkdownEditorView* pView = dynamic_cast<CMarkdownEditorView*>(m_wndSplitter.GetPane(0, 1));
		if (pView == NULL)
			return;
		if (!s_bShowExmaple)
		{
			CLeftView* pLeft = dynamic_cast<CLeftView*>(m_wndSplitter.GetPane(0, 0));
			pLeft->GetWindowText(s_lastText);
			pLeft->SetWindowText(STR_EXAMPLE.c_str());
			pLeft->OnEnChange();

			_bShowLeft = true;
			m_wndSplitter.ShowLeft(_bShowLeft);
		}
		else
		{
			CLeftView* pLeft = dynamic_cast<CLeftView*>(m_wndSplitter.GetPane(0, 0));

			pLeft->SetWindowText(s_lastText);
			pLeft->OnEnChange();

			pView->GetDocument()->UpdateAllViews(pLeft, LPARAM_Update);
		}
		s_bShowExmaple = !s_bShowExmaple;
	}
