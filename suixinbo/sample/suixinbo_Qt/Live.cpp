#include "stdafx.h"
#include "Live.h"

Live::Live( QWidget * parent /*= 0*/, Qt::WindowFlags f /*= 0*/ )
	:QDialog(parent, f)
{
	m_ui.setupUi(this);

	m_userType =  E_RoomUserInvalid;

	m_pLocalCameraRender = new VideoRender(this);
	m_pScreenShareRender = new VideoRender(this);
	m_ui.layoutLocalVideo->addWidget(m_pLocalCameraRender);
	m_ui.layoutScreenShare->addWidget(m_pScreenShareRender);
	connect( m_pLocalCameraRender, SIGNAL(applyFullScreen(VideoRender*)), this, SLOT(OnVideoRenderFullScreen(VideoRender*)) );
	connect( m_pLocalCameraRender, SIGNAL(exitFullScreen(VideoRender*)), this, SLOT(OnExitVideoRenderFullScreen(VideoRender*)) );
	connect( m_pScreenShareRender, SIGNAL(applyFullScreen(VideoRender*)), this, SLOT(OnVideoRenderFullScreen(VideoRender*)) );
	connect( m_pScreenShareRender, SIGNAL(exitFullScreen(VideoRender*)), this, SLOT(OnExitVideoRenderFullScreen(VideoRender*)) );

	for(int i=0; i<MaxVideoRender; ++i)
	{
		m_arrRemoteIdentifiers.push_back("");
		m_pRemoteVideoRenders[i] = new VideoRender(this);	
		m_bRemoteVideoRenderFrees[i] = true;
		connect( m_pRemoteVideoRenders[i], SIGNAL(applyFullScreen(VideoRender*)), this, SLOT(OnVideoRenderFullScreen(VideoRender*)) );
		connect( m_pRemoteVideoRenders[i], SIGNAL(exitFullScreen(VideoRender*)), this, SLOT(OnExitVideoRenderFullScreen(VideoRender*)) );
	}
	m_ui.layoutRemoteVideo0->addWidget(m_pRemoteVideoRenders[0]);
	m_ui.layoutRemoteVideo1->addWidget(m_pRemoteVideoRenders[1]);
	m_ui.layoutRemoteVideo2->addWidget(m_pRemoteVideoRenders[2]);

	m_x0 = 0;
	m_y0 = 0;
	m_fps = 10;
	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect screenRect = desktopWidget->screenGeometry();
	m_x1 = screenRect.width();
	m_y1 = screenRect.height();
	m_ui.sbX0->setValue(m_x0);
	m_ui.sbY0->setValue(m_y0);
	m_ui.sbX1->setValue(m_x1);
	m_ui.sbY1->setValue(m_y1);
	m_ui.sbFPS->setValue(m_fps);

	m_nRoomSize = 0;

	m_pTimer = new QTimer(this);
	m_pDelayUpdateTimer = new QTimer(this);
	m_pFillFrameTimer = new QTimer(this);

	m_nCurSelectedMember = -1;

	m_pMenuInviteInteract = new QMenu(this);
	QAction* pActInviteInteract = new QAction( QString::fromLocal8Bit("����"), m_pMenuInviteInteract );
	m_pMenuInviteInteract->addAction(pActInviteInteract);
	m_pMenuCancelInteract = new QMenu(this);
	QAction* pActCancelInteract = new QAction( QString::fromLocal8Bit("�Ͽ�"), m_pMenuInviteInteract );
	m_pMenuCancelInteract->addAction(pActCancelInteract);

	m_ui.cbRecordDataType->addItem( FromBits("��·(����ͷ/�Զ���ɼ�)"), QVariant(E_RecordCamera) );
	m_ui.cbRecordDataType->addItem( FromBits("��·(��Ļ����)"), QVariant(E_RecordScreen) );
	m_ui.cbRecordDataType->setCurrentIndex(0);

	m_ui.cbPushDataType->addItem( FromBits("��·(����ͷ/�Զ���ɼ�)"), QVariant(E_PushCamera) );
	m_ui.cbPushDataType->addItem( FromBits("��·(��Ļ����)"), QVariant(E_PushScreen) );
	m_ui.cbPushDataType->setCurrentIndex(0);

	m_ui.cbPushEncodeType->addItem(FromBits("HLS"), QVariant(HLS) );
	m_ui.cbPushEncodeType->addItem(FromBits("RTMP"),QVariant(RTMP) );
	m_ui.cbPushEncodeType->setCurrentIndex(0);

	m_channelId = 0;

	connect( m_ui.btnOpenCamera, SIGNAL(clicked()), this, SLOT(OnBtnOpenCamera()) );
	connect( m_ui.btnCloseCamera, SIGNAL(clicked()), this, SLOT(OnBtnCloseCamera()) );
	connect( m_ui.btnOpenExternalCapture, SIGNAL(clicked()), this, SLOT(OnBtnOpenExternalCapture()) );
	connect( m_ui.btnCloseExternalCapture, SIGNAL(clicked()), this, SLOT(OnBtnCloseExternalCapture()) );
	connect( m_ui.btnOpenMic, SIGNAL(clicked()), this, SLOT(OnBtnOpenMic()) );
	connect( m_ui.btnCloseMic, SIGNAL(clicked()), this, SLOT(OnBtnCloseMic()) );
	connect( m_ui.btnOpenPlayer, SIGNAL(clicked()), this, SLOT(OnBtnOpenPlayer()) );
	connect( m_ui.btnClosePlayer, SIGNAL(clicked()), this, SLOT(OnBtnClosePlayer()) );
	connect( m_ui.btnOpenScreenShareArea, SIGNAL(clicked()), this, SLOT(OnBtnOpenScreenShareArea()) );
	connect( m_ui.btnOpenScreenShareWnd, SIGNAL(clicked()), this, SLOT(OnBtnOpenScreenShareWnd()) );
	connect( m_ui.btnUpdateScreenShare, SIGNAL(clicked()), this, SLOT(OnBtnUpdateScreenShare()) );
	connect( m_ui.btnCloseScreenShare, SIGNAL(clicked()), this, SLOT(OnBtnCloseScreenShare()) );
	connect( m_ui.btnSendGroupMsg, SIGNAL(clicked()), this, SLOT(OnBtnSendGroupMsg()) );
	connect( m_ui.btnStartRecord, SIGNAL(clicked()), this, SLOT(OnBtnStartRecord()) );
	connect( m_ui.btnStopRecord, SIGNAL(clicked()), this, SLOT(OnBtnStopRecord()) );
	connect( m_ui.btnStartPushStream, SIGNAL(clicked()), this, SLOT(OnBtnStartPushStream()) );
	connect( m_ui.btnStopPushStream, SIGNAL(clicked()), this, SLOT(OnBtnStopPushStream()) );
	connect( m_ui.btnPraise, SIGNAL(clicked()), this, SLOT(OnBtnPraise()) );
	connect( m_ui.hsPlayerVol, SIGNAL(valueChanged(int)), this, SLOT(OnHsPlayerVol(int)) );
	connect( m_ui.sbPlayerVol, SIGNAL(valueChanged(int)), this, SLOT(OnSbPlayerVol(int)) );
	connect( m_ui.hsMicVol, SIGNAL(valueChanged(int)), this, SLOT(OnHsMicVol(int)) );
	connect( m_ui.sbMicVol, SIGNAL(valueChanged(int)), this, SLOT(OnSbMicVol(int)) );
	connect( m_ui.vsSkinSmooth, SIGNAL(valueChanged(int)), this, SLOT(OnVsSkinSmoothChanged(int)) );
	connect( m_ui.sbSkinSmooth, SIGNAL(valueChanged(int)), this, SLOT(OnSbSkinSmoothChanged(int)) );
	connect( m_ui.vsSkinWhite, SIGNAL(valueChanged(int)), this, SLOT(OnVsSkinWhiteChanged(int)) );
	connect( m_ui.sbSkinWhite, SIGNAL(valueChanged(int)), this, SLOT(OnSbSkinWhiteChanged(int)) );
	connect( m_pTimer, SIGNAL(timeout()), this, SLOT(OnHeartBeatTimer()) );
	connect( m_pDelayUpdateTimer, SIGNAL(timeout()), this, SLOT(OnDelayUpdateTimer()) );
	connect( m_pFillFrameTimer, SIGNAL(timeout()), this, SLOT(OnFillFrameTimer()) );
	connect( pActInviteInteract, SIGNAL(triggered()), this, SLOT(OnActInviteInteract()) );
	connect( pActCancelInteract, SIGNAL(triggered()), this, SLOT(OnActCancelInteract()) );
}

void Live::setRoomID( int roomID )
{
	m_ui.sbRoomID->setValue(roomID);
}

void Live::setRoomUserType( E_RoomUserType userType )
{
	m_userType = userType;
	m_ui.SkinGB->setVisible(false);
	m_ui.btnOpenPlayer->setEnabled(true);
	m_ui.btnClosePlayer->setEnabled(false);
	m_ui.cameraGB->setEnabled(true);
	m_ui.externalCaptureGB->setEnabled(true);
	updatePlayerVol();
	updateMicVol();
	switch(m_userType)
	{
	case E_RoomUserCreator:
		{
			m_ui.cameraGB->setVisible(true);
			m_ui.btnOpenCamera->setEnabled(true);
			m_ui.btnCloseCamera->setEnabled(false);
			updateCameraList();

			m_ui.externalCaptureGB->setVisible(true);
			m_ui.btnOpenExternalCapture->setEnabled(true);
			m_ui.btnCloseExternalCapture->setEnabled(false);

			m_ui.microphoneGB->setVisible(true);
			m_ui.btnOpenMic->setEnabled(true);
			m_ui.btnCloseMic->setEnabled(false);

			m_ui.screenShareGB->setVisible(true);
			m_ui.sbFPS->setEnabled(true);
			m_ui.btnOpenScreenShareArea->setEnabled(true);
			m_ui.btnUpdateScreenShare->setEnabled(false);
			m_ui.btnCloseScreenShare->setEnabled(false);

			m_ui.recordGB->setVisible(true);
			m_ui.pushStreamGB->setVisible(true);
			updatePushAndRecordStateUI();

			m_ui.lbPraiseNum->setVisible(true);
			m_ui.btnPraise->setVisible(false);

			this->setWindowTitle( QString::fromLocal8Bit("����") );
			break;
		}
	case E_RoomUserJoiner:
		{
			m_ui.cameraGB->setVisible(true);
			m_ui.btnOpenCamera->setEnabled(true);
			m_ui.btnCloseCamera->setEnabled(false);
			updateCameraList();

			m_ui.externalCaptureGB->setVisible(true);
			m_ui.btnOpenExternalCapture->setEnabled(true);
			m_ui.btnCloseExternalCapture->setEnabled(false);

			m_ui.microphoneGB->setVisible(true);
			m_ui.btnOpenMic->setEnabled(true);
			m_ui.btnCloseMic->setEnabled(false);

			m_ui.screenShareGB->setVisible(true);
			m_ui.sbFPS->setEnabled(true);
			m_ui.btnOpenScreenShareArea->setEnabled(true);
			m_ui.btnUpdateScreenShare->setEnabled(false);
			m_ui.btnCloseScreenShare->setEnabled(false);

			m_ui.recordGB->setVisible(false);
			m_ui.pushStreamGB->setVisible(false);

			m_ui.lbPraiseNum->setVisible(false);
			m_ui.btnPraise->setVisible(true);

			this->setWindowTitle( QString::fromLocal8Bit("������") );
			break;
		}
	case E_RoomUserWatcher:
		{
			m_ui.cameraGB->setVisible(false);
			m_ui.externalCaptureGB->setVisible(false);
			m_ui.microphoneGB->setVisible(false);
			m_ui.screenShareGB->setVisible(false);
			this->setWindowTitle( QString::fromLocal8Bit("����") );
			m_ui.recordGB->setVisible(false);
			m_ui.pushStreamGB->setVisible(false);
			m_ui.lbPraiseNum->setVisible(false);
			m_ui.btnPraise->setVisible(true);
			break;
		}
	}
}

void Live::ChangeRoomUserType()
{
	if (m_userType==E_RoomUserWatcher)
	{
		OnAcceptInteract();
	}
	else if(m_userType==E_RoomUserJoiner)
	{
		OnExitInteract();
	}
}

void Live::updatePushAndRecordStateUI()
{
	if ( GetILive()->getCurCameraState() || GetILive()->getExternalCaptureState() || GetILive()->getScreenShareState() )
	{
		m_ui.pushStreamGB->setEnabled(true);
		m_ui.recordGB->setEnabled(true);
	}
	else
	{
		if ( isRecording )
		{
			OnBtnStopRecord();
		}
		if ( isPushing )
		{
			OnBtnStopPushStream();
		}
		m_ui.pushStreamGB->setEnabled(false);
		m_ui.recordGB->setEnabled(false);
		return;
	}

	if ( isRecording )//¼����
	{
		m_ui.btnStartRecord->setEnabled(false);
		m_ui.btnStopRecord->setEnabled(true);
		m_ui.cbRecordDataType->setEnabled(false);
	}
	else
	{
		m_ui.btnStartRecord->setEnabled(true);
		m_ui.btnStopRecord->setEnabled(false);
		m_ui.cbRecordDataType->setEnabled(true);
	}

	if( isPushing )//������
	{
		m_ui.btnStartPushStream->setEnabled(false);
		m_ui.btnStopPushStream->setEnabled(true);
		m_ui.cbPushDataType->setEnabled(false);
		m_ui.cbPushEncodeType->setEnabled(false);
		QString szUrl;
		for (std::list<LiveUrl>::iterator iter = m_pushUrls.begin(); iter != m_pushUrls.end(); ++iter)
		{
			szUrl += QString::fromStdString( iter->url.c_str() ) + "\n";
		}
		m_ui.tePushStreamUrl->setPlainText(szUrl);
	}
	else
	{
		m_ui.btnStartPushStream->setEnabled(true);
		m_ui.btnStopPushStream->setEnabled(false);
		m_ui.cbPushDataType->setEnabled(true);
		m_ui.cbPushEncodeType->setEnabled(true);
		m_ui.tePushStreamUrl->setPlainText("");
	}
}

void Live::dealMessage( const Message& message )
{
	std::string szSender = message.sender.c_str();	
	for (size_t i = 0; i < message.elems.size(); ++i)
	{
		MessageElem *pElem = message.elems[i];
		switch( pElem->type )
		{
		case TEXT:
			{
				QString szShow = QString::fromStdString( szSender + ": " );
				MessageTextElem *elem = static_cast<MessageTextElem*>(pElem);
				addMsgLab( szShow + elem->content.c_str() );
				break;
			}
		case CUSTOM:
			{
				MessageCustomElem *elem = static_cast<MessageCustomElem*>(pElem);
				std::string szExt = elem->ext.c_str();
				//if (szExt==LiveNoti) //��ǰ�汾�ݲ����ô�������,������ƽ̨һ������
				{
					std::string szDate = elem->data.c_str();
					parseCusMessage(szSender, szDate);
				}
				break;
			}
		default:
			break;
		}
	}
}

void Live::parseCusMessage( const std::string& sender, std::string msg )
{
	QString qmsg = QString::fromStdString(msg);
	QJsonDocument doc = QJsonDocument::fromJson( qmsg.toLocal8Bit() );
	if (doc.isObject())
	{
		QJsonObject obj = doc.object();
		QVariantMap varmap = obj.toVariantMap();
		int nUserAction = AVIMCMD_None;
		QString szActionParam;
		if ( varmap.contains("userAction") )
		{
			nUserAction = varmap.value("userAction").toInt();
		}
		if ( varmap.contains("actionParam") )
		{
			szActionParam = varmap.value("actionParam").toString();
		}
		dealCusMessage( sender, nUserAction, szActionParam);
	}
}

void Live::dealCusMessage( const std::string& sender, int nUserAction, QString szActionParam )
{
	switch(nUserAction)
	{
	case AVIMCMD_Multi_Host_Invite: //�����յ���������
		{
			if ( sender != g_pMainWindow->getCurRoomInfo().szId.toStdString() )//�����·�����������������
			{
				break;
			}
			QMessageBox::StandardButton ret = QMessageBox::question(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("���������������Ƿ����?") );
			if ( ret == QMessageBox::Yes )
			{
				acceptInteract();
			}
			else
			{
				refuseInteract();
			}
			break;
		}
	case AVIMCMD_Multi_CancelInteract: //�����յ���������
		{
			if ( m_userType==E_RoomUserJoiner && szActionParam==g_pMainWindow->getUserId() ) //�����������������
			{
				exitInteract();
			}
			else
			{
				updateLater();
			}
			break;
		}
	case AVIMCMD_Multi_Interact_Join: //�����յ����ڽ�����������Ļظ�
		{
			sxbRoomIdList(); //���������б�
			break;
		}
	case AVIMCMD_Multi_Interact_Refuse://�����յ����ھܾ���������Ļظ�
		{
			ShowTips( FromBits("��ʾ"), szActionParam+FromBits("�ܾ��������������."), this);
			break;
		}
	case AVIMCMD_EnterLive:
		{
			int i;
			for (i=0; i<m_roomMemberList.size(); ++i)
			{
				if (m_roomMemberList[i].szID==szActionParam)
				{
					break;
				}
			}
			if ( i==m_roomMemberList.size() )
			{
				RoomMember roomMember;
				roomMember.szID = szActionParam;
				roomMember.userType = E_RoomUserWatcher;
				m_roomMemberList.push_back(roomMember);
				m_nRoomSize++;
				updateMemberList();
			}
			addMsgLab( QString::fromStdString(sender)+FromBits("���뷿��") );
			break;
		}
	case AVIMCMD_ExitLive:
		{
			close();
			ShowTips( FromBits("�����˳�����"), FromBits("�����Ѿ��˳�����."), g_pMainWindow );
			break;
		}
	case AVIMCMD_Praise:
		{
			if (m_userType==E_RoomUserCreator)
			{
				g_pMainWindow->increasePraise();
				m_ui.lbPraiseNum->setText( FromBits("������: ")+QString::number(g_pMainWindow->getCurRoomInfo().info.thumbup) );
			}
			addMsgLab( szActionParam+FromBits("����+1") );
			break;
		}
	default:
		break;
	}
}

void Live::startTimer()
{
	sxbRoomIdList();
	m_pTimer->start(10000); //���Ĳ���̨Ҫ��10���ϱ�һ������
}

void Live::stopTimer()
{
	m_pTimer->stop();
}

void Live::updateLater(int msec)
{
	m_pDelayUpdateTimer->start(msec);
}

void Live::OnMemStatusChange( E_EndpointEventId event_id, const Vector<String> &ids, void* data )
{
	Live* pLive = reinterpret_cast<Live*>(data);
	switch(event_id)
	{
	case EVENT_ID_ENDPOINT_NO_CAMERA_VIDEO:
		{
			std::vector<std::string> list;
			for (auto i = ids.begin(); i != ids.end(); ++i)
			{
				list.push_back( std::string(i->c_str()) );
			}
			pLive->freeCameraVideoRenders(list);
			break;
		}
	case EVENT_ID_ENDPOINT_NO_SCREEN_VIDEO:
		{
			pLive->freeScreenVideoRender();
			break;
		}
	default:
		break;
	}
}

void Live::OnRoomDisconnect( int reason, const char *errorinfo, void* data )
{
	
}

void Live::OnLocalVideo( const LiveVideoFrame* video_frame, void* custom_data )
{
	Live* pLive = reinterpret_cast<Live*>(custom_data);

	if(video_frame->desc.srcType == VIDEO_SRC_TYPE_SCREEN)
	{
		pLive->m_pScreenShareRender->DoRender(video_frame);
	}
	else if (video_frame->desc.srcType == VIDEO_SRC_TYPE_CAMERA)
	{
		pLive->m_pLocalCameraRender->DoRender(video_frame);
	}
}

void Live::OnRemoteVideo( const LiveVideoFrame* video_frame, void* custom_data )
{
	Live* pLive = reinterpret_cast<Live*>(custom_data);
	if (video_frame->desc.srcType == VIDEO_SRC_TYPE_SCREEN)
	{
		pLive->m_pScreenShareRender->DoRender(video_frame);
	}
	else if(video_frame->desc.srcType == VIDEO_SRC_TYPE_CAMERA)
	{
		VideoRender* pRender = pLive->getVideoRender(video_frame->identifier.c_str());
		if (pRender)
		{
			pRender->DoRender(video_frame);
		}
		else
		{
			//iLiveLog_e("suixinbo", "Render is not enough.");
		}
	}
}

void Live::OnMessage( const Message& msg, void* data )
{
	Live* pThis = reinterpret_cast<Live*>(data);
	if ( pThis->isVisible() )
	{
		pThis->dealMessage(msg);
	}
}

void Live::OnBtnOpenCamera()
{
	if (m_cameraList.size()==0)
	{
		ShowErrorTips( FromBits("�޿��õ�����ͷ."), this );
		return;
	}
	m_ui.btnOpenCamera->setEnabled(false);
	int ndx = m_ui.cbCamera->currentIndex();
	int nRet = GetILive()->openCamera(m_cameraList[ndx].first.c_str());
	if (nRet==NO_ERR)
	{
		m_ui.SkinGB->setVisible(true);
		m_ui.btnCloseCamera->setEnabled(true);
		m_ui.externalCaptureGB->setEnabled(false);
		updatePushAndRecordStateUI();
	}
	else
	{
		m_ui.btnOpenCamera->setEnabled(true);
		ShowCodeErrorTips( nRet, "Open Camera Failed.", this );
	}
}

void Live::OnBtnCloseCamera()
{
	m_ui.btnCloseCamera->setEnabled(false);
	int nRet = GetILive()->closeCamera();
	if (nRet==0)
	{
		m_ui.SkinGB->setVisible(false);
		m_ui.btnOpenCamera->setEnabled(true);
		m_ui.externalCaptureGB->setEnabled(true);
		m_pLocalCameraRender->update();
		updatePushAndRecordStateUI();
	}
	else
	{
		m_ui.btnCloseCamera->setEnabled(true);
		ShowErrorTips( "Close Camera Failed.", this );
	}
}

void Live::OnBtnOpenExternalCapture()
{
	m_ui.btnOpenExternalCapture->setEnabled(false);
	m_ui.btnCloseExternalCapture->setEnabled(true);
	int nRet = GetILive()->openExternalCapture();
	if (nRet == NO_ERR )
	{
		m_pFillFrameTimer->start(66); // ֡��1000/66Լ����15
		m_ui.cameraGB->setEnabled(false);
		updatePushAndRecordStateUI();
	}
	else
	{
		m_ui.btnOpenExternalCapture->setEnabled(true);
		m_ui.btnCloseExternalCapture->setEnabled(false);
		ShowCodeErrorTips(nRet, FromBits("���Զ���ɼ�ʧ��"), this );
	}
	return;
}

void Live::OnBtnCloseExternalCapture()
{
	m_ui.btnOpenExternalCapture->setEnabled(true);
	m_ui.btnCloseExternalCapture->setEnabled(false);
	int nRet = GetILive()->closeExternalCapture();
	if (nRet == NO_ERR )
	{
		m_pFillFrameTimer->stop();
		m_pLocalCameraRender->update();
		m_ui.cameraGB->setEnabled(true);
		updatePushAndRecordStateUI();
	}
	else
	{
		m_ui.btnOpenExternalCapture->setEnabled(false);
		m_ui.btnCloseExternalCapture->setEnabled(true);
		ShowCodeErrorTips(nRet, FromBits("�ر��Զ���ɼ�ʧ��"), this );
	}
	return;
}

void Live::OnBtnOpenMic()
{
	m_ui.btnOpenMic->setEnabled(false);
	
	Vector< Pair<String/*id*/, String/*name*/> > micList;
	int nRet = GetILive()->getMicList(micList);
	if (nRet != NO_ERR)
	{
		m_ui.btnOpenMic->setEnabled(true);
		ShowCodeErrorTips(nRet, "get Mic List Failed.", this );
		return;
	}
	nRet = GetILive()->openMic(micList[0].first);

	if ( nRet != NO_ERR)
	{
		m_ui.btnOpenMic->setEnabled(true);
		ShowCodeErrorTips(nRet, "Open Mic Failed.", this );
		return;
	}
	m_ui.btnCloseMic->setEnabled(true);
	updateMicVol();
}

void Live::OnBtnCloseMic()
{
	m_ui.btnCloseMic->setEnabled(false);
	int nRet = GetILive()->closeMic();
	if (nRet==0)
	{
		m_ui.btnOpenMic->setEnabled(true);
		updateMicVol();
	}
	else
	{
		m_ui.btnCloseMic->setEnabled(true);
		ShowErrorTips( "Close Mic Failed.", this );
	}
}

void Live::OnBtnOpenPlayer()
{
	m_ui.btnOpenPlayer->setEnabled(false);
	Vector< Pair<String, String> > playerList;
	int nRet = GetILive()->getPlayerList(playerList);
	if (nRet!=NO_ERR)
	{
		ShowCodeErrorTips(nRet, "Get Player List Failed.", this );
		m_ui.btnOpenPlayer->setEnabled(true);
		return;
	}
	String szPlayerID = playerList[0].first;
	nRet = GetILive()->openPlayer(String(szPlayerID.c_str()));
	if (nRet!=NO_ERR)
	{
		ShowCodeErrorTips(nRet, "Open Player Failed.", this );
		m_ui.btnOpenPlayer->setEnabled(true);
		return;
	}
	m_ui.btnClosePlayer->setEnabled(true);
	updatePlayerVol();
}

void Live::OnBtnClosePlayer()
{
	m_ui.btnClosePlayer->setEnabled(false);
	int nRet = GetILive()->closePlayer();
	if (nRet==0)
	{		
		m_ui.btnOpenPlayer->setEnabled(true);
		updatePlayerVol();
	}
	else
	{
		m_ui.btnClosePlayer->setEnabled(true);
		ShowErrorTips( "Close Player Failed.", this );
	}
}

void Live::OnBtnOpenScreenShareArea()
{
	m_x0 = m_ui.sbX0->value();
	m_y0 = m_ui.sbY0->value();
	m_x1 = m_ui.sbX1->value();
	m_y1 = m_ui.sbY1->value();
	m_fps= m_ui.sbFPS->value();
	int nRet = GetILive()->openScreenShare(m_x0, m_y0, m_x1, m_y1, m_fps);
	if (nRet==0)
	{
		updatePushAndRecordStateUI();
		updateScreenShareUI();
	}
	else
	{
		if (nRet==1008)
		{
			ShowErrorTips( FromBits("������ֻ����һ���û�����Ļ����"), this );
		}
		else
		{
			ShowCodeErrorTips( nRet, "Open Screen Share Failed.", this );
		}
	}
}

void Live::OnBtnOpenScreenShareWnd()
{
	m_fps= m_ui.sbFPS->value();

	Vector< Pair<HWND/*id*/, String/*name*/> > wndList;
	int nRet = GetILive()->getWndList(wndList);

	if (nRet != NO_ERR)
	{
		if (nRet==1301)//AV_ERR_DEVICE_NOT_EXIST û�пɹ�����Ĵ���
		{
			ShowCodeErrorTips( nRet, FromBits("û�пɹ�����Ĵ���."), this );
		}
		else
		{
			ShowCodeErrorTips( nRet, "get window list failed.", this );
		}
		return;
	}

	nRet = GetILive()->openScreenShare( wndList[0].first, m_fps );//������ʾ�����һ�����ô���
	if (nRet==0)
	{
		updatePushAndRecordStateUI();
		updateScreenShareUI();
	}
	else
	{
		if (nRet==1008)
		{
			ShowErrorTips( FromBits("������ֻ����һ���û�����Ļ����"), this );
		}
		else
		{
			ShowCodeErrorTips( nRet, "Open Screen Share Failed.", this );
		}
	}
}

void Live::OnBtnUpdateScreenShare()
{
	m_x0 = m_ui.sbX0->value();
	m_y0 = m_ui.sbY0->value();
	m_x1 = m_ui.sbX1->value();
	m_y1 = m_ui.sbY1->value();

	int nRet = GetILive()->changeScreenShareSize( m_x0, m_y0, m_x1, m_y1 );
	if (nRet==NO_ERR)
	{
		updateScreenShareUI();
	}
	else
	{
		ShowCodeErrorTips( nRet, "changeScreenShareAreaSize failed.", this );
	}
}

void Live::OnBtnCloseScreenShare()
{
	int nRet = GetILive()->closeScreenShare();
	if (nRet==0)
	{
		m_pScreenShareRender->update();
		updateScreenShareUI();
		updatePushAndRecordStateUI();
	}
	else
	{
		updateScreenShareUI();
		ShowErrorTips( "Close Screen Share Failed.", this );
	}
}

void Live::OnBtnSendGroupMsg()
{
	QString szText = m_ui.teEditText->toPlainText();
	m_ui.teEditText->setPlainText("");
	if ( szText.isEmpty() )
	{
		return;
	}

	Message msg;
	MessageTextElem *elem = new MessageTextElem(String(szText.toStdString().c_str()));
	msg.elems.push_back(elem);
	addMsgLab( QString::fromLocal8Bit("��˵�� ") + szText );
	GetILive()->sendGroupMessage(  msg, OnSendGroupMsgSuc, OnSendGroupMsgErr, this );
}

void Live::OnBtnStartRecord()
{
	bool bClickedOK;
	m_inputRecordName = QInputDialog::getText( this, FromBits("¼���ļ���"),FromBits("������¼���ļ���"), QLineEdit::Normal, "", &bClickedOK );
	if (!bClickedOK)//�û������ȡ����ť
	{
		return;
	}
	if ( m_inputRecordName.isEmpty() )
	{
		ShowErrorTips( FromBits("¼���ļ�������Ϊ��"), this );
		return;
	}	
	//���Ĳ���̨Ҫ��¼���ļ���ͳһ��ʽ"sxb_�û�id_�û�������ļ���"
	QString fileName = "sxb_";
	fileName += g_pMainWindow->getUserId();
	fileName += "_";
	fileName += m_inputRecordName;
	
	m_recordOpt.fileName = fileName.toStdString().c_str();
	m_recordOpt.recordDataType = (E_RecordDataType)m_ui.cbRecordDataType->itemData( m_ui.cbRecordDataType->currentIndex() ).value<int>();
	GetILive()->startRecord(m_recordOpt, OnStartRecordVideoSuc, OnStartRecordVideoErr, this);
}

void Live::OnBtnStopRecord()
{
	GetILive()->stopRecord( OnStopRecordSuc, OnStopRecordVideoErr, this);
}

void Live::OnBtnStartPushStream()
{
	m_pushOpt.pushDataType = (E_PushDataType)m_ui.cbPushDataType->itemData( m_ui.cbPushDataType->currentIndex() ).value<int>();
	m_pushOpt.encode = (E_iLiveStreamEncode)m_ui.cbPushEncodeType->itemData( m_ui.cbPushEncodeType->currentIndex() ).value<int>();
	m_pushOpt.recordFileType = RecordFile_NONE;
	GetILive()->startPushStream( m_pushOpt, OnStartPushStreamSuc, OnStartPushStreamErr, this );
}

void Live::OnBtnStopPushStream()
{
	GetILive()->stopPushStream(m_channelId, OnStopPushStreamSuc, OnStopPushStreamErr, this);
}

void Live::OnBtnPraise()
{
	g_sendGroupCustomCmd( AVIMCMD_Praise, g_pMainWindow->getUserId() );
	addMsgLab( g_pMainWindow->getUserId()+FromBits("����") );
}

void Live::OnHsPlayerVol( int value )
{
	m_ui.sbPlayerVol->blockSignals(true);
	m_ui.sbPlayerVol->setValue(value);
	m_ui.sbPlayerVol->blockSignals(false);

	GetILive()->setPlayerVolume(value);
}

void Live::OnSbPlayerVol( int value )
{
	m_ui.hsPlayerVol->blockSignals(true);
	m_ui.hsPlayerVol->setValue(value);
	m_ui.hsPlayerVol->blockSignals(false);

	GetILive()->setPlayerVolume(value);
}

void Live::OnHsMicVol( int value )
{
	m_ui.sbMicVol->blockSignals(true);
	m_ui.sbMicVol->setValue(value);
	m_ui.sbMicVol->blockSignals(false);

	GetILive()->setMicVolume(value);
}

void Live::OnSbMicVol( int value )
{
	m_ui.hsMicVol->blockSignals(true);
	m_ui.hsMicVol->setValue(value);
	m_ui.hsMicVol->blockSignals(false);

	GetILive()->setMicVolume(value);
}

void Live::OnVsSkinSmoothChanged( int value )
{
	m_ui.sbSkinSmooth->blockSignals(true);
	m_ui.sbSkinSmooth->setValue(value);
	m_ui.sbSkinSmooth->blockSignals(false);
	iLiveSetSkinSmoothGrade(value);
}

void Live::OnSbSkinSmoothChanged( int value )
{
	m_ui.vsSkinSmooth->blockSignals(true);
	m_ui.vsSkinSmooth->setValue(value);
	m_ui.vsSkinSmooth->blockSignals(false);
	iLiveSetSkinSmoothGrade(value);
}

void Live::OnVsSkinWhiteChanged( int value )
{
	m_ui.sbSkinWhite->blockSignals(true);
	m_ui.sbSkinWhite->setValue(value);
	m_ui.sbSkinWhite->blockSignals(false);
	iLiveSetSkinWhitenessGrade(value);
}

void Live::OnSbSkinWhiteChanged( int value )
{
	m_ui.vsSkinWhite->blockSignals(true);
	m_ui.vsSkinWhite->setValue(value);
	m_ui.vsSkinWhite->blockSignals(false);
	iLiveSetSkinWhitenessGrade(value);
}

void Live::OnHeartBeatTimer()
{
	sxbHeartBeat();
	sxbRoomIdList();
}

void Live::OnDelayUpdateTimer()
{
	m_pDelayUpdateTimer->stop();
	this->update();
}

void Live::OnFillFrameTimer()
{
	////////////////////////////////////////////////
	//������ʾ�Զ���ɼ�����ȡһ�ű���ͼƬ��ÿһ֡�������ͼƬ��Ϊ��������
	HBITMAP hbitmap = (HBITMAP)LoadImageA(NULL, "ExternalCapture.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION );
	if (!hbitmap)
	{
		return;
	}

	BITMAP bitmap;
	GetObject(hbitmap, sizeof(BITMAP), &bitmap );

	/////////////////������ֵ�ͼƬ��start////////////////
	HDC hDC = GetDC( (HWND)(this->winId()) );
	HDC hMemDC = CreateCompatibleDC(hDC);
	SelectObject(hMemDC, hbitmap);

	char chFont[20];
	HFONT hfont = CreateFontA( 100, 0, 0, 0, 400, 0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,	DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, chFont);
	
	SelectObject(hMemDC, hfont);
	TextOutA( hMemDC, 0, 0, "�����Զ���ɼ��Ļ���", strlen("�����Զ���ɼ��Ļ���") );

	DeleteObject(hfont);
	DeleteObject(hMemDC);
	ReleaseDC( (HWND)(this->winId()), hDC );
	/////////////////������ֵ�ͼƬ��end////////////////

	LiveVideoFrame frame;
	frame.data = (uint8*)bitmap.bmBits;	
	frame.dataSize = bitmap.bmWidth * bitmap.bmHeight * 3;
	frame.desc.colorFormat = COLOR_FORMAT_RGB24;
	frame.desc.width = bitmap.bmWidth;
	frame.desc.height = bitmap.bmHeight;
	frame.desc.rotate = 0;

	int nRet = GetILive()->fillExternalCaptureFrame(frame);
	if (nRet!=NO_ERR)
	{
		m_pFillFrameTimer->stop();
		if (nRet != NO_ERR)
		{
			ShowCodeErrorTips( nRet, FromBits("�Զ���ɼ���Ƶ�������"), this );
		}
	}

	DeleteObject(hbitmap);
}

void Live::closeEvent( QCloseEvent* event )
{
	m_ui.liMsgs->clear();
	freeAllCameraVideoRender();	
	stopTimer();
	if ( m_pFillFrameTimer->isActive() )
	{
		m_pFillFrameTimer->stop();
	}
	if (m_userType==E_RoomUserCreator)//�����˳�������Ҫ�����Ĳ��������ϱ��˳�����
	{
		sendQuitRoom();
		sxbCreatorQuitRoom();
	}
	else//���ں��������ֻ��Ҫ�����Ĳ��������ϱ��Լ���ID
	{
		sxbWatcherOrJoinerQuitRoom();
	}
	g_pMainWindow->setUseable(true);

	event->accept();
}

void Live::updateCameraList()
{
	GetILive()->getCameraList(m_cameraList);
	m_ui.cbCamera->clear();
	for(int i=0; i<m_cameraList.size(); ++i)
	{
		m_ui.cbCamera->addItem( QString::fromStdString(m_cameraList[i].second.c_str()) );
	}
	m_ui.cbCamera->setCurrentIndex(0);
}

VideoRender* Live::getVideoRender( std::string szIdentifier )
{
	for(int i=0; i<MaxVideoRender; ++i)
	{
		if (m_arrRemoteIdentifiers[i]==szIdentifier)
		{
			return m_pRemoteVideoRenders[i];
		}
	}
	for(int i=0; i<MaxVideoRender; ++i)
	{
		if (m_bRemoteVideoRenderFrees[i])
		{
			m_bRemoteVideoRenderFrees[i] = false;
			m_arrRemoteIdentifiers[i] = szIdentifier;
			return m_pRemoteVideoRenders[i];
		}
	}
	return NULL;
}

void Live::freeCameraVideoRenders( std::vector<std::string> arrNeedFreeRenders )
{
	for (size_t i=0; i<arrNeedFreeRenders.size(); ++i)
	{
		for (size_t j = 0; j<m_arrRemoteIdentifiers.size(); ++j)
		{
			std::string str1 = m_arrRemoteIdentifiers[j];
			std::string str2 = arrNeedFreeRenders[i];
			if (str1 == str2)
			{
				m_arrRemoteIdentifiers[j] = "";
				m_bRemoteVideoRenderFrees[j] = true;
				m_pRemoteVideoRenders[j]->update();
			}
		}
	}
	updateLater();
}

void Live::freeAllCameraVideoRender()
{
	m_pLocalCameraRender->exitFullScreen();
	m_pScreenShareRender->exitFullScreen();
	m_pLocalCameraRender->recoverRender();
	m_pScreenShareRender->recoverRender();
	for (int i=0; i<MaxVideoRender; ++i)
	{
		m_pRemoteVideoRenders[i]->exitFullScreen();
		m_pRemoteVideoRenders[i]->recoverRender();
		m_arrRemoteIdentifiers[i] = "";
		m_bRemoteVideoRenderFrees[i] = true;
	}
}

void Live::freeScreenVideoRender()
{
	m_pScreenShareRender->update();
	updateLater();
}

void Live::addMsgLab( QString msg )
{
	m_ui.liMsgs->addItem( new QListWidgetItem(msg) );
	m_ui.liMsgs->setCurrentRow( m_ui.liMsgs->count()-1 );
}

void Live::updateMemberList()
{
	m_ui.sbTotalMemNum->setValue(m_nRoomSize);
	m_ui.liMembers->clear();
	for (int i=0; i<m_roomMemberList.size(); ++i)
	{
		RoomMember& member = m_roomMemberList[i];
		QString szShowName = member.szID;
		switch(member.userType)
		{
		case E_RoomUserJoiner:
			szShowName += QString::fromLocal8Bit("(����)");
			break;
		case E_RoomUserCreator:
			szShowName += QString::fromLocal8Bit("(����)");
			break;
		case E_RoomUserWatcher:
			break;
		}
		m_ui.liMembers->addItem( new QListWidgetItem(szShowName) );
	}
}

void Live::updateScreenShareUI()
{
	m_ui.sbX0->blockSignals(true);
	m_ui.sbY0->blockSignals(true);
	m_ui.sbX1->blockSignals(true);
	m_ui.sbY1->blockSignals(true);
	m_ui.sbFPS->blockSignals(true);
	m_ui.sbX0->setValue(m_x0);
	m_ui.sbY0->setValue(m_y0);
	m_ui.sbX1->setValue(m_x1);
	m_ui.sbY1->setValue(m_y1);
	m_ui.sbFPS->setValue(m_fps);
	m_ui.sbX0->blockSignals(false);
	m_ui.sbY0->blockSignals(false);
	m_ui.sbX1->blockSignals(false);
	m_ui.sbY1->blockSignals(false);
	m_ui.sbFPS->blockSignals(false);

	E_ScreenShareState state = GetILive()->getScreenShareState();
	switch(state)
	{
	case E_ScreenShareNone:
		{
			m_ui.sbX0->setEnabled(true);
			m_ui.sbY0->setEnabled(true);
			m_ui.sbX1->setEnabled(true);
			m_ui.sbY1->setEnabled(true);
			m_ui.sbFPS->setEnabled(true);
			m_ui.btnOpenScreenShareArea->setEnabled(true);
			m_ui.btnOpenScreenShareWnd->setEnabled(true);
			m_ui.btnUpdateScreenShare->setEnabled(false);
			m_ui.btnCloseScreenShare->setEnabled(false);
			break;
		}
	case E_ScreenShareWnd:
		{
			m_ui.sbX0->setEnabled(false);
			m_ui.sbY0->setEnabled(false);
			m_ui.sbX1->setEnabled(false);
			m_ui.sbY1->setEnabled(false);
			m_ui.sbFPS->setEnabled(false);
			m_ui.btnOpenScreenShareArea->setEnabled(false);
			m_ui.btnOpenScreenShareWnd->setEnabled(false);
			m_ui.btnUpdateScreenShare->setEnabled(false);
			m_ui.btnCloseScreenShare->setEnabled(true);
			break;
		}
	case E_ScreenShareArea:
		{
			m_ui.sbX0->setEnabled(true);
			m_ui.sbY0->setEnabled(true);
			m_ui.sbX1->setEnabled(true);
			m_ui.sbY1->setEnabled(true);
			m_ui.sbFPS->setEnabled(false);
			m_ui.btnOpenScreenShareArea->setEnabled(false);
			m_ui.btnOpenScreenShareWnd->setEnabled(false);
			m_ui.btnUpdateScreenShare->setEnabled(true);
			m_ui.btnCloseScreenShare->setEnabled(true);
			break;
		}
	default:
		{
			break;
		}
	}
}

void Live::updatePlayerVol()
{
	m_ui.sbPlayerVol->blockSignals(true);
	m_ui.hsPlayerVol->blockSignals(true);

	uint32 uVol = GetILive()->getPlayerVolume();
	m_ui.sbPlayerVol->setValue(uVol);
	m_ui.hsPlayerVol->setValue(uVol);

	m_ui.sbPlayerVol->blockSignals(false);
	m_ui.hsPlayerVol->blockSignals(false);

	if ( GetILive()->getCurPlayerState() )
	{
		m_ui.sbPlayerVol->setEnabled(true);
		m_ui.hsPlayerVol->setEnabled(true);
	}
	else
	{
		m_ui.sbPlayerVol->setEnabled(false);
		m_ui.hsPlayerVol->setEnabled(false);
	}	
}

void Live::updateMicVol()
{
	m_ui.sbMicVol->blockSignals(true);
	m_ui.hsMicVol->blockSignals(true);

	uint32 uVol = GetILive()->getMicVolume();
	m_ui.sbMicVol->setValue(uVol);
	m_ui.hsMicVol->setValue(uVol);

	m_ui.sbMicVol->blockSignals(false);
	m_ui.hsMicVol->blockSignals(false);

	if ( GetILive()->getCurMicState() )
	{
		m_ui.sbMicVol->setEnabled(true);
		m_ui.hsMicVol->setEnabled(true);
	}
	else
	{
		m_ui.sbMicVol->setEnabled(false);
		m_ui.hsMicVol->setEnabled(false);
	}
}

void Live::sendInviteInteract()
{
	g_sendC2CCustomCmd( m_roomMemberList[m_nCurSelectedMember].szID, AVIMCMD_Multi_Host_Invite, "", OnSendInviteInteractSuc, OnSendInviteInteractErr, this );
}

void Live::sendCancelInteract()
{
	g_sendGroupCustomCmd( AVIMCMD_Multi_CancelInteract, m_roomMemberList[m_nCurSelectedMember].szID );
}

void Live::OnSendInviteInteractSuc(void* data)
{
	//ShowTips( FromBits("����ɹ�"), FromBits("�ɹ��������룬�ȴ����ڽ�������."), reinterpret_cast<Live*>(data) );
}

void Live::OnSendInviteInteractErr( const int code, const char *desc, void* data )
{
	ShowCodeErrorTips(code, desc, reinterpret_cast<Live*>(data), "Send Invite Interact Error.");
}

void Live::acceptInteract()
{
	iLiveChangeRole(LiveGuest);
}

void Live::refuseInteract()
{
	//֪ͨ�����ܾ�����
	g_sendC2CCustomCmd( g_pMainWindow->getCurRoomInfo().szId, AVIMCMD_Multi_Interact_Refuse, g_pMainWindow->getUserId() );
}

void Live::OnAcceptInteract()
{
	setRoomUserType(E_RoomUserJoiner);
	OnBtnOpenCamera();
	OnBtnOpenMic();

	//��ݱ�Ϊ�����û������������ϱ��Լ���ݱ仯,��������ȡ�����Ա�б�
	sxbHeartBeat();
	sxbRoomIdList();
	//���������֪ͨ����
	g_sendC2CCustomCmd( g_pMainWindow->getCurRoomInfo().szId, AVIMCMD_Multi_Interact_Join, g_pMainWindow->getUserId() );
}

void Live::exitInteract()
{
	iLiveChangeRole(Guest);
}

void Live::OnExitInteract()
{
	if ( m_ui.btnCloseCamera->isEnabled() )
	{
		OnBtnCloseCamera();
	}
	if ( m_ui.btnCloseMic->isEnabled() )
	{
		OnBtnCloseMic();
	}
	if ( m_ui.btnCloseScreenShare->isEnabled() )
	{
		OnBtnCloseScreenShare();
	}
	setRoomUserType(E_RoomUserWatcher);
	
	//��ݱ仯�����������ϱ���ݣ����������󷿼��Ա�б�
	sxbHeartBeat();
	sxbRoomIdList();
}

void Live::sendQuitRoom()
{
	g_sendGroupCustomCmd( AVIMCMD_ExitLive, g_pMainWindow->getUserId() );
}

void Live::sxbCreatorQuitRoom()
{
	QVariantMap varmap;
	varmap.insert( "token", g_pMainWindow->getToken() );
	varmap.insert( "roomnum", g_pMainWindow->getCurRoomInfo().info.roomnum );
	varmap.insert( "type", "live" );
	SxbServerHelper::request(varmap, "live", "exitroom", OnSxbCreatorQuitRoom, this);
}

void Live::sxbWatcherOrJoinerQuitRoom()
{
	QVariantMap varmap;
	varmap.insert( "token", g_pMainWindow->getToken() );
	varmap.insert( "id", g_pMainWindow->getUserId() );
	varmap.insert( "roomnum", g_pMainWindow->getCurRoomInfo().info.roomnum );
	varmap.insert( "role", (int)m_userType );//��Ա0 ����1 �����Ա2
	varmap.insert( "operate", 1);//���뷿��0  �˳�����1
	SxbServerHelper::request(varmap, "live", "reportmemid", OnSxbWatcherOrJoinerQuitRoom, this);
}

void Live::sxbHeartBeat()
{
	QVariantMap varmap;
	varmap.insert("token", g_pMainWindow->getToken());
	varmap.insert("roomnum", g_pMainWindow->getCurRoomInfo().info.roomnum);
	varmap.insert("role", (int)m_userType); //0 ���� 1 ���� 2 �������
	if(m_userType==E_RoomUserCreator)
	{
		varmap.insert("thumbup", g_pMainWindow->getCurRoomInfo().info.thumbup);
	}
	SxbServerHelper::request(varmap, "live", "heartbeat", OnSxbHeartBeat, this);
}

void Live::sxbRoomIdList()
{
	QVariantMap varmap;
	varmap.insert( "token", g_pMainWindow->getToken() );
	varmap.insert( "roomnum", g_pMainWindow->getCurRoomInfo().info.roomnum );
	varmap.insert( "index", 0 );
	varmap.insert( "size", MaxShowMembers );
	SxbServerHelper::request(varmap, "live", "roomidlist", OnSxbRoomIdList, this);
}

void Live::sxbReportrecord()
{
	QVariantMap varmap;
	varmap.insert( "token", g_pMainWindow->getToken() );
	varmap.insert( "roomnum", g_pMainWindow->getCurRoomInfo().info.roomnum );
	varmap.insert( "uid", g_pMainWindow->getCurRoomInfo().szId );//������
	varmap.insert( "name", m_inputRecordName );//�û������¼����
	varmap.insert( "type", 0 );//Ԥ���ֶΣ�����0
	varmap.insert( "cover", "" );//TODO PC���Ĳ��ݲ�֧��ֱ�������ϴ�,������ʱ�ϴ�Ϊ�գ���������
	SxbServerHelper::request(varmap, "live", "reportrecord", OnSxbReportrecord, this);
}

void Live::OnSxbCreatorQuitRoom( int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData )
{
	Live* pLive = reinterpret_cast<Live*>(pCusData);

	if (errorCode==E_SxbOK)
	{
		pLive->iLiveQuitRoom();
	}
	else
	{
		ShowCodeErrorTips( errorCode, errorInfo, pLive, FromBits("�����˳�����ʧ��") );
	}
}

void Live::OnSxbWatcherOrJoinerQuitRoom( int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData )
{
	Live* pLive = reinterpret_cast<Live*>(pCusData);
	
	if (errorCode==E_SxbOK || errorCode==10010)//�ɹ����߷����Ѿ�������
	{
		pLive->iLiveQuitRoom();
	}
	else
	{
		ShowCodeErrorTips( errorCode, errorInfo, pLive, FromBits("�����˳�����ʧ��") );
	}
}

void Live::OnSxbHeartBeat( int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData )
{
	Live* pLive = reinterpret_cast<Live*>(pCusData);

	if (errorCode!=E_SxbOK)
	{
		//iLiveLog_e( "suixinbo", "Sui xin bo heartbeat failed: %d %s", errorCode, errorInfo.toStdString().c_str() );
	}
}

void Live::OnSxbRoomIdList( int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData )
{
	Live* pLive = reinterpret_cast<Live*>(pCusData);

	if (errorCode!=E_SxbOK)
	{
		//iLiveLog_e( "suixinbo", "Suixinbo get Room id list failed: %d %s", errorCode, errorInfo.toStdString().c_str() );
		return ;
	}

	if (datamap.contains("total"))
	{
		pLive->m_nRoomSize = datamap.value("total").toInt();
	}
	if (datamap.contains("idlist"))
	{
		pLive->m_roomMemberList.clear();
		QVariantList idlist = datamap.value("idlist").toList();
		for (int i=0; i<idlist.size(); ++i)
		{
			QVariantMap idmap = idlist[i].toMap();
			RoomMember member;
			if (idmap.contains("id"))
			{
				member.szID = idmap.value("id").toString();

			}
			if (idmap.contains("role"))
			{
				member.userType = (E_RoomUserType)idmap.value("role").toInt();
			}
			pLive->m_roomMemberList.push_back(member);
		}
		pLive->updateMemberList();
	}	
}

void Live::OnSxbReportrecord( int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData )
{
	Live* pLive = reinterpret_cast<Live*>(pCusData);

	if (errorCode!=E_SxbOK)
	{
		//iLiveLog_e( "suixinbo", "Suixinbo report record video failed: %d %s", errorCode, errorInfo.toStdString().c_str() );
		return ;
	}
}

void Live::iLiveQuitRoom()
{
	GetILive()->quitRoom(OnQuitRoomSuc, OnQuitRoomErr, this);
}

void Live::iLiveChangeRole( const std::string& szControlRole )
{
	GetILive()->changeRole(szControlRole.c_str(), OnChangeRoleSuc, OnChangeRoleErr, this);
}

int Live::iLiveSetSkinSmoothGrade( int grade )
{
	return GetILive()->setSkinSmoothGrade(grade);
}

int Live::iLiveSetSkinWhitenessGrade( int grade )
{
	return GetILive()->setSkinWhitenessGrade(grade);
}

void Live::OnQuitRoomSuc( void* data )
{
	Room roominfo = g_pMainWindow->getCurRoomInfo();
	roominfo.szId = "";
	roominfo.info.thumbup = 0;
	g_pMainWindow->setCurRoomIdfo(roominfo);
}

void Live::OnQuitRoomErr( int code, const char *desc, void* data )
{
	ShowCodeErrorTips(code, desc, reinterpret_cast<Live*>(data), "Quit iLive Room Error.");
}

void Live::OnChangeRoleSuc( void* data )
{
	reinterpret_cast<Live*>(data)->ChangeRoomUserType();
}

void Live::OnChangeRoleErr( int code, const char *desc, void* data )
{
	ShowCodeErrorTips(code, desc, reinterpret_cast<Live*>(data), "Change Role Error.");
}

void Live::OnSendGroupMsgSuc( void* data )
{

}

void Live::OnSendGroupMsgErr( int code, const char *desc, void* data )
{
	ShowCodeErrorTips(code, desc, reinterpret_cast<Live*>(data), "Send Group Message Error.");
}

void Live::OnMemberListMenu( QPoint point )
{
	if ( m_userType != E_RoomUserCreator )
	{
		return;
	}
	m_nCurSelectedMember = m_ui.liMembers->currentRow();
	if ( m_nCurSelectedMember>=0 && m_nCurSelectedMember<m_roomMemberList.size() )
	{
		RoomMember& roomMember = m_roomMemberList[m_nCurSelectedMember];
		if (roomMember.userType==E_RoomUserWatcher)
		{
			m_pMenuInviteInteract->exec( QCursor::pos() );
		}
		else if(roomMember.userType==E_RoomUserJoiner)
		{
			m_pMenuCancelInteract->exec( QCursor::pos() );
		}
	}
}

void Live::OnActInviteInteract()
{
	sendInviteInteract();
}

void Live::OnActCancelInteract()
{
	RoomMember& roomber = m_roomMemberList[m_nCurSelectedMember];
	roomber.userType = E_RoomUserWatcher;
	updateMemberList();

	sendCancelInteract();
}

void Live::OnVideoRenderFullScreen( VideoRender* pRender )
{
	pRender->recoverRender();
	pRender->enterFullScreen();
	if (m_pLocalCameraRender!=pRender)
	{
		m_pLocalCameraRender->pauseRender();
		m_pLocalCameraRender->exitFullScreen();
	}
	if (m_pScreenShareRender!=pRender)
	{
		m_pScreenShareRender->pauseRender();
		m_pScreenShareRender->exitFullScreen();
	}
	for (int i=0; i<MaxVideoRender; ++i)
	{
		if (m_pRemoteVideoRenders[i]!=pRender)
		{
			m_pRemoteVideoRenders[i]->pauseRender();
			m_pRemoteVideoRenders[i]->exitFullScreen();
		}
	}
}

void Live::OnExitVideoRenderFullScreen( VideoRender* pRender )
{
	m_pLocalCameraRender->recoverRender();
	m_pLocalCameraRender->exitFullScreen();
	m_pScreenShareRender->recoverRender();
	m_pScreenShareRender->exitFullScreen();
	for (int i=0; i<MaxVideoRender; ++i)
	{
		m_pRemoteVideoRenders[i]->recoverRender();
		m_pRemoteVideoRenders[i]->exitFullScreen();
	}
}

void Live::OnStartRecordVideoSuc( void* data )
{
	isRecording = true;
	reinterpret_cast<Live*>(data)->updatePushAndRecordStateUI();
	
}

void Live::OnStartRecordVideoErr( int code, const char *desc, void* data )
{
	ShowCodeErrorTips(code, desc, reinterpret_cast<Live*>(data), "Start Record Video Error.");
}

void Live::OnStopRecordSuc( Vector<String>& value, void* data )
{
	isRecording = false;
	Live* pLive = reinterpret_cast<Live*>(data);
	pLive->updatePushAndRecordStateUI();
	pLive->sxbReportrecord();
	
}

void Live::OnStopRecordVideoErr( int code, const char *desc, void* data )
{
	ShowCodeErrorTips(code, desc, reinterpret_cast<Live*>(data), "Stop Record Video Error.");
}

void Live::OnStartPushStreamSuc( PushStreamRsp &value, void *data )
{
	isPushing = true;
	Live* pLive = reinterpret_cast<Live*>(data);
	pLive->m_channelId = value.channelId;
	for (auto i = value.urls.begin(); i != value.urls.end(); ++i) {
		pLive->m_pushUrls.push_back(*i);
	}
	pLive->updatePushAndRecordStateUI();
}

void Live::OnStartPushStreamErr( int code, const char *desc, void* data )
{
	ShowCodeErrorTips(code, desc, reinterpret_cast<Live*>(data), "Start Push Stream Error.");
}

void Live::OnStopPushStreamSuc( void* data )
{
	isPushing = false;
	Live* pLive = reinterpret_cast<Live*>(data);
	pLive->m_channelId = 0;
	pLive->m_pushUrls.clear();
	pLive->updatePushAndRecordStateUI();
	
}

void Live::OnStopPushStreamErr( int code, const char *desc, void* data )
{
	ShowCodeErrorTips(code, desc, reinterpret_cast<Live*>(data), "Stop Push Stream Error.");
}

