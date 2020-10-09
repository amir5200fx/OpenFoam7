#include <phaseScalarTransport.hxx>

#include <fixedValueFvPatchField.hxx>
#include <fvcDdt.hxx>
#include <fvcDiv.hxx>
#include <fvmDdt.hxx>
#include <fvmDiv.hxx>
#include <fvmLaplacian.hxx>
#include <nonOrthogonalSolutionControl.hxx>
#include <surfaceFields.hxx>
#include <turbulenceModel.hxx>
#include <wallFvPatch.hxx>
#include <zeroGradientFvPatchField.hxx>
#include <addToRunTimeSelectionTable.hxx>

#define PhiDimensionErrorInFunction(phi)                                       \
    FatalErrorInFunction                                                       \
        << "Incompatible dimensions for " << phi.name() << ": "                \
        << phi.dimensions() << nl                                              \
        << "Dimensions should be " << dimMass/dimTime << " or "                \
        << dimVolume/dimTime << exit(FatalError)

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(phaseScalarTransport, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			phaseScalarTransport,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::volScalarField& tnbLib::functionObjects::phaseScalarTransport::Phi()
{
	if (!PhiPtr_.valid())
	{
		const surfaceScalarField& phi =
			mesh_.lookupObject<surfaceScalarField>(phiName_);
		const volScalarField& p =
			mesh_.lookupObject<volScalarField>(pName_);

		wordList PhiPatchFieldTypes(mesh_.boundaryMesh().size());
		forAll(p.boundaryField(), patchi)
		{
			PhiPatchFieldTypes[patchi] =
				p.boundaryField()[patchi].fixesValue()
				? fixedValueFvPatchField<scalar>::typeName
				: zeroGradientFvPatchField<scalar>::typeName;
		}

		PhiPtr_.set
		(
			new volScalarField
			(
				IOobject
				(
					"Phi" + s_.name(),
					mesh_.time().timeName(),
					mesh_,
					IOobject::READ_IF_PRESENT,
					IOobject::AUTO_WRITE
				),
				mesh_,
				dimensionedScalar(phi.dimensions() / dimLength, Zero),
				PhiPatchFieldTypes
			)
		);

		mesh_.setFluxRequired(PhiPtr_->name());
	}

	return PhiPtr_();
}


tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::functionObjects::phaseScalarTransport::alphaPhi()
{
	// If alphaPhi exists then return it
	if (mesh_.foundObject<surfaceScalarField>(alphaPhiName_))
	{
		return mesh_.lookupObject<surfaceScalarField>(alphaPhiName_);
	}

	// Otherwise generate it ...
	Info << type() << ": " << surfaceScalarField::typeName << " "
		<< alphaPhiName_ << " was not found, so generating it" << endl;

	const volScalarField& alpha =
		mesh_.lookupObject<volScalarField>(alphaName_);
	const surfaceScalarField& phi =
		mesh_.lookupObject<surfaceScalarField>(phiName_);

	// Make a crude guess of the phase flux using default interpolation
	tmp<surfaceScalarField> tAlphaPhi
	(
		new surfaceScalarField
		(
			alphaPhiName_,
			phi*fvc::interpolate(alpha)
		)
	);
	surfaceScalarField& alphaPhi = tAlphaPhi.ref();

	// Get the potential field
	volScalarField& Phi(this->Phi());

	// Construct the scheme names
	const word laplacianScheme = "laplacian(" + pName_ + ")";

	// Debug writing. Write the material derivative of alpha, before and after
	// the solution of the potential and the correction of alphaPhi. Before
	// correction the field should be non-zero, and after it should be
	// comparable to the solution tolerance.
	auto writeDDt = [&](const label i)
	{
		const volScalarField DDtAlpha
		(
			"DDt("
			+ IOobject::groupName
			(
				IOobject::member(alpha.name()) + tnbLib::name(i),
				IOobject::group(alpha.name())
			)
			+ ")",
			fvc::ddt(alpha) + fvc::div(alphaPhi)
		);
		Info << type() << ": Writing " << DDtAlpha.name() << endl;
		DDtAlpha.write();
	};
	if (debug && mesh_.time().writeTime())
	{
		writeDDt(0);
	}

	// Lookup the non-orthogonal solution control
	nonOrthogonalSolutionControl& control =
		mesh_.lookupObjectRef<nonOrthogonalSolutionControl>
		(
			solutionControl::typeName
			);

	// Solve for the potential and correct alphaPhi with the resulting flux
	if (phi.dimensions() == dimVolume / dimTime)
	{
		while (control.correctNonOrthogonal())
		{
			fvScalarMatrix PhiEqn
			(
				fvm::laplacian(Phi, laplacianScheme)
				+ fvc::ddt(alpha)
				+ fvc::div(alphaPhi)
			);

			PhiEqn.solve(pName_);

			if (control.finalNonOrthogonalIter())
			{
				alphaPhi += PhiEqn.flux();
			}
		}
	}
	else if (phi.dimensions() == dimMass / dimTime)
	{
		const volScalarField& rho =
			mesh_.lookupObject<volScalarField>(rhoName_);

		while (control.correctNonOrthogonal())
		{
			fvScalarMatrix PhiEqn
			(
				fvm::laplacian(Phi, laplacianScheme)
				+ fvc::ddt(rho, alpha)
				+ fvc::div(alphaPhi)
			);

			PhiEqn.solve(pName_);

			if (control.finalNonOrthogonalIter())
			{
				alphaPhi += PhiEqn.flux();
			}
		}
	}
	else
	{
		PhiDimensionErrorInFunction(phi);
	}

	// Debug writing
	if (debug && mesh_.time().writeTime())
	{
		writeDDt(1);
	}

	return tAlphaPhi;
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::functionObjects::phaseScalarTransport::D
(
	const surfaceScalarField& alphaPhi
) const
{
	if (constantD_)
	{
		return volScalarField::New
		(
			"D" + s_.name(),
			mesh_,
			dimensionedScalar(alphaPhi.dimensions() / dimLength, D_)
		);
	}

	const word& nameNoPhase = turbulenceModel::propertiesName;
	const word namePhase = IOobject::groupName(nameNoPhase, phaseName_);

	const word& name =
		mesh_.foundObject<turbulenceModel>(namePhase)
		? namePhase
		: mesh_.foundObject<turbulenceModel>(nameNoPhase)
		? nameNoPhase
		: word::null;

	if (name == word::null)
	{
		return volScalarField::New
		(
			"D" + s_.name(),
			mesh_,
			dimensionedScalar(alphaPhi.dimensions() / dimLength, 0)
		);
	}

	const turbulenceModel& turbulence =
		mesh_.lookupObject<turbulenceModel>(name);

	if (alphaPhi.dimensions() == dimVolume / dimTime)
	{
		return alphaD_ * turbulence.nu() + alphaDt_ * turbulence.nut();
	}
	else if (alphaPhi.dimensions() == dimMass / dimTime)
	{
		return alphaD_ * turbulence.mu() + alphaDt_ * turbulence.mut();
	}
	else
	{
		PhiDimensionErrorInFunction(alphaPhi);
		return tmp<volScalarField>(nullptr);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::phaseScalarTransport::phaseScalarTransport
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	fieldName_(dict.lookup("field")),
	phaseName_(IOobject::group(fieldName_)),
	nCorr_(0),
	residualAlpha_(rootSmall),
	fvOptions_(mesh_),
	s_
	(
		IOobject
		(
			fieldName_,
			mesh_.time().timeName(),
			mesh_,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE
		),
		mesh_
	),
	alphaSPtr_(nullptr),
	PhiPtr_(nullptr)
{
	if (phaseName_ == word::null)
	{
		FatalErrorInFunction
			<< "Field \"" << fieldName_ << "\" does not have a phase extension "
			<< "in its name. If it is associated with \"phaseA\" then it "
			<< "should be named \"" << fieldName_ << ".phaseA\"."
			<< exit(FatalError);
	}

	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::phaseScalarTransport::~phaseScalarTransport()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::phaseScalarTransport::read(const dictionary& dict)
{
	fvMeshFunctionObject::read(dict);

	alphaName_ =
		dict.lookupOrDefault<word>
		(
			"alpha",
			IOobject::groupName("alpha", phaseName_)
			);
	alphaPhiName_ =
		dict.lookupOrDefault<word>
		(
			"alphaPhi",
			IOobject::groupName("alphaPhi", phaseName_)
			);
	phiName_ = dict.lookupOrDefault<word>("phi", "phi");
	rhoName_ =
		dict.lookupOrDefault<word>
		(
			"rho",
			IOobject::groupName("rho", phaseName_)
			);
	pName_ = dict.lookupOrDefault<word>("p", "p");
	schemesField_ = dict.lookupOrDefault<word>("schemesField", fieldName_);

	constantD_ = dict.readIfPresent("D", D_);
	alphaD_ = dict.lookupOrDefault<scalar>("alphaD", 1);
	alphaDt_ = dict.lookupOrDefault<scalar>("alphaDt", 1);

	dict.readIfPresent("nCorr", nCorr_);
	dict.readIfPresent("residualAlpha", residualAlpha_);
	writeAlphaField_ = dict.lookupOrDefault<bool>("writeAlphaField", true);

	if (dict.found("fvOptions"))
	{
		fvOptions_.reset(dict.subDict("fvOptions"));
	}

	return true;
}


bool tnbLib::functionObjects::phaseScalarTransport::execute()
{
	Info << type() << ": Executing" << endl;

	const volScalarField& alpha =
		mesh_.lookupObject<volScalarField>(alphaName_);

	// Get the phase flux
	tmp<surfaceScalarField> tAlphaPhi(this->alphaPhi());
	const surfaceScalarField& alphaPhi = tAlphaPhi();

	// Get the diffusivity
	const volScalarField D(this->D(alphaPhi));

	// Construct the scheme names
	const word divScheme =
		"div(" + alphaPhi.name() + "," + schemesField_ + ")";
	const word laplacianScheme =
		"laplacian(" + D.name() + "," + schemesField_ + ")";

	// Get the relaxation coefficient
	const scalar relaxCoeff =
		mesh_.relaxEquation(schemesField_)
		? mesh_.equationRelaxationFactor(schemesField_)
		: 0;

	// Solve
	if (alphaPhi.dimensions() == dimVolume / dimTime)
	{
		for (label i = 0; i <= nCorr_; ++i)
		{
			fvScalarMatrix fieldEqn
			(
				fvm::ddt(alpha, s_)
				+ fvm::div(alphaPhi, s_, divScheme)
				- fvm::laplacian
				(
					fvc::interpolate(alpha)*fvc::interpolate(D),
					s_,
					laplacianScheme
				)
				==
				fvOptions_(alpha, s_)
				- fvm::ddt(residualAlpha_, s_)
				+ fvc::ddt(residualAlpha_, s_)
			);

			fieldEqn.relax(relaxCoeff);
			fvOptions_.constrain(fieldEqn);
			fieldEqn.solve(schemesField_);
		}
	}
	else if (alphaPhi.dimensions() == dimMass / dimTime)
	{
		const volScalarField& rho =
			mesh_.lookupObject<volScalarField>(rhoName_);

		for (label i = 0; i <= nCorr_; ++i)
		{
			fvScalarMatrix fieldEqn
			(
				fvm::ddt(alpha, rho, s_)
				+ fvm::div(alphaPhi, s_, divScheme)
				- fvm::laplacian
				(
					fvc::interpolate(alpha)*fvc::interpolate(D),
					s_,
					laplacianScheme
				)
				==
				fvOptions_(alpha, rho, s_)
				- fvm::ddt(residualAlpha_*rho, s_)
				+ fvc::ddt(residualAlpha_*rho, s_)
			);

			fieldEqn.relax(relaxCoeff);
			fvOptions_.constrain(fieldEqn);
			fieldEqn.solve(schemesField_);
		}
	}
	else
	{
		PhiDimensionErrorInFunction(alphaPhi);
	}

	// Update
	if (writeAlphaField_)
	{
		if (!alphaSPtr_.valid())
		{
			alphaSPtr_.set
			(
				new volScalarField
				(
					IOobject
					(
						"alpha"
						+ word(toupper(fieldName_[0]))
						+ fieldName_(1, fieldName_.size() - 1),
						mesh_.time().timeName(),
						mesh_,
						IOobject::NO_READ,
						IOobject::AUTO_WRITE
					),
					mesh_,
					dimensionedScalar(s_.dimensions(), Zero)
				)
			);
		}

		alphaSPtr_() = alpha * s_;
	}
	else
	{
		if (alphaSPtr_.valid())
		{
			alphaSPtr_().clear();
		}
	}

	Info << endl;

	return true;
}


bool tnbLib::functionObjects::phaseScalarTransport::write()
{
	return true;
}


// ************************************************************************* //