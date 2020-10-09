#include <codedFunctionObject.hxx>

#include <volFields.hxx>
#include <dictionary.hxx>
#include <Time.hxx>
#include <SHA1Digest.hxx>
#include <dynamicCode.hxx>
#include <dynamicCodeContext.hxx>
#include <stringOps.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * Protected Static Data Members * * * * * * * * * * * //

const tnbLib::wordList tnbLib::codedFunctionObject::codeKeys_ =
{
	"codeData",
	"codeEnd",
	"codeExecute",
	"codeInclude",
	"codeRead",
	"codeWrite",
	"localCode"
};


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(codedFunctionObject, 0);

	addToRunTimeSelectionTable
	(
		functionObject,
		codedFunctionObject,
		dictionary
	);
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::codedFunctionObject::prepare
(
	dynamicCode& dynCode,
	const dynamicCodeContext& context
) const
{
	cout << "added by amir: check this function" << std::endl   //- added by amir
		<< FUNCTION_NAME << std::endl;
	dynCode.setFilterVariable("typeName", name_);

	// Compile filtered C template
	dynCode.addCompileFile("functionObjectTemplate.C");

	// Copy filtered H template
	dynCode.addCopyFile("functionObjectTemplate.H");

	// Debugging: make BC verbose
	// dynCode.setFilterVariable("verbose", "true");
	// Info<<"compile " << name_ << " sha1: "
	//     << context.sha1() << endl;

	// Define Make/options
	dynCode.setMakeOptions
	(
		"EXE_INC = -g \\\n"
		"-I$(LIB_SRC)/finiteVolume/lnInclude \\\n"
		"-I$(LIB_SRC)/meshTools/lnInclude \\\n"
		+ context.options()
		+ "\n\nLIB_LIBS = \\\n"
		+ "    -lOpenFOAM \\\n"
		+ "    -lfiniteVolume \\\n"
		+ "    -lmeshTools \\\n"
		+ context.libs()
	);
}


tnbLib::dlLibraryTable& tnbLib::codedFunctionObject::libs() const
{
	return const_cast<Time&>(time_).libs();
}


tnbLib::string tnbLib::codedFunctionObject::description() const
{
	return "functionObject " + name();
}


void tnbLib::codedFunctionObject::clearRedirect() const
{
	redirectFunctionObjectPtr_.clear();
}


const tnbLib::dictionary& tnbLib::codedFunctionObject::codeDict() const
{
	return dict_;
}


const tnbLib::wordList& tnbLib::codedFunctionObject::codeKeys() const
{
	return codeKeys_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::codedFunctionObject::codedFunctionObject
(
	const word& name,
	const Time& time,
	const dictionary& dict
)
	:
	functionObject(name),
	codedBase(),
	time_(time),
	dict_(dict)
{
	read(dict_);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::codedFunctionObject::~codedFunctionObject()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::functionObject& tnbLib::codedFunctionObject::redirectFunctionObject() const
{
	if (!redirectFunctionObjectPtr_.valid())
	{
		dictionary constructDict(dict_);
		constructDict.set("type", name_);

		redirectFunctionObjectPtr_ = functionObject::New
		(
			name_,
			time_,
			constructDict
		);
	}
	return redirectFunctionObjectPtr_();
}


bool tnbLib::codedFunctionObject::execute()
{
	updateLibrary(name_);
	return redirectFunctionObject().execute();
}


bool tnbLib::codedFunctionObject::write()
{
	updateLibrary(name_);
	return redirectFunctionObject().write();
}


bool tnbLib::codedFunctionObject::end()
{
	updateLibrary(name_);
	return redirectFunctionObject().end();
}


bool tnbLib::codedFunctionObject::read(const dictionary& dict)
{
	// The name keyword is "name". "redirectType" is also maintained here
	// for backwards compatibility, but "name" is taken in preference and
	// is printed in the error message if neither keyword is present.
	name_ = word::null;
	name_ = dict.lookupOrDefault("redirectType", name_);
	name_ = dict.lookupOrDefault("name", name_);
	if (name_ == word::null)
	{
		dict.lookup("name"); // <-- generate error message with "name" in it
	}

	updateLibrary(name_);
	return redirectFunctionObject().read(dict);
}


// ************************************************************************* //