#include <AMIInterpolation.hxx>

#include <AMIMethod.hxx>
#include <meshTools.hxx>
#include <mapDistribute.hxx>
#include <flipOp.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type, class CombineOp>
void tnbLib::AMIInterpolation::interpolateToTarget
(
	const UList<Type>& fld,
	const CombineOp& cop,
	List<Type>& result,
	const UList<Type>& defaultValues
) const
{
	if (fld.size() != srcAddress_.size())
	{
		FatalErrorInFunction
			<< "Supplied field size is not equal to source patch size" << nl
			<< "    source patch   = " << srcAddress_.size() << nl
			<< "    target patch   = " << tgtAddress_.size() << nl
			<< "    supplied field = " << fld.size()
			<< abort(FatalError);
	}

	if (lowWeightCorrection_ > 0)
	{
		if (defaultValues.size() != tgtAddress_.size())
		{
			FatalErrorInFunction
				<< "Employing default values when sum of weights falls below "
				<< lowWeightCorrection_
				<< " but supplied default field size is not equal to target "
				<< "patch size" << nl
				<< "    default values = " << defaultValues.size() << nl
				<< "    target patch   = " << tgtAddress_.size() << nl
				<< abort(FatalError);
		}
	}

	result.setSize(tgtAddress_.size());

	if (singlePatchProc_ == -1)
	{
		const mapDistribute& map = srcMapPtr_();

		List<Type> work(fld);
		map.distribute(work);

		forAll(result, facei)
		{
			if (tgtWeightsSum_[facei] < lowWeightCorrection_)
			{
				result[facei] = defaultValues[facei];
			}
			else
			{
				const labelList& faces = tgtAddress_[facei];
				const scalarList& weights = tgtWeights_[facei];

				forAll(faces, i)
				{
					cop(result[facei], facei, work[faces[i]], weights[i]);
				}
			}
		}
	}
	else
	{
		forAll(result, facei)
		{
			if (tgtWeightsSum_[facei] < lowWeightCorrection_)
			{
				result[facei] = defaultValues[facei];
			}
			else
			{
				const labelList& faces = tgtAddress_[facei];
				const scalarList& weights = tgtWeights_[facei];

				forAll(faces, i)
				{
					cop(result[facei], facei, fld[faces[i]], weights[i]);
				}
			}
		}
	}
}


template<class Type, class CombineOp>
void tnbLib::AMIInterpolation::interpolateToSource
(
	const UList<Type>& fld,
	const CombineOp& cop,
	List<Type>& result,
	const UList<Type>& defaultValues
) const
{
	if (fld.size() != tgtAddress_.size())
	{
		FatalErrorInFunction
			<< "Supplied field size is not equal to target patch size" << nl
			<< "    source patch   = " << srcAddress_.size() << nl
			<< "    target patch   = " << tgtAddress_.size() << nl
			<< "    supplied field = " << fld.size()
			<< abort(FatalError);
	}

	if (lowWeightCorrection_ > 0)
	{
		if (defaultValues.size() != srcAddress_.size())
		{
			FatalErrorInFunction
				<< "Employing default values when sum of weights falls below "
				<< lowWeightCorrection_
				<< " but supplied default field size is not equal to target "
				<< "patch size" << nl
				<< "    default values = " << defaultValues.size() << nl
				<< "    source patch   = " << srcAddress_.size() << nl
				<< abort(FatalError);
		}
	}

	result.setSize(srcAddress_.size());

	if (singlePatchProc_ == -1)
	{
		const mapDistribute& map = tgtMapPtr_();

		List<Type> work(fld);
		map.distribute(work);

		forAll(result, facei)
		{
			if (srcWeightsSum_[facei] < lowWeightCorrection_)
			{
				result[facei] = defaultValues[facei];
			}
			else
			{
				const labelList& faces = srcAddress_[facei];
				const scalarList& weights = srcWeights_[facei];

				forAll(faces, i)
				{
					cop(result[facei], facei, work[faces[i]], weights[i]);
				}
			}
		}
	}
	else
	{
		forAll(result, facei)
		{
			if (srcWeightsSum_[facei] < lowWeightCorrection_)
			{
				result[facei] = defaultValues[facei];
			}
			else
			{
				const labelList& faces = srcAddress_[facei];
				const scalarList& weights = srcWeights_[facei];

				forAll(faces, i)
				{
					cop(result[facei], facei, fld[faces[i]], weights[i]);
				}
			}
		}
	}
}


template<class Type, class CombineOp>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::AMIInterpolation::interpolateToSource
(
	const Field<Type>& fld,
	const CombineOp& cop,
	const UList<Type>& defaultValues
) const
{
	tmp<Field<Type>> tresult
	(
		new Field<Type>
		(
			srcAddress_.size(),
			Zero
			)
	);

	interpolateToSource
	(
		fld,
		multiplyWeightedOp<Type, CombineOp>(cop),
		tresult.ref(),
		defaultValues
	);

	return tresult;
}


template<class Type, class CombineOp>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::AMIInterpolation::interpolateToSource
(
	const tmp<Field<Type>>& tFld,
	const CombineOp& cop,
	const UList<Type>& defaultValues
) const
{
	return interpolateToSource(tFld(), cop, defaultValues);
}


template<class Type, class CombineOp>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::AMIInterpolation::interpolateToTarget
(
	const Field<Type>& fld,
	const CombineOp& cop,
	const UList<Type>& defaultValues
) const
{
	tmp<Field<Type>> tresult
	(
		new Field<Type>
		(
			tgtAddress_.size(),
			Zero
			)
	);

	interpolateToTarget
	(
		fld,
		multiplyWeightedOp<Type, CombineOp>(cop),
		tresult.ref(),
		defaultValues
	);

	return tresult;
}


template<class Type, class CombineOp>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::AMIInterpolation::interpolateToTarget
(
	const tmp<Field<Type>>& tFld,
	const CombineOp& cop,
	const UList<Type>& defaultValues
) const
{
	return interpolateToTarget(tFld(), cop, defaultValues);
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::AMIInterpolation::interpolateToSource
(
	const Field<Type>& fld,
	const UList<Type>& defaultValues
) const
{
	return interpolateToSource(fld, plusEqOp<Type>(), defaultValues);
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::AMIInterpolation::interpolateToSource
(
	const tmp<Field<Type>>& tFld,
	const UList<Type>& defaultValues
) const
{
	return interpolateToSource(tFld(), plusEqOp<Type>(), defaultValues);
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::AMIInterpolation::interpolateToTarget
(
	const Field<Type>& fld,
	const UList<Type>& defaultValues
) const
{
	return interpolateToTarget(fld, plusEqOp<Type>(), defaultValues);
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::AMIInterpolation::interpolateToTarget
(
	const tmp<Field<Type>>& tFld,
	const UList<Type>& defaultValues
) const
{
	return interpolateToTarget(tFld(), plusEqOp<Type>(), defaultValues);
}


// ************************************************************************* //