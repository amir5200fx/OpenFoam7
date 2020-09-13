#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
Type tnbLib::subModelBase::getBaseProperty
(
	const word& entryName,
	const Type& defaultValue
) const
{
	Type result = defaultValue;

	if (properties_.found(baseName_))
	{
		const dictionary& baseDict = properties_.subDict(baseName_);
		baseDict.readIfPresent(entryName, result);
	}

	return result;
}


template<class Type>
void tnbLib::subModelBase::getBaseProperty
(
	const word& entryName,
	Type& value
) const
{
	if (properties_.found(baseName_))
	{
		const dictionary& baseDict = properties_.subDict(baseName_);
		baseDict.readIfPresent(entryName, value);
	}
}


template<class Type>
void tnbLib::subModelBase::setBaseProperty
(
	const word& entryName,
	const Type& value
)
{
	if (properties_.found(baseName_))
	{
		dictionary& baseDict = properties_.subDict(baseName_);
		baseDict.add(entryName, value, true);
	}
	else
	{
		properties_.add(baseName_, dictionary());
		properties_.subDict(baseName_).add(entryName, value);
	}
}


template<class Type>
void tnbLib::subModelBase::getModelProperty
(
	const word& entryName,
	Type& value
) const
{
	if (properties_.found(baseName_))
	{
		const dictionary& baseDict = properties_.subDict(baseName_);

		if (inLine() && baseDict.found(modelName_))
		{
			baseDict.subDict(modelName_).readIfPresent(entryName, value);
		}
		else if (baseDict.found(modelType_))
		{
			baseDict.subDict(modelType_).readIfPresent(entryName, value);
		}
	}
}


template<class Type>
Type tnbLib::subModelBase::getModelProperty
(
	const word& entryName,
	const Type& defaultValue
) const
{
	Type result = defaultValue;
	getModelProperty(entryName, result);
	return result;
}


template<class Type>
void tnbLib::subModelBase::setModelProperty
(
	const word& entryName,
	const Type& value
)
{
	if (properties_.found(baseName_))
	{
		dictionary& baseDict = properties_.subDict(baseName_);

		if (inLine())
		{
			if (baseDict.found(modelName_))
			{
				baseDict.subDict(modelName_).add(entryName, value, true);
			}
			else
			{
				baseDict.add(modelName_, dictionary());
				baseDict.subDict(modelName_).add(entryName, value, true);
			}
		}
		else
		{
			if (baseDict.found(modelType_))
			{
				baseDict.subDict(modelType_).add(entryName, value, true);
			}
			else
			{
				baseDict.add(modelType_, dictionary());
				baseDict.subDict(modelType_).add(entryName, value, true);
			}
		}
	}
	else
	{
		properties_.add(baseName_, dictionary());

		if (inLine())
		{
			properties_.subDict(baseName_).add(modelName_, dictionary());
			properties_.subDict(baseName_).subDict(modelName_).add
			(
				entryName,
				value
			);
		}
		else
		{
			properties_.subDict(baseName_).add(modelType_, dictionary());
			properties_.subDict(baseName_).subDict(modelType_).add
			(
				entryName,
				value
			);
		}
	}
}


// ************************************************************************* //