#include <UOprocess.hxx>

#include <Kmesh.hxx>
#include <dictionary.hxx>
#include <error.hxx>
#include <OSstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	complexVector UOprocess::WeinerProcess()
	{
		return RootDeltaT * complexVector
		(
			complex(GaussGen.scalarNormal(), GaussGen.scalarNormal()),
			complex(GaussGen.scalarNormal(), GaussGen.scalarNormal()),
			complex(GaussGen.scalarNormal(), GaussGen.scalarNormal())
		);
	}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// from components
	UOprocess::UOprocess
	(
		const Kmesh& kmesh,
		const scalar deltaT,
		const dictionary& UOdict
	)
		:
		GaussGen(label(0)),
		Mesh(kmesh),
		DeltaT(deltaT),
		RootDeltaT(sqrt(DeltaT)),
		UOfield(Mesh.size()),

		Alpha(readScalar(UOdict.lookup("UOalpha"))),
		Sigma(readScalar(UOdict.lookup("UOsigma"))),
		Kupper(readScalar(UOdict.lookup("UOKupper"))),
		Klower(readScalar(UOdict.lookup("UOKlower"))),
		Scale((Kupper - Klower)*pow(scalar(Mesh.size()), 1.0 / vector::dim))
	{
		const vectorField& K = Mesh;

		scalar sqrKupper = sqr(Kupper);
		scalar sqrKlower = sqr(Klower) + small;
		scalar sqrK;

		forAll(UOfield, i)
		{
			if ((sqrK = magSqr(K[i])) < sqrKupper && sqrK > sqrKlower)
			{
				UOfield[i] = Scale * Sigma*WeinerProcess();
			}
			else
			{
				UOfield[i] = complexVector
				(
					complex(0, 0),
					complex(0, 0),
					complex(0, 0)
				);
			}
		}
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	const complexVectorField& UOprocess::newField()
	{
		const vectorField& K = Mesh;

		label count = 0;
		scalar sqrKupper = sqr(Kupper);
		scalar sqrKlower = sqr(Klower) + small;
		scalar sqrK;

		forAll(UOfield, i)
		{
			if ((sqrK = magSqr(K[i])) < sqrKupper && sqrK > sqrKlower)
			{
				count++;
				UOfield[i] =
					(1.0 - Alpha * DeltaT)*UOfield[i]
					+ Scale * Sigma*WeinerProcess();
			}
		}

		Info << "    Number of forced K = " << count << nl;

		return UOfield;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //