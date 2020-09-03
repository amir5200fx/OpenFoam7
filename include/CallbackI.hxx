#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CallbackType>
tnbLib::Callback<CallbackType>::Callback(CallbackRegistry<CallbackType>& cbr)
	:
	cbr_(cbr)
{
	checkIn();
}


template<class CallbackType>
tnbLib::Callback<CallbackType>::Callback(const Callback<CallbackType>& cb)
	:
	cbr_(cb.cbr_)
{
	checkIn();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CallbackType>
tnbLib::Callback<CallbackType>::~Callback()
{
	checkOut();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CallbackType>
bool tnbLib::Callback<CallbackType>::checkIn()
{
	if (!Callback<CallbackType>::link::registered())
	{
		cbr_.append(static_cast<CallbackType*>(this));
		return true;
	}
	else
	{
		return false;
	}
}


template<class CallbackType>
bool tnbLib::Callback<CallbackType>::checkOut()
{
	if (Callback<CallbackType>::link::registered())
	{
		CallbackType* cbPtr = cbr_.remove(static_cast<CallbackType*>(this));

		if (cbPtr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //