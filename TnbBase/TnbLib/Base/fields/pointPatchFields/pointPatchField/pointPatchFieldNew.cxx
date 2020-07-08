#include <pointPatchField.hxx>

#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::autoPtr<tnbLib::pointPatchField<Type>> tnbLib::pointPatchField<Type>::New
(
	const word& patchFieldType,
	const word& actualPatchType,
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF
)
{
	if (debug)
	{
		InfoInFunction << "Constructing pointPatchField<Type>" << endl;
	}

	typename pointPatchConstructorTable::iterator cstrIter =
		pointPatchConstructorTablePtr_->find(patchFieldType);

	if (cstrIter == pointPatchConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown patchFieldType type "
			<< patchFieldType << nl << nl
			<< "Valid patchField types are :" << endl
			<< pointPatchConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	autoPtr<pointPatchField<Type>> pfPtr(cstrIter()(p, iF));

	if
		(
			actualPatchType == word::null
			|| actualPatchType != p.type()
			)
	{
		if (pfPtr().constraintType() != p.constraintType())
		{
			// Use default constraint type
			typename pointPatchConstructorTable::iterator patchTypeCstrIter =
				pointPatchConstructorTablePtr_->find(p.type());

			if (patchTypeCstrIter == pointPatchConstructorTablePtr_->end())
			{
				FatalErrorInFunction
					<< "inconsistent patch and patchField types for \n"
					<< "    patch type " << p.type()
					<< " and patchField type " << patchFieldType
					<< exit(FatalError);
			}

			return patchTypeCstrIter()(p, iF);
		}
	}
	else
	{
		if (pointPatchConstructorTablePtr_->found(p.type()))
		{
			pfPtr().patchType() = actualPatchType;
		}
	}

	return pfPtr;
}


template<class Type>
tnbLib::autoPtr<tnbLib::pointPatchField<Type>> tnbLib::pointPatchField<Type>::New
(
	const word& patchFieldType,
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF
)
{
	return New(patchFieldType, word::null, p, iF);
}


template<class Type>
tnbLib::autoPtr<tnbLib::pointPatchField<Type>> tnbLib::pointPatchField<Type>::New
(
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const dictionary& dict
)
{
	if (debug)
	{
		InfoInFunction << "Constructing pointPatchField<Type>" << endl;
	}

	word patchFieldType(dict.lookup("type"));

	typename dictionaryConstructorTable::iterator cstrIter
		= dictionaryConstructorTablePtr_->find(patchFieldType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		if (!disallowGenericPointPatchField)
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

	// Construct (but not necessarily returned)
	autoPtr<pointPatchField<Type>> pfPtr(cstrIter()(p, iF, dict));

	if
		(
			!dict.found("patchType")
			|| word(dict.lookup("patchType")) != p.type()
			)
	{
		if (pfPtr().constraintType() == p.constraintType())
		{
			// Compatible (constraint-wise) with the patch type
			return pfPtr;
		}
		else
		{
			// Use default constraint type
			typename dictionaryConstructorTable::iterator patchTypeCstrIter
				= dictionaryConstructorTablePtr_->find(p.type());

			if (patchTypeCstrIter == dictionaryConstructorTablePtr_->end())
			{
				FatalIOErrorInFunction
				(
					dict
				) << "inconsistent patch and patchField types for \n"
					<< "    patch type " << p.type()
					<< " and patchField type " << patchFieldType
					<< exit(FatalIOError);
			}

			return patchTypeCstrIter()(p, iF, dict);
		}
	}

	return cstrIter()(p, iF, dict);
}


template<class Type>
tnbLib::autoPtr<tnbLib::pointPatchField<Type>> tnbLib::pointPatchField<Type>::New
(
	const pointPatchField<Type>& ptf,
	const pointPatch& p,
	const DimensionedField<Type, pointMesh>& iF,
	const pointPatchFieldMapper& pfMapper
)
{
	if (debug)
	{
		InfoInFunction << "Constructing pointPatchField<Type>" << endl;
	}

	typename patchMapperConstructorTable::iterator cstrIter =
		patchMapperConstructorTablePtr_->find(ptf.type());

	if (cstrIter == patchMapperConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown patchField type "
			<< ptf.type() << nl << nl
			<< "Valid patchField types are :" << endl
			<< patchMapperConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return cstrIter()(ptf, p, iF, pfMapper);
}


// ************************************************************************* //