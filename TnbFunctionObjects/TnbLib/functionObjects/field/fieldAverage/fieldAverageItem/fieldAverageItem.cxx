#include <fieldAverageItem.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::word tnbLib::functionObjects::fieldAverageItem::EXT_MEAN
(
	"Mean"
);

const tnbLib::word tnbLib::functionObjects::fieldAverageItem::EXT_PRIME2MEAN
(
	"Prime2Mean"
);

template<>
const char* tnbLib::NamedEnum
<
	tnbLib::functionObjects::fieldAverageItem::baseType,
	2
>::names[] = { "iteration", "time" };

const tnbLib::NamedEnum
<
	tnbLib::functionObjects::fieldAverageItem::baseType,
	2
> tnbLib::functionObjects::fieldAverageItem::baseTypeNames_;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldAverageItem::fieldAverageItem()
	:
	fieldName_("unknown"),
	mean_(0),
	meanFieldName_("unknown"),
	prime2Mean_(0),
	prime2MeanFieldName_("unknown"),
	base_(baseType::iter),
	window_(-1.0),
	windowName_("")
{}


tnbLib::functionObjects::fieldAverageItem::fieldAverageItem
(
	const fieldAverageItem& faItem
)
	:
	fieldName_(faItem.fieldName_),
	mean_(faItem.mean_),
	meanFieldName_(faItem.meanFieldName_),
	prime2Mean_(faItem.prime2Mean_),
	prime2MeanFieldName_(faItem.prime2MeanFieldName_),
	base_(faItem.base_),
	window_(faItem.window_),
	windowName_(faItem.windowName_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldAverageItem::~fieldAverageItem()
{}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::functionObjects::fieldAverageItem::operator=
(
	const fieldAverageItem& rhs
	)
{
	// Check for assignment to self
	if (this == &rhs)
	{
		FatalErrorInFunction
			<< "Attempted assignment to self" << nl
			<< abort(FatalError);
	}

	// Set updated values
	fieldName_ = rhs.fieldName_;
	mean_ = rhs.mean_;
	meanFieldName_ = rhs.meanFieldName_;
	prime2Mean_ = rhs.prime2Mean_;
	prime2MeanFieldName_ = rhs.prime2MeanFieldName_;
	base_ = rhs.base_;
	window_ = rhs.window_;
	windowName_ = rhs.windowName_;
}


// ************************************************************************* //