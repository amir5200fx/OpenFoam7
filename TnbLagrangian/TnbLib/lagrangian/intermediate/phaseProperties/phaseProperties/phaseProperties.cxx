#include <phaseProperties.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::phaseProperties::phaseType,
		4
		>::names[] =
	{
		"gas",
		"liquid",
		"solid",
		"unknown"
	};
}

const tnbLib::NamedEnum<tnbLib::phaseProperties::phaseType, 4>
tnbLib::phaseProperties::phaseTypeNames;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::phaseProperties::reorder(const wordList& specieNames)
{
	// ***HGW Unfortunately in the current implementation it is assumed that
	// if no species are specified the phase is not present and this MUST
	// be checked at the point of use.  This needs a rewrite.
	if (!names_.size())
	{
		return;
	}

	// Store the current sames and mass-fractions
	List<word> names0(names_);
	scalarField Y0(Y_);

	// Update the specie names to those given
	names_ = specieNames;

	// Re-size mass-fractions if necessary, initialize to 0
	if (names_.size() != names0.size())
	{
		Y_.setSize(names_.size());
		Y_ = 0;
	}

	// Set the mass-fraction for each specie in the list to the corresponding
	// value in the original list
	forAll(names0, i)
	{
		bool found = false;
		forAll(names_, j)
		{
			if (names_[j] == names0[i])
			{
				Y_[j] = Y0[i];
				found = true;
				break;
			}
		}

		if (!found)
		{
			FatalErrorInFunction
				<< "Could not find specie " << names0[i]
				<< " in list " << names_
				<< " for phase " << phaseTypeNames[phase_]
				<< exit(FatalError);
		}
	}
}


void tnbLib::phaseProperties::setCarrierIds
(
	const wordList& carrierNames
)
{
	carrierIds_ = -1;

	forAll(names_, i)
	{
		forAll(carrierNames, j)
		{
			if (carrierNames[j] == names_[i])
			{
				carrierIds_[i] = j;
				break;
			}
		}
		if (carrierIds_[i] == -1)
		{
			FatalErrorInFunction
				<< "Could not find carrier specie " << names_[i]
				<< " in species list" << nl
				<< "Available species are: " << nl << carrierNames << nl
				<< exit(FatalError);
		}
	}
}


void tnbLib::phaseProperties::checkTotalMassFraction() const
{
	scalar total = 0.0;
	forAll(Y_, speciei)
	{
		total += Y_[speciei];
	}

	if (Y_.size() != 0 && mag(total - 1.0) > small)
	{
		FatalErrorInFunction
			<< "Specie fractions must total to unity for phase "
			<< phaseTypeNames[phase_] << nl
			<< "Species: " << nl << names_ << nl
			<< exit(FatalError);
	}
}


tnbLib::word tnbLib::phaseProperties::phaseToStateLabel(const phaseType pt) const
{
	word state = "(unknown)";
	switch (pt)
	{
	case GAS:
	{
		state = "(g)";
		break;
	}
	case LIQUID:
	{
		state = "(l)";
		break;
	}
	case SOLID:
	{
		state = "(s)";
		break;
	}
	default:
	{
		FatalErrorInFunction
			<< "Invalid phase: " << phaseTypeNames[pt] << nl
			<< "    phase must be gas, liquid or solid" << nl
			<< exit(FatalError);
	}
	}

	return state;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::phaseProperties::phaseProperties()
	:
	phase_(UNKNOWN),
	stateLabel_("(unknown)"),
	names_(0),
	Y_(0),
	carrierIds_(0)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::phaseProperties::~phaseProperties()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::phaseProperties::reorder
(
	const wordList& gasNames,
	const wordList& liquidNames,
	const wordList& solidNames
)
{
	// Determine the addressing to map between species listed in the phase
	// with those given in the (main) thermo properties
	switch (phase_)
	{
	case GAS:
	{
		// The list of gaseous species in the mixture may be a sub-set of
		// the gaseous species in the carrier phase
		setCarrierIds(gasNames);
		break;
	}
	case LIQUID:
	{
		// Set the list of liquid species to correspond to the complete list
		// defined in the thermodynamics package.
		reorder(liquidNames);
		// Set the ids of the corresponding species in the carrier phase
		setCarrierIds(gasNames);
		break;
	}
	case SOLID:
	{
		// Set the list of solid species to correspond to the complete list
		// defined in the thermodynamics package.
		reorder(solidNames);
		// Assume there is no correspondence between the solid species and
		// the species in the carrier phase (no sublimation).
		break;
	}
	default:
	{
		FatalErrorInFunction
			<< "Invalid phase: " << phaseTypeNames[phase_] << nl
			<< "    phase must be gas, liquid or solid" << nl
			<< exit(FatalError);
	}
	}
}


tnbLib::phaseProperties::phaseType tnbLib::phaseProperties::phase() const
{
	return phase_;
}


const tnbLib::word& tnbLib::phaseProperties::stateLabel() const
{
	return stateLabel_;
}


tnbLib::word tnbLib::phaseProperties::phaseTypeName() const
{
	return phaseTypeNames[phase_];
}


const tnbLib::List<tnbLib::word>& tnbLib::phaseProperties::names() const
{
	return names_;
}


const tnbLib::word& tnbLib::phaseProperties::name(const label speciei) const
{
	if (speciei >= names_.size())
	{
		FatalErrorInFunction
			<< "Requested specie " << speciei << "out of range" << nl
			<< "Available phase species:" << nl << names_ << nl
			<< exit(FatalError);
	}

	return names_[speciei];
}


const tnbLib::scalarField& tnbLib::phaseProperties::Y() const
{
	return Y_;
}


tnbLib::scalar& tnbLib::phaseProperties::Y(const label speciei)
{
	if (speciei >= Y_.size())
	{
		FatalErrorInFunction
			<< "Requested specie " << speciei << "out of range" << nl
			<< "Available phase species:" << nl << names_ << nl
			<< exit(FatalError);
	}

	return Y_[speciei];
}


const tnbLib::labelList& tnbLib::phaseProperties::carrierIds() const
{
	return carrierIds_;
}


tnbLib::label tnbLib::phaseProperties::id(const word& specieName) const
{
	forAll(names_, speciei)
	{
		if (names_[speciei] == specieName)
		{
			return speciei;
		}
	}

	return -1;
}

//- added by amir
bool tnbLib::phaseProperties::operator==(const phaseProperties & p) const
{
	notImplemented("bool tnbLib::phaseProperties::operator==(const phaseProperties & p) const");
	return true;
}

bool tnbLib::phaseProperties::operator!=(const phaseProperties & p) const
{
	return !operator==(p);
}

// ************************************************************************* //