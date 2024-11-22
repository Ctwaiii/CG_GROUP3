#include "stdafx.h"
#include "BSplineCurveManager.h"

BSplineCurveManager::BSplineCurveManager()
{
}

BSplineCurveManager::BSplineCurveManager(const std::vector<CPoint3D>& vec)
{
	vec_CPoint3D = vec;
}

void BSplineCurveManager::Display(CGLDisplayContext* dContext)
{
	if (!dContext)
		return;
	
	dContext->DeleteAll();

	clear();
	CListOfCPoint3D* myCPList = new CListOfCPoint3D;

	for (int ii = 0; ii < vec_CPoint3D.size(); ++ii) {
		const CPoint3D& pt = vec_CPoint3D[ii];
		myCPList->Append(pt);

		CGLPoint* gP = new CGLPoint(pt);
		mm_glpoint[gP->GetObjID()] = { gP, ii };
		dContext->Display(gP);

		CString str;
		str.Format("P%d(%0.3lf,%0.3lf,%0.3lf)", ii, pt.GetX(), pt.GetY(), pt.GetZ());
		CGLFont* myFont = new CGLFont((LPCTSTR)str, pt);
		mm_glfont[myFont->GetObjID()] = { myFont,ii };
		dContext->Display(myFont);
	}

	CBezierCurve B(myCPList);
	gCRV = new CGLCurve(&B);
	dContext->Display(gCRV);

	if (enable_stretch_face) {
		double s = 0.0;
		double e = (double)stretch_len;
		CExtrudedSurface E(&B, stretch_dir, s, e);
		stretch_face = new CGLSurface(&E);
		dContext->Display(stretch_face);
	}

	delete myCPList;
}

void BSplineCurveManager::clear()
{
	if (gCRV) {
		delete gCRV;
		gCRV = nullptr;
	}
	if (stretch_face) {
		delete stretch_face;
		stretch_face = nullptr;
	}
	for (auto& p : mm_glpoint)
	{
		delete p.second.first;
	}
	mm_glpoint.clear();
	for (auto& p : mm_glfont)
	{
		delete p.second.first;
	}
	mm_glfont.clear();
}
