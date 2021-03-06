#include <externalCoupledTemperatureMixedFvPatchScalarField.hxx>

#include <turbulentFluidThermoModel.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <OFstream.hxx>

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::externalCoupledTemperatureMixedFvPatchScalarField::writeHeader
(
	OFstream& os
) const
{
	os << "# Values: magSf value qDot htc" << endl;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::externalCoupledTemperatureMixedFvPatchScalarField::
externalCoupledTemperatureMixedFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	externalCoupledMixedFvPatchField<scalar>(p, iF)
{}


tnbLib::externalCoupledTemperatureMixedFvPatchScalarField::
externalCoupledTemperatureMixedFvPatchScalarField
(
	const externalCoupledTemperatureMixedFvPatchScalarField& ptf,
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	externalCoupledMixedFvPatchField<scalar>(ptf, p, iF, mapper)
{}


tnbLib::externalCoupledTemperatureMixedFvPatchScalarField::
externalCoupledTemperatureMixedFvPatchScalarField
(
	const fvPatch& p,
	const DimensionedField<scalar, volMesh>& iF,
	const dictionary& dict
)
	:
	externalCoupledMixedFvPatchField<scalar>(p, iF, dict)
{}


tnbLib::externalCoupledTemperatureMixedFvPatchScalarField::
externalCoupledTemperatureMixedFvPatchScalarField
(
	const externalCoupledTemperatureMixedFvPatchScalarField& ecmpf
)
	:
	externalCoupledMixedFvPatchField<scalar>(ecmpf)
{}


tnbLib::externalCoupledTemperatureMixedFvPatchScalarField::
externalCoupledTemperatureMixedFvPatchScalarField
(
	const externalCoupledTemperatureMixedFvPatchScalarField& ecmpf,
	const DimensionedField<scalar, volMesh>& iF
)
	:
	externalCoupledMixedFvPatchField<scalar>(ecmpf, iF)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::externalCoupledTemperatureMixedFvPatchScalarField::
~externalCoupledTemperatureMixedFvPatchScalarField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::externalCoupledTemperatureMixedFvPatchScalarField::transferData
(
	OFstream& os
) const
{
	if (log())
	{
		Info << type() << ": " << this->patch().name()
			<< ": writing data to " << os.name()
			<< endl;
	}

	const label patchi = patch().index();

	// heat flux [W/m^2]
	scalarField qDot(this->patch().size(), 0.0);

	typedef compressible::turbulenceModel cmpTurbModelType;

	static word turbName
	(
		IOobject::groupName
		(
			turbulenceModel::propertiesName,
			internalField().group()
		)
	);

	static word thermoName(basicThermo::dictName);

	if (db().foundObject<cmpTurbModelType>(turbName))
	{
		const cmpTurbModelType& turbModel =
			db().lookupObject<cmpTurbModelType>(turbName);

		const basicThermo& thermo = turbModel.transport();

		const fvPatchScalarField& hep = thermo.he().boundaryField()[patchi];

		qDot = turbModel.alphaEff(patchi)*hep.snGrad();
	}
	else if (db().foundObject<basicThermo>(thermoName))
	{
		const basicThermo& thermo = db().lookupObject<basicThermo>(thermoName);

		const fvPatchScalarField& hep = thermo.he().boundaryField()[patchi];

		qDot = thermo.alpha().boundaryField()[patchi] * hep.snGrad();
	}
	else
	{
		FatalErrorInFunction
			<< "Condition requires either compressible turbulence and/or "
			<< "thermo model to be available" << exit(FatalError);
	}

	// patch temperature [K]
	const scalarField Tp(*this);

	// near wall cell temperature [K]
	const scalarField Tc(patchInternalField());

	// heat transfer coefficient [W/m^2/K]
	const scalarField htc(qDot / (Tp - Tc + rootVSmall));

	if (Pstream::parRun())
	{
		int tag = Pstream::msgType() + 1;

		List<Field<scalar>> magSfs(Pstream::nProcs());
		magSfs[Pstream::myProcNo()].setSize(this->patch().size());
		magSfs[Pstream::myProcNo()] = this->patch().magSf();
		Pstream::gatherList(magSfs, tag);

		List<Field<scalar>> values(Pstream::nProcs());
		values[Pstream::myProcNo()].setSize(this->patch().size());
		values[Pstream::myProcNo()] = Tp;
		Pstream::gatherList(values, tag);

		List<Field<scalar>> qDots(Pstream::nProcs());
		qDots[Pstream::myProcNo()].setSize(this->patch().size());
		qDots[Pstream::myProcNo()] = qDot;
		Pstream::gatherList(qDots, tag);

		List<Field<scalar>> htcs(Pstream::nProcs());
		htcs[Pstream::myProcNo()].setSize(this->patch().size());
		htcs[Pstream::myProcNo()] = htc;
		Pstream::gatherList(htcs, tag);

		if (Pstream::master())
		{
			forAll(values, proci)
			{
				const Field<scalar>& magSf = magSfs[proci];
				const Field<scalar>& value = values[proci];
				const Field<scalar>& qDot = qDots[proci];
				const Field<scalar>& htc = htcs[proci];

				forAll(magSf, facei)
				{
					os << magSf[facei] << token::SPACE
						<< value[facei] << token::SPACE
						<< qDot[facei] << token::SPACE
						<< htc[facei] << token::SPACE
						<< nl;
				}
			}

			os.flush();
		}
	}
	else
	{
		const Field<scalar>& magSf(this->patch().magSf());

		forAll(patch(), facei)
		{
			os << magSf[facei] << token::SPACE
				<< Tp[facei] << token::SPACE
				<< qDot[facei] << token::SPACE
				<< htc[facei] << token::SPACE
				<< nl;
		}

		os.flush();
	}
}


void tnbLib::externalCoupledTemperatureMixedFvPatchScalarField::evaluate
(
	const Pstream::commsTypes comms
)
{
	externalCoupledMixedFvPatchField<scalar>::evaluate(comms);
}


void tnbLib::externalCoupledTemperatureMixedFvPatchScalarField::write
(
	Ostream& os
) const
{
	externalCoupledMixedFvPatchField<scalar>::write(os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchScalarField,
		externalCoupledTemperatureMixedFvPatchScalarField
	);
}


// ************************************************************************* //