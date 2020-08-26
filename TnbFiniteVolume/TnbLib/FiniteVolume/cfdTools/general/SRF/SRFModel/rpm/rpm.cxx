#include <rpm.hxx>

#include <mathematicalConstants.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace SRF
	{
		defineTypeNameAndDebug(rpm, 0);

		addToRunTimeSelectionTable
		(
			SRFModel,
			rpm,
			dictionary
		);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::SRF::rpm::rpm
(
	const volVectorField& U
)
	:
	SRFModel(typeName, U),
	rpm_(readScalar(SRFModelCoeffs_.lookup("rpm")))
{
	// Initialise the angular velocity
	omega_.value() = axis_ * rpm_*constant::mathematical::twoPi / 60.0;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::SRF::rpm::~rpm()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::SRF::rpm::read()
{
	if (SRFModel::read())
	{
		// Re-read rpm
		SRFModelCoeffs_.lookup("rpm") >> rpm_;

		// Update angular velocity
		omega_.value() = axis_ * rpm_*(constant::mathematical::twoPi / 60.0);

		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //