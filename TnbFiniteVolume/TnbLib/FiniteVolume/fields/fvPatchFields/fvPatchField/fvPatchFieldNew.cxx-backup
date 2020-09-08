#include <fvPatchField.hxx>

#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::fvPatchField<Type>> tnbLib::fvPatchField<Type>::New
(
	const word& patchFieldType,
	const word& actualPatchType,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
{
	if (debug)
	{
		InfoInFunction
			<< "patchFieldType = " << patchFieldType
			<< " : " << p.type()
			<< endl;
	}

	typename patchConstructorTable::iterator cstrIter =
		patchConstructorTablePtr_->find(patchFieldType);

	if (cstrIter == patchConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown patchField type "
			<< patchFieldType << nl << nl
			<< "Valid patchField types are :" << endl
			<< patchConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	typename patchConstructorTable::iterator patchTypeCstrIter =
		patchConstructorTablePtr_->find(p.type());

	if
		(
			actualPatchType == word::null
			|| actualPatchType != p.type()
			)
	{
		if (patchTypeCstrIter != patchConstructorTablePtr_->end())
		{
			return patchTypeCstrIter()(p, iF);
		}
		else
		{
			return cstrIter()(p, iF);
		}
	}
	else
	{
		tmp<fvPatchField<Type>> tfvp = cstrIter()(p, iF);

		// Check if constraint type override and store patchType if so
		if ((patchTypeCstrIter != patchConstructorTablePtr_->end()))
		{
			tfvp.ref().patchType() = actualPatchType;
		}
		return tfvp;
	}
}


template<class Type>
tnbLib::tmp<tnbLib::fvPatchField<Type>> tnbLib::fvPatchField<Type>::New
(
	const word& patchFieldType,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
{
	return New(patchFieldType, word::null, p, iF);
}


template<class Type>
tnbLib::tmp<tnbLib::fvPatchField<Type>> tnbLib::fvPatchField<Type>::New
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
{
	const word patchFieldType(dict.lookup("type"));

	if (debug)
	{
		InfoInFunction
			<< "patchFieldType = " << patchFieldType
			<< endl;
	}

	typename dictionaryConstructorTable::iterator cstrIter
		= dictionaryConstructorTablePtr_->find(patchFieldType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		if (!disallowGenericFvPatchField)
		{
			cstrIter = dictionaryConstructorTablePtr_->find("generic");
		}

		if (cstrIter == dictionaryConstructorTablePtr_->end())
		{
			FatalIOErrorInFunction
			(
				dict
			) << "Unknown patchField type " << patchFieldType
				<< " for patch type " << p.type() << nl << nl
				<< "Valid patchField types are :" << endl
				<< dictionaryConstructorTablePtr_->sortedToc()
				<< exit(FatalIOError);
		}
	}

	if
		(
			!dict.found("patchType")
			|| word(dict.lookup("patchType")) != p.type()
			)
	{
		typename dictionaryConstructorTable::iterator patchTypeCstrIter
			= dictionaryConstructorTablePtr_->find(p.type());

		if
			(
				patchTypeCstrIter != dictionaryConstructorTablePtr_->end()
				&& patchTypeCstrIter() != cstrIter()
				)
		{
			FatalIOErrorInFunction
			(
				dict
			) << "inconsistent patch and patchField types for \n"
				"    patch type " << p.type()
				<< " and patchField type " << patchFieldType
				<< exit(FatalIOError);
		}
	}

	return cstrIter()(p, iF, dict);
}


template<class Type>
tnbLib::tmp<tnbLib::fvPatchField<Type>> tnbLib::fvPatchField<Type>::New
(
	const fvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& pfMapper
)
{
	if (debug)
	{
		InfoInFunction << "Constructing fvPatchField<Type>" << endl;
	}

	typename patchMapperConstructorTable::iterator cstrIter =
		patchMapperConstructorTablePtr_->find(ptf.type());

	if (cstrIter == patchMapperConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown patchField type " << ptf.type() << nl << nl
			<< "Valid patchField types are :" << endl
			<< patchMapperConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return cstrIter()(ptf, p, iF, pfMapper);
}


// ************************************************************************* //