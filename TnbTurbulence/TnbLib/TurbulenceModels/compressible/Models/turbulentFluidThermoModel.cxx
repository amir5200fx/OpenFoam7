#include <turbulentFluidThermoModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace compressible
	{
		template<class BasicCompressibleTurbulenceModel>
		autoPtr<BasicCompressibleTurbulenceModel> New
		(
			const volScalarField& rho,
			const volVectorField& U,
			const surfaceScalarField& phi,
			const typename BasicCompressibleTurbulenceModel::transportModel&
			transport,
			const word& propertiesName
		)
		{
			return BasicCompressibleTurbulenceModel::New
			(
				geometricOneField(),
				rho,
				U,
				phi,
				phi,
				transport,
				propertiesName
			);
		}
	}
}


// ************************************************************************* //