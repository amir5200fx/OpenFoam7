#define FoamNamedEnum_EXPORT_DEFINE

#include <fixedTemperatureConstraint.hxx>

#include <fvMesh.hxx>
#include <fvMatrices.hxx>
#include <basicThermo.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(fixedTemperatureConstraint, 0);
		addToRunTimeSelectionTable
		(
			option,
			fixedTemperatureConstraint,
			dictionary
		);
	}

	template<>
	const char* NamedEnum<fv::fixedTemperatureConstraint::temperatureMode, 2>::
		names[] =
	{
		"uniform",
		"lookup"
	};
}

const tnbLib::NamedEnum<tnbLib::fv::fixedTemperatureConstraint::temperatureMode, 2>
tnbLib::fv::fixedTemperatureConstraint::temperatureModeNames_;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::fixedTemperatureConstraint::fixedTemperatureConstraint
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	cellSetOption(name, modelType, dict, mesh),
	mode_(temperatureModeNames_.read(coeffs_.lookup("mode"))),
	Tuniform_(nullptr),
	TName_("T")
{
	switch (mode_)
	{
	case tmUniform:
	{
		Tuniform_.reset
		(
			Function1<scalar>::New("temperature", coeffs_).ptr()
		);
		break;
	}
	case tmLookup:
	{
		TName_ = coeffs_.lookupOrDefault<word>("T", "T");
		break;
	}
	default:
	{
		// error handling done by NamedEnum
	}
	}


	// Set the field name to that of the energy field from which the temperature
	// is obtained

	const basicThermo& thermo =
		mesh_.lookupObject<basicThermo>(basicThermo::dictName);

	fieldNames_.setSize(1, thermo.he().name());

	applied_.setSize(1, false);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fv::fixedTemperatureConstraint::constrain
(
	fvMatrix<scalar>& eqn,
	const label
)
{
	const basicThermo& thermo =
		mesh_.lookupObject<basicThermo>(basicThermo::dictName);

	switch (mode_)
	{
	case tmUniform:
	{
		const scalar t = mesh_.time().value();
		scalarField Tuni(cells_.size(), Tuniform_->value(t));
		eqn.setValues(cells_, thermo.he(thermo.p(), Tuni, cells_));

		break;
	}
	case tmLookup:
	{
		const volScalarField& T =
			mesh().lookupObject<volScalarField>(TName_);

		scalarField Tlkp(T, cells_);
		eqn.setValues(cells_, thermo.he(thermo.p(), Tlkp, cells_));

		break;
	}
	default:
	{
		// error handling done by NamedEnum
	}
	}
}


bool tnbLib::fv::fixedTemperatureConstraint::read(const dictionary& dict)
{
	if (cellSetOption::read(dict))
	{
		if (coeffs_.found(Tuniform_->name()))
		{
			Tuniform_.reset
			(
				Function1<scalar>::New(Tuniform_->name(), dict).ptr()
			);
		}

		coeffs_.readIfPresent("T", TName_);

		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //