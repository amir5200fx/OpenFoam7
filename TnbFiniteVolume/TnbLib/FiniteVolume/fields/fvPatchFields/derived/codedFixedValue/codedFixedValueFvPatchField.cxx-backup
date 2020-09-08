#include <codedFixedValueFvPatchField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchFieldMapper.hxx>
#include <volFields.hxx>
#include <dynamicCode.hxx>
#include <dynamicCodeContext.hxx>
#include <stringOps.hxx>

#include <IStringStream.hxx>  // added by amir
#include <OStringStream.hxx>  // added by amir

// * * * * * * * * * * * * Private Static Data Members * * * * * * * * * * * //

template<class Type>
const tnbLib::wordList tnbLib::codedFixedValueFvPatchField<Type>::codeKeys_ =
{ "code", "codeInclude", "localCode" };


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class Type>
const tnbLib::word tnbLib::codedFixedValueFvPatchField<Type>::codeTemplateC =
"fixedValueFvPatchFieldTemplate.C";

template<class Type>
const tnbLib::word tnbLib::codedFixedValueFvPatchField<Type>::codeTemplateH =
"fixedValueFvPatchFieldTemplate.H";


// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

template<class Type>
void tnbLib::codedFixedValueFvPatchField<Type>::setFieldTemplates
(
	dynamicCode& dynCode
)
{
	word fieldType(pTraits<Type>::typeName);

	// template type for fvPatchField
	dynCode.setFilterVariable("TemplateType", fieldType);

	// Name for fvPatchField - eg, ScalarField, VectorField, ...
	fieldType[0] = toupper(fieldType[0]);
	dynCode.setFilterVariable("FieldType", fieldType + "Field");
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
const tnbLib::IOdictionary& tnbLib::codedFixedValueFvPatchField<Type>::dict() const
{
	const objectRegistry& obr = this->db();

	if (obr.foundObject<IOdictionary>("codeDict"))
	{
		return obr.lookupObject<IOdictionary>("codeDict");
	}
	else
	{
		return obr.store
		(
			new IOdictionary
			(
				IOobject
				(
					"codeDict",
					this->db().time().system(),
					this->db(),
					IOobject::MUST_READ_IF_MODIFIED,
					IOobject::NO_WRITE
				)
			)
		);
	}
}


template<class Type>
tnbLib::dlLibraryTable& tnbLib::codedFixedValueFvPatchField<Type>::libs() const
{
	return const_cast<dlLibraryTable&>(this->db().time().libs());
}


template<class Type>
void tnbLib::codedFixedValueFvPatchField<Type>::prepare
(
	dynamicCode& dynCode,
	const dynamicCodeContext& context
) const
{
	// take no chances - typeName must be identical to name_
	dynCode.setFilterVariable("typeName", name_);

	// set TemplateType and FieldType filter variables
	// (for fvPatchField)
	setFieldTemplates(dynCode);

	// compile filtered C template
	dynCode.addCompileFile(codeTemplateC);

	// copy filtered H template
	dynCode.addCopyFile(codeTemplateH);


	// debugging: make BC verbose
	//  dynCode.setFilterVariable("verbose", "true");
	//  Info<<"compile " << name_ << " sha1: "
	//      << context.sha1() << endl;

	// define Make/options
	dynCode.setMakeOptions
	(
		"EXE_INC = -g \\\n"
		"-I$(LIB_SRC)/finiteVolume/lnInclude \\\n"
		+ context.options()
		+ "\n\nLIB_LIBS = \\\n"
		+ "    -lOpenFOAM \\\n"
		+ "    -lfiniteVolume \\\n"
		+ context.libs()
	);
}


template<class Type>
const tnbLib::dictionary& tnbLib::codedFixedValueFvPatchField<Type>::codeDict()
const
{
	// use system/codeDict or in-line
	return
		(
			dict_.found("code")
			? dict_
			: this->dict().subDict(name_)
			);
}


template<class Type>
const tnbLib::wordList& tnbLib::codedFixedValueFvPatchField<Type>::codeKeys() const
{
	return codeKeys_;
}


template<class Type>
tnbLib::string tnbLib::codedFixedValueFvPatchField<Type>::description() const
{
	return
		"patch "
		+ this->patch().name()
		+ " on field "
		+ this->internalField().name();
}


template<class Type>
void tnbLib::codedFixedValueFvPatchField<Type>::clearRedirect() const
{
	// remove instantiation of fvPatchField provided by library
	redirectPatchFieldPtr_.clear();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::codedFixedValueFvPatchField<Type>::codedFixedValueFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedValueFvPatchField<Type>(p, iF),
	codedBase(),
	redirectPatchFieldPtr_()
{}


template<class Type>
tnbLib::codedFixedValueFvPatchField<Type>::codedFixedValueFvPatchField
(
	const codedFixedValueFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	fixedValueFvPatchField<Type>(ptf, p, iF, mapper),
	codedBase(),
	dict_(ptf.dict_),
	name_(ptf.name_),
	redirectPatchFieldPtr_()
{}


template<class Type>
tnbLib::codedFixedValueFvPatchField<Type>::codedFixedValueFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	fixedValueFvPatchField<Type>(p, iF, dict),
	codedBase(),
	dict_(dict),
	name_
	(
		dict.found("redirectType")
		? dict.lookup("redirectType")
		: dict.lookup("name")
	),
	redirectPatchFieldPtr_()
{
	updateLibrary(name_);
}


template<class Type>
tnbLib::codedFixedValueFvPatchField<Type>::codedFixedValueFvPatchField
(
	const codedFixedValueFvPatchField<Type>& ptf
)
	:
	fixedValueFvPatchField<Type>(ptf),
	codedBase(),
	dict_(ptf.dict_),
	name_(ptf.name_),
	redirectPatchFieldPtr_()
{}


template<class Type>
tnbLib::codedFixedValueFvPatchField<Type>::codedFixedValueFvPatchField
(
	const codedFixedValueFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	fixedValueFvPatchField<Type>(ptf, iF),
	codedBase(),
	dict_(ptf.dict_),
	name_(ptf.name_),
	redirectPatchFieldPtr_()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
const tnbLib::fvPatchField<Type>&
tnbLib::codedFixedValueFvPatchField<Type>::redirectPatchField() const
{
	if (!redirectPatchFieldPtr_.valid())
	{
		// Construct a patch
		// Make sure to construct the patchfield with up-to-date value

		OStringStream os;
		writeEntry(os, "type", name_);
		writeEntry(os, "value", *this);
		IStringStream is(os.str());
		dictionary dict(is);

		redirectPatchFieldPtr_.set
		(
			fvPatchField<Type>::New
			(
				this->patch(),
				this->internalField(),
				dict
			).ptr()
		);
	}
	return redirectPatchFieldPtr_();
}


template<class Type>
void tnbLib::codedFixedValueFvPatchField<Type>::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	// Make sure library containing user-defined fvPatchField is up-to-date
	updateLibrary(name_);

	const fvPatchField<Type>& fvp = redirectPatchField();

	const_cast<fvPatchField<Type>&>(fvp).updateCoeffs();

	// Copy through value
	this->operator==(fvp);

	fixedValueFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::codedFixedValueFvPatchField<Type>::evaluate
(
	const Pstream::commsTypes commsType
)
{
	// Make sure library containing user-defined fvPatchField is up-to-date
	updateLibrary(name_);

	const fvPatchField<Type>& fvp = redirectPatchField();

	const_cast<fvPatchField<Type>&>(fvp).evaluate(commsType);

	fixedValueFvPatchField<Type>::evaluate(commsType);
}


template<class Type>
void tnbLib::codedFixedValueFvPatchField<Type>::write(Ostream& os) const
{
	fixedValueFvPatchField<Type>::write(os);
	os.writeKeyword("name") << name_
		<< token::END_STATEMENT << nl;

	if (dict_.found("codeInclude"))
	{
		os.writeKeyword("codeInclude")
			<< token::HASH << token::BEGIN_BLOCK;

		os.writeQuoted(string(dict_["codeInclude"]), false)
			<< token::HASH << token::END_BLOCK
			<< token::END_STATEMENT << nl;
	}

	if (dict_.found("localCode"))
	{
		os.writeKeyword("localCode")
			<< token::HASH << token::BEGIN_BLOCK;

		os.writeQuoted(string(dict_["localCode"]), false)
			<< token::HASH << token::END_BLOCK
			<< token::END_STATEMENT << nl;
	}

	if (dict_.found("code"))
	{
		os.writeKeyword("code")
			<< token::HASH << token::BEGIN_BLOCK;

		os.writeQuoted(string(dict_["code"]), false)
			<< token::HASH << token::END_BLOCK
			<< token::END_STATEMENT << nl;
	}

	if (dict_.found("codeOptions"))
	{
		os.writeKeyword("codeOptions")
			<< token::HASH << token::BEGIN_BLOCK;

		os.writeQuoted(string(dict_["codeOptions"]), false)
			<< token::HASH << token::END_BLOCK
			<< token::END_STATEMENT << nl;
	}

	if (dict_.found("codeLibs"))
	{
		os.writeKeyword("codeLibs")
			<< token::HASH << token::BEGIN_BLOCK;

		os.writeQuoted(string(dict_["codeLibs"]), false)
			<< token::HASH << token::END_BLOCK
			<< token::END_STATEMENT << nl;
	}
}


// ************************************************************************* //