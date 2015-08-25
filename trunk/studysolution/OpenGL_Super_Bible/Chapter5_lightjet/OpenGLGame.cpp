#include "OpenGLGame.h"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")



OpenGLGame::OpenGLGame( const char* szWindowTitle /*= NULL*/, GLsizei width /*= 640*/, GLsizei height /*= 480*/, GLsizei bitmode /*= 16 */ )
	: m_szTitle( szWindowTitle )
{
	m_nWidth = width;
	m_nHeight = height;
	m_nBitMode = bitmode;

	m_hRC = NULL;
	m_hDC = NULL;
	m_hWnd = NULL;
	m_hInstance = NULL;

	memset( m_vbPressKeys, 0, sizeof( m_vbPressKeys ) );
	m_bActive = true;
	m_bFullScreen = false;

	xRot = yRot = 0;
}

bool OpenGLGame::update()
{
	if ( !isActive() )						// ���򼤻��ô?
	{
		return true;
	}

	if ( isKeyPressed( VK_ESCAPE ) )				// ESC ������ô?
	{
		return false;				// ESC �����˳��ź�
	}

	// �����˳���ʱ��ˢ����Ļ
	drawGLScene();				// ���Ƴ���
	::SwapBuffers( m_hDC );			// �������� (˫����)

	if ( isKeyPressed( VK_F1 ) )					// F1��������ô?
	{
		onKeyReleased( VK_F1 );			// ���ǣ�ʹ��Ӧ��Key�����е�ֵΪ FALSE
		killGLWindow();					// ���ٵ�ǰ�Ĵ���
		m_bFullScreen = !m_bFullScreen; // �л� ȫ�� / ���� ģʽ

		// �ؽ� OpenGL ����
		if ( !createGLWindow() )
		{
			return false;				// �������δ�ܴ����������˳�
		}
	}

	return true;
}



int OpenGLGame::drawGLScene( GLvoid )
{

	GLTVector3 vNormal;	// Storeage for calculated surface normal

	// Clear the window with current clearing color
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Save the matrix state and do the rotations
	glPushMatrix();
	glRotatef( xRot, 1.0f, 0.0f, 0.0f );
	glRotatef( yRot, 0.0f, 1.0f, 0.0f );


	// Nose Cone - Points straight down
	// Set material color
	glColor3ub( 128, 128, 128 );
	glBegin( GL_TRIANGLES );
	glNormal3f( 0.0f, -1.0f, 0.0f );
	glNormal3f( 0.0f, -1.0f, 0.0f );
	glVertex3f( 0.0f, 0.0f, 60.0f );
	glVertex3f( -15.0f, 0.0f, 30.0f );
	glVertex3f( 15.0f, 0.0f, 30.0f );


	// Verticies for this panel
	{
		GLTVector3 vPoints[3] = {{ 15.0f, 0.0f,  30.0f},
			{ 0.0f,  15.0f, 30.0f},
			{ 0.0f,  0.0f,  60.0f}
		};

		// Calculate the normal for the plane
		gltGetNormalVector( vPoints[0], vPoints[1], vPoints[2], vNormal );
		glNormal3fv( vNormal );
		glVertex3fv( vPoints[0] );
		glVertex3fv( vPoints[1] );
		glVertex3fv( vPoints[2] );
	}


	{
		GLTVector3 vPoints[3] = {{ 0.0f, 0.0f, 60.0f },
			{ 0.0f, 15.0f, 30.0f },
			{ -15.0f, 0.0f, 30.0f }
		};

		gltGetNormalVector( vPoints[0], vPoints[1], vPoints[2], vNormal );
		glNormal3fv( vNormal );
		glVertex3fv( vPoints[0] );
		glVertex3fv( vPoints[1] );
		glVertex3fv( vPoints[2] );
	}


	// Body of the Plane ////////////////////////
	{
		GLTVector3 vPoints[3] = {{ -15.0f, 0.0f, 30.0f },
			{ 0.0f, 15.0f, 30.0f },
			{ 0.0f, 0.0f, -56.0f }
		};

		gltGetNormalVector( vPoints[0], vPoints[1], vPoints[2], vNormal );
		glNormal3fv( vNormal );
		glVertex3fv( vPoints[0] );
		glVertex3fv( vPoints[1] );
		glVertex3fv( vPoints[2] );
	}

	{
		GLTVector3 vPoints[3] = {{ 0.0f, 0.0f, -56.0f },
			{ 0.0f, 15.0f, 30.0f },
			{ 15.0f, 0.0f, 30.0f }
		};

		gltGetNormalVector( vPoints[0], vPoints[1], vPoints[2], vNormal );
		glNormal3fv( vNormal );
		glVertex3fv( vPoints[0] );
		glVertex3fv( vPoints[1] );
		glVertex3fv( vPoints[2] );
	}


	glNormal3f( 0.0f, -1.0f, 0.0f );
	glVertex3f( 15.0f, 0.0f, 30.0f );
	glVertex3f( -15.0f, 0.0f, 30.0f );
	glVertex3f( 0.0f, 0.0f, -56.0f );

	///////////////////////////////////////////////
	// Left wing
	// Large triangle for bottom of wing
	{
		GLTVector3 vPoints[3] = {{ 0.0f, 2.0f, 27.0f },
			{ -60.0f, 2.0f, -8.0f },
			{ 60.0f, 2.0f, -8.0f }
		};

		gltGetNormalVector( vPoints[0], vPoints[1], vPoints[2], vNormal );
		glNormal3fv( vNormal );
		glVertex3fv( vPoints[0] );
		glVertex3fv( vPoints[1] );
		glVertex3fv( vPoints[2] );
	}


	{
		GLTVector3 vPoints[3] = {{ 60.0f, 2.0f, -8.0f},
			{0.0f, 7.0f, -8.0f},
			{0.0f, 2.0f, 27.0f }
		};

		gltGetNormalVector( vPoints[0], vPoints[1], vPoints[2], vNormal );
		glNormal3fv( vNormal );
		glVertex3fv( vPoints[0] );
		glVertex3fv( vPoints[1] );
		glVertex3fv( vPoints[2] );
	}

	{
		GLTVector3 vPoints[3] = {{60.0f, 2.0f, -8.0f},
			{ -60.0f, 2.0f, -8.0f},
			{0.0f, 7.0f, -8.0f }
		};

		gltGetNormalVector( vPoints[0], vPoints[1], vPoints[2], vNormal );
		glNormal3fv( vNormal );
		glVertex3fv( vPoints[0] );
		glVertex3fv( vPoints[1] );
		glVertex3fv( vPoints[2] );
	}

	{
		GLTVector3 vPoints[3] = {{0.0f, 2.0f, 27.0f},
			{0.0f, 7.0f, -8.0f},
			{ -60.0f, 2.0f, -8.0f}
		};

		gltGetNormalVector( vPoints[0], vPoints[1], vPoints[2], vNormal );
		glNormal3fv( vNormal );
		glVertex3fv( vPoints[0] );
		glVertex3fv( vPoints[1] );
		glVertex3fv( vPoints[2] );
	}


	// Tail section///////////////////////////////
	// Bottom of back fin
	glNormal3f( 0.0f, -1.0f, 0.0f );
	glVertex3f( -30.0f, -0.50f, -57.0f );
	glVertex3f( 30.0f, -0.50f, -57.0f );
	glVertex3f( 0.0f, -0.50f, -40.0f );

	{
		GLTVector3 vPoints[3] = {{ 0.0f, -0.5f, -40.0f },
			{30.0f, -0.5f, -57.0f},
			{0.0f, 4.0f, -57.0f }
		};

		gltGetNormalVector( vPoints[0], vPoints[1], vPoints[2], vNormal );
		glNormal3fv( vNormal );
		glVertex3fv( vPoints[0] );
		glVertex3fv( vPoints[1] );
		glVertex3fv( vPoints[2] );
	}


	{
		GLTVector3 vPoints[3] = {{ 0.0f, 4.0f, -57.0f },
			{ -30.0f, -0.5f, -57.0f },
			{ 0.0f, -0.5f, -40.0f }
		};

		gltGetNormalVector( vPoints[0], vPoints[1], vPoints[2], vNormal );
		glNormal3fv( vNormal );
		glVertex3fv( vPoints[0] );
		glVertex3fv( vPoints[1] );
		glVertex3fv( vPoints[2] );
	}


	{
		GLTVector3 vPoints[3] = {{ 30.0f, -0.5f, -57.0f },
			{ -30.0f, -0.5f, -57.0f },
			{ 0.0f, 4.0f, -57.0f }
		};

		gltGetNormalVector( vPoints[0], vPoints[1], vPoints[2], vNormal );
		glNormal3fv( vNormal );
		glVertex3fv( vPoints[0] );
		glVertex3fv( vPoints[1] );
		glVertex3fv( vPoints[2] );
	}

	{
		GLTVector3 vPoints[3] = {{ 0.0f, 0.5f, -40.0f },
			{ 3.0f, 0.5f, -57.0f },
			{ 0.0f, 25.0f, -65.0f }
		};

		gltGetNormalVector( vPoints[0], vPoints[1], vPoints[2], vNormal );
		glNormal3fv( vNormal );
		glVertex3fv( vPoints[0] );
		glVertex3fv( vPoints[1] );
		glVertex3fv( vPoints[2] );
	}


	{
		GLTVector3 vPoints[3] = {{ 0.0f, 25.0f, -65.0f },
			{ -3.0f, 0.5f, -57.0f},
			{ 0.0f, 0.5f, -40.0f }
		};

		gltGetNormalVector( vPoints[0], vPoints[1], vPoints[2], vNormal );
		glNormal3fv( vNormal );
		glVertex3fv( vPoints[0] );
		glVertex3fv( vPoints[1] );
		glVertex3fv( vPoints[2] );
	}

	{
		GLTVector3 vPoints[3] = {{ 3.0f, 0.5f, -57.0f },
			{ -3.0f, 0.5f, -57.0f },
			{ 0.0f, 25.0f, -65.0f }
		};

		gltGetNormalVector( vPoints[0], vPoints[1], vPoints[2], vNormal );
		glNormal3fv( vNormal );
		glVertex3fv( vPoints[0] );
		glVertex3fv( vPoints[1] );
		glVertex3fv( vPoints[2] );
	}


	glEnd();

	// Restore the matrix state
	glPopMatrix();

	return TRUE;								//  һ�� OK
}

LRESULT CALLBACK OpenGLGame::wndProc(	HWND	hWnd,					// ���ڵľ��
                                        UINT	uMsg,					// ���ڵ���Ϣ
                                        WPARAM	wParam,					// ���ӵ���Ϣ����
                                        LPARAM	lParam )					// ���ӵ���Ϣ����
{
	OpenGLGame* pOpenGLGame = getOpenGLGame();

	switch ( uMsg )								// ���Windows��Ϣ
	{
		case WM_ACTIVATE:						// ���Ӵ��ڼ�����Ϣ
			{
				if ( !HIWORD( wParam ) )					// �����С��״̬
				{
					s_pOpenGLGame->setActive( TRUE );					// �����ڼ���״̬
				}
				else
				{
					s_pOpenGLGame->setActive( FALSE );					// �����ټ���
				}

				return 0;						// ������Ϣѭ��
			}
		case WM_SYSCOMMAND:						// ϵͳ�ж�����
			{
				switch ( wParam )						// ���ϵͳ����
				{
					case SC_SCREENSAVE:				// ����Ҫ����?
					case SC_MONITORPOWER:				// ��ʾ��Ҫ����ڵ�ģʽ?
						return 0;					// ��ֹ����
				}

				break;							// �˳�
			}
		case WM_CLOSE:							// �յ�Close��Ϣ?
			{
				PostQuitMessage( 0 );					// �����˳���Ϣ
				return 0;						// ����
			}
		case WM_KEYDOWN:						// �м�����ô?
			{
				s_pOpenGLGame->onKeyPressed( wParam ) ;					// ����ǣ���ΪTRUE
				return 0;						// ����
			}
		case WM_KEYUP:							// �м��ſ�ô?
			{
				s_pOpenGLGame->onKeyReleased( wParam ) ;						// ����ǣ���ΪFALSE
				return 0;						// ����
			}
		case WM_SIZE:							// ����OpenGL���ڴ�С
			{
				s_pOpenGLGame->resizeGLScene( LOWORD( lParam ), HIWORD( lParam ) );		// LoWord=Width,HiWord=Height
				return 0;						// ����
			}
	}

	// �� DefWindowProc��������δ��������Ϣ��
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

BOOL OpenGLGame::createGLWindow()
{
	GLuint		PixelFormat;						// �������ƥ��Ľ��
	WNDCLASS	wc;							// ������ṹ
	DWORD		dwExStyle;						// ��չ���ڷ��
	DWORD		dwStyle;						// ���ڷ��

	RECT WindowRect;							// ȡ�þ��ε����ϽǺ����½ǵ�����ֵ
	WindowRect.left = ( long )0;						// ��Left   ��Ϊ 0
	WindowRect.right = ( long )m_nWidth;						// ��Right  ��ΪҪ��Ŀ���
	WindowRect.top = ( long )0;							// ��Top    ��Ϊ 0
	WindowRect.bottom = ( long )m_nHeight;						// ��Bottom ��ΪҪ��ĸ߶�

	m_hInstance		= GetModuleHandle( NULL );			// ȡ�����Ǵ��ڵ�ʵ��
	wc.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// �ƶ�ʱ�ػ�����Ϊ����ȡ��DC
	wc.lpfnWndProc		= ( WNDPROC ) &OpenGLGame::wndProc;				// WndProc������Ϣ
	wc.cbClsExtra		= 0;						// �޶��ⴰ������
	wc.cbWndExtra		= 0;						// �޶��ⴰ������
	wc.hInstance		= m_hInstance;					// ����ʵ��
	wc.hIcon		= LoadIcon( NULL, IDI_WINLOGO );			// װ��ȱʡͼ��
	wc.hCursor		= LoadCursor( NULL, IDC_ARROW );			// װ�����ָ��
	wc.hbrBackground	= NULL;						// GL����Ҫ����
	wc.lpszMenuName		= NULL;						// ����Ҫ�˵�
	wc.lpszClassName	= "OpenG";					// �趨������


	if ( !RegisterClass( &wc ) )						// ����ע�ᴰ����
	{
		MessageBox( NULL, "ע�ᴰ��ʧ��", "����", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// �˳�������FALSE
	}

	if ( m_bFullScreen )								// Ҫ����ȫ��ģʽ��?
	{
		DEVMODE dmScreenSettings;						// �豸ģʽ
		memset( &dmScreenSettings, 0, sizeof( dmScreenSettings ) );			// ȷ���ڴ����Ϊ��
		dmScreenSettings.dmSize = sizeof( dmScreenSettings );			// Devmode �ṹ�Ĵ�С
		dmScreenSettings.dmPelsWidth	= m_nWidth;				// ��ѡ��Ļ����
		dmScreenSettings.dmPelsHeight	= m_nHeight;				// ��ѡ��Ļ�߶�
		dmScreenSettings.dmBitsPerPel	= m_nBitMode;					// ÿ������ѡ��ɫ�����
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;



		// ����������ʾģʽ�����ؽ����ע: CDS_FULLSCREEN ��ȥ��״̬����
		if ( ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL )
		{
			// ��ģʽʧ�ܣ��ṩ����ѡ��˳����ڴ��������С�
			if ( MessageBox( NULL, "ȫ��ģʽ�ڵ�ǰ�Կ�������ʧ�ܣ�\nʹ�ô���ģʽ��", "G", MB_YESNO | MB_ICONEXCLAMATION ) == IDYES )
			{
				m_bFullScreen = FALSE;				// ѡ�񴰿�ģʽ(Fullscreen=FALSE)
			}
			else
			{
				// ����һ���Ի��򣬸����û��������
				MessageBox( NULL, "���򽫱��ر�", "����", MB_OK | MB_ICONSTOP );
				return FALSE;					//  �˳������� FALSE
			}
		}
	}


	if ( m_bFullScreen )								// �Դ���ȫ��ģʽ��?
	{
		dwExStyle = WS_EX_APPWINDOW;					// ��չ������
		dwStyle = WS_POPUP;						// ������
		ShowCursor( FALSE );						// �������ָ��
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// ��չ������
		dwStyle = WS_OVERLAPPEDWINDOW;					//  ������
	}

	AdjustWindowRectEx( &WindowRect, dwStyle, FALSE, dwExStyle );		// �������ڴﵽ����Ҫ��Ĵ�С

	if ( !( m_hWnd = CreateWindowEx(	dwExStyle,				// ��չ������
	                                    "OpenG",				// ������
	                                    m_szTitle,					// ���ڱ���
	                                    WS_CLIPSIBLINGS |			// ����Ĵ���������
	                                    WS_CLIPCHILDREN |			// ����Ĵ���������
	                                    dwStyle,				// ѡ��Ĵ�������
	                                    0, 0,					// ����λ��
	                                    WindowRect.right - WindowRect.left,	// ��������õĴ��ڿ���
	                                    WindowRect.bottom - WindowRect.top,	// ��������õĴ��ڸ߶�
	                                    NULL,					// �޸�����
	                                    NULL,					// �޲˵�
	                                    m_hInstance,				// ʵ��
	                                    NULL ) ) )					// ����WM_CREATE�����κζ���
	{
		killGLWindow();							// ������ʾ��
		MessageBox( NULL, "���ܴ���һ�������豸������", "����", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// ���� FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =					// /pfd ���ߴ���������ϣ���Ķ�����������ʹ�õ����ظ�ʽ
	{
		sizeof( PIXELFORMATDESCRIPTOR ),					// ������ʽ�������Ĵ�С
		1,								// �汾��
		PFD_DRAW_TO_WINDOW |						// ��ʽ֧�ִ���
		PFD_SUPPORT_OPENGL |						// ��ʽ����֧��OpenGL
		PFD_DOUBLEBUFFER,						// ����֧��˫����
		PFD_TYPE_RGBA,							// ���� RGBA ��ʽ
		m_nBitMode,								// ѡ��ɫ�����
		0, 0, 0, 0, 0, 0,						// ���Ե�ɫ��λ
		0,								// ��Alpha����
		0,								// ����Shift Bit
		0,								// ���ۼӻ���
		0, 0, 0, 0,							// ���Ծۼ�λ
		16,								// 16λ Z-���� (��Ȼ���)
		0,								// ���ɰ建��
		0,								// �޸�������
		PFD_MAIN_PLANE,							// ����ͼ��
		0,								// Reserved
		0, 0, 0								// ���Բ�����
	};


	if ( !( m_hDC = GetDC( m_hWnd ) ) )							// ȡ���豸��������ô?
	{
		killGLWindow();							// ������ʾ��
		MessageBox( NULL, "���ܴ���һ����ƥ������ظ�ʽ", "����", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// ���� FALSE
	}

	if ( !( PixelFormat = ChoosePixelFormat( m_hDC, &pfd ) ) )				// Windows �ҵ���Ӧ�����ظ�ʽ����?
	{
		killGLWindow();							// ������ʾ��
		MessageBox( NULL, "�����������ظ�ʽ", "����", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// ���� FALSE
	}

	if( !SetPixelFormat( m_hDC, PixelFormat, &pfd ) )				// �ܹ��������ظ�ʽô?
	{
		killGLWindow();							// ������ʾ��
		MessageBox( NULL, "�����������ظ�ʽ", "����", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// ���� FALSE
	}


	if ( !( m_hRC = wglCreateContext( m_hDC ) ) )					// �ܷ�ȡ����ɫ������?
	{
		killGLWindow();							// ������ʾ��
		MessageBox( NULL, "���ܴ���OpenGL��Ⱦ������", "����", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// ���� FALSE
	}

	if( !wglMakeCurrent( m_hDC, m_hRC ) )						// ���Լ�����ɫ������
	{
		killGLWindow();							// ������ʾ��
		MessageBox( NULL, "���ܼ��ǰ��OpenGL��Ȼ������", "����", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// ���� FALSE
	}

	ShowWindow( m_hWnd, SW_SHOW );						// ��ʾ����
	SetForegroundWindow( m_hWnd );						// ����������ȼ�
	SetFocus( m_hWnd );								// ���ü��̵Ľ������˴���
	resizeGLScene( m_nWidth, m_nHeight );						// ����͸�� GL ��Ļ


	if ( !initGL() )								// ��ʼ���½���GL����
	{
		killGLWindow();							// ������ʾ��
		MessageBox( NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return FALSE;							// ���� FALSE
	}


	return TRUE;								// �ɹ�
}

GLvoid OpenGLGame::killGLWindow( GLvoid ) /* ������ ٴ��?*/
{
	if ( m_bFullScreen )								// ���Ǵ���ȫ��ģʽ��?
	{
		ChangeDisplaySettings( NULL, 0 );					// �ǵĻ����л�������
		ShowCursor( TRUE );						// ��ʾ���ָ��
	}

	if ( m_hRC )								// ����ӵ��OpenGL��Ⱦ��������?
	{
		if ( !wglMakeCurrent( NULL, NULL ) )					// �����ܷ��ͷ�DC��RC������?
		{
			MessageBox( NULL, "�ͷ�DC��RCʧ�ܡ�", "�رմ���", MB_OK | MB_ICONINFORMATION );
		}

		if ( !wglDeleteContext( m_hRC ) )					// �����ܷ�ɾ��RC?
		{
			MessageBox( NULL, "�ͷ�RCʧ�ܡ�", "�رմ���", MB_OK | MB_ICONINFORMATION );
		}

		m_hRC = NULL;							// ��RC��Ϊ NULL
	}

	if ( m_hDC && !ReleaseDC( m_hWnd, m_hDC ) )					// �����ܷ��ͷ� DC?
	{
		MessageBox( NULL, "�ͷ�DCʧ�ܡ�", "�رմ���", MB_OK | MB_ICONINFORMATION );
		m_hDC = NULL;							// �� DC ��Ϊ NULL
	}

	if ( m_hWnd && !DestroyWindow( m_hWnd ) )					// �ܷ����ٴ���?
	{
		MessageBox( NULL, "�ͷŴ��ھ��ʧ�ܡ�", "�رմ���", MB_OK | MB_ICONINFORMATION );
		m_hWnd = NULL;							// �� hWnd ��Ϊ NULL
	}

	if ( !UnregisterClass( "OpenG", m_hInstance ) )				// �ܷ�ע����?
	{
		MessageBox( NULL, "����ע�������ࡣ", "�رմ���", MB_OK | MB_ICONINFORMATION );
		m_hInstance = NULL;							// �� hInstance ��Ϊ NULL
	}
}

int OpenGLGame::initGL( GLvoid ) /* �˴���ʼ��OpenGL������������ */
{
	// Light values and coordinates
	GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat  specuref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glEnable( GL_DEPTH_TEST );	// Hidden surface removal
	glFrontFace( GL_CCW );		// Counter clock-wise polygons face out
	glEnable( GL_CULL_FACE );		// Do not calculate inside of jet

	// Enable lighting
	glEnable( GL_LIGHTING );

	// Setup and enable light 0
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
	glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
	glEnable( GL_LIGHT0 );

	// Enable color tracking
	glEnable( GL_COLOR_MATERIAL );

	// Set Material properties to follow glColor values
    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
    glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
    glMateriali( GL_FRONT, GL_SHININESS, 128 );

    glMaterialfv( GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, specular );

	// Light blue background
	glClearColor( 0.0f, 0.0f, 1.0f, 1.0f );

	return TRUE; // Initialization Went OK
}

GLvoid OpenGLGame::resizeGLScene( GLsizei w, GLsizei h )
{
	GLfloat fAspect;
	GLfloat lightPos[] = { -50.f, 50.0f, 100.0f, 1.0f };

	// Prevent a divide by zero
	if( h == 0 )
	{
		h = 1;
	}

	// Set Viewport to window dimensions
	glViewport( 0, 0, w, h );

	// Reset coordinate system
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	fAspect = ( GLfloat ) w / ( GLfloat ) h;
	gluPerspective( 45.0f, fAspect, 1.0f, 225.0f );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glLightfv( GL_LIGHT0, GL_POSITION, lightPos );
	glTranslatef( 0.0f, 0.0f, -150.0f );
}


void OpenGLGame::onKeyPressed( char key )
{
	if( key == VK_UP )
	{
		xRot -= 5.0f;
	}

	if( key == VK_DOWN )
	{
		xRot += 5.0f;
	}

	if( key == VK_LEFT )
	{
		yRot -= 5.0f;
	}

	if( key == VK_RIGHT )
	{
		yRot += 5.0f;
	}

	if( key > 356.0f )
	{
		xRot = 0.0f;
	}

	if( key < -1.0f )
	{
		xRot = 355.0f;
	}

	if( key > 356.0f )
	{
		yRot = 0.0f;
	}

	if( key < -1.0f )
	{
		yRot = 355.0f;
	}
}

void OpenGLGame::onKeyReleased( char key )
{
	m_vbPressKeys[key] = false;
}

bool OpenGLGame::isKeyPressed( char key )
{
	return m_vbPressKeys[key];
}

void OpenGLGame::setFullScreen( bool bFullSceen )
{
	m_bFullScreen = bFullSceen;
}

bool OpenGLGame::isFullScreen() const
{
	return m_bFullScreen;
}

bool OpenGLGame::isActive() const
{
	return m_bActive;
}

void OpenGLGame::setActive( bool bActive )
{
	m_bActive = bActive;
}

void OpenGLGame::drawGround( void )
{

}

