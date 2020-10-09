#include <CorrectPhi.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

void tnbLib::correctUphiBCs
(
	volVectorField& U,
	surfaceScalarField& phi,
	const bool evaluateUBCs
)
{
	const fvMesh& mesh = U.mesh();

	if (mesh.changing())
	{
		volVectorField::Boundary& Ubf = U.boundaryFieldRef();
		surfaceScalarField::Boundary& phibf = phi.boundaryFieldRef();

		if (evaluateUBCs)
		{
			forAll(Ubf, patchi)
			{
				if (Ubf[patchi].fixesValue())
				{
					Ubf[patchi].initEvaluate();
				}
			}
		}

		forAll(Ubf, patchi)
		{
			if (Ubf[patchi].fixesValue())
			{
				if (evaluateUBCs)
				{
					Ubf[patchi].evaluate();
				}

				phibf[patchi] = Ubf[patchi] & mesh.Sf().boundaryField()[patchi];
			}
		}
	}
}


void tnbLib::correctUphiBCs
(
	const volScalarField& rho,
	volVectorField& U,
	surfaceScalarField& phi,
	const bool evaluateUBCs
)
{
	const fvMesh& mesh = U.mesh();

	if (mesh.changing())
	{
		volVectorField::Boundary& Ubf = U.boundaryFieldRef();
		surfaceScalarField::Boundary& phibf = phi.boundaryFieldRef();

		if (evaluateUBCs)
		{
			forAll(Ubf, patchi)
			{
				if (Ubf[patchi].fixesValue())
				{
					Ubf[patchi].initEvaluate();
				}
			}
		}

		forAll(Ubf, patchi)
		{
			if (Ubf[patchi].fixesValue())
			{
				if (evaluateUBCs)
				{
					Ubf[patchi].evaluate();
				}

				phibf[patchi] =
					rho.boundaryField()[patchi]
					* (
						Ubf[patchi]
						& mesh.Sf().boundaryField()[patchi]
						);
			}
		}
	}
}


// ************************************************************************* //