#define FoamNamedEnum_EXPORT_DEFINE

#include <radiationCoupledBase.hxx>

#include <volFields.hxx>
#include <mappedPatchBase.hxx>
#include <fvPatchFieldMapper.hxx>
#include <radiationModel.hxx>
#include <opaqueSolid.hxx>
#include <absorptionEmissionModel.hxx>

// * * * * * * * * * * * * * Static Member Data  * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(radiationCoupledBase, 0);
}

template<>
const char* tnbLib::NamedEnum
<
	tnbLib::radiationCoupledBase::emissivityMethodType,
	2
>::names[] =
{
	"solidRadiation",
	"lookup"
};

const tnbLib::NamedEnum
<
	tnbLib::radiationCoupledBase::emissivityMethodType,
	2
> tnbLib::radiationCoupledBase::emissivityMethodTypeNames_;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationCoupledBase::radiationCoupledBase
(
	const fvPatch& patch,
	const word& calculationType,
	const scalarField& emissivity
)
	:
	patch_(patch),
	method_(emissivityMethodTypeNames_[calculationType]),
	emissivity_(emissivity)
{}


tnbLib::radiationCoupledBase::radiationCoupledBase
(
	const fvPatch& patch,
	const word& calculationType,
	const scalarField& emissivity,
	const fvPatchFieldMapper& mapper
)
	:
	patch_(patch),
	method_(emissivityMethodTypeNames_[calculationType]),
	emissivity_(mapper(emissivity))
{}


tnbLib::radiationCoupledBase::radiationCoupledBase
(
	const fvPatch& patch,
	const dictionary& dict
)
	:
	patch_(patch),
	method_(emissivityMethodTypeNames_.read(dict.lookup("emissivityMode")))
{
	switch (method_)
	{
	case SOLIDRADIATION:
	{
		if (!isA<mappedPatchBase>(patch_.patch()))
		{
			FatalIOErrorInFunction
			(
				dict
			) << "\n    patch type '" << patch_.type()
				<< "' not type '" << mappedPatchBase::typeName << "'"
				<< "\n    for patch " << patch_.name()
				<< exit(FatalIOError);
		}

		emissivity_ = scalarField(patch_.size(), 0.0);
	}
	break;

	case LOOKUP:
	{
		if (!dict.found("emissivity"))
		{
			FatalIOErrorInFunction
			(
				dict
			) << "\n    emissivity key does not exist for patch "
				<< patch_.name()
				<< exit(FatalIOError);
		}
		else
		{
			emissivity_ = scalarField("emissivity", dict, patch_.size());
		}
	}
	break;
	}
}


// * * * * * * * * * * * * * * * * Destructor    * * * * * * * * * * * * * * //

tnbLib::radiationCoupledBase::~radiationCoupledBase()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::scalarField tnbLib::radiationCoupledBase::emissivity() const
{
	switch (method_)
	{
	case SOLIDRADIATION:
	{
		// Get the coupling information from the mappedPatchBase
		const mappedPatchBase& mpp =
			refCast<const mappedPatchBase>(patch_.patch());

		const polyMesh& nbrMesh = mpp.sampleMesh();

		const radiationModels::opaqueSolid& radiation =
			nbrMesh.lookupObject<radiationModels::opaqueSolid>
			(
				"radiationProperties"
				);

		const fvMesh& nbrFvMesh = refCast<const fvMesh>(nbrMesh);

		const fvPatch& nbrPatch =
			nbrFvMesh.boundary()[mpp.samplePolyPatch().index()];

		// NOTE: for an opaqueSolid the absorptionEmission model returns the
		// emissivity of the surface rather than the emission coefficient
		// and the input specification MUST correspond to this.
		scalarField emissivity
		(
			radiation.absorptionEmission().e()().boundaryField()
			[
				nbrPatch.index()
			]
		);
		mpp.distribute(emissivity);

		return emissivity;
	}
	break;

	case LOOKUP:
	{
		// Return local value
		return emissivity_;
	}

	default:
	{
		FatalErrorInFunction
			<< "Unimplemented method " << method_ << endl
			<< "Please set 'emissivity' to one of "
			<< emissivityMethodTypeNames_.toc()
			<< exit(FatalError);
	}
	break;
	}

	return scalarField(0);
}


void tnbLib::radiationCoupledBase::autoMap(const fvPatchFieldMapper& m)
{
	m(emissivity_, emissivity_);
}


void tnbLib::radiationCoupledBase::rmap
(
	const fvPatchScalarField& ptf,
	const labelList& addr
)
{
	const radiationCoupledBase& mrptf =
		refCast<const radiationCoupledBase>(ptf);

	emissivity_.rmap(mrptf.emissivity_, addr);
}


void tnbLib::radiationCoupledBase::write(Ostream& os) const
{
	writeEntry(os, "emissivityMode", emissivityMethodTypeNames_[method_]);
	writeEntry(os, "emissivity", emissivity_);
}


// ************************************************************************* //