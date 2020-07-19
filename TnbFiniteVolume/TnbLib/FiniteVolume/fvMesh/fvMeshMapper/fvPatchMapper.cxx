#include <fvPatchMapper.hxx>

#include <fvPatch.hxx>
#include <fvBoundaryMesh.hxx>
#include <fvMesh.hxx>
#include <mapPolyMesh.hxx>
#include <faceMapper.hxx>

#include <demandDrivenData.hxx>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::fvPatchMapper::calcAddressing() const
{
	if
		(
			directAddrPtr_
			|| interpolationAddrPtr_
			|| weightsPtr_
			)
	{
		FatalErrorInFunction
			<< "Addressing already calculated"
			<< abort(FatalError);
	}

	// Mapping
	const label oldPatchStart =
		faceMap_.oldPatchStarts()[patch_.index()];

	const label oldPatchEnd =
		oldPatchStart + faceMap_.oldPatchSizes()[patch_.index()];

	hasUnmapped_ = false;

	// Assemble the maps: slice to patch
	if (direct())
	{
		// Direct mapping - slice to size
		directAddrPtr_ = new labelList
		(
			patch_.patchSlice
			(
				static_cast<const labelList&>(faceMap_.directAddressing())
			)
		);
		labelList& addr = *directAddrPtr_;

		// Adjust mapping to manage hits into other patches and into
		// internal
		forAll(addr, facei)
		{
			if
				(
					addr[facei] >= oldPatchStart
					&& addr[facei] < oldPatchEnd
					)
			{
				addr[facei] -= oldPatchStart;
			}
			else
			{
				// addr[facei] = 0;
				addr[facei] = -1;
				hasUnmapped_ = true;
			}
		}

		if (fvMesh::debug)
		{
			if (min(addr) < 0)
			{
				WarningInFunction
					<< "Unmapped entry in patch mapping for patch "
					<< patch_.index() << " named " << patch_.name()
					<< endl;
			}
		}
	}
	else
	{
		// Interpolative mapping
		interpolationAddrPtr_ =
			new labelListList
			(
				patch_.patchSlice(faceMap_.addressing())
			);
		labelListList& addr = *interpolationAddrPtr_;

		weightsPtr_ =
			new scalarListList
			(
				patch_.patchSlice(faceMap_.weights())
			);
		scalarListList& w = *weightsPtr_;

		// Adjust mapping to manage hits into other patches and into
		// internal
		forAll(addr, facei)
		{
			labelList& curAddr = addr[facei];
			scalarList& curW = w[facei];

			if
				(
					min(curAddr) >= oldPatchStart
					&& max(curAddr) < oldPatchEnd
					)
			{
				// No adjustment of weights, just subtract patch start
				forAll(curAddr, i)
				{
					curAddr[i] -= oldPatchStart;
				}
			}
			else
			{
				// Need to recalculate weights to exclude hits into internal
				labelList newAddr(curAddr.size(), false);
				scalarField newWeights(curAddr.size());
				label nActive = 0;

				forAll(curAddr, lfI)
				{
					if
						(
							curAddr[lfI] >= oldPatchStart
							&& curAddr[lfI] < oldPatchEnd
							)
					{
						newAddr[nActive] = curAddr[lfI] - oldPatchStart;
						newWeights[nActive] = curW[lfI];
						nActive++;
					}
				}

				newAddr.setSize(nActive);
				newWeights.setSize(nActive);

				// Re-scale the weights
				if (nActive > 0)
				{
					newWeights /= sum(newWeights);
				}
				else
				{
					hasUnmapped_ = true;
				}

				// Reset addressing and weights
				curAddr = newAddr;
				curW = newWeights;
			}
		}

		if (fvMesh::debug)
		{
			forAll(addr, i)
			{
				if (min(addr[i]) < 0)
				{
					FatalErrorInFunction
						<< "Error in patch mapping for patch "
						<< patch_.index() << " named " << patch_.name()
						<< abort(FatalError);
				}
			}
		}
	}
}


void tnbLib::fvPatchMapper::clearOut()
{
	deleteDemandDrivenData(directAddrPtr_);
	deleteDemandDrivenData(interpolationAddrPtr_);
	deleteDemandDrivenData(weightsPtr_);
	hasUnmapped_ = false;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fvPatchMapper::fvPatchMapper
(
	const fvPatch& patch,
	const faceMapper& faceMap
)
	:
	patch_(patch),
	faceMap_(faceMap),
	sizeBeforeMapping_(faceMap.oldPatchSizes()[patch_.index()]),
	hasUnmapped_(false),
	directAddrPtr_(nullptr),
	interpolationAddrPtr_(nullptr),
	weightsPtr_(nullptr)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fvPatchMapper::~fvPatchMapper()
{
	clearOut();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::labelUList& tnbLib::fvPatchMapper::directAddressing() const
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


const tnbLib::labelListList& tnbLib::fvPatchMapper::addressing() const
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


const tnbLib::scalarListList& tnbLib::fvPatchMapper::weights() const
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


// ************************************************************************* //