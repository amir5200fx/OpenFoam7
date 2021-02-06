#include <combustionModel.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(combustionModel, 0);
}

const tnbLib::word tnbLib::combustionModel::combustionPropertiesName
(
	"combustionProperties"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::IOobject tnbLib::combustionModel::createIOobject
(
	basicThermo& thermo,
	const word& combustionProperties
) const
{
	IOobject io
	(
		thermo.phasePropertyName(combustionProperties),
		thermo.db().time().constant(),
		thermo.db(),
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


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::combustionModel::combustionModel
(
	const word& modelType,
	basicThermo& thermo,
	const compressibleTurbulenceModel& turb,
	const word& combustionProperties
)
	:
	IOdictionary(createIOobject(thermo, combustionProperties)),
	mesh_(thermo.p().mesh()),
	turb_(turb),
	coeffs_(optionalSubDict(modelType + "Coeffs")),
	modelType_(modelType)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::combustionModel::~combustionModel()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::combustionModel::read()
{
	if (regIOobject::read())
	{
		coeffs_ = optionalSubDict(modelType_ + "Coeffs");
		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //