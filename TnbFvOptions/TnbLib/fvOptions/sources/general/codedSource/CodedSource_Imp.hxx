#pragma once
#include <fvMesh.hxx>
#include <fvMatrices.hxx>
#include <dynamicCode.hxx>
#include <dynamicCodeContext.hxx>

// * * * * * * * * * * * Protected Static Data Members * * * * * * * * * * * //

template<class Type>
const tnbLib::wordList tnbLib::fv::CodedSource<Type>::codeKeys_ =
{ "codeAddSup", "codeCorrect", "codeInclude", "codeSetValue", "localCode" };


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::fv::CodedSource<Type>::prepare
(
	dynamicCode& dynCode,
	const dynamicCodeContext& context
) const
{
	word sourceType(pTraits<Type>::typeName);

	// Set additional rewrite rules
	dynCode.setFilterVariable("typeName", name_);
	dynCode.setFilterVariable("TemplateType", sourceType);
	dynCode.setFilterVariable("SourceType", sourceType + "Source");

	// compile filtered C template
	dynCode.addCompileFile("codedFvOptionTemplate.C");

	// copy filtered H template
	dynCode.addCopyFile("codedFvOptionTemplate.H");

	// debugging: make BC verbose
	//         dynCode.setFilterVariable("verbose", "true");
	//         Info<<"compile " << name_ << " sha1: "
	//             << context.sha1() << endl;

	// define Make/options
	dynCode.setMakeOptions
	(
		"EXE_INC = -g \\\n"
		"-I$(LIB_SRC)/finiteVolume/lnInclude \\\n"
		"-I$(LIB_SRC)/meshTools/lnInclude \\\n"
		"-I$(LIB_SRC)/sampling/lnInclude \\\n"
		"-I$(LIB_SRC)/fvOptions/lnInclude \\\n"
		+ context.options()
		+ "\n\nLIB_LIBS = \\\n"
		+ "    -lmeshTools \\\n"
		+ "    -lfvOptions \\\n"
		+ "    -lsampling \\\n"
		+ "    -lfiniteVolume \\\n"
		+ context.libs()
	);
}


template<class Type>
tnbLib::dlLibraryTable& tnbLib::fv::CodedSource<Type>::libs() const
{
	return const_cast<Time&>(mesh_.time()).libs();
}


template<class Type>
tnbLib::string tnbLib::fv::CodedSource<Type>::description() const
{
	return "fvOption:: " + name_;
}


template<class Type>
void tnbLib::fv::CodedSource<Type>::clearRedirect() const
{
	redirectFvOptionPtr_.clear();
}


template<class Type>
const tnbLib::dictionary& tnbLib::fv::CodedSource<Type>::codeDict() const
{
	return coeffs_;
}


template<class Type>
const tnbLib::wordList& tnbLib::fv::CodedSource<Type>::codeKeys() const
{
	return codeKeys_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::fv::CodedSource<Type>::CodedSource
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	cellSetOption(name, modelType, dict, mesh)
{
	read(dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::fv::option& tnbLib::fv::CodedSource<Type>::redirectFvOption() const
{
	if (!redirectFvOptionPtr_.valid())
	{
		dictionary constructDict(dict_);
		constructDict.set("type", name_);

		redirectFvOptionPtr_ = option::New
		(
			name_,
			constructDict,
			mesh_
		);
	}
	return redirectFvOptionPtr_();
}


template<class Type>
void tnbLib::fv::CodedSource<Type>::correct
(
	GeometricField<Type, fvPatchField, volMesh>& field
)
{
	if (debug)
	{
		Info << "CodedSource<" << pTraits<Type>::typeName
			<< ">::correct for source " << name_ << endl;
	}

	updateLibrary(name_);
	redirectFvOption().correct(field);
}


template<class Type>
void tnbLib::fv::CodedSource<Type>::addSup
(
	fvMatrix<Type>& eqn,
	const label fieldi
)
{
	if (debug)
	{
		Info << "CodedSource<" << pTraits<Type>::typeName
			<< ">::addSup for source " << name_ << endl;
	}

	updateLibrary(name_);
	redirectFvOption().addSup(eqn, fieldi);
}


template<class Type>
void tnbLib::fv::CodedSource<Type>::addSup
(
	const volScalarField& rho,
	fvMatrix<Type>& eqn,
	const label fieldi
)
{
	if (debug)
	{
		Info << "CodedSource<" << pTraits<Type>::typeName
			<< ">::addSup for source " << name_ << endl;
	}

	updateLibrary(name_);
	redirectFvOption().addSup(rho, eqn, fieldi);
}


template<class Type>
void tnbLib::fv::CodedSource<Type>::constrain
(
	fvMatrix<Type>& eqn,
	const label fieldi
)
{
	if (debug)
	{
		Info << "CodedSource<" << pTraits<Type>::typeName
			<< ">::constrain for source " << name_ << endl;
	}

	updateLibrary(name_);
	redirectFvOption().constrain(eqn, fieldi);
}


// ************************************************************************* //