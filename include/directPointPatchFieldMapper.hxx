#pragma once
#ifndef _directPointPatchFieldMapper_Header
#define _directPointPatchFieldMapper_Header

#include <pointPatchFieldMapper.hxx>
#include <directFieldMapper.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					 Class directPointPatchFieldMapper Declaration
	\*---------------------------------------------------------------------------*/

	class directPointPatchFieldMapper
		:
		public pointPatchFieldMapper,
		public directFieldMapper
	{
		// Private Data

			//- Addressing from new back to old
		const labelUList& addressing_;

		//- Does map contain any unmapped values
		bool hasUnmapped_;


	public:

		// Constructors

			//- Construct given addressing
		directPointPatchFieldMapper(const labelUList& addressing)
			:
			addressing_(addressing),
			hasUnmapped_(false)
		{
			if (addressing_.size() && min(addressing_) < 0)
			{
				hasUnmapped_ = true;
			}
		}


		//- Destructor
		virtual ~directPointPatchFieldMapper()
		{}


		// Member Functions

		bool hasUnmapped() const
		{
			return hasUnmapped_;
		}

		const labelUList& addressing() const
		{
			return addressing_;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_directPointPatchFieldMapper_Header
