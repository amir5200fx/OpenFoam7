#include <WallCollisionRecord.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class Type>
const tnbLib::scalar tnbLib::WallCollisionRecord<Type>::errorCosAngle(1.0 + 1e-6);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::WallCollisionRecord<Type>::WallCollisionRecord()
	:
	accessed_(false),
	pRel_(),
	data_(Zero)
{}


template<class Type>
tnbLib::WallCollisionRecord<Type>::WallCollisionRecord
(
	bool accessed,
	const vector& pRel,
	const Type& data
)
	:
	accessed_(accessed),
	pRel_(pRel),
	data_(data)
{}


template<class Type>
tnbLib::WallCollisionRecord<Type>::WallCollisionRecord
(
	const WallCollisionRecord<Type>& wCR
)
	:
	accessed_(wCR.accessed_),
	pRel_(wCR.pRel_),
	data_(wCR.data_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::WallCollisionRecord<Type>::~WallCollisionRecord()
{}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<class Type>
void tnbLib::WallCollisionRecord<Type>::operator=
(
	const WallCollisionRecord<Type>& rhs
	)
{
	// Check for assignment to self
	if (this == &rhs)
	{
		FatalErrorInFunction
			<< "Attempted assignment to self"
			<< abort(FatalError);
	}

	accessed_ = rhs.accessed_;
	pRel_ = rhs.pRel_;
	data_ = rhs.data_;
}


// * * * * * * * * * * * * * *  IOStream operators * * * * * * * * * * * * * //

#include <WallCollisionRecordIO.cxx>


// ************************************************************************* //