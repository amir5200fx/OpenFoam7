#include <radiationModel.hxx>

#include <absorptionEmissionModel.hxx>
#include <scatterModel.hxx>
#include <sootModel.hxx>
#include <fvmSup.hxx>
#include <basicThermo.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(radiationModel, 0);
	defineRunTimeSelectionTable(radiationModel, T);
	defineRunTimeSelectionTable(radiationModel, dictionary);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::IOobject tnbLib::radiationModel::createIOobject(const fvMesh& mesh) const
{
	IOobject io
	(
		"radiationProperties",
		mesh.time().constant(),
		mesh,
		IOobject::MUST_READ,
		IOobject::NO_WRITE
	);

	if (io.typeHeaderOk<IOdictionary>(true))
	{
		io.readOpt() = IOobject::MUST_READ_IF_MODIFIED;
		return io;
	}
	else
	{
		io.readOpt() = IOobject::NO_READ;
		return io;
	}
}


void tnbLib::radiationModel::initialise()
{
	solverFreq_ = max(1, lookupOrDefault<label>("solverFreq", 1));

	absorptionEmission_.reset
	(
		radiationModels::absorptionEmissionModel::New(*this, mesh_).ptr()
	);

	scatter_.reset(radiationModels::scatterModel::New(*this, mesh_).ptr());

	soot_.reset(radiationModels::sootModel::New(*this, mesh_).ptr());
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationModel::radiationModel(const volScalarField& T)
	:
	IOdictionary
	(
		IOobject
		(
			"radiationProperties",
			T.time().constant(),
			T.mesh(),
			IOobject::NO_READ,
			IOobject::NO_WRITE
		)
	),
	mesh_(T.mesh()),
	time_(T.time()),
	T_(T),
	coeffs_(dictionary::null),
	solverFreq_(0),
	firstIter_(true),
	absorptionEmission_(nullptr),
	scatter_(nullptr),
	soot_(nullptr)
{}


tnbLib::radiationModel::radiationModel(const word& type, const volScalarField& T)
	:
	IOdictionary(createIOobject(T.mesh())),
	mesh_(T.mesh()),
	time_(T.time()),
	T_(T),
	coeffs_(subOrEmptyDict(type + "Coeffs")),
	solverFreq_(1),
	firstIter_(true),
	absorptionEmission_(nullptr),
	scatter_(nullptr),
	soot_(nullptr)
{
	initialise();
}


tnbLib::radiationModel::radiationModel
(
	const word& type,
	const dictionary& dict,
	const volScalarField& T
)
	:
	IOdictionary
	(
		IOobject
		(
			"radiationProperties",
			T.time().constant(),
			T.mesh(),
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		dict
	),
	mesh_(T.mesh()),
	time_(T.time()),
	T_(T),
	coeffs_(subOrEmptyDict(type + "Coeffs")),
	solverFreq_(1),
	firstIter_(true),
	absorptionEmission_(nullptr),
	scatter_(nullptr),
	soot_(nullptr)
{
	initialise();
}


// * * * * * * * * * * * * * * * * Destructor    * * * * * * * * * * * * * * //

tnbLib::radiationModel::~radiationModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::radiationModel::correct()
{
	if (firstIter_ || (time_.timeIndex() % solverFreq_ == 0))
	{
		calculate();
		firstIter_ = false;
	}

	if (!soot_.empty())
	{
		soot_->correct();
	}
}


bool tnbLib::radiationModel::read()
{
	if (regIOobject::read())
	{
		coeffs_ = subOrEmptyDict(type() + "Coeffs");

		solverFreq_ = lookupOrDefault<label>("solverFreq", 1);
		solverFreq_ = max(1, solverFreq_);

		return true;
	}
	else
	{
		return false;
	}
}


tnbLib::tmp<tnbLib::fvScalarMatrix> tnbLib::radiationModel::Sh
(
	const basicThermo& thermo,
	const volScalarField& he
) const
{
	const volScalarField Cpv(thermo.Cpv());
	const volScalarField T3(pow3(T_));

	return
		(
			Ru()
			- fvm::Sp(4.0*Rp()*T3 / Cpv, he)
			- Rp()*T3*(T_ - 4.0*he / Cpv)
			);
}


tnbLib::tmp<tnbLib::fvScalarMatrix> tnbLib::radiationModel::ST
(
	const dimensionedScalar& rhoCp,
	volScalarField& T
) const
{
	return
		(
			Ru() / rhoCp
			- fvm::Sp(Rp()*pow3(T) / rhoCp, T)
			);
}


const tnbLib::radiationModels::absorptionEmissionModel&
tnbLib::radiationModel::absorptionEmission() const
{
	if (!absorptionEmission_.valid())
	{
		FatalErrorInFunction
			<< "Requested radiation absorptionEmission model, but model is "
			<< "not active" << abort(FatalError);
	}

	return absorptionEmission_();
}


const tnbLib::radiationModels::sootModel& tnbLib::radiationModel::soot() const
{
	if (!soot_.valid())
	{
		FatalErrorInFunction
			<< "Requested radiation sootModel model, but model is "
			<< "not active" << abort(FatalError);
	}

	return soot_();
}


// ************************************************************************* //