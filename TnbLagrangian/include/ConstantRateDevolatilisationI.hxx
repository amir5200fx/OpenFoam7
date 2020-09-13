#pragma once
#include <primitiveFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ConstantRateDevolatilisation<CloudType>::ConstantRateDevolatilisation
(
	const dictionary& dict,
	CloudType& owner
)
	:
	DevolatilisationModel<CloudType>(dict, owner, typeName),
	volatileData_(this->coeffDict().lookup("volatileData")),
	YVolatile0_(volatileData_.size()),
	volatileToGasMap_(volatileData_.size()),
	residualCoeff_(readScalar(this->coeffDict().lookup("residualCoeff")))
{
	if (volatileData_.empty())
	{
		WarningInFunction
			<< "Devolatilisation model selected, but no volatiles defined"
			<< nl << endl;
	}
	else
	{
		Info << "Participating volatile species:" << endl;

		// Determine mapping between active volatiles and cloud gas components
		const label idGas = owner.composition().idGas();
		const scalar YGasTot = owner.composition().YMixture0()[idGas];
		const scalarField& YGas = owner.composition().Y0(idGas);
		forAll(volatileData_, i)
		{
			const word& specieName = volatileData_[i].first();
			const label id = owner.composition().localId(idGas, specieName);
			volatileToGasMap_[i] = id;
			YVolatile0_[i] = YGasTot * YGas[id];

			Info << "    " << specieName << ": particle mass fraction = "
				<< YVolatile0_[i] << endl;
		}
	}
}


template<class CloudType>
tnbLib::ConstantRateDevolatilisation<CloudType>::ConstantRateDevolatilisation
(
	const ConstantRateDevolatilisation<CloudType>& dm
)
	:
	DevolatilisationModel<CloudType>(dm),
	volatileData_(dm.volatileData_),
	YVolatile0_(dm.YVolatile0_),
	volatileToGasMap_(dm.volatileToGasMap_),
	residualCoeff_(dm.residualCoeff_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ConstantRateDevolatilisation<CloudType>::~ConstantRateDevolatilisation()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::ConstantRateDevolatilisation<CloudType>::calculate
(
	const scalar dt,
	const scalar age,
	const scalar mass0,
	const scalar mass,
	const scalar T,
	const scalarField& YGasEff,
	const scalarField& YLiquidEff,
	const scalarField& YSolidEff,
	label& canCombust,
	scalarField& dMassDV
) const
{
	bool done = true;
	forAll(volatileData_, i)
	{
		const label id = volatileToGasMap_[i];
		const scalar massVolatile0 = mass0 * YVolatile0_[i];
		const scalar massVolatile = mass * YGasEff[id];

		// Combustion allowed once all volatile components evolved
		done = done && (massVolatile <= residualCoeff_ * massVolatile0);

		// Model coefficients
		const scalar A0 = volatileData_[i].second();

		// Mass transferred from particle to carrier gas phase
		dMassDV[id] = min(dt*A0*massVolatile0, massVolatile);
	}

	if (done && canCombust != -1)
	{
		canCombust = 1;
	}
}


// ************************************************************************* //