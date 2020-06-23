#include <polyPatch.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::polyPatch> tnbLib::polyPatch::New
(
	const word& patchType,
	const word& name,
	const label size,
	const label start,
	const label index,
	const polyBoundaryMesh& bm
)
{
	if (debug)
	{
		InfoInFunction << "Constructing polyPatch" << endl;
	}

	wordConstructorTable::iterator cstrIter =
		wordConstructorTablePtr_->find(patchType);

	if (cstrIter == wordConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown polyPatch type "
			<< patchType << " for patch " << name << nl << nl
			<< "Valid polyPatch types are :" << endl
			<< wordConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<polyPatch>
		(
			cstrIter()
			(
				name,
				size,
				start,
				index,
				bm,
				patchType
				)
			);
}


tnbLib::autoPtr<tnbLib::polyPatch> tnbLib::polyPatch::New
(
	const word& name,
	const dictionary& dict,
	const label index,
	const polyBoundaryMesh& bm
)
{
	if (debug)
	{
		InfoInFunction << "Constructing polyPatch" << endl;
	}

	word patchType(dict.lookup("type"));
	dict.readIfPresent("geometricType", patchType);

	return polyPatch::New(patchType, name, dict, index, bm);
}


tnbLib::autoPtr<tnbLib::polyPatch> tnbLib::polyPatch::New
(
	const word& patchType,
	const word& name,
	const dictionary& dict,
	const label index,
	const polyBoundaryMesh& bm
)
{
	if (debug)
	{
		InfoInFunction << "Constructing polyPatch" << endl;
	}

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(patchType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		if (!disallowGenericPolyPatch)
		{
			cstrIter = dictionaryConstructorTablePtr_->find("genericPatch");
		}

		if (cstrIter == dictionaryConstructorTablePtr_->end())
		{
			FatalIOErrorInFunction
			(
				dict
			) << "Unknown polyPatch type "
				<< patchType << " for patch " << name << nl << nl
				<< "Valid polyPatch types are :" << endl
				<< dictionaryConstructorTablePtr_->sortedToc()
				<< exit(FatalIOError);
		}
	}

	return autoPtr<polyPatch>(cstrIter()(name, dict, index, bm, patchType));
}


// ************************************************************************* //