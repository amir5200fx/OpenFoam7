#include <motionSmootherData.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::motionSmootherData::motionSmootherData
(
	const pointMesh& pMesh
)
	:
	displacement_
	(
		tnbLib::IOobject
		(
			"displacement",
			pMesh.time().timeName(),
			pMesh(),
			tnbLib::IOobject::MUST_READ,
			tnbLib::IOobject::AUTO_WRITE
		),
		pMesh
	),
	scale_
	(
		tnbLib::IOobject
		(
			"scale",
			pMesh.time().timeName(),
			pMesh(),
			tnbLib::IOobject::NO_READ,
			tnbLib::IOobject::AUTO_WRITE
		),
		pMesh,
		dimensionedScalar(dimless, 1.0)
	),
	oldPoints_(pMesh().points())
{}


tnbLib::motionSmootherData::motionSmootherData
(
	const pointVectorField& displacement
)
	:
	displacement_
	(
		tnbLib::IOobject
		(
			"displacement",
			displacement.time().timeName(),
			displacement.mesh()(),
			tnbLib::IOobject::NO_READ,
			tnbLib::IOobject::AUTO_WRITE
		),
		displacement
	),
	scale_
	(
		tnbLib::IOobject
		(
			"scale",
			displacement.time().timeName(),
			displacement.mesh()(),
			tnbLib::IOobject::NO_READ,
			tnbLib::IOobject::AUTO_WRITE
		),
		displacement.mesh(),
		dimensionedScalar(dimless, 1.0)
	),
	oldPoints_(displacement.mesh()().points())
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::pointVectorField& tnbLib::motionSmootherData::displacement()
{
	return displacement_;
}


const tnbLib::pointVectorField& tnbLib::motionSmootherData::displacement() const
{
	return displacement_;
}


const tnbLib::pointScalarField& tnbLib::motionSmootherData::scale() const
{
	return scale_;
}


const tnbLib::pointField& tnbLib::motionSmootherData::oldPoints() const
{
	return oldPoints_;
}


// ************************************************************************* //