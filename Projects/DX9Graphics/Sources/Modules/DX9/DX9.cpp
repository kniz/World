#include "DX9.hpp"
#include "../../../../WindowModules/Sources/WindowModule/Sources/EntryPoints/Headers.hpp"
#include "../Sprite/Sprite.hpp"
#include "../Texture/Texture.hpp"
#include "../TabledTexture/TabledTexture.hpp"
#include "../FixedProgram/FixedProgram.hpp"
#include "../BloomProgram/BloomProgram.hpp"
#include "../BlurProgram/BlurProgram.hpp"
#include "../NoiseProgram/NoiseProgram.hpp"
#include "../DXFont/DXFont.hpp"
#include "../Camera/Camera.hpp"
#include "define.hpp"

namespace DX9Graphics
{
	HWND DX9::global_window = NE_NULL;

	DX9::DX9()
		: NEModule(), _direct3d(NE_NULL), _device(NE_NULL), _window_handle(NE_NULL)
	{
		_release();
	}

	DX9::DX9(const DX9& source)
		: NEModule(source), _direct3d(NE_NULL), _device(NE_NULL), _window_handle(NE_NULL)
	{
		_assign(source);
	}

	DX9::~DX9()
	{
		_release();
	}

	type_result DX9::_onExecute()
	{
		//	main:
		//		디바이스가 없다면 초기화:
		if( ! isDeviceActive())
		{
			_initializeDirects();
			//getDevice()->SetRenderState( D3DRS_AMBIENT, 0xffffffff );
			getDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			getDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			//getDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
			//getDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			//getDevice()->LightEnable(0, FALSE);
			//getDevice()->LightEnable(1, FALSE);
		}

		return _render();
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
			NETStringSet& args = _header.getArgumentsComments();
			args.resize(12);
			args.push("WindowBinder\n그래픽을 렌더링할 Window 를 가리킵니다.\nkniz.Window Module을 사용하세요.");
			args.push("Cameras\n렌더링을 할 \"Camera.kniz\" Module을 참조합니다. disabled 되면 렌더링을 수행하지 않습니다.");
			args.push("Vertical Sync.\n수직동기화를 킵니다.");
			args.push("Window mode\n창 모드로 초기화 합니다.");
			args.push("32Bit Color\n32Bit Color로 렌더링 합니다.");
			args.push("32Bit Texture\n32bit Texture를 사용합니다.");
			args.push("ScreenWidth\n렌더링할 버퍼 폭 입니다. 이는 실제 화면의 크기(= 윈도우의 크기)와는 별개의 개념입니다.");
			args.push("ScreenHeight\n렌더링할 높이 입니다.");
			args.push("ScreenRatio\n비율입니다.");
			args.push("BackBuffer Count\n몇 개의 백버퍼를 사용하나요?");
			args.push("SwapEffect\n버퍼 전환 방식을 정합니다.");
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


	type_result DX9::_bindWindowHandle()
	{
		NEModuleSelector& selector = arg_window_binder.getValue();

		while(&selector.getModule())
		{
			NEModule& module = selector.peekModule();

			if(module.getHeader().NEExportable::Identifier::operator==(Window().getHeader()))
			{
				//	윈도우 핸들 획득:
				Window& window = static_cast<Window&>(module);
				_window_handle = window.getHWND();
				break;
			}
		}	

		if( ! _window_handle)
			return ALERT_ERROR(" : 셀렉터로부터 윈도우를 가져오지 못했습니다.");

		return RESULT_SUCCESS;
	}


	DX9& DX9::getInstancedDX()
	{
		static type_code code = -1;	
		static NEModuleSelector sel;

		DX9* nullpointer = 0x00;		
		NEModule* m = &sel.getModule();
		if(	code == -1	||
			! m			)
		{
			code = Kernal::getInstance().getModuleManager()
				.getModule(NEExportable::Identifier("DX9.kniz.1")).getScriptCode();
			if(code == -1)
				return *nullpointer;

			sel.initializeReferingPoint();
			sel.setCodes(NECodeSet(NECodeType(NECodeType::ALL)));
			sel.setModuleCodes(NECodeSet(NECode(code, NECodeType::MODULE_SCRIPT)));
			sel.isUsingAutoBinding() = true;
			sel.NENodeSelector::isUsingAutoBinding() = true;

			m = &sel.getModule();
			if( ! m)
				return *nullpointer;
		}
		sel.initializeReferingPoint();

		return static_cast<DX9&>(*m);
	}

	type_index DX9::camera_index = 0;

	type_result DX9::_render()
	{
		if( ! getDevice()) return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;


		type_uint color = D3DCOLOR_XRGB(0, 0, 0);
		_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0);

		const NECodeSet& cs = Camera::getModuleScriptCodes();

		NEModuleSelector& ms = arg_cameras.getValue();
		NEListTemplate<Camera*> bucket;
		while(NEModule* e = &ms.getModule())
			if (cs.find(NECode(e->getScriptCode(), NECodeType::MODULE_SCRIPT)) != NE_INDEX_ERROR)
				bucket.push(static_cast<Camera*>(e));

		camera_index = 0x8000;			//	means first_index
		int n = 0;
		for(NEListTemplate<Camera*>::Iterator* e = bucket.getIterator(0); e; e = e->getNext())
		{
			if(n == bucket.getLengthLastIndex())
				camera_index |= 0x0001;	//	means last_index

			e->getValue().render();	//	내부에서 View, Projection Matrix를 정의하고 render를 호출한다.

			n++;
			camera_index = 0;
		}


		getDevice()->Present(0, 0, 0, 0);
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
			if( NEResult::hasError(_bindWindowHandle()))
				return ALERT_ERROR(" : 윈도우 핸들을 바인딩하는 과정에서 실패함. 작업을 취소합니다.");

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
			just_preferred.setWindowed(arg_is_windowed.getValue());
			just_preferred.Width = arg_screen_width.getValue();
			just_preferred.Height = arg_screen_height.getValue();
			just_preferred.RefreshRate = arg_screen_reflesh_rate.getValue();
			//						parameters에 할당:
			parameters.setPreferredDisplayMode(just_preferred);
			//						기타 데이터:
			parameters.hDeviceWindow = _window_handle;
			parameters.SwapEffect = D3DSWAPEFFECT(arg_swap_effect.getValue());
			parameters.BackBufferCount = arg_back_buffer_count.getValue();
			if(arg_is_windowed.getValue())
				parameters.BackBufferFormat = getCurrentDisplayMode().Format;
			parameters.BackBufferHeight = arg_screen_height.getValue();
			parameters.BackBufferWidth = arg_screen_width.getValue();
			parameters.AutoDepthStencilFormat = D3DFMT_D24S8;	//	이거 임의로 주면 안되지 않나?
			parameters.EnableAutoDepthStencil = true;
			if( ! arg_is_vertical_synchronized.getValue())
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

		if (FAILED(result = _direct3d->CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _window_handle, 
			_capabilities.isHardWareVertexProcessingAvailable() ? D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
			&_present_parameter, &_device)) ) // 스태틱변수(HWND)를 사용하고있다
			return ALERT_ERROR(" : 디바이스 생성 실패.\n\t에러코드: %d", result);

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
		selector.setCodes(NECodeType(NECodeType::ALL));
		selector.setModuleCodes(_getResourceCodes());

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

	const DX9& DX9::_assign(const DX9& source)
	{
		if(this == &source) return *this;

		_window_handle = source._window_handle;
		_direct3d = source._direct3d;
		_device = source._device;
		_present_parameter = source._present_parameter;
		_display_mode_manager = source._display_mode_manager;
		_capabilities = source._capabilities;
		arg_window_binder = source.arg_window_binder;
		arg_cameras = source.arg_cameras;
		arg_is_vertical_synchronized = source.arg_is_vertical_synchronized;
		arg_is_windowed = source.arg_is_windowed;
		arg_is_32bit_color = source.arg_is_32bit_color;
		arg_is_32bit_texture = source.arg_is_32bit_texture;
		arg_screen_width = source.arg_screen_width;
		arg_screen_height = source.arg_screen_height;
		arg_screen_ratio = source.arg_screen_ratio;
		arg_back_buffer_count = source.arg_back_buffer_count;
		arg_screen_reflesh_rate = source.arg_screen_reflesh_rate;
		arg_swap_effect = source.arg_swap_effect;

		return *this;
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
		int swap_effect = arg_swap_effect.getValue();
		if(	swap_effect != 1			&&
			swap_effect != 2			&&
			swap_effect != 3			&&
			swap_effect != 4			&&
			swap_effect != 5			&&
			swap_effect	!= 0x7fffffff	)
			return false;
		if(arg_screen_width.getValue() <= 0) return false;
		if(arg_screen_height.getValue() <= 0) return false;
		if(arg_screen_ratio.getValue() <= 0.0f) return false;
		if(arg_back_buffer_count.getValue() < 0) return false;

		return true;
	}

	type_result DX9::__initializeCapabilities()
	{
		//	pre:
		//		에러체크:
		if( ! getDirect3D())
			return ALERT_ERROR(" : 다이렉트X3D가 초기화 되지 않았기 때문에 호환성 여부를 알아낼 수 없습니다.");
		//		초기화:
		_capabilities.release();


		// main:
		if(FAILED(getDirect3D()->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &_capabilities)))
			return ALERT_ERROR("그래픽 카드 호환성 목록을 가져오지 못했습니다.(Capabilities)");


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
		NECodeType type(NECodeType::MODULE_SCRIPT);
		static NECodeSet _instance(type);

		if(_instance.getSize() <= 0)
		{
			NEModuleManager& moduler = Kernal::getInstance().getModuleManager();			
			_instance.create(4);
			_instance.push(Sprite().getHeader());
			_instance.push(Texture().getHeader());
			_instance.push(TabledTexture().getHeader());
			_instance.push(DXFont().getHeader());
		}

		return _instance;
	}

	const NECodeSet& DX9::_getShaderCodes() const
	{
		NECodeType type(NECodeType::MODULE_SCRIPT);
		static NECodeSet _instance(type);

		if(_instance.getSize() <= 0)
		{
			NEModuleManager& moduler = Kernal::getInstance().getModuleManager();
			_instance.create(3);
			_instance.push(FixedProgram().getHeader());
			//_instance.push(NoiseProgram().getHeader());
			_instance.push(BlurProgram().getHeader());
			_instance.push(BloomProgram().getHeader());
		}

		return _instance;
	}

	type_result DX9::_releaseResourcesFromShaderProgram()
	{
		RenderTargetSet& targets = ShaderProgram::_getRenderTargetSet(*this);		
		targets.release();

		RenderTargetSet& bloom_temps = BloomProgram::_getTemporaryRenderTargetSet(*this);
		bloom_temps.release();

		RenderTargetSet& blur_temps = BlurProgram::_getTemporaryRenderTargetSet(*this);
		blur_temps.release();

		return RESULT_SUCCESS;
	}

	type_result DX9::_updateTargetWindowSizeWithSpecifiedScreenSize() const
	{
		//	pre:
		type_uint	w = &arg_screen_width.getValue() ? arg_screen_width.getValue() : 0,
			h = &arg_screen_height.getValue() ? arg_screen_height.getValue() : 0;
		RECT to_return = {0, 0, w, h};

		if(	to_return.right <= 0	||	to_return.bottom <= 0	|| 
			! _window_handle									)
			return ALERT_ERROR("데이터가 잘못되어서 제대로 윈도우의 크기를 변경할 수 없습니다.");


		//	main:
		DWORD style = GetWindowLong(_window_handle, GWL_STYLE);
		BOOL is_there_a_menu = /*style & WS_SYSMENU*/FALSE;
		if( ! style)
			return ALERT_ERROR("스타일 정보를 획득할 수 없었습니다");

		AdjustWindowRect(&to_return, style, is_there_a_menu);
		if( ! SetWindowPos(_window_handle, 0, 0, 0, 
			to_return.right - to_return.left, 
			to_return.bottom - to_return.top, 
			SWP_NOMOVE | SWP_NOZORDER))
			return ALERT_ERROR("윈도우 크기 변경 실패");

		return RESULT_SUCCESS;
	}
}