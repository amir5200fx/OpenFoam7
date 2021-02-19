#include <variableHeatTransfer.hxx>

#include <turbulentFluidThermoModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(variableHeatTransfer, 0);
		addToRunTimeSelectionTable
		(
			option,
			variableHeatTransfer,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::variableHeatTransfer::variableHeatTransfer
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	interRegionHeatTransferModel(name, modelType, dict, mesh),
	UNbrName_(coeffs_.lookupOrDefault<word>("UNbr", "U")),
	a_(0),
	b_(0),
	c_(0),
	ds_(0),
	Pr_(0),
	AoV_()
{
	if (master_)
	{
		a_ = readScalar(coeffs_.lookup("a"));
		b_ = readScalar(coeffs_.lookup("b"));
		c_ = readScalar(coeffs_.lookup("c"));
		ds_ = readScalar(coeffs_.lookup("ds"));
		Pr_ = readScalar(coeffs_.lookup("Pr"));
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
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fv::variableHeatTransfer::~variableHeatTransfer()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fv::variableHeatTransfer::calculateHtc()
{
	const fvMesh& nbrMesh =
		mesh_.time().lookupObject<fvMesh>(nbrRegionName());

	const compressible::turbulenceModel& nbrTurb =
		nbrMesh.lookupObject<compressible::turbulenceModel>
		(
			turbulenceModel::propertiesName
			);

	const fluidThermo& nbrThermo =
		nbrMesh.lookupObject<fluidThermo>(basicThermo::dictName);

	const volVectorField& UNbr =
		nbrMesh.lookupObject<volVectorField>(UNbrName_);

	const volScalarField ReNbr(mag(UNbr)*ds_*nbrThermo.rho() / nbrTurb.mut());

	const volScalarField NuNbr(a_*pow(ReNbr, b_)*pow(Pr_, c_));

	const scalarField htcNbr(NuNbr*nbrTurb.kappaEff() / ds_);

	const scalarField htcNbrMapped(interpolate(htcNbr));

	htc_.primitiveFieldRef() = htcNbrMapped * AoV_;
}


bool tnbLib::fv::variableHeatTransfer::read(const dictionary& dict)
{
	if (interRegionHeatTransferModel::read(dict))
	{
		coeffs_.readIfPresent("UNbr", UNbrName_);

		coeffs_.readIfPresent("a", a_);
		coeffs_.readIfPresent("b", b_);
		coeffs_.readIfPresent("c", c_);
		coeffs_.readIfPresent("ds", ds_);
		coeffs_.readIfPresent("Pr", Pr_);

		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //