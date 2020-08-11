#include <solidProperties.hxx>

#include <Switch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::solidProperties> tnbLib::solidProperties::New
(
	const word& name
)
{
	if (debug)
	{
		InfoInFunction << "Constructing solidProperties" << endl;
	}

	ConstructorTable::iterator cstrIter = ConstructorTablePtr_->find(name);

	if (cstrIter == ConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown solidProperties type "
			<< name << nl << nl
			<< "Valid solidProperties types are:" << nl
			<< ConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<solidProperties>(cstrIter()());
}


tnbLib::autoPtr<tnbLib::solidProperties> tnbLib::solidProperties::New
(
	const dictionary& dict
)
{
	if (debug)
	{
		InfoInFunction << "Constructing solid" << endl;
	}

	const word solidType(dict.dictName());

	if (dict.found("defaultCoeffs"))
	{
		// Backward-compatibility

		if (Switch(dict.lookup("defaultCoeffs")))
		{
			return New(solidType);
		}
		else
		{
			return autoPtr<solidProperties>
				(
					new solidProperties(dict.optionalSubDict(solidType + "Coeffs"))
					);
		}
	}
	else
	{
		dictionaryConstructorTable::iterator cstrIter =
			dictionaryConstructorTablePtr_->find(solidType);

		if (cstrIter == dictionaryConstructorTablePtr_->end())
		{
			FatalErrorInFunction
				<< "Unknown solidProperties type "
				<< solidType << nl << nl
				<< "Valid solidProperties types are:" << nl
				<< dictionaryConstructorTablePtr_->sortedToc()
				<< exit(FatalError);
		}

		return autoPtr<solidProperties>(cstrIter()(dict));
	}
}


// ************************************************************************* //