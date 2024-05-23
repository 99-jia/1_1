
// 1_1View.h: CMy11View 类的接口
//

#pragma once


class CMy11View : public CView
{
protected: // 仅从序列化创建
	CMy11View() noexcept;
	DECLARE_DYNCREATE(CMy11View)

// 特性
public:
	CMy11Doc* GetDocument() const;
	virtual void OnTimer(UINT nIDEvent);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	

// 操作
public:
	int ituxing;
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMy11View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 1_1View.cpp 中的调试版本
inline CMy11Doc* CMy11View::GetDocument() const
   { return reinterpret_cast<CMy11Doc*>(m_pDocument); }
#endif

