#pragma once
#include <fvMesh.hxx>
#include <fvMatrices.hxx>
#include <fvmSup.hxx>

// * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * * //

template<class Type>
const tnbLib::wordList tnbLib::fv::SemiImplicitSource<Type>::volumeModeTypeNames_
(
	IStringStream("(absolute specific)")()
);


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

template<class Type>
typename tnbLib::fv::SemiImplicitSource<Type>::volumeModeType
tnbLib::fv::SemiImplicitSource<Type>::wordToVolumeModeType
(
	const word& vmtName
) const
{
	forAll(volumeModeTypeNames_, i)
	{
		if (vmtName == volumeModeTypeNames_[i])
		{
			return volumeModeType(i);
		}
	}

	FatalErrorInFunction
		<< "Unknown volumeMode type " << vmtName
		<< ". Valid volumeMode types are:" << nl << volumeModeTypeNames_
		<< exit(FatalError);

	return volumeModeType(0);
}


template<class Type>
tnbLib::word tnbLib::fv::SemiImplicitSource<Type>::volumeModeTypeToWord
(
	const volumeModeType& vmtType
) const
{
	if (vmtType > volumeModeTypeNames_.size())
	{
		return "UNKNOWN";
	}
	else
	{
		return volumeModeTypeNames_[vmtType];
	}
}


template<class Type>
void tnbLib::fv::SemiImplicitSource<Type>::setFieldData(const dictionary& dict)
{
	fieldNames_.setSize(dict.toc().size());
	injectionRate_.setSize(fieldNames_.size());

	applied_.setSize(fieldNames_.size(), false);

	label i = 0;
	forAllConstIter(dictionary, dict, iter)
	{
		fieldNames_[i] = iter().keyword();
		dict.lookup(iter().keyword()) >> injectionRate_[i];
		i++;
	}

	// Set volume normalisation
	if (volumeMode_ == vmAbsolute)
	{
		VDash_ = V_;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::fv::SemiImplicitSource<Type>::SemiImplicitSource
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	cellSetOption(name, modelType, dict, mesh),
	volumeMode_(vmAbsolute),
	VDash_(1.0),
	injectionRate_()
{
	read(dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::fv::SemiImplicitSource<Type>::addSup
(
	fvMatrix<Type>& eqn,
	const label fieldi
)
{
	if (debug)
	{
		Info << "SemiImplicitSource<" << pTraits<Type>::typeName
			<< ">::addSup for source " << name_ << endl;
	}

	const GeometricField<Type, fvPatchField, volMesh>& psi = eqn.psi();

	typename GeometricField<Type, fvPatchField, volMesh>::Internal Su
	(
		IOobject
		(
			name_ + fieldNames_[fieldi] + "Su",
			mesh_.time().timeName(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh_,
		dimensioned<Type>
		(
			"zero",
			eqn.dimensions() / dimVolume,
			Zero
			),
		false
	);

	UIndirectList<Type>(Su, cells_) = injectionRate_[fieldi].first() / VDash_;

	volScalarField::Internal Sp
	(
		IOobject
		(
			name_ + fieldNames_[fieldi] + "Sp",
			mesh_.time().timeName(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh_,
		dimensioned<scalar>
		(
			"zero",
			Su.dimensions() / psi.dimensions(),
			0.0
			),
		false
	);

	UIndirectList<scalar>(Sp, cells_) = injectionRate_[fieldi].second() / VDash_;

	eqn += Su + fvm::SuSp(Sp, psi);
}


template<class Type>
void tnbLib::fv::SemiImplicitSource<Type>::addSup
(
	const volScalarField& rho,
	fvMatrix<Type>& eqn,
	const label fieldi
)
{
	if (debug)
	{
		Info << "SemiImplicitSource<" << pTraits<Type>::typeName
			<< ">::addSup for source " << name_ << endl;
	}

	return this->addSup(eqn, fieldi);
}


// ************************************************************************* //