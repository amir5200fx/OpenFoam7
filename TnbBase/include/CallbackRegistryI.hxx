#pragma once
#include <UList.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CallbackType>
tnbLib::CallbackRegistry<CallbackType>::CallbackRegistry()
	:
	CallbackRegistryName(),
	UIDLList<CallbackType>()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CallbackType>
tnbLib::CallbackRegistry<CallbackType>::~CallbackRegistry()
{
	forAllIter(typename CallbackRegistry<CallbackType>, *this, iter)
	{
		iter().Callback<CallbackType>::checkOut();
	}
}


// ************************************************************************* //