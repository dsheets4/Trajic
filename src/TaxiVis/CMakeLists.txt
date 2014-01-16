
# =============================================================================
# Configure files

# -----------------------------------------------------------------------------
SET(TAXIVIS_DEFAULT_WIDTH 800)  # Default window width
SET(TAXIVIS_DEFAULT_HEIGHT 600) # Default window height
CONFIGURE_FILE(
   "${CMAKE_CURRENT_SOURCE_DIR}/TaxiVisConstants.in.h" 
   "${CMAKE_CURRENT_BINARY_DIR}/TaxiVisConstants.h"
)


# =============================================================================
# Add subdirectories
ADD_SUBDIRECTORY( exe_gui )
