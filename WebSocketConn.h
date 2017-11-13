/*
 * =====================================================================================
 *
 *       Filename:  WebSocketConn.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/23/16 09:44:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yangzhimin, 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef WEBSOCKETCONN_H_
#define WEBSOCKETCONN_H_

#include <MsgConn.h>
#include <WebSocket.h>

class WebSocketConn :public CMsgConn {
public:
	WebSocketConn():CMsgConn(){m_websocket_inited = false;}
	virtual void OnRead();
	virtual int Send(void* data, int len);
private:
	bool m_websocket_inited;
	//WebSocket *m_websocket;
};

#endif
