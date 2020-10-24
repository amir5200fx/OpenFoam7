#include <manualRenumber.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <IFstream.hxx>
#include <labelIOList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(manualRenumber, 0);

	addToRunTimeSelectionTable
	(
		renumberMethod,
		manualRenumber,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::manualRenumber::manualRenumber(const dictionary& renumberDict)
	:
	renumberMethod(renumberDict),
	dataFile_
	(
		renumberDict.optionalSubDict(typeName + "Coeffs").lookup("dataFile")
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::labelList tnbLib::manualRenumber::renumber
(
	const polyMesh& mesh,
	const pointField& points
) const
{
	labelIOList newToOld
	(
		IOobject
		(
			dataFile_,
			mesh.facesInstance(),
			mesh,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE,
			false
		)
	);

	// check if the final renumbering is OK

	if (newToOld.size() != points.size())
	{
		FatalErrorInFunction
			<< "Size of renumber list does not correspond "
			<< "to the number of points.  Size: "
			<< newToOld.size() << " Number of points: "
			<< points.size()
			<< ".\n" << "Manual renumbering data read from file "
			<< dataFile_ << "." << endl
			<< exit(FatalError);
	}

	// Invert to see if one to one
	labelList oldToNew(points.size(), -1);
	forAll(newToOld, i)
	{
		label origCelli = newToOld[i];

		if (origCelli < 0 || origCelli >= points.size())
		{
			FatalErrorInFunction
				<< "Renumbering is not one-to-one. Index "
				<< i << " maps onto original cell " << origCelli
				<< ".\n" << "Manual renumbering data read from file "
				<< dataFile_ << "." << endl
				<< exit(FatalError);
		}

		if (oldToNew[origCelli] == -1)
		{
			oldToNew[origCelli] = i;
		}
		else
		{
			FatalErrorInFunction
				<< "Renumbering is not one-to-one. Both index "
				<< oldToNew[origCelli]
				<< " and " << i << " map onto " << origCelli
				<< ".\n" << "Manual renumbering data read from file "
				<< dataFile_ << "." << endl
				<< exit(FatalError);
		}
	}

	return move(newToOld);
}


// ************************************************************************* //