#include <laminarFlameSpeed.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::laminarFlameSpeed> tnbLib::laminarFlameSpeed::New
(
	const psiuReactionThermo& ct
)
{
	// do not register the dictionary
	IOdictionary propDict
	(
		IOobject
		(
			"combustionProperties",
			ct.T().time().constant(),
			ct.T().db(),
			IOobject::MUST_READ_IF_MODIFIED,
			IOobject::NO_WRITE,
			false
		)
	);

	const word corrType(propDict.lookup("laminarFlameSpeedCorrelation"));

	Info << "Selecting laminar flame speed correlation " << corrType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(corrType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalIOErrorInFunction
		(
			propDict
		) << "Unknown laminarFlameSpeed type "
			<< corrType << nl << nl
			<< "Valid laminarFlameSpeed types are :" << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	return autoPtr<laminarFlameSpeed>(cstrIter()(propDict, ct));
}


// ************************************************************************* //