#include <wallDist.hxx>

#include <wallPolyPatch.hxx>

#include <Time.hxx> // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(wallDist, 0);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::wallDist::constructn() const
{
	n_ = volVectorField::New
	(
		"n" & patchTypeName_,
		mesh(),
		dimensionedVector(dimless, Zero),
		patchDistMethod::patchTypes<vector>(mesh(), patchIDs_)
	);

	const fvPatchList& patches = mesh().boundary();

	volVectorField::Boundary& nbf = n_.ref().boundaryFieldRef();

	forAllConstIter(labelHashSet, patchIDs_, iter)
	{
		label patchi = iter.key();
		nbf[patchi] == patches[patchi].nf();
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::wallDist::wallDist(const fvMesh& mesh, const word& patchTypeName)
	:
	MeshObject<fvMesh, tnbLib::UpdateableMeshObject, wallDist>(mesh),
	patchIDs_(mesh.boundaryMesh().findPatchIDs<wallPolyPatch>()),
	patchTypeName_(patchTypeName),
	pdm_
	(
		patchDistMethod::New
		(
			static_cast<const fvSchemes&>(mesh)
			.subDict(patchTypeName_ & "Dist"),
			mesh,
			patchIDs_
		)
	),
	y_
	(
		IOobject
		(
			"y" & patchTypeName_,
			mesh.time().timeName(),
			mesh
		),
		mesh,
		dimensionedScalar("y" & patchTypeName_, dimLength, small),
		patchDistMethod::patchTypes<scalar>(mesh, patchIDs_)
	),
	nRequired_
	(
		static_cast<const fvSchemes&>(mesh).subDict(patchTypeName_ & "Dist")
		.lookupOrDefault<Switch>("nRequired", false)
	),
	n_(volVectorField::null())
{
	if (nRequired_)
	{
		constructn();
	}

	movePoints();
}


tnbLib::wallDist::wallDist
(
	const fvMesh& mesh,
	const labelHashSet& patchIDs,
	const word& patchTypeName
)
	:
	MeshObject<fvMesh, tnbLib::UpdateableMeshObject, wallDist>(mesh),
	patchIDs_(patchIDs),
	patchTypeName_(patchTypeName),
	pdm_
	(
		patchDistMethod::New
		(
			static_cast<const fvSchemes&>(mesh)
			.subDict(patchTypeName_ & "Dist"),
			mesh,
			patchIDs_
		)
	),
	y_
	(
		IOobject
		(
			"y" & patchTypeName_,
			mesh.time().timeName(),
			mesh
		),
		mesh,
		dimensionedScalar("y" & patchTypeName_, dimLength, small),
		patchDistMethod::patchTypes<scalar>(mesh, patchIDs_)
	),
	nRequired_
	(
		static_cast<const fvSchemes&>(mesh).subDict(patchTypeName_ & "Dist")
		.lookupOrDefault<Switch>("nRequired", false)
	),
	n_(volVectorField::null())
{
	if (nRequired_)
	{
		constructn();
	}

	movePoints();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::wallDist::~wallDist()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::volVectorField& tnbLib::wallDist::n() const
{
	if (isNull(n_()))
	{
		WarningInFunction
			<< "n requested but 'nRequired' not specified in the "
			<< (patchTypeName_ & "Dist") << " dictionary" << nl
			<< "    Recalculating y and n fields." << endl;

		nRequired_ = true;
		constructn();
		pdm_->correct(y_, n_.ref());
	}

	return n_();
}


bool tnbLib::wallDist::movePoints()
{
	if (pdm_->movePoints())
	{
		if (nRequired_)
		{
			return pdm_->correct(y_, n_.ref());
		}
		else
		{
			return pdm_->correct(y_);
		}
	}
	else
	{
		return false;
	}
}


void tnbLib::wallDist::updateMesh(const mapPolyMesh& mpm)
{
	pdm_->updateMesh(mpm);
	movePoints();
}


// ************************************************************************* //