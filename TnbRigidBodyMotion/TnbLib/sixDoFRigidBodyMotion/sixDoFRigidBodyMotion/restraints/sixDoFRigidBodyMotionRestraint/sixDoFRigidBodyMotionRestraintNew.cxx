#include <sixDoFRigidBodyMotionRestraint.hxx>

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::sixDoFRigidBodyMotionRestraint>
tnbLib::sixDoFRigidBodyMotionRestraint::New
(
	const word& name,
	const dictionary& sDoFRBMRDict
)
{
	const word restraintType
	(
		sDoFRBMRDict.lookup("sixDoFRigidBodyMotionRestraint")
	);

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(restraintType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown sixDoFRigidBodyMotionRestraint type "
			<< restraintType << nl << nl
			<< "Valid sixDoFRigidBodyMotionRestraint types are : " << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<sixDoFRigidBodyMotionRestraint>
		(
			cstrIter()(name, sDoFRBMRDict)
			);
}


// ************************************************************************* //