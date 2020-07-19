#include <regionCoupledBaseGAMGInterface.hxx>

#include <AMIInterpolation.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <Map.hxx>
#include <polyMesh.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::regionCoupledBaseGAMGInterface::regionCoupledBaseGAMGInterface
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
	fineRegionCoupledLduInterface_
	(
		refCast<const regionCoupledLduInterface>(fineInterface)
	)
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

	/*
	// On the owner side construct the AMI
	if (fineRegionCoupledLduInterface_.owner())
	{
		const polyMesh& nbrMesh =
			fineRegionCoupledLduInterface_.nbrMesh();

		if
		(
			nbrMesh.foundObject<GAMGAgglomeration>(GAMGAgglomeration::typeName)
		)
		{
			const GAMGAgglomeration& nbrAgg = nbrMesh.thisDb().lookupObject
			<
				GAMGAgglomeration
			>
			(
				GAMGAgglomeration::typeName
			);

			label nbrLevel(-1);
			if (nbrAgg.size() > fineLevelIndex)
			{
				nbrLevel = fineLevelIndex;
			}
			else
			{
				nbrLevel = nbrAgg.size() - 1;
			}

			const labelField& nbrRestrictMap =
				nbrAgg.restrictAddressing(nbrLevel);

			const labelUList& nbrFaceCells =
				nbrLduInterface
				(
					nbrLevel,
					neighbPatchID()
				).faceCells();


			const IndirectList<label> nbrPatchRestrictMap
			(
				nbrRestrictMap,
				nbrFaceCells
			);

			labelList nbrFaceRestrictAddressing;
			{
				// From face to coarse face
				DynamicList<label> dynNbrFaceRestrictAddressing
				(
					nbrPatchRestrictMap.size()
				);

				Map<label> masterToCoarseFace(nbrPatchRestrictMap.size());

				forAll(nbrPatchRestrictMap, ffi)
				{
					label curMaster = nbrPatchRestrictMap[ffi];

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

				nbrFaceRestrictAddressing.transfer
				(
					dynNbrFaceRestrictAddressing
				);
			}

			amiPtr_.reset
			(
				new AMIInterpolation
				(
					fineRegionCoupledLduInterface_.AMI(),
					faceRestrictAddressing_,
					nbrFaceRestrictAddressing
				)
			);
		}
		else
		{
			FatalErrorInFunction
				<< " GAMGAgglomeration was not found in the nbr mesh. "
				<< " Check on the cacheAgglomeration flag in fvSolution"
				<< exit(FatalError);
		}
	}
	*/

}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::regionCoupledBaseGAMGInterface::~regionCoupledBaseGAMGInterface()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::labelField> tnbLib::regionCoupledBaseGAMGInterface::
internalFieldTransfer
(
	const Pstream::commsTypes,
	const labelUList& iF
) const
{
	/*
	// const labelUList& nbrFaceCells = neighbPatch().faceCells();

	const labelUList& nbrFaceCells = nbrLduInterface().faceCells();

	tmp<labelField> tpnf(new labelField(nbrFaceCells.size()));
	labelField& pnf = tpnf();

	forAll(pnf, facei)
	{
		pnf[facei] = iF[nbrFaceCells[facei]];
	}
	*/
	tmp<labelField> tpnf(new labelField(iF));

	return tpnf;
}


// ************************************************************************* //