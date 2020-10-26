set(OE_QMAKE_PATH_EXTERNAL_HOST_BINS $ENV{OE_QMAKE_PATH_HOST_BINS})
# set(QT_MOC_EXECUTABLE /home/wuzhuobin/Qt5.12.7/5.12.7/gcc_64/bin/moc)
# add_executable(Qt5::moc IMPORTED)
# set_property(
#   TARGET Qt5::moc
#   PROPERTY IMPORTED_LOCATION ${QT_MOC_EXECUTABLE}
# )
# set(QT_UIC_EXECUTABLE /home/wuzhuobin/Qt5.12.7/5.12.7/gcc_64/bin/uic)
# add_executable(Qt5::uic IMPORTED)
# set_property(
#   TARGET Qt5::uic
#   PROPERTY IMPORTED_LOCATION ${QT_UIC_EXECUTABLE}
# )
# set(QT_RCC_EXECUTABLE /home/wuzhuobin/Qt5.12.7/5.12.7/gcc_64/bin/rcc)
# add_executable(Qt5::rcc IMPORTED)
# set_property(
#   TARGET Qt5::rcc
#   PROPERTY IMPORTED_LOCATION ${QT_RCC_EXECUTABLE}
# )
set(
  QWT_INCLUDE_DIR /home/wuzhuobin/ccode/qwt-6.1.4/install-arm/qwt-6.1.4/include
  CACHE PATH ""
  FORCE
)
set(
  QWT_LIBRARY /home/wuzhuobin/ccode/qwt-6.1.4/install-arm/qwt-6.1.4/lib/libqwt.so.6.1.4
  CACHE FILEPATH ""
  FORCE
)
# set(CMAKE_SYSROOT /home/wuzhuobin/fslc-x11-glibc-x86_64-core-image-x11-cortexa9t2hf-neon-imx6qdlsabresd-toolchain-2.7/sysroots)