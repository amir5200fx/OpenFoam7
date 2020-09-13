#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace incompressible
	{
		template<class BasicIncompressibleTurbulenceModel>
		autoPtr<BasicIncompressibleTurbulenceModel> New
		(
			const volVectorField& U,
			const surfaceScalarField& phi,
			const typename BasicIncompressibleTurbulenceModel::transportModel&
			transport,
			const word& propertiesName
		)
		{
			return BasicIncompressibleTurbulenceModel::New
			(
				geometricOneField(),
				geometricOneField(),
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