#include <phaseProperties.hxx>

#include <dictionaryEntry.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::phaseProperties::phaseProperties(Istream& is)
	:
	phase_(UNKNOWN),
	stateLabel_("(unknown)"),
	names_(0),
	Y_(0),
	carrierIds_(0)
{
	is.check("tnbLib::phaseProperties::phaseProperties(Istream& is)");

	dictionaryEntry phaseInfo(dictionary::null, is);

	phase_ = phaseTypeNames[phaseInfo.keyword()];
	stateLabel_ = phaseToStateLabel(phase_);

	if (phaseInfo.size() > 0)
	{
		label nComponents = phaseInfo.size();
		names_.setSize(nComponents, "unknownSpecie");
		Y_.setSize(nComponents, 0.0);
		carrierIds_.setSize(nComponents, -1);

		label cmptI = 0;
		forAllConstIter(IDLList<entry>, phaseInfo, iter)
		{
			names_[cmptI] = iter().keyword();
			Y_[cmptI] = readScalar(phaseInfo.lookup(names_[cmptI]));
			cmptI++;
		}

		checkTotalMassFraction();
	}
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

FoamLagrangian_EXPORT tnbLib::Istream& tnbLib::operator>>(Istream& is, phaseProperties& pp)
{
	is.check
	(
		"tnbLib::Istream& tnbLib::operator>>(Istream&, phaseProperties&)"
	);

	dictionaryEntry phaseInfo(dictionary::null, is);

	pp.phase_ = pp.phaseTypeNames[phaseInfo.keyword()];
	pp.stateLabel_ = pp.phaseToStateLabel(pp.phase_);

	if (phaseInfo.size() > 0)
	{
		label nComponents = phaseInfo.size();

		pp.names_.setSize(nComponents, "unknownSpecie");
		pp.Y_.setSize(nComponents, 0.0);
		pp.carrierIds_.setSize(nComponents, -1);

		label cmptI = 0;
		forAllConstIter(IDLList<entry>, phaseInfo, iter)
		{
			pp.names_[cmptI] = iter().keyword();
			pp.Y_[cmptI] = readScalar(phaseInfo.lookup(pp.names_[cmptI]));
			cmptI++;
		}

		pp.checkTotalMassFraction();
	}

	return is;
}


FoamLagrangian_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const phaseProperties& pp)
{
	os.check
	(
		"tnbLib::Ostream& tnbLib::operator<<(Ostream&, const phaseProperties&)"
	);

	os << pp.phaseTypeNames[pp.phase_] << nl << token::BEGIN_BLOCK << nl
		<< incrIndent;

	forAll(pp.names_, cmptI)
	{
		writeEntry(os, pp.names_[cmptI], pp.Y_[cmptI]);
	}

	os << decrIndent << token::END_BLOCK << nl;

	os.check
	(
		"tnbLib::Ostream& tnbLib::operator<<(Ostream&, const phaseProperties&)"
	);

	return os;
}


// ************************************************************************* //