#pragma once
#include <filmThermoModel.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

			template<class Type>
			void kinematicSingleLayer::constrainFilmField
			(
				Type& field,
				const typename Type::cmptType& value
			)
			{
				typename Type::Boundary& fieldBf = field.boundaryFieldRef();

				forAll(intCoupledPatchIDs_, i)
				{
					label patchi = intCoupledPatchIDs_[i];
					fieldBf[patchi] = value;
					if (debug)
					{
						Info << "Constraining " << field.name()
							<< " boundary " << field.boundaryField()[patchi].patch().name()
							<< " to " << value << endl;
					}
				}

				forAll(passivePatchIDs_, i)
				{
					label patchi = passivePatchIDs_[i];
					fieldBf[patchi] = value;
					if (debug)
					{
						Info << "Constraining " << field.name()
							<< " boundary " << field.boundaryField()[patchi].patch().name()
							<< " to " << value << endl;
					}
				}
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // end namespace tnbLib
	} // end namespace regionModels
} // end namespace surfaceFilmModels

// ************************************************************************* //