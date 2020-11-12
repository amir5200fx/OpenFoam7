#pragma once
#include <gaussConvectionScheme.hxx>
#include <blendedSchemeBase.hxx>
#include <fvcCellReduce.hxx>

// .cxx
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
bool tnbLib::functionObjects::blendingFactor::calcBF()
{
	typedef GeometricField<Type, fvPatchField, volMesh> FieldType;

	if (!foundObject<FieldType>(fieldName_))
	{
		return false;
	}

	const FieldType& field = lookupObject<FieldType>(fieldName_);

	const word divScheme("div(" + phiName_ + ',' + fieldName_ + ')');
	ITstream& its = mesh_.divScheme(divScheme);

	const surfaceScalarField& phi = lookupObject<surfaceScalarField>(phiName_);

	tmp<fv::convectionScheme<Type>> cs =
		fv::convectionScheme<Type>::New(mesh_, phi, its);

	const fv::gaussConvectionScheme<Type>& gcs =
		refCast<const fv::gaussConvectionScheme<Type>>(cs());

	const surfaceInterpolationScheme<Type>& interpScheme =
		gcs.interpScheme();

	if (!isA<blendedSchemeBase<Type>>(interpScheme))
	{
		FatalErrorInFunction
			<< interpScheme.typeName << " is not a blended scheme"
			<< exit(FatalError);
	}

	// Retrieve the face-based blending factor
	const blendedSchemeBase<Type>& blendedScheme =
		refCast<const blendedSchemeBase<Type>>(interpScheme);
	tmp<surfaceScalarField> factorf(blendedScheme.blendingFactor(field));

	// Convert into vol field whose values represent the local face maxima
	return store
	(
		resultName_,
		fvc::cellReduce(factorf, maxEqOp<scalar>())
	);
}


// ************************************************************************* //