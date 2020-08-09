#include <constantSurfaceTension.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace surfaceTensionModels
	{
		defineTypeNameAndDebug(constant, 0);
		addToRunTimeSelectionTable(surfaceTensionModel, constant, dictionary);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::surfaceTensionModels::constant::constant
(
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	surfaceTensionModel(mesh),
	sigma_("sigma", dimensionSet(1, 0, -2, 0, 0), dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::surfaceTensionModels::constant::~constant()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::surfaceTensionModels::constant::sigma() const
{
	return volScalarField::New(sigma_.name(), mesh_, sigma_);
}


bool tnbLib::surfaceTensionModels::constant::readDict(const dictionary& dict)
{
	// Handle sub-dictionary format as a special case
	if (dict.isDict("sigma"))
	{
		dict.subDict("sigma").lookup("sigma") >> sigma_;
	}
	else
	{
		dict.lookup("sigma") >> sigma_;
	}

	return true;
}


bool tnbLib::surfaceTensionModels::constant::writeData(Ostream& os) const
{
	if (surfaceTensionModel::writeData(os))
	{
		os << sigma_ << token::END_STATEMENT << nl;
		return os.good();
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //