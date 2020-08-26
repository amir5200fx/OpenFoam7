#include <integrationScheme.hxx>

#include <error.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::integrationScheme> tnbLib::integrationScheme::New
(
	const word& phiName,
	const dictionary& dict
)
{
	const word schemeName(dict.lookup(phiName));

	Info << "Selecting " << phiName << " integration scheme "
		<< schemeName << endl;

	typename wordConstructorTable::iterator cstrIter =
		wordConstructorTablePtr_->find(schemeName);

	if (cstrIter == wordConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown integration scheme type "
			<< schemeName << nl << nl
			<< "Valid integration scheme types are:" << nl
			<< wordConstructorTablePtr_->sortedToc() << nl
			<< exit(FatalError);
	}

	return autoPtr<integrationScheme>(cstrIter()());
}

// ************************************************************************* //