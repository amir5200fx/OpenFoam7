#pragma once

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::compressibleInterPhaseTransportModel::alphaEff() const
{
	if (twoPhaseTransport_)
	{
		return
			mixture_.alpha1() * mixture_.thermo1().alphaEff
			(
				turbulence1_->alphat()
			)
			+ mixture_.alpha2() * mixture_.thermo2().alphaEff
			(
				turbulence2_->alphat()
			);
	}
	else
	{
		return mixture_.alphaEff(turbulence_->alphat());
	}
}


tnbLib::tmp<tnbLib::fvVectorMatrix>
tnbLib::compressibleInterPhaseTransportModel::divDevRhoReff
(
	volVectorField& U
) const
{
	if (twoPhaseTransport_)
	{
		return
			turbulence1_->divDevRhoReff(U)
			+ turbulence2_->divDevRhoReff(U);
	}
	else
	{
		return turbulence_->divDevRhoReff(U);
	}
}


void tnbLib::compressibleInterPhaseTransportModel::correctPhasePhi()
{
	if (twoPhaseTransport_)
	{
		const volScalarField& rho1 = mixture_.thermo1().rho();
		const volScalarField& rho2 = mixture_.thermo2().rho();

		alphaRhoPhi1_.ref() = fvc::interpolate(rho1) * alphaPhi10_;
		alphaRhoPhi2_.ref() = fvc::interpolate(rho2) * (phi_ - alphaPhi10_);
	}
}