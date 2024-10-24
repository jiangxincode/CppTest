aux_source_directory(./HospitalSys/src HOSPITALSYS_DIR_SRCS)
add_executable (HospitalSys ${HOSPITALSYS_DIR_SRCS})
target_compile_options(HospitalSys
        PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:/Zc:strictStrings->"
)

aux_source_directory(./LibraySystemC/src LIBRAYSYSTEMC_DIR_SRCS)
add_executable (LibraySystemC ${LIBRAYSYSTEMC_DIR_SRCS})
target_compile_options(LibraySystemC
        PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:/Zc:strictStrings->"
)

aux_source_directory(./LoanSys/src LOANSYS_DIR_SRCS)
add_executable (LoanSys ${LOANSYS_DIR_SRCS})
target_compile_options(LoanSys
        PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:/Zc:strictStrings->"
)

aux_source_directory(./ShoppingSys/src SHOPPINGSYS_DIR_SRCS)
add_executable (ShoppingSys ${SHOPPINGSYS_DIR_SRCS})
target_compile_options(ShoppingSys
        PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:/Zc:strictStrings->"
)

aux_source_directory(./ShopSysC1/src SHOPSYSC1_DIR_SRCS)
add_executable (ShopSysC1 ${SHOPSYSC1_DIR_SRCS})
target_compile_options(ShopSysC1
        PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:/Zc:strictStrings->"
)

aux_source_directory(./SubwayChargeC0/src SUBWAYCHARGEC0_DIR_SRCS)
add_executable (SubwayChargeC0 ${SUBWAYCHARGEC0_DIR_SRCS})
target_compile_options(SubwayChargeC0
        PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:/Zc:strictStrings->"
)
