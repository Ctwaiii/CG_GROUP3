// CadSurfView.cpp : implementation of the CCadSurfView class
//

#include "stdafx.h"
#include "CadSurf.h"

#include "CadSurfDoc.h"
#include "CadSurfView.h"
#include "ChildFrm.h" 
#include "Light.h"


#include "GLView.h"
#include "COMMAND.H"
#include "CREATECMD.H"

#include "Input.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCadSurfView

IMPLEMENT_DYNCREATE(CCadSurfView, CView)

BEGIN_MESSAGE_MAP(CCadSurfView, CView)
	//{{AFX_MSG_MAP(CCadSurfView)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_ZOOMWIN, OnZoomwin)
	ON_COMMAND(ID_RESETVIEW, OnResetview)
	ON_COMMAND(ID_DISPLAYMODE, OnDisplaymode)
	ON_UPDATE_COMMAND_UI(ID_DISPLAYMODE, OnUpdateDisplaymode)
	ON_COMMAND(ID_VIEW_DISPLAYALL, OnViewDisplayall)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DISPLAYALL, OnUpdateViewDisplayall)
	ON_COMMAND(ID_VIEW_ERASEALL, OnViewEraseall)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ERASEALL, OnUpdateViewEraseall)
	ON_COMMAND(ID_VIEW_DISPLAYSELECTED, OnViewDisplayselected)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DISPLAYSELECTED, OnUpdateViewDisplayselected)
	ON_COMMAND(ID_VIEW_ERASESELECTED, OnViewEraseselected)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ERASESELECTED, OnUpdateViewEraseselected)
	ON_COMMAND(ID_PREFERENCES_DISPLAYMODE_SHADED, OnPreferencesDisplaymodeShaded)
	ON_UPDATE_COMMAND_UI(ID_PREFERENCES_DISPLAYMODE_SHADED, OnUpdatePreferencesDisplaymodeShaded)
	ON_COMMAND(ID_PREFERENCES_DISPLAYMODE_WIREFRAME, OnPreferencesDisplaymodeWireframe)
	ON_UPDATE_COMMAND_UI(ID_PREFERENCES_DISPLAYMODE_WIREFRAME, OnUpdatePreferencesDisplaymodeWireframe)
	ON_COMMAND(ID_PREFERENCES_MATERIAL, OnPreferencesMaterial)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_COORD, OnUpdateCoordViewer)
	ON_UPDATE_COMMAND_UI(ID_PREFERENCES_MATERIAL, OnUpdatePreferencesMaterial)
	ON_COMMAND(ID_PREFERENCES_COLOR, OnPreferencesColor)
	ON_UPDATE_COMMAND_UI(ID_PREFERENCES_COLOR, OnUpdatePreferencesColor)
	ON_COMMAND(ID_PREFERENCES_BACKGROUNDCOLOR, OnPreferencesBackgroundcolor)
	ON_COMMAND(ID_HLREMOVED, OnHlremoved)
	ON_COMMAND(ID_ANTIALIAS, OnAntialias)
	ON_COMMAND(ID_PREFERENCES_LINESTYLE_SOLID, OnPreferencesLinestyleSolid)
	ON_COMMAND(ID_PREFERENCES_LINESTYLE_DOTTED, OnPreferencesLinestyleDotted)
	ON_COMMAND(ID_PREFERENCES_LINESTYLE_DASHED, OnPreferencesLinestyleDashed)
	ON_COMMAND(ID_PREFERENCES_LINESTYLE_DASHEDDOTTED, OnPreferencesLinestyleDasheddotted)
	ON_COMMAND(ID_PREFERENCES_GRID_ON, OnPreferencesGridOn)
	ON_UPDATE_COMMAND_UI(ID_PREFERENCES_GRID_ON, OnUpdatePreferencesGridOn)
	ON_COMMAND(ID_PREFERENCES_GRID_SETTINGS, OnPreferencesGridSettings)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_SNAPSHOT, OnSnapshot)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_TOPVIEW, OnTopview)
	ON_COMMAND(ID_BOTTOMVIEW, OnBottomview)
	ON_COMMAND(ID_FRONTVIEW, OnFrontview)
	ON_COMMAND(ID_BACKVIEW, OnBackview)
	ON_COMMAND(ID_LEFTVIEW, OnLeftview)
	ON_COMMAND(ID_RIGHTVIEW, OnRightview)
	ON_COMMAND(ID_AXONVIEW, OnAxonview)
	ON_COMMAND(ID_FITALL, OnFitall)
	ON_COMMAND(ID_PROJECTION_TYPE, OnProjectionType)
	ON_UPDATE_COMMAND_UI(ID_PROJECTION_TYPE, OnUpdateProjectionType)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_PREFERENCES_LIGHT, OnPreferencesLight)
	ON_UPDATE_COMMAND_UI(ID_PREFERENCES_LIGHT, OnUpdatePreferencesLight)
	ON_COMMAND(ID_SKECH_LINE, &CCadSurfView::OnSkechLine)
	ON_UPDATE_COMMAND_UI(ID_SKECH_LINE, &CCadSurfView::OnUpdateSkechLine)
	ON_COMMAND(ID_SKETCH_XOY, &CCadSurfView::OnSketchXoy)
	ON_UPDATE_COMMAND_UI(ID_SKETCH_XOY, &CCadSurfView::OnUpdateSketchXoy)
	ON_COMMAND(ID_SKETCH_XOZ, &CCadSurfView::OnSketchXoz)
	ON_UPDATE_COMMAND_UI(ID_SKETCH_XOZ, &CCadSurfView::OnUpdateSketchXoz)
	ON_COMMAND(ID_SKETCH_YOZ, &CCadSurfView::OnSketchYoz)
	ON_COMMAND(ID_SKETCH_CLOSE, &CCadSurfView::OnSketchClose)
	ON_UPDATE_COMMAND_UI(ID_SKETCH_YOZ, &CCadSurfView::OnUpdateSketchYoz)
	ON_UPDATE_COMMAND_UI(ID_SKETCH_CLOSE, &CCadSurfView::OnUpdateSketchClose)
	ON_COMMAND(ID_SKECH_CIRCLE, &CCadSurfView::OnSkechCircle)
	ON_UPDATE_COMMAND_UI(ID_SKECH_CIRCLE, &CCadSurfView::OnUpdateSkechCircle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCadSurfView construction/destruction

CCadSurfView::CCadSurfView()
{
	m_iSketchPlane = 0;
	m_iSketchType = 0; //什么都不做;

	// TODO: add construction code here
	lbutdown = false;
	mbutdown = false;
	rbutdown = false;
	winZoom = false;
	dShaded = true;
	antialiased = false;
	gridOn = false;
	coord.Format("");
	view.Format(_T("AXO"));
	m_Pen = new CPen(PS_SOLID, 2, RGB(0, 0, 0));

	hDIB = NULL;
	m_palDIB = new CPalette;
	m_nSaveBMPFlag = BMPCLIENT;

	m_pCmd = NULL;
}

CCadSurfView::~CCadSurfView()
{
	if (m_pCmd)
		delete m_pCmd;

	delete m_Pen;

	//printing
	if (hDIB != NULL)
	{
		::GlobalUnlock(hDIB);
		::GlobalFree(hDIB);
		hDIB = NULL;
	}
	if (m_palDIB != NULL)
	{
		delete m_palDIB;
		m_palDIB = NULL;
	}
}

BOOL CCadSurfView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

int CCadSurfView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here
	myView = new CGLView(this, GetDocument()->dContext);
	return 0;
}

void CCadSurfView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	delete myView;
}

/////////////////////////////////////////////////////////////////////////////
// CCadSurfView drawing

void CCadSurfView::OnDraw(CDC* pDC)
{
	CCadSurfDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if (pDC->IsPrinting())
		PrintDIB(pDC);
	else
	{
		::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		myView->Draw();
		myView->SwapBuffers();
		//GDI
		pDC->SetBkMode(0);
		pDC->SetTextColor(RGB(255, 255, 0));
		pDC->TextOut(1, 1, view);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCadSurfView printing

BOOL CCadSurfView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	pInfo->SetMaxPage(1);
	m_nSaveBMPFlag = BMPCLIENT;
	return DoPreparePrinting(pInfo);
}

void CCadSurfView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCadSurfView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCadSurfView diagnostics

#ifdef _DEBUG
void CCadSurfView::AssertValid() const
{
	CView::AssertValid();
}

void CCadSurfView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCadSurfDoc* CCadSurfView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCadSurfDoc)));
	return (CCadSurfDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCadSurfView message handlers

void CCadSurfView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	SetTimer(1, 1000, NULL);
	// TODO: Add your specialized code here and/or call the base class

}

void CCadSurfView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (myView)
		myView->ReSize(cx, cy);
}

void CCadSurfView::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CView::OnTimer(nIDEvent);
}


void CCadSurfView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	SetCapture(); // 捕获鼠标事件，确保能够处理后续动作

	// 获取当前鼠标选中的图形对象
	CGLObject* sel_obj = myView->CurrentSelected();

	// **处理选中的点对象**
	CGLPoint* sel_pt = dynamic_cast<CGLPoint*>(sel_obj); // 尝试将选中对象转换为点对象
	if (sel_pt) {
		// 在 bsp_mgr 的 mm_glpoint 映射表中找到该点
		auto itr = GetDocument()->bsp_mgr.mm_glpoint.find(sel_pt->GetObjID());
		if (itr != GetDocument()->bsp_mgr.mm_glpoint.end()) {
			ASSERT(itr->second.first->GetObjID() == sel_pt->GetObjID()); // 验证对象 ID 一致性

			// 创建输入框以显示和修改点的坐标
			Input ip(this);
			CPoint3D* pt3d = (CPoint3D*)sel_pt->Geometry(); // 获取点的几何数据

			// 将点的当前坐标格式化为字符串
			std::string tmp = "x:" + std::to_string(pt3d->GetX())
				+ ";y:" + std::to_string(pt3d->GetY()) + ";z:" + std::to_string(pt3d->GetZ());
			ip.str = tmp.c_str();

			// 弹出对话框，等待用户输入新的坐标
			auto ret = ip.DoModal();
			if (ret == 1) { // 如果用户确认修改
				CString rString = ip.str; // 获取输入的字符串

				// 解析用户输入的坐标值
				int nCurPos = 0;
				std::vector<double> vec_num;
				CString strSep(_T(";"));
				CString strSub = rString.Tokenize(strSep, nCurPos); // 按 ";" 分隔输入
				auto num_len = strSub.GetLength() - strSub.Find(":") - 1;
				auto rr = strSub.Right(num_len).Trim();
				double a = atof(rr.GetString());
				vec_num.push_back(a);

				while (strSub != _T(""))
				{
					strSub.Trim();
					strSub = rString.Tokenize(strSep, nCurPos);
					if (strSub != _T(""))
					{
						auto num_len = strSub.GetLength() - strSub.Find(":") - 1;
						auto rr = strSub.Right(num_len).Trim();
						double a = atof(rr.GetString());
						vec_num.push_back(a);
					}
				}

				// 更新点的坐标
				int idx = itr->second.second;
				CPoint3D& newpt = GetDocument()->bsp_mgr.vec_CPoint3D[idx];
				newpt.SetX(vec_num[0]);
				newpt.SetY(vec_num[1]);
				newpt.SetZ(vec_num[2]);

				// 重新显示场景
				GetDocument()->bsp_mgr.Display(GetDocument()->dContext);
				return;
			}
		}
	}
	// **处理选中的曲线对象**
	CGLCurve* sel_curve = dynamic_cast<CGLCurve*>(sel_obj);
	if (sel_curve) {
		// 验证选中的曲线是否是当前管理的曲线对象
		CGLCurve* target_curve = GetDocument()->bsp_mgr.gCRV;
		if (target_curve && target_curve->GetObjID() == sel_curve->GetObjID()) {

			// 获取当前拉伸面启用状态
			int nEnbale = GetDocument()->bsp_mgr.enable_stretch_face ? 1 : 0;

			// 显示当前状态并允许用户修改
			std::string tmp = "enable face:" + std::to_string(nEnbale);
			Input ip(this);
			ip.str = tmp.c_str();
			auto ret = ip.DoModal();
			if (ret == 1) { // 如果用户确认修改
				CString rString = ip.str;
				auto num_len = rString.GetLength() - rString.Find(":") - 1;
				auto rr = rString.Right(num_len).Trim();
				int a = atoi(rr.GetString());
				if (nEnbale != a) {
					if (a == 1) {
						GetDocument()->bsp_mgr.enable_stretch_face = true; // 启用拉伸面
					}
					else {
						GetDocument()->bsp_mgr.enable_stretch_face = false; // 禁用拉伸面
					}
					// 重新显示场景
					GetDocument()->bsp_mgr.Display(GetDocument()->dContext);
					return;
				}
			}
		}
	}
	// **处理选中的拉伸面对象**
	CGLSurface* sel_surface = dynamic_cast<CGLSurface*>(sel_obj);
	if (sel_surface) {
		// 验证选中的拉伸面是否是当前管理的拉伸面对象
		CGLSurface* target_surface = GetDocument()->bsp_mgr.stretch_face;
		if (target_surface && target_surface->GetObjID() == sel_surface->GetObjID()) {

			// 获取拉伸面的方向和长度
			CVector3D& dir = GetDocument()->bsp_mgr.stretch_dir;
			unsigned long int& len = GetDocument()->bsp_mgr.stretch_len;

			// 显示当前方向和长度，并允许用户修改
			std::string tmp = "dir_x:" + std::to_string(dir.GetX())
				+ ";dir_y:" + std::to_string(dir.GetY())
				+ ";dir_z:" + std::to_string(dir.GetZ())
				+ ";len:" + std::to_string(len);

			Input ip(this);
			ip.str = tmp.c_str();
			auto ret = ip.DoModal();
			if (ret == 1) { // 如果用户确认修改
				CString rString = ip.str;

				// 解析用户输入的方向和长度值
				int nCurPos = 0;
				std::vector<double> vec_num;
				CString strSep(_T(";"));
				CString strSub = rString.Tokenize(strSep, nCurPos);
				auto num_len = strSub.GetLength() - strSub.Find(":") - 1;
				auto rr = strSub.Right(num_len).Trim();
				double a = atof(rr.GetString());
				vec_num.push_back(a);

				while (strSub != _T(""))
				{
					strSub.Trim();
					strSub = rString.Tokenize(strSep, nCurPos);
					if (strSub != _T(""))
					{
						auto num_len = strSub.GetLength() - strSub.Find(":") - 1;
						auto rr = strSub.Right(num_len).Trim();
						double a = atof(rr.GetString());
						vec_num.push_back(a);
					}
				}

				// 更新方向和长度
				dir.SetX(vec_num[0]);
				dir.SetY(vec_num[1]);
				dir.SetZ(vec_num[2]);
				len = (unsigned long int)vec_num[3];

				// 重新显示场景
				GetDocument()->bsp_mgr.Display(GetDocument()->dContext);
				return;
			}
		}
	}

	// 如果选中对象不是点、曲线或拉伸面，则调用父类默认处理
	CView::OnLButtonDown(nFlags, point);
}

void CCadSurfView::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();

	//如果草图绘制;
	if (m_pCmd)
	{
		CPoint3D pt3d;
		myView->ScreenToPoint(point.x, point.y, pt3d);
		m_pCmd->OnLButtonDown(nFlags, pt3d);
		CView::OnLButtonDown(nFlags, point);
		return;
	}

	myXmin = point.x;  myYmin = point.y;
	myXmax = point.x;  myYmax = point.y;


	lbutdown = true;
	lDownPnt = point;

	// 将鼠标点击屏幕坐标转换为场景中的 3D 点
	CPoint3D clickedPt;
	myView->ScreenToPoint(point.x, point.y, clickedPt);

	// 初始化最近点的变量
	double minDistance = DBL_MAX; // 设置一个很大的初始距离
	int closestPointIdx = -1;     // 最近点的索引
	CPoint3D* closestPoint = nullptr;

	// 遍历所有点，找到距离鼠标点击点最近的点
	for (int i = 0; i < GetDocument()->bsp_mgr.vec_CPoint3D.size(); ++i)
	{
		CPoint3D& pt = GetDocument()->bsp_mgr.vec_CPoint3D[i]; // 获取控制点
		double distance = sqrt(pow(pt.GetX() - clickedPt.GetX(), 2) +
			pow(pt.GetY() - clickedPt.GetY(), 2) +
			pow(pt.GetZ() - clickedPt.GetZ(), 2)); // 计算欧几里得距离

		if (distance < minDistance) // 更新最近点
		{
			minDistance = distance;
			closestPointIdx = i;
			closestPoint = &pt;
		}
	}

	// 如果找到最近点，更新其坐标为鼠标点击的坐标
	if (closestPoint)
	{
		closestPoint->SetX(clickedPt.GetX());
		closestPoint->SetY(clickedPt.GetY());
		closestPoint->SetZ(clickedPt.GetZ());

		// 更新场景显示
		GetDocument()->bsp_mgr.Display(GetDocument()->dContext);
	}

	if (!(nFlags & MK_SHIFT) && !(nFlags & MK_CONTROL) && !winZoom)
	{
		myView->Select(point.x, point.y);
		InvalidateRect(NULL, FALSE);
	}
	if ((nFlags & MK_SHIFT) && !(nFlags & MK_CONTROL) && !winZoom)
	{
		myView->MultiSelect(point.x, point.y);
		InvalidateRect(NULL, FALSE);
	}
	CView::OnLButtonDown(nFlags, point);
}

void CCadSurfView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_pCmd)
	{
		ReleaseCapture();

		CView::OnLButtonUp(nFlags, point);
		return;
	}
	// TODO: Add your message handler code here and/or call default
	lbutdown = false;
	myView->StopZooming();

	if (!(nFlags & MK_SHIFT) && !(nFlags & MK_CONTROL) && !winZoom)
	{
		DrawRectangle(false);
		CRect rect(lDownPnt, point);
		rect.NormalizeRect();
		if (rect.Width() && rect.Height())
			myView->SweepSelect(rect);
		InvalidateRect(NULL, FALSE);
	}

	if (winZoom)
	{
		myXmax = point.x;  myYmax = point.y;
		DrawRectangle(false);
		CRect myZoomRect(myXmin, myYmax, myXmax, myYmin);
		if ((abs(myXmin - myXmax) > 1) || (abs(myYmin - myYmax) > 1))
			// Test if the zoom window size is not null
		{
			myView->ZoomWindow(myZoomRect);
		}
	}

	winZoom = false;
	ReleaseCapture();

	CView::OnLButtonUp(nFlags, point);
}

void CCadSurfView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	mbutdown = true;
	mDownPnt = point;
	CView::OnMButtonDown(nFlags, point);
}

void CCadSurfView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	mbutdown = false;
	myView->StopPanning();
	CView::OnMButtonUp(nFlags, point);
}

void CCadSurfView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	rbutdown = true;
	rDownPnt = point;
	CView::OnRButtonDown(nFlags, point);
}

void CCadSurfView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	rbutdown = false;
	myView->StopRotation();
	CView::OnRButtonUp(nFlags, point);
}

void CCadSurfView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_pCmd)
	{
		CPoint3D pt3d;
		myView->ScreenToPoint(point.x, point.y, pt3d);
		// 		//处理一下，根据视图;
		// 		if (myView->GetViewType() == GLFRONTVIEW) //FRONT
		// 		{
		// 			pt3d.SetY(pt3d.GetZ());
		// 		}
		// 		else if (myView->GetViewType() == GLLEFTVIEW) //LEFT
		// 		{
		// 			pt3d.SetX(pt3d.GetZ());
		// 		}
		m_pCmd->OnMouseMove(nFlags, pt3d);
		CView::OnMouseMove(nFlags, point);
		return;
	}

	// TODO: Add your message handler code here and/or call default
	if (lbutdown && (nFlags & MK_CONTROL))
	{
		myView->ZoomView(lDownPnt, point);
		Invalidate(FALSE);
	}
	if (mbutdown && (nFlags & MK_CONTROL))
	{
		myView->PanView(mDownPnt, point);
		Invalidate(FALSE);
	}
	if (rbutdown && (nFlags & MK_CONTROL))
	{
		if (myView->GetViewType() == GLAXONVIEW || myView->GetViewType() == GLUNDEFINEDVIEW)
		{
			myView->RotateView(rDownPnt, point);
			Invalidate(FALSE);
		}
		else
			coord.Format("Rotation Allowed Only In Axonometric View");
	}
	if (lbutdown && !(nFlags & MK_CONTROL) && !(nFlags & MK_SHIFT))
	{
		myXmax = point.x; myYmax = point.y;
		DrawRectangle(true, LongDash);
	}

	CPoint3D C;
	myView->ScreenToPoint(point.x, point.y, C);
	coord.Format("X %0.3lf  Y %0.3lf  Z%0.3lf", C.GetX(), C.GetY(), C.GetZ());

	CView::OnMouseMove(nFlags, point);
}



void CCadSurfView::OnTopview()
{
	// TODO: Add your command handler code here
	myView->TopView();
	view.Format(_T("TOP"));
}

void CCadSurfView::OnBottomview()
{
	// TODO: Add your command handler code here
	myView->BottomView();
	view.Format(_T("BOTTOM"));
}

void CCadSurfView::OnFrontview()
{
	// TODO: Add your command handler code here
	myView->FrontView();
	view.Format(_T("FRONT"));
}

void CCadSurfView::OnBackview()
{
	// TODO: Add your command handler code here
	myView->BackView();
	view.Format(_T("BACK"));
}

void CCadSurfView::OnLeftview()
{
	// TODO: Add your command handler code here
	myView->LeftView();
	view.Format(_T("LEFT"));
}

void CCadSurfView::OnRightview()
{
	// TODO: Add your command handler code here
	myView->RightView();
	view.Format(_T("RIGHT"));
}

void CCadSurfView::OnAxonview()
{
	// TODO: Add your command handler code here
	myView->AxonView();
	view.Format(_T("AXO"));
}

void CCadSurfView::OnFitall()
{
	// TODO: Add your command handler code here
	myView->FitAll();
}

void CCadSurfView::OnZoomwin()
{
	// TODO: Add your command handler code here
	winZoom = true;
}

void CCadSurfView::OnResetview()
{
	// TODO: Add your command handler code here
	myView->ResetView();
	view.Format(_T("AXO"));
}


void CCadSurfView::OnDisplaymode()
{
	// TODO: Add your command handler code here
	dShaded = !dShaded;
	if (dShaded)
	{
		POSITION pos = GetDocument()->GetFirstViewPosition();
		while (pos != NULL)
		{
			CCadSurfView* view = (CCadSurfView*)GetDocument()->GetNextView(pos);
			view->GetView()->SetDisplayMode(GLSHADED);
		}
	}
	else
	{
		POSITION pos = GetDocument()->GetFirstViewPosition();
		while (pos != NULL)
		{
			CCadSurfView* view = (CCadSurfView*)GetDocument()->GetNextView(pos);
			view->GetView()->SetDisplayMode(GLWIREFRAME);
		}
	}
}

void CCadSurfView::OnUpdateDisplaymode(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
}

void CCadSurfView::OnHlremoved()
{
	// TODO: Add your command handler code here
	POSITION pos = GetDocument()->GetFirstViewPosition();
	while (pos != NULL)
	{
		CCadSurfView* view = (CCadSurfView*)GetDocument()->GetNextView(pos);
		view->GetView()->SetDisplayMode(GLHLREMOVED);
	}
}

void CCadSurfView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: Add your specialized code here and/or call the base class
	POSITION pos = GetDocument()->GetFirstViewPosition();
	while (pos != NULL)
	{
		CCadSurfView* view = (CCadSurfView*)GetDocument()->GetNextView(pos);
		view->GetView()->Refresh();
	}
	CView::OnUpdate(pSender, lHint, pHint);

}


void CCadSurfView::OnViewDisplayall()
{
	// TODO: Add your command handler code here
	GetDocument()->dContext->DisplayAll();
}

void CCadSurfView::OnUpdateViewDisplayall(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!GetDocument()->dContext->IsAllDisplayed());
}

void CCadSurfView::OnViewEraseall()
{
	// TODO: Add your command handler code here
	GetDocument()->dContext->EraseAll();
}

void CCadSurfView::OnUpdateViewEraseall(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!GetDocument()->dContext->IsAllErased());
}

void CCadSurfView::OnViewDisplayselected()
{
	// TODO: Add your command handler code here
	CGLDisplayContext* ctx = GetDocument()->dContext;
	ctx->DisplaySelected();
}

void CCadSurfView::OnUpdateViewDisplayselected(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CGLDisplayContext* ctx = GetDocument()->dContext;
	pCmdUI->Enable(ctx->HasSelected());
}

void CCadSurfView::OnViewEraseselected()
{
	// TODO: Add your command handler code here
	CGLDisplayContext* ctx = GetDocument()->dContext;
	ctx->EraseSelected();
}

void CCadSurfView::OnUpdateViewEraseselected(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CGLDisplayContext* ctx = GetDocument()->dContext;
	pCmdUI->Enable(ctx->HasSelected());
}

void CCadSurfView::OnUpdateCoordViewer(CCmdUI* pCmdUI)
{
	if (myView->GetViewType() == GLAXONVIEW || myView->GetViewType() == GLUNDEFINEDVIEW)
		pCmdUI->SetText(_T(""));
	else
		pCmdUI->SetText((LPCTSTR)coord);
}

void CCadSurfView::OnPreferencesDisplaymodeShaded()
{
	// TODO: Add your command handler code here
	dShaded = true;
	POSITION pos = GetDocument()->GetFirstViewPosition();
	while (pos != NULL)
	{
		CCadSurfView* view = (CCadSurfView*)GetDocument()->GetNextView(pos);
		view->GetView()->SetDisplayMode(GLSHADED);
	}
}

void CCadSurfView::OnPreferencesDisplaymodeWireframe()
{
	// TODO: Add your command handler code here
	dShaded = false;
	POSITION pos = GetDocument()->GetFirstViewPosition();
	while (pos != NULL)
	{
		CCadSurfView* view = (CCadSurfView*)GetDocument()->GetNextView(pos);
		view->GetView()->SetDisplayMode(GLWIREFRAME);
	}
}

void CCadSurfView::OnUpdatePreferencesDisplaymodeWireframe(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(!dShaded);
}

void CCadSurfView::OnAntialias()
{
	// TODO: Add your command handler code here
	antialiased = !antialiased;
	POSITION pos = GetDocument()->GetFirstViewPosition();
	while (pos != NULL)
	{
		CCadSurfView* view = (CCadSurfView*)GetDocument()->GetNextView(pos);
		view->GetView()->SetAntiAliasing(antialiased);
	}
}

#include "MaterialDlg.h"
void CCadSurfView::OnPreferencesMaterial()
{
	// TODO: Add your command handler code here
	CMaterialDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CGLDisplayContext* ctx = GetDocument()->dContext;
		for (ctx->InitSelected(); ctx->MoreSelected(); ctx->NextSelected())
		{
			CGLObject* O = ctx->CurrentSelected();
			O->SetLight(dlg.m_Matl);
		}
		InvalidateRect(NULL, FALSE);
		GetDocument()->UpdateAllViews(NULL);
	}
}

void CCadSurfView::OnUpdatePreferencesMaterial(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CGLDisplayContext* ctx = GetDocument()->dContext;
	pCmdUI->Enable(ctx->HasSelected() && dShaded);
}

void CCadSurfView::OnPreferencesColor()
{
	// TODO: Add your command handler code here
	CColorDialog dlg;
	dlg.m_cc.Flags |= CC_RGBINIT;
	dlg.m_cc.rgbResult = RGB(255, 0, 0);
	if (dlg.DoModal() == IDOK)
	{
		COLORREF color = dlg.GetColor();
		GLubyte m_Red = (GLubyte)GetRValue(color);
		GLubyte m_Green = (GLubyte)GetGValue(color);
		GLubyte m_Blue = (GLubyte)GetBValue(color);
		CGLDisplayContext* ctx = GetDocument()->dContext;
		for (ctx->InitSelected(); ctx->MoreSelected(); ctx->NextSelected())
		{
			CGLObject* O = ctx->CurrentSelected();
			O->SetColor(m_Red, m_Green, m_Blue);
		}
		InvalidateRect(NULL, FALSE);
		GetDocument()->UpdateAllViews(NULL);
	}
}

void CCadSurfView::OnUpdatePreferencesColor(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CGLDisplayContext* ctx = GetDocument()->dContext;
	pCmdUI->Enable(ctx->HasSelected());
}

void CCadSurfView::OnPreferencesLinestyleSolid()
{
	// TODO: Add your command handler code here
	CGLDisplayContext* ctx = GetDocument()->dContext;
	for (ctx->InitSelected(); ctx->MoreSelected(); ctx->NextSelected())
	{
		CGLObject* O = ctx->CurrentSelected();
		if (O->IsOfType(GLCURVE))
		{
			CGLCurve* crv = static_cast<CGLCurve*>(O);
			crv->SetLineStyle(LINE_SOLID);
		}
	}
	InvalidateRect(NULL, FALSE);
}

void CCadSurfView::OnPreferencesLinestyleDotted()
{
	// TODO: Add your command handler code here
	CGLDisplayContext* ctx = GetDocument()->dContext;
	for (ctx->InitSelected(); ctx->MoreSelected(); ctx->NextSelected())
	{
		CGLObject* O = ctx->CurrentSelected();
		if (O->IsOfType(GLCURVE))
		{
			CGLCurve* crv = static_cast<CGLCurve*>(O);
			crv->SetLineStyle(LINE_DOTTED);
		}
	}
	InvalidateRect(NULL, FALSE);
}

void CCadSurfView::OnPreferencesLinestyleDashed()
{
	// TODO: Add your command handler code here
	CGLDisplayContext* ctx = GetDocument()->dContext;
	for (ctx->InitSelected(); ctx->MoreSelected(); ctx->NextSelected())
	{
		CGLObject* O = ctx->CurrentSelected();
		if (O->IsOfType(GLCURVE))
		{
			CGLCurve* crv = static_cast<CGLCurve*>(O);
			crv->SetLineStyle(LINE_DASHED);
		}
	}
	InvalidateRect(NULL, FALSE);
}

void CCadSurfView::OnPreferencesLinestyleDasheddotted()
{
	// TODO: Add your command handler code here
	CGLDisplayContext* ctx = GetDocument()->dContext;
	for (ctx->InitSelected(); ctx->MoreSelected(); ctx->NextSelected())
	{
		CGLObject* O = ctx->CurrentSelected();
		if (O->IsOfType(GLCURVE))
		{
			CGLCurve* crv = static_cast<CGLCurve*>(O);
			crv->SetLineStyle(LINE_DASHDOTTED);
		}
	}
	InvalidateRect(NULL, FALSE);
}

void CCadSurfView::OnUpdatePreferencesDisplaymodeShaded(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(dShaded);
}

void CCadSurfView::OnPreferencesGridOn()
{
	// TODO: Add your command handler code here
	gridOn = !gridOn;
	myView->SetGridOn(gridOn);
}

void CCadSurfView::OnUpdatePreferencesGridOn(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if (!gridOn)
	{
		pCmdUI->SetText((LPCTSTR)_T("ON"));
	}
	else
	{
		pCmdUI->SetText((LPCTSTR)_T("OFF"));
	}

}

#include "GridDlg.h"
void CCadSurfView::OnPreferencesGridSettings()
{
	// TODO: Add your command handler code here
	CGridDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		//GLfloat x,y,z;
		//x=dlg.m_x;y=dlg.m_y;z=dlg.m_z;

		double dx, dy, dz, size, step;
		//step=dlg.m_x;size=dlg.m_y;dz=dlg.m_z;
		dx = dlg.m_DX;
		dy = dlg.m_DY;
		dz = dlg.m_DZ;
		size = dlg.m_Size;
		step = dlg.m_Step;
		dy = 60; dx = 100;
		if (dx == 0 && dy == 0 && dz == 0)
			dz = 1;
		CPlane plane(dx, dy, dz, 0);
		myView->SetGridPara(plane, size, step);
	}
}

void CCadSurfView::OnPreferencesBackgroundcolor()
{
	// TODO: Add your command handler code here
	CColorDialog dlg;
	dlg.m_cc.Flags |= CC_RGBINIT;
	dlg.m_cc.rgbResult = RGB(0, 0, 0);
	if (dlg.DoModal() == IDOK)
	{
		COLORREF color = dlg.GetColor();
		GLfloat m_Red = (GLfloat)GetRValue(color);
		GLfloat m_Green = (GLfloat)GetGValue(color);
		GLfloat m_Blue = (GLfloat)GetBValue(color);

		POSITION pos = GetDocument()->GetFirstViewPosition();
		while (pos != NULL)
		{
			CCadSurfView* view = (CCadSurfView*)GetDocument()->GetNextView(pos);
			view->GetView()->SetBackgroundColor(m_Red / 255, m_Green / 255, m_Blue / 255);
		}
	}
}

void CCadSurfView::DrawRectangle(const bool  Draw,
	const LineStyle aLineStyle)
{
	static int m_DrawMode = R2_MERGEPENNOT;
	static		int StoredMinX, StoredMaxX, StoredMinY, StoredMaxY;
	static		bool m_IsVisible = false;
	static      int  StoredLineStyle = aLineStyle;

	CPen* aOldPen;
	CClientDC clientDC(this);
	if (m_Pen) aOldPen = clientDC.SelectObject(m_Pen);
	clientDC.SetROP2(m_DrawMode);

	if (m_IsVisible) //  erase at the old position 
	{
		clientDC.MoveTo(StoredMinX, StoredMinY); clientDC.LineTo(StoredMinX, StoredMaxY);
		clientDC.LineTo(StoredMaxX, StoredMaxY);
		clientDC.LineTo(StoredMaxX, StoredMinY); clientDC.LineTo(StoredMinX, StoredMinY);
		m_IsVisible = false;
	}

	StoredMinX = min(myXmin, myXmax);    StoredMinY = min(myYmin, myYmax);
	StoredMaxX = max(myXmin, myXmax);    StoredMaxY = max(myYmin, myYmax);

	if (Draw) { // move : draw
		if (StoredLineStyle != aLineStyle) {
			delete m_Pen;
			if (aLineStyle == Solid)
			{
				m_Pen = new CPen(PS_SOLID, 2, RGB(0, 0, 0)); m_DrawMode = R2_MERGEPENNOT;
			}
			else if (aLineStyle == Dot)
			{
				m_Pen = new CPen(PS_DOT, 1, RGB(0, 0, 0));   m_DrawMode = R2_XORPEN;
			}
			else if (aLineStyle == ShortDash)
			{
				m_Pen = new CPen(PS_DASH, 1, RGB(255, 0, 0));	m_DrawMode = R2_XORPEN;
			}
			else if (aLineStyle == LongDash)
			{
				m_Pen = new CPen(PS_DASH, 1, RGB(0, 0, 0));	m_DrawMode = R2_NOTXORPEN;
			}
			clientDC.SelectObject(m_Pen);
		}

		clientDC.SetROP2(m_DrawMode);
		clientDC.MoveTo(StoredMinX, StoredMinY); clientDC.LineTo(StoredMinX, StoredMaxY);
		clientDC.LineTo(StoredMaxX, StoredMaxY);
		clientDC.LineTo(StoredMaxX, StoredMinY); clientDC.LineTo(StoredMinX, StoredMinY);
		m_IsVisible = true;
	}

	if (m_Pen) clientDC.SelectObject(aOldPen);
}

void CCadSurfView::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);

	// TODO: Add your message handler code here
	((CChildFrame*)GetParentFrame())->m_wndSplitter.RefreshSplitBars();
}

void CCadSurfView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	// TODO: Add your message handler code here
	((CChildFrame*)GetParentFrame())->m_wndSplitter.RefreshSplitBars();
}

void CCadSurfView::OnSnapshot()
{
	// TODO: Add your command handler code here
	GetDIB();
	if (hDIB == NULL)
	{
		MessageBox("HDIB handle is NULL, save abort !!!");
		return;
	}
	CFileDialog  dilg(FALSE, NULL, "*.bmp", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||");

	dilg.m_ofn.lpstrTitle = "Save Bitmap Dialog";
	if (dilg.DoModal() != IDOK)
	{
		FreeDIB();
		return;
	}
	CString pszPathName = dilg.GetPathName();

	CFile file;
	CFileException fe;

	if (!file.Open(pszPathName, CFile::modeCreate |
		CFile::modeReadWrite | CFile::shareExclusive, &fe))
	{
		FreeDIB();
		MessageBox("Cannot save the BMP file <" + pszPathName + "> !!!");
		return;
	}

	BOOL bSuccess = FALSE;
	TRY
	{
		BeginWaitCursor();
		bSuccess = ::SaveDIB(hDIB, (HANDLE)file.m_hFile);
		file.Close();
	}
		CATCH(CException, eSave)
	{
		file.Abort(); // will not throw an exception
		EndWaitCursor();
		FreeDIB();
		MessageBox("Cannot save the BMP file <" + pszPathName + "> !!!");
		return;
	}
	END_CATCH
		EndWaitCursor();
	if (!bSuccess)
	{
		FreeDIB();
		MessageBox("Cannot save the BMP file <" + pszPathName + "> !!!");
	}

	FreeDIB();
}

void CCadSurfView::OnFilePrint()
{
	// TODO: Add your command handler code here
	m_nSaveBMPFlag = BMPCLIENT;
	GetDIB();

	CView::OnFilePrint();
}

void CCadSurfView::OnFilePrintPreview()
{
	// TODO: Add your command handler code here
	m_nSaveBMPFlag = BMPCLIENT;
	GetDIB();

	CView::OnFilePrintPreview();
}

void CCadSurfView::GetDIB()
{
	if (hDIB != NULL)
	{
		::GlobalUnlock(hDIB);
		::GlobalFree(hDIB);
		hDIB = NULL;
	}

	m_nSaveBMPFlag = BMPCLIENT;
	hDIB = ::CopyWindowToDIB(GetSafeHwnd(), m_nSaveBMPFlag);
}

void CCadSurfView::FreeDIB()
{
	::GlobalUnlock(hDIB);
	::GlobalFree(hDIB);
	hDIB = NULL;
}


void CCadSurfView::PrintDIB(CDC* pDC)
{
	if (hDIB == NULL || m_palDIB == NULL) return;

	int cxPage = pDC->GetDeviceCaps(HORZRES);
	int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
	int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);

	char* pDIB = (char*)::GlobalLock(hDIB);
	int cxDIB = (int)  ::DIBWidth(pDIB);
	int cyDIB = (int)  ::DIBHeight(pDIB);
	if (cxDIB <= 0 || cyDIB <= 0) return;

	RECT rcDst, rcDIB;
	rcDIB.top = 0;
	rcDIB.left = 0;
	rcDIB.right = cxDIB;
	rcDIB.bottom = cyDIB;
	rcDst.left = 0;
	rcDst.top = 0;
	rcDst.right = cxPage;
	rcDst.bottom = (int)(1.0 * cyDIB * cxPage * cyInch / cxDIB / cxInch);

	::PaintDIB(pDC->m_hDC, &rcDst, (HDIB)hDIB, &rcDIB, (HPALETTE)m_palDIB->m_hObject);
}


void CCadSurfView::OnProjectionType()
{
	// TODO: Add your command handler code here
	POSITION pos = GetDocument()->GetFirstViewPosition();
	while (pos != NULL)
	{
		CCadSurfView* view = (CCadSurfView*)GetDocument()->GetNextView(pos);
		CGLView::GLProjectionType aType = view->GetView()->GetProjectionType();
		view->GetView()->SetProjectionType((aType == CGLView::GLORTHOGRAPHIC) ? CGLView::GLPERSPECTIVE : CGLView::GLORTHOGRAPHIC);
	}
}

void CCadSurfView::OnUpdateProjectionType(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	POSITION pos = GetDocument()->GetFirstViewPosition();
	while (pos != NULL)
	{
		CCadSurfView* view = (CCadSurfView*)GetDocument()->GetNextView(pos);
		CGLView::GLProjectionType aType = view->GetView()->GetProjectionType();
		pCmdUI->SetCheck((aType == CGLView::GLPERSPECTIVE));
	}
}

#include "LightDlg.h"
void CCadSurfView::OnPreferencesLight()
{
	// TODO: 在此添加命令处理程序代码
	CLightDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		GLfloat x, y, z, w, s, e, c;
		x = dlg.m_x; y = dlg.m_y; z = dlg.m_z; w = dlg.m_w; s = dlg.m_s; e = dlg.m_e; c = dlg.m_c;
		CGLDisplayContext* ctx = GetDocument()->dContext;

		for (ctx->InitSelected(); ctx->MoreSelected(); ctx->NextSelected())
		{
			CGLObject* O = ctx->CurrentSelected();
			O->SetMaterial(x, y, z, w, s, e, c);
		}
		InvalidateRect(NULL, FALSE);
		GetDocument()->UpdateAllViews(NULL);

	}
}


void CCadSurfView::OnUpdatePreferencesLight(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CGLDisplayContext* ctx = GetDocument()->dContext;
	pCmdUI->Enable(ctx->HasSelected() && dShaded);
}


//草图打开时，应该许多命令不能执行;此逻辑需要梳理;

void CCadSurfView::OnSkechLine()
{
	//绘制草图直线，交互绘制;
	m_iSketchType = 1;

	//command
	if (m_pCmd) {
		m_pCmd->Cancel();
		delete m_pCmd;
		m_pCmd = NULL;
	}

	m_pCmd = new CCreateLine();
}


void CCadSurfView::OnUpdateSkechLine(CCmdUI* pCmdUI)
{
	//在关闭草图的情况下，此功能关闭;
	pCmdUI->Enable(m_iSketchPlane != 0);
	pCmdUI->SetCheck(m_iSketchType == 1);
}


void CCadSurfView::OnSketchXoy()
{
	//在XOY平面绘制草图;
	m_iSketchPlane = 1;
	OnTopview();
}


void CCadSurfView::OnUpdateSketchXoy(CCmdUI* pCmdUI)
{
	//
	pCmdUI->SetCheck(m_iSketchPlane == 1);
}


void CCadSurfView::OnSketchXoz()
{
	// TODO: 在此添加命令处理程序代码
	m_iSketchPlane = 2;
	OnFrontview();
}


void CCadSurfView::OnUpdateSketchXoz(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码;
	pCmdUI->SetCheck(m_iSketchPlane == 2);
}


void CCadSurfView::OnSketchYoz()
{
	// TODO: 在此添加命令处理程序代码;
	m_iSketchPlane = 3;
	OnLeftview();
}


void CCadSurfView::OnUpdateSketchYoz(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码;
	pCmdUI->SetCheck(m_iSketchPlane == 3);
}

void CCadSurfView::OnSketchClose()
{
	// TODO: 在此添加命令处理程序代码;
	m_iSketchPlane = 0;
	OnResetview();

	if (m_pCmd) {
		m_pCmd->Cancel();
		delete m_pCmd;
		m_pCmd = NULL;
	}
}


void CCadSurfView::OnUpdateSketchClose(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码;
	pCmdUI->SetCheck(m_iSketchPlane == 0);
}


void CCadSurfView::OnSkechCircle()
{
	// TODO: 在此添加命令处理程序代码;
	m_iSketchType = 2;
}


void CCadSurfView::OnUpdateSkechCircle(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码;
	pCmdUI->SetCheck(m_iSketchType == 2);
	pCmdUI->Enable(m_iSketchPlane != 0);
}
