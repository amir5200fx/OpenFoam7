#include <dimensionedConstants.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	dictionary* dimensionedConstantsPtr_(nullptr);

	dictionary& dimensionedConstants()
	{
		return debug::switchSet
		(
			"DimensionedConstants",
			dimensionedConstantsPtr_
		);
	}


	dimensionedScalar dimensionedConstant
	(
		const word& group,
		const word& varName
	)
	{
		dictionary& dict = dimensionedConstants();

		// Check that the entries exist.
		// Note: should make FatalError robust instead!

		if (!dict.found("unitSet"))
		{
			std::cerr << "Cannot find unitSet in dictionary " << dict.name()
				<< std::endl;
		}

		const word unitSetCoeffs(word(dict.lookup("unitSet")) + "Coeffs");

		if (!dict.found(unitSetCoeffs))
		{
			std::cerr << "Cannot find " << unitSetCoeffs << " in dictionary "
				<< dict.name() << std::endl;
		}

		dictionary& unitDict = dict.subDict(unitSetCoeffs);

		dictionary& groupDict = unitDict.subDict(group);

		return dimensionedScalar(groupDict.lookup(varName));
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //