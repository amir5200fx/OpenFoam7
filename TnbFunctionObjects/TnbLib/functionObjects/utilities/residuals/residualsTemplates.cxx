#include <residuals.hxx>

//#include <volFields.hxx>
//#include <ResidualsTemplate.hxx>
//#include <ListOps.hxx>
//
//// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//
//template<class Type>
//void tnbLib::functionObjects::residuals::writeFileHeader(const word& fieldName)
//{
//	typedef GeometricField<Type, fvPatchField, volMesh> fieldType;
//
//	if (obr_.foundObject<fieldType>(fieldName))
//	{
//		typename pTraits<Type>::labelType validComponents
//		(
//			mesh_.validComponents<Type>()
//		);
//
//		for (direction cmpt = 0; cmpt < pTraits<Type>::nComponents; cmpt++)
//		{
//			if (component(validComponents, cmpt) != -1)
//			{
//				writeTabbed
//				(
//					file(),
//					fieldName + word(pTraits<Type>::componentNames[cmpt])
//				);
//			}
//		}
//	}
//}
//
//
//template<class Type>
//void tnbLib::functionObjects::residuals::writeResidual(const word& fieldName)
//{
//	typedef GeometricField<Type, fvPatchField, volMesh> fieldType;
//
//	if (obr_.foundObject<fieldType>(fieldName))
//	{
//		if (Residuals<Type>::found(mesh_, fieldName))
//		{
//			const DynamicList<SolverPerformance<Type>>& sp
//			(
//				Residuals<Type>::field(mesh_, fieldName)
//			);
//
//			const Type& residual = sp.first().initialResidual();
//
//			typename pTraits<Type>::labelType validComponents
//			(
//				mesh_.validComponents<Type>()
//			);
//
//			for (direction cmpt = 0; cmpt < pTraits<Type>::nComponents; cmpt++)
//			{
//				if (component(validComponents, cmpt) != -1)
//				{
//					file() << tab << component(residual, cmpt);
//				}
//			}
//		}
//		else
//		{
//			file() << tab << "N/A";
//		}
//	}
//}
//
//
//// ************************************************************************* //