#pragma once

#include <phaseSystem.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

using namespace tnbLib;

template<class BasePhaseModel>
tnbLib::PurePhaseModel<BasePhaseModel>::PurePhaseModel
(
	const phaseSystem& fluid,
	const word& phaseName,
	const label index
)
	:
	BasePhaseModel(fluid, phaseName, index)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class BasePhaseModel>
tnbLib::PurePhaseModel<BasePhaseModel>::~PurePhaseModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class BasePhaseModel>
bool tnbLib::PurePhaseModel<BasePhaseModel>::pure() const
{
	return true;
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::fvScalarMatrix>
tnbLib::PurePhaseModel<BasePhaseModel>::YiEqn(volScalarField& Yi)
{
	FatalErrorInFunction
		<< "Cannot construct a species fraction equation for a pure phase"
		<< exit(FatalError);

	return tmp<fvScalarMatrix>();
}


template<class BasePhaseModel>
const tnbLib::PtrList<tnbLib::volScalarField>&
tnbLib::PurePhaseModel<BasePhaseModel>::Y() const
{
	// Y_ has never been set, so we are returning an empty list

	return Y_;
}


template<class BasePhaseModel>
const tnbLib::volScalarField&
tnbLib::PurePhaseModel<BasePhaseModel>::Y(const word& name) const
{
	FatalErrorInFunction
		<< "Cannot get a species fraction by name from a pure phase"
		<< exit(FatalError);

	return NullObjectRef<volScalarField>();
}


template<class BasePhaseModel>
tnbLib::PtrList<tnbLib::volScalarField>&
tnbLib::PurePhaseModel<BasePhaseModel>::YRef()
{
	FatalErrorInFunction
		<< "Cannot access the species fractions of for a pure phase"
		<< exit(FatalError);

	return Y_;
}


template<class BasePhaseModel>
const tnbLib::UPtrList<tnbLib::volScalarField>&
tnbLib::PurePhaseModel<BasePhaseModel>::YActive() const
{
	// Y_ has never been set, so we are returning an empty list

	return Y_;
}


template<class BasePhaseModel>
tnbLib::UPtrList<tnbLib::volScalarField>&
tnbLib::PurePhaseModel<BasePhaseModel>::YActiveRef()
{
	FatalErrorInFunction
		<< "Cannot access the species fractions of for a pure phase"
		<< exit(FatalError);

	return Y_;
}