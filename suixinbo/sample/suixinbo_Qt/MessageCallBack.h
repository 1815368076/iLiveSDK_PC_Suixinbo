#ifndef MessageCallBack_h_
#define MessageCallBack_h_

#include <imsdk/tim_msg.h>

#define ILVLIVE_IMCMD_CUSTOM_LOW_LIMIT 0x800
#define ILVLIVE_IMCMD_CUSTOM_UP_LIMIT 0x900

enum E_CustomCmd
{
	AVIMCMD_None,               // ���¼���0

	AVIMCMD_EnterLive,          // �û�����ֱ��, Group��Ϣ �� 1
	AVIMCMD_ExitLive,           // �û��˳�ֱ��, Group��Ϣ �� 2
	AVIMCMD_Praise,             // ������Ϣ, Demo��ʹ��Group��Ϣ �� 3
	AVIMCMD_Host_Leave,         // �����򻥶������뿪, Group��Ϣ �� 4
	AVIMCMD_Host_Back,          // �����򻥶����ڻ���, Group��Ϣ �� 5

	AVIMCMD_Multi = ILVLIVE_IMCMD_CUSTOM_LOW_LIMIT,  // ���˻�����Ϣ���� �� 2048

	AVIMCMD_Multi_Host_Invite,          // ������������������Ϣ, C2C��Ϣ �� 2049
	AVIMCMD_Multi_CancelInteract,       // �ѽ��뻥��ʱ���Ͽ�������Group��Ϣ�����Ͽ��ߵ�imUsreid���� �� 2050
	AVIMCMD_Multi_Interact_Join,        // ���˻������յ�AVIMCMD_Multi_Host_Invite���������ͬ�⣬C2C��Ϣ �� 2051
	AVIMCMD_Multi_Interact_Refuse,      // ���˻������յ�AVIMCMD_Multi_Invite��������󣬾ܾ���C2C��Ϣ �� 2052
};

class MessageCallBack : public imcore::TIMMessageCallBack
{
public:
	virtual void OnNewMessage(const std::vector<TIMMessage> &msgs);
	
	static 	QQueue<TIMMessage>	ms_messageQueue;
};

class ForceOfflineCallBack : public imcore::TIMForceOfflineCallBack
{
public:
	virtual void OnForceOffline();
};

#endif//MesageCallBack_h_