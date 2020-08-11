#include <constLaminarFlameSpeed.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarFlameSpeedModels
	{
		defineTypeNameAndDebug(constant, 0);

		addToRunTimeSelectionTable
		(
			laminarFlameSpeed,
			constant,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::laminarFlameSpeedModels::constant::constant
(
	const dictionary& dict,
	const psiuReactionThermo& ct
)
	:
	laminarFlameSpeed(dict, ct),

	Su_(dict.lookup("Su"))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::laminarFlameSpeedModels::constant::~constant()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::laminarFlameSpeedModels::constant::operator()() const
{
	return volScalarField::New
	(
		"Su0",
		psiuReactionThermo_.T().mesh(),
		Su_
	);
}


// ************************************************************************* //