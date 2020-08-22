#include <extrudeModel.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(extrudeModel, 0);
	defineRunTimeSelectionTable(extrudeModel, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::extrudeModel::extrudeModel
(
	const word& modelType,
	const dictionary& dict
)
	:
	nLayers_(dict.lookupOrDefault<label>("nLayers", 1)),
	expansionRatio_(dict.lookupOrDefault<scalar>("expansionRatio", 1)),
	dict_(dict),
	coeffDict_(dict.optionalSubDict(modelType + "Coeffs"))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::extrudeModel::~extrudeModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::extrudeModel::nLayers() const
{
	return nLayers_;
}


tnbLib::scalar tnbLib::extrudeModel::expansionRatio() const
{
	return expansionRatio_;
}


tnbLib::scalar tnbLib::extrudeModel::sumThickness(const label layer) const
{
	// 1+r+r^2+ .. +r^(n-1) = (1-r^n)/(1-r)

	if (mag(1.0 - expansionRatio_) < small)
	{
		return scalar(layer) / nLayers_;
	}
	else
	{
		return
			(1.0 - pow(expansionRatio_, layer))
			/ (1.0 - pow(expansionRatio_, nLayers_));
	}
}


// ************************************************************************* //