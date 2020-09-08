#include <interpolation.hxx>

#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::autoPtr<tnbLib::interpolation<Type>> tnbLib::interpolation<Type>::New
(
	const word& interpolationType,
	const GeometricField<Type, fvPatchField, volMesh>& psi
)
{
	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(interpolationType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown interpolation type " << interpolationType
			<< " for field " << psi.name() << nl << nl
			<< "Valid interpolation types : " << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<interpolation<Type>>(cstrIter()(psi));
}


template<class Type>
tnbLib::autoPtr<tnbLib::interpolation<Type>> tnbLib::interpolation<Type>::New
(
	const dictionary& interpolationSchemes,
	const GeometricField<Type, fvPatchField, volMesh>& psi
)
{
	return New(word(interpolationSchemes.lookup(psi.name())), psi);
}


// ************************************************************************* //