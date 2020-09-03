#pragma once
#include <lduInterfaceField.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
void tnbLib::LduMatrix<Type, DType, LUType>::initMatrixInterfaces
(
	const FieldField<Field, LUType>& interfaceCoeffs,
	const Field<Type>& psiif,
	Field<Type>& result
) const
{
	if
		(
			Pstream::defaultCommsType == Pstream::commsTypes::blocking
			|| Pstream::defaultCommsType == Pstream::commsTypes::nonBlocking
			)
	{
		forAll(interfaces_, interfacei)
		{
			if (interfaces_.set(interfacei))
			{
				interfaces_[interfacei].initInterfaceMatrixUpdate
				(
					result,
					psiif,
					interfaceCoeffs[interfacei],
					// Amultiplier<Type, LUType>(interfaceCoeffs[interfacei]),
					Pstream::defaultCommsType
				);
			}
		}
	}
	else if (Pstream::defaultCommsType == Pstream::commsTypes::scheduled)
	{
		const lduSchedule& patchSchedule = this->patchSchedule();

		// Loop over the "global" patches are on the list of interfaces but
		// beyond the end of the schedule which only handles "normal" patches
		for
			(
				label interfacei = patchSchedule.size() / 2;
				interfacei < interfaces_.size();
				interfacei++
				)
		{
			if (interfaces_.set(interfacei))
			{
				interfaces_[interfacei].initInterfaceMatrixUpdate
				(
					result,
					psiif,
					interfaceCoeffs[interfacei],
					// Amultiplier<Type, LUType>(interfaceCoeffs[interfacei]),
					Pstream::commsTypes::blocking
				);
			}
		}
	}
	else
	{
		FatalErrorInFunction
			<< "Unsupported communications type "
			<< Pstream::commsTypeNames[Pstream::defaultCommsType]
			<< exit(FatalError);
	}
}


template<class Type, class DType, class LUType>
void tnbLib::LduMatrix<Type, DType, LUType>::updateMatrixInterfaces
(
	const FieldField<Field, LUType>& interfaceCoeffs,
	const Field<Type>& psiif,
	Field<Type>& result
) const
{
	if
		(
			Pstream::defaultCommsType == Pstream::commsTypes::blocking
			|| Pstream::defaultCommsType == Pstream::commsTypes::nonBlocking
			)
	{
		// Block until all sends/receives have been finished
		if (Pstream::defaultCommsType == Pstream::commsTypes::nonBlocking)
		{
			IPstream::waitRequests();
			OPstream::waitRequests();
		}

		forAll(interfaces_, interfacei)
		{
			if (interfaces_.set(interfacei))
			{
				interfaces_[interfacei].updateInterfaceMatrix
				(
					result,
					psiif,
					interfaceCoeffs[interfacei],
					// Amultiplier<Type, LUType>(interfaceCoeffs[interfacei]),
					Pstream::defaultCommsType
				);
			}
		}
	}
	else if (Pstream::defaultCommsType == Pstream::commsTypes::scheduled)
	{
		const lduSchedule& patchSchedule = this->patchSchedule();

		// Loop over all the "normal" interfaces relating to standard patches
		forAll(patchSchedule, i)
		{
			label interfacei = patchSchedule[i].patch;

			if (interfaces_.set(interfacei))
			{
				if (patchSchedule[i].init)
				{
					interfaces_[interfacei].initInterfaceMatrixUpdate
					(
						result,
						psiif,
						interfaceCoeffs[interfacei],
						// Amultiplier<Type, LUType>(interfaceCoeffs[interfacei]),
						Pstream::commsTypes::scheduled
					);
				}
				else
				{
					interfaces_[interfacei].updateInterfaceMatrix
					(
						result,
						psiif,
						interfaceCoeffs[interfacei],
						// Amultiplier<Type, LUType>(interfaceCoeffs[interfacei]),
						Pstream::commsTypes::scheduled
					);
				}
			}
		}

		// Loop over the "global" patches are on the list of interfaces but
		// beyond the end of the schedule which only handles "normal" patches
		for
			(
				label interfacei = patchSchedule.size() / 2;
				interfacei < interfaces_.size();
				interfacei++
				)
		{
			if (interfaces_.set(interfacei))
			{
				interfaces_[interfacei].updateInterfaceMatrix
				(
					result,
					psiif,
					interfaceCoeffs[interfacei],
					// Amultiplier<Type, LUType>(interfaceCoeffs[interfacei]),
					Pstream::commsTypes::blocking
				);
			}
		}
	}
	else
	{
		FatalErrorInFunction
			<< "Unsupported communications type "
			<< Pstream::commsTypeNames[Pstream::defaultCommsType]
			<< exit(FatalError);
	}
}


// ************************************************************************* //