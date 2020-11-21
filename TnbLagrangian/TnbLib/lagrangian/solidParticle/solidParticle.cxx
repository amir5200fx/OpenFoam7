#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <solidParticle.hxx>

#include <solidParticleCloud.hxx>  // added by amir
#include <volMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug(Cloud<solidParticle>, 0);
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::solidParticle::move
(
	solidParticleCloud& cloud,
	trackingData& td,
	const scalar trackTime
)
{
	td.switchProcessor = false;
	td.keepParticle = true;

	while (td.keepParticle && !td.switchProcessor && stepFraction() < 1)
	{
		if (debug)
		{
			Info << "Time = " << mesh().time().timeName()
				<< " trackTime = " << trackTime
				<< " steptFraction() = " << stepFraction() << endl;
		}


		const scalar sfrac = stepFraction();

		const scalar f = 1 - stepFraction();
		trackToAndHitFace(f*trackTime*U_, f, cloud, td);

		const scalar dt = (stepFraction() - sfrac)*trackTime;

		const tetIndices tetIs = this->currentTetIndices();
		scalar rhoc = td.rhoInterp().interpolate(this->coordinates(), tetIs);
		vector Uc = td.UInterp().interpolate(this->coordinates(), tetIs);
		scalar nuc = td.nuInterp().interpolate(this->coordinates(), tetIs);

		scalar rhop = cloud.rhop();
		scalar magUr = mag(Uc - U_);

		scalar ReFunc = 1.0;
		scalar Re = magUr * d_ / nuc;

		if (Re > 0.01)
		{
			ReFunc += 0.15*pow(Re, 0.687);
		}

		scalar Dc = (24.0*nuc / d_)*ReFunc*(3.0 / 4.0)*(rhoc / (d_*rhop));

		U_ = (U_ + dt * (Dc*Uc + (1.0 - rhoc / rhop)*td.g())) / (1.0 + dt * Dc);
	}

	return td.keepParticle;
}


bool tnbLib::solidParticle::hitPatch(solidParticleCloud&, trackingData&)
{
	return false;
}


void tnbLib::solidParticle::hitProcessorPatch
(
	solidParticleCloud&,
	trackingData& td
)
{
	td.switchProcessor = true;
}


void tnbLib::solidParticle::hitWallPatch(solidParticleCloud& cloud, trackingData&)
{
	const vector nw = normal();

	const scalar Un = U_ & nw;
	const vector Ut = U_ - Un * nw;

	if (Un > 0)
	{
		U_ -= (1.0 + cloud.e())*Un*nw;
	}

	U_ -= cloud.mu()*Ut;
}


void tnbLib::solidParticle::transformProperties(const tensor& T)
{
	particle::transformProperties(T);
	U_ = transform(T, U_);
}


void tnbLib::solidParticle::transformProperties(const vector& separation)
{
	particle::transformProperties(separation);
}


// ************************************************************************* //