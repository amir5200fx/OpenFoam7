#include <solidBodyMotionFunction.hxx>

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::solidBodyMotionFunction> tnbLib::solidBodyMotionFunction::New
(
	const dictionary& SBMFCoeffs,
	const Time& runTime
)
{
	const word motionType(SBMFCoeffs.lookup("solidBodyMotionFunction"));

	Info << "Selecting solid-body motion function " << motionType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(motionType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown solidBodyMotionFunction type "
			<< motionType << nl << nl
			<< "Valid solidBodyMotionFunctions are : " << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<solidBodyMotionFunction>(cstrIter()(SBMFCoeffs, runTime));
}


// ************************************************************************* //