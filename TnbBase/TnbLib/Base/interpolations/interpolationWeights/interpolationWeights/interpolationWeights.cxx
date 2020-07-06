#include <interpolationWeights.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineTypeNameAndDebug(interpolationWeights, 0);
	defineRunTimeSelectionTable(interpolationWeights, word);


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	interpolationWeights::interpolationWeights
	(
		const scalarField& samples
	)
		:
		samples_(samples)
	{}


	// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

	autoPtr<interpolationWeights> interpolationWeights::New
	(
		const word& type,
		const scalarField& samples
	)
	{
		if (debug)
		{
			InfoInFunction
				<< "Selecting interpolationWeights "
				<< type << endl;
		}

		wordConstructorTable::iterator cstrIter =
			wordConstructorTablePtr_->find(type);

		if (cstrIter == wordConstructorTablePtr_->end())
		{
			FatalErrorInFunction
				<< "Unknown interpolationWeights type "
				<< type
				<< endl << endl
				<< "Valid interpolationWeights types are :" << endl
				<< wordConstructorTablePtr_->sortedToc()
				<< exit(FatalError);
		}

		return autoPtr<interpolationWeights>(cstrIter()(samples));
	}


	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	interpolationWeights::~interpolationWeights()
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //