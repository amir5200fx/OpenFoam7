#include <dynamicFvMesh.hxx>

#include <staticFvMesh.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::dynamicFvMesh> tnbLib::dynamicFvMesh::New(const IOobject& io)
{
	IOobject dictHeader(dynamicMeshDictIOobject(io));

	if (dictHeader.typeHeaderOk<IOdictionary>(true))
	{
		IOdictionary dict(dictHeader);

		const word dynamicFvMeshTypeName(dict.lookup("dynamicFvMesh"));

		Info << "Selecting dynamicFvMesh " << dynamicFvMeshTypeName << endl;

		const_cast<Time&>(io.time()).libs().open
		(
			dict,
			"dynamicFvMeshLibs",
			IOobjectConstructorTablePtr_
		);

		if (!IOobjectConstructorTablePtr_)
		{
			FatalErrorInFunction
				<< "dynamicFvMesh table is empty"
				<< exit(FatalError);
		}

		IOobjectConstructorTable::iterator cstrIter =
			IOobjectConstructorTablePtr_->find(dynamicFvMeshTypeName);

		if (cstrIter == IOobjectConstructorTablePtr_->end())
		{
			FatalErrorInFunction
				<< "Unknown dynamicFvMesh type "
				<< dynamicFvMeshTypeName << nl << nl
				<< "Valid dynamicFvMesh types are :" << endl
				<< IOobjectConstructorTablePtr_->sortedToc()
				<< exit(FatalError);
		}

		return autoPtr<dynamicFvMesh>(cstrIter()(io));
	}
	else
	{
		return autoPtr<dynamicFvMesh>(new staticFvMesh(io));
	}
}


// ************************************************************************* //