#include <partialFaceAreaWeightAMI.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(partialFaceAreaWeightAMI, 0);
	addToRunTimeSelectionTable(AMIMethod, partialFaceAreaWeightAMI, components);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::partialFaceAreaWeightAMI::setNextFaces
(
	label& startSeedI,
	label& srcFacei,
	label& tgtFacei,
	const boolList& mapFlag,
	labelList& seedFaces,
	const DynamicList<label>& visitedFaces,
	const bool errorOnNotFound
) const
{
	faceAreaWeightAMI::setNextFaces
	(
		startSeedI,
		srcFacei,
		tgtFacei,
		mapFlag,
		seedFaces,
		visitedFaces,
		false // no error on not found
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::partialFaceAreaWeightAMI::partialFaceAreaWeightAMI
(
	const primitivePatch& srcPatch,
	const primitivePatch& tgtPatch,
	const scalarField& srcMagSf,
	const scalarField& tgtMagSf,
	const faceAreaIntersect::triangulationMode& triMode,
	const bool reverseTarget,
	const bool requireMatch
)
	:
	faceAreaWeightAMI
	(
		srcPatch,
		tgtPatch,
		srcMagSf,
		tgtMagSf,
		triMode,
		reverseTarget,
		requireMatch
	)
{}


// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * //

tnbLib::partialFaceAreaWeightAMI::~partialFaceAreaWeightAMI()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::partialFaceAreaWeightAMI::conformal() const
{
	return false;
}


void tnbLib::partialFaceAreaWeightAMI::calculate
(
	labelListList& srcAddress,
	scalarListList& srcWeights,
	labelListList& tgtAddress,
	scalarListList& tgtWeights,
	label srcFacei,
	label tgtFacei
)
{
	bool ok =
		this->initialise
		(
			srcAddress,
			srcWeights,
			tgtAddress,
			tgtWeights,
			srcFacei,
			tgtFacei
		);

	if (!ok)
	{
		return;
	}

	// temporary storage for addressing and weights
	List<DynamicList<label>> srcAddr(this->srcPatch_.size());
	List<DynamicList<scalar>> srcWght(srcAddr.size());
	List<DynamicList<label>> tgtAddr(this->tgtPatch_.size());
	List<DynamicList<scalar>> tgtWght(tgtAddr.size());

	faceAreaWeightAMI::calcAddressing
	(
		srcAddr,
		srcWght,
		tgtAddr,
		tgtWght,
		srcFacei,
		tgtFacei
	);

	// transfer data to persistent storage
	forAll(srcAddr, i)
	{
		srcAddress[i].transfer(srcAddr[i]);
		srcWeights[i].transfer(srcWght[i]);
	}
	forAll(tgtAddr, i)
	{
		tgtAddress[i].transfer(tgtAddr[i]);
		tgtWeights[i].transfer(tgtWght[i]);
	}
}


// ************************************************************************* //