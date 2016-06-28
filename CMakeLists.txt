cmake_minimum_required(VERSION 2.6)
PROJECT(websocket_server)

AUX_SOURCE_DIRECTORY(./ SRC_LIST)
AUX_SOURCE_DIRECTORY(../msg_server MSG_SERVER_SRC_LIST)

#SET(LIBRARY_OUTPUT_PATH ./)
SET(EXECUTABLE_OUTPUT_PATH  ./)
if(APPLE)
    SET(PB_LIB_DIR ../base/pb/lib/mac)
    SET(SECURITY_LIB_DIR ../base/security/lib/mac)
    SET(OTHER_INCLUDE /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift-migrator/sdk/MacOSX.sdk/usr/include/)
elseif(UNIX)
    SET(PB_LIB_DIR ../base/pb/lib/linux)
    SET(SECURITY_LIB_DIR ../base/security/lib/linux)
endif()


ADD_DEFINITIONS( -g -W -Wall -D_REENTRANT -D_FILE_OFFSET_BITS=64 -DAC_HAS_INFO
-DAC_HAS_WARNING -DAC_HAS_ERROR -DAC_HAS_CRITICAL -DTIXML_USE_STL
-DAC_HAS_DEBUG -DLINUX_DAEMON -std=c++11)

INCLUDE_DIRECTORIES(./ ../msg_server ../base ./websocket ../base/pb/protocol ../base/pb/ ../base/security/ ${OTHER_INCLUDE})
LINK_DIRECTORIES(./ ../base ./websocket  ${PB_LIB_DIR} ../base/slog/lib ${SECURITY_LIB_DIR})

#ADD_XXXX必须在TARGET_LINK_LIBRARIES前面，否则会报错
#ADD_LIBRARY(${PROJECTNAME} SHARED/STATIC ${SRC_LIST})

LIST(REMOVE_ITEM MSG_SERVER_SRC_LIST ../msg_server/msg_server.cpp)
LIST(REMOVE_ITEM MSG_SERVER_SRC_LIST ../msg_server/LoginServConn.cpp)

ADD_EXECUTABLE(websocket_server ${SRC_LIST} ${MSG_SERVER_SRC_LIST})

TARGET_LINK_LIBRARIES(websocket_server base websocket protobuf-lite slog crypto pthread )
 
