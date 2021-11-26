#include <liquidPropertiesSurfaceTension.hxx>

#include <liquidThermo.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace surfaceTensionModels
	{
		defineTypeNameAndDebug(liquidProperties, 0);
		addToRunTimeSelectionTable
		(
			surfaceTensionModel,
			liquidProperties,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::surfaceTensionModels::liquidProperties::liquidProperties
(
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	surfaceTensionModel(mesh),
	phaseName_(dict.lookup("phase"))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::surfaceTensionModels::liquidProperties::~liquidProperties()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::surfaceTensionModels::liquidProperties::sigma() const
{
	const heRhoThermopureMixtureliquidProperties& thermo =
		mesh_.lookupObject<heRhoThermopureMixtureliquidProperties>
		(
			IOobject::groupName(basicThermo::dictName, phaseName_)
			);

	const tnbLib::liquidProperties& liquid = thermo.mixture().properties();

	tmp<volScalarField> tsigma
	(
		volScalarField::New
		(
			"sigma",
			mesh_,
			dimSigma
		)
	);
	volScalarField& sigma = tsigma.ref();

	const volScalarField& T = thermo.T();
	const volScalarField& p = thermo.p();

	volScalarField::Internal& sigmai = sigma;
	const volScalarField::Internal& pi = p;
	const volScalarField::Internal& Ti = T;

	forAll(sigmai, celli)
	{
		sigmai[celli] = liquid.sigma(pi[celli], Ti[celli]);
	}

	volScalarField::Boundary& sigmaBf = sigma.boundaryFieldRef();
	const volScalarField::Boundary& pBf = p.boundaryField();
	const volScalarField::Boundary& TBf = T.boundaryField();

	forAll(sigmaBf, patchi)
	{
		scalarField& sigmaPf = sigmaBf[patchi];
		const scalarField& pPf = pBf[patchi];
		const scalarField& TPf = TBf[patchi];

		forAll(sigmaPf, facei)
		{
			sigmaPf[facei] = liquid.sigma(pPf[facei], TPf[facei]);
		}
	}

	return tsigma;
}


bool tnbLib::surfaceTensionModels::liquidProperties::readDict
(
	const dictionary& dict
)
{
	return true;
}


bool tnbLib::surfaceTensionModels::liquidProperties::writeData
(
	Ostream& os
) const
{
	if (surfaceTensionModel::writeData(os))
	{
		return os.good();
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //