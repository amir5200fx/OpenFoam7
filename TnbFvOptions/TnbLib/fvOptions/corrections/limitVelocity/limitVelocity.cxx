#include <limitVelocity.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(limitVelocity, 0);
		addToRunTimeSelectionTable
		(
			option,
			limitVelocity,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::limitVelocity::limitVelocity
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	cellSetOption(name, modelType, dict, mesh),
	UName_(coeffs_.lookupOrDefault<word>("U", "U")),
	max_(readScalar(coeffs_.lookup("max")))
{
	fieldNames_.setSize(1, UName_);
	applied_.setSize(1, false);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::fv::limitVelocity::read(const dictionary& dict)
{
	if (cellSetOption::read(dict))
	{
		coeffs_.lookup("max") >> max_;

		return true;
	}
	else
	{
		return false;
	}
}


void tnbLib::fv::limitVelocity::correct(volVectorField& U)
{
	const scalar maxSqrU = sqr(max_);

	vectorField& Uif = U.primitiveFieldRef();

	forAll(cells_, i)
	{
		const label celli = cells_[i];

		const scalar magSqrUi = magSqr(Uif[celli]);

		if (magSqrUi > maxSqrU)
		{
			Uif[celli] *= sqrt(maxSqrU / magSqrUi);
		}
	}

	// handle boundaries in the case of 'all'
	if (selectionMode_ == smAll)
	{
		volVectorField::Boundary& Ubf = U.boundaryFieldRef();

		forAll(Ubf, patchi)
		{
			fvPatchVectorField& Up = Ubf[patchi];

			if (!Up.fixesValue())
			{
				forAll(Up, facei)
				{
					const scalar magSqrUi = magSqr(Up[facei]);

					if (magSqrUi > maxSqrU)
					{
						Up[facei] *= sqrt(maxSqrU / magSqrUi);
					}
				}
			}
		}
	}
}


// ************************************************************************* //