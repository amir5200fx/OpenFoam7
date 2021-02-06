#include <reactionRateFlameArea.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::reactionRateFlameArea> tnbLib::reactionRateFlameArea::New
(
	const dictionary& dict,
	const fvMesh& mesh,
	const combustionModel& combModel
)
{
	word reactionRateFlameAreaType
	(
		dict.lookup("reactionRateFlameArea")
	);

	Info << "Selecting reaction rate flame area correlation "
		<< reactionRateFlameAreaType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(reactionRateFlameAreaType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalIOErrorInFunction
		(
			dict
		) << "Unknown reactionRateFlameArea type "
			<< reactionRateFlameAreaType << endl << endl
			<< "Valid reaction rate flame area types are :" << endl
			<< dictionaryConstructorTablePtr_->toc()
			<< exit(FatalIOError);
	}

	const label tempOpen = reactionRateFlameAreaType.find('<');

	const word className = reactionRateFlameAreaType(0, tempOpen);

	return autoPtr<reactionRateFlameArea>
		(cstrIter()(className, dict, mesh, combModel));
}


// ************************************************************************* //