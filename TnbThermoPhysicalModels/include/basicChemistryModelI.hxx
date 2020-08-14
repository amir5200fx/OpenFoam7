#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::fvMesh& tnbLib::basicChemistryModel::mesh() const
{
	return mesh_;
}


inline tnbLib::Switch tnbLib::basicChemistryModel::chemistry() const
{
	return chemistry_;
}


inline const tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>&
tnbLib::basicChemistryModel::deltaTChem() const
{
	return deltaTChem_;
}


inline tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>&
tnbLib::basicChemistryModel::deltaTChem()
{
	return deltaTChem_;
}


// ************************************************************************* //