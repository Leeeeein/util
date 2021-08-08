//
// Created by hujianzhe on 2019-7-10.
//

#ifndef	UTIL_C_DATASTRUCT_TRANSPORT_CTX_H
#define	UTIL_C_DATASTRUCT_TRANSPORT_CTX_H

#include "list.h"

enum {
	NETPACKET_SYN = 1,				/* [reliable UDP client connect] or [client reconnect] use */
	NETPACKET_SYN_ACK,				/* [reliable UDP listener] or [reconnect ack] use */
	NETPACKET_ACK,
	NETPACKET_NO_ACK_FRAGMENT,		/* only tcp use */
	NETPACKET_NO_ACK_FRAGMENT_EOF,
	NETPACKET_FIN,
	NETPACKET_FRAGMENT,
	NETPACKET_FRAGMENT_EOF
};
enum {
	NETPACKET_DGRAM_HAS_SEND_SEQ = NETPACKET_FIN,
	NETPACKET_STREAM_HAS_SEND_SEQ = NETPACKET_FRAGMENT
};

typedef struct NetPacket_t {
	ListNode_t node;
	char type;
	char wait_ack;
	char cached;
	union {
		/* dgram */
		struct {
			char resend_times;
			long long resend_msec;
		};
		/* stream */
		struct {
			unsigned int off;
		};
	};
	unsigned int seq;
	unsigned int hdrlen;
	unsigned int bodylen;
	unsigned char buf[1];
} NetPacket_t;

typedef struct DgramTransportCtx_t {
	List_t recvlist;
	List_t sendlist;
	unsigned char send_all_acked;
	unsigned char cwndsize;
	unsigned int cache_recv_bytes;
	/* private */
	unsigned int m_sendseq;
	unsigned int m_recvseq;
	unsigned int m_cwndseq;
	unsigned int m_ackseq;
	ListNode_t* m_recvnode;
} DgramTransportCtx_t;

typedef struct StreamTransportCtx_t {
	List_t recvlist;
	List_t sendlist;
	unsigned char send_all_acked;
	unsigned int cache_recv_bytes;
	/* private */
	unsigned int m_sendseq;
	unsigned int m_recvseq;
	unsigned int m_cwndseq;
} StreamTransportCtx_t;

#ifdef	__cplusplus
extern "C" {
#endif

__declspec_dll DgramTransportCtx_t* dgramtransportctxInit(DgramTransportCtx_t* ctx, unsigned int initseq);
__declspec_dll int dgramtransportctxRecvCheck(DgramTransportCtx_t* ctx, unsigned int seq, int pktype);
__declspec_dll void dgramtransportctxCacheRecvPacket(DgramTransportCtx_t* ctx, NetPacket_t* packet);
__declspec_dll int dgramtransportctxMergeRecvPacket(DgramTransportCtx_t* ctx, List_t* list);
__declspec_dll unsigned int dgramtransportctxNextSendSeq(DgramTransportCtx_t* ctx, int pktype);
__declspec_dll int dgramtransportctxCacheSendPacket(DgramTransportCtx_t* ctx, NetPacket_t* packet);
__declspec_dll int dgramtransportctxAckSendPacket(DgramTransportCtx_t* ctx, unsigned int ackseq, NetPacket_t** ackpacket);
__declspec_dll int dgramtransportctxSendWindowHasPacket(DgramTransportCtx_t* ctx, NetPacket_t* packet);

__declspec_dll StreamTransportCtx_t* streamtransportctxInit(StreamTransportCtx_t* ctx, unsigned int initseq);
__declspec_dll int streamtransportctxRecvCheck(StreamTransportCtx_t* ctx, unsigned int seq, int pktype);
__declspec_dll void streamtransportctxCacheRecvPacket(StreamTransportCtx_t* ctx, NetPacket_t* packet);
__declspec_dll int streamtransportctxMergeRecvPacket(StreamTransportCtx_t* ctx, List_t* list);
__declspec_dll int streamtransportctxSendCheckBusy(StreamTransportCtx_t* ctx);
__declspec_dll unsigned int streamtransportctxNextSendSeq(StreamTransportCtx_t* ctx, int pktype);
__declspec_dll int streamtransportctxCacheSendPacket(StreamTransportCtx_t* ctx, NetPacket_t* packet);
__declspec_dll int streamtransportctxAckSendPacket(StreamTransportCtx_t* ctx, unsigned int ackseq, NetPacket_t** ackpacket);
__declspec_dll List_t streamtransportctxRemoveFinishedSendPacket(StreamTransportCtx_t* ctx);

#ifdef	__cplusplus
}
#endif

#endif