#include <faceMapper.hxx>

#include <demandDrivenData.hxx>
#include <polyMesh.hxx>
#include <mapPolyMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::faceMapper::calcAddressing() const
{
	if
		(
			directAddrPtr_
			|| interpolationAddrPtr_
			|| weightsPtr_
			|| insertedFaceLabelsPtr_
			)
	{
		FatalErrorInFunction
			<< "Addressing already calculated."
			<< abort(FatalError);
	}

	if (direct())
	{
		// Direct addressing, no weights

		directAddrPtr_ = new labelList(mpm_.faceMap());
		labelList& directAddr = *directAddrPtr_;

		// Reset the size of addressing list to contain only live faces
		directAddr.setSize(mesh_.nFaces());

		insertedFaceLabelsPtr_ = new labelList(mesh_.nFaces());
		labelList& insertedFaces = *insertedFaceLabelsPtr_;

		label nInsertedFaces = 0;

		forAll(directAddr, facei)
		{
			if (directAddr[facei] < 0)
			{
				// Found inserted face
				directAddr[facei] = 0;
				insertedFaces[nInsertedFaces] = facei;
				nInsertedFaces++;
			}
		}

		insertedFaces.setSize(nInsertedFaces);
	}
	else
	{
		// Interpolative addressing

		interpolationAddrPtr_ = new labelListList(mesh_.nFaces());
		labelListList& addr = *interpolationAddrPtr_;

		weightsPtr_ = new scalarListList(mesh_.nFaces());
		scalarListList& w = *weightsPtr_;

		const List<objectMap>& ffp = mpm_.facesFromPointsMap();

		forAll(ffp, ffpI)
		{
			// Get addressing
			const labelList& mo = ffp[ffpI].masterObjects();

			label facei = ffp[ffpI].index();

			if (addr[facei].size())
			{
				FatalErrorInFunction
					<< "Master face " << facei
					<< " mapped from point faces " << mo
					<< " already destination of mapping." << abort(FatalError);
			}

			// Map from masters, uniform weights
			addr[facei] = mo;
			w[facei] = scalarList(mo.size(), 1.0 / mo.size());
		}

		const List<objectMap>& ffe = mpm_.facesFromEdgesMap();

		forAll(ffe, ffeI)
		{
			// Get addressing
			const labelList& mo = ffe[ffeI].masterObjects();

			label facei = ffe[ffeI].index();

			if (addr[facei].size())
			{
				FatalErrorInFunction
					<< "Master face " << facei
					<< " mapped from edge faces " << mo
					<< " already destination of mapping." << abort(FatalError);
			}

			// Map from masters, uniform weights
			addr[facei] = mo;
			w[facei] = scalarList(mo.size(), 1.0 / mo.size());
		}

		const List<objectMap>& fff = mpm_.facesFromFacesMap();

		forAll(fff, fffI)
		{
			// Get addressing
			const labelList& mo = fff[fffI].masterObjects();

			label facei = fff[fffI].index();

			if (addr[facei].size())
			{
				FatalErrorInFunction
					<< "Master face " << facei
					<< " mapped from face faces " << mo
					<< " already destination of mapping." << abort(FatalError);
			}

			// Map from masters, uniform weights
			addr[facei] = mo;
			w[facei] = scalarList(mo.size(), 1.0 / mo.size());
		}


		// Do mapped faces. Note that can already be set from facesFromFaces
		// so check if addressing size still zero.
		const labelList& fm = mpm_.faceMap();

		forAll(fm, facei)
		{
			if (fm[facei] > -1 && addr[facei].empty())
			{
				// Mapped from a single face
				addr[facei] = labelList(1, fm[facei]);
				w[facei] = scalarList(1, 1.0);
			}
		}


		// Grab inserted faces (for them the size of addressing is still zero)

		insertedFaceLabelsPtr_ = new labelList(mesh_.nFaces());
		labelList& insertedFaces = *insertedFaceLabelsPtr_;

		label nInsertedFaces = 0;

		forAll(addr, facei)
		{
			if (addr[facei].empty())
			{
				// Mapped from a dummy face
				addr[facei] = labelList(1, label(0));
				w[facei] = scalarList(1, 1.0);

				insertedFaces[nInsertedFaces] = facei;
				nInsertedFaces++;
			}
		}

		insertedFaces.setSize(nInsertedFaces);
	}
}


void tnbLib::faceMapper::clearOut()
{
	deleteDemandDrivenData(directAddrPtr_);
	deleteDemandDrivenData(interpolationAddrPtr_);
	deleteDemandDrivenData(weightsPtr_);
	deleteDemandDrivenData(insertedFaceLabelsPtr_);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::faceMapper::faceMapper(const mapPolyMesh& mpm)
	:
	mesh_(mpm.mesh()),
	mpm_(mpm),
	insertedFaces_(true),
	direct_(false),
	directAddrPtr_(nullptr),
	interpolationAddrPtr_(nullptr),
	weightsPtr_(nullptr),
	insertedFaceLabelsPtr_(nullptr)
{
	// Check for possibility of direct mapping
	if
		(
			mpm_.facesFromPointsMap().empty()
			&& mpm_.facesFromEdgesMap().empty()
			&& mpm_.facesFromFacesMap().empty()
			)
	{
		direct_ = true;
	}
	else
	{
		direct_ = false;
	}

	// Check for inserted faces
	if (direct_ && (mpm_.faceMap().empty() || min(mpm_.faceMap()) > -1))
	{
		insertedFaces_ = false;
	}
	else
	{
		// Need to check all 3 lists to see if there are inserted faces
		// with no owner

		// Make a copy of the face map, add the entries for faces from points
		// and faces from edges and check for left-overs
		labelList fm(mesh_.nFaces(), -1);

		const List<objectMap>& ffp = mpm_.facesFromPointsMap();

		forAll(ffp, ffpI)
		{
			fm[ffp[ffpI].index()] = 0;
		}

		const List<objectMap>& ffe = mpm_.facesFromEdgesMap();

		forAll(ffe, ffeI)
		{
			fm[ffe[ffeI].index()] = 0;
		}

		const List<objectMap>& fff = mpm_.facesFromFacesMap();

		forAll(fff, fffI)
		{
			fm[fff[fffI].index()] = 0;
		}

		if (min(fm) < 0)
		{
			insertedFaces_ = true;
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::faceMapper::~faceMapper()
{
	clearOut();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::faceMapper::sizeBeforeMapping() const
{
	return mpm_.nOldFaces();
}


tnbLib::label tnbLib::faceMapper::internalSizeBeforeMapping() const
{
	return mpm_.nOldInternalFaces();
}


const tnbLib::labelUList& tnbLib::faceMapper::directAddressing() const
{
	if (!direct())
	{
		FatalErrorInFunction
			<< "Requested direct addressing for an interpolative mapper."
			<< abort(FatalError);
	}

	if (!insertedObjects())
	{
		// No inserted faces.  Re-use faceMap
		return mpm_.faceMap();
	}
	else
	{
		if (!directAddrPtr_)
		{
			calcAddressing();
		}

		return *directAddrPtr_;
	}
}


const tnbLib::labelListList& tnbLib::faceMapper::addressing() const
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


const tnbLib::scalarListList& tnbLib::faceMapper::weights() const
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


const tnbLib::labelList& tnbLib::faceMapper::insertedObjectLabels() const
{
	if (!insertedFaceLabelsPtr_)
	{
		if (!insertedObjects())
		{
			// There are no inserted faces
			insertedFaceLabelsPtr_ = new labelList(0);
		}
		else
		{
			calcAddressing();
		}
	}

	return *insertedFaceLabelsPtr_;
}


const tnbLib::labelHashSet& tnbLib::faceMapper::flipFaceFlux() const
{
	return mpm_.flipFaceFlux();
}


tnbLib::label tnbLib::faceMapper::nOldInternalFaces() const
{
	return mpm_.nOldInternalFaces();
}


const tnbLib::labelList& tnbLib::faceMapper::oldPatchStarts() const
{
	return mpm_.oldPatchStarts();
}


const tnbLib::labelList& tnbLib::faceMapper::oldPatchSizes() const
{
	return mpm_.oldPatchSizes();
}


// ************************************************************************* //