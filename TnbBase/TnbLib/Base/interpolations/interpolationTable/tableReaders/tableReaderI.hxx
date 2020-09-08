#pragma once
// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class Type>
tnbLib::autoPtr<tnbLib::tableReader<Type>> tnbLib::tableReader<Type>::New
(
	const dictionary& spec
)
{
	const word readerType = spec.lookupOrDefault<word>
		(
			"readerType",
			"openFoam"
			);

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_
		->find(readerType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown reader type " << readerType
			<< nl << nl
			<< "Valid reader types : " << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<tableReader<Type>>(cstrIter()(spec));
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::tableReader<Type>::tableReader(const dictionary&)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::tableReader<Type>::~tableReader()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::tableReader<Type>::write(Ostream& os) const
{
	if (this->type() != "openFoam")
	{
		writeEntry(os, "readerType", this->type());
	}
}


// ************************************************************************* //