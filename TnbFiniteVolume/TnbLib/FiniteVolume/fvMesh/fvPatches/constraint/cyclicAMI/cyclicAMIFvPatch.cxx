#include <cyclicAMIFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvMesh.hxx>
#include <Time.hxx>
#include <transform.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicAMIFvPatch, 0);
	addToRunTimeSelectionTable(fvPatch, cyclicAMIFvPatch, polyPatch);
}


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField> tnbLib::cyclicAMIFvPatch::deltan() const
{
	return nf() & coupledFvPatch::delta();
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::cyclicAMIFvPatch::nbrDeltan() const
{
	if (coupled())
	{
		const cyclicAMIFvPatch& nbrPatch = neighbFvPatch();

		tmp<scalarField> tnbrDeltan;
		if (applyLowWeightCorrection())
		{
			tnbrDeltan =
				interpolate
				(
					nbrPatch.nf() & nbrPatch.coupledFvPatch::delta(),
					scalarField(this->size(), 1.0)
				);
		}
		else
		{
			tnbrDeltan =
				interpolate(nbrPatch.nf() & nbrPatch.coupledFvPatch::delta());
		}

		return tnbrDeltan;
	}
	else
	{
		return tmp<scalarField>();
	}
}


void tnbLib::cyclicAMIFvPatch::makeWeights(scalarField& w) const
{
	if (coupled())
	{
		const scalarField deltan(this->deltan());
		const scalarField nbrDeltan(this->nbrDeltan());

		forAll(deltan, facei)
		{
			scalar di = deltan[facei];
			scalar dni = nbrDeltan[facei];

			w[facei] = dni / (di + dni);
		}
	}
	else
	{
		// Behave as uncoupled patch
		fvPatch::makeWeights(w);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::cyclicAMIFvPatch::coupled() const
{
	return
		Pstream::parRun()
		|| !this->boundaryMesh().mesh().time().processorCase();
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::cyclicAMIFvPatch::delta() const
{
	const cyclicAMIFvPatch& nbrPatch = neighbFvPatch();

	if (coupled())
	{
		const vectorField patchD(coupledFvPatch::delta());

		tmp<vectorField> tnbrPatchD;
		if (applyLowWeightCorrection())
		{
			tnbrPatchD =
				interpolate
				(
					nbrPatch.coupledFvPatch::delta(),
					vectorField(this->size(), Zero)
				);
		}
		else
		{
			tnbrPatchD = interpolate(nbrPatch.coupledFvPatch::delta());
		}

		const vectorField& nbrPatchD = tnbrPatchD();

		tmp<vectorField> tpdv(new vectorField(patchD.size()));
		vectorField& pdv = tpdv.ref();

		// do the transformation if necessary
		if (parallel())
		{
			forAll(patchD, facei)
			{
				const vector& ddi = patchD[facei];
				const vector& dni = nbrPatchD[facei];

				pdv[facei] = ddi - dni;
			}
		}
		else
		{
			forAll(patchD, facei)
			{
				const vector& ddi = patchD[facei];
				const vector& dni = nbrPatchD[facei];

				pdv[facei] = ddi - transform(forwardT()[0], dni);
			}
		}

		return tpdv;
	}
	else
	{
		return coupledFvPatch::delta();
	}
}


tnbLib::tmp<tnbLib::labelField> tnbLib::cyclicAMIFvPatch::interfaceInternalField
(
	const labelUList& internalData
) const
{
	return patchInternalField(internalData);
}


tnbLib::tmp<tnbLib::labelField> tnbLib::cyclicAMIFvPatch::internalFieldTransfer
(
	const Pstream::commsTypes commsType,
	const labelUList& iF
) const
{
	return neighbFvPatch().patchInternalField(iF);
}


// ************************************************************************* //