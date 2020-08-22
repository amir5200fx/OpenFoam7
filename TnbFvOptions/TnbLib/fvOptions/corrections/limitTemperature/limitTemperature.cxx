#include <limitTemperature.hxx>

#include <fvMesh.hxx>
#include <basicThermo.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(limitTemperature, 0);
		addToRunTimeSelectionTable
		(
			option,
			limitTemperature,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::limitTemperature::limitTemperature
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	cellSetOption(name, modelType, dict, mesh),
	Tmin_(readScalar(coeffs_.lookup("min"))),
	Tmax_(readScalar(coeffs_.lookup("max"))),
	phase_(coeffs_.lookupOrDefault<word>("phase", word::null))
{
	// Set the field name to that of the energy field from which the temperature
	// is obtained
	const basicThermo& thermo =
		mesh_.lookupObject<basicThermo>
		(
			IOobject::groupName(basicThermo::dictName, phase_)
			);

	fieldNames_.setSize(1, thermo.he().name());

	applied_.setSize(1, false);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::fv::limitTemperature::read(const dictionary& dict)
{
	if (cellSetOption::read(dict))
	{
		coeffs_.lookup("min") >> Tmin_;
		coeffs_.lookup("max") >> Tmax_;

		return true;
	}
	else
	{
		return false;
	}
}


void tnbLib::fv::limitTemperature::correct(volScalarField& he)
{
	const basicThermo& thermo =
		mesh_.lookupObject<basicThermo>
		(
			IOobject::groupName(basicThermo::dictName, phase_)
			);

	scalarField Tmin(cells_.size(), Tmin_);
	scalarField Tmax(cells_.size(), Tmax_);

	scalarField heMin(thermo.he(thermo.p(), Tmin, cells_));
	scalarField heMax(thermo.he(thermo.p(), Tmax, cells_));

	scalarField& hec = he.primitiveFieldRef();

	forAll(cells_, i)
	{
		label celli = cells_[i];
		hec[celli] = max(min(hec[celli], heMax[i]), heMin[i]);
	}

	// handle boundaries in the case of 'all'
	if (selectionMode_ == smAll)
	{
		volScalarField::Boundary& bf = he.boundaryFieldRef();

		forAll(bf, patchi)
		{
			fvPatchScalarField& hep = bf[patchi];

			if (!hep.fixesValue())
			{
				const scalarField& pp = thermo.p().boundaryField()[patchi];

				scalarField Tminp(pp.size(), Tmin_);
				scalarField Tmaxp(pp.size(), Tmax_);

				scalarField heMinp(thermo.he(pp, Tminp, patchi));
				scalarField heMaxp(thermo.he(pp, Tmaxp, patchi));

				forAll(hep, facei)
				{
					hep[facei] =
						max(min(hep[facei], heMaxp[facei]), heMinp[facei]);
				}
			}
		}
	}
}


// ************************************************************************* //