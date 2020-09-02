cmake_minimum_required(VERSION 2.6)
PROJECT(websocket_server)

AUX_SOURCE_DIRECTORY(./ SRC_LIST)
AUX_SOURCE_DIRECTORY(../msg_server MSG_SERVER_SRC_LIST)

#SET(LIBRARY_OUTPUT_PATH ./)
SET(EXECUTABLE_OUTPUT_PATH  ./)



SET(PB_INCLUDE_DIR ../protobuf/include)
SET(PB_LIB_DIR ../protobuf/lib)


#设置自己mac os的openssl的路径
if(APPLE)
    SET(OPENSSL_INCLUDE_DIR /usr/local/Cellar/openssl/1.0.2n/include)
    SET(OPENSSL_LIB_DIR /usr/local/Cellar/openssl/1.0.2n/lib)
endif()



if(APPLE)
    SET(SECURITY_LIB_DIR ../base/security/lib/mac)
    SET(OTHER_INCLUDE /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift-migrator/sdk/MacOSX.sdk/usr/include/)
elseif(UNIX)
    SET(SECURITY_LIB_DIR ../base/security/lib/linux)
endif()


ADD_DEFINITIONS( -g -W -Wall -D_REENTRANT -D_FILE_OFFSET_BITS=64 -DAC_HAS_INFO
-DAC_HAS_WARNING -DAC_HAS_ERROR -DAC_HAS_CRITICAL -DTIXML_USE_STL
-DAC_HAS_DEBUG -DLINUX_DAEMON -std=c++11  -Wno-deprecated)

INCLUDE_DIRECTORIES(./ ../msg_server ../base ./websocket ../base/jsoncpp ../base/pb/protocol ${PB_INCLUDE_DIR} ../base/security/ ${OPENSSL_INCLUDE_DIR}  ${OTHER_INCLUDE})
LINK_DIRECTORIES(./ ../base ./websocket  ${PB_LIB_DIR} ../base/slog/lib  ../slog  ${SECURITY_LIB_DIR} ${OPENSSL_LIB_DIR})

#ADD_XXXX必须在TARGET_LINK_LIBRARIES前面，否则会报错
#ADD_LIBRARY(${PROJECTNAME} SHARED/STATIC ${SRC_LIST})

LIST(REMOVE_ITEM MSG_SERVER_SRC_LIST ../msg_server/msg_server.cpp)

# remove client_connect_impl.cpp for teamtalk project that my fork 
LIST(REMOVE_ITEM MSG_SERVER_SRC_LIST ../msg_server/client_connect_impl.cpp)
#LIST(REMOVE_ITEM MSG_SERVER_SRC_LIST ../msg_server/LoginServConn.cpp)

ADD_EXECUTABLE(websocket_server ${SRC_LIST} ${MSG_SERVER_SRC_LIST})

TARGET_LINK_LIBRARIES(websocket_server base websocket protobuf-lite slog crypto ssl pthread )
 
