#pragma once
#include <volFields.hxx>

// * * * * * * * * * * * * * * *  Member Functions * * * * * * * * * * * * * //

template<class RhoFieldType>
void tnbLib::fv::actuationDiskSource::addActuationDiskAxialInertialResistance
(
	vectorField& Usource,
	const labelList& cells,
	const scalarField& Vcells,
	const RhoFieldType& rho,
	const vectorField& U
) const
{
	scalar a = 1.0 - Cp_ / Ct_;
	vector uniDiskDir = diskDir_ / mag(diskDir_);
	tensor E(Zero);
	E.xx() = uniDiskDir.x();
	E.yy() = uniDiskDir.y();
	E.zz() = uniDiskDir.z();

	vector upU = vector(vGreat, vGreat, vGreat);
	scalar upRho = vGreat;
	if (upstreamCellId_ != -1)
	{
		upU = U[upstreamCellId_];
		upRho = rho[upstreamCellId_];
	}
	reduce(upU, minOp<vector>());
	reduce(upRho, minOp<scalar>());

	scalar T = 2.0*upRho*diskArea_*mag(upU)*a*(1 - a);

	forAll(cells, i)
	{
		Usource[cells[i]] += ((Vcells[cells[i]] / V())*T*E) & upU;
	}
}


// ************************************************************************* //