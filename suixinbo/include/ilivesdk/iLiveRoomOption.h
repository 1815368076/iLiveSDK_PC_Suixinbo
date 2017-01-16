#ifndef iLiveRoomOption_h_
#define iLiveRoomOption_h_

#include <ilivesdk/iLiveCommon.h>
#include <avsdk/av_common.h>
#include <avsdk/av_room_multi.h>

using tencent::av::AudioCategory;
using tencent::av::AVRoomMulti;
using tencent::av::VideoRecvMode;

namespace ilivesdk
{
	/**
	@brief SDK�����˳������������ָ�롣
	@details SDK�ڲ�����Ϊ30s��������ʱ��ԭ�������˳����䣬APP��Ҫ�������˳������¼����Ը��¼�������Ӧ����
	@param [in] reason �˳�ԭ��, �ο�av_error.h��
	@param [in] data �û��Զ��������ͣ��ص�������ԭ�ⲻ�����ظ�ҵ��ࡣ
	*/
	typedef void (*iLiveRoomDisconnectListener)(int32 reason, void* data);
	/**
	@brief �����ڳ�Ա�仯��������ָ�롣
	@details �������Ա����״̬�仯(���Ƿ���Ƶ���Ƿ���Ƶ��)ʱ����ͨ���ú���ָ��֪ͨҵ��ࡣ
	@param [in] event_id ״̬�仯id�����EndpointEventId�Ķ��塣
	@param [in] identifier_list ����״̬�仯�ĳ�Աid�б�
	@param [in] data �û��Զ��������ͣ��ص�������ԭ�ⲻ�����ظ�ҵ��ࡣ
	*/
	typedef void (*iLiveMemStatusListener)(AVRoomMulti::EndpointEventId event_id, std::vector<std::string> identifier_list, void* data);
	/**
    @brief ���Զ�ģʽ��������ͷ��Ƶ���¼�֪ͨ��
    @details ���Զ�ģʽ��������ͷ��Ƶ���¼�֪ͨ��Ҳ���ǵ����뷿��ʱ������Ѿ����˷�������Ƶ������Զ�������Щ��Ƶ�������ֶ�ȥ���󡣵�Ȼ�����뷿�������������ٷ�����Ƶ���򲻻��Զ����ա�
	@param [in] identifier_list �Զ����յ�����ͷ��Ƶ����Ӧ�ĳ�Աid�б�
	@param [in] data �û��Զ��������ͣ��ص�������ԭ�ⲻ�����ظ�ҵ��ࡣ
    */
	typedef	void (*iLiveSemiAutoRecvCameraVideoListener)(std::vector<std::string> identifier_list, void* data);

	/**
	@brief iLiveRoom�����
	@details �ڴ������߼��뷿��ʱ����Ҫ����д�˽ṹ��Ϊ��������;
	*/
	struct iLiveRoomOption
	{
		/**
		@brief ���캯������ʼ����Ա����ֵ��
		*/
		iLiveRoomOption()
			:roomId(0)
			,m_roomDisconnectListener(NULL)
			,m_memberStatusListener(NULL)
			,m_autoRecvListener(NULL)
			,data(NULL)
		{
		}

		uint32			roomId;			///< ����ID,��ҵ��ഴ����ά���ķ���ID
		std::string		auth_buffer;	///< ͨ������Ȩ��λ�ļ��ܴ�
		std::string		control_role;	///< ��ɫ����web������Ƶ�������ù��������õĽ�ɫ��
		AudioCategory	audio_category;	///< ���ӳ�������,��ϸ��Ϣ��AudioCategory�Ķ���.
		VideoRecvMode	video_recv_mode;///< ��Ƶ����ģʽ

		iLiveRoomDisconnectListener				m_roomDisconnectListener; ///< SDK�����˳�������ʾ,�μ�iLiveRoomDisconnectListener���塣
		iLiveMemStatusListener					m_memberStatusListener;	  ///< �����Ա״̬�仯֪ͨ���μ�iLiveMemStatusListener���塣
		iLiveSemiAutoRecvCameraVideoListener	m_autoRecvListener;		  ///< ���Զ�ģʽ��������ͷ��Ƶ��֪ͨ���μ�iLiveSemiAutoRecvCameraVideoListener���塣
		void*									data;					  ///< �û��Զ����������ͣ���m_roomDisconnectListener��m_memberStatusListener��m_autoRecvListener��ԭ�ⲻ�����ء�
	};
}

#endif//iLiveRoomOption_h_