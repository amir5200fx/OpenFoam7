#include <scalarTransport.hxx>

#include <surfaceFields.hxx>
#include <fvmDdt.hxx>
#include <fvmDiv.hxx>
#include <fvmLaplacian.hxx>
#include <fvmSup.hxx>
#include <turbulentTransportModel.hxx>
#include <turbulentFluidThermoModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(scalarTransport, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			scalarTransport,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::functionObjects::scalarTransport::D
(
	const surfaceScalarField& phi
) const
{
	typedef incompressible::turbulenceModel icoModel;
	typedef compressible::turbulenceModel cmpModel;

	word Dname("D" + s_.name());

	if (constantD_)
	{
		return volScalarField::New
		(
			Dname,
			mesh_,
			dimensionedScalar(Dname, phi.dimensions() / dimLength, D_)
		);
	}
	else if (mesh_.foundObject<icoModel>(turbulenceModel::propertiesName))
	{
		const icoModel& model = mesh_.lookupObject<icoModel>
			(
				turbulenceModel::propertiesName
				);

		return alphaD_ * model.nu() + alphaDt_ * model.nut();
	}
	else if (mesh_.foundObject<cmpModel>(turbulenceModel::propertiesName))
	{
		const cmpModel& model = mesh_.lookupObject<cmpModel>
			(
				turbulenceModel::propertiesName
				);

		return alphaD_ * model.mu() + alphaDt_ * model.mut();
	}
	else
	{
		return volScalarField::New
		(
			Dname,
			mesh_,
			dimensionedScalar(Dname, phi.dimensions() / dimLength, 0)
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::scalarTransport::scalarTransport
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	fieldName_(dict.lookupOrDefault<word>("field", "s")),
	D_(0),
	nCorr_(0),
	fvOptions_(mesh_),
	s_
	(
		IOobject
		(
			fieldName_,
			mesh_.time().timeName(),
			mesh_,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE
		),
		mesh_
	)
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::scalarTransport::~scalarTransport()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::scalarTransport::read(const dictionary& dict)
{
	fvMeshFunctionObject::read(dict);

	phiName_ = dict.lookupOrDefault<word>("phi", "phi");
	rhoName_ = dict.lookupOrDefault<word>("rho", "rho");
	schemesField_ = dict.lookupOrDefault<word>("schemesField", fieldName_);

	constantD_ = dict.readIfPresent("D", D_);
	alphaD_ = dict.lookupOrDefault("alphaD", 1.0);
	alphaDt_ = dict.lookupOrDefault("alphaDt", 1.0);

	dict.readIfPresent("nCorr", nCorr_);

	if (dict.found("fvOptions"))
	{
		fvOptions_.reset(dict.subDict("fvOptions"));
	}

	return true;
}


bool tnbLib::functionObjects::scalarTransport::execute()
{
	Info << type() << " write:" << endl;

	const surfaceScalarField& phi =
		mesh_.lookupObject<surfaceScalarField>(phiName_);

	// Calculate the diffusivity
	volScalarField D(this->D(phi));

	word divScheme("div(phi," + schemesField_ + ")");
	word laplacianScheme("laplacian(" + D.name() + "," + schemesField_ + ")");

	// Set under-relaxation coeff
	scalar relaxCoeff = 0.0;
	if (mesh_.relaxEquation(schemesField_))
	{
		relaxCoeff = mesh_.equationRelaxationFactor(schemesField_);
	}

	if (phi.dimensions() == dimMass / dimTime)
	{
		const volScalarField& rho =
			mesh_.lookupObject<volScalarField>(rhoName_);

		for (label i = 0; i <= nCorr_; i++)
		{
			fvScalarMatrix sEqn
			(
				fvm::ddt(rho, s_)
				+ fvm::div(phi, s_, divScheme)
				- fvm::laplacian(D, s_, laplacianScheme)
				==
				fvOptions_(rho, s_)
			);

			sEqn.relax(relaxCoeff);

			fvOptions_.constrain(sEqn);

			sEqn.solve(schemesField_);
		}
	}
	else if (phi.dimensions() == dimVolume / dimTime)
	{
		for (label i = 0; i <= nCorr_; i++)
		{
			fvScalarMatrix sEqn
			(
				fvm::ddt(s_)
				+ fvm::div(phi, s_, divScheme)
				- fvm::laplacian(D, s_, laplacianScheme)
				==
				fvOptions_(s_)
			);

			sEqn.relax(relaxCoeff);

			fvOptions_.constrain(sEqn);

			sEqn.solve(schemesField_);
		}
	}
	else
	{
		FatalErrorInFunction
			<< "Incompatible dimensions for phi: " << phi.dimensions() << nl
			<< "Dimensions should be " << dimMass / dimTime << " or "
			<< dimVolume / dimTime << exit(FatalError);
	}

	Info << endl;

	return true;
}


bool tnbLib::functionObjects::scalarTransport::write()
{
	return true;
}


// ************************************************************************* //