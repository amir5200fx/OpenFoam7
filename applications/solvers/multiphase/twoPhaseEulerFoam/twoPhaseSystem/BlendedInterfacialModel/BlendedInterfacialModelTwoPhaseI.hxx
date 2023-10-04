#pragma once

#include <fixedValueFvsPatchFields.hxx>
#include <surfaceInterpolate.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class modelType>
template<class GeometricField>
void tnbLib::BlendedInterfacialModel<modelType>::correctFixedFluxBCs
(
	GeometricField& field
) const
{
	typename GeometricField::Boundary& fieldBf =
		field.boundaryFieldRef();

	forAll(pair_.phase1().phi().boundaryField(), patchi)
	{
		if
			(
				isA<fixedValueFvsPatchScalarField>
				(
					pair_.phase1().phi().boundaryField()[patchi]
					)
				)
		{
			fieldBf[patchi] = Zero;
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class modelType>
tnbLib::BlendedInterfacialModel<modelType>::BlendedInterfacialModel
(
	const phasePair::dictTable& modelTable,
	const blendingMethod& blending,
	const phasePair& pair,
	const orderedPhasePair& pair1In2,
	const orderedPhasePair& pair2In1,
	const bool correctFixedFluxBCs
)
	:
	pair_(pair),
	pair1In2_(pair1In2),
	pair2In1_(pair2In1),
	blending_(blending),
	correctFixedFluxBCs_(correctFixedFluxBCs)
{
	if (modelTable.found(pair_))
	{
		model_.set
		(
			modelType::New
			(
				modelTable[pair_],
				pair_
			).ptr()
		);
	}

	if (modelTable.found(pair1In2_))
	{
		model1In2_.set
		(
			modelType::New
			(
				modelTable[pair1In2_],
				pair1In2_
			).ptr()
		);
	}

	if (modelTable.found(pair2In1_))
	{
		model2In1_.set
		(
			modelType::New
			(
				modelTable[pair2In1_],
				pair2In1_
			).ptr()
		);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class modelType>
tnbLib::BlendedInterfacialModel<modelType>::~BlendedInterfacialModel()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class modelType>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::BlendedInterfacialModel<modelType>::K() const
{
	tmp<volScalarField> f1, f2;

	if (model_.valid() || model1In2_.valid())
	{
		f1 = blending_.f1(pair1In2_.dispersed(), pair2In1_.dispersed());
	}

	if (model_.valid() || model2In1_.valid())
	{
		f2 = blending_.f2(pair1In2_.dispersed(), pair2In1_.dispersed());
	}

	tmp<volScalarField> x
	(
		volScalarField::New
		(
			modelType::typeName + ":K",
			pair_.phase1().mesh(),
			dimensionedScalar(modelType::dimK, 0)
		)
	);

	if (model_.valid())
	{
		x.ref() += model_->K() * (f1() - f2());
	}

	if (model1In2_.valid())
	{
		x.ref() += model1In2_->K() * (1 - f1);
	}

	if (model2In1_.valid())
	{
		x.ref() += model2In1_->K() * f2;
	}

	if
		(
			correctFixedFluxBCs_
			&& (model_.valid() || model1In2_.valid() || model2In1_.valid())
			)
	{
		correctFixedFluxBCs(x.ref());
	}

	return x;
}


template<class modelType>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::BlendedInterfacialModel<modelType>::Kf() const
{
	tmp<surfaceScalarField> f1, f2;

	if (model_.valid() || model1In2_.valid())
	{
		f1 = fvc::interpolate
		(
			blending_.f1(pair1In2_.dispersed(), pair2In1_.dispersed())
		);
	}

	if (model_.valid() || model2In1_.valid())
	{
		f2 = fvc::interpolate
		(
			blending_.f2(pair1In2_.dispersed(), pair2In1_.dispersed())
		);
	}

	tmp<surfaceScalarField> x
	(
		surfaceScalarField::New
		(
			modelType::typeName + ":Kf",
			pair_.phase1().mesh(),
			dimensionedScalar(modelType::dimK, 0)
		)
	);

	if (model_.valid())
	{
		x.ref() += model_->Kf() * (f1() - f2());
	}

	if (model1In2_.valid())
	{
		x.ref() += model1In2_->Kf() * (1 - f1);
	}

	if (model2In1_.valid())
	{
		x.ref() += model2In1_->Kf() * f2;
	}

	if
		(
			correctFixedFluxBCs_
			&& (model_.valid() || model1In2_.valid() || model2In1_.valid())
			)
	{
		correctFixedFluxBCs(x.ref());
	}

	return x;
}


template<class modelType>
template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvPatchField, tnbLib::volMesh>>
tnbLib::BlendedInterfacialModel<modelType>::F() const
{
	tmp<volScalarField> f1, f2;

	if (model_.valid() || model1In2_.valid())
	{
		f1 = blending_.f1(pair1In2_.dispersed(), pair2In1_.dispersed());
	}

	if (model_.valid() || model2In1_.valid())
	{
		f2 = blending_.f2(pair1In2_.dispersed(), pair2In1_.dispersed());
	}

	tmp<GeometricField<Type, fvPatchField, volMesh>> x
	(
		new GeometricField<Type, fvPatchField, volMesh>
		(
			IOobject
			(
				modelType::typeName + ":F",
				pair_.phase1().mesh().time().timeName(),
				pair_.phase1().mesh(),
				IOobject::NO_READ,
				IOobject::NO_WRITE,
				false
			),
			pair_.phase1().mesh(),
			dimensioned<Type>("zero", modelType::dimF, Zero)
			)
	);

	if (model_.valid())
	{
		x.ref() += model_->F() * (f1() - f2());
	}

	if (model1In2_.valid())
	{
		x.ref() += model1In2_->F() * (1 - f1);
	}

	if (model2In1_.valid())
	{
		x.ref() -= model2In1_->F() * f2; // note : subtraction
	}

	if
		(
			correctFixedFluxBCs_
			&& (model_.valid() || model1In2_.valid() || model2In1_.valid())
			)
	{
		correctFixedFluxBCs(x.ref());
	}

	return x;
}


template<class modelType>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::BlendedInterfacialModel<modelType>::Ff() const
{
	tmp<surfaceScalarField> f1, f2;

	if (model_.valid() || model1In2_.valid())
	{
		f1 = fvc::interpolate
		(
			blending_.f1(pair1In2_.dispersed(), pair2In1_.dispersed())
		);
	}

	if (model_.valid() || model2In1_.valid())
	{
		f2 = fvc::interpolate
		(
			blending_.f2(pair1In2_.dispersed(), pair2In1_.dispersed())
		);
	}

	tmp<surfaceScalarField> x
	(
		surfaceScalarField::New
		(
			modelType::typeName + ":Ff",
			pair_.phase1().mesh(),
			dimensionedScalar(modelType::dimF * dimArea, 0)
		)
	);

	if (model_.valid())
	{
		x.ref() += model_->Ff() * (f1() - f2());
	}

	if (model1In2_.valid())
	{
		x.ref() += model1In2_->Ff() * (1 - f1);
	}

	if (model2In1_.valid())
	{
		x.ref() -= model2In1_->Ff() * f2; // note : subtraction
	}

	if
		(
			correctFixedFluxBCs_
			&& (model_.valid() || model1In2_.valid() || model2In1_.valid())
			)
	{
		correctFixedFluxBCs(x.ref());
	}

	return x;
}


template<class modelType>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::BlendedInterfacialModel<modelType>::D() const
{
	tmp<volScalarField> f1, f2;

	if (model_.valid() || model1In2_.valid())
	{
		f1 = blending_.f1(pair1In2_.dispersed(), pair2In1_.dispersed());
	}

	if (model_.valid() || model2In1_.valid())
	{
		f2 = blending_.f2(pair1In2_.dispersed(), pair2In1_.dispersed());
	}

	tmp<volScalarField> x
	(
		volScalarField::New
		(
			modelType::typeName + ":D",
			pair_.phase1().mesh(),
			dimensionedScalar(modelType::dimD, 0)
		)
	);

	if (model_.valid())
	{
		x.ref() += model_->D() * (f1() - f2());
	}

	if (model1In2_.valid())
	{
		x.ref() += model1In2_->D() * (1 - f1);
	}

	if (model2In1_.valid())
	{
		x.ref() += model2In1_->D() * f2;
	}

	if
		(
			correctFixedFluxBCs_
			&& (model_.valid() || model1In2_.valid() || model2In1_.valid())
			)
	{
		correctFixedFluxBCs(x.ref());
	}

	return x;
}


template<class modelType>
bool tnbLib::BlendedInterfacialModel<modelType>::hasModel
(
	const class phaseModel& phase
) const
{
	return
		&phase == &(pair_.phase1())
		? model1In2_.valid()
		: model2In1_.valid();
}


template<class modelType>
const modelType& tnbLib::BlendedInterfacialModel<modelType>::phaseModel
(
	const class phaseModel& phase
) const
{
	return &phase == &(pair_.phase1()) ? model1In2_ : model2In1_;
}