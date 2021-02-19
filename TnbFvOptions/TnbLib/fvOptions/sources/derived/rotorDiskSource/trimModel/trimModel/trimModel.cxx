#include <trimModel.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(trimModel, 0);
	defineRunTimeSelectionTable(trimModel, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::trimModel::trimModel
(
	const fv::rotorDiskSource& rotor,
	const dictionary& dict,
	const word& name
)
	:
	rotor_(rotor),
	name_(name),
	coeffs_(dictionary::null)
{
	read(dict);
}

// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

tnbLib::trimModel::~trimModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::trimModel::read(const dictionary& dict)
{
	coeffs_ = dict.optionalSubDict(name_ + "Coeffs");
}


// ************************************************************************* //