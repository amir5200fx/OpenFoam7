#include <dsmcParcel.hxx>

#include <DSMCCloudTemplate.hxx>
#include <NoBinaryCollision.hxx>
#include <VariableHardSphere.hxx>
#include <LarsenBorgnakkeVariableHardSphere.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	typedef DSMCCloud<dsmcParcel> CloudType;

	makeBinaryCollisionModel(DSMCCloud<dsmcParcel>);

	// Add instances of collision model to the table
	makeBinaryCollisionModelType(NoBinaryCollision, CloudType);
	makeBinaryCollisionModelType(VariableHardSphere, CloudType);
	makeBinaryCollisionModelType(LarsenBorgnakkeVariableHardSphere, CloudType);
}


// ************************************************************************* //