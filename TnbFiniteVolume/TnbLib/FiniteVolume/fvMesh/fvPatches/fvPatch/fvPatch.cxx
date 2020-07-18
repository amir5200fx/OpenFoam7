#include <fvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvBoundaryMesh.hxx>
#include <fvMesh.hxx>
#include <primitiveMesh.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(fvPatch, 0);
	defineRunTimeSelectionTable(fvPatch, polyPatch);
	addToRunTimeSelectionTable(fvPatch, fvPatch, polyPatch);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fvPatch::fvPatch(const polyPatch& p, const fvBoundaryMesh& bm)
	:
	polyPatch_(p),
	boundaryMesh_(bm)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fvPatch::~fvPatch()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::fvPatch::constraintType(const word& pt)
{
	return fvPatchField<scalar>::patchConstructorTablePtr_->found(pt);
}


tnbLib::wordList tnbLib::fvPatch::constraintTypes()
{
	wordList cTypes(polyPatchConstructorTablePtr_->size());

	label i = 0;

	for
		(
			polyPatchConstructorTable::iterator cstrIter =
			polyPatchConstructorTablePtr_->begin();
			cstrIter != polyPatchConstructorTablePtr_->end();
			++cstrIter
			)
	{
		if (constraintType(cstrIter.key()))
		{
			cTypes[i++] = cstrIter.key();
		}
	}

	cTypes.setSize(i);

	return cTypes;
}


const tnbLib::labelUList& tnbLib::fvPatch::faceCells() const
{
	return polyPatch_.faceCells();
}


const tnbLib::vectorField& tnbLib::fvPatch::Cf() const
{
	return boundaryMesh().mesh().Cf().boundaryField()[index()];
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::fvPatch::Cn() const
{
	tmp<vectorField> tcc(new vectorField(size()));
	vectorField& cc = tcc.ref();

	const labelUList& faceCells = this->faceCells();

	// get reference to global cell centres
	const vectorField& gcc = boundaryMesh().mesh().cellCentres();

	forAll(faceCells, facei)
	{
		cc[facei] = gcc[faceCells[facei]];
	}

	return tcc;
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::fvPatch::nf() const
{
	return Sf() / magSf();
}


const tnbLib::vectorField& tnbLib::fvPatch::Sf() const
{
	return boundaryMesh().mesh().Sf().boundaryField()[index()];
}


const tnbLib::scalarField& tnbLib::fvPatch::magSf() const
{
	return boundaryMesh().mesh().magSf().boundaryField()[index()];
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::fvPatch::delta() const
{
	// Use patch-normal delta for all non-coupled BCs
	const vectorField nHat(nf());
	return nHat * (nHat & (Cf() - Cn()));
}


void tnbLib::fvPatch::makeWeights(scalarField& w) const
{
	w = 1.0;
}


void tnbLib::fvPatch::initMovePoints()
{}


void tnbLib::fvPatch::movePoints()
{}


const tnbLib::scalarField& tnbLib::fvPatch::deltaCoeffs() const
{
	return boundaryMesh().mesh().deltaCoeffs().boundaryField()[index()];
}


const tnbLib::scalarField& tnbLib::fvPatch::weights() const
{
	return boundaryMesh().mesh().weights().boundaryField()[index()];
}


// ************************************************************************* //