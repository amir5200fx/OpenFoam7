#include <chemkinReader.hxx>

#include <fstream>
#include <atomicWeights.hxx>
#include <ReactionProxy.hxx>
//#include <IrreversibleReaction.hxx>
//#include <ReversibleReaction.hxx>
#include <NonEquilibriumReversibleReaction.hxx>
//#include <ArrheniusReactionRate.hxx>
//#include <thirdBodyArrheniusReactionRate.hxx>
#include <FallOffReactionRate.hxx>
#include <ChemicallyActivatedReactionRate.hxx>
//#include <LindemannFallOffFunction.hxx>
//#include <TroeFallOffFunction.hxx>
//#include <SRIFallOffFunction.hxx>
#include <LandauTellerReactionRate.hxx>
#include <JanevReactionRate.hxx>
#include <powerSeriesReactionRate.hxx>
#include <addToRunTimeSelectionTable.hxx>


/* * * * * * * * * * * * * * * * * Static data * * * * * * * * * * * * * * * */

namespace tnbLib
{
	addChemistryReaderType(chemkinReader, gasHThermoPhysics);
}


/* * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * */

const char* tnbLib::chemkinReader::reactionTypeNames[4] =
{
	"irreversible",
	"reversible",
	"nonEquilibriumReversible",
	"unknownReactionType"
};

const char* tnbLib::chemkinReader::reactionRateTypeNames[8] =
{
	"Arrhenius",
	"thirdBodyArrhenius",
	"unimolecularFallOff",
	"chemicallyActivatedBimolecular",
	"LandauTeller",
	"Janev",
	"powerSeries",
	"unknownReactionRateType"
};

const char* tnbLib::chemkinReader::fallOffFunctionNames[4] =
{
	"Lindemann",
	"Troe",
	"SRI",
	"unknownFallOffFunctionType"
};

void tnbLib::chemkinReader::initReactionKeywordTable()
{
	reactionKeywordTable_.insert("M", thirdBodyReactionType);
	reactionKeywordTable_.insert("LOW", unimolecularFallOffReactionType);
	reactionKeywordTable_.insert
	(
		"HIGH",
		chemicallyActivatedBimolecularReactionType
	);
	reactionKeywordTable_.insert("TROE", TroeReactionType);
	reactionKeywordTable_.insert("SRI", SRIReactionType);
	reactionKeywordTable_.insert("LT", LandauTellerReactionType);
	reactionKeywordTable_.insert("RLT", reverseLandauTellerReactionType);
	reactionKeywordTable_.insert("JAN", JanevReactionType);
	reactionKeywordTable_.insert("FIT1", powerSeriesReactionRateType);
	reactionKeywordTable_.insert("HV", radiationActivatedReactionType);
	reactionKeywordTable_.insert("TDEP", speciesTempReactionType);
	reactionKeywordTable_.insert("EXCI", energyLossReactionType);
	reactionKeywordTable_.insert("MOME", plasmaMomentumTransfer);
	reactionKeywordTable_.insert("XSMI", collisionCrossSection);
	reactionKeywordTable_.insert("REV", nonEquilibriumReversibleReactionType);
	reactionKeywordTable_.insert("DUPLICATE", duplicateReactionType);
	reactionKeywordTable_.insert("DUP", duplicateReactionType);
	reactionKeywordTable_.insert("FORD", speciesOrderForward);
	reactionKeywordTable_.insert("RORD", speciesOrderReverse);
	reactionKeywordTable_.insert("UNITS", UnitsOfReaction);
	reactionKeywordTable_.insert("END", end);
}


tnbLib::scalar tnbLib::chemkinReader::molecularWeight
(
	const List<specieElement>& specieComposition
) const
{
	scalar molWt = 0.0;

	forAll(specieComposition, i)
	{
		label nAtoms = specieComposition[i].nAtoms();
		const word& elementName = specieComposition[i].name();

		if (isotopeAtomicWts_.found(elementName))
		{
			molWt += nAtoms * isotopeAtomicWts_[elementName];
		}
		else if (atomicWeights.found(elementName))
		{
			molWt += nAtoms * atomicWeights[elementName];
		}
		else
		{
			FatalErrorInFunction
				<< "Unknown element " << elementName
				<< " on line " << lineNo_ - 1 << nl
				<< "    specieComposition: " << specieComposition
				<< exit(FatalError);
		}
	}

	return molWt;
}


void tnbLib::chemkinReader::checkCoeffs
(
	const scalarList& reactionCoeffs,
	const char* reactionRateName,
	const label nCoeffs
) const
{
	if (reactionCoeffs.size() != nCoeffs)
	{
		FatalErrorInFunction
			<< "Wrong number of coefficients for the " << reactionRateName
			<< " rate expression on line "
			<< lineNo_ - 1 << ", should be "
			<< nCoeffs << " but " << reactionCoeffs.size() << " supplied." << nl
			<< "Coefficients are "
			<< reactionCoeffs << nl
			<< exit(FatalError);
	}
}

//template<class ReactionRateType>
//void tnbLib::chemkinReader::addReactionType
//(
//	const reactionType rType,
//	DynamicList<specieCoeffs>& lhs,
//	DynamicList<specieCoeffs>& rhs,
//	const ReactionRateType& rr
//)
//{
//	switch (rType)
//	{
//	case irreversible:
//	{
//		reactions_.append
//		(
//			new IrreversibleReaction
//			<Reaction, gasHThermoPhysics, ReactionRateType>
//			(
//				ReactionProxy<gasHThermoPhysics>
//				(
//					speciesTable_,
//					lhs.shrink(),
//					rhs.shrink(),
//					speciesThermo_
//					),
//				rr
//				)
//		);
//	}
//	break;
//
//	case reversible:
//	{
//		reactions_.append
//		(
//			new ReversibleReaction
//			<Reaction, gasHThermoPhysics, ReactionRateType>
//			(
//				ReactionProxy<gasHThermoPhysics>
//				(
//					speciesTable_,
//					lhs.shrink(),
//					rhs.shrink(),
//					speciesThermo_
//					),
//				rr
//				)
//		);
//	}
//	break;
//
//	default:
//
//		if (rType < 3)
//		{
//			FatalErrorInFunction
//				<< "Reaction type " << reactionTypeNames[rType]
//				<< " on line " << lineNo_ - 1
//				<< " not handled by this function"
//				<< exit(FatalError);
//		}
//		else
//		{
//			FatalErrorInFunction
//				<< "Unknown reaction type " << rType
//				<< " on line " << lineNo_ - 1
//				<< exit(FatalError);
//		}
//	}
//}
//
//template<template<class, class> class PressureDependencyType>
//void tnbLib::chemkinReader::addPressureDependentReaction
//(
//	const reactionType rType,
//	const fallOffFunctionType fofType,
//	DynamicList<specieCoeffs>& lhs,
//	DynamicList<specieCoeffs>& rhs,
//	const scalarList& efficiencies,
//	const scalarList& k0Coeffs,
//	const scalarList& kInfCoeffs,
//	const HashTable<scalarList>& reactionCoeffsTable,
//	const scalar Afactor0,
//	const scalar AfactorInf,
//	const scalar RR
//)
//{
//	checkCoeffs(k0Coeffs, "k0", 3);
//	checkCoeffs(kInfCoeffs, "kInf", 3);
//
//	switch (fofType)
//	{
//	case Lindemann:
//	{
//		addReactionType
//		(
//			rType,
//			lhs, rhs,
//			PressureDependencyType
//			<ArrheniusReactionRate, LindemannFallOffFunction>
//			(
//				ArrheniusReactionRate
//				(
//					Afactor0*k0Coeffs[0],
//					k0Coeffs[1],
//					k0Coeffs[2] / RR
//				),
//				ArrheniusReactionRate
//				(
//					AfactorInf*kInfCoeffs[0],
//					kInfCoeffs[1],
//					kInfCoeffs[2] / RR
//				),
//				LindemannFallOffFunction(),
//				thirdBodyEfficiencies(speciesTable_, efficiencies)
//				)
//		);
//		break;
//	}
//	case Troe:
//	{
//		scalarList TroeCoeffs
//		(
//			reactionCoeffsTable[fallOffFunctionNames[fofType]]
//		);
//
//		if (TroeCoeffs.size() != 4 && TroeCoeffs.size() != 3)
//		{
//			FatalErrorInFunction
//				<< "Wrong number of coefficients for Troe rate expression"
//				" on line " << lineNo_ - 1 << ", should be 3 or 4 but "
//				<< TroeCoeffs.size() << " supplied." << nl
//				<< "Coefficients are "
//				<< TroeCoeffs << nl
//				<< exit(FatalError);
//		}
//
//		if (TroeCoeffs.size() == 3)
//		{
//			TroeCoeffs.setSize(4);
//			TroeCoeffs[3] = great;
//		}
//
//		addReactionType
//		(
//			rType,
//			lhs, rhs,
//			PressureDependencyType
//			<ArrheniusReactionRate, TroeFallOffFunction>
//			(
//				ArrheniusReactionRate
//				(
//					Afactor0*k0Coeffs[0],
//					k0Coeffs[1],
//					k0Coeffs[2] / RR
//				),
//				ArrheniusReactionRate
//				(
//					AfactorInf*kInfCoeffs[0],
//					kInfCoeffs[1],
//					kInfCoeffs[2] / RR
//				),
//				TroeFallOffFunction
//				(
//					TroeCoeffs[0],
//					TroeCoeffs[1],
//					TroeCoeffs[2],
//					TroeCoeffs[3]
//				),
//				thirdBodyEfficiencies(speciesTable_, efficiencies)
//				)
//		);
//		break;
//	}
//	case SRI:
//	{
//		scalarList SRICoeffs
//		(
//			reactionCoeffsTable[fallOffFunctionNames[fofType]]
//		);
//
//		if (SRICoeffs.size() != 5 && SRICoeffs.size() != 3)
//		{
//			FatalErrorInFunction
//				<< "Wrong number of coefficients for SRI rate expression"
//				" on line " << lineNo_ - 1 << ", should be 3 or 5 but "
//				<< SRICoeffs.size() << " supplied." << nl
//				<< "Coefficients are "
//				<< SRICoeffs << nl
//				<< exit(FatalError);
//		}
//
//		if (SRICoeffs.size() == 3)
//		{
//			SRICoeffs.setSize(5);
//			SRICoeffs[3] = 1.0;
//			SRICoeffs[4] = 0.0;
//		}
//
//		addReactionType
//		(
//			rType,
//			lhs, rhs,
//			PressureDependencyType
//			<ArrheniusReactionRate, SRIFallOffFunction>
//			(
//				ArrheniusReactionRate
//				(
//					Afactor0*k0Coeffs[0],
//					k0Coeffs[1],
//					k0Coeffs[2] / RR
//				),
//				ArrheniusReactionRate
//				(
//					AfactorInf*kInfCoeffs[0],
//					kInfCoeffs[1],
//					kInfCoeffs[2] / RR
//				),
//				SRIFallOffFunction
//				(
//					SRICoeffs[0],
//					SRICoeffs[1],
//					SRICoeffs[2],
//					SRICoeffs[3],
//					SRICoeffs[4]
//				),
//				thirdBodyEfficiencies(speciesTable_, efficiencies)
//				)
//		);
//		break;
//	}
//	default:
//	{
//		FatalErrorInFunction
//			<< "Fall-off function type "
//			<< fallOffFunctionNames[fofType]
//			<< " on line " << lineNo_ - 1
//			<< " not implemented"
//			<< exit(FatalError);
//	}
//	}
//}


void tnbLib::chemkinReader::addReaction
(
	DynamicList<specieCoeffs>& lhs,
	DynamicList<specieCoeffs>& rhs,
	const scalarList& efficiencies,
	const reactionType rType,
	const reactionRateType rrType,
	const fallOffFunctionType fofType,
	const scalarList& ArrheniusCoeffs,
	HashTable<scalarList>& reactionCoeffsTable,
	const scalar RR
)
{
	checkCoeffs(ArrheniusCoeffs, "Arrhenius", 3);

	scalarList nAtoms(elementNames_.size(), 0.0);

	forAll(lhs, i)
	{
		const List<specieElement>& specieComposition =
			speciesComposition_[speciesTable_[lhs[i].index]];

		forAll(specieComposition, j)
		{
			label elementi = elementIndices_[specieComposition[j].name()];
			nAtoms[elementi] +=
				lhs[i].stoichCoeff*specieComposition[j].nAtoms();
		}
	}

	forAll(rhs, i)
	{
		const List<specieElement>& specieComposition =
			speciesComposition_[speciesTable_[rhs[i].index]];

		forAll(specieComposition, j)
		{
			label elementi = elementIndices_[specieComposition[j].name()];
			nAtoms[elementi] -=
				rhs[i].stoichCoeff*specieComposition[j].nAtoms();
		}
	}


	// Calculate the unit conversion factor for the A coefficient
	// for the change from mol/cm^3 to kmol/m^3 concentraction units
	const scalar concFactor = 0.001;
	scalar sumExp = 0.0;
	forAll(lhs, i)
	{
		sumExp += lhs[i].exponent;
	}
	scalar Afactor = pow(concFactor, sumExp - 1.0);

	scalar AfactorRev = Afactor;

	if (rType == nonEquilibriumReversible)
	{
		sumExp = 0.0;
		forAll(rhs, i)
		{
			sumExp += rhs[i].exponent;
		}
		AfactorRev = pow(concFactor, sumExp - 1.0);
	}

	switch (rrType)
	{
	case Arrhenius:
	{
		if (rType == nonEquilibriumReversible)
		{
			const scalarList& reverseArrheniusCoeffs =
				reactionCoeffsTable[reactionTypeNames[rType]];

			checkCoeffs(reverseArrheniusCoeffs, "reverse Arrhenius", 3);

			reactions_.append
			(
				new NonEquilibriumReversibleReaction
				<Reaction, gasHThermoPhysics, ArrheniusReactionRate>
				(
					ReactionProxy<gasHThermoPhysics>
					(
						speciesTable_,
						lhs.shrink(),
						rhs.shrink(),
						speciesThermo_
						),
					ArrheniusReactionRate
					(
						Afactor*ArrheniusCoeffs[0],
						ArrheniusCoeffs[1],
						ArrheniusCoeffs[2] / RR
					),
					ArrheniusReactionRate
					(
						AfactorRev*reverseArrheniusCoeffs[0],
						reverseArrheniusCoeffs[1],
						reverseArrheniusCoeffs[2] / RR
					)
					)
			);
		}
		else
		{
			addReactionType
			(
				rType,
				lhs, rhs,
				ArrheniusReactionRate
				(
					Afactor*ArrheniusCoeffs[0],
					ArrheniusCoeffs[1],
					ArrheniusCoeffs[2] / RR
				)
			);
		}
		break;
	}
	case thirdBodyArrhenius:
	{
		if (rType == nonEquilibriumReversible)
		{
			const scalarList& reverseArrheniusCoeffs =
				reactionCoeffsTable[reactionTypeNames[rType]];

			checkCoeffs(reverseArrheniusCoeffs, "reverse Arrhenius", 3);

			reactions_.append
			(
				new NonEquilibriumReversibleReaction
				<
				Reaction,
				gasHThermoPhysics,
				thirdBodyArrheniusReactionRate
				>
				(
					ReactionProxy<gasHThermoPhysics>
					(
						speciesTable_,
						lhs.shrink(),
						rhs.shrink(),
						speciesThermo_
						),
					thirdBodyArrheniusReactionRate
					(
						Afactor*concFactor*ArrheniusCoeffs[0],
						ArrheniusCoeffs[1],
						ArrheniusCoeffs[2] / RR,
						thirdBodyEfficiencies(speciesTable_, efficiencies)
					),
					thirdBodyArrheniusReactionRate
					(
						AfactorRev*concFactor*reverseArrheniusCoeffs[0],
						reverseArrheniusCoeffs[1],
						reverseArrheniusCoeffs[2] / RR,
						thirdBodyEfficiencies(speciesTable_, efficiencies)
					)
					)
			);
		}
		else
		{
			addReactionType
			(
				rType,
				lhs, rhs,
				thirdBodyArrheniusReactionRate
				(
					Afactor*concFactor*ArrheniusCoeffs[0],
					ArrheniusCoeffs[1],
					ArrheniusCoeffs[2] / RR,
					thirdBodyEfficiencies(speciesTable_, efficiencies)
				)
			);
		}
		break;
	}
	case unimolecularFallOff:
	{
		addPressureDependentReaction<FallOffReactionRate>
			(
				rType,
				fofType,
				lhs,
				rhs,
				efficiencies,
				reactionCoeffsTable[reactionRateTypeNames[rrType]],
				ArrheniusCoeffs,
				reactionCoeffsTable,
				concFactor*Afactor,
				Afactor,
				RR
				);
		break;
	}
	case chemicallyActivatedBimolecular:
	{
		addPressureDependentReaction<ChemicallyActivatedReactionRate>
			(
				rType,
				fofType,
				lhs,
				rhs,
				efficiencies,
				ArrheniusCoeffs,
				reactionCoeffsTable[reactionRateTypeNames[rrType]],
				reactionCoeffsTable,
				Afactor,
				Afactor / concFactor,
				RR
				);
		break;
	}
	case LandauTeller:
	{
		const scalarList& LandauTellerCoeffs =
			reactionCoeffsTable[reactionRateTypeNames[rrType]];
		checkCoeffs(LandauTellerCoeffs, "Landau-Teller", 2);

		if (rType == nonEquilibriumReversible)
		{
			const scalarList& reverseArrheniusCoeffs =
				reactionCoeffsTable[reactionTypeNames[rType]];
			checkCoeffs(reverseArrheniusCoeffs, "reverse Arrhenius", 3);

			const scalarList& reverseLandauTellerCoeffs =
				reactionCoeffsTable
				[
					word(reactionTypeNames[rType])
					+ reactionRateTypeNames[rrType]
				];
			checkCoeffs(LandauTellerCoeffs, "reverse Landau-Teller", 2);

			reactions_.append
			(
				new NonEquilibriumReversibleReaction
				<
				Reaction,
				gasHThermoPhysics,
				LandauTellerReactionRate
				>
				(
					ReactionProxy<gasHThermoPhysics>
					(
						speciesTable_,
						lhs.shrink(),
						rhs.shrink(),
						speciesThermo_
						),
					LandauTellerReactionRate
					(
						Afactor*ArrheniusCoeffs[0],
						ArrheniusCoeffs[1],
						ArrheniusCoeffs[2] / RR,
						LandauTellerCoeffs[0],
						LandauTellerCoeffs[1]
					),
					LandauTellerReactionRate
					(
						AfactorRev*reverseArrheniusCoeffs[0],
						reverseArrheniusCoeffs[1],
						reverseArrheniusCoeffs[2] / RR,
						reverseLandauTellerCoeffs[0],
						reverseLandauTellerCoeffs[1]
					)
					)
			);
		}
		else
		{
			addReactionType
			(
				rType,
				lhs, rhs,
				LandauTellerReactionRate
				(
					Afactor*ArrheniusCoeffs[0],
					ArrheniusCoeffs[1],
					ArrheniusCoeffs[2] / RR,
					LandauTellerCoeffs[0],
					LandauTellerCoeffs[1]
				)
			);
		}
		break;
	}
	case Janev:
	{
		const scalarList& JanevCoeffs =
			reactionCoeffsTable[reactionRateTypeNames[rrType]];

		checkCoeffs(JanevCoeffs, "Janev", 9);

		addReactionType
		(
			rType,
			lhs, rhs,
			JanevReactionRate
			(
				Afactor*ArrheniusCoeffs[0],
				ArrheniusCoeffs[1],
				ArrheniusCoeffs[2] / RR,
				FixedList<scalar, 9>(JanevCoeffs)
			)
		);
		break;
	}
	case powerSeries:
	{
		const scalarList& powerSeriesCoeffs =
			reactionCoeffsTable[reactionRateTypeNames[rrType]];

		checkCoeffs(powerSeriesCoeffs, "power-series", 4);

		addReactionType
		(
			rType,
			lhs, rhs,
			powerSeriesReactionRate
			(
				Afactor*ArrheniusCoeffs[0],
				ArrheniusCoeffs[1],
				ArrheniusCoeffs[2] / RR,
				FixedList<scalar, 4>(powerSeriesCoeffs)
			)
		);
		break;
	}
	case unknownReactionRateType:
	{
		FatalErrorInFunction
			<< "Internal error on line " << lineNo_ - 1
			<< ": reaction rate type has not been set"
			<< exit(FatalError);
		break;
	}
	default:
	{
		FatalErrorInFunction
			<< "Reaction rate type " << reactionRateTypeNames[rrType]
			<< " on line " << lineNo_ - 1
			<< " not implemented"
			<< exit(FatalError);
	}
	}


	forAll(nAtoms, i)
	{
		if (mag(nAtoms[i]) > imbalanceTol_)
		{
			FatalErrorInFunction
				<< "Elemental imbalance of " << mag(nAtoms[i])
				<< " in " << elementNames_[i]
				<< " in reaction" << nl
				<< reactions_.last() << nl
				<< " on line " << lineNo_ - 1
				<< exit(FatalError);
		}
	}

	lhs.clear();
	rhs.clear();
	reactionCoeffsTable.clear();
}


void tnbLib::chemkinReader::read
(
	const fileName& CHEMKINFileName,
	const fileName& thermoFileName,
	const fileName& transportFileName
)
{
	Reaction<gasHThermoPhysics>::TlowDefault = 0;
	Reaction<gasHThermoPhysics>::ThighDefault = great;

	transportDict_.read(IFstream(transportFileName)());

	if (thermoFileName != fileName::null)
	{
		std::ifstream thermoStream(thermoFileName.c_str());

		if (!thermoStream)
		{
			FatalErrorInFunction
				<< "file " << thermoFileName << " not found"
				<< exit(FatalError);
		}

		yy_buffer_state* bufferPtr(yy_create_buffer(&thermoStream, yyBufSize));
		yy_switch_to_buffer(bufferPtr);

		while (lex() != 0)
		{
		}

		yy_delete_buffer(bufferPtr);

		lineNo_ = 1;
	}

	std::ifstream CHEMKINStream(CHEMKINFileName.c_str());

	if (!CHEMKINStream)
	{
		FatalErrorInFunction
			<< "file " << CHEMKINFileName << " not found"
			<< exit(FatalError);
	}

	yy_buffer_state* bufferPtr(yy_create_buffer(&CHEMKINStream, yyBufSize));
	yy_switch_to_buffer(bufferPtr);

	initReactionKeywordTable();

	while (lex() != 0)
	{
	}

	yy_delete_buffer(bufferPtr);
}


// * * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * //

tnbLib::chemkinReader::chemkinReader
(
	speciesTable& species,
	const fileName& CHEMKINFileName,
	const fileName& transportFileName,
	const fileName& thermoFileName,
	const bool newFormat
)
	:
	lineNo_(1),
	specieNames_(10),
	speciesTable_(species),
	reactions_(speciesTable_, speciesThermo_),
	newFormat_(newFormat),
	imbalanceTol_(rootSmall)
{
	read(CHEMKINFileName, thermoFileName, transportFileName);
}


tnbLib::chemkinReader::chemkinReader
(
	const dictionary& thermoDict,
	speciesTable& species
)
	:
	lineNo_(1),
	specieNames_(10),
	speciesTable_(species),
	reactions_(speciesTable_, speciesThermo_),
	newFormat_(thermoDict.lookupOrDefault("newFormat", false)),
	imbalanceTol_(thermoDict.lookupOrDefault("imbalanceTolerance", rootSmall))
{
	if (newFormat_)
	{
		Info << "Reading CHEMKIN thermo data in new file format" << endl;
	}

	fileName chemkinFile(fileName(thermoDict.lookup("CHEMKINFile")).expand());

	fileName thermoFile = fileName::null;

	if (thermoDict.found("CHEMKINThermoFile"))
	{
		thermoFile = fileName(thermoDict.lookup("CHEMKINThermoFile")).expand();
	}

	fileName transportFile
	(
		fileName(thermoDict.lookup("CHEMKINTransportFile")).expand()
	);

	// allow relative file names
	fileName relPath = thermoDict.name().path();
	if (relPath.size())
	{
		if (!chemkinFile.isAbsolute())
		{
			chemkinFile = relPath / chemkinFile;
		}

		if (thermoFile != fileName::null && !thermoFile.isAbsolute())
		{
			thermoFile = relPath / thermoFile;
		}

		if (!transportFile.isAbsolute())
		{
			transportFile = relPath / transportFile;
		}
	}

	read(chemkinFile, thermoFile, transportFile);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //