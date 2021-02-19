#include <tabulatedHeatTransfer.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(tabulatedHeatTransfer, 0);
		addToRunTimeSelectionTable
		(
			option,
			tabulatedHeatTransfer,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

const tnbLib::interpolation2DTable<tnbLib::scalar>&
tnbLib::fv::tabulatedHeatTransfer::hTable()
{
	if (!hTable_.valid())
	{
		hTable_.reset(new interpolation2DTable<scalar>(coeffs_));
	}

	return hTable_();
}


const tnbLib::volScalarField& tnbLib::fv::tabulatedHeatTransfer::AoV()
{
	if (!AoV_.valid())
	{
		AoV_.reset
		(
			new volScalarField
			(
				IOobject
				(
					"AoV",
					startTimeName_,
					mesh_,
					IOobject::MUST_READ,
					IOobject::AUTO_WRITE
				),
				mesh_
			)
		);
	}

	return AoV_();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::tabulatedHeatTransfer::tabulatedHeatTransfer
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	interRegionHeatTransferModel(name, modelType, dict, mesh),
	UName_(coeffs_.lookupOrDefault<word>("U", "U")),
	UNbrName_(coeffs_.lookupOrDefault<word>("UNbr", "U")),
	hTable_(),
	AoV_(),
	startTimeName_(mesh.time().timeName())
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fv::tabulatedHeatTransfer::~tabulatedHeatTransfer()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fv::tabulatedHeatTransfer::calculateHtc()
{
	const fvMesh& nbrMesh = mesh_.time().lookupObject<fvMesh>(nbrRegionName());

	const volVectorField& UNbr =
		nbrMesh.lookupObject<volVectorField>(UNbrName_);

	const scalarField UMagNbr(mag(UNbr));

	const scalarField UMagNbrMapped(interpolate(UMagNbr));

	const volVectorField& U = mesh_.lookupObject<volVectorField>(UName_);

	scalarField& htcc = htc_.primitiveFieldRef();

	forAll(htcc, i)
	{
		htcc[i] = hTable()(mag(U[i]), UMagNbrMapped[i]);
	}

	htcc = htcc * AoV();
}


bool tnbLib::fv::tabulatedHeatTransfer::read(const dictionary& dict)
{
	if (interRegionHeatTransferModel::read(dict))
	{
		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //