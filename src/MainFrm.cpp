
// MainFrm.cpp : CMainFrame 类的实现
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
		ID_SEPARATOR,           // 状态行指示器
		ID_INDICATOR_CAPS,
		ID_INDICATOR_NUM,
		ID_INDICATOR_SCRL,
	};

	// CMainFrame 构造/析构

	CMainFrame::CMainFrame()
	{
		_bInited = false;
		_bShowLeft = true;
		// TODO: 在此添加成员初始化代码
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
			TRACE0("未能创建状态栏\n");
			return -1;      // 未能创建
		}
		m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
		OnSwitch();
		return 0;
	}

	BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
		CCreateContext* pContext)
	{
		// 创建拆分窗口
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
		// TODO: 在此处通过修改
		//  CREATESTRUCT cs 来修改窗口类或样式

		return TRUE;
	}

	// CMainFrame 诊断

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


	// CMainFrame 消息处理程序


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
	//注意，此相应函数必须放在MainFrame中，如果放在MarkdownEditorView中，如果MarkdownEditorView失去焦点，则菜单不能点
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
# 欢迎使用 MarkdownEditor 编辑阅读器\r\n\
\r\n\
------\r\n\
\r\n\
我们理解您需要更便捷更高效的工具记录思想，整理笔记、知识，并将其中承载的价值传播给他人， **MarkdownEditor** 是我们给出的答案 —— 我们为记录思想和分享知识提供更专业的工具。 您可以使用 MarkdownEditor：\r\n\
\r\n\
> * 整理知识，学习笔记\r\n\
> * 发布日记，杂文，所见所想\r\n\
> * 撰写发布技术文稿（代码支持）\r\n\
> * 撰写发布学术论文（LaTeX 公式支持）\r\n\
\r\n\
您还可以前往[github](https://github.com/k1988/markdowneditor)下载最新版本：\r\n\
\r\n\
------\r\n\
\r\n\
## 什么是 Markdown\r\n\
\r\n\
Markdown 是一种方便记忆、书写的纯文本标记语言，用户可以使用这些标记符号以最小的输入代价生成极富表现力的文档：譬如您正在阅读的这份文档。它使用简单的符号标记不同的标题，分割不同的段落，**粗体** 或者 *斜体* 某些文字，更棒的是，它还可以\r\n\
\r\n\
### 1. 制作一份待办事宜 \r\n\
\r\n\
- [ ] 支持以 PDF 格式导出文稿\r\n\
- [ ] 改进 Cmd 渲染算法，使用局部渲染技术提高渲染效率\r\n\
- [x] 新增 Todo 列表功能\r\n\
- [x] 修复 LaTex 公式渲染问题\r\n\
- [x] 新增 LaTex 公式编号功能\r\n\
\r\n\
### 2. 绘制表格\r\n\
\r\n\
| 项目        | 价格   |  数量  |\r\n\
| --------   | -----:  | :----:  |\r\n\
| 计算机     | \\$1600 |   5     |\r\n\
| 手机        |  \\$12   |   12   |\r\n\
| 管线        |    \\$1    |  234  |\r\n\
\r\n\
---\r\n\
\r\n\
## 什么是 MarkdownEditor\r\n\
\r\n\
您可以使用很多工具书写 Markdown，但是 MarkdownEditor 是这个星球上我们已知的、最好的 Markdown 工具——没有之一 ：）因为深信文字的力量，所以我们和你一样，对流畅书写，分享思想和知识，以及阅读体验有极致的追求，我们把对于这些诉求的回应整合在 MarkdownEditor，并且一次，两次，三次，乃至无数次地提升这个工具的体验。\r\n\
\r\n\
### 1. 实时同步预览\r\n\
\r\n\
我们将 MarkdownEditor 的主界面一分为二，左边为**编辑区**，右边为**预览区**，在编辑区的操作会实时地渲染到预览区方便查看最终的版面效果，超酷！\r\n\
\r\n\
### 3. 编辑模式\r\n\
\r\n\
完全心无旁骛的方式编辑文字：点击菜单 **查看/编辑** 切换到独立的编辑模式，这是一个极度简洁的写作环境，所有可能会引起分心的元素都已经被挪除，超清爽！\r\n\
\r\n\
\r\n\
作者 [@k1988](https://github.com/k1988)    \r\n\
2016 年 05月 18日    \r\n\
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
