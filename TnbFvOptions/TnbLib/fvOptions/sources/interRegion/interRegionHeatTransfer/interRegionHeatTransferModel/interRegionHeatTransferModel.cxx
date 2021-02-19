#include <interRegionHeatTransferModel.hxx>

#include <basicThermo.hxx>
#include <fvmSup.hxx>
#include <zeroGradientFvPatchFields.hxx>
#include <fvcVolumeIntegrate.hxx>
#include <fvOptionList.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(interRegionHeatTransferModel, 0);
	}
}


// * * * * * * * * * * * *  Protected member functions * * * * * * * * * * * //

void tnbLib::fv::interRegionHeatTransferModel::setNbrModel()
{
	if (!firstIter_)
	{
		return;
	}

	const fvMesh& nbrMesh = mesh_.time().lookupObject<fvMesh>(nbrRegionName_);

	const optionList& fvOptions = nbrMesh.lookupObject<optionList>("fvOptions");

	bool nbrModelFound = false;

	forAll(fvOptions, i)
	{
		if (fvOptions[i].name() == nbrModelName_)
		{
			nbrModel_ = &const_cast<interRegionHeatTransferModel&>
				(
					refCast<const interRegionHeatTransferModel>(fvOptions[i])
					);
			nbrModelFound = true;
			break;
		}
	}

	if (!nbrModelFound)
	{
		FatalErrorInFunction
			<< "Neighbour model not found" << nbrModelName_
			<< " in region " << nbrMesh.name() << nl
			<< exit(FatalError);
	}

	firstIter_ = false;

	// Set nbr model's nbr model to avoid construction order problems
	nbrModel_->setNbrModel();
}


void tnbLib::fv::interRegionHeatTransferModel::correct()
{
	if (master_)
	{
		if (mesh_.time().timeIndex() != timeIndex_)
		{
			calculateHtc();
			timeIndex_ = mesh_.time().timeIndex();
		}
	}
	else
	{
		nbrModel().correct();
		interpolate(nbrModel().htc(), htc_);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::interRegionHeatTransferModel::interRegionHeatTransferModel
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	interRegionOption
	(
		name,
		modelType,
		dict,
		mesh
	),
	nbrModelName_(coeffs_.lookup("nbrModel")),
	nbrModel_(nullptr),
	firstIter_(true),
	timeIndex_(-1),
	htc_
	(
		IOobject
		(
			type() + ":htc",
			mesh.time().timeName(),
			mesh,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh,
		dimensionedScalar
		(
			dimEnergy / dimTime / dimTemperature / dimVolume,
			0
		),
		zeroGradientFvPatchScalarField::typeName
	),
	semiImplicit_(false),
	TName_(coeffs_.lookupOrDefault<word>("T", "T")),
	TNbrName_(coeffs_.lookupOrDefault<word>("TNbr", "T"))
{
	if (active())
	{
		coeffs_.lookup("fields") >> fieldNames_;
		applied_.setSize(fieldNames_.size(), false);

		coeffs_.lookup("semiImplicit") >> semiImplicit_;
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fv::interRegionHeatTransferModel::~interRegionHeatTransferModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fv::interRegionHeatTransferModel::addSup
(
	fvMatrix<scalar>& eqn,
	const label fieldi
)
{
	setNbrModel();

	correct();

	const volScalarField& he = eqn.psi();

	const volScalarField& T = mesh_.lookupObject<volScalarField>(TName_);

	tmp<volScalarField> tTmapped
	(
		volScalarField::New(type() + ":Tmapped", T)
	);

	volScalarField& Tmapped = tTmapped.ref();

	const fvMesh& nbrMesh = mesh_.time().lookupObject<fvMesh>(nbrRegionName_);

	const volScalarField& Tnbr =
		nbrMesh.lookupObject<volScalarField>(TNbrName_);

	interpolate(Tnbr, Tmapped.primitiveFieldRef());

	if (debug)
	{
		Info << "Volumetric integral of htc: "
			<< fvc::domainIntegrate(htc_).value()
			<< endl;

		if (mesh_.time().writeTime())
		{
			Tmapped.write();
			htc_.write();
		}
	}

	if (semiImplicit_)
	{
		if (he.dimensions() == dimEnergy / dimMass)
		{
			if (mesh_.foundObject<basicThermo>(basicThermo::dictName))
			{
				const basicThermo& thermo =
					mesh_.lookupObject<basicThermo>(basicThermo::dictName);

				volScalarField htcByCpv(htc_ / thermo.Cpv());

				eqn += htc_ * (Tmapped - T) + htcByCpv * he - fvm::Sp(htcByCpv, he);

				if (debug)
				{
					const dimensionedScalar energy =
						fvc::domainIntegrate(htc_*(he / thermo.Cp() - Tmapped));

					Info << "Energy exchange from region " << nbrMesh.name()
						<< " To " << mesh_.name() << " : " << energy.value()
						<< endl;
				}
			}
			else
			{
				FatalErrorInFunction
					<< " on mesh " << mesh_.name()
					<< " could not find object basicThermo."
					<< " The available objects are: "
					<< mesh_.names()
					<< exit(FatalError);
			}
		}
		else if (he.dimensions() == dimTemperature)
		{
			eqn += htc_ * Tmapped - fvm::Sp(htc_, he);
		}
	}
	else
	{
		eqn += htc_ * (Tmapped - T);
	}
}


void tnbLib::fv::interRegionHeatTransferModel::addSup
(
	const volScalarField& rho,
	fvMatrix<scalar>& eqn,
	const label fieldi
)
{
	addSup(eqn, fieldi);
}


// ************************************************************************* //