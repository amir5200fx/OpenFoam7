#include <multiMotion.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace solidBodyMotionFunctions
	{
		defineTypeNameAndDebug(multiMotion, 0);
		addToRunTimeSelectionTable
		(
			solidBodyMotionFunction,
			multiMotion,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::solidBodyMotionFunctions::multiMotion::multiMotion
(
	const dictionary& SBMFCoeffs,
	const Time& runTime
)
	:
	solidBodyMotionFunction(SBMFCoeffs, runTime)
{
	read(SBMFCoeffs);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::solidBodyMotionFunctions::multiMotion::~multiMotion()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::septernion
tnbLib::solidBodyMotionFunctions::multiMotion::transformation() const
{
	scalar t = time_.value();

	septernion TR = SBMFs_[0].transformation();

	for (label i = 1; i < SBMFs_.size(); i++)
	{
		TR *= SBMFs_[i].transformation();
	}

	DebugInFunction << "Time = " << t << " transformation: " << TR << endl;

	return TR;
}


bool tnbLib::solidBodyMotionFunctions::multiMotion::read
(
	const dictionary& SBMFCoeffs
)
{
	solidBodyMotionFunction::read(SBMFCoeffs);

	label i = 0;
	SBMFs_.setSize(SBMFCoeffs_.size());

	forAllConstIter(IDLList<entry>, SBMFCoeffs_, iter)
	{
		if (iter().isDict())
		{
			SBMFs_.set
			(
				i,
				solidBodyMotionFunction::New(iter().dict(), time_)
			);

			Info << "Constructed SBMF " << i << " : "
				<< iter().keyword() << " of type "
				<< SBMFs_[i].type() << endl;

			i++;
		}
	}
	SBMFs_.setSize(i);

	return true;
}


// ************************************************************************* //