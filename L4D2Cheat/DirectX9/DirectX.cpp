#include "DirectX.h"

int* GetDirectDeviceVTable()
{
	int* vTable = nullptr;
	D3DPRESENT_PARAMETERS d3dpp{};
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;

	IDirect3DDevice9* device;
	IDirect3D9* d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	if (d3d9)
	{
		HRESULT deviceCreated = d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &device);

		if (deviceCreated == D3D_OK)
		{
			vTable = *(int**)device;

			device->Release();

		}
		else
		{
			d3dpp.Windowed = false;
			deviceCreated = d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &device);
			if (deviceCreated == D3D_OK)
			{
				vTable = *(int**)device;

				device->Release();
			}
		}

		d3d9->Release();

	}

	return vTable;
}