#include <findRefCell.hxx>

#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

bool tnbLib::setRefCell
(
	const volScalarField& field,
	const volScalarField& fieldRef,
	const dictionary& dict,
	label& refCelli,
	scalar& refValue,
	const bool forceReference
)
{
	if (fieldRef.needReference() || forceReference)
	{
		word refCellName = field.name() + "RefCell";
		word refPointName = field.name() + "RefPoint";

		word refValueName = field.name() + "RefValue";

		if (dict.found(refCellName))
		{
			if (Pstream::master())
			{
				refCelli = readLabel(dict.lookup(refCellName));

				if (refCelli < 0 || refCelli >= field.mesh().nCells())
				{
					FatalIOErrorInFunction
					(
						dict
					) << "Illegal master cellID " << refCelli
						<< ". Should be 0.." << field.mesh().nCells()
						<< exit(FatalIOError);
				}
			}
			else
			{
				refCelli = -1;
			}
		}
		else if (dict.found(refPointName))
		{
			point refPointi(dict.lookup(refPointName));

			// Try fast approximate search avoiding octree construction
			refCelli = field.mesh().findCell(refPointi, polyMesh::FACE_PLANES);

			label hasRef = (refCelli >= 0 ? 1 : 0);
			label sumHasRef = returnReduce<label>(hasRef, sumOp<label>());

			// If reference cell no found use octree search
			// with cell tet-decompositoin
			if (sumHasRef != 1)
			{
				refCelli = field.mesh().findCell(refPointi);

				hasRef = (refCelli >= 0 ? 1 : 0);
				sumHasRef = returnReduce<label>(hasRef, sumOp<label>());
			}

			if (sumHasRef != 1)
			{
				FatalIOErrorInFunction
				(
					dict
				) << "Unable to set reference cell for field " << field.name()
					<< nl << "    Reference point " << refPointName
					<< " " << refPointi
					<< " found on " << sumHasRef << " domains (should be one)"
					<< nl << exit(FatalIOError);
			}
		}
		else
		{
			FatalIOErrorInFunction
			(
				dict
			) << "Unable to set reference cell for field " << field.name()
				<< nl
				<< "    Please supply either " << refCellName
				<< " or " << refPointName << nl << exit(FatalIOError);
		}

		refValue = readScalar(dict.lookup(refValueName));

		return true;
	}
	else
	{
		return false;
	}
}


bool tnbLib::setRefCell
(
	const volScalarField& field,
	const dictionary& dict,
	label& refCelli,
	scalar& refValue,
	const bool forceReference
)
{
	return setRefCell(field, field, dict, refCelli, refValue, forceReference);
}


tnbLib::scalar tnbLib::getRefCellValue
(
	const volScalarField& field,
	const label refCelli
)
{
	scalar refCellValue = (refCelli >= 0 ? field[refCelli] : 0.0);
	return returnReduce(refCellValue, sumOp<scalar>());
}


// ************************************************************************* //