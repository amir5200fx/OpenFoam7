#include <adjustPhi.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <inletOutletFvPatchFields.hxx>

#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

bool tnbLib::adjustPhi
(
	surfaceScalarField& phi,
	const volVectorField& U,
	volScalarField& p
)
{
	if (p.needReference())
	{
		scalar massIn = 0.0;
		scalar fixedMassOut = 0.0;
		scalar adjustableMassOut = 0.0;

		surfaceScalarField::Boundary& bphi =
			phi.boundaryFieldRef();

		forAll(bphi, patchi)
		{
			const fvPatchVectorField& Up = U.boundaryField()[patchi];
			const fvsPatchScalarField& phip = bphi[patchi];

			if (!phip.coupled())
			{
				if (Up.fixesValue() && !isA<inletOutletFvPatchVectorField>(Up))
				{
					forAll(phip, i)
					{
						if (phip[i] < 0.0)
						{
							massIn -= phip[i];
						}
						else
						{
							fixedMassOut += phip[i];
						}
					}
				}
				else
				{
					forAll(phip, i)
					{
						if (phip[i] < 0.0)
						{
							massIn -= phip[i];
						}
						else
						{
							adjustableMassOut += phip[i];
						}
					}
				}
			}
		}

		// Calculate the total flux in the domain, used for normalisation
		scalar totalFlux = vSmall + sum(mag(phi)).value();

		reduce(massIn, sumOp<scalar>());
		reduce(fixedMassOut, sumOp<scalar>());
		reduce(adjustableMassOut, sumOp<scalar>());

		scalar massCorr = 1.0;
		scalar magAdjustableMassOut = mag(adjustableMassOut);

		if
			(
				magAdjustableMassOut > vSmall
				&& magAdjustableMassOut / totalFlux > small
				)
		{
			massCorr = (massIn - fixedMassOut) / adjustableMassOut;
		}
		else if (mag(fixedMassOut - massIn) / totalFlux > 1e-8)
		{
			FatalErrorInFunction
				<< "Continuity error cannot be removed by adjusting the"
				" outflow.\nPlease check the velocity boundary conditions"
				" and/or run potentialFoam to initialise the outflow." << nl
				<< "Total flux              : " << totalFlux << nl
				<< "Specified mass inflow   : " << massIn << nl
				<< "Specified mass outflow  : " << fixedMassOut << nl
				<< "Adjustable mass outflow : " << adjustableMassOut << nl
				<< exit(FatalError);
		}

		forAll(bphi, patchi)
		{
			const fvPatchVectorField& Up = U.boundaryField()[patchi];
			fvsPatchScalarField& phip = bphi[patchi];

			if (!phip.coupled())
			{
				if
					(
						!Up.fixesValue()
						|| isA<inletOutletFvPatchVectorField>(Up)
						)
				{
					forAll(phip, i)
					{
						if (phip[i] > 0.0)
						{
							phip[i] *= massCorr;
						}
					}
				}
			}
		}

		return mag(massIn) / totalFlux < small
			&& mag(fixedMassOut) / totalFlux < small
			&& mag(adjustableMassOut) / totalFlux < small;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //