#include <AMIMethod.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::AMIMethod> tnbLib::AMIMethod::New
(
	const word& methodName,
	const primitivePatch& srcPatch,
	const primitivePatch& tgtPatch,
	const scalarField& srcMagSf,
	const scalarField& tgtMagSf,
	const faceAreaIntersect::triangulationMode& triMode,
	const bool reverseTarget,
	const bool requireMatch
)
{
	if (debug)
	{
		Info << "Selecting AMIMethod " << methodName << endl;
	}

	typename componentsConstructorTable::iterator cstrIter =
		componentsConstructorTablePtr_->find(methodName);

	if (cstrIter == componentsConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown AMIMethod type "
			<< methodName << nl << nl
			<< "Valid AMIMethod types are:" << nl
			<< componentsConstructorTablePtr_->sortedToc() << exit(FatalError);
	}

	return autoPtr<AMIMethod>
		(
			cstrIter()
			(
				srcPatch,
				tgtPatch,
				srcMagSf,
				tgtMagSf,
				triMode,
				reverseTarget,
				requireMatch
				)
			);
}


// ************************************************************************* //