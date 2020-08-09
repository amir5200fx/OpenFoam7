#include <bound.hxx>

#include <volFields.hxx>
#include <fvc.hxx>

// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

tnbLib::volScalarField&
tnbLib::bound(volScalarField& vsf, const dimensionedScalar& lowerBound)
{
	const scalar minVsf = min(vsf).value();

	if (minVsf < lowerBound.value())
	{
		Info << "bounding " << vsf.name()
			<< ", min: " << minVsf
			<< " max: " << max(vsf).value()
			<< " average: " << gAverage(vsf.primitiveField())
			<< endl;

		vsf.primitiveFieldRef() = max
		(
			max
			(
				vsf.primitiveField(),
				fvc::average(max(vsf, lowerBound))().primitiveField()
				* pos0(-vsf.primitiveField())
			),
			lowerBound.value()
		);

		vsf.boundaryFieldRef() = max(vsf.boundaryField(), lowerBound.value());
	}

	return vsf;
}


// ************************************************************************* //