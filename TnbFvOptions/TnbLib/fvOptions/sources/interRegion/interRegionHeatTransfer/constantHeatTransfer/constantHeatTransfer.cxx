#include <constantHeatTransfer.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(constantHeatTransfer, 0);
		addToRunTimeSelectionTable
		(
			option,
			constantHeatTransfer,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::constantHeatTransfer::constantHeatTransfer
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	interRegionHeatTransferModel(name, modelType, dict, mesh),
	htcConst_(),
	AoV_()
{
	if (active() && master_)
	{
		htcConst_.reset
		(
			new volScalarField
			(
				IOobject
				(
					"htcConst",
					mesh_.time().timeName(),
					mesh_,
					IOobject::MUST_READ,
					IOobject::AUTO_WRITE
				),
				mesh_
			)
		);

		AoV_.reset
		(
			new volScalarField
			(
				IOobject
				(
					"AoV",
					mesh_.time().timeName(),
					mesh_,
					IOobject::MUST_READ,
					IOobject::AUTO_WRITE
				),
				mesh_
			)
		);

		htc_ = htcConst_()*AoV_();
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fv::constantHeatTransfer::~constantHeatTransfer()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fv::constantHeatTransfer::calculateHtc()
{}


bool tnbLib::fv::constantHeatTransfer::read(const dictionary& dict)
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