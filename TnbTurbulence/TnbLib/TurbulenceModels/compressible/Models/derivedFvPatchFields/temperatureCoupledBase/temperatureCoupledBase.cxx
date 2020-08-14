#include <temperatureCoupledBase.hxx>

#include <volFields.hxx>
#include <fluidThermo.hxx>
#include <solidThermo.hxx>
#include <turbulentFluidThermoModel.hxx>

// * * * * * * * * * * * * * Static Member Data  * * * * * * * * * * * * * * //

namespace tnbLib
{
	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::temperatureCoupledBase::KMethodType,
		4
		>::names[] =
	{
		"fluidThermo",
		"solidThermo",
		"directionalSolidThermo",
		"lookup"
	};
}


const tnbLib::NamedEnum<tnbLib::temperatureCoupledBase::KMethodType, 4>
tnbLib::temperatureCoupledBase::KMethodTypeNames_;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::temperatureCoupledBase::temperatureCoupledBase
(
	const fvPatch& patch,
	const word& calculationType,
	const word& kappaName,
	const word& alphaAniName
)
	:
	patch_(patch),
	method_(KMethodTypeNames_[calculationType]),
	kappaName_(kappaName),
	alphaAniName_(alphaAniName)
{}


tnbLib::temperatureCoupledBase::temperatureCoupledBase
(
	const fvPatch& patch,
	const dictionary& dict
)
	:
	patch_(patch),
	method_(KMethodTypeNames_.read(dict.lookup("kappaMethod"))),
	kappaName_(dict.lookupOrDefault<word>("kappa", "none")),
	alphaAniName_(dict.lookupOrDefault<word>("alphaAni", "Anialpha"))
{
	switch (method_)
	{
	case mtDirectionalSolidThermo:
	{
		if (!dict.found("alphaAni"))
		{
			FatalIOErrorInFunction(dict)
				<< "Did not find entry 'alphaAni'"
				" required for 'kappaMethod' "
				<< KMethodTypeNames_[method_]
				<< exit(FatalIOError);
		}

		break;
	}

	case mtLookup:
	{
		if (!dict.found("kappa"))
		{
			FatalIOErrorInFunction(dict)
				<< "Did not find entry 'kappa'"
				" required for 'kappaMethod' "
				<< KMethodTypeNames_[method_] << nl
				<< "    Please set 'kappa' to the name of a volScalarField"
				" or volSymmTensorField"
				<< exit(FatalIOError);
		}

		break;
	}

	default:
		break;
	}
}


tnbLib::temperatureCoupledBase::temperatureCoupledBase
(
	const fvPatch& patch,
	const temperatureCoupledBase& base
)
	:
	patch_(patch),
	method_(base.method_),
	kappaName_(base.kappaName_),
	alphaAniName_(base.alphaAniName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField> tnbLib::temperatureCoupledBase::kappa
(
	const scalarField& Tp
) const
{
	const fvMesh& mesh = patch_.boundaryMesh().mesh();
	const label patchi = patch_.index();

	switch (method_)
	{
	case mtFluidThermo:
	{
		typedef compressible::turbulenceModel turbulenceModel;

		word turbName(turbulenceModel::propertiesName);

		if
			(
				mesh.foundObject<turbulenceModel>(turbName)
				)
		{
			const turbulenceModel& turbModel =
				mesh.lookupObject<turbulenceModel>(turbName);

			return turbModel.kappaEff(patchi);
		}
		else if (mesh.foundObject<fluidThermo>(basicThermo::dictName))
		{
			const fluidThermo& thermo =
				mesh.lookupObject<fluidThermo>(basicThermo::dictName);

			return thermo.kappa(patchi);
		}
		else
		{
			FatalErrorInFunction
				<< "kappaMethod defined to employ "
				<< KMethodTypeNames_[method_]
				<< " method, but thermo package not available"
				<< exit(FatalError);
		}

		break;
	}

	case mtSolidThermo:
	{
		const solidThermo& thermo =
			mesh.lookupObject<solidThermo>(basicThermo::dictName);

		return thermo.kappa(patchi);
		break;
	}

	case mtDirectionalSolidThermo:
	{
		const solidThermo& thermo =
			mesh.lookupObject<solidThermo>(basicThermo::dictName);

		const symmTensorField& alphaAni =
			patch_.lookupPatchField<volSymmTensorField, scalar>
			(
				alphaAniName_
				);

		const scalarField& pp = thermo.p().boundaryField()[patchi];

		const symmTensorField kappa(alphaAni*thermo.Cp(pp, Tp, patchi));

		const vectorField n(patch_.nf());

		return n & kappa & n;
	}

	case mtLookup:
	{
		if (mesh.foundObject<volScalarField>(kappaName_))
		{
			return patch_.lookupPatchField<volScalarField, scalar>
				(
					kappaName_
					);
		}
		else if (mesh.foundObject<volSymmTensorField>(kappaName_))
		{
			const symmTensorField& KWall =
				patch_.lookupPatchField<volSymmTensorField, scalar>
				(
					kappaName_
					);

			const vectorField n(patch_.nf());

			return n & KWall & n;
		}
		else
		{
			FatalErrorInFunction
				<< "Did not find field " << kappaName_
				<< " on mesh " << mesh.name() << " patch " << patch_.name()
				<< nl
				<< "    Please set 'kappa' to the name of a volScalarField"
				" or volSymmTensorField."
				<< exit(FatalError);
		}

		break;
	}

	default:
	{
		FatalErrorInFunction
			<< "Unimplemented method " << KMethodTypeNames_[method_] << nl
			<< "    Please set 'kappaMethod' to one of "
			<< KMethodTypeNames_.toc()
			<< " and 'kappa' to the name of the volScalar"
			<< " or volSymmTensor field (if kappa=lookup)"
			<< exit(FatalError);
	}
	}

	return scalarField(0);
}


void tnbLib::temperatureCoupledBase::write(Ostream& os) const
{
	writeEntry(os, "kappaMethod", KMethodTypeNames_[method_]);
	writeEntry(os, "kappa", kappaName_);
	writeEntry(os, "alphaAni", alphaAniName_);
}


// ************************************************************************* //