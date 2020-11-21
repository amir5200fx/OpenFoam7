#include <randomise.hxx>

//#include <Random.hxx>
//#include <volFields.hxx>
//
//// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
//
//template<class Type>
//bool tnbLib::functionObjects::randomise::calcRandomised()
//{
//	typedef GeometricField<Type, fvPatchField, volMesh> VolFieldType;
//
//	if (foundObject<VolFieldType>(fieldName_))
//	{
//		const VolFieldType& field = lookupObject<VolFieldType>(fieldName_);
//
//		resultName_ = fieldName_ + "Random";
//
//		tmp<VolFieldType> rfieldt(new VolFieldType(field));
//		VolFieldType& rfield = rfieldt.ref();
//
//		Random rand(1234567);
//
//		forAll(field, celli)
//		{
//			Type rndPert = rand.sample01<Type>();
//			rndPert = 2.0*rndPert - pTraits<Type>::one;
//			rndPert /= mag(rndPert);
//			rfield[celli] += magPerturbation_ * rndPert;
//		}
//
//		return store(resultName_, rfieldt);
//	}
//	else
//	{
//		return false;
//	}
//}
//
//
//// ************************************************************************* //