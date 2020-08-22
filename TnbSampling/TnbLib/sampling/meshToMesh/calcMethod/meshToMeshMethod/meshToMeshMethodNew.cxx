#include <meshToMeshMethod.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::meshToMeshMethod> tnbLib::meshToMeshMethod::New
(
	const word& methodName,
	const polyMesh& src,
	const polyMesh& tgt
)
{
	if (debug)
	{
		Info << "Selecting AMIMethod " << methodName << endl;
	}

	componentsConstructorTable::iterator cstrIter =
		componentsConstructorTablePtr_->find(methodName);

	if (cstrIter == componentsConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown meshToMesh type "
			<< methodName << nl << nl
			<< "Valid meshToMesh types are:" << nl
			<< componentsConstructorTablePtr_->sortedToc() << exit(FatalError);
	}

	return autoPtr<meshToMeshMethod>(cstrIter()(src, tgt));
}


// ************************************************************************* //