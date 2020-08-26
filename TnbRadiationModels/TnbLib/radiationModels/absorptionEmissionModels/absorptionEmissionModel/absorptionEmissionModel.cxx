#include <absorptionEmissionModel.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		defineTypeNameAndDebug(absorptionEmissionModel, 0);
		defineRunTimeSelectionTable(absorptionEmissionModel, dictionary);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationModels::absorptionEmissionModel::absorptionEmissionModel
(
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	dict_(dict),
	mesh_(mesh)
{}


// * * * * * * * * * * * * * * * * Destructor    * * * * * * * * * * * * * * //

tnbLib::radiationModels::absorptionEmissionModel::~absorptionEmissionModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModel::a(const label bandI) const
{
	return aDisp(bandI) + aCont(bandI);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModel::aCont(const label bandI) const
{
	return volScalarField::New
	(
		"aCont",
		mesh_,
		dimensionedScalar(dimless / dimLength, 0)
	);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModel::aDisp(const label bandI) const
{
	return volScalarField::New
	(
		"aDisp",
		mesh_,
		dimensionedScalar(dimless / dimLength, 0)
	);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModel::e(const label bandI) const
{
	return eDisp(bandI) + eCont(bandI);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModel::eCont(const label bandI) const
{
	return volScalarField::New
	(
		"eCont",
		mesh_,
		dimensionedScalar(dimless / dimLength, 0)
	);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModel::eDisp(const label bandI) const
{
	return volScalarField::New
	(
		"eDisp",
		mesh_,
		dimensionedScalar(dimless / dimLength, 0)
	);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModel::E(const label bandI) const
{
	return EDisp(bandI) + ECont(bandI);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModel::ECont(const label bandI) const
{
	return volScalarField::New
	(
		"ECont",
		mesh_,
		dimensionedScalar(dimMass / dimLength / pow3(dimTime), 0)
	);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModel::EDisp(const label bandI) const
{
	return volScalarField::New
	(
		"EDisp",
		mesh_,
		dimensionedScalar(dimMass / dimLength / pow3(dimTime), 0)
	);
}


tnbLib::label tnbLib::radiationModels::absorptionEmissionModel::nBands() const
{
	return pTraits<label>::one;
}


const tnbLib::Vector2D<tnbLib::scalar>&
tnbLib::radiationModels::absorptionEmissionModel::bands(const label n) const
{
	return Vector2D<scalar>::one;
}


bool tnbLib::radiationModels::absorptionEmissionModel::isGrey() const
{
	return false;
}


void tnbLib::radiationModels::absorptionEmissionModel::correct
(
	volScalarField& a,
	PtrList<volScalarField>& aj
) const
{
	a = this->a();
	aj[0] = a;
}


// ************************************************************************* //