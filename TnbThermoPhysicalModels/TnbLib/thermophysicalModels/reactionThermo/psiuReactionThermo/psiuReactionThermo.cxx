#include <psiuReactionThermo.hxx>

#include <fvMesh.hxx>
#include <zeroGradientFvPatchFields.hxx>
#include <fixedUnburntEnthalpyFvPatchScalarField.hxx>
#include <gradientUnburntEnthalpyFvPatchScalarField.hxx>
#include <mixedUnburntEnthalpyFvPatchScalarField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/* * * * * * * * * * * * * * * private static data * * * * * * * * * * * * * */

	defineTypeNameAndDebug(psiuReactionThermo, 0);
	defineRunTimeSelectionTable(psiuReactionThermo, fvMesh);

	// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

	wordList psiuReactionThermo::heuBoundaryTypes()
	{
		const volScalarField::Boundary& tbf =
			this->Tu().boundaryField();

		wordList hbt = tbf.types();

		forAll(tbf, patchi)
		{
			if (isA<fixedValueFvPatchScalarField>(tbf[patchi]))
			{
				hbt[patchi] = fixedUnburntEnthalpyFvPatchScalarField::typeName;
			}
			else if
				(
					isA<zeroGradientFvPatchScalarField>(tbf[patchi])
					|| isA<fixedGradientFvPatchScalarField>(tbf[patchi])
					)
			{
				hbt[patchi] = gradientUnburntEnthalpyFvPatchScalarField::typeName;
			}
			else if (isA<mixedFvPatchScalarField>(tbf[patchi]))
			{
				hbt[patchi] = mixedUnburntEnthalpyFvPatchScalarField::typeName;
			}
		}

		return hbt;
	}

	void psiuReactionThermo::heuBoundaryCorrection(volScalarField& heu)
	{
		volScalarField::Boundary& hbf = heu.boundaryFieldRef();

		forAll(hbf, patchi)
		{
			if
				(
					isA<gradientUnburntEnthalpyFvPatchScalarField>(hbf[patchi])
					)
			{
				refCast<gradientUnburntEnthalpyFvPatchScalarField>(hbf[patchi])
					.gradient() = hbf[patchi].fvPatchField::snGrad();
			}
			else if
				(
					isA<mixedUnburntEnthalpyFvPatchScalarField>(hbf[patchi])
					)
			{
				refCast<mixedUnburntEnthalpyFvPatchScalarField>(hbf[patchi])
					.refGrad() = hbf[patchi].fvPatchField::snGrad();
			}
		}
	}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	psiuReactionThermo::psiuReactionThermo
	(
		const fvMesh& mesh,
		const word& phaseName
	)
		:
		psiReactionThermo(mesh, phaseName)
	{}


	// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

	tnbLib::autoPtr<tnbLib::psiuReactionThermo> tnbLib::psiuReactionThermo::New
	(
		const fvMesh& mesh,
		const word& phaseName
	)
	{
		return basicThermo::New<psiuReactionThermo>(mesh, phaseName);
	}


	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	psiuReactionThermo::~psiuReactionThermo()
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //