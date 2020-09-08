#include <interpolation.hxx>

#include <volFields.hxx>
#include <polyMesh.hxx>
#include <calculatedPointPatchFields.hxx>

// * * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::interpolation<Type>::interpolation
(
	const GeometricField<Type, fvPatchField, volMesh>& psi
)
	:
	psi_(psi),
	pMesh_(psi.mesh()),
	pMeshPoints_(pMesh_.points()),
	pMeshFaces_(pMesh_.faces()),
	pMeshFaceCentres_(pMesh_.faceCentres()),
	pMeshFaceAreas_(pMesh_.faceAreas())
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <interpolationNew.cxx>

// ************************************************************************* //