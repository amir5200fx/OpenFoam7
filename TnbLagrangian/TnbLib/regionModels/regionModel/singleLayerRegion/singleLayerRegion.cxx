#include <singleLayerRegion.hxx>

#include <fvMesh.hxx>
#include <Time.hxx>
#include <zeroGradientFvPatchFields.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		defineTypeNameAndDebug(singleLayerRegion, 0);
	}
}

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void tnbLib::regionModels::singleLayerRegion::constructMeshObjects()
{
	// construct patch normal vectors
	nHatPtr_.reset
	(
		new volVectorField
		(
			IOobject
			(
				"nHat",
				time_.timeName(),
				regionMesh(),
				IOobject::READ_IF_PRESENT,
				NO_WRITE
			),
			regionMesh(),
			dimensionedVector(dimless, Zero),
			zeroGradientFvPatchField<vector>::typeName
		)
	);

	// construct patch areas
	magSfPtr_.reset
	(
		new volScalarField
		(
			IOobject
			(
				"magSf",
				time_.timeName(),
				regionMesh(),
				IOobject::READ_IF_PRESENT,
				NO_WRITE
			),
			regionMesh(),
			dimensionedScalar(dimArea, 0),
			zeroGradientFvPatchField<scalar>::typeName
		)
	);
}


void tnbLib::regionModels::singleLayerRegion::initialise()
{
	if (debug)
	{
		Pout << "singleLayerRegion::initialise()" << endl;
	}

	label nBoundaryFaces = 0;
	const polyBoundaryMesh& rbm = regionMesh().boundaryMesh();
	volVectorField& nHat = nHatPtr_();
	volScalarField& magSf = magSfPtr_();
	forAll(intCoupledPatchIDs_, i)
	{
		const label patchi = intCoupledPatchIDs_[i];
		const polyPatch& pp = rbm[patchi];
		const labelList& fCells = pp.faceCells();

		nBoundaryFaces += fCells.size();

		UIndirectList<vector>(nHat, fCells) = pp.faceNormals();
		UIndirectList<scalar>(magSf, fCells) = mag(pp.faceAreas());
	}
	nHat.correctBoundaryConditions();
	magSf.correctBoundaryConditions();

	if (nBoundaryFaces != regionMesh().nCells())
	{
		FatalErrorInFunction
			<< "Number of primary region coupled boundary faces not equal to "
			<< "the number of cells in the local region" << nl << nl
			<< "Number of cells = " << regionMesh().nCells() << nl
			<< "Boundary faces  = " << nBoundaryFaces << nl
			<< abort(FatalError);
	}

	scalarField passiveMagSf(magSf.size(), 0.0);
	passivePatchIDs_.setSize(intCoupledPatchIDs_.size(), -1);
	forAll(intCoupledPatchIDs_, i)
	{
		const label patchi = intCoupledPatchIDs_[i];
		const polyPatch& ppIntCoupled = rbm[patchi];
		if (ppIntCoupled.size() > 0)
		{
			label cellId = rbm[patchi].faceCells()[0];
			const cell& cFaces = regionMesh().cells()[cellId];

			label facei = ppIntCoupled.start();
			label faceO = cFaces.opposingFaceLabel(facei, regionMesh().faces());

			label passivePatchi = rbm.whichPatch(faceO);
			passivePatchIDs_[i] = passivePatchi;
			const polyPatch& ppPassive = rbm[passivePatchi];
			UIndirectList<scalar>(passiveMagSf, ppPassive.faceCells()) =
				mag(ppPassive.faceAreas());
		}
	}

	Pstream::listCombineGather(passivePatchIDs_, maxEqOp<label>());
	Pstream::listCombineScatter(passivePatchIDs_);

	magSf.field() = 0.5*(magSf + passiveMagSf);
	magSf.correctBoundaryConditions();
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

bool tnbLib::regionModels::singleLayerRegion::read()
{
	return regionModel::read();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::regionModels::singleLayerRegion::singleLayerRegion
(
	const fvMesh& mesh,
	const word& regionType
)
	:
	regionModel(mesh, regionType),
	nHatPtr_(nullptr),
	magSfPtr_(nullptr),
	passivePatchIDs_()
{}


tnbLib::regionModels::singleLayerRegion::singleLayerRegion
(
	const fvMesh& mesh,
	const word& regionType,
	const word& modelName,
	bool readFields
)
	:
	regionModel(mesh, regionType, modelName, false),
	nHatPtr_(nullptr),
	magSfPtr_(nullptr),
	passivePatchIDs_()
{
	if (active_)
	{
		constructMeshObjects();
		initialise();

		if (readFields)
		{
			read();
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::regionModels::singleLayerRegion::~singleLayerRegion()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

const tnbLib::volVectorField& tnbLib::regionModels::singleLayerRegion::nHat() const
{
	if (!nHatPtr_.valid())
	{
		FatalErrorInFunction
			<< "Region patch normal vectors not available"
			<< abort(FatalError);
	}

	return nHatPtr_();
}


const tnbLib::volScalarField& tnbLib::regionModels::singleLayerRegion::magSf() const
{
	if (!magSfPtr_.valid())
	{
		FatalErrorInFunction
			<< "Region patch areas not available"
			<< abort(FatalError);
	}

	return magSfPtr_();
}


const tnbLib::labelList&
tnbLib::regionModels::singleLayerRegion::passivePatchIDs() const
{
	return passivePatchIDs_;
}


// ************************************************************************* //