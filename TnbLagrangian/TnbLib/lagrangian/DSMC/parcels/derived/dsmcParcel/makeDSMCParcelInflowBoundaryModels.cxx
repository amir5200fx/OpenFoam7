#include <dsmcParcel.hxx>

#include <DSMCCloudTemplate.hxx>
#include <FreeStream.hxx>
#include <NoInflow.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	typedef DSMCCloud<dsmcParcel> CloudType;

	makeInflowBoundaryModel(CloudType);

	// Add instances of inflow boundary model to the table
	makeInflowBoundaryModelType(FreeStream, CloudType);
	makeInflowBoundaryModelType(NoInflow, CloudType);
}


// ************************************************************************* //