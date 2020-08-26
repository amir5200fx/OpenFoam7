#include <MRFZoneList.hxx>

#include <GeometricFieldReuseFunctions.hxx>  // added by amir

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvsPatchField, tnbLib::surfaceMesh>>
tnbLib::MRFZoneList::zeroFilter
(
	const tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>& tphi
) const
{
	if (size())
	{
		tmp<surfaceScalarField> zphi
		(
			New
			(
				tphi,
				"zeroFilter(" + tphi().name() + ')',
				tphi().dimensions(),
				true
			)
		);

		forAll(*this, i)
		{
			operator[](i).zero(zphi.ref());
		}

		return zphi;
	}
	else
	{
		return tmp<surfaceScalarField>(tphi, true);
	}
}


// ************************************************************************* //