#pragma once
#include <constants.hxx>

#include <vector.hxx>  // added by amir
#include <polyPatch.hxx>  // added by amir
#include <Random.hxx>  // added by amir

using namespace tnbLib::constant;

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::MaxwellianThermal<CloudType>::MaxwellianThermal
(
	const dictionary& dict,
	CloudType& cloud
)
	:
	WallInteractionModel<CloudType>(cloud)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::MaxwellianThermal<CloudType>::~MaxwellianThermal()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::MaxwellianThermal<CloudType>::correct
(
	typename CloudType::parcelType& p
)
{
	vector& U = p.U();

	scalar& Ei = p.Ei();

	label typeId = p.typeId();

	const label wppIndex = p.patch();

	const polyPatch& wpp = p.mesh().boundaryMesh()[wppIndex];

	label wppLocalFace = wpp.whichFace(p.face());

	const vector nw = p.normal();

	// Normal velocity magnitude
	scalar U_dot_nw = U & nw;

	// Wall tangential velocity (flow direction)
	vector Ut = U - U_dot_nw * nw;

	CloudType& cloud(this->owner());

	Random& rndGen(cloud.rndGen());

	while (mag(Ut) < small)
	{
		// If the incident velocity is parallel to the face normal, no
		// tangential direction can be chosen.  Add a perturbation to the
		// incoming velocity and recalculate.

		U = vector
		(
			U.x()*(0.8 + 0.2*rndGen.scalar01()),
			U.y()*(0.8 + 0.2*rndGen.scalar01()),
			U.z()*(0.8 + 0.2*rndGen.scalar01())
		);

		U_dot_nw = U & nw;

		Ut = U - U_dot_nw * nw;
	}

	// Wall tangential unit vector
	vector tw1 = Ut / mag(Ut);

	// Other tangential unit vector
	vector tw2 = nw ^ tw1;

	scalar T = cloud.boundaryT().boundaryField()[wppIndex][wppLocalFace];

	scalar mass = cloud.constProps(typeId).mass();

	direction iDof = cloud.constProps(typeId).internalDegreesOfFreedom();

	U =
		sqrt(physicoChemical::k.value()*T / mass)
		*(
			rndGen.scalarNormal()*tw1
			+ rndGen.scalarNormal()*tw2
			- sqrt(-2.0*log(max(1 - rndGen.scalar01(), vSmall)))*nw
			);

	U += cloud.boundaryU().boundaryField()[wppIndex][wppLocalFace];

	Ei = cloud.equipartitionInternalEnergy(T, iDof);
}


// ************************************************************************* //