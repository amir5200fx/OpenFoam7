#include <fieldAverageItem.hxx>

#include <IOstreams.hxx>
#include <dictionaryEntry.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldAverageItem::fieldAverageItem(Istream& is)
	:
	fieldName_("unknown"),
	mean_(0),
	meanFieldName_("unknown"),
	prime2Mean_(0),
	prime2MeanFieldName_("unknown"),
	base_(baseType::iter),
	window_(-1.0)
{
	is.check
	(
		"tnbLib::functionObjects::fieldAverageItem::fieldAverageItem"
		"(tnbLib::Istream&)"
	);

	const dictionaryEntry entry(dictionary::null, is);

	fieldName_ = entry.keyword();
	entry.lookup("mean") >> mean_;
	entry.lookup("prime2Mean") >> prime2Mean_;
	base_ = baseTypeNames_[entry.lookup("base")];
	window_ = entry.lookupOrDefault<scalar>("window", -1.0);
	windowName_ = entry.lookupOrDefault<word>("windowName", "");

	meanFieldName_ = fieldName_ + EXT_MEAN;
	prime2MeanFieldName_ = fieldName_ + EXT_PRIME2MEAN;
	if ((window_ > 0) && (windowName_ != ""))
	{
		meanFieldName_ = meanFieldName_ + "_" + windowName_;
		prime2MeanFieldName_ = prime2MeanFieldName_ + "_" + windowName_;
	}
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

FoamFunctionObjects_EXPORT tnbLib::Istream& tnbLib::functionObjects::operator>>
(
	Istream& is,
	fieldAverageItem& faItem
	)
{
	is.check
	(
		"tnbLib::Istream& tnbLib::operator>>"
		"(tnbLib::Istream&, tnbLib::functionObjects::fieldAverageItem&)"
	);

	const dictionaryEntry entry(dictionary::null, is);

	faItem.fieldName_ = entry.keyword();
	entry.lookup("mean") >> faItem.mean_;
	entry.lookup("prime2Mean") >> faItem.prime2Mean_;
	faItem.base_ = faItem.baseTypeNames_[entry.lookup("base")];
	faItem.window_ = entry.lookupOrDefault<scalar>("window", -1.0);
	faItem.windowName_ = entry.lookupOrDefault<word>("windowName", "");

	faItem.meanFieldName_ = faItem.fieldName_ + fieldAverageItem::EXT_MEAN;
	faItem.prime2MeanFieldName_ =
		faItem.fieldName_ + fieldAverageItem::EXT_PRIME2MEAN;

	if ((faItem.window_ > 0) && (faItem.windowName_ != ""))
	{
		faItem.meanFieldName_ =
			faItem.meanFieldName_ + "_" + faItem.windowName_;

		faItem.prime2MeanFieldName_ =
			faItem.prime2MeanFieldName_ + "_" + faItem.windowName_;
	}
	return is;
}


FoamFunctionObjects_EXPORT tnbLib::Ostream& tnbLib::functionObjects::operator<<
(
	Ostream& os,
	const fieldAverageItem& faItem
	)
{
	os.check
	(
		"tnbLib::Ostream& tnbLib::operator<<"
		"(tnbLib::Ostream&, const tnbLib::functionObjects::fieldAverageItem&)"
	);

	os << faItem.fieldName_ << nl << token::BEGIN_BLOCK << nl;

	writeEntry(os, "mean", faItem.mean_);
	writeEntry(os, "prime2Mean", faItem.prime2Mean_);
	writeEntry(os, "base", faItem.baseTypeNames_[faItem.base_]);

	if (faItem.window_ > 0)
	{
		writeEntry(os, "window", faItem.window_);

		if (faItem.windowName_ != "")
		{
			writeEntry(os, "windowName", faItem.windowName_);
		}
	}

	os << token::END_BLOCK << nl;

	os.check
	(
		"tnbLib::Ostream& tnbLib::operator<<"
		"(tnbLib::Ostream&, const tnbLib::functionObjects::fieldAverageItem&)"
	);

	return os;
}


// ************************************************************************* //