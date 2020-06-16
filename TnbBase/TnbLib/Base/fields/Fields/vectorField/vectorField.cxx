#include <vectorField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::vectorField> tnbLib::zip
(
	const tmp<scalarField>& x,
	const tmp<scalarField>& y,
	const tmp<scalarField>& z
)
{
	tmp<vectorField> txyz(new vectorField(x->size()));
	vectorField& xyz = txyz.ref();
	xyz.replace(0, x);
	xyz.replace(1, y);
	xyz.replace(2, z);
	return txyz;
}

// ************************************************************************* //
