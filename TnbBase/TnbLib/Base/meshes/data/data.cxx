#include <data.hxx>

#include <Time.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

int tnbLib::data::debug(tnbLib::debug::debugSwitch("data", false));

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::data::data(const objectRegistry& obr)
	:
	IOdictionary
	(
		IOobject
		(
			"data",
			obr.time().system(),
			obr,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		)
	)
{}


// ************************************************************************* //