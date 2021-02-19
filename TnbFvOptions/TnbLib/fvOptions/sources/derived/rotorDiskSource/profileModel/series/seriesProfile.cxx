#include <seriesProfile.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <IFstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(seriesProfile, 0);
	addToRunTimeSelectionTable(profileModel, seriesProfile, dictionary);
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

tnbLib::scalar tnbLib::seriesProfile::evaluateDrag
(
	const scalar& xIn,
	const List<scalar>& values
) const
{
	scalar result = 0.0;

	forAll(values, i)
	{
		result += values[i] * cos(i*xIn);
	}

	return result;
}


tnbLib::scalar tnbLib::seriesProfile::evaluateLift
(
	const scalar& xIn,
	const List<scalar>& values
) const
{
	scalar result = 0.0;

	forAll(values, i)
	{
		// note: first contribution always zero since sin(0) = 0, but
		// keep zero base to be consistent with drag coeffs
		result += values[i] * sin(i*xIn);
	}

	return result;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::seriesProfile::seriesProfile
(
	const dictionary& dict,
	const word& modelName
)
	:
	profileModel(dict, modelName),
	CdCoeffs_(),
	ClCoeffs_()
{
	if (readFromFile())
	{
		IFstream is(fName_);
		is >> CdCoeffs_ >> ClCoeffs_;
	}
	else
	{
		dict.lookup("CdCoeffs") >> CdCoeffs_;
		dict.lookup("ClCoeffs") >> ClCoeffs_;
	}


	if (CdCoeffs_.empty())
	{
		FatalErrorInFunction
			<< "CdCoeffs must be specified" << exit(FatalError);
	}
	if (ClCoeffs_.empty())
	{
		FatalErrorInFunction
			<< "ClCoeffs must be specified" << exit(FatalError);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::seriesProfile::Cdl(const scalar alpha, scalar& Cd, scalar& Cl) const
{
	Cd = evaluateDrag(alpha, CdCoeffs_);
	Cl = evaluateLift(alpha, ClCoeffs_);
}


// ************************************************************************* //