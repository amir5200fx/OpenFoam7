#pragma once
inline const tnbLib::speciesTable&
tnbLib::basicMultiComponentMixture::species() const
{
	return species_;
}


inline bool tnbLib::basicMultiComponentMixture::contains
(
	const word& specieName
) const
{
	return species_.contains(specieName);
}


inline bool tnbLib::basicMultiComponentMixture::active(label speciei) const
{
	return active_[speciei];
}


inline const tnbLib::List<bool>& tnbLib::basicMultiComponentMixture::active() const
{
	return active_;
}


inline void tnbLib::basicMultiComponentMixture::setActive(label speciei)
{
	active_[speciei] = true;
}


inline void tnbLib::basicMultiComponentMixture::setInactive(label speciei)
{
	active_[speciei] = false;
}


inline tnbLib::PtrList<tnbLib::volScalarField>&
tnbLib::basicMultiComponentMixture::Y()
{
	return Y_;
}


inline const tnbLib::PtrList<tnbLib::volScalarField>&
tnbLib::basicMultiComponentMixture::Y() const
{
	return Y_;
}


inline tnbLib::volScalarField& tnbLib::basicMultiComponentMixture::Y(const label i)
{
	return Y_[i];
}


inline const tnbLib::volScalarField& tnbLib::basicMultiComponentMixture::Y
(
	const label i
) const
{
	return Y_[i];
}


inline tnbLib::volScalarField& tnbLib::basicMultiComponentMixture::Y
(
	const word& specieName
)
{
	return Y_[species_[specieName]];
}


inline const tnbLib::volScalarField& tnbLib::basicMultiComponentMixture::Y
(
	const word& specieName
) const
{
	return Y_[species_[specieName]];
}


// ************************************************************************* //