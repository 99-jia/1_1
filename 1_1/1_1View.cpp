
// 1_1View.cpp: CMy11View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "1_1.h"
#endif

#include "1_1Doc.h"
#include "1_1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy11View

IMPLEMENT_DYNCREATE(CMy11View, CView)

BEGIN_MESSAGE_MAP(CMy11View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy11View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMy11View 构造/析构

CMy11View::CMy11View() noexcept
{
	ituxing = 0;
	// TODO: 在此处添加构造代码

}

CMy11View::~CMy11View()
{
}

BOOL CMy11View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy11View 绘图

void CMy11View::OnDraw(CDC* pDC)
{
	CMy11Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//清除当前图形
	CBrush mybrush1;
	mybrush1.CreateSolidBrush(RGB(255, 255, 255));
	CRect myrect1(0, 0, 1024, 768);
	pDC->FillRect(myrect1, &mybrush1);
	//判断当前图形ituxing
	if (ituxing == 1)
		//ituxing=1，画矩形
		pDC->Rectangle(20, 20, 89, 89);
	else if (ituxing == 2)
		//ituxing=2，画圆
		pDC->Ellipse(20, 20, 89, 89);
	else
		//否则，画三角形
	{
		pDC->MoveTo(20, 20);
		pDC->LineTo(89, 45);
		pDC->LineTo(20, 89);
		pDC->LineTo(20, 20);
	}
}


// CMy11View 打印


void CMy11View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy11View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy11View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy11View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMy11View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy11View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy11View 诊断

#ifdef _DEBUG
void CMy11View::AssertValid() const
{
	CView::AssertValid();
}

void CMy11View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy11Doc* CMy11View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy11Doc)));
	return (CMy11Doc*)m_pDocument;
}
#endif //_DEBUG
void CMy11View::OnTimer(UINT nIDEvent)
{

	//获取指针pdc
	CDC* pDC = GetDC();

	//调用OnDraw(pDC)重画
	OnDraw(pDC);

	//使ituxing循环
	ituxing = (ituxing + 1) % 3;
	CView::OnTimer(nIDEvent);
}
int CMy11View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	//设置更新时间
	SetTimer(1, 750, NULL);
	return 0;
}

// CMy11View 消息处理程序
//99+更新