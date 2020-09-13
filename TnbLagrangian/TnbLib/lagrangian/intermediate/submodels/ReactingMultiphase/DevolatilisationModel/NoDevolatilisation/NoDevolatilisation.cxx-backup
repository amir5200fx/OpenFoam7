#include <NoDevolatilisation.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoDevolatilisation<CloudType>::NoDevolatilisation
(
	const dictionary&,
	CloudType& owner
)
	:
	DevolatilisationModel<CloudType>(owner)
{}


template<class CloudType>
tnbLib::NoDevolatilisation<CloudType>::NoDevolatilisation
(
	const NoDevolatilisation<CloudType>& dm
)
	:
	DevolatilisationModel<CloudType>(dm.owner_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::NoDevolatilisation<CloudType>::~NoDevolatilisation()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
bool tnbLib::NoDevolatilisation<CloudType>::active() const
{
	return false;
}


template<class CloudType>
void tnbLib::NoDevolatilisation<CloudType>::calculate
(
	const scalar,
	const scalar,
	const scalar,
	const scalar,
	const scalar,
	const scalarField&,
	const scalarField&,
	const scalarField&,
	label& canCombust,
	scalarField&
) const
{
	// Model does not stop combustion taking place
	canCombust = true;
}


// ************************************************************************* //