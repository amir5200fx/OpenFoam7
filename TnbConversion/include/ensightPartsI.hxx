#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
void tnbLib::ensightParts::writeField
(
	ensightFile& os,
	const GeometricField<Type, fvPatchField, volMesh>& field
) const
{
	// find offset to patch parts (ie, the first face data)
	label patchOffset = 0;
	forAll(partsList_, partI)
	{
		if (partsList_[partI].isFaceData())
		{
			patchOffset = partI;
			break;
		}
	}

	forAll(partsList_, partI)
	{
		label patchi = partI - patchOffset;

		if (partsList_[partI].isCellData())
		{
			partsList_[partI].writeField
			(
				os,
				field
			);
		}
		else if (patchi < field.boundaryField().size())
		{
			partsList_[partI].writeField
			(
				os,
				field.boundaryField()[patchi]
			);
		}
	}
}


// ************************************************************************* //