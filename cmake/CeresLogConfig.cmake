include(GNUInstallDirs)


install(TARGETS CeresLog
    EXPORT CeresLog-export
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(EXPORT CeresLog-targets
  FILE
    CeresLogTargets.cmake
  NAMESPACE
    CeresLog::
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/CeresLog
)

get_filename_component(CeresLog_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(CMakeFindDependencyMacro)

if(NOT TARGET CeresLog::CeresLog)
    include("${CeresLog_CMAKE_DIR}/CeresLogTargets.cmake")
endif()