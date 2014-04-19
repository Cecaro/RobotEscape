###############################################################################
# PROJECT_ALL_DIR - store all directories under the project
# used by the find<package>.cmake modules
# PROJECT_ALL_LIB_DIR - store all directories under the project
# which stores the built libraries
#

# - Try to find VECTORMATH
# Once done this will define following variables
#
# VECTORMATH_FOUND - system has VectorMath
# VECTORMATH_INCLUDE_DIRS - the VectorMath include directory
# VECTORMATH_LIBRARY_DIRS - the VectorMath library directory
# VECTORMATH_LIBRARIES - Link these to use VectorMath
#

SET( VECTORMATH_FOUND TRUE )
SET( VECTORMATH_INCLUDE_DIRS ${PROJECT_ALL_DIR} )
SET( VECTORMATH_LIBRARY_DIRS ${PROJECT_ALL_LIB_DIR} )
SET( VECTORMATH_LIBRARIES )

## verbose
#IF( BUILD_VERBOSE )
#MESSAGE( STATUS
#"----verbose: VECTORMATH_INCLUDE_DIRS:
#${VECTORMATH_INCLUDE_DIRS}" )
#MESSAGE( STATUS
#"----verbose: VECTORMATH_LIBRARY_DIRS:
#${VECTORMATH_LIBRARY_DIRS}" )
#MESSAGE( STATUS
#"----verbose: VECTORMATH_LIBRARIES:
#${VECTORMATH_LIBRARIES}" )
#ENDIF( BUILD_VERBOSE )

