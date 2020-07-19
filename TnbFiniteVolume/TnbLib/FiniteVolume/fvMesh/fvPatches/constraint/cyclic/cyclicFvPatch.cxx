#include <cyclicFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvMesh.hxx>
#include <transform.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicFvPatch, 0);
	addToRunTimeSelectionTable(fvPatch, cyclicFvPatch, polyPatch);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::cyclicFvPatch::makeWeights(scalarField& w) const
{
	const cyclicFvPatch& nbrPatch = neighbFvPatch();

	const vectorField delta(coupledFvPatch::delta());
	const vectorField nbrDelta(nbrPatch.coupledFvPatch::delta());

	const scalarField nfDelta(nf() & delta);
	const scalarField nbrNfDelta(nbrPatch.nf() & nbrDelta);

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


tnbLib::tmp<tnbLib::vectorField> tnbLib::cyclicFvPatch::delta() const
{
	const vectorField patchD(coupledFvPatch::delta());
	const vectorField nbrPatchD(neighbFvPatch().coupledFvPatch::delta());

	tmp<vectorField> tpdv(new vectorField(patchD.size()));
	vectorField& pdv = tpdv.ref();

	// To the transformation if necessary
	if (parallel())
	{
		forAll(patchD, facei)
		{
			vector ddi = patchD[facei];
			vector dni = nbrPatchD[facei];

			pdv[facei] = ddi - dni;
		}
	}
	else
	{
		forAll(patchD, facei)
		{
			vector ddi = patchD[facei];
			vector dni = nbrPatchD[facei];

			pdv[facei] = ddi - transform(forwardT()[0], dni);
		}
	}

	return tpdv;
}


tnbLib::tmp<tnbLib::labelField> tnbLib::cyclicFvPatch::interfaceInternalField
(
	const labelUList& internalData
) const
{
	return patchInternalField(internalData);
}


tnbLib::tmp<tnbLib::labelField> tnbLib::cyclicFvPatch::internalFieldTransfer
(
	const Pstream::commsTypes commsType,
	const labelUList& iF
) const
{
	return neighbFvPatch().patchInternalField(iF);
}


// ************************************************************************* //