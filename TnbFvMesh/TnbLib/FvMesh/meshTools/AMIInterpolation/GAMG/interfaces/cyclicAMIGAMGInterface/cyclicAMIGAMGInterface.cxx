#include <cyclicAMIGAMGInterface.hxx>

#include <AMIInterpolation.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <Map.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicAMIGAMGInterface, 0);
	addToRunTimeSelectionTable
	(
		GAMGInterface,
		cyclicAMIGAMGInterface,
		lduInterface
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cyclicAMIGAMGInterface::cyclicAMIGAMGInterface
(
	const label index,
	const lduInterfacePtrsList& coarseInterfaces,
	const lduInterface& fineInterface,
	const labelField& localRestrictAddressing,
	const labelField& neighbourRestrictAddressing,
	const label fineLevelIndex,
	const label coarseComm
)
	:
	GAMGInterface
	(
		index,
		coarseInterfaces
	),
	fineCyclicAMIInterface_
	(
		refCast<const cyclicAMILduInterface>(fineInterface)
	),
	AMIs_(),
	AMITransforms_()
{
	// Construct face agglomeration from cell agglomeration
	{
		// From coarse face to cell
		DynamicList<label> dynFaceCells(localRestrictAddressing.size());

		// From face to coarse face
		DynamicList<label> dynFaceRestrictAddressing
		(
			localRestrictAddressing.size()
		);

		Map<label> masterToCoarseFace(localRestrictAddressing.size());

		forAll(localRestrictAddressing, ffi)
		{
			label curMaster = localRestrictAddressing[ffi];

			Map<label>::const_iterator fnd = masterToCoarseFace.find
			(
				curMaster
			);

			if (fnd == masterToCoarseFace.end())
			{
				// New coarse face
				label coarseI = dynFaceCells.size();
				dynFaceRestrictAddressing.append(coarseI);
				dynFaceCells.append(curMaster);
				masterToCoarseFace.insert(curMaster, coarseI);
			}
			else
			{
				// Already have coarse face
				dynFaceRestrictAddressing.append(fnd());
			}
		}

		faceCells_.transfer(dynFaceCells);
		faceRestrictAddressing_.transfer(dynFaceRestrictAddressing);
	}


	// On the owner side construct the AMI

	if (fineCyclicAMIInterface_.owner())
	{
		// Construct the neighbour side agglomeration (as the neighbour would
		// do it so it the exact loop above using neighbourRestrictAddressing
		// instead of localRestrictAddressing)

		labelList nbrFaceRestrictAddressing;
		{
			// From face to coarse face
			DynamicList<label> dynNbrFaceRestrictAddressing
			(
				neighbourRestrictAddressing.size()
			);

			Map<label> masterToCoarseFace(neighbourRestrictAddressing.size());

			forAll(neighbourRestrictAddressing, ffi)
			{
				label curMaster = neighbourRestrictAddressing[ffi];

				Map<label>::const_iterator fnd = masterToCoarseFace.find
				(
					curMaster
				);

				if (fnd == masterToCoarseFace.end())
				{
					// New coarse face
					label coarseI = masterToCoarseFace.size();
					dynNbrFaceRestrictAddressing.append(coarseI);
					masterToCoarseFace.insert(curMaster, coarseI);
				}
				else
				{
					// Already have coarse face
					dynNbrFaceRestrictAddressing.append(fnd());
				}
			}

			nbrFaceRestrictAddressing.transfer(dynNbrFaceRestrictAddressing);
		}

		AMIs_.resize(fineCyclicAMIInterface_.AMIs().size());
		AMITransforms_.resize(fineCyclicAMIInterface_.AMITransforms().size());

		forAll(AMIs(), i)
		{
			AMIs_.set
			(
				i,
				new AMIInterpolation
				(
					fineCyclicAMIInterface_.AMIs()[i],
					faceRestrictAddressing_,
					nbrFaceRestrictAddressing
				)
			);

			AMITransforms_[i] = fineCyclicAMIInterface_.AMITransforms()[i];
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cyclicAMIGAMGInterface::~cyclicAMIGAMGInterface()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::labelField> tnbLib::cyclicAMIGAMGInterface::internalFieldTransfer
(
	const Pstream::commsTypes,
	const labelUList& iF
) const
{
	const cyclicAMIGAMGInterface& nbr =
		dynamic_cast<const cyclicAMIGAMGInterface&>(neighbPatch());

	const labelUList& nbrFaceCells = nbr.faceCells();

	tmp<labelField> tpnf(new labelField(nbrFaceCells.size()));
	labelField& pnf = tpnf.ref();

	forAll(pnf, facei)
	{
		pnf[facei] = iF[nbrFaceCells[facei]];
	}

	return tpnf;
}


// ************************************************************************* //