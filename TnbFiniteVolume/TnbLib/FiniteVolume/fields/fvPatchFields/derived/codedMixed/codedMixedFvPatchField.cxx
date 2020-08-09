#include <codedMixedFvPatchField.hxx>

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
const tnbLib::wordList tnbLib::codedMixedFvPatchField<Type>::codeKeys_ =
{ "code", "codeInclude", "localCode" };


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class Type>
const tnbLib::word tnbLib::codedMixedFvPatchField<Type>::codeTemplateC =
"mixedFvPatchFieldTemplate.C";

template<class Type>
const tnbLib::word tnbLib::codedMixedFvPatchField<Type>::codeTemplateH =
"mixedFvPatchFieldTemplate.H";


// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

template<class Type>
void tnbLib::codedMixedFvPatchField<Type>::setFieldTemplates
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
const tnbLib::IOdictionary& tnbLib::codedMixedFvPatchField<Type>::dict() const
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
tnbLib::dlLibraryTable& tnbLib::codedMixedFvPatchField<Type>::libs() const
{
	return const_cast<dlLibraryTable&>(this->db().time().libs());
}


template<class Type>
void tnbLib::codedMixedFvPatchField<Type>::prepare
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
const tnbLib::dictionary& tnbLib::codedMixedFvPatchField<Type>::codeDict()
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
const tnbLib::wordList& tnbLib::codedMixedFvPatchField<Type>::codeKeys() const
{
	return codeKeys_;
}


template<class Type>
tnbLib::string tnbLib::codedMixedFvPatchField<Type>::description() const
{
	return
		"patch "
		+ this->patch().name()
		+ " on field "
		+ this->internalField().name();
}


template<class Type>
void tnbLib::codedMixedFvPatchField<Type>::clearRedirect() const
{
	// remove instantiation of fvPatchField provided by library
	redirectPatchFieldPtr_.clear();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::codedMixedFvPatchField<Type>::codedMixedFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	mixedFvPatchField<Type>(p, iF),
	codedBase(),
	redirectPatchFieldPtr_()
{}


template<class Type>
tnbLib::codedMixedFvPatchField<Type>::codedMixedFvPatchField
(
	const codedMixedFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	mixedFvPatchField<Type>(ptf, p, iF, mapper),
	codedBase(),
	dict_(ptf.dict_),
	name_(ptf.name_),
	redirectPatchFieldPtr_()
{}


template<class Type>
tnbLib::codedMixedFvPatchField<Type>::codedMixedFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	mixedFvPatchField<Type>(p, iF, dict),
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
tnbLib::codedMixedFvPatchField<Type>::codedMixedFvPatchField
(
	const codedMixedFvPatchField<Type>& ptf
)
	:
	mixedFvPatchField<Type>(ptf),
	codedBase(),
	dict_(ptf.dict_),
	name_(ptf.name_),
	redirectPatchFieldPtr_()
{}


template<class Type>
tnbLib::codedMixedFvPatchField<Type>::codedMixedFvPatchField
(
	const codedMixedFvPatchField<Type>& ptf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	mixedFvPatchField<Type>(ptf, iF),
	codedBase(),
	dict_(ptf.dict_),
	name_(ptf.name_),
	redirectPatchFieldPtr_()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
const tnbLib::mixedFvPatchField<Type>&
tnbLib::codedMixedFvPatchField<Type>::redirectPatchField() const
{
	if (!redirectPatchFieldPtr_.valid())
	{
		// Construct a patch
		// Make sure to construct the patchfield with up-to-date value

		// Write the data from the mixed b.c.
		OStringStream os;
		mixedFvPatchField<Type>::write(os);
		IStringStream is(os.str());
		// Construct dictionary from it.
		dictionary dict(is);

		// Override the type to enforce the fvPatchField::New constructor
		// to choose our type
		dict.set("type", name_);

		redirectPatchFieldPtr_.set
		(
			dynamic_cast<mixedFvPatchField<Type>*>
			(
				fvPatchField<Type>::New
				(
					this->patch(),
					this->internalField(),
					dict
				).ptr()
				)
		);
	}
	return redirectPatchFieldPtr_();
}


template<class Type>
void tnbLib::codedMixedFvPatchField<Type>::updateCoeffs()
{
	if (this->updated())
	{
		return;
	}

	// Make sure library containing user-defined fvPatchField is up-to-date
	updateLibrary(name_);

	const mixedFvPatchField<Type>& fvp = redirectPatchField();

	const_cast<mixedFvPatchField<Type>&>(fvp).updateCoeffs();

	// Copy through coefficients
	this->refValue() = fvp.refValue();
	this->refGrad() = fvp.refGrad();
	this->valueFraction() = fvp.valueFraction();

	mixedFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void tnbLib::codedMixedFvPatchField<Type>::evaluate
(
	const Pstream::commsTypes commsType
)
{
	// Make sure library containing user-defined fvPatchField is up-to-date
	updateLibrary(name_);

	const mixedFvPatchField<Type>& fvp = redirectPatchField();

	// - updates the value of fvp (though not used)
	// - resets the updated() flag
	const_cast<mixedFvPatchField<Type>&>(fvp).evaluate(commsType);

	// Update the value (using the coefficients) locally
	mixedFvPatchField<Type>::evaluate(commsType);
}


template<class Type>
void tnbLib::codedMixedFvPatchField<Type>::write(Ostream& os) const
{
	mixedFvPatchField<Type>::write(os);
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