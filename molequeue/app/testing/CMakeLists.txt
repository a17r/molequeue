include_directories(${CMAKE_SOURCE_DIR}/molequeue
  ${CMAKE_BINARY_DIR}/molequeue/client
  ${CMAKE_BINARY_DIR}/molequeue/app/testing)

set(MoleQueue_HAS_ZMQ ${USE_ZERO_MQ})
set(MoleQueue_TESTDATA_DIR
  "${MoleQueue_SOURCE_DIR}/molequeue/app/testing/data/")
set(MoleQueue_TESTSCRIPT_DIR
  "${MoleQueue_SOURCE_DIR}/molequeue/app/testing/scripts/")
set(MoleQueue_TESTEXEC_DIR "${MoleQueue_BINARY_DIR}/bin/")
if(PYTHON_EXECUTABLE)
  set(MoleQueue_PYTHON_EXECUTABLE "${PYTHON_EXECUTABLE}")
endif()
configure_file(molequeuetestconfig.h.in molequeuetestconfig.h)

if(USE_ZERO_MQ)
  add_definitions(-DUSE_ZERO_MQ)
endif()

set(testutils_SRCS
  dummyconnection.cpp
  dummyconnectionlistener.cpp
  dummyqueuemanager.cpp
  dummyqueueremote.cpp
  dummyserver.cpp
  dummysshcommand.cpp
  referencestring.cpp
  testserver.cpp
  xmlutils.cpp
)

add_library(testutils STATIC ${testutils_SRCS})
set_target_properties(testutils PROPERTIES AUTOMOC TRUE)
qt5_use_modules(testutils Test)
target_link_libraries(testutils molequeue_static)

set(MyTests
  filespecification
  jobmanager
  jsonrpc
  message
  pbs
  program
  queue
  queuemanager
  queueremote
  server
  sge
  slurm
  sshcommand
  )

# This test is currently only configured to run on unix
if(NOT WIN32)
  list(APPEND MyTests clientserver)
endif()

if(MoleQueue_USE_EZHPC_UIT)
  list(APPEND MyTests
    authenticatecont
    authenticateresponse
    compositeiodevice
    dirlistinginfo
    filestreamingdata
    jobeventlist
    jobsubmissioninfo
    kerberoscredentials
    uit
    userhostassoclist)
endif()

foreach(test ${MyTests})
  add_executable(${test}test MACOSX_BUNDLE ${test}test.cpp)
  qt5_use_modules(${test}test Test)
  set_target_properties(${test}test PROPERTIES AUTOMOC TRUE)
  target_link_libraries(${test}test testutils)
  add_test(NAME molequeue-${test} COMMAND ${test}test)
endforeach()

add_subdirectory(clienttestsrc)
