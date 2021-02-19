#include <solidificationMeltingSource.hxx>

#include <fvMatrices.hxx>
#include <basicThermo.hxx>
#include <uniformDimensionedFields.hxx>
#include <zeroGradientFvPatchFields.hxx>
#include <extrapolatedCalculatedFvPatchFields.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <geometricOneField.hxx>

// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

namespace tnbLib
{
	/*template<>
	const char* NamedEnum
		<
		fv::solidificationMeltingSource::thermoMode,
		2
		>::names[] =
	{
		"thermo",
		"lookup"
	};*/

	namespace fv
	{
		defineTypeNameAndDebug(solidificationMeltingSource, 0);

		addToRunTimeSelectionTable
		(
			option,
			solidificationMeltingSource,
			dictionary
		);
	}
}

const tnbLib::NamedEnum<tnbLib::fv::solidificationMeltingSource::thermoMode, 2>
tnbLib::fv::solidificationMeltingSource::thermoModeTypeNames_;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::fv::solidificationMeltingSource::Cp() const
{
	switch (mode_)
	{
	case mdThermo:
	{
		const basicThermo& thermo =
			mesh_.lookupObject<basicThermo>(basicThermo::dictName);

		return thermo.Cp();
		break;
	}
	case mdLookup:
	{
		if (CpName_ == "CpRef")
		{
			scalar CpRef = readScalar(coeffs_.lookup("CpRef"));

			return volScalarField::New
			(
				name_ + ":Cp",
				mesh_,
				dimensionedScalar
				(
					dimEnergy / dimMass / dimTemperature,
					CpRef
				),
				extrapolatedCalculatedFvPatchScalarField::typeName
			);
		}
		else
		{
			return mesh_.lookupObject<volScalarField>(CpName_);
		}

		break;
	}
	default:
	{
		FatalErrorInFunction
			<< "Unhandled thermo mode: " << thermoModeTypeNames_[mode_]
			<< abort(FatalError);
	}
	}

	return tmp<volScalarField>(nullptr);
}


tnbLib::vector tnbLib::fv::solidificationMeltingSource::g() const
{
	if (mesh_.foundObject<uniformDimensionedVectorField>("g"))
	{
		const uniformDimensionedVectorField& value =
			mesh_.lookupObject<uniformDimensionedVectorField>("g");
		return value.value();
	}
	else
	{
		return coeffs_.lookup("g");
	}
}


void tnbLib::fv::solidificationMeltingSource::update(const volScalarField& Cp)
{
	if (curTimeIndex_ == mesh_.time().timeIndex())
	{
		return;
	}

	if (debug)
	{
		Info << type() << ": " << name_ << " - updating phase indicator" << endl;
	}

	// update old time alpha1 field
	alpha1_.oldTime();

	const volScalarField& T = mesh_.lookupObject<volScalarField>(TName_);

	forAll(cells_, i)
	{
		const label celli = cells_[i];

		const scalar Tc = T[celli];
		const scalar Cpc = Cp[celli];
		const scalar alpha1New =
			alpha1_[celli]
			+ relax_ * Cpc
			*(
				Tc
				- max
				(
					Tsol_,
					Tsol_
					+ (Tliq_ - Tsol_)*(alpha1_[celli] - alpha1e_) / (1 - alpha1e_)
				)
				) / L_;

		alpha1_[celli] = max(0, min(alpha1New, 1));
		deltaT_[i] =
			Tc
			- max
			(
				Tsol_,
				Tsol_
				+ (Tliq_ - Tsol_)*(alpha1_[celli] - alpha1e_) / (1 - alpha1e_)
			);
	}

	alpha1_.correctBoundaryConditions();

	curTimeIndex_ = mesh_.time().timeIndex();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::solidificationMeltingSource::solidificationMeltingSource
(
	const word& sourceName,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	cellSetOption(sourceName, modelType, dict, mesh),
	Tsol_(readScalar(coeffs_.lookup("Tsol"))),
	Tliq_(coeffs_.lookupOrDefault("Tliq", Tsol_)),
	alpha1e_(coeffs_.lookupOrDefault("alpha1e", 0.0)),
	L_(readScalar(coeffs_.lookup("L"))),
	relax_(coeffs_.lookupOrDefault("relax", 0.9)),
	mode_(thermoModeTypeNames_.read(coeffs_.lookup("thermoMode"))),
	rhoRef_(readScalar(coeffs_.lookup("rhoRef"))),
	TName_(coeffs_.lookupOrDefault<word>("T", "T")),
	CpName_(coeffs_.lookupOrDefault<word>("Cp", "Cp")),
	UName_(coeffs_.lookupOrDefault<word>("U", "U")),
	phiName_(coeffs_.lookupOrDefault<word>("phi", "phi")),
	Cu_(coeffs_.lookupOrDefault<scalar>("Cu", 100000)),
	q_(coeffs_.lookupOrDefault("q", 0.001)),
	beta_(readScalar(coeffs_.lookup("beta"))),
	alpha1_
	(
		IOobject
		(
			name_ + ":alpha1",
			mesh.time().timeName(),
			mesh,
			IOobject::READ_IF_PRESENT,
			IOobject::AUTO_WRITE
		),
		mesh,
		dimensionedScalar(dimless, 0),
		zeroGradientFvPatchScalarField::typeName
	),
	curTimeIndex_(-1),
	deltaT_(cells_.size(), 0)
{
	fieldNames_.setSize(2);
	fieldNames_[0] = UName_;

	switch (mode_)
	{
	case mdThermo:
	{
		const basicThermo& thermo =
			mesh_.lookupObject<basicThermo>(basicThermo::dictName);

		fieldNames_[1] = thermo.he().name();
		break;
	}
	case mdLookup:
	{
		fieldNames_[1] = TName_;
		break;
	}
	default:
	{
		FatalErrorInFunction
			<< "Unhandled thermo mode: " << thermoModeTypeNames_[mode_]
			<< abort(FatalError);
	}
	}

	applied_.setSize(fieldNames_.size(), false);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fv::solidificationMeltingSource::addSup
(
	fvMatrix<scalar>& eqn,
	const label fieldi
)
{
	apply(geometricOneField(), eqn);
}


void tnbLib::fv::solidificationMeltingSource::addSup
(
	const volScalarField& rho,
	fvMatrix<scalar>& eqn,
	const label fieldi
)
{
	apply(rho, eqn);
}


void tnbLib::fv::solidificationMeltingSource::addSup
(
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	if (debug)
	{
		Info << type() << ": applying source to " << eqn.psi().name() << endl;
	}

	const volScalarField Cp(this->Cp());

	update(Cp);

	vector g = this->g();

	scalarField& Sp = eqn.diag();
	vectorField& Su = eqn.source();
	const scalarField& V = mesh_.V();

	forAll(cells_, i)
	{
		const label celli = cells_[i];

		const scalar Vc = V[celli];
		const scalar alpha1c = alpha1_[celli];

		const scalar S = -Cu_ * sqr(1.0 - alpha1c) / (pow3(alpha1c) + q_);
		const vector Sb = rhoRef_ * g*beta_*deltaT_[i];

		Sp[celli] += Vc * S;
		Su[celli] += Vc * Sb;
	}
}


void tnbLib::fv::solidificationMeltingSource::addSup
(
	const volScalarField& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	// Momentum source uses a Boussinesq approximation - redirect
	addSup(eqn, fieldi);
}


// ************************************************************************* //