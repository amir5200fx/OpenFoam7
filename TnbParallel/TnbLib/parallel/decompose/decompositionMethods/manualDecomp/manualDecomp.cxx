#include <manualDecomp.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <IFstream.hxx>
#include <labelIOList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(manualDecomp, 0);

	addToRunTimeSelectionTable
	(
		decompositionMethod,
		manualDecomp,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::manualDecomp::manualDecomp(const dictionary& decompositionDict)
	:
	decompositionMethod(decompositionDict),
	decompDataFile_
	(
		decompositionDict.optionalSubDict
		(
			word(decompositionDict.lookup("method")) + "Coeffs"
		).lookup("dataFile")
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::labelList tnbLib::manualDecomp::decompose
(
	const polyMesh& mesh,
	const pointField& points,
	const scalarField& pointWeights
)
{
	labelIOList finalDecomp
	(
		IOobject
		(
			decompDataFile_,
			mesh.facesInstance(),
			mesh,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE,
			false
		)
	);

	// check if the final decomposition is OK

	if (finalDecomp.size() != points.size())
	{
		FatalErrorInFunction
			<< "Size of decomposition list does not correspond "
			<< "to the number of points.  Size: "
			<< finalDecomp.size() << " Number of points: "
			<< points.size()
			<< ".\n" << "Manual decomposition data read from file "
			<< decompDataFile_ << "." << endl
			<< exit(FatalError);
	}

	if (min(finalDecomp) < 0 || max(finalDecomp) > nProcessors_ - 1)
	{
		FatalErrorInFunction
			<< "According to the decomposition, cells assigned to "
			<< "impossible processor numbers.  Min processor = "
			<< min(finalDecomp) << " Max processor = " << max(finalDecomp)
			<< ".\n" << "Manual decomposition data read from file "
			<< decompDataFile_ << "." << endl
			<< exit(FatalError);
	}

	return move(finalDecomp);
}


// ************************************************************************* //