if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cmdplus PROPERTY CXX_STANDARD 20)
endif()

aux_source_directory(./HospitalSys/src HOSPITALSYS_DIR_SRCS)
add_executable (HospitalSys ${HOSPITALSYS_DIR_SRCS})

aux_source_directory(./LibraySystemC/src LIBRAYSYSTEMC_DIR_SRCS)
add_executable (LibraySystemC ${LIBRAYSYSTEMC_DIR_SRCS})

aux_source_directory(./LoanSys/src LOANSYS_DIR_SRCS)
add_executable (LoanSys ${LOANSYS_DIR_SRCS})


aux_source_directory(./ShoppingSys/src SHOPPINGSYS_DIR_SRCS)
add_executable (ShoppingSys ${SHOPPINGSYS_DIR_SRCS})

aux_source_directory(./ShopSysC1/src SHOPSYSC1_DIR_SRCS)
add_executable (ShopSysC1 ${SHOPSYSC1_DIR_SRCS})

aux_source_directory(./SubwayChargeC0/src SUBWAYCHARGEC0_DIR_SRCS)
add_executable (SubwayChargeC0 ${SUBWAYCHARGEC0_DIR_SRCS})
