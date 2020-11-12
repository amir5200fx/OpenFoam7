#pragma once

#include <atomicWeights.hxx>
#include <ReactionProxy.hxx>
#include <IrreversibleReaction.hxx>
#include <ReversibleReaction.hxx>
#include <LindemannFallOffFunction.hxx>
#include <ArrheniusReactionRate.hxx>
#include <thirdBodyArrheniusReactionRate.hxx>
#include <TroeFallOffFunction.hxx>
#include <SRIFallOffFunction.hxx>

template<class ReactionRateType>
void tnbLib::chemkinReader::addReactionType
(
	const reactionType rType,
	DynamicList<specieCoeffs>& lhs,
	DynamicList<specieCoeffs>& rhs,
	const ReactionRateType& rr
)
{
	switch (rType)
	{
	case irreversible:
	{
		reactions_.append
		(
			new IrreversibleReaction
			<Reaction, gasHThermoPhysics, ReactionRateType>
			(
				ReactionProxy<gasHThermoPhysics>
				(
					speciesTable_,
					lhs.shrink(),
					rhs.shrink(),
					speciesThermo_
					),
				rr
				)
		);
	}
	break;

	case reversible:
	{
		reactions_.append
		(
			new ReversibleReaction
			<Reaction, gasHThermoPhysics, ReactionRateType>
			(
				ReactionProxy<gasHThermoPhysics>
				(
					speciesTable_,
					lhs.shrink(),
					rhs.shrink(),
					speciesThermo_
					),
				rr
				)
		);
	}
	break;

	default:

		if (rType < 3)
		{
			FatalErrorInFunction
				<< "Reaction type " << reactionTypeNames[rType]
				<< " on line " << lineNo_ - 1
				<< " not handled by this function"
				<< exit(FatalError);
		}
		else
		{
			FatalErrorInFunction
				<< "Unknown reaction type " << rType
				<< " on line " << lineNo_ - 1
				<< exit(FatalError);
		}
	}
}

template<template<class, class> class PressureDependencyType>
void tnbLib::chemkinReader::addPressureDependentReaction
(
	const reactionType rType,
	const fallOffFunctionType fofType,
	DynamicList<specieCoeffs>& lhs,
	DynamicList<specieCoeffs>& rhs,
	const scalarList& efficiencies,
	const scalarList& k0Coeffs,
	const scalarList& kInfCoeffs,
	const HashTable<scalarList>& reactionCoeffsTable,
	const scalar Afactor0,
	const scalar AfactorInf,
	const scalar RR
)
{
	checkCoeffs(k0Coeffs, "k0", 3);
	checkCoeffs(kInfCoeffs, "kInf", 3);

	switch (fofType)
	{
	case Lindemann:
	{
		addReactionType
		(
			rType,
			lhs, rhs,
			PressureDependencyType
			<ArrheniusReactionRate, LindemannFallOffFunction>
			(
				ArrheniusReactionRate
				(
					Afactor0 * k0Coeffs[0],
					k0Coeffs[1],
					k0Coeffs[2] / RR
				),
				ArrheniusReactionRate
				(
					AfactorInf * kInfCoeffs[0],
					kInfCoeffs[1],
					kInfCoeffs[2] / RR
				),
				LindemannFallOffFunction(),
				thirdBodyEfficiencies(speciesTable_, efficiencies)
				)
		);
		break;
	}
	case Troe:
	{
		scalarList TroeCoeffs
		(
			reactionCoeffsTable[fallOffFunctionNames[fofType]]
		);

		if (TroeCoeffs.size() != 4 && TroeCoeffs.size() != 3)
		{
			FatalErrorInFunction
				<< "Wrong number of coefficients for Troe rate expression"
				" on line " << lineNo_ - 1 << ", should be 3 or 4 but "
				<< TroeCoeffs.size() << " supplied." << nl
				<< "Coefficients are "
				<< TroeCoeffs << nl
				<< exit(FatalError);
		}

		if (TroeCoeffs.size() == 3)
		{
			TroeCoeffs.setSize(4);
			TroeCoeffs[3] = great;
		}

		addReactionType
		(
			rType,
			lhs, rhs,
			PressureDependencyType
			<ArrheniusReactionRate, TroeFallOffFunction>
			(
				ArrheniusReactionRate
				(
					Afactor0 * k0Coeffs[0],
					k0Coeffs[1],
					k0Coeffs[2] / RR
				),
				ArrheniusReactionRate
				(
					AfactorInf * kInfCoeffs[0],
					kInfCoeffs[1],
					kInfCoeffs[2] / RR
				),
				TroeFallOffFunction
				(
					TroeCoeffs[0],
					TroeCoeffs[1],
					TroeCoeffs[2],
					TroeCoeffs[3]
				),
				thirdBodyEfficiencies(speciesTable_, efficiencies)
				)
		);
		break;
	}
	case SRI:
	{
		scalarList SRICoeffs
		(
			reactionCoeffsTable[fallOffFunctionNames[fofType]]
		);

		if (SRICoeffs.size() != 5 && SRICoeffs.size() != 3)
		{
			FatalErrorInFunction
				<< "Wrong number of coefficients for SRI rate expression"
				" on line " << lineNo_ - 1 << ", should be 3 or 5 but "
				<< SRICoeffs.size() << " supplied." << nl
				<< "Coefficients are "
				<< SRICoeffs << nl
				<< exit(FatalError);
		}

		if (SRICoeffs.size() == 3)
		{
			SRICoeffs.setSize(5);
			SRICoeffs[3] = 1.0;
			SRICoeffs[4] = 0.0;
		}

		addReactionType
		(
			rType,
			lhs, rhs,
			PressureDependencyType
			<ArrheniusReactionRate, SRIFallOffFunction>
			(
				ArrheniusReactionRate
				(
					Afactor0 * k0Coeffs[0],
					k0Coeffs[1],
					k0Coeffs[2] / RR
				),
				ArrheniusReactionRate
				(
					AfactorInf * kInfCoeffs[0],
					kInfCoeffs[1],
					kInfCoeffs[2] / RR
				),
				SRIFallOffFunction
				(
					SRICoeffs[0],
					SRICoeffs[1],
					SRICoeffs[2],
					SRICoeffs[3],
					SRICoeffs[4]
				),
				thirdBodyEfficiencies(speciesTable_, efficiencies)
				)
		);
		break;
	}
	default:
	{
		FatalErrorInFunction
			<< "Fall-off function type "
			<< fallOffFunctionNames[fofType]
			<< " on line " << lineNo_ - 1
			<< " not implemented"
			<< exit(FatalError);
	}
	}
}