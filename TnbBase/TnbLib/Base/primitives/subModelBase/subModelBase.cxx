#include <subModelBase.hxx>

// * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

bool tnbLib::subModelBase::subModelBase::inLine() const
{
	return (modelName_ != word::null);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::subModelBase::subModelBase(dictionary& properties)
	:
	modelName_(word::null),
	properties_(properties),
	dict_(dictionary::null),
	baseName_(word::null),
	modelType_(word::null),
	coeffDict_(dictionary::null)
{}


tnbLib::subModelBase::subModelBase
(
	dictionary& properties,
	const dictionary& dict,
	const word& baseName,
	const word& modelType,
	const word& dictExt
)
	:
	modelName_(word::null),
	properties_(properties),
	dict_(dict),
	baseName_(baseName),
	modelType_(modelType),
	coeffDict_(dict.subDict(modelType + dictExt))
{}


tnbLib::subModelBase::subModelBase
(
	const word& modelName,
	dictionary& properties,
	const dictionary& dict,
	const word& baseName,
	const word& modelType
)
	:
	modelName_(modelName),
	properties_(properties),
	dict_(dict),
	baseName_(baseName),
	modelType_(modelType),
	coeffDict_(dict)
{}


tnbLib::subModelBase::subModelBase(const subModelBase& smb)
	:
	modelName_(smb.modelName_),
	properties_(smb.properties_),
	dict_(smb.dict_),
	baseName_(smb.baseName_),
	modelType_(smb.modelType_),
	coeffDict_(smb.coeffDict_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::subModelBase::~subModelBase()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::word& tnbLib::subModelBase::modelName() const
{
	return modelName_;
}


const tnbLib::dictionary& tnbLib::subModelBase::dict() const
{
	return dict_;
}


const tnbLib::word& tnbLib::subModelBase::baseName() const
{
	return baseName_;
}


const tnbLib::word& tnbLib::subModelBase::modelType() const
{
	return modelType_;
}


const tnbLib::dictionary& tnbLib::subModelBase::coeffDict() const
{
	return coeffDict_;
}


const tnbLib::dictionary& tnbLib::subModelBase::properties() const
{
	return properties_;
}


bool tnbLib::subModelBase::defaultCoeffs(const bool printMsg) const
{
	bool def = coeffDict_.lookupOrDefault<bool>("defaultCoeffs", false);
	if (printMsg && def)
	{
		Info << incrIndent;
		Info << indent << "Employing default coefficients" << endl;
		Info << decrIndent;
	}

	return def;
}


bool tnbLib::subModelBase::active() const
{
	return true;
}


void tnbLib::subModelBase::cacheFields(const bool)
{}


bool tnbLib::subModelBase::writeTime() const
{
	return active();
}


void tnbLib::subModelBase::write(Ostream& os) const
{
	os << coeffDict_;
}


// ************************************************************************* //
