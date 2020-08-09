#include <LESdelta.hxx>

#include <calculatedFvPatchFields.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(LESdelta, 0);
	defineRunTimeSelectionTable(LESdelta, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::LESdelta::LESdelta
(
	const word& name,
	const turbulenceModel& turbulence
)
	:
	turbulenceModel_(turbulence),
	delta_
	(
		IOobject
		(
			name,
			turbulence.mesh().time().timeName(),
			turbulence.mesh(),
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		turbulence.mesh(),
		dimensionedScalar(name, dimLength, small),
		calculatedFvPatchScalarField::typeName
	)
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::LESdelta> tnbLib::LESdelta::New
(
	const word& name,
	const turbulenceModel& turbulence,
	const dictionary& dict
)
{
	const word deltaType(dict.lookup("delta"));

	Info << "Selecting LES delta type " << deltaType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(deltaType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown LESdelta type "
			<< deltaType << nl << nl
			<< "Valid LESdelta types are :" << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<LESdelta>(cstrIter()(name, turbulence, dict));
}


tnbLib::autoPtr<tnbLib::LESdelta> tnbLib::LESdelta::New
(
	const word& name,
	const turbulenceModel& turbulence,
	const dictionary& dict,
	const dictionaryConstructorTable& additionalConstructors
)
{
	const word deltaType(dict.lookup("delta"));

	Info << "Selecting LES delta type " << deltaType << endl;

	// First on additional ones
	dictionaryConstructorTable::const_iterator cstrIter =
		additionalConstructors.find(deltaType);

	if (cstrIter != additionalConstructors.end())
	{
		return autoPtr<LESdelta>(cstrIter()(name, turbulence, dict));
	}
	else
	{
		dictionaryConstructorTable::const_iterator cstrIter =
			dictionaryConstructorTablePtr_->find(deltaType);

		if (cstrIter == dictionaryConstructorTablePtr_->end())
		{
			FatalErrorInFunction
				<< "Unknown LESdelta type "
				<< deltaType << nl << nl
				<< "Valid LESdelta types are :" << endl
				<< additionalConstructors.sortedToc()
				<< " and "
				<< dictionaryConstructorTablePtr_->sortedToc()
				<< exit(FatalError);
			return autoPtr<LESdelta>();
		}
		else
		{
			return autoPtr<LESdelta>(cstrIter()(name, turbulence, dict));
		}
	}
}


// ************************************************************************* //