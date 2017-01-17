#pragma once
#include "xptypes.h"
#include "bicsprotocoldef.h"
#include "AVGUDTCodec.h"



class _XP_CLS IUDTParamCallback
{
public:
    virtual void OnSetSkipInfo( boolean bSkipFlag, uint32 uLeftFrm, uint32 uTotalFrm ) = 0;
    virtual void OnSetUnsendDataInTick( uint32 uDataLen ) = 0;
    virtual void OnSetLostRateBeforeArq( uint32 uCurLostRate, uint32 uTotalPkg, uint32 uRealPkg ) = 0;
    virtual void OnSetUDTSendCwnd( uint32 uUDTSendCwnd ) = 0;
};

typedef struct tagUDTSkipInfo
{
    uint32 uBufLenInTick;
    uint32 uSkipLeftFrm;
    uint32 uSkipTotalFrm;
    tagUDTSkipInfo()
    {
        uBufLenInTick = 0;
        uSkipLeftFrm = 0;
        uSkipTotalFrm = 0;
    }
} UDTSkipInfo;

class _XP_CLS IUDTParam
{
public:
    virtual void SetSkipInfoTable( UDTSkipInfo *pUDTSkipInfoTable,int32 nUDTSkipInfoTableLen ) = 0;
    virtual void GetTotalSendSpeed( uint32 &uSendSpeed, uint32 &uSendPacket ) = 0;
    virtual void GetSendSpeed( uint32 &uSendSpeed, uint32 &uSendPacket ) = 0;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct tagUDTLossRate
{
    uint32 dwLoss100;
    uint32 dwTotalNum;
    uint32 dwRealNum;
    uint32 dwAvgLossCnt;

    tagUDTLossRate()
    {
        dwLoss100 = 0;
        dwTotalNum = 0;
        dwRealNum = 0;
        dwAvgLossCnt = 0;
    }
};

enum emGVUdtRecvPacketEvent
{
    AVGUdtRecvPacketEvent_LossRequest = 0,  //��������
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct tagUDTSendParams
{
    uint16 wQueuePeriod;      // ���г��Ⱥ���
    uint16 wResendMin;        // ��С�ط����
    uint16 wResendMax;        // ����ط����
    uint16 wRTTDelta;         // RTT+wRTTDelta�ó��ط����
    uint16 wMaxResendCnt;     // ÿ�����ݰ�����ط��Ĵ���
    uint16 wTimerResendCnt;   // ÿ��timer�ط�������
    uint16 wCalcSendLossTime;
    boolean bCongestion;
    uint16 wCwndLossRate;
    uint16 wCwndDownFactor;
    uint64 u64CwndUpTable;
    uint16 wCwndMin;
    uint16 wMinCwndMax;
    uint16 wRTOFactor;
    uint16 wCongestionLen;
};

class IUDTSendEventCallBack
{
public:
    //pc��NotifyUDTSendEventûʵ�����á������Ȳ�ʵ�֡�
    //virtual void NotifyUDTSendEvent(UDTSendEvent enEvt, ITXData* pData) = 0;
    virtual void UDTSendDataToNet(uint8*pBuf, uint32 uLen) = 0;
};

class _XP_CLS IUDTSend
{
public:
    virtual boolean Start() = 0;
    virtual void Stop() = 0;
    virtual boolean UDTSaveRawData(uint8*pBuf, uint32 uSize, uint32 dwSeq, uint8 cSubType) = 0;
    virtual boolean UDTRecvACK(uint32* arSeq, uint16 wSeqNum) = 0;
    virtual void UDTSetSendParams(const tagUDTSendParams& param) = 0;
    virtual void UDTSetResendTimeByRTT(uint32 dwRTT) = 0;
    virtual void UDTCalcSendLoss(uint32& dwLoss100, uint32& dwTotalNum, uint32& dwRealNum, uint32& dwAvgLossMode) = 0;
    virtual void UDTEnableResend(boolean bEnable) = 0;
    virtual void UDTEnableCongestion(boolean bEnable) = 0;
    virtual boolean OnSenderAvailable( uint32 uLimit ) = 0;
    virtual boolean CheckOverBuffer() = 0;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct tagUDTRecvParams
{
    uint16 wQueuePeriod;
    uint16 wFirstGetTime;
    uint16 wNextGetTime;
    uint16 wGetPkgTimeout;
    uint16 wCalcRecvLossTime;
    uint16 wTimelineDelta;
    uint16 wOutPutDelay;      //20160709
    uint16 wPeriodMinDelay;   //20160709
    uint16 wUdtMode;          //20160709
    uint16 wPushGopNum;       //20160709
};

typedef struct tagUdtPacketHeadInfo
{
    uint8  cHeadLen;        //ͷ��Ϣ�ĳ���
    uint8  cSubType;        //����������Ƶ��С��Ƶ
    uint8  cFrmType;        //����Ƶ������֡������
    uint8  cPkgIndex;       //packet index
    uint8  cTotalPkgCount;  //total packet num of frame, exclude fec packet
    uint8  cFecPkgCount;    //fec packet num
    uint8  cFrameIndex;     //֡index
    uint8  cGopIndex;       //GOP index
    uint32 uTimeStamp;      //MediaEngine��MultiContrlPkgHeadDefͷ�����ʱ��

    tagUdtPacketHeadInfo()
    {
        cHeadLen  = 0;
        cSubType  = 0;
        cFrmType  = 0;
        cPkgIndex = 0;
        cTotalPkgCount = 0;
        cFecPkgCount = 0;
        cFrameIndex = 0;
        cGopIndex   = 0;
        uTimeStamp  = 0;
    }

} UdtPacketHeadInfo, *pUdtPacketHeadInfo;

struct tagReplyData
{
    uint64 ullUserAccount;
    uint8 cSubType;
    uint32 dwUserSeq;
    uint8 cResult;
    tagReplyData()
    {
        ullUserAccount = 0;
        cSubType = 0;
        dwUserSeq = 0;
        cResult = 0;
    }
};

class IUDTRecvEventCallBack
{
public:
	virtual void OnUDTRecvOutData(UDTCodecBaseDecode_V2 *pRecvData, int* nAudioPlayDelayRTS = NULL) = 0;

	/*
      SendUdtData����Server������ָ��
	  pBuffer�Ǹ���wType������ȥ����
	  wTypeΪemGVUdtSendPacketType����
	  ��wType = GVUdtSendPacketType_LossRequestʱ
	  pBuffer������Ϊ:
	  wDataNum(uint16)+dwUin(uint32)+dwSeq(uint32)+...+dwUin(uint32)+dwSeq(uint32)+dwReserve(uint32)
	  nSendCount:�ط�����
	*/
	virtual int UdtRecvHandleEvent(uint16 wType, uint8 *pBuffer, uint32 nBufSize, uint32 nSendCount, uint32 nUdtV2) = 0;

    /* samqn udt_s: �������յ������ݰ��İ�ͷ��Ϣ 20160222 */
    virtual int UdtParsePacketHeadInfo(uint8 *pRecvData, UdtPacketHeadInfo &stUdtPktHeadInfo) = 0;
};

class _XP_CLS IUDTRecv
{
public:
    virtual void Stop() = 0;
    virtual void Start() = 0;
    virtual void UDTSetRecvRTT(uint32 dwRTT) = 0;
    virtual void UDTSetRecvParams(const tagUDTRecvParams& params) = 0;
    virtual void UDTCalcRecvLoss(uint32& dwLoss100, uint32& dwTotalNum, uint32& dwRealNum, uint32& dwAvgLossMode) = 0;
    virtual void GetDownPacketRecvInfo(uint32 &dwExpectRecv, uint32 &dwRealRecv, uint32 &dwBytesRecv, uint32 &dwIFrmLostInfo) = 0;
    virtual void UDTEnableReGetPkg(boolean bEnable) = 0;
    virtual void SetRoomState(uint32 dwRoomState) = 0;
    virtual boolean UDTReceiveNetData(uint32 dwSendSeq, uint64 llAccount, uint32 dwSeq, uint16 wTimeStamp, uint8 cSubType, UDTCodecBaseDecode_V2 *pData) = 0;
    virtual void ClearRecvChn(uint64 llAccount, uint32 dwIsClearAll) = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class _XP_CLS ILogWriterCallback
{
public:

};

typedef void (*LogUDTFunc)(int level, const char* module, const char *file, int line, const char *func, const char* format, va_list args);

#ifdef __cplusplus
extern "C" {
#endif
    _XP_API bool CreateUDTSend(IUDTSend **ppUDTSend, IUDTSendEventCallBack *pCallBack);
    _XP_API bool CreateUDTRecv(IUDTRecv **ppUDTRecv, IUDTRecvEventCallBack *pCallBack);
    _XP_API bool GetUDTParam(IUDTParam **ppParam, IUDTParamCallback *pCallBack);
    _XP_API bool SetLogFunction(LogUDTFunc pLogFunc, bool bUdtLogDetail);
    _XP_API bool DestroyUDTSend(IUDTSend *pUDTSend);
    _XP_API bool DestroyUDTRecv(IUDTRecv *pUDTRecv);
#ifdef __cplusplus
}

#endif