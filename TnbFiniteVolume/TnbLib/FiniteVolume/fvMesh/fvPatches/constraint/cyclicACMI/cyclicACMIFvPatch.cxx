#include <cyclicACMIFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvMesh.hxx>
#include <transform.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cyclicACMIFvPatch, 0);
	addToRunTimeSelectionTable(fvPatch, cyclicACMIFvPatch, polyPatch);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::cyclicACMIFvPatch::updateAreas() const
{
	if (cyclicACMIPatch().updated())
	{
		if (debug)
		{
			Pout << "cyclicACMIFvPatch::updateAreas() : updating fv areas for "
				<< name() << " and " << nonOverlapFvPatch().name()
				<< endl;
		}

		// owner couple
		const_cast<vectorField&>(Sf()) = patch().faceAreas();
		const_cast<scalarField&>(magSf()) = mag(patch().faceAreas());

		// owner non-overlapping
		const fvPatch& nonOverlapPatch = nonOverlapFvPatch();
		const_cast<vectorField&>(nonOverlapPatch.Sf()) =
			nonOverlapPatch.patch().faceAreas();
		const_cast<scalarField&>(nonOverlapPatch.magSf()) =
			mag(nonOverlapPatch.patch().faceAreas());

		// neighbour couple
		const cyclicACMIFvPatch& nbrACMI = neighbFvPatch();
		const_cast<vectorField&>(nbrACMI.Sf()) =
			nbrACMI.patch().faceAreas();
		const_cast<scalarField&>(nbrACMI.magSf()) =
			mag(nbrACMI.patch().faceAreas());

		// neighbour non-overlapping
		const fvPatch& nbrNonOverlapPatch = nbrACMI.nonOverlapFvPatch();
		const_cast<vectorField&>(nbrNonOverlapPatch.Sf()) =
			nbrNonOverlapPatch.patch().faceAreas();
		const_cast<scalarField&>(nbrNonOverlapPatch.magSf()) =
			mag(nbrNonOverlapPatch.patch().faceAreas());

		// set the updated flag
		cyclicACMIPatch().setUpdated(false);
	}
}


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

void tnbLib::cyclicACMIFvPatch::makeWeights(scalarField& w) const
{
	if (coupled())
	{
		// These deltas are of the cyclic part alone - they are
		// not affected by the amount of overlap with the nonOverlapPatch
		const scalarField deltan(this->deltan());
		const scalarField nbrDeltan(this->nbrDeltan());

		forAll(deltan, facei)
		{
			scalar di = deltan[facei];
			scalar dni = nbrDeltan[facei];

			if (dni < cyclicACMIPolyPatch::tolerance())
			{
				// Avoid zero weights on disconnected faces. This value
				// will be weighted with the (zero) face area so will not
				// influence calculations.
				w[facei] = 1.0;
			}
			else
			{
				w[facei] = dni / (di + dni);
			}
		}
	}
	else
	{
		// Behave as uncoupled patch
		fvPatch::makeWeights(w);
	}
}


// ************************************************************************* //