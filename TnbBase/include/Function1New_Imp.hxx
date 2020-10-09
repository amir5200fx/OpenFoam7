#pragma once
//#include <Function1.hxx>
//#include <Constant.hxx>

// #include <Istream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::autoPtr<tnbLib::Function1<Type>> tnbLib::Function1<Type>::New
(
	const word& entryName,
	const dictionary& dict
)
{
	if (dict.isDict(entryName))
	{
		const dictionary& coeffsDict(dict.subDict(entryName));

		const word Function1Type(coeffsDict.lookup("type"));

		typename dictionaryConstructorTable::iterator cstrIter =
			dictionaryConstructorTablePtr_->find(Function1Type);

		if (cstrIter == dictionaryConstructorTablePtr_->end())
		{
			FatalErrorInFunction
				<< "Unknown Function1 type "
				<< Function1Type << " for Function1 "
				<< entryName << nl << nl
				<< "Valid Function1 types are:" << nl
				<< dictionaryConstructorTablePtr_->sortedToc() << nl
				<< exit(FatalError);
		}

		return cstrIter()(entryName, coeffsDict);
	}
	else
	{
		Istream& is(dict.lookup(entryName, false));

		token firstToken(is);
		word Function1Type;

		if (!firstToken.isWord())
		{
			is.putBack(firstToken);
			/*return autoPtr<Function1<Type>>
				(
					new Function1Types::template Constant<Type>(entryName, is)
					);*/
			return Function1Types::createConstant<Type>(entryName, is);  // modified by amir
		}
		else
		{
			Function1Type = firstToken.wordToken();
		}

		typename dictionaryConstructorTable::iterator cstrIter =
			dictionaryConstructorTablePtr_->find(Function1Type);

		if (cstrIter == dictionaryConstructorTablePtr_->end())
		{
			FatalErrorInFunction
				<< "Unknown Function1 type "
				<< Function1Type << " for Function1 "
				<< entryName << nl << nl
				<< "Valid Function1 types are:" << nl
				<< dictionaryConstructorTablePtr_->sortedToc() << nl
				<< exit(FatalError);
		}

		return cstrIter()
			(
				entryName,
				dict.found(entryName + "Coeffs")
				? dict.subDict(entryName + "Coeffs")
				: dict
				);
	}
}


// ************************************************************************* //