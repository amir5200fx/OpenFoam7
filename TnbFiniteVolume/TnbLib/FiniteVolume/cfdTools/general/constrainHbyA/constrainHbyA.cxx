#include <constrainHbyA.hxx>

#include <volFields.hxx>
#include <fixedFluxExtrapolatedPressureFvPatchScalarField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volVectorField> tnbLib::constrainHbyA
(
	const tmp<volVectorField>& tHbyA,
	const volVectorField& U,
	const volScalarField& p
)
{
	tmp<volVectorField> tHbyANew;

	if (tHbyA.isTmp())
	{
		tHbyANew = tHbyA;
		tHbyANew.ref().rename("HbyA");
	}
	else
	{
		tHbyANew = new volVectorField("HbyA", tHbyA);
	}

	volVectorField& HbyA = tHbyANew.ref();
	volVectorField::Boundary& HbyAbf = HbyA.boundaryFieldRef();

	forAll(U.boundaryField(), patchi)
	{
		if
			(
				!U.boundaryField()[patchi].assignable()
				&& !isA<fixedFluxExtrapolatedPressureFvPatchScalarField>
				(
					p.boundaryField()[patchi]
					)
				)
		{
			HbyAbf[patchi] = U.boundaryField()[patchi];
		}
	}

	return tHbyANew;
}


// ************************************************************************* //