#include <sixDoFRigidBodyMotionConstraint.hxx>

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::sixDoFRigidBodyMotionConstraint>
tnbLib::sixDoFRigidBodyMotionConstraint::New
(
	const word& name,
	const dictionary& sDoFRBMCDict,
	const sixDoFRigidBodyMotion& motion
)
{
	const word constraintType
	(
		sDoFRBMCDict.lookup("sixDoFRigidBodyMotionConstraint")
	);

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(constraintType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown sixDoFRigidBodyMotionConstraint type "
			<< constraintType << nl << nl
			<< "Valid sixDoFRigidBodyMotionConstraints are : " << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<sixDoFRigidBodyMotionConstraint>
		(
			cstrIter()(name, sDoFRBMCDict, motion)
			);
}


// ************************************************************************* //