#include <blockDescriptor.hxx>  // added by amir

namespace tnbLib
{
	inline point faceCorr(const point& p)
	{
		return p / mag(p);
	}
}

// Edited by amir
//tnbLib::label tnbLib::blockDescriptor::correctFacePoints
//(
//	FixedList<List<point>, 6>& facePoints
//) const
//{
//	forAll(facePoints, facei)
//	{
//		forAll(facePoints[facei], pointi)
//		{
//			facePoints[facei][pointi] = faceCorr(facePoints[facei][pointi]);
//		}
//	}
//
//	return 6;
//}


