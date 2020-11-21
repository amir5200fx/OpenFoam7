#include <InjectionModelTemplateList.hxx>

//// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //
//
//template<class CloudType>
//tnbLib::InjectionModelList<CloudType>::InjectionModelList(CloudType& owner)
//	:
//	PtrList<InjectionModel<CloudType>>()
//{}
//
//
//template<class CloudType>
//tnbLib::InjectionModelList<CloudType>::InjectionModelList
//(
//	const dictionary& dict,
//	CloudType& owner
//)
//	:
//	PtrList<InjectionModel<CloudType>>()
//{
//	wordList modelNames(dict.toc());
//
//	Info << "Constructing particle injection models" << endl;
//
//	if (modelNames.size() > 0)
//	{
//		this->setSize(modelNames.size());
//
//		label i = 0;
//		forAllConstIter(IDLList<entry>, dict, iter)
//		{
//			const word& model = iter().keyword();
//			Info << "Creating injector: " << model << endl;
//			const dictionary& props = iter().dict();
//
//			this->set
//			(
//				i++,
//				InjectionModel<CloudType>::New
//				(
//					props,
//					model,
//					props.lookup("type"),
//					owner
//				)
//			);
//		}
//	}
//	else
//	{
//		this->setSize(1);
//
//		this->set
//		(
//			0,
//			InjectionModel<CloudType>::New
//			(
//				dict,
//				"none",
//				"none",
//				owner
//			)
//		);
//	}
//}
//
//
//template<class CloudType>
//tnbLib::InjectionModelList<CloudType>::InjectionModelList
//(
//	const InjectionModelList<CloudType>& iml
//)
//	:
//	PtrList<InjectionModel<CloudType>>(iml)
//{}
//
//
//// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //
//
//template<class CloudType>
//tnbLib::InjectionModelList<CloudType>::~InjectionModelList()
//{}
//
//
//// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
//
//template<class CloudType>
//tnbLib::scalar tnbLib::InjectionModelList<CloudType>::timeStart() const
//{
//	scalar minTime = great;
//	forAll(*this, i)
//	{
//		minTime = min(minTime, this->operator[](i).timeStart());
//	}
//
//	return minTime;
//}
//
//
//template<class CloudType>
//tnbLib::scalar tnbLib::InjectionModelList<CloudType>::timeEnd() const
//{
//	scalar maxTime = -great;
//	forAll(*this, i)
//	{
//		maxTime = max(maxTime, this->operator[](i).timeEnd());
//	}
//
//	return maxTime;
//}
//
//
//template<class CloudType>
//tnbLib::scalar tnbLib::InjectionModelList<CloudType>::volumeToInject
//(
//	const scalar time0,
//	const scalar time1
//)
//{
//	scalar vol = 0.0;
//	forAll(*this, i)
//	{
//		vol += this->operator[](i).volumeToInject(time0, time1);
//	}
//
//	return vol;
//}
//
//
//template<class CloudType>
//tnbLib::scalar tnbLib::InjectionModelList<CloudType>::averageParcelMass()
//{
//	scalar mass = 0.0;
//	scalar massTotal = 0.0;
//	forAll(*this, i)
//	{
//		scalar mt = this->operator[](i).massTotal();
//		mass += mt * this->operator[](i).averageParcelMass();
//		massTotal += mt;
//	}
//
//	return mass / massTotal;
//}
//
//
//template<class CloudType>
//void tnbLib::InjectionModelList<CloudType>::updateMesh()
//{
//	forAll(*this, i)
//	{
//		this->operator[](i).updateMesh();
//	}
//}
//
//
//template<class CloudType>
//template<class TrackCloudType>
//void tnbLib::InjectionModelList<CloudType>::inject
//(
//	TrackCloudType& cloud,
//	typename CloudType::parcelType::trackingData& td
//)
//{
//	forAll(*this, i)
//	{
//		this->operator[](i).inject(cloud, td);
//	}
//}
//
//
//template<class CloudType>
//template<class TrackCloudType>
//void tnbLib::InjectionModelList<CloudType>::injectSteadyState
//(
//	TrackCloudType& cloud,
//	typename CloudType::parcelType::trackingData& td,
//	const scalar trackTime
//)
//{
//	forAll(*this, i)
//	{
//		this->operator[](i).injectSteadyState(cloud, td, trackTime);
//	}
//}
//
//
//template<class CloudType>
//void tnbLib::InjectionModelList<CloudType>::info(Ostream& os)
//{
//	forAll(*this, i)
//	{
//		this->operator[](i).info(os);
//	}
//}
//
//
//// ************************************************************************* //