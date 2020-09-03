#pragma once
#include <ISstream.hxx> // added by amir
#include <fileOperation.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Function1Types::TableFile<Type>::TableFile
(
	const word& entryName,
	const dictionary& dict
)
	:
	TableBase<Type>(entryName, dict),
	fName_("none")
{
	dict.lookup("file") >> fName_;

	fileName expandedFile(fName_);
	// IFstream is(expandedFile.expand());
	autoPtr<ISstream> isPtr(fileHandler().NewIFstream(expandedFile.expand()));
	ISstream& is = isPtr();

	if (!is.good())
	{
		FatalIOErrorInFunction
		(
			is
		) << "Cannot open file." << exit(FatalIOError);
	}

	is >> this->table_;

	TableBase<Type>::check();
}


template<class Type>
tnbLib::Function1Types::TableFile<Type>::TableFile(const TableFile<Type>& tbl)
	:
	TableBase<Type>(tbl),
	fName_(tbl.fName_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Function1Types::TableFile<Type>::~TableFile()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::Function1Types::TableFile<Type>::writeData(Ostream& os) const
{
	Function1<Type>::writeData(os);

	os << token::END_STATEMENT << nl
		<< indent << word(this->name() + "Coeffs") << nl
		<< indent << token::BEGIN_BLOCK << nl << incrIndent;

	// Note: for TableBase write the dictionary entries it needs but not
	// the values themselves
	TableBase<Type>::writeEntries(os);

	writeEntry(os, "file", fName_);
	os << decrIndent << indent << token::END_BLOCK << endl;
}


// ************************************************************************* //