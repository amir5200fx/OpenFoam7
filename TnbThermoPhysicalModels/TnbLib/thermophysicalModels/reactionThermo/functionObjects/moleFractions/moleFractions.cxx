#include <moleFractions.hxx>

#include <basicThermo.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class ThermoType>
void tnbLib::moleFractions<ThermoType>::calculateMoleFractions()
{
	const ThermoType& thermo =
		mesh_.lookupObject<ThermoType>(basicThermo::dictName);

	const PtrList<volScalarField>& Y = thermo.composition().Y();

	const volScalarField W(thermo.W());

	forAll(Y, i)
	{
		const dimensionedScalar Wi
		(
			"Wi",
			dimMass / dimMoles,
			thermo.composition().Wi(i)
		);

		X_[i] = W * Y[i] / Wi;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ThermoType>
tnbLib::moleFractions<ThermoType>::moleFractions
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict)
{
	if (mesh_.foundObject<ThermoType>(basicThermo::dictName))
	{
		const ThermoType& thermo =
			mesh_.lookupObject<ThermoType>(basicThermo::dictName);

		const PtrList<volScalarField>& Y = thermo.composition().Y();

		X_.setSize(Y.size());

		forAll(Y, i)
		{
			X_.set
			(
				i,
				new volScalarField
				(
					IOobject
					(
						"X_" + Y[i].name(),
						mesh_.time().timeName(),
						mesh_
					),
					mesh_,
					dimensionedScalar(dimless, 0)
				)
			);
		}

		calculateMoleFractions();
	}
	else
	{
		FatalErrorInFunction
			<< "Cannot find thermodynamics model of type "
			<< ThermoType::typeName
			<< exit(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class ThermoType>
tnbLib::moleFractions<ThermoType>::~moleFractions()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ThermoType>
bool tnbLib::moleFractions<ThermoType>::read
(
	const dictionary& dict
)
{
	return true;
}


template<class ThermoType>
bool tnbLib::moleFractions<ThermoType>::execute()
{
	calculateMoleFractions();
	return true;
}


template<class ThermoType>
bool tnbLib::moleFractions<ThermoType>::write()
{
	forAll(X_, i)
	{
		X_[i].write();
	}

	return true;
}


// ************************************************************************* //