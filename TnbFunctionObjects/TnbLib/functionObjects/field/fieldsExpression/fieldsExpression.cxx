#include <fieldsExpression.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(fieldsExpression, 0);
	}
}


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

void tnbLib::functionObjects::fieldsExpression::setResultName
(
	const word& typeName,
	const wordList& defaultArgs
)
{
	if (fieldNames_.empty())
	{
		fieldNames_ = defaultArgs;
	}

	if (resultName_.empty())
	{
		if (!fieldNames_.empty())
		{
			resultName_ = typeName + '(' + fieldNames_[0];
			for (label i = 1; i < fieldNames_.size(); i++)
			{
				resultName_ += ',' + fieldNames_[i];
			}
			resultName_ += ')';
		}
		else
		{
			resultName_ = typeName;
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldsExpression::fieldsExpression
(
	const word& name,
	const Time& runTime,
	const dictionary& dict,
	const wordList& fieldNames,
	const word& resultName
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	fieldNames_(fieldNames),
	resultName_(resultName)
{
	read(dict);

	if (fieldNames_.size() < 2)
	{
		FatalIOErrorInFunction(dict)
			<< "functionObject::" << type() << " " << name
			<< " requires at least 2 fields only "
			<< fieldNames_.size() << " provided: " << fieldNames_
			<< exit(FatalIOError);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldsExpression::~fieldsExpression()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::fieldsExpression::read(const dictionary& dict)
{
	fvMeshFunctionObject::read(dict);

	if (fieldNames_.empty() || dict.found("fields"))
	{
		dict.lookup("fields") >> fieldNames_;
	}

	if (dict.found("result"))
	{
		dict.lookup("result") >> resultName_;
	}

	return true;
}


bool tnbLib::functionObjects::fieldsExpression::execute()
{
	if (!calc())
	{
		Warning
			<< "    functionObjects::" << type() << " " << name()
			<< " cannot find required fields " << fieldNames_ << endl;

		// Clear the result fields from the objectRegistry if present
		clear();

		return false;
	}
	else
	{
		return true;
	}
}


bool tnbLib::functionObjects::fieldsExpression::write()
{
	return writeObject(resultName_);
}


bool tnbLib::functionObjects::fieldsExpression::clear()
{
	return clearObject(resultName_);
}


// ************************************************************************* //