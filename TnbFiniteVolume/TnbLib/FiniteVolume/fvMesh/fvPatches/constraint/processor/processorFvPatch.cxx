#include <processorFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <transformField.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(processorFvPatch, 0);
	addToRunTimeSelectionTable(fvPatch, processorFvPatch, polyPatch);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::processorFvPatch::makeWeights(scalarField& w) const
{
	if (Pstream::parRun())
	{
		const vectorField delta(coupledFvPatch::delta());

		// The face normals point in the opposite direction on the other side
		const vectorField nbrDelta
		(
			procPolyPatch_.neighbFaceCentres()
			- procPolyPatch_.neighbFaceCellCentres()
		);

		const scalarField nfDelta(nf() & delta);

		const scalarField nbrNfDelta
		(
			(
				procPolyPatch_.neighbFaceAreas()
				/ (mag(procPolyPatch_.neighbFaceAreas()) + vSmall)
				) & nbrDelta
		);

		forAll(delta, facei)
		{
			const scalar ndoi = nfDelta[facei];
			const scalar ndni = nbrNfDelta[facei];
			const scalar ndi = ndoi + ndni;

			if (ndni / vGreat < ndi)
			{
				w[facei] = ndni / ndi;
			}
			else
			{
				const scalar doi = mag(delta[facei]);
				const scalar dni = mag(nbrDelta[facei]);
				const scalar di = doi + dni;

				w[facei] = dni / di;
			}
		}
	}
	else
	{
		w = 1.0;
	}
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::processorFvPatch::delta() const
{
	if (Pstream::parRun())
	{
		// To the transformation if necessary
		if (parallel())
		{
			return
				coupledFvPatch::delta()
				- (
					procPolyPatch_.neighbFaceCentres()
					- procPolyPatch_.neighbFaceCellCentres()
					);
		}
		else
		{
			return
				coupledFvPatch::delta()
				- transform
				(
					forwardT(),
					(
						procPolyPatch_.neighbFaceCentres()
						- procPolyPatch_.neighbFaceCellCentres()
						)
				);
		}
	}
	else
	{
		return coupledFvPatch::delta();
	}
}


tnbLib::tmp<tnbLib::labelField> tnbLib::processorFvPatch::interfaceInternalField
(
	const labelUList& internalData
) const
{
	return patchInternalField(internalData);
}


void tnbLib::processorFvPatch::initInternalFieldTransfer
(
	const Pstream::commsTypes commsType,
	const labelUList& iF
) const
{
	send(commsType, patchInternalField(iF)());
}


tnbLib::tmp<tnbLib::labelField> tnbLib::processorFvPatch::internalFieldTransfer
(
	const Pstream::commsTypes commsType,
	const labelUList&
) const
{
	return receive<label>(commsType, this->size());
}


// ************************************************************************* //