#include <refinementHistoryConstraint.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <syncTools.hxx>

#include <refinementHistory.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeName(refinementHistoryConstraint);

	addToRunTimeSelectionTable
	(
		decompositionConstraint,
		refinementHistoryConstraint,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::refinementHistoryConstraint::refinementHistoryConstraint
(
	const dictionary& constraintsDict,
	const word& modelType
)
	:
	decompositionConstraint(constraintsDict, typeName)
{
	if (decompositionConstraint::debug)
	{
		Info << type() << " : setting constraints to preserve refinement history"
			<< endl;
	}
}


tnbLib::refinementHistoryConstraint::refinementHistoryConstraint()
	:
	decompositionConstraint(dictionary(), typeName)
{
	if (decompositionConstraint::debug)
	{
		Info << type() << " : setting constraints to refinement history"
			<< endl;
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::refinementHistoryConstraint::add
(
	const polyMesh& mesh,
	boolList& blockedFace,
	PtrList<labelList>& specifiedProcessorFaces,
	labelList& specifiedProcessor,
	List<labelPair>& explicitConnections
) const
{
	autoPtr<const refinementHistory> storagePtr;
	refinementHistory const* refPtr = nullptr;

	if (mesh.foundObject<refinementHistory>("refinementHistory"))
	{
		if (decompositionConstraint::debug)
		{
			Info << type() << " : found refinementHistory" << endl;
		}
		refPtr = &mesh.lookupObject<refinementHistory>("refinementHistory");
	}
	else
	{
		if (decompositionConstraint::debug)
		{
			Info << type() << " : reading refinementHistory from time "
				<< mesh.facesInstance() << endl;
		}
		storagePtr.reset
		(
			new refinementHistory
			(
				IOobject
				(
					"refinementHistory",
					mesh.facesInstance(),
					polyMesh::meshSubDir,
					mesh,
					IOobject::READ_IF_PRESENT,
					IOobject::NO_WRITE
				),
				mesh.nCells()
			)
		);
	}

	const refinementHistory& history =
		(
			storagePtr.valid()
			? storagePtr()
			: *refPtr
			);

	if (history.active())
	{
		// refinementHistory itself implements decompositionConstraint
		history.add
		(
			blockedFace,
			specifiedProcessorFaces,
			specifiedProcessor,
			explicitConnections
		);
	}
}


void tnbLib::refinementHistoryConstraint::apply
(
	const polyMesh& mesh,
	const boolList& blockedFace,
	const PtrList<labelList>& specifiedProcessorFaces,
	const labelList& specifiedProcessor,
	const List<labelPair>& explicitConnections,
	labelList& decomposition
) const
{
	autoPtr<const refinementHistory> storagePtr;
	refinementHistory const* refPtr = nullptr;

	if (mesh.foundObject<refinementHistory>("refinementHistory"))
	{
		// if (decompositionConstraint::debug)
		//{
		//    Info<< type() << " : found refinementHistory" << endl;
		//}
		refPtr = &mesh.lookupObject<refinementHistory>("refinementHistory");
	}
	else
	{
		// if (decompositionConstraint::debug)
		//{
		//    Info<< type() << " : reading refinementHistory from time "
		//        << mesh.facesInstance() << endl;
		//}
		storagePtr.reset
		(
			new refinementHistory
			(
				IOobject
				(
					"refinementHistory",
					mesh.facesInstance(),
					polyMesh::meshSubDir,
					mesh,
					IOobject::READ_IF_PRESENT,
					IOobject::NO_WRITE
				),
				mesh.nCells()
			)
		);
	}

	const refinementHistory& history =
		(
			storagePtr.valid()
			? storagePtr()
			: *refPtr
			);

	if (history.active())
	{
		// refinementHistory itself implements decompositionConstraint
		history.apply
		(
			blockedFace,
			specifiedProcessorFaces,
			specifiedProcessor,
			explicitConnections,
			decomposition
		);
	}
}


// ************************************************************************* //