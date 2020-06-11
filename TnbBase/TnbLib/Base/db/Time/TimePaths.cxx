#include <TimePaths.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::TimePaths::TimePaths
(
	const fileName& rootPath,
	const fileName& caseName,
	const word& systemName,
	const word& constantName
)
	:
	processorCase_(false),
	rootPath_(rootPath),
	case_(caseName),
	system_(systemName),
	constant_(constantName)
{
	// Find out from case name whether a processor directory
	std::string::size_type pos = caseName.find("processor");
	if (pos != string::npos)
	{
		processorCase_ = true;

		if (pos == 0)
		{
			globalCaseName_ = ".";
		}
		else
		{
			globalCaseName_ = caseName(pos - 1);
		}
	}
	else
	{
		globalCaseName_ = caseName;
	}
}


tnbLib::TimePaths::TimePaths
(
	const bool processorCase,
	const fileName& rootPath,
	const fileName& globalCaseName,
	const fileName& caseName,
	const word& systemName,
	const word& constantName
)
	:
	processorCase_(processorCase),
	rootPath_(rootPath),
	globalCaseName_(globalCaseName),
	case_(caseName),
	system_(systemName),
	constant_(constantName)
{
	if (!processorCase)
	{
		// For convenience: find out from case name whether it is a
		// processor directory and set processorCase flag so file searching
		// goes up one level.
		std::string::size_type pos = caseName.find("processor");

		if (pos != string::npos)
		{
			processorCase_ = true;

			if (pos == 0)
			{
				globalCaseName_ = ".";
			}
			else
			{
				globalCaseName_ = caseName(pos - 1);
			}
		}
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::fileName tnbLib::TimePaths::caseSystem() const
{
	if (processorCase_)
	{
		return ".." / system();
	}
	else
	{
		return system();
	}
}


tnbLib::fileName tnbLib::TimePaths::caseConstant() const
{
	if (processorCase_)
	{
		return ".." / constant();
	}
	else
	{
		return constant();
	}
}



// ************************************************************************* //