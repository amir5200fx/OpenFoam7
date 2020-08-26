#include <radiativeIntensityRay.hxx>

#include <fvm.hxx>
#include <fvDOM.hxx>
#include <constants.hxx>

#include <Time.hxx>  // added by amir
#include <transform.hxx>  // added by amir

using namespace tnbLib::constant;

const tnbLib::word tnbLib::radiationModels::radiativeIntensityRay::intensityPrefix
(
	"ILambda"
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationModels::radiativeIntensityRay::radiativeIntensityRay
(
	const fvDOM& dom,
	const fvMesh& mesh,
	const scalar phi,
	const scalar theta,
	const scalar deltaPhi,
	const scalar deltaTheta,
	const label nLambda,
	const absorptionEmissionModel& absorptionEmission,
	const blackBodyEmission& blackBody,
	const label rayId
)
	:
	dom_(dom),
	mesh_(mesh),
	absorptionEmission_(absorptionEmission),
	blackBody_(blackBody),
	I_
	(
		IOobject
		(
			"I" + name(rayId),
			mesh_.time().timeName(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh_,
		dimensionedScalar(dimMass / pow3(dimTime), 0)
	),
	qr_
	(
		IOobject
		(
			"qr" + name(rayId),
			mesh_.time().timeName(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh_,
		dimensionedScalar(dimMass / pow3(dimTime), 0)
	),
	qin_
	(
		IOobject
		(
			"qin" + name(rayId),
			mesh_.time().timeName(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh_,
		dimensionedScalar(dimMass / pow3(dimTime), 0)
	),
	qem_
	(
		IOobject
		(
			"qem" + name(rayId),
			mesh_.time().timeName(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh_,
		dimensionedScalar(dimMass / pow3(dimTime), 0)
	),
	d_(Zero),
	dAve_(Zero),
	theta_(theta),
	phi_(phi),
	omega_(0.0),
	nLambda_(nLambda),
	ILambda_(nLambda),
	myRayId_(rayId)
{
	scalar sinTheta = tnbLib::sin(theta);
	scalar cosTheta = tnbLib::cos(theta);
	scalar sinPhi = tnbLib::sin(phi);
	scalar cosPhi = tnbLib::cos(phi);

	omega_ = 2.0*sinTheta*tnbLib::sin(deltaTheta / 2.0)*deltaPhi;
	d_ = vector(sinTheta*sinPhi, sinTheta*cosPhi, cosTheta);
	dAve_ = vector
	(
		sinPhi
		*tnbLib::sin(0.5*deltaPhi)
		*(deltaTheta - tnbLib::cos(2.0*theta)
			*tnbLib::sin(deltaTheta)),
		cosPhi
		*tnbLib::sin(0.5*deltaPhi)
		*(deltaTheta - tnbLib::cos(2.0*theta)
			*tnbLib::sin(deltaTheta)),
		0.5*deltaPhi*tnbLib::sin(2.0*theta)*tnbLib::sin(deltaTheta)
	);

	// Transform directions so that they fall inside the bounds of reduced
	// dimension cases
	if (mesh_.nSolutionD() == 2)
	{
		vector meshDir(vector::zero);
		for (direction cmpt = 0; cmpt < vector::nComponents; cmpt++)
		{
			if (mesh_.geometricD()[cmpt] == -1)
			{
				meshDir[cmpt] = 1;
			}
		}
		const vector normal(vector(0, 0, 1));

		const tensor coordRot = rotationTensor(normal, meshDir);

		dAve_ = coordRot & dAve_;
		d_ = coordRot & d_;
	}
	else if (mesh_.nSolutionD() == 1)
	{
		vector meshDir(vector::zero);
		for (direction cmpt = 0; cmpt < vector::nComponents; cmpt++)
		{
			if (mesh_.geometricD()[cmpt] == 1)
			{
				meshDir[cmpt] = 1;
			}
		}
		const vector normal(vector(1, 0, 0));

		dAve_ = (dAve_ & normal)*meshDir;
		d_ = (d_ & normal)*meshDir;
	}


	autoPtr<volScalarField> IDefaultPtr;

	forAll(ILambda_, lambdaI)
	{
		IOobject IHeader
		(
			intensityPrefix + "_" + name(rayId) + "_" + name(lambdaI),
			mesh_.time().timeName(),
			mesh_,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE
		);

		// Check if field exists and can be read
		if (IHeader.typeHeaderOk<volScalarField>(true))
		{
			ILambda_.set
			(
				lambdaI,
				new volScalarField(IHeader, mesh_)
			);
		}
		else
		{
			// Demand driven load the IDefault field
			if (!IDefaultPtr.valid())
			{
				IDefaultPtr.reset
				(
					new volScalarField
					(
						IOobject
						(
							"IDefault",
							mesh_.time().timeName(),
							mesh_,
							IOobject::MUST_READ,
							IOobject::NO_WRITE
						),
						mesh_
					)
				);
			}

			// Reset the MUST_READ flag
			IOobject noReadHeader(IHeader);
			noReadHeader.readOpt() = IOobject::NO_READ;

			ILambda_.set
			(
				lambdaI,
				new volScalarField(noReadHeader, IDefaultPtr())
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::radiationModels::radiativeIntensityRay::~radiativeIntensityRay()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::radiationModels::radiativeIntensityRay::correct()
{
	// Reset boundary heat flux to zero
	qr_.boundaryFieldRef() = 0.0;

	scalar maxResidual = -great;

	const surfaceScalarField Ji(dAve_ & mesh_.Sf());

	forAll(ILambda_, lambdaI)
	{
		const volScalarField& k = dom_.aLambda(lambdaI);

		fvScalarMatrix IiEq
		(
			fvm::div(Ji, ILambda_[lambdaI], "div(Ji,Ii_h)")
			+ fvm::Sp(k*omega_, ILambda_[lambdaI])
			==
			1.0 / constant::mathematical::pi*omega_
			*(
				// Remove aDisp from k
			(k - absorptionEmission_.aDisp(lambdaI))
				*blackBody_.bLambda(lambdaI)

				+ absorptionEmission_.E(lambdaI) / 4
				)
		);

		IiEq.relax();

		const solverPerformance ILambdaSol = solve(IiEq, "Ii");

		const scalar initialRes =
			ILambdaSol.initialResidual()*omega_ / dom_.omegaMax();

		maxResidual = max(initialRes, maxResidual);
	}

	return maxResidual;
}


void tnbLib::radiationModels::radiativeIntensityRay::addIntensity()
{
	I_ = dimensionedScalar(dimMass / pow3(dimTime), 0);

	forAll(ILambda_, lambdaI)
	{
		I_ += ILambda_[lambdaI];
	}
}


// ************************************************************************* //