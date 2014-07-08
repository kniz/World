#include "DX9.hpp"
#include "define.hpp"
#include "../../../../WindowModules/Sources/WindowModule/Sources/EntryPoints/Headers.hpp"
#include "../Sprite/Sprite.hpp"
#include "../Texture/Texture.hpp"
#include "../TabledTexture/TabledTexture.hpp"
#include "../FixedProgram/FixedProgram.hpp"
#include "../BloomProgram/BloomProgram.hpp"
#include "../BlurProgram/BlurProgram.hpp"
#include "../DXFont/DXFont.hpp"

namespace DX9Graphics
{
	HWND DX9::global_window = NE_NULL;

		type_result  DX9::Connector::connect(NEKeyCodeSet& keyset)
		{
			if(keyset.getLength() < _KEY_COUNT) return RESULT_TYPE_ERROR | RESULT_WRONG_BOUNDARY | RESULT_WRONG_PARAMETER | RESULT_WRONG_POINTER_ADDRESSING;
			for(int n=0; n < _KEY_COUNT ;n++)
				if( ! &keyset[n] ) return RESULT_TYPE_ERROR | RESULT_WRONG_POINTER_ADDRESSING | RESULT_WRONG_PARAMETER | RESULT_WRONG_BOUNDARY;

			_window_selector = static_cast<NEModuleSelector*>( &(keyset[0]) );
			_is_load_from_ini_when_start = static_cast<NEBooleanKey*>( &(keyset[1]) );
			_is_vertical_synchronized = static_cast<NEBooleanKey*>( &(keyset[2]) );
			_is_windowed = static_cast<NEBooleanKey*>( &(keyset[3]) );			
			_is_32bit_color = static_cast<NEBooleanKey*>( &(keyset[4]) );
			_is_32bit_texture = static_cast<NEBooleanKey*>( &(keyset[5]) );			
			_screen_width = static_cast<NEIntKey*>( &(keyset[6]) );
			_screen_height = static_cast<NEIntKey*>( &(keyset[7]) );
			_screen_ratio = static_cast<NEFloatKey*>( &(keyset[8]) );
			_back_buffer_count = static_cast<NEIntKey*>( &(keyset[9]) );
			_screen_refresh_rate = static_cast<NEIntKey*>( &(keyset[10]) );
			_swap_effect = static_cast<NEIntKey*>( &(keyset[11]) );

			return RESULT_SUCCESS;
		}

		NEModuleSelector& DX9::Connector::getWindowSelector()
		{
			return *_window_selector;
		}

		const NEModuleSelector& DX9::Connector::getWindowSelector() const
		{
			return *_window_selector;
		}

		NEBooleanKey &DX9::Connector::isVerticalSynchronized()
		{
			return *_is_vertical_synchronized;
		}

		const NEBooleanKey &DX9::Connector::isVerticalSynchronized() const
		{
			return *_is_vertical_synchronized;
		}

		const NEBooleanKey &DX9::Connector::isWindowed() const
		{
			return *_is_windowed;
		}

		NEBooleanKey &DX9::Connector::isWindowed()
		{
			return *_is_windowed;
		}

		NEBooleanKey &DX9::Connector::is32BitColor()
		{
			return *_is_32bit_color;
		}

		const NEBooleanKey &DX9::Connector::is32BitColor() const
		{
			return *_is_32bit_color;
		}

		NEBooleanKey &DX9::Connector::is32BitTexture()
		{
			return *_is_32bit_texture;
		}

		const NEBooleanKey &DX9::Connector::is32BitTexture() const
		{
			return *_is_32bit_texture;
		}

		NEIntKey &DX9::Connector::getScreenWidth()
		{
			return *_screen_width;
		}

		const NEIntKey &DX9::Connector::getScreenWidth() const
		{
			return *_screen_width;
		}

		NEIntKey &DX9::Connector::getScreenHeight()
		{
			return *_screen_height;
		}

		const NEIntKey &DX9::Connector::getScreenHeight() const
		{
			return *_screen_height;
		}

		NEFloatKey& DX9::Connector::getScreenRatio()
		{
			return *_screen_ratio;
		}

		const NEFloatKey& DX9::Connector::getScreenRatio() const
		{
			return *_screen_ratio;
		}

		NEBooleanKey &DX9::Connector::isLoadFromINIWhenStart()
		{
			return *_is_load_from_ini_when_start;
		}

		const NEBooleanKey &DX9::Connector::isLoadFromINIWhenStart() const
		{
			return *_is_load_from_ini_when_start;
		}

		NEIntKey &DX9::Connector::getBackBufferCount()
		{
			return *_back_buffer_count;
		}

		const NEIntKey &DX9::Connector::getBackBufferCount() const
		{
			return *_back_buffer_count;
		}

		NEIntKey &DX9::Connector::getScreenRefreshRate()
		{
			return *_screen_refresh_rate;
		}

		const NEIntKey &DX9::Connector::getScreenRefreshRate() const
		{
			return *_screen_refresh_rate;
		}
		const NEIntKey& DX9::Connector::getSwapEffect() const
		{
			return *_swap_effect;
		}

		NEIntKey& DX9::Connector::getSwapEffect()
		{
			return *_swap_effect;
		}

	DX9::DX9()
		: NEModule(), _direct3d(NE_NULL), _device(NE_NULL), _window_handle(NE_NULL)
	{
		_release();
	}

	DX9::DX9(const DX9& source)
		: NEModule(source), _direct3d(NE_NULL), _device(NE_NULL), _window_handle(NE_NULL)
	{
		getConnector().connect(getKeySet());
		_assign(source);
	}

	DX9::~DX9()
	{
		_release();
	}
		
	DX9::Connector &DX9::getConnector()
	{
		return _connector;
	}
		
	const DX9::Connector &DX9::getConnector() const
	{
		return _connector;
	}

	type_result DX9::initialize()
	{
		NEKeyCodeSet& keyset = getKeySet();
		keyset.create(12);
		keyset.push(NEModuleSelector());
		keyset.push(NEBooleanKey(_DEFAULT_IS_LOAD_FROM_INI_WHEN_START));
		keyset.push(NEBooleanKey(_DEFAULT_IS_VERTICAL_SYNCHRONIZED));
		keyset.push(NEBooleanKey(_DEFAULT_IS_WINDOW_MODE));
		keyset.push(NEBooleanKey(_DEFAULT_IS_32BIT_COLOR_MODE));
		keyset.push(NEBooleanKey(_DEFAULT_IS_32BIT_TEXTURE_MODE));		
		keyset.push(NEIntKey(_DEFAULT_SCREEN_WIDTH));
		keyset.push(NEIntKey(_DEFAULT_SCREEN_HEIGHT));
		keyset.push(NEFloatKey(_DEFAULT_SCREEN_RATIO));
		keyset.push(NEIntKey(_DEFAULT_BACK_BUFFER_COUNT));
		keyset.push(NEIntKey(_DEFAULT_SCREEN_REFRESH_RATE));
		keyset.push(NEIntKey(_DEFAULT_SWAP_EFFECT));
		
		getConnector().connect(keyset);

		return RESULT_SUCCESS;
	}

	type_result DX9::execute()
	{
		if(_device)
		{
			return RESULT_SUCCESS;
		}

		//	main:
		//		디바이스가 없다면 초기화:
		if( ! isDeviceActive())
		{
			_initializeDirects();
			getDevice()->SetRenderState( D3DRS_AMBIENT, 0xffffffff );
			getDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			getDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			getDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
			getDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			getDevice()->LightEnable(0, FALSE);
			getDevice()->LightEnable(1, FALSE);
		}

		return RESULT_SUCCESS;
	}

	type_result DX9::forceWindowHandle(HWND window_handle_to_force)
	{
		if(isDeviceActive())
		{
			ALERT_ERROR(" : 이미 디바이스가 활성화 되어있기 때문에 강제로 변경할 수 없습니다.");
			return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;
		}

		_window_handle = window_handle_to_force;

		return RESULT_SUCCESS;
	}

	type_result DX9::forcePresentParameters(PresentParameters& parameters_to_force)
	{
		if(isDeviceActive())
		{
			ALERT_ERROR(" : 이미 디바이스가 활성화 되어있기 때문에 강제로 변경할 수 없습니다.");
			return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;
		}
		if(NEResult::hasError(parameters_to_force.isValid()))
		{
			ALERT_ERROR(" : 주어진 파라메터가 손상되었습니다.\n강제 변경을 취소합니다.");
			return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
		}

		_present_parameter = parameters_to_force;

		return RESULT_SUCCESS;
	}

	const DX9::Capabilities& DX9::getCapabilities() const
	{
		const Capabilities* nullpointer = NE_NULL;
		if( ! isDeviceActive())
			return *nullpointer;

		return _capabilities;
	}

	const DX9::DisplayModeManager& DX9::getDisplayModeManager() const
	{
		const DisplayModeManager* nullpointer = NE_NULL;
		if( ! isDeviceActive())
			return *nullpointer;

		return _display_mode_manager;
	}

	DX9::DisplayMode DX9::getCurrentDisplayMode()
	{
		if( ! getDirect3D())
		{
			ALERT_ERROR("direct3d가 초기화 되지 않았습니다");

			return DisplayMode();				
		}



		//	main:
		DisplayMode buffer;
		if( FAILED( _direct3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &buffer)))
			ALERT_ERROR(" : 현재 그래픽카드의 디스플레이 모드를 가져오지 못했습니다");

		return buffer;
	}

	LPDIRECT3D9 DX9::getDirect3D()
	{
		return _direct3d;
	}

	const LPDIRECT3D9 DX9::getDirect3D() const
	{
		return _direct3d;
	}

	LPDIRECT3DDEVICE9 DX9::getDevice()
	{
		return _device;
	}

	const LPDIRECT3DDEVICE9 DX9::getDevice() const
	{
		return _device;
	}

	bool DX9::isDeviceActive() const
	{
		return getDevice() && getDirect3D();
	}


	const NEExportable::ModuleHeader& DX9::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T(_NAME);
			_header.getDeveloper() = _T(_DEVELOPER);
			_header.setRevision(_REVISION);
			_header.getComment() = _T(_COMMENT);
			_header.getVersion()  = _T(_VERSION);
			_header.getReleaseDate() = _T(_DATE);
			_header.getModuleDependencies().create(_DEPENDENCIES_COUNT);
			_header.setMaxErrorCodeCount(1);
		}

		return _header;
	}

	const DX9::PresentParameters& DX9::getPresentParameters() const
	{
		return _present_parameter;
	}

	NEObject& DX9::clone() const
	{
		return *(new DX9(*this));
	}

	void DX9::release()
	{
		SuperClass::release();

		_release();
	}

	NEBinaryFileSaver& DX9::serialize(NEBinaryFileSaver& saver) const
	{
		SuperClass::serialize(saver);

		//	나머지는 initialize때에 생성되는 것 / 저장이 불가능한 것이다.
		return saver << _present_parameter;
	}

	NEBinaryFileLoader& DX9::serialize(NEBinaryFileLoader& loader)
	{
		SuperClass::serialize(loader);

		return loader >> _present_parameter;
	}

	type_result DX9::isValid() const
	{
		type_result result = SuperClass::isValid();
		if(NEResult::hasError(result)) return result;
		if(NEResult::hasError(result = getCapabilities().isValid())) return result;
		if(NEResult::hasError(result = getPresentParameters().isValid())) return result;
		if(NEResult::hasError(result = getDisplayModeManager().isValid())) return result;

		return RESULT_SUCCESS;
	}

	type_result DX9::restore()
	{
		HRESULT	results = _device->TestCooperativeLevel();
		while(results == D3DERR_DEVICELOST)
		{
			while(results != D3DERR_DEVICENOTRESET)
			{
				Sleep(1000);
				MSG	message;
				PeekMessage(&message, NULL, 0, 0, PM_REMOVE);
				TranslateMessage(&message);
				DispatchMessage(&message);

				results = _device->TestCooperativeLevel();
			}		

			_releaseShaders();
			_releaseResources();

			if ( FAILED(_device->Reset(&_present_parameter)) )
				results = D3DERR_DEVICELOST;
			else
			{			
				_restoreResources();
				_releaseShaders();
				results = _device->TestCooperativeLevel();
			}		
		}

		return RESULT_SUCCESS;
	}

	type_result DX9::__initializeDirect3D()
	{
		_direct3d = Direct3DCreate9(D3D_SDK_VERSION);

		if ( ! _direct3d)
		{
			ALERT_ERROR(" : DirectX3D9 초기화 실패");

			return RESULT_TYPE_ERROR;
		}

		return RESULT_SUCCESS;
	}

	type_result DX9::__initializeDevice()
	{	
		//	pre:
		//		사전 준비:
		//			외부로부터 set 될 수 있는 데이터의 형태가 다양하게 존재하기 때문에, 
		//			어떤 형태로 데이터를 준비해야 하는지도 판단해야 한다.
		//			판단해야 하는 데이터의 종류는 2종류다.
		//				1. 윈도우 핸들
		//					a. 스크립트편집을 통해 키셋에 지정한 모듈셀렉터로 가져온다.(기본값)
		//					b. 강제로 프로그램상에서 핸들을 지정한다.(이 경우, b의 과정은 건너 뜀)
		//				2. PresentParameters
		//					a. INI로부터 키셋의 데이터를 가져온다. 이후로는 b와 동일
		//					b. 스크립트 편집을 통해 키셋에 지정한 값들로 PresentParameters를 생성한다
		//					(기본값. PresentParameters의 값이 많이 있기 때문에 가장 많이 쓸법한 몇개만을
		//					편집 가능하다)
		//					c. 강제로 프로그램상에서 PresentParameters 지정한다.( a의 과정은 건너 뜀)
		//			핸들:		
		if(global_window)
			_window_handle = global_window;

		if( ! _window_handle)
		{
			if( NEResult::hasError(_bindWindowHandle()) )
			{
				ALERT_ERROR(" : 윈도우 핸들을 바인딩하는 과정에서 실패함. 작업을 취소합니다.");

				return RESULT_TYPE_ERROR;
			}
		}
		//			PresentParameters:
		//				데이터가 외부에서 입력되지 않았다면:
		//					왜 Valid를 검사하는 것이 데이터가 외부에서 입력되지 않았다는
		//					것을 의미하게 되는가:
		//						외부에서 데이터를 입력하지 않으면 PresentParameters는 release를
		//						수행한 상태일 것이고, BackBufferWidth, Height는 각각 0이 된다.
		//						그런데, Width와 Height가 0이라는 부분은 명백하게 유효하지 않은
		//						부분 이므로 isValid로 검사할 때 에러가 나오게 된다.
		if(NEResult::hasError(getPresentParameters().isValid()))
		{
			//				INI에서 가져오는가:
			if(getConnector().isLoadFromINIWhenStart().getValue())
			{
				//				복구용 데이터 작성:
				NEKeyCodeSet& keyset = getKeySet();
				NEArrayTemplate<NEKey*, true> buffer(keyset.getLength());	//	내부에 NENodeSetKey 등이 없으므로, 이렇게 해도 무방하다.
				for(int n=0; n < keyset.getLength() ;n++)
					buffer.push(keyset[n]);
				//				데이터 획득:
				_loadKeysFromINI();
				//				데이터 복구:
				//					복구 해야 하는가:
				if( ! isKeysForPresentParametersValid())
				{
					ALERT_ERROR(" : INI로 로드를 하려 했으나, 잘못된 값으로 인하여, 이전 값으로 복구 합니다.");
					
					for(int n=0; n < buffer.getLength() ;n++)
						keyset[n].assign(buffer[n]);
				}
			}
			//				키셋으로부터 PresentParameters를 생성:
			//					타겟팅:
			PresentParameters& parameters = _present_parameter;
			//					초기화:
			parameters.release();			
			//					데이터 할당:
			//						Display에 관한 부분 차후 검증과정을 수행해야 한다. 하드웨어의 특성을 타기 때문에
			//						지원가능한 Display 목록을 획득한 다음에 가장 일치하는 디스플레이 목록으로
			//						변경해야만 한다.
			//						일단 선호하는 디스플레이 정보를 할당:
			DisplayMode just_preferred;
			just_preferred.setWindowed(getConnector().isWindowed().getValue());
			just_preferred.Width = getConnector().getScreenWidth().getValue();
			just_preferred.Height = getConnector().getScreenHeight().getValue();
			just_preferred.RefreshRate = getConnector().getScreenRefreshRate().getValue();
			//						parameters에 할당:
			parameters.setPreferredDisplayMode(just_preferred);
			//						기타 데이터:
			parameters.hDeviceWindow = _window_handle;
			parameters.SwapEffect = D3DSWAPEFFECT(getConnector().getSwapEffect().getValue());
			parameters.BackBufferCount = getConnector().getBackBufferCount().getValue();
			if(getConnector().isWindowed().getValue())
				parameters.BackBufferFormat = getCurrentDisplayMode().Format;
			parameters.BackBufferHeight = getConnector().getScreenHeight().getValue();
			parameters.BackBufferWidth = getConnector().getScreenWidth().getValue();
			parameters.AutoDepthStencilFormat = D3DFMT_D24S8;	//	이거 임의로 주면 안되지 않나?
			parameters.EnableAutoDepthStencil = true;
			if( ! getConnector().isVerticalSynchronized().getValue())
				parameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		}
		

		//	main:			
		//		PresentParameters 할당:
		//			PreferredDisplay를 조정:
		DisplayMode& displaymode_to_adjust = getPresentParameters().getPreferredDisplayMode();		
		_display_mode_manager.makeDisplayModeAvailable(displaymode_to_adjust, getDirect3D());
		_present_parameter.setPreferredDisplayMode(displaymode_to_adjust);
		//		Capabilities 획득:		
		__initializeCapabilities();	//	DirectX가 초기화 되었으므로 initialize가 호출 가능하다.
		//		윈도우 크기 변경:
		_updateTargetWindowSizeWithSpecifiedScreenSize();
		//		Direct 3D 디바이스 생성:
		HRESULT result = S_OK;

		if( FAILED(result = _direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _window_handle, _capabilities.isHardWareVertexProcessingAvailable() ? D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING, &_present_parameter, &_device)) ) // 스태틱변수(HWND)를 사용하고있다
		{
			ALERT_ERROR(" : 디바이스 생성 실패.\n\t에러코드: %d", result);

			return RESULT_TYPE_ERROR;
		}

		return RESULT_SUCCESS;
	}

	type_result DX9::_releaseDevice()
	{
		type_result result = RESULT_SUCCESS;
		if(_device)
			result +=_device->Release();
		_device = NE_NULL;

		if(_direct3d)
			result += _direct3d->Release();
		_direct3d = NE_NULL;

		return result;
	}

	type_result DX9::_releaseResources()
	{
		_releaseResourcesFromModules();
		
		return _releaseResourcesFromShaderProgram();
	}

	type_result DX9::_releaseResourcesFromModules()
	{
		if( ! _device) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		
		NEModuleSelector selector;
		selector.setNodeType(NECodeType::ALL);
		selector.setModuleType(NECodeType::SCRIPT);
		selector.setModuleCodeSet(_getResourceCodes());

		while(&selector.getModule())
		{
			Resource& itr = static_cast<Resource&>(selector.peekModule());

			itr.releaseResource();
		}
		return RESULT_SUCCESS;
	}

	type_result DX9::_releaseShaders()
	{
		if( ! _device) return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		return RESULT_SUCCESS;
	}

	type_result DX9::_restoreResources()
	{
		if( ! _device) return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		return RESULT_SUCCESS;
	}

	type_result DX9::_restoreShaders()
	{
		if( ! _device) return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		return RESULT_SUCCESS;
	}

	type_result DX9::_loadKeysFromINI()
	{
		NEINIManager& ini = Kernal::getInstance().getINIManager();

		const NEExportable::Identifier& identifier = getHeader();

		type_result result = RESULT_SUCCESS;
		NETString buffer;
		result += ini.readModuleIniString(identifier, _KEYNAME_OF_IS_WINDOW_MODE, buffer);
		getConnector().isWindowed().getValue() = buffer.toBoolean();
		result += ini.readModuleIniString(identifier, _KEYNAME_OF_IS_VERTICAL_SYNCHRONIZED, buffer);
		getConnector().isVerticalSynchronized().getValue() = buffer.toBoolean();
		result += ini.readModuleIniString(identifier, _KEYNAME_OF_IS_32BIT_COLOR_MODE, buffer);
		getConnector().is32BitColor().getValue() = buffer.toBoolean();
		result += ini.readModuleIniString(identifier, _KEYNAME_OF_IS_32BIT_TEXTURE_MODE, buffer);
		getConnector().is32BitTexture().getValue() = buffer.toBoolean();
		result += ini.readModuleIniString(identifier, _KEYNAME_OF_SCREEN_WIDTH, buffer);
		getConnector().getScreenWidth().getValue() = buffer.toInt();
		result += ini.readModuleIniString(identifier, _KEYNAME_OF_SCREEN_HEIGHT, buffer);
		getConnector().getScreenHeight().getValue() = buffer.toInt();
		result += ini.readModuleIniString(identifier, _KEYNAME_OF_SCREEN_RATIO, buffer);
		getConnector().getScreenRatio().getValue() = static_cast<float>(buffer.toDouble());
		result += ini.readModuleIniString(identifier, _KEYNAME_OF_BACK_BUFFER_COUNT, buffer);
		getConnector().getBackBufferCount().getValue() = buffer.toInt();
		result += ini.readModuleIniString(identifier, _KEYNAME_OF_SCREEN_REFRESH_RATE, buffer);
		getConnector().getScreenRefreshRate().getValue() = buffer.toInt();
		result += ini.readModuleIniString(identifier, _KEYNAME_OF_SWAP_EFFECT, buffer);
		getConnector().getSwapEffect().getValue() = buffer.toInt();		

		return result;
	}

	type_result DX9::_saveKeysToINI() const
	{
		NEINIManager& ini = Kernal::getInstance().getINIManager();

		const NEExportable::Identifier& identifier = getHeader();

		type_result result = RESULT_SUCCESS;		
		result += ini.writeModuleIniString(identifier, _KEYNAME_OF_IS_WINDOW_MODE, getConnector().isWindowed().getValue());
		result += ini.writeModuleIniString(identifier, _KEYNAME_OF_IS_VERTICAL_SYNCHRONIZED, getConnector().isVerticalSynchronized().getValue());
		result += ini.writeModuleIniString(identifier, _KEYNAME_OF_IS_32BIT_COLOR_MODE, getConnector().is32BitColor().getValue());
		result += ini.writeModuleIniString(identifier, _KEYNAME_OF_IS_32BIT_TEXTURE_MODE, getConnector().is32BitTexture().getValue());
		result += ini.writeModuleIniString(identifier, _KEYNAME_OF_SCREEN_WIDTH, getConnector().getScreenWidth().getValue());
		result += ini.writeModuleIniString(identifier, _KEYNAME_OF_SCREEN_HEIGHT, getConnector().getScreenHeight().getValue());
		result += ini.writeModuleIniString(identifier, _KEYNAME_OF_SCREEN_RATIO, getConnector().getScreenRatio().getValue());
		result += ini.writeModuleIniString(identifier, _KEYNAME_OF_BACK_BUFFER_COUNT, getConnector().getBackBufferCount().getValue());
		result += ini.writeModuleIniString(identifier, _KEYNAME_OF_SCREEN_REFRESH_RATE, getConnector().getScreenRefreshRate().getValue());
		result += ini.writeModuleIniString(identifier, _KEYNAME_OF_SWAP_EFFECT, getConnector().getSwapEffect().getValue());		

		return result;
	}

	const DX9& DX9::_assign(const DX9& source)
	{
		if(this == &source) return *this;

		_window_handle = source._window_handle;
		_direct3d = source._direct3d;
		_device = source._device;
		_present_parameter = source._present_parameter;
		_display_mode_manager = source._display_mode_manager;
		_capabilities = source._capabilities;

		return *this;
	}

	type_result DX9::_bindWindowHandle()
	{
		NEModuleSelector& selector = getConnector().getWindowSelector();
		if(selector.getBinder().isBinded()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		
		while( &selector.getModule())
		{
			NEModule& module = selector.peekModule();
			
			if( module.getHeader().NEExportable::Identifier::operator==(Window().getHeader()) )
			{
				//	윈도우 핸들 획득:
				Window& window = static_cast<Window&>(module);
				_window_handle = window.getHWND();
				//	바인딩:
				//		현재의 윈도우 핸들이 유효하지 않게 되었을때 체크 가능하다.
				selector.bind();
				selector.initializeReferingPoint();
				break;
			}
		}	
		
		if( ! _window_handle)
		{
			ALERT_ERROR(" : 셀렉터로부터 윈도우를 가져오지 못했습니다.");		
			return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
		}

		return RESULT_SUCCESS;
	}

	void DX9::_release()
	{
		_releaseShaders();
		_releaseResources();
		_releaseDevice();
		_present_parameter.release();
		_capabilities.release();
		_display_mode_manager.release();
		_window_handle = NE_NULL;		
	}

	bool DX9::isKeysForPresentParametersValid() const
	{
		int swap_effect = getConnector().getSwapEffect().getValue();
		if(	swap_effect != 1			&&
			swap_effect != 2			&&
			swap_effect != 3			&&
			swap_effect != 4			&&
			swap_effect != 5			&&
			swap_effect	!= 0x7fffffff	)
			return false;
		if(getConnector().getScreenWidth().getValue() <= 0) return false;
		if(getConnector().getScreenHeight().getValue() <= 0) return false;
		if(getConnector().getScreenRatio().getValue() <= 0.0f) return false;
		if(getConnector().getBackBufferCount().getValue() < 0) return false;

		return true;
	}

	type_result DX9::__initializeCapabilities()
	{
		//	pre:
		//		에러체크:
		if( ! getDirect3D())
		{
			ALERT_ERROR(" : 다이렉트X3D가 초기화 되지 않았기 때문에 호환성 여부를 알아낼 수 없습니다.");
			return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
		}
		//		초기화:
		_capabilities.release();



		// main:
		if(FAILED(getDirect3D()->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &_capabilities)))
		{
			ALERT_ERROR("그래픽 카드 호환성 목록을 가져오지 못했습니다.(Capabilities)");

			return RESULT_TYPE_ERROR;
		}



		//	post:
		return RESULT_SUCCESS;
	}

	type_result DX9::_initializeDirects()
	{
		type_result result = RESULT_SUCCESS;
		result |= __initializeDirect3D();
		result |= __initializeDevice();

		return result;
	}

	const NECodeSet& DX9::_getResourceCodes() const
	{
		static NECodeSet _instance;
		
		if(_instance.getSize() <= 0)
		{
			NEModuleManager& moduler = Kernal::getInstance().getModuleManager();			
			_instance.create(4);
			_instance.setCodeType(NECodeType::SCRIPT);
			_instance.push(Sprite().getHeader());
			_instance.push(Texture().getHeader());
			_instance.push(TabledTexture().getHeader());
			_instance.push(DXFont().getHeader());
		}

		return _instance;
	}

	const NECodeSet& DX9::_getShaderCodes() const
	{
		static NECodeSet _instance;

		if(_instance.getSize() <= 0)
		{
			NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
			_instance.create(1);
			_instance.setCodeType(NECodeType::SCRIPT);
			_instance.push(FixedProgram().getHeader());
		}

		return _instance;
	}

	type_result DX9::_releaseResourcesFromShaderProgram()
	{
		ShaderProgram::RenderTargetSet& targets = ShaderProgram::_getRenderTargetSet(*this);		
		targets.release();

		ShaderProgram::RenderTargetSet& bloom_temps = BloomProgram::_getTemporaryRenderTargetSet(*this);
		bloom_temps.release();

		ShaderProgram::RenderTargetSet& blur_temps = BlurProgram::_getTemporaryRenderTargetSet(*this);
		blur_temps.release();

		return RESULT_SUCCESS;
	}

	type_result DX9::_updateTargetWindowSizeWithSpecifiedScreenSize() const
	{
		//	pre:
		const Connector& cn = getConnector();
		RECT to_return = {0, 0, 
			&cn.getScreenWidth() ? cn.getScreenWidth().getValue() : 0,
			&cn.getScreenHeight() ? cn.getScreenHeight().getValue() : 0
		};
		
		if(	to_return.right <= 0	|| 
			to_return.bottom <= 0	|| 
			! _window_handle		)
		{
			ALERT_ERROR("데이터가 잘못되어서 제대로 윈도우의 크기를 변경할 수 없습니다.");
			return RESULT_TYPE_ERROR;
		}


		//	main:
		DWORD style = GetWindowLong(_window_handle, GWL_STYLE);
		BOOL is_there_a_menu = /*style & WS_SYSMENU*/FALSE;
		if( ! style)
		{
			ALERT_ERROR("스타일 정보를 획득할 수 없었습니다");
			return RESULT_TYPE_ERROR;
		}
		AdjustWindowRect(&to_return, style, is_there_a_menu);
		if( ! SetWindowPos(_window_handle, 0, 0, 0, 
			to_return.right - to_return.left, 
			to_return.bottom - to_return.top, 
			SWP_NOMOVE | SWP_NOZORDER))
		{
			ALERT_ERROR("윈도우 크기 변경 실패");
			return RESULT_TYPE_ERROR;
		}
		return RESULT_SUCCESS;
	}
}