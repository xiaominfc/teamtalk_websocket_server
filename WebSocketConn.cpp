/*
 * =====================================================================================
 *
 *       Filename:  WebSocketConn.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/23/16 09:59:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <WebSocketConn.h>

void WebSocketConn::OnRead()
{
    for (;;)
    {
        uint32_t free_buf_len = m_in_buf.GetAllocSize() - m_in_buf.GetWriteOffset();
        if (free_buf_len < READ_BUF_SIZE)
            m_in_buf.Extend(READ_BUF_SIZE);
        int ret = netlib_recv(m_handle, m_in_buf.GetBuffer() + m_in_buf.GetWriteOffset(), READ_BUF_SIZE);
        if (ret <= 0)
            break;
        m_recv_bytes += ret;
        m_in_buf.IncWriteOffset(ret);
        m_last_recv_tick = get_tick_count();
    }
/*
    if(m_websocket == NULL)
    {
        m_websocket = new WebSocket;
    }
*/
    
    WebSocket websocket;
    if(m_websocket_inited)
    {
        CImPdu *pPdu = NULL;
        unsigned char *dataBuffer = (unsigned char*)malloc(m_in_buf.GetWriteOffset());
        try{
            int data_length = 0;
            int use_length = 0;
            int read_count = 0;
            WebSocketFrameType frameType = websocket.getFrame(m_in_buf.GetBuffer() ,m_in_buf.GetWriteOffset() ,dataBuffer ,m_in_buf.GetWriteOffset(), data_length,use_length);
            log("len:%d use:%d",m_in_buf.GetWriteOffset(),use_length);
            while(frameType == BINARY_FRAME || frameType == TEXT_FRAME)
            {
                read_count = read_count + use_length;
                while((pPdu = CImPdu::ReadPdu((uchar_t*)dataBuffer,data_length)))
                {
                    uint32_t pdu_len = pPdu->GetLength();
                    HandlePdu(pPdu);
                    //m_in_buf.Read(NULL, pdu_len);
                    //dataBuffer = dataBuffer + pdu_len;
                    delete pPdu;
                    pPdu = NULL;
                    break;
                }
                if(read_count >= m_in_buf.GetWriteOffset()) {
                    break;
                }
                data_length = 0;
                use_length = 0;
                frameType = websocket.getFrame(m_in_buf.GetBuffer() + read_count,m_in_buf.GetWriteOffset() ,dataBuffer ,m_in_buf.GetWriteOffset(), data_length,use_length);
            }
            m_in_buf.~CSimpleBuffer();
        }catch(CPduException& ex)
        {

        }
        free(dataBuffer);

    }else 
    {
        WebSocketFrameType type = websocket.parseHandshake(m_in_buf.GetBuffer(),m_in_buf.GetWriteOffset()); 
        if(type == OPENING_FRAME) {
            string answer = websocket.answerHandshake();
            CMsgConn::Send((void *)answer.c_str(), answer.size());
            m_in_buf.Read(NULL, m_in_buf.GetWriteOffset());
            m_in_buf.~CSimpleBuffer();
            m_websocket_inited = true;                        
        }else {
            //OnClose();
        }    
    }
}



int WebSocketConn::Send(void *data, int len)
{
    WebSocket websocket;
    unsigned char* outData = (unsigned char*)malloc(len + 14);
    int out_len = websocket.makeFrame(BINARY_FRAME, (unsigned char*)data,len,outData ,len + 14);
    int result =  CMsgConn::Send(outData ,out_len);
    free(outData);
    return result;
}
