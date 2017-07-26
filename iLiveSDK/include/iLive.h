#ifndef iLive_h_
#define iLive_h_

#include <iLiveCommon.h>
#include <iLiveString.h>
#include <iLiveVector.h>
#include <iLivePair.h>

namespace ilive
{
	/**
	@brief iLiveSDK�����뼯��
	*/
	enum E_iLiveError
	{
		INVALID_INTETER_VALUE   = -1,   ///< ��Ч�����ͷ���ֵ(ͨ��)
		NO_ERR                  = 0,    ///< �ɹ�
		ERR_IM_NOT_READY        = 8001, ///< IMģ��δ������δ����
		ERR_AV_NOT_READY        = 8002, ///< AVģ��δ������δ����
		ERR_NO_ROOM             = 8003, ///< ����Ч�ķ���
		ERR_ALREADY_EXIST       = 8004, ///< Ŀ���Ѵ���
		ERR_NULL_POINTER        = 8005, ///< ��ָ�����
		ERR_ENTER_AV_ROOM_FAIL  = 8006, ///< ����AV����ʧ��
		ERR_USER_CANCEL         = 8007, ///< �û�ȡ��
		ERR_WRONG_STATE         = 8008, ///< ״̬�쳣
		ERR_NOT_LOGIN			= 8009, ///< δ��¼
		ERR_ALREADY_IN_ROOM		= 8010, ///< ���ڷ�����
		ERR_BUSY_HERE			= 8011,	///< �ڲ�æ(��һ����δ���)
		ERR_NET_UNDEFINE		= 8012, ///< ����δʶ������粻�ɴ�
		ERR_SDK_FAILED          = 8020, ///< iLiveSDK����ʧ��(ͨ��)
		ERR_INVALID_PARAM       = 8021, ///< ��Ч�Ĳ���
		ERR_NOT_FOUND           = 8022, ///< �޷��ҵ�Ŀ��
		ERR_NOT_SUPPORT         = 8023, ///< ����֧��
		ERR_ALREADY_STATE       = 8024, ///< ״̬�ѵ�λ(һ��Ϊ�ظ���������)
		ERR_KICK_OUT            = 8050, ///< ��������
		ERR_EXPIRE              = 8051, ///< Ʊ�ݹ���(�����Ʊ��userSig)
	};

	/**
	@brief �����¼�
	*/
	enum E_EndpointEventId
	{
		EVENT_ID_NONE = 0,						///< ��
		EVENT_ID_ENDPOINT_ENTER = 1,			///< ���뷿���¼�
		EVENT_ID_ENDPOINT_EXIT = 2,				///< �˳������¼�
		EVENT_ID_ENDPOINT_HAS_CAMERA_VIDEO = 3, ///< �з�����ͷ��Ƶ�¼�
		EVENT_ID_ENDPOINT_NO_CAMERA_VIDEO = 4,	///< �޷�����ͷ��Ƶ�¼�
		EVENT_ID_ENDPOINT_HAS_AUDIO = 5,		///< �з���Ƶ�¼�
		EVENT_ID_ENDPOINT_NO_AUDIO = 6,			///< �޷���Ƶ�¼�
		EVENT_ID_ENDPOINT_HAS_SCREEN_VIDEO = 7, ///< �з���Ļ��Ƶ�¼�
		EVENT_ID_ENDPOINT_NO_SCREEN_VIDEO = 8,	///< �޷���Ļ��Ƶ�¼�
		EVENT_ID_ENDPOINT_HAS_MEDIA_VIDEO = 9,	///< �в�����Ƶ�¼�
		EVENT_ID_ENDPOINT_NO_MEDIA_VIDEO = 10,	///< �޲�����Ƶ�¼�
	};

	/**
	@brief ��Ƶ��������
	*/
	enum E_AudioCategory
	{
		AUDIO_CATEGORY_VOICECHAT = 0,				///< VoIPģʽ���ʺ���ʵʱ��Ƶͨ�ų�������ʵʱ����ͨ��
		AUDIO_CATEGORY_MEDIA_PLAY_AND_RECORD = 1,	///< ý��ɼ��벥��ģʽ���ʺ�����Щ������Ҫ��Ƚϸߵ�ֱ�������������������е�������Ա
		AUDIO_CATEGORY_MEDIA_PLAYBACK = 2,			///< ý�岥��ģʽ���ʺ�����Щ������Ҫ��Ƚϸߵ�ֱ�������������������е�����
	};

	/**
	@brief ��Ϣ���͡�
	*/
	enum E_MessageElemType
	{
		TEXT,
		CUSTOM,
	};

	/**
	@brief ��Ƶ�����ʽ
	*/
	enum E_iLiveStreamEncode
	{
		HLS = 0x01,			///< ����FLV�������Ƶ��URL
		FLV = 0x02,			///< ����HLS�������Ƶ��URL
		HLS_AND_FLV = 0x03, ///< ͬʱ����HLS��FLV�������Ƶ��URL
		RAW = 0X04,			///< RAW����
		RTMP = 0X05,		///< RTMP
		HLS_AND_RTMP = 0X06,///< HLS AND RTMP
	};

	/**
	@brief ¼���������� 
	*/
	enum E_RecordDataType
	{
		E_RecordCamera = 0, ///< ¼������ͷ
		E_RecordScreen,		///< ¼�Ƹ���(��Ļ����)
	};

	/**
	@brief ¼���ļ�����(RecordFile_NONE��¼��)
	*/
	enum E_RecordFileType
	{
		RecordFile_NONE= 0,
		RecordFile_HLS = 1,
		RecordFile_FLV = 2,
		RecordFile_HLS_FLV = 3,
		RecordFile_MP4 = 4,
		RecordFile_HLS_MP4 = 5,
		RecordFile_FLV_MP4 = 6,
		RecordFile_HLS_FLV_MP4 = 7
	};

	/**
	@brief ������������
	*/
	enum E_PushDataType
	{
		E_PushCamera = 0,///< ����ͷ
		E_PushScreen,	 ///< ����(��Ļ����)
	};

	/**
	@brief ���ʵ�λ
	*/
	enum E_RateType
	{
		RATE_TYPE_ORIGINAL = 0,	///< ԭʼ����
		RATE_TYPE_550 = 10,		///< ��������550K
		RATE_TYPE_900 = 20,		///< ��������900K
	};

	/**
	@brief ɫ�ʸ�ʽ��
	*/
	enum E_ColorFormat
	{
		COLOR_FORMAT_NONE = -1,		///< ������
		COLOR_FORMAT_I420 = 0,		///< i420��ʽ
		COLOR_FORMAT_NV21 = 1,
		COLOR_FORMAT_NV12 = 3,
		COLOR_FORMAT_RGB16 = 7,
		COLOR_FORMAT_RGB24 = 8,		///< rgb24��ʽ
		COLOR_FORMAT_RGB32 = 9,
	};

	/**
	@brief ��Ļ����״̬��
	@details ��Ļ����״̬��
	*/
	enum E_ScreenShareState
	{
		E_ScreenShareNone,	///< δ������Ļ����
		E_ScreenShareWnd,	///< ������ָ�����ڵĹ���
		E_ScreenShareArea,	///< ������ָ������Ĺ���
	};

	/**
	@brief ��Ƭ״̬��
	*/
	enum E_PlayMediaFileState
	{
		E_PlayMediaFileStop,	///< ֹͣ����
		E_PlayMediaFilePlaying,	///< ������
		E_PlayMediaFilePause,	///< ��ͣ��
	};

	/**
	@brief ��Ƶ�������͡�
	@details ��Ƶ�������͡�
	*/
	enum E_VideoSrc
	{
		VIDEO_SRC_TYPE_NONE = 0,	///< Ĭ��ֵ��������
		VIDEO_SRC_TYPE_CAMERA = 1,	///< ����ͷ
		VIDEO_SRC_TYPE_SCREEN = 2,	///< ��Ļ
		VIDEO_SRC_TYPE_MEDIA = 3,	///< ��Ƭ
	};

	/**
	@brief �豸��������
	*/
	enum E_DeviceOperationType
	{
		E_DeviceOperationNone,		///< Ĭ��ֵ��������
		E_OpenCamera,				///< ������ͷ
		E_CloseCamera,				///< �ر�����ͷ
		E_OpenExternalCapture,		///< ���Զ���ɼ�
		E_CloseExternalCapture,		///< �ر��Զ���ɼ�
		E_OpenMic,					///< ����˷�
		E_CloseMic,					///< �ر���˷�
		E_OpenPlayer,				///< ��������
		E_ClosePlayer,				///< �ر�������
		E_OpenScreenShare,			///< ����Ļ����
		E_CloseScreenShare,			///< �ر���Ļ����
		E_OpenSystemVoiceInput,		///< ��ϵͳ�����ɼ�
		E_CloseSystemVoiceInput,	///< �ر�ϵͳ�����ɼ�
		E_OpenPlayMediaFile,		///< ���ļ�����
		E_ClosePlayMediaFile,		///< �ر��ļ�����
	};

	/// ����Ƶͨ����ͨ������Ȩ��λ��
	const uint64 AUTH_BITS_DEFAULT              = -1;			///< ����Ȩ�ޡ�
	const uint64 AUTH_BITS_CREATE_ROOM          = 0x00000001;	///< ��������Ȩ�ޡ�
	const uint64 AUTH_BITS_JOIN_ROOM            = 0x00000002;	///< ���뷿���Ȩ�ޡ�
	const uint64 AUTH_BITS_SEND_AUDIO           = 0x00000004;	///< ������Ƶ��Ȩ�ޡ�
	const uint64 AUTH_BITS_RECV_AUDIO           = 0x00000008;	///< ������Ƶ��Ȩ�ޡ�
	const uint64 AUTH_BITS_SEND_CAMERA_VIDEO    = 0x00000010;	///< ��������ͷ��Ƶ��Ȩ�ޡ�
	const uint64 AUTH_BITS_RECV_CAMERA_VIDEO    = 0x00000020;	///< ��������ͷ��Ƶ��Ȩ�ޡ�
	const uint64 AUTH_BITS_SEND_SCREEN_VIDEO    = 0x00000040;	///< ������Ļ��Ƶ��Ȩ�ޡ�
	const uint64 AUTH_BITS_RECV_SCREEN_VIDEO    = 0x00000080;	///< ������Ļ��Ƶ��Ȩ�ޡ�

	/**
	@brief �������߻ص�����ָ������;
	*/
	typedef void (*ForceOfflineCallback)();
	
	/**
	@brief �ɹ���ֵ�ص�����ָ�����͵ķ�װ
	*/
	template <typename T>
	struct Type
	{
		/**
		@brief ͨ�õĳɹ���ֵ�ص�����ָ������;
		@param [in] value �����ɹ���SDK���ظ�ҵ�����Ӧ���͵�ֵ;
		@param [in] data SDK����ҵ����Զ��������ָ��;
		*/
		typedef void (*iLiveValueSuccCallback)(T value, void* data);
	};

	/**
	@brief �յ���Ϣ�Ļص�����ָ�����͡�
	@param [in] msg �յ���Ⱥ��Ϣ
	*/
	typedef void (*iLiveMessageCallback)( const struct Message &msg, void* data );

	/**
    @brief ��Ƶ֡Ԥ����ص�
    @param video_frame ��Ƶ֡����
    @param data �Զ���ָ��
    */
	typedef void (*iLivePreTreatmentCallback)( struct LiveVideoFrame* video_frame, void* data );
	/**
    @brief ��Ƶ֡�ص�
    @param video_frame ��Ƶ֡����
    @param data �Զ���ָ��
    */
    typedef void (*iLivePreviewCallback)( const struct LiveVideoFrame* video_frame, void* data );

	/**
	@brief �豸�����ص�
	@param [in] oper �豸��������;
	@param [in] retCode �����룬NO_ERR��ʾ�ɹ�;
	@param [in] data �Զ���ָ��;
	*/
	typedef void (*iLiveDeviceOperationCallback)(E_DeviceOperationType oper, int retCode, void* data);
	/**
	@brief ͨ��ʧ�ܻص�
	@param [in] code ������
	@param [in] desc ��������
	@param [in] data �Զ���ָ��
	*/
	typedef void (*iLiveErrCallback)(const int code, const char *desc, void* data);
	/**
	@brief ͨ�óɹ��ص�
	@param [in] data �Զ���ָ��
	*/
	typedef void (*iLiveSuccCallback)(void* data);

	/**
	@brief SDK�����˳������������ָ��
	@details SDK�ڲ�����Ϊ30s��������ʱ��ԭ�������˳����䣬APP��Ҫ�������˳������¼����Ը��¼�������Ӧ����
	@param [in] reason �˳�ԭ�������
	@param [in] errorinfo �˳�ԭ������
	@param [in] data �û��Զ�����ָ�룬�ص�������ԭ�ⲻ�����ظ�ҵ���
	*/
	typedef void (*iLiveRoomDisconnectListener)(int reason, const char *errorInfo, void* data);
	/**
	@brief �����ڳ�Ա�仯��������ָ��
	@details �������Ա����״̬�仯(���Ƿ���Ƶ���Ƿ���Ƶ��)ʱ����ͨ���ú���ָ��֪ͨҵ���
	@param [in] event_id ״̬�仯id�����EndpointEventId�Ķ���
	@param [in] identifier_list ����״̬�仯�ĳ�Աid�б�
	@param [in] data �û��Զ��������ͣ��ص�������ԭ�ⲻ�����ظ�ҵ���
	*/
	typedef void (*iLiveMemStatusListener)(E_EndpointEventId eventId, const Vector<String> &ids, void* data);

	/**
	@brief ��ϢԪ�ػ���
	*/
	struct MessageElem
	{
		E_MessageElemType type;
		virtual ~MessageElem() {};
	};

	/**
	@brief �ı���ϢԪ��
	*/
	struct MessageTextElem : public MessageElem
	{
		MessageTextElem(const String& _content)
		:content(_content)
		{
			type = TEXT;
		}
		String content;
	};

	/**
	@brief �Զ�����ϢԪ��
	*/
	struct MessageCustomElem : public MessageElem
	{
		MessageCustomElem(const String& _data, const String& _ext) : data(_data), ext(_ext)
		{
			type = CUSTOM;
		}
		String data;
		String ext;
	};

	/**
	@brief ��Ϣ
	@details һ����Ϣ�ڿ��԰��������ϢԪ�أ�����˳������vector��
	*/
	struct Message
	{
		String sender;
		Vector<MessageElem*> elems;
		
		Message()
		{
		}

		Message(const Message& other)
		{
			sender = other.sender;
			for (int i = 0; i < other.elems.size(); ++i)
			{
				const MessageElem* elem = other.elems[i];
				switch(elem->type)
				{
				case TEXT:
					{
						const MessageTextElem *otherElem = static_cast<const MessageTextElem*>(other.elems[i]);
						MessageTextElem *e = new MessageTextElem(otherElem->content);
						elems.push_back(e);
						break;
					}
				case CUSTOM:
					{
						const MessageCustomElem *otherElem = static_cast<const MessageCustomElem*>(other.elems[i]);
						MessageCustomElem *e = new MessageCustomElem(otherElem->data, otherElem->ext);
						elems.push_back(e);
						break;
					}
				}
			}
		}

		Message& Message::operator=(const Message& other)
		{
			if (&other == this) return *this;
			sender = other.sender;
			for (int i = 0; i < other.elems.size(); ++i)
			{
				const MessageElem* elem = other.elems[i];
				switch(elem->type)
				{
				case TEXT:
					{
						const MessageTextElem *otherElem = static_cast<const MessageTextElem*>(other.elems[i]);
						MessageTextElem *e = new MessageTextElem(otherElem->content);
						elems.push_back(e);
						break;
					}
				case CUSTOM:
					{
						const MessageCustomElem *otherElem = static_cast<const MessageCustomElem*>(other.elems[i]);
						MessageCustomElem *e = new MessageCustomElem(otherElem->data, otherElem->ext);
						elems.push_back(e);
						break;
					}
				}
			}
			return *this;
		}

		~Message()
		{
			for (int i = 0; i < elems.size(); ++i)
			{
				delete elems[i];
			}
		}
	};
	
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
			:audioCategory(AUDIO_CATEGORY_MEDIA_PLAY_AND_RECORD)//����ֱ������
			,roomId(0)
			,autoRequestCamera(true)
			,autoRequestScreen(true)
			,autoRequestMediaFile(true)
			,roomDisconnectListener(NULL)
			,memberStatusListener(NULL)
			,data(NULL)
		{
		}

		E_AudioCategory			audioCategory;			///< ���ӳ�������,��ϸ��Ϣ��E_AudioCategory�Ķ���.
		uint32					roomId;					///< ����ID,��ҵ��ഴ����ά���ķ���ID
		String					controlRole;			///< ��ɫ����web������Ƶ�������ù��������õĽ�ɫ��
		String					authBuffer;				///< ͨ������Ȩ��λ�ļ��ܴ�
		bool					autoRequestCamera;		///< �������г�Ա������ͷʱ���Ƿ��Զ�������;
		bool					autoRequestScreen;		///< �������г�Ա����Ļ����ʱ���Ƿ��Զ�������;
		bool					autoRequestMediaFile;	///< �������г�Ա�򿪲�Ƭʱ���Ƿ��Զ�������;

		iLiveRoomDisconnectListener	roomDisconnectListener;	///< SDK�����˳�����ص�;һ����������Ͽ�30���,���յ��˻ص�,��ʱ�ѱ�sdkǿ���˳�����,����,��Ҫ�����˳�����ӿ�;����������,��Ҫ���´���\���뷿��,�μ�iLiveRoomDisconnectListener���塣
		iLiveMemStatusListener		memberStatusListener;	///< �����Ա״̬�仯֪ͨ���μ�iLiveMemStatusListener���塣
		void*						data;					///< �û��Զ����������ͣ���roomDisconnectListener��memberStatusListener��ԭ�ⲻ�����ء�
	};

	/**
	@brief ¼�������
	@details ¼�Ʋ�����Ҫ��������͵Ĳ�����
	*/
	struct RecordOption
	{
		/**
		@brief ���캯������ʼ����Ա����ֵ��
		*/
		RecordOption()
			:recordDataType(E_RecordCamera)
			,fileName("")
			,classId(0)
		{
		}

		E_RecordDataType	recordDataType; ///< ¼�Ƶ���������,�μ�E_RecordDataType���塣
		String				fileName;		///< ¼�ƺ���ļ�����
		int					classId;		///< ��Ƶ����ID(����Ч)��
	};

	/**
	@brief ���������
	@details ����������Ҫ��������͵Ĳ�����
	*/
	struct PushStreamOption
	{
		/**
		@brief ���캯������ʼ����Ա������
		*/
		PushStreamOption()
			:pushDataType(E_PushCamera)
			,encode(HLS)
			,recordFileType(RecordFile_NONE)
		{
		}

		E_PushDataType				pushDataType;		///< �����������ͣ��μ�E_PushDataType����.
		E_iLiveStreamEncode			encode;				///< �������ݱ��뷽ʽ���μ�E_TIMStreamEncode����.
		E_RecordFileType			recordFileType;		///< ����ʱ�Զ�¼�Ƶ��ļ����ͣ��μ�E_RecordFileType����.
	};

	/**
	@brief ��������url����
	*/
	struct LiveUrl
	{
		int			encodeType;	///< ��Ƶ����������
		String		url;		///< ��Ƶ������URL
		E_RateType	rateType;	///< ���ʵ�λ��Ϣ
	};
	
	/**
	@brief ����������������
	*/
	struct PushStreamRsp
	{
		PushStreamRsp()
			:channelId(0)
		{
		}

		Vector<LiveUrl>		urls;		///< Url�б�
		uint64				channelId;	///< Ƶ��ID
		uint32				tapeTaskId; ///< ¼�Ʊ��Ϊ¼�Ƶ�ʱ�����¼��task_id��Ч
	};

	/**
	@brief ��Ƶ֡������
	@details ��Ƶ֡������
	*/
	struct VideoFrameDesc
	{
		VideoFrameDesc()
		: colorFormat(COLOR_FORMAT_RGB24)
		, width(0)
		, height(0)
		, externalData(false)
		, rotate(0)
		, srcType(VIDEO_SRC_TYPE_CAMERA)
		{
		}

		E_ColorFormat	colorFormat;	///< ɫ�ʸ�ʽ�������ColorFormat�Ķ��塣
		uint32			width;			///< ��ȣ���λ�����ء�
		uint32			height;			///< �߶ȣ���λ�����ء�
		bool			externalData;	///< �����Ƿ������ⲿ����ͷ��
		E_VideoSrc		srcType;		///< ��ƵԴ���ͣ������VideoSrcType�Ķ��塣
		/**
		������ת�ĽǶȣ�
		- source_typeΪVIDEO_SRC_TYPE_CAMERAʱ����ʾ��ƵԴΪ����ͷ��
		  ���ն��ϣ�����ͷ������֧����ת�ģ�App��Ҫ������ת�Ƕȵ�����Ⱦ��Ĵ����Ա�֤�����������ʾ��
		- source_typeΪ����ֵʱ��rotate��Ϊ0��
		*/
		uint32			rotate;
	};

	/**
	@brief ��Ƶ֡��
	*/
	struct LiveVideoFrame
	{
		LiveVideoFrame()
		: dataSize(0)
		, data(NULL)
		, timeStamp(0)
		{
		}

		String			identifier;	///< ��Ƶ֡�����ķ����Աid��
		VideoFrameDesc	desc;		///< ��Ƶ֡������
		uint32			dataSize;	///< ��Ƶ֡�����ݻ�������С����λ���ֽڡ�
		uint8*			data;		///< ��Ƶ֡�����ݻ�������SDK�ڲ�����������ķ�����ͷš�
		uint64			timeStamp;  ///< ��Ƶ֡��ʱ�����SDK�ڲ����Զ���д�ã�utcʱ�䣬0Ϊ��Чֵ��
	};

	/**
	@brief ֱ������Ϣ
	*/
	struct AVStream
	{
		AVStream(String id, E_VideoSrc type): id(id), srcType(type) {};
		String		id;
		E_VideoSrc	srcType;
	};

	/**
	@brief �ӿڷ�װ����ӿ�
	*/
	struct iLive
	{
		/**
		@brief ��ȡ�汾��
		@return �汾��
		*/
		virtual const char *getVersion() = 0;
		/**
		@brief ��ʼ��
		@details ʹ��ilive�����ǰ�����ȳ�ʼ��
		@param [in] appId ����Ѷ�������sdkappid
		@param [in] accountType ����Ѷ�������accountType
		@param [in] imSupport �Ƿ���Ҫ����ȼ�ʱͨѶ����
		@return ���ز������,�ɹ��򷵻�NO_ERR
		*/
		virtual int init(const int appId, const int accountType, bool imSupport = true) = 0;
		/**
		@brief �ͷ�
		@details ʹ����ilive����Ҫ�ͷ���Դ��
		@param [in] suc �ɹ��ص�
		@param [in] err ʧ�ܻص�
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��);
		@remark �˺���������7��ǰ��������־�ļ�(iLiveSDK��AVSDK��IMSDK)��
		*/
		virtual void release(iLiveSuccCallback suc = NULL, iLiveErrCallback err = NULL, void* data = NULL) = 0;
		/**
		@brief ���ñ������߼���
		@details ÿ���˺Ų���ͬʱ��¼��̨�豸���������豸��¼��ͬ�˺�ʱ���յ����֪ͨ
		@param [in] cb �ص�����
		*/
		virtual void setForceOfflineCallback(ForceOfflineCallback cb) = 0;
		/**
		@brief ������Ϣ����
		@param [in] cb �ص�����
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��);
		@note ��ǰ����֮���Ⱥ��Ϣ�ᱻsdk���˵�;
		*/
		virtual void setMessageCallBack( iLiveMessageCallback cb, void* data ) = 0;

		/**
		@brief ����Ԥ������ָ�롣
		@details ����Ƶ�������ȥǰ���û������ڴ˻ص���������Ԥ����;
		@param [in] pPreTreatmentFun Ԥ������ָ�롣
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��);
		@remark Ԥ��������ʱ��Ҫ���ã���ÿ�����10ms��; ͬʱ���ܸı�ͼ���С��ͼ����ɫ��ʽ��
		@note SDK�������߳���ִ�д˻ص�.
		*/
		virtual void setPreTreatmentFun( iLivePreTreatmentCallback pPreTreatmentFun, void* data ) = 0;
		/**
		@brief ���ñ�����Ƶ�ص�����ָ�롣
		@param [in] pLocalVideoCB ������Ƶ�ص�����ָ��
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��);
		@remark ҵ���ʵ�ָûص�������SDK��ûص��������뱾����Ƶ������ݣ�ҵ����õ����ݺ������Ⱦ��ʾ
		*/
		virtual void setLocalVideoCallBack( iLivePreviewCallback pLocalVideoCB, void* data ) = 0;
		/**
		@brief ����Զ����Ƶ�ص�����ָ�롣
		@param [in] pRemoteVideoCB Զ����Ƶ�ص�����ָ��
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��);
		@remark ҵ���ʵ�ָûص�������SDK��ûص���������Զ����Ƶ������ݣ�ҵ����õ����ݺ������Ⱦ��ʾ
		*/
		virtual void setRemoteVideoCallBack( iLivePreviewCallback pRemoteVideoCB, void* data ) = 0;
		/**
		@brief �����豸�����ص�����ָ�롣
		@details ����ͷ���Զ���ɼ�����˷硢����������Ļ����ϵͳ�����ɼ����ļ����ŵ��豸�����������ͨ���˻ص�֪ͨ��ҵ��㡣
		@param [in] cb �豸�����Ļص�����ָ��.
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��);
		*/
		virtual	void setDeviceOperationCallback( iLiveDeviceOperationCallback cb, void* data ) = 0;
		/**
		@brief ��¼
		@param [in] userId �û�id
		@param [in] userSig �û�ǩ��
		@param [in] suc �ɹ��ص�
		@param [in] err ʧ�ܻص�
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��);
		*/
		virtual void login(const char *userId, const char *userSig, iLiveSuccCallback suc, iLiveErrCallback err, void* data) = 0;
		/**
		@brief �ǳ�
		@param [in] suc �ɹ��ص�
		@param [in] err ʧ�ܻص�
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��);
		*/
		virtual void logout(iLiveSuccCallback suc, iLiveErrCallback err, void* data) = 0;
		/**
		@brief ����ֱ������
		@param [in] roomOption ��������
		@param [in] suc �ɹ��ص�
		@param [in] err ʧ�ܻص�
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��);
		*/
		virtual void createRoom(const iLiveRoomOption &roomOption, iLiveSuccCallback suc, iLiveErrCallback err, void* data) = 0;
		/**
		@brief ����ֱ������
		@param [in] roomOption ��������
		@param [in] suc �ɹ��ص�
		@param [in] err ʧ�ܻص�
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��);
		*/
		virtual void joinRoom(const iLiveRoomOption& roomOption, iLiveSuccCallback suc, iLiveErrCallback err, void* data) = 0;
		/**
		@brief �˳�ֱ������
		@param [in] suc �ɹ��ص�
		@param [in] err ʧ�ܻص�
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��);
		*/
		virtual void quitRoom(iLiveSuccCallback suc, iLiveErrCallback err, void* data) = 0;
		/**
		@brief ����һ��������Ա����Ƶ����
		@param [in] streams �������
		@param [in] suc �ɹ��ص�
		@param [in] err ʧ�ܻص�
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��)
		@note 
		1��requestStream��������ȴ��첽�ص�����ִ�н����󣬲��ܽ����µ�requestStream����;<br/>
		2��requestStream��cancelStream��cancelAllStream���ܲ���ִ�У���ͬһʱ��ֻ�ܽ���һ�ֲ���;
		*/
		virtual void requestStream(const Vector<AVStream> &streams, iLiveSuccCallback suc, iLiveErrCallback err, void* data) = 0;
		/**
		@brief  ȡ��ָ���û��Ļ��档
		@param [in] streams ȡ������
		@param [in] suc �ɹ��ص�
		@param [in] err ʧ�ܻص�
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��)
		@note 
		1��cancelStream��������ȴ��첽�ص�����ִ�н����󣬲��ܽ����µ�cancelStream����;<br/>
		2��requestStream��cancelStream��cancelAllStream���ܲ���ִ�У���ͬһʱ��ֻ�ܽ���һ�ֲ���;
		*/
		virtual void cancelStream(const Vector<AVStream> &streams, iLiveSuccCallback suc, iLiveErrCallback err, void* data) = 0;
		/**
		@brief ȡ�������������Ƶ���档
		@param [in] suc �ɹ��ص�
		@param [in] err ʧ�ܻص�
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��)
		@note requestStream��cancelStream��cancelAllStream���ܲ���ִ�У���ͬһʱ��ֻ�ܽ���һ�ֲ���;
		*/
		virtual void cancelAllStream(iLiveSuccCallback suc, iLiveErrCallback err, void* data) = 0;
		/**
		@brief ��C2C��Ϣ
		@param [in] dstUser ���շ�id
		@param [in] message Ҫ���͵���Ϣ
		@param [in] suc �ɹ��ص�
		@param [in] err ʧ�ܻص�
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��)
		*/
 		virtual void sendC2CMessage( const char *dstUser, const Message	&message, iLiveSuccCallback suc, iLiveErrCallback err, void* data ) = 0;
 		/**
		@brief ��Ⱥ��Ϣ
		@param [in] message Ҫ���͵���Ϣ
		@param [in] suc �ɹ��ص�
		@param [in] err ʧ�ܻص�
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��)
		@note �˴�����Ⱥ��Ϣ���������ڵ�ǰֱ�����з���Ⱥ��Ϣ��
		*/
		virtual void sendGroupMessage( const Message &message, iLiveSuccCallback suc, iLiveErrCallback err, void* data ) = 0;
		/**
		@brief ��ʼ����
		@param [in] pushOption ��������
		@param [in] suc �ɹ��ص�
		@param [in] err ʧ�ܻص�
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��)
		*/
		virtual void startPushStream( const PushStreamOption& pushOption, Type<PushStreamRsp&>::iLiveValueSuccCallback suc, iLiveErrCallback err, void* data ) = 0;
		/**
		@brief ��������
		@param [in] channelId Ƶ��id(�������ɹ��ĵĻص��з��ص�Ƶ��id)
		@param [in] suc �ɹ��ص�
		@param [in] err ʧ�ܻص�
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��)
		*/
		virtual void stopPushStream( uint64 channelId, iLiveSuccCallback suc, iLiveErrCallback err, void* data ) = 0;

		/**
		@brief ��ʼ¼�ơ�
		@param [in] recordOption ¼������ѡ�
		@param [in] suc �ɹ��ص�
		@param [in] err ʧ�ܻص�
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��)
		*/
		virtual void startRecord(const RecordOption& recordOption, iLiveSuccCallback suc, iLiveErrCallback err, void* data) = 0;

		/**
		@brief ֹͣ¼�ơ�
		@param [in] suc �ɹ��ص�
		@param [in] err ʧ�ܻص�
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��)
		@remark ֹͣ¼�Ƴɹ��ص�������¼����Ƶ�ļ���ID�б�; ҵ��࿪���Զ�¼��ʱ�������ؿ��б��û���ֱ�ӵ���̨��ѯ��
		*/
		virtual void stopRecord(Type<Vector<String>&>::iLiveValueSuccCallback suc, iLiveErrCallback err, void* data) = 0;

		/**
		@brief ��������
		@param [in] role ��ɫ
		@param [in] suc �ɹ��ص�
		@param [in] err ʧ�ܻص�
		@param [in] data �û��Զ������ݵ�ָ�룬�ص�������ԭ�ⲻ���ش���(ͨ��Ϊ�������ָ��)
		*/
		virtual void changeRole( const char *role, iLiveSuccCallback suc, iLiveErrCallback err, void* data ) = 0;		 
		/**
		@brief �������ճ̶�
		@param [in] grade ���ճ̶Ȳ�����gradeȡֵ��Χ��0-9֮�䣬0��ʾ���չر�
		@return ����ֵΪNO_ERRʱ��ʾ�ɹ��������ʾʧ��
		@note ���ա����׹���ֻ�Ա�����������Ч��SDK������Զ���ɼ��������ա����״���;
		*/
		virtual int setSkinSmoothGrade(int grade) = 0;
		/**
		@brief �������׳̶�
		@param [in] grade ���׳̶Ȳ�����gradeȡֵ��Χ��0-9֮�䣬0��ʾ���׹ر�
		@return ����ֵΪNO_ERRʱ��ʾ�ɹ��������ʾʧ��
		@note ���ա����׹���ֻ�Ա�����������Ч��SDK������Զ���ɼ��������ա����״���;
		*/
		virtual int setSkinWhitenessGrade(int grade) = 0;
		/**
		@brief ��ȡ��������ͷ�б�
		@param [out] cameraList ���ػ�ȡ��������ͷ�б�,��һ��(����0)ΪϵͳĬ���豸;
		@return �������,NO_ERR��ʾ�޴���;���û�п�������ͷ,����AV_ERR_DEVICE_NOT_EXIST������(�������github�ϵĴ������);
		*/
		virtual int getCameraList( Vector< Pair<String/*id*/, String/*name*/> >& cameraList ) = 0;
		/**
		@brief ��ȡ������˷��б�
		@param [out] micList ���ػ�ȡ������˷��б�,��һ��(����0)ΪϵͳĬ���豸;
		@return �������,NO_ERR��ʾ�޴���;���û�п�����˷�,����AV_ERR_DEVICE_NOT_EXIST������(�������github�ϵĴ������);
		*/
		virtual int getMicList( Vector< Pair<String/*id*/, String/*name*/> >& micList ) = 0;
		/**
		@brief ��ȡ���õ��������б�
		@param [out] playerList ���ػ�ȡ�����������б�,��һ��(����0)ΪϵͳĬ���豸;
		@return �������,NO_ERR��ʾ�޴���;���û�п���������,����AV_ERR_DEVICE_NOT_EXIST������(�������github�ϵĴ������);
		*/
		virtual int getPlayerList( Vector< Pair<String/*id*/, String/*name*/> >& playerList ) = 0;
		/**
		@brief ��ȡ�������򿪵����д��ڡ�
		@param [out] wndList ���ػ�ȡ���Ĵ����б�(����˵����ɼ�����\�ޱ��ⴰ��\��С����״̬�Ĵ���)��
		@return �������,NO_ERR��ʾ�޴���;���û�пɷ�����,����AV_ERR_DEVICE_NOT_EXIST������(�������github�ϵĴ������);
		@remark �û����Ե��ô˽ӿڻ�ȡ���Խ�����Ļ����Ĵ��ھ���б�,Ҳ�����Լ���ȡ;
		*/
		virtual int getWndList( Vector< Pair<HWND/*id*/, String/*name*/> >& wndList ) = 0;
		/**
		@brief ������ͷ
		@param [in] szCameraId ͨ��getCameraList()������ȡ������ͷ�б��е�ĳ������ͷid
		@note 
		1��������ͷ�ɹ�������û����ϴ���ƵȨ�ޣ�����Զ���ʼ�ϴ�����ͷ��Ƶ;<br/>
		2��������ͷ�����ʹ��Զ���ɼ��ǻ���Ĳ���;���ͬʱ�򿪣��᷵�ش���AV_ERR_EXCLUSIVE_OPERATION(�������github�ϵĴ������)
		*/
		virtual void openCamera(const String& szCameraId) = 0;
		/**
		@brief �رյ�ǰ�򿪵�����ͷ
		*/
		virtual void closeCamera() = 0;
		/**
		@brief ���Զ���ɼ�
		@note 
		1�����Զ���ɼ��ɹ�������û����ϴ���ƵȨ�ޣ��û�ͨ��fillExternalCaptureFrame()�����ÿһ֡���潫��ͨ��sdk�ϴ�;<br/>
		2��������ͷ�����ʹ��Զ���ɼ��ǻ���Ĳ���;���ͬʱ�򿪣��᷵�ش���AV_ERR_EXCLUSIVE_OPERATION(�������github�ϵĴ������);
		*/
		virtual void openExternalCapture() = 0;
		/**
		@brief �ر��Զ���ɼ�
		*/
		virtual void closeExternalCapture() = 0;
		/**
		@brief �ⲿ������Ƶ���ݽӿڡ�
		@return ���������NO_ERR��ʾ�޴���;
		@note 
		1��Ŀǰsdk֧�ֵ�VideoFrame��ʽֻ��COLOR_FORMAT_RGB24��COLOR_FORMAT_I420,����������Ƶ֡���Ǵ����ָ�ʽ��������ERR_NOT_SUPPORT;<br/>
		2����Ƶֻ֡������Щ����(176*144��192*144��320*240��480*360��640*368��640*480��960*540��1280*720��144*176��144*192��240*320��360*480��368*640��480*640��540*960��720*1280),���򷵻�AV_ERR_INVALID_ARGUMENT(�������github�ϵĴ������);<br/>
		3����Ƶ֡�������10-15֡����;
		4���������Ƶ֡�ֱ���������ڿ���̨SPEAR�������õ�ֵ����Ƶ���ᱻ�ü���SPEAR���õķֱ���(������Ԥ������͹��ڶ˻����С���᲻һ��);<br/>
		   ���С�ڿ���̨���õ�ֵ�����ᰴ�մ������Ƶ֡��С���뵽���ڶ�(�����ᱻ�Ŵ󵽿���̨���õ�ֵ);
		*/
		virtual int fillExternalCaptureFrame( const LiveVideoFrame &frame ) = 0;
		/**
		@brief ����˷硣
		@param [in] szMicId ͨ��getMicList()������ȡ����˷��б��е�ĳ����˷�id��
		@note ����˷�ɹ�������û����ϴ�����Ȩ�ޣ�����Զ���ʼ�ϴ���˷���Ƶ��
		*/
		virtual void openMic(const String &szMicId) = 0;
		/**
		@brief ������˷���ǿ��
		@param [in] value ������˷���ǿ,ȡֵ��Χ[0,100].
		@return ���������NO_ERR��ʾ�޴���;
		@note 
		1����������˷���ǿ������ָ��˷�����,������Ϊ0�����ǻ�����Ƶ����;
		2��ֻ�д�����˷���ܽ�������,���򷵻�ERR_WRONG_STATE;<br/>
		3�������̨SPEAR�������ô���agc(��˷��Զ�����),����ֵ̫Сʱ���ᱻ�Զ���������;
		*/
		virtual int	setMicVolume(int value) = 0;
		/**
		@brief ��ȡ��˷���ǿ��
		@return ������˷���ǿ,δ����˷��򷵻�0;
		*/
		virtual uint32 getMicVolume() = 0;
		/**
		@brief �رյ�ǰ�򿪵���˷硣
		*/
		virtual void closeMic() = 0;
		/**
		@brief ����������
		@param [in] szPlayerId ͨ��getPlayerList()������ȡ���������б��е�ĳ��������id��
		@note ���������ɹ�������û��н�����ƵȨ�ޣ�����Զ���ʼ����Զ����Ƶ��
		*/
		virtual void openPlayer(const String& szPlayerId) = 0;
		/**
		@brief ����������������
		@param [in] value ������������Ŀ������,ȡֵ��Χ[0,100].
		@return ���������NO_ERR��ʾ�޴���;
		@note ֻ�д������������ܽ�������,���򷵻�ERR_WRONG_STATE;
		*/
		virtual int setPlayerVolume( uint32 value ) = 0;
		/**
		@brief ��ȡ������������
		@return ��������������,δ���������򷵻�0;
		*/
		virtual uint32 getPlayerVolume() = 0;
		/**
		@brief �رյ�ǰ�򿪵���������
		*/
		virtual void closePlayer() = 0;
		/**
		@brief ����Ļ����(ָ������)��
		@param [in] hWnd ��Ҫ����Ĵ��ھ��(NULL��ʾȫ��)����������hWnd������Ч���ھ��\���ڲ��ɼ�\���ڴ�����С��״̬�����᷵��ERR_INVALID_PARAM;
		@param [in] fps ����֡��,ȡֵ��Χ[1,10]��
		@remark ����Ĳ���(fps)���ܻᾭ��sdk�ڲ���������ͨ�����÷�ʽ���ظ������ߣ�ʵ�ʷ���ʹ�õ�fps�Դ���ֵΪ׼;
		@note
		��Ļ����Ͳ�Ƭ���ܶ���ͨ����·�����䣬������Ļ����Ͳ�Ƭ����ʹ��;
		��·�����Լ�ռ�ã��豸�����ص��У����ش�����AV_ERR_EXCLUSIVE_OPERATION(�������github�ϵĴ������);
		��������������Առ�ã��豸�����ص��У����ش�����AV_ERR_RESOURCE_IS_OCCUPIED(�������github�ϵĴ������);
		*/
		virtual void openScreenShare( HWND hWnd, uint32& fps ) = 0;
		/**
		@brief ����Ļ����(ָ������)��
		@param [in] left/top/right/bottom ��Ҫ������Ļ�������������Ͻ�����(left, top)�����½�����(right, bottom)������������Ļ�����Ͻ�����Ϊԭ��ġ�
		@param [in] fps ����֡�ʣ�ȡֵ��Χ[1,10];
		@remark ����Ĳ������ܻᾭ��sdk�ڲ�ϸ΢�ĵ�������ͨ�����÷�ʽ���ظ������ߣ�ʵ�ʵķ��������Դ��ص�ֵΪ׼;
		@note
		��Ļ����Ͳ�Ƭ���ܶ���ͨ����·�����䣬������Ļ����Ͳ�Ƭ����ʹ��;
		��·�����Լ�ռ�ã��豸�����ص��У����ش�����AV_ERR_EXCLUSIVE_OPERATION(�������github�ϵĴ������);
		��������������Առ�ã��豸�����ص��У����ش�����AV_ERR_RESOURCE_IS_OCCUPIED(�������github�ϵĴ������);
		*/
		virtual void openScreenShare( int32& left, int32& top, int32& right, int32& bottom, uint32& fps ) = 0;
		/**
		@brief ��Ļ���������,��̬�޸���Ļ���������
		@param [in] left/top/right/bottom ��Ҫ������Ļ�������������Ͻ�����(left, top)�����½�����(right, bottom)����������Ļ�����Ͻ�Ϊԭ�㡣
		@return ���������NO_ERR��ʾ�޴���
		@remark ����Ĳ������ܻᾭ��sdk�ڲ�ϸ΢�ĵ�������ͨ�����÷�ʽ���ظ������ߣ�ʵ�ʵķ��������Դ��ص�ֵΪ׼;
		@note �˽ӿ�ֻ���ڴ���ָ���������Ļ����ʱ����Ч,����״̬�½��᷵��ERR_WRONG_STATE����;
		*/
		virtual int changeScreenShareSize( int32& left, int32& top, int32& right, int32& bottom ) = 0;
		/**
		@brief �ر���Ļ����
		@return ���������NO_ERR��ʾ�޴���
		@remark ָ�����ڵ���Ļ�����ָ���������Ļ�������ô˽ӿ����ر�.
		*/
		virtual void closeScreenShare() = 0;

		/**
		@brief ��ϵͳ�����ɼ���
		@details �ɼ�ϵͳ������
		@remark �ļ����ź�ϵͳ�����ɼ���Ӧ��ͬʱ�򿪣������ļ����ŵ������ֻᱻϵͳ�����ɼ�����������������;
		*/
		virtual void openSystemVoiceInput() = 0;
		/**
		@brief �ر�ϵͳ�����ɼ���
		*/
		virtual void closeSystemVoiceInput() = 0;
		/**
		@brief ����ϵͳ�����ɼ���������
		@param [in] value ����Ŀ������,ȡֵ��Χ[0,100].
		@return ���������NO_ERR��ʾ�޴���;
		@note ֻ�д���ϵͳ�����ɼ����ܽ�������,���򷵻�ERR_WRONG_STATE;
		*/
		virtual int	setSystemVoiceInputVolume( uint32 value ) = 0;
		/**
		@brief ��ȡϵͳ�����ɼ�������
		@return ����ϵͳ�����ɼ�����,δ���򷵻�0;
		*/
		virtual uint32 getSystemVoiceInputVolume() = 0;

		/**
		@brief ���ļ����š�
		@details ��ʼ���ű�����Ƶ\��Ƶ�ļ��������ļ�ǰ������ȵ���isValidMediaFile()����ļ��Ŀ����ԡ�
		@param [in] szMediaFile �ļ�·����
		@remark
		1��֧�ֵ��ļ�����:<br/>
		*.aac,*.ac3,*.amr,*.ape,*.mp3,*.flac,*.midi,*.wav,*.wma,*.ogg,*.amv,
		*.mkv,*.mod,*.mts,*.ogm,*.f4v,*.flv,*.hlv,*.asf,*.avi,*.wm,*.wmp,*.wmv,
		*.ram,*.rm,*.rmvb,*.rpm,*.rt,*.smi,*.dat,*.m1v,*.m2p,*.m2t,*.m2ts,*.m2v,
		*.mp2v, *.tp,*.tpr,*.ts,*.m4b,*.m4p,*.m4v,*.mp4,*.mpeg4,*.3g2,*.3gp,*.3gp2,
		*.3gpp,*.mov,*.pva,*.dat,*.m1v,*.m2p,*.m2t,*.m2ts,*.m2v,*.mp2v,*.pss,*.pva,
		*.ifo,*.vob,*.divx,*.evo,*.ivm,*.mkv,*.mod,*.mts,*.ogm,*.scm,*.tod,*.vp6,*.webm,*.xlmv��<br/>
		2��Ŀǰsdk��Դ���640*480����Ƶ�ü���640*480;<br/>
		3���ļ����ź�ϵͳ�����ɼ���Ӧ��ͬʱ�򿪣������ļ����ŵ������ֻᱻϵͳ�����ɼ�����������������;
		@note
		��Ļ����Ͳ�Ƭ���ܶ���ͨ����·�����䣬������Ļ����Ͳ�Ƭ����ʹ��;
		��·�����Լ�ռ�ã��豸�����ص��У����ش�����AV_ERR_EXCLUSIVE_OPERATION(�������github�ϵĴ������);
		��������������Առ�ã��豸�����ص��У����ش�����AV_ERR_RESOURCE_IS_OCCUPIED(�������github�ϵĴ������);
		*/
		virtual void openPlayMediaFile( const String& szMediaFile ) = 0;
		/**
		@brief �ر��ļ����š�
		*/
		virtual void closePlayMediaFile() = 0;
		/**
		@brief ��ͷ�����ļ���
		@return ���������NO_ERR��ʾ�޴���
		@note ֻ���ڴ��ڲ���״̬��(E_PlayMediaFilePlaying)���˽ӿڲ���Ч�����򷵻�ERR_WRONG_STATE;
		*/
		virtual int restartMediaFile() = 0;
		/**
		@brief ��ͣ�����ļ���
		@return ���������NO_ERR��ʾ�޴���
		*/
		virtual int pausePlayMediaFile() = 0;
		/**
		@brief �ָ������ļ���
		@return ���������NO_ERR��ʾ�޴���
		*/
		virtual int	resumePlayMediaFile() = 0;
		/**
		@brief ���ò����ļ����ȡ�
		@param [in] n64Pos ����λ��(��λ: ��)
		@return ���������NO_ERR��ʾ�޴���
		*/
		virtual int setPlayMediaFilePos(const int64& n64Pos) = 0;
		/**
		@brief ��ȡ�����ļ����ȡ�
		@param [out] n64Pos ��ǰ����λ��(��λ: ��)
		@param [out] n64MaxPos ��ǰ�������ļ����ܳ���(��λ: ��)
		@return ���������NO_ERR��ʾ�޴���
		*/
		virtual int getPlayMediaFilePos(int64& n64Pos, int64& n64MaxPos) = 0;
		/**
		@brief �ж��ļ��Ƿ�����ڲ��š�
		@param [in] szMediaFile Ҫ������Ƶ�ļ�.
		@return �Ƿ����;����ļ������ڣ�Ҳ�᷵��false;
		*/
		virtual bool isValidMediaFile(const String& szMediaFile) = 0;

		/**
		@brief ��ȡ��ǰ����ͷ״̬
		@return true:�� false���ر�
		*/
		virtual bool getCurCameraState() = 0;
		/**
		@brief ��ȡ�Զ���ɼ�״̬��
		@return true:�� false���ر�
		*/
		virtual bool getExternalCaptureState() = 0;
		/**
		@brief ��ȡ��ǰ��˷�״̬
		@return true:�� false���ر�
		*/
		virtual bool getCurMicState() = 0;
		/**
		@brief ��ȡ��ǰ������״̬
		@return true:�� false���ر�
		*/
		virtual bool getCurPlayerState() = 0;
		/**
		@brief ��ȡ��ǰ��Ļ����״̬
		@return ��ǰ��Ļ����״̬
		*/
		virtual E_ScreenShareState getScreenShareState() = 0;
		/**
		@brief ��ȡ��ǰ�ļ�����״̬��
		@return ��ǰ�ļ�����״̬.
		*/
		virtual E_PlayMediaFileState getPlayMediaFileState() = 0;
		/**
		@brief ��ȡ��ǰϵͳ�����ɼ�״̬
		@return true:�� false���ر�
		*/
		virtual bool getCurSystemVoiceInputState() = 0;

	};

	/**
	@brief ��ȡiLive��ָ��
	@return iLive��ָ��
	*/
	extern "C" iLiveAPI iLive* GetILive();
}
#endif //iLive_h_