#include <dimensionedSphericalTensor.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<>
	dimensionedSphericalTensor dimensionedSphericalTensor::T() const
	{
		return dimensionedSphericalTensor
		(
			name() + ".T()",
			dimensions(),
			value().T()
		);
	}


	// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //

	dimensionedScalar tr(const dimensionedSphericalTensor& dt)
	{
		return dimensionedScalar
		(
			"tr(" + dt.name() + ')',
			dt.dimensions(),
			tr(dt.value())
		);
	}


	dimensionedScalar det(const dimensionedSphericalTensor& dt)
	{
		return dimensionedScalar
		(
			"det(" + dt.name() + ')',
			pow(dt.dimensions(), sphericalTensor::dim),
			det(dt.value())
		);
	}


	dimensionedSphericalTensor inv(const dimensionedSphericalTensor& dt)
	{
		return dimensionedSphericalTensor
		(
			"inv(" + dt.name() + ')',
			dimless / dt.dimensions(),
			inv(dt.value())
		);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //