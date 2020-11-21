#pragma once
#ifndef _Constant_Header
#define _Constant_Header

#include <Function1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace Function1Types
	{

		/*---------------------------------------------------------------------------*\
								   Class Constant Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class Constant
			:
			public Function1<Type>
		{
			// Private Data

				//- Constant value
			Type value_;


		public:

			// Runtime type information
			//TypeName("constant");
			static const char* typeName_() { return "constant"; }
			static FoamBase_EXPORT const ::tnbLib::word typeName;
			static FoamBase_EXPORT int debug;
			virtual const word& type() const { return typeName; };


			// Constructors

				//- Construct from entry name and value
			Constant(const word& entryName, const Type& val);

			//- Construct from entry name and dictionary
			Constant(const word& entryName, const dictionary& dict);

			//- Construct from entry name and Istream
			//  Reads the constant value without the Function1 type
			//  for backward compatibility
			Constant(const word& entryName, Istream& is);

			//- Copy constructor
			Constant(const Constant<Type>& cnst);

			//- Construct and return a clone
			virtual tmp<Function1<Type>> clone() const
			{
				return tmp<Function1<Type>>(new Constant<Type>(*this));
			}


			//- Destructor
			virtual ~Constant();


			// Member Functions

				//- Return constant value
			virtual inline Type value(const scalar) const;

			//- Integrate between two values
			virtual inline Type integrate(const scalar x1, const scalar x2) const;

			//- Return value as a function of (scalar) independent variable
			virtual tmp<Field<Type>> value(const scalarField& x) const;

			//- Integrate between two (scalar) values
			virtual tmp<Field<Type>> integrate
			(
				const scalarField& x1,
				const scalarField& x2
			) const;

			//- Write in dictionary format
			virtual void writeData(Ostream& os) const;


			// Member Operators

				//- Disallow default bitwise assignment
			void operator=(const Constant<Type>&) = delete;
		};


		template<>
		FoamBase_EXPORT tmp<Field<label>> Function1Types::Constant<label>::integrate
		(
			const scalarField& x1,
			const scalarField& x2
		) const;


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace Function1Types
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <ConstantI.hxx>
#include <Constant_Imp.hxx>

//#ifdef NoRepository
//#include <Constant.cxx>
//#include <Function1New.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * // 

#endif // !_Constant_Header
