#include <patchInteractionData.hxx>

#include <dictionaryEntry.hxx>
#include <PatchInteractionModel.hxx>

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

tnbLib::patchInteractionData::patchInteractionData()
	:
	interactionTypeName_("unknownInteractionTypeName"),
	patchName_("unknownPatch"),
	e_(0.0),
	mu_(0.0)
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

const tnbLib::word& tnbLib::patchInteractionData::interactionTypeName() const
{
	return interactionTypeName_;
}


const tnbLib::word& tnbLib::patchInteractionData::patchName() const
{
	return patchName_;
}


tnbLib::scalar tnbLib::patchInteractionData::e() const
{
	return e_;
}


tnbLib::scalar tnbLib::patchInteractionData::mu() const
{
	return mu_;
}

bool tnbLib::patchInteractionData::operator==(const patchInteractionData & p) const
{
	notImplemented("bool tnbLib::patchInteractionData::operator==(const patchInteractionData & p) const");
	return true;
}

bool tnbLib::patchInteractionData::operator!=(const patchInteractionData & p) const
{
	return !operator==(p);
}

// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

FoamLagrangian_EXPORT tnbLib::Ostream & tnbLib::operator<<
(
	Ostream & os,
	const patchInteractionData & pid
	)
{
	notImplemented("tnbLib::Ostream& tnbLib::operator<<(Ostream&, patchInteractionData &)");
	return os;
}

FoamLagrangian_EXPORT tnbLib::Istream& tnbLib::operator>>
(
	Istream& is,
	patchInteractionData& pid
	)
{
	is.check("Istream& operator>>(Istream&, patchInteractionData&)");

	const dictionaryEntry entry(dictionary::null, is);

	pid.patchName_ = entry.keyword();
	entry.lookup("type") >> pid.interactionTypeName_;
	pid.e_ = entry.lookupOrDefault<scalar>("e", 1.0);
	pid.mu_ = entry.lookupOrDefault<scalar>("mu", 0.0);

	return is;
}


// ************************************************************************* //