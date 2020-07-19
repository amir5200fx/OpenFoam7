#include <fvSurfaceMapper.hxx>

#include <fvMesh.hxx>
#include <mapPolyMesh.hxx>
#include <faceMapper.hxx>

#include <demandDrivenData.hxx> // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::fvSurfaceMapper::calcAddressing() const
{
	if
		(
			directAddrPtr_
			|| interpolationAddrPtr_
			|| weightsPtr_
			|| insertedObjectLabelsPtr_
			)
	{
		FatalErrorInFunction
			<< "Addressing already calculated"
			<< abort(FatalError);
	}

	// Mapping

	const label oldNInternal = faceMap_.nOldInternalFaces();

	// Assemble the maps
	if (direct())
	{
		// Direct mapping - slice to size
		directAddrPtr_ =
			new labelList
			(
				labelList::subList
				(
					faceMap_.directAddressing(),
					mesh_.nInternalFaces()
				)
			);
		labelList& addr = *directAddrPtr_;

		// Adjust for creation of an internal face from a boundary face
		forAll(addr, facei)
		{
			if (addr[facei] > oldNInternal)
			{
				addr[facei] = 0;
			}
		}
	}
	else
	{
		// Interpolative mapping - slice to size
		interpolationAddrPtr_ =
			new labelListList
			(
				labelListList::subList
				(
					faceMap_.addressing(),
					mesh_.nInternalFaces()
				)
			);
		labelListList& addr = *interpolationAddrPtr_;

		weightsPtr_ =
			new scalarListList
			(
				scalarListList::subList
				(
					faceMap_.weights(),
					mesh_.nInternalFaces()
				)
			);
		scalarListList& w = *weightsPtr_;

		// Adjust for creation of an internal face from a boundary face
		forAll(addr, facei)
		{
			if (max(addr[facei]) >= oldNInternal)
			{
				addr[facei] = labelList(1, label(0));
				w[facei] = scalarList(1, 1.0);
			}
		}
	}

	// Inserted objects

	// If there are, assemble the labels
	if (insertedObjects())
	{
		const labelList& insFaces = faceMap_.insertedObjectLabels();

		insertedObjectLabelsPtr_ = new labelList(insFaces.size());
		labelList& ins = *insertedObjectLabelsPtr_;

		label nIns = 0;

		forAll(insFaces, facei)
		{
			// If the face is internal, keep it here
			if (insFaces[facei] < mesh_.nInternalFaces())
			{
				ins[nIns] = insFaces[facei];
				nIns++;
			}
		}

		ins.setSize(nIns);
	}
	else
	{
		// No inserted objects
		insertedObjectLabelsPtr_ = new labelList(0);
	}
}


void tnbLib::fvSurfaceMapper::clearOut()
{
	deleteDemandDrivenData(directAddrPtr_);
	deleteDemandDrivenData(interpolationAddrPtr_);
	deleteDemandDrivenData(weightsPtr_);

	deleteDemandDrivenData(insertedObjectLabelsPtr_);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fvSurfaceMapper::fvSurfaceMapper
(
	const fvMesh& mesh,
	const faceMapper& fMapper
)
	:
	mesh_(mesh),
	faceMap_(fMapper),
	directAddrPtr_(nullptr),
	interpolationAddrPtr_(nullptr),
	weightsPtr_(nullptr),
	insertedObjectLabelsPtr_(nullptr)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fvSurfaceMapper::~fvSurfaceMapper()
{
	clearOut();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::labelUList& tnbLib::fvSurfaceMapper::directAddressing() const
{
	if (!direct())
	{
		FatalErrorInFunction
			<< "Requested direct addressing for an interpolative mapper."
			<< abort(FatalError);
	}

	if (!directAddrPtr_)
	{
		calcAddressing();
	}

	return *directAddrPtr_;
}


const tnbLib::labelListList& tnbLib::fvSurfaceMapper::addressing() const
{
	if (direct())
	{
		FatalErrorInFunction
			<< "Requested interpolative addressing for a direct mapper."
			<< abort(FatalError);
	}

	if (!interpolationAddrPtr_)
	{
		calcAddressing();
	}

	return *interpolationAddrPtr_;
}


const tnbLib::scalarListList& tnbLib::fvSurfaceMapper::weights() const
{
	if (direct())
	{
		FatalErrorInFunction
			<< "Requested interpolative weights for a direct mapper."
			<< abort(FatalError);
	}

	if (!weightsPtr_)
	{
		calcAddressing();
	}

	return *weightsPtr_;
}


const tnbLib::labelList& tnbLib::fvSurfaceMapper::insertedObjectLabels() const
{
	if (!insertedObjectLabelsPtr_)
	{
		calcAddressing();
	}

	return *insertedObjectLabelsPtr_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //


// ************************************************************************* //