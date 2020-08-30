#pragma once
#include <constants.hxx>

using namespace tnbLib::constant;

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

inline void tnbLib::moleculeCloud::evaluatePair
(
	molecule& molI,
	molecule& molJ
)
{
	const pairPotentialList& pairPot = pot_.pairPotentials();

	const pairPotential& electrostatic = pairPot.electrostatic();

	label idI = molI.id();

	label idJ = molJ.id();

	const molecule::constantProperties& constPropI(constProps(idI));

	const molecule::constantProperties& constPropJ(constProps(idJ));

	List<label> siteIdsI = constPropI.siteIds();

	List<label> siteIdsJ = constPropJ.siteIds();

	List<bool> pairPotentialSitesI = constPropI.pairPotentialSites();

	List<bool> electrostaticSitesI = constPropI.electrostaticSites();

	List<bool> pairPotentialSitesJ = constPropJ.pairPotentialSites();

	List<bool> electrostaticSitesJ = constPropJ.electrostaticSites();

	forAll(siteIdsI, sI)
	{
		label idsI(siteIdsI[sI]);

		forAll(siteIdsJ, sJ)
		{
			label idsJ(siteIdsJ[sJ]);

			if (pairPotentialSitesI[sI] && pairPotentialSitesJ[sJ])
			{
				vector rsIsJ =
					molI.sitePositions()[sI] - molJ.sitePositions()[sJ];

				scalar rsIsJMagSq = magSqr(rsIsJ);

				if (pairPot.rCutSqr(idsI, idsJ, rsIsJMagSq))
				{
					scalar rsIsJMag = mag(rsIsJ);

					vector fsIsJ =
						(rsIsJ / rsIsJMag)
						*pairPot.force(idsI, idsJ, rsIsJMag);

					molI.siteForces()[sI] += fsIsJ;

					molJ.siteForces()[sJ] += -fsIsJ;

					scalar potentialEnergy
					(
						pairPot.energy(idsI, idsJ, rsIsJMag)
					);

					molI.potentialEnergy() += 0.5*potentialEnergy;

					molJ.potentialEnergy() += 0.5*potentialEnergy;

					vector rIJ = molI.position() - molJ.position();

					tensor virialContribution =
						(rsIsJ*fsIsJ)*(rsIsJ & rIJ) / rsIsJMagSq;

					molI.rf() += virialContribution;

					molJ.rf() += virialContribution;
				}
			}

			if (electrostaticSitesI[sI] && electrostaticSitesJ[sJ])
			{
				vector rsIsJ =
					molI.sitePositions()[sI] - molJ.sitePositions()[sJ];

				scalar rsIsJMagSq = magSqr(rsIsJ);

				if (rsIsJMagSq <= electrostatic.rCutSqr())
				{
					scalar rsIsJMag = mag(rsIsJ);

					scalar chargeI = constPropI.siteCharges()[sI];

					scalar chargeJ = constPropJ.siteCharges()[sJ];

					vector fsIsJ =
						(rsIsJ / rsIsJMag)
						*chargeI*chargeJ*electrostatic.force(rsIsJMag);

					molI.siteForces()[sI] += fsIsJ;

					molJ.siteForces()[sJ] += -fsIsJ;

					scalar potentialEnergy =
						chargeI * chargeJ
						*electrostatic.energy(rsIsJMag);

					molI.potentialEnergy() += 0.5*potentialEnergy;

					molJ.potentialEnergy() += 0.5*potentialEnergy;

					vector rIJ = molI.position() - molJ.position();

					tensor virialContribution =
						(rsIsJ*fsIsJ)*(rsIsJ & rIJ) / rsIsJMagSq;

					molI.rf() += virialContribution;

					molJ.rf() += virialContribution;
				}
			}
		}
	}
}


inline bool tnbLib::moleculeCloud::evaluatePotentialLimit
(
	molecule& molI,
	molecule& molJ
) const
{
	const pairPotentialList& pairPot = pot_.pairPotentials();

	const pairPotential& electrostatic = pairPot.electrostatic();

	label idI = molI.id();

	label idJ = molJ.id();

	const molecule::constantProperties& constPropI(constProps(idI));

	const molecule::constantProperties& constPropJ(constProps(idJ));

	List<label> siteIdsI = constPropI.siteIds();

	List<label> siteIdsJ = constPropJ.siteIds();

	List<bool> pairPotentialSitesI = constPropI.pairPotentialSites();

	List<bool> electrostaticSitesI = constPropI.electrostaticSites();

	List<bool> pairPotentialSitesJ = constPropJ.pairPotentialSites();

	List<bool> electrostaticSitesJ = constPropJ.electrostaticSites();

	forAll(siteIdsI, sI)
	{
		label idsI(siteIdsI[sI]);

		forAll(siteIdsJ, sJ)
		{
			label idsJ(siteIdsJ[sJ]);

			if (pairPotentialSitesI[sI] && pairPotentialSitesJ[sJ])
			{
				vector rsIsJ =
					molI.sitePositions()[sI] - molJ.sitePositions()[sJ];

				scalar rsIsJMagSq = magSqr(rsIsJ);

				if (pairPot.rCutSqr(idsI, idsJ, rsIsJMagSq))
				{
					scalar rsIsJMag = mag(rsIsJ);

					// Guard against pairPot.energy being evaluated
					// if rIJMag < small. A floating point exception will
					// happen otherwise.

					if (rsIsJMag < small)
					{
						WarningInFunction
							<< "Molecule site pair closer than "
							<< small
							<< ": mag separation = " << rsIsJMag
							<< ". These may have been placed on top of each"
							<< " other by a rounding error in mdInitialise in"
							<< " parallel or a block filled with molecules"
							<< " twice. Removing one of the molecules."
							<< endl;

						return true;
					}

					// Guard against pairPot.energy being evaluated if rIJMag <
					// rMin.  A tabulation lookup error will occur otherwise.

					if (rsIsJMag < pairPot.rMin(idsI, idsJ))
					{
						return true;
					}

					if
						(
							mag(pairPot.energy(idsI, idsJ, rsIsJMag))
					> pot_.potentialEnergyLimit()
							)
					{
						return true;
					};
				}
			}

			if (electrostaticSitesI[sI] && electrostaticSitesJ[sJ])
			{
				vector rsIsJ =
					molI.sitePositions()[sI] - molJ.sitePositions()[sJ];

				scalar rsIsJMagSq = magSqr(rsIsJ);

				if (pairPot.rCutMaxSqr(rsIsJMagSq))
				{
					scalar rsIsJMag = mag(rsIsJ);

					// Guard against pairPot.energy being evaluated
					// if rIJMag < small. A floating point exception will
					// happen otherwise.

					if (rsIsJMag < small)
					{
						WarningInFunction
							<< "Molecule site pair closer than "
							<< small
							<< ": mag separation = " << rsIsJMag
							<< ". These may have been placed on top of each"
							<< " other by a rounding error in mdInitialise in"
							<< " parallel or a block filled with molecules"
							<< " twice. Removing one of the molecules."
							<< endl;

						return true;
					}

					if (rsIsJMag < electrostatic.rMin())
					{
						return true;
					}

					scalar chargeI = constPropI.siteCharges()[sI];

					scalar chargeJ = constPropJ.siteCharges()[sJ];

					if
						(
							mag(chargeI*chargeJ*electrostatic.energy(rsIsJMag))
					> pot_.potentialEnergyLimit()
							)
					{
						return true;
					};
				}
			}
		}
	}

	return false;
}


inline tnbLib::vector tnbLib::moleculeCloud::equipartitionLinearVelocity
(
	scalar temperature,
	scalar mass
)
{
	return
		sqrt(physicoChemical::k.value()*temperature / mass)
		*rndGen_.sampleNormal<vector>();
}


inline tnbLib::vector tnbLib::moleculeCloud::equipartitionAngularMomentum
(
	scalar temperature,
	const molecule::constantProperties& cP
)
{
	scalar sqrtKbT = sqrt(physicoChemical::k.value()*temperature);

	if (cP.linearMolecule())
	{
		return sqrtKbT * vector
		(
			0.0,
			sqrt(cP.momentOfInertia().yy())*rndGen_.scalarNormal(),
			sqrt(cP.momentOfInertia().zz())*rndGen_.scalarNormal()
		);
	}
	else
	{
		return sqrtKbT * vector
		(
			sqrt(cP.momentOfInertia().xx())*rndGen_.scalarNormal(),
			sqrt(cP.momentOfInertia().yy())*rndGen_.scalarNormal(),
			sqrt(cP.momentOfInertia().zz())*rndGen_.scalarNormal()
		);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::polyMesh& tnbLib::moleculeCloud::mesh() const
{
	return mesh_;
}


inline const tnbLib::potential& tnbLib::moleculeCloud::pot() const
{
	return pot_;
}


inline const tnbLib::List<tnbLib::DynamicList<tnbLib::molecule*>>&
tnbLib::moleculeCloud::cellOccupancy() const
{
	return cellOccupancy_;
}


inline const tnbLib::InteractionLists<tnbLib::molecule>&
tnbLib::moleculeCloud::il() const
{
	return il_;
}


inline const tnbLib::List<tnbLib::molecule::constantProperties>
tnbLib::moleculeCloud::constProps() const
{
	return constPropList_;
}


inline const tnbLib::molecule::constantProperties&
tnbLib::moleculeCloud::constProps(label id) const
{
	return constPropList_[id];
}


inline tnbLib::Random& tnbLib::moleculeCloud::rndGen()
{
	return rndGen_;
}


// ************************************************************************* //