#include "ListOfCPoint3D.h"
#include "GLDisplayContext.h"
#include "GLPoint.h"
#include "GLFont.h"
#include "GLCurve.h"
#include "GLSurface.h"
#include <map>
#include <vector>

class BSplineCurveManager
{
public:
	BSplineCurveManager();
	BSplineCurveManager(const std::vector<CPoint3D>& vec);
	void Display(CGLDisplayContext* dContext);
	void clear();

	std::map<unsigned long int, std::pair<CGLPoint*, int>> mm_glpoint;
	std::map<unsigned long int, std::pair<CGLFont*, int>> mm_glfont;
	CGLCurve* gCRV = nullptr;
	
	std::vector<CPoint3D> vec_CPoint3D;

	bool enable_stretch_face = false;
	CVector3D stretch_dir = CVector3D(0, 0,1);
	unsigned long int stretch_len = 200;
	CGLSurface* stretch_face = nullptr;
};