/**
@file 
@brief Defines macros intended to allow for a convenient conversion from 
       enumerations to string and vice versa.

@details 

   The macros of interest are provided as examples below.  The user must 
   create an enumeration in a header file.  As a general recommendation,
   it is advised to place the enumeration in a namespace to avoid name
   clashing.  The user defines an enumeration and matching set of string
   values representing those enumerations.  The macros add some additional 
   enumeration values at the end of the enumeration definition and define
   conversion from enumeration to string and vice versa.  In the example
   LIBRARY_EXPORT_MACRO represents the import/export macro for the 
   library.  e.g.
   
   @code
   #define LIBRARY_EXPORT_MACRO __declspec(dllimport).
   @endcode

   The END_ENUM macro adds in some additional values to the 
   enumeration that allow a generic implementation of the conversion 
   code.  The STRING_ENUM_FUNCS_HDR macro defines the prototypes for the 
   conversion functions.

@code
   //! In a header file define the following.
   namespace MyEnum
   {
      //! Describe the general purpose of the enumeration
      enum Enum
      {
         MyEnumValue,  //!< Describe the use of this value

         END_ENUM
      };

      STRING_ENUM_FUNCS_HDR(LIBRARY_EXPORT_MACRO);
   };
@endcode


Then, in a source file, add the following to implement the 
functionality.  Note that the string representation does not need to 
match the enumeration exactly.  This allows the string version to be 
more user friendly.

@code
   // An enumeration of all the available options of the class.
   namespace MyEnum
   {
      std::string strings[] = {
         "My Enum Value"
      };

      STRING_ENUM_FUNCS_SRC(LIBRARY_EXPORT_MACRO);
   };
@endcode

This allows conversions from string to enumeration and enumeration to
string using the following constructs.

@code
   // Convert a string to the enumeration value.
   MyEnum::Enum e = MyEnum::ToEnum  ( "My Enum Value" );

   // Convert an enumeration value to a string.
   std::string  s = MyEnum::ToString(  MyEnumValue  );
@endcode

*/
#include <string>
#include <QtGlobal>

// ============================================================================
//! @todo Work on componentizing the definitions in StringEnumeration to 
//!       reduce some of the duplication.  For example, the word Unknown is 
//!       repeated several times as is Num_Enums.  This will likely cause 
//!       some rippling with additional libraries requiring linking.  It
//!       also open up some additional definitions that aren't intended
//!       for use outside this specific header.  We'll need to figure out
//!       a good approach for this.
// ============================================================================


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    Do not use these macros directly.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//! Not for external use!
//! Macro to abstract and coordinate the conversion function signatures.
#define STRING_TO_ENUM	Enum ToEnum( std::string s )

//! Not for external use!
//! Macro to abstract and coordinate the conversion function signatures.
#define ENUM_TO_STRING	std::string ToString( Enum e )
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ============================================================================
//  Macros that define the enumerations with string conversions.
// ============================================================================
//! Use this definition if there is no export required so that the macro will 
//! compile.
//! @code
//!      STRING_ENUM_FUNCS_HDR( STRING_ENUM__NO_LIB_EXPORT );
//!      // OR
//!      STRING_ENUM_FUNCS_SRC( STRING_ENUM__NO_LIB_EXPORT );
//! @endcode
#define STRING_ENUM__NO_LIB_EXPORT

//! Macro that is placed at the END of the enumeration definition to inject 
//! some additional values used in the conversion functions.
#define END_ENUM		Num_Enums,Unknown

//! The macro placed in the namespace definition within a header file
//! to provide the conversion function prototypes.
#define STRING_ENUM_FUNCS_HDR(LibExport) \
   LibExport STRING_TO_ENUM; \
   LibExport ENUM_TO_STRING;


//! The macro placed in the namespace definition within a source file
//! to provide the conversion function implementation.
#define STRING_ENUM_FUNCS_SRC(LibExport) \
   LibExport STRING_TO_ENUM\
      {\
         Q_ASSERT( Num_Enums == (sizeof(strings)/sizeof(std::string)) );\
         for( int i = 0; i < Num_Enums; ++i ) \
         { \
            if( s == strings[i] ) \
               return static_cast<Enum>( i ); \
         } \
         Q_ASSERT(s == "Unknown"); \
         return Unknown; \
      } \
      \
      LibExport ENUM_TO_STRING \
      { \
         Q_ASSERT( Num_Enums == (sizeof(strings)/sizeof(std::string)) );\
         if( e < Num_Enums ) \
            return strings[e]; \
         else \
         { \
            Q_ASSERT(e == Unknown); \
            return "Unknown"; \
         } \
      }

// ============================================================================
// ============================================================================
