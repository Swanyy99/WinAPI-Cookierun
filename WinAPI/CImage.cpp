#include "framework.h"
#include "CImage.h"

#include "CRenderManager.h"

CImage::CImage()
{
	m_pBitmap = nullptr;
}

CImage::~CImage()
{
	if (nullptr != m_pBitmap)
		m_pBitmap->Release();
	m_pBitmap = nullptr;
}

ID2D1Bitmap* CImage::GetImage()
{
	return m_pBitmap;
}

int CImage::GetWidth()
{
	return (int)m_pBitmap->GetSize().width;
}

int CImage::GetHeight()
{
	return (int)m_pBitmap->GetSize().height;
}

void CImage::Load(const wstring& filePath)
{
	HRESULT hResult;

	IWICBitmapDecoder*		p_decoder;		// 압축된 이미지를 해제할 객체
	IWICBitmapFrameDecode*	p_frame;		// 특정 그림을 선택한 객체
	IWICFormatConverter*	p_converter;	// 이미지 변환 객체

	// WIC용 Factory 객체를 사용하여 이미지 압축 해제를 위한 객체를 생성
	hResult = RENDER->GetImageFactory()->CreateDecoderFromFilename(filePath.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &p_decoder);
	assert(S_OK == hResult && "Decoder Create Failed");

	// 파일을 구성하는 이미지 중에서 첫번째 이미지를 선택
	hResult = p_decoder->GetFrame(0, &p_frame);
	assert(S_OK == hResult && "Decoder GetFrame Failed");
	
	// IWICBitmap형식의 비트맵을 ID2D1Bitmap. 형식으로 변환하기 위한 객체 생성
	hResult = RENDER->GetImageFactory()->CreateFormatConverter(&p_converter);
	assert(S_OK == hResult && "Format Convert Failed");

	// 선택된 그림을 어떤 형식의 비트맵으로 변환할 것인지 설정
	hResult = p_converter->Initialize(p_frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);
	assert(S_OK == hResult && "Converter Initialize Failed");

	// IWICBitmap 형식의 비트맵으로 ID2D1Bitmap 객체를 생성
	hResult = RENDER->GetRenderTarget()->CreateBitmapFromWicBitmap(p_converter, NULL, &m_pBitmap);
	assert(S_OK == hResult && "Bitmap Create Failed");

	p_converter->Release();		// 이미지 변환 객체 제거
	p_frame->Release();			// 그림파일에 있는 이미지를 선택하기 위해 사용한 객체 제거
	p_decoder->Release();		// 압축을 해제하기 위해 생성한 객체 제거
}