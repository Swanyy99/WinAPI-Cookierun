#include "framework.h"
#include "CRenderManager.h"

#include "CCameraManager.h"

#include "WinAPI.h"
#include "CImage.h"

CRenderManager::CRenderManager()
{
	m_pFactory = nullptr;
	m_pRenderTarget = nullptr;
	m_pImageFactory = nullptr;
	m_pWriteFactory = nullptr;

	m_pDefaultBrush = nullptr;
	m_pDefaultTextFormat = nullptr;
	m_pCurBrush = nullptr;
	m_pCurTextFormat = nullptr;
}

CRenderManager::~CRenderManager()
{

}

void CRenderManager::Init()
{
	HRESULT hResult;

	// D2D1Factory 생성
	hResult = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);
	assert(S_OK == hResult && "D2D1Factory Create Failed");

	// 지정한 윈도우의 클라이언트 영역에 그림을 그리기 위한 Render Target을 생성
	hResult = m_pFactory->CreateHwndRenderTarget
	(
		RenderTargetProperties(),
		HwndRenderTargetProperties(
			hWnd,
			SizeU(WINSIZEX, WINSIZEY),
			D2D1_PRESENT_OPTIONS_IMMEDIATELY),
		&m_pRenderTarget
	);
	assert(S_OK == hResult && "HwndRenderTarget Create Failed");

	// WICImagingFactory 생성
	hResult = CoInitialize(nullptr);
	assert(S_OK == hResult && "CoInitialize Failed");

	hResult = CoCreateInstance(CLSID_WICImagingFactory, nullptr,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pImageFactory));
	assert(S_OK == hResult && "ImageFactory Create Failed");

	hResult = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(m_pWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pWriteFactory));
	assert(S_OK == hResult && "WriteFactory Create Failed");

	// 텍스트 포맷 생성
	hResult = m_pWriteFactory->CreateTextFormat(
		L"a피오피동글OL",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		10.f,
		L"ko",
		&m_pDefaultTextFormat);
	assert(S_OK == hResult && "TextFormat Create Failed");

	hResult = m_pDefaultTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	assert(S_OK == hResult && "TextFormat SetAlignment Failed");

	hResult = m_pDefaultTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	assert(S_OK == hResult && "TextFormat SetParagraphAlignment Failed");

	// 브러쉬 생성
	hResult = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.f, 0.f, 0.f), &m_pDefaultBrush);
	assert(S_OK == hResult && "SolidColorBrush Create Failed");

	// 텍스트 포맷 생성
	hResult = m_pWriteFactory->CreateTextFormat(
		L"a피오피동글OL",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		10.f,
		L"ko",
		&m_pCurTextFormat);
	assert(S_OK == hResult && "TextFormat Create Failed");

	hResult = m_pCurTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	assert(S_OK == hResult && "TextFormat SetAlignment Failed");

	hResult = m_pCurTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	assert(S_OK == hResult && "TextFormat SetParagraphAlignment Failed");

	// 브러쉬 생성
	hResult = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.f, 0.f, 0.f), &m_pCurBrush);
	assert(S_OK == hResult && "SolidColorBrush Create Failed");
}

void CRenderManager::BeginDraw()
{
	m_pRenderTarget->BeginDraw();
	Vector screenPos = CAMERA->ScreenToWorldPoint(Vector(0, 0));
	FillRect(screenPos.x, screenPos.y, screenPos.x + WINSIZEX, screenPos.y + WINSIZEY, Color(255, 255, 255, 1.f));
}

void CRenderManager::EndDraw()
{
	m_pRenderTarget->EndDraw();
}

void CRenderManager::Release()
{
	// 마무리는 초기화의 역순으로
	if (nullptr != m_pCurBrush)
	{
		m_pDefaultBrush->Release();
		m_pDefaultBrush = nullptr;
	}
	if (nullptr != m_pCurTextFormat)
	{
		m_pDefaultTextFormat->Release();
		m_pDefaultTextFormat = nullptr;
	}
	if (nullptr != m_pDefaultBrush)
	{
		m_pDefaultBrush->Release();
		m_pDefaultBrush = nullptr;
	}
	if (nullptr != m_pDefaultTextFormat)
	{
		m_pDefaultTextFormat->Release();
		m_pDefaultTextFormat = nullptr;
	}
	if (nullptr != m_pWriteFactory)
	{
		m_pWriteFactory->Release();
		m_pWriteFactory = nullptr;
	}
	if (nullptr != m_pImageFactory)
	{
		m_pImageFactory->Release();
		m_pImageFactory = nullptr;
	}
	if (nullptr != m_pRenderTarget)
	{
		m_pRenderTarget->Release();
		m_pRenderTarget = nullptr;
	}
	if (nullptr != m_pFactory)
	{
		m_pFactory->Release();
		m_pFactory = nullptr;
	}
}

void CRenderManager::SetBrush(Color color)
{
	m_pDefaultBrush->SetColor(D2D1::ColorF(
		(FLOAT)color.r / 255.f,
		(FLOAT)color.g / 255.f,
		(FLOAT)color.b / 255.f,
		color.a)
	);
}

void CRenderManager::SetTextFormat(wstring fontName, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, wstring localeName)
{
	HRESULT hResult;

	DWRITE_TEXT_ALIGNMENT textAlignment = m_pDefaultTextFormat->GetTextAlignment();
	DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment = m_pDefaultTextFormat->GetParagraphAlignment();

	if (nullptr != m_pDefaultTextFormat)
	{
		m_pDefaultTextFormat->Release();
		m_pDefaultTextFormat = nullptr;
	}

	hResult = m_pWriteFactory->CreateTextFormat(
		fontName.c_str(),
		NULL,
		fontWeight,
		fontStyle,
		fontStretch,
		fontSize,
		localeName.c_str(),
		&m_pDefaultTextFormat
	);
	assert(S_OK == hResult && "TextFormat Create Failed");

	hResult = m_pDefaultTextFormat->SetTextAlignment(textAlignment);
	assert(S_OK == hResult && "TextFormat SetAlignment Failed");

	hResult = m_pDefaultTextFormat->SetParagraphAlignment(paragraphAlignment);
	assert(S_OK == hResult && "TextFormat SetParagraphAlignment Failed");
}

void CRenderManager::SetTextAlignment(DWRITE_TEXT_ALIGNMENT textAlignment)
{
	HRESULT hResult = m_pDefaultTextFormat->SetTextAlignment(textAlignment);
	assert(S_OK == hResult && "TextFormat SetAlignment Failed");
}

void CRenderManager::SetTextParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment)
{
	HRESULT hResult = m_pDefaultTextFormat->SetParagraphAlignment(paragraphAlignment);
	assert(S_OK == hResult && "TextFormat SetParagraphAlignment Failed");
}

void CRenderManager::Text(wstring str, float startX, float startY, float endX, float endY)
{
	Vector start = CAMERA->WorldToScreenPoint(Vector(startX, startY));
	startX = start.x;
	startY = start.y;
	Vector end = CAMERA->WorldToScreenPoint(Vector(endX, endY));
	endX = end.x;
	endY = end.y;

	D2D1_RECT_F rect = { startX, startY, endX, endY };
	m_pRenderTarget->DrawTextW(str.c_str(), (UINT32)str.size(), m_pDefaultTextFormat,
		rect, m_pDefaultBrush);
}

void CRenderManager::Text(wstring str, float startX, float startY, float endX, float endY, Color color, float fontSize)
{
	Vector start = CAMERA->WorldToScreenPoint(Vector(startX, startY));
	startX = start.x;
	startY = start.y;
	Vector end = CAMERA->WorldToScreenPoint(Vector(endX, endY));
	endX = end.x;
	endY = end.y;

	D2D1_RECT_F rect = { startX, startY, endX, endY };

	if (m_pCurTextFormat->GetFontSize() != fontSize)
	{
		HRESULT hResult;

		WCHAR fontFamilyName[255];
		m_pDefaultTextFormat->GetFontFamilyName(fontFamilyName, 255);
		WCHAR localeName[255];
		m_pDefaultTextFormat->GetLocaleName(localeName, 255);

		m_pCurTextFormat->Release();
		hResult = m_pWriteFactory->CreateTextFormat(
			fontFamilyName,
			NULL,
			m_pDefaultTextFormat->GetFontWeight(),
			m_pDefaultTextFormat->GetFontStyle(),
			m_pDefaultTextFormat->GetFontStretch(),
			fontSize,
			localeName,
			&m_pCurTextFormat);
		assert(S_OK == hResult && "TextFormat Create Failed");

		hResult = m_pCurTextFormat->SetTextAlignment(m_pDefaultTextFormat->GetTextAlignment());
		assert(S_OK == hResult && "TextFormat SetAlignment Failed");

		hResult = m_pCurTextFormat->SetParagraphAlignment(m_pDefaultTextFormat->GetParagraphAlignment());
		assert(S_OK == hResult && "TextFormat SetParagraphAlignment Failed");
	}

	m_pCurBrush->SetColor(D2D1::ColorF(
		(FLOAT)color.r / 255.f,
		(FLOAT)color.g / 255.f,
		(FLOAT)color.b / 255.f,
		color.a));
	m_pRenderTarget->DrawTextW(str.c_str(), (UINT32)str.size(), m_pCurTextFormat,
		rect, m_pCurBrush);
}

void CRenderManager::Line(Vector startPoint, Vector endPoint)
{
	startPoint = CAMERA->WorldToScreenPoint(startPoint);
	endPoint = CAMERA->WorldToScreenPoint(endPoint);

	D2D1_POINT_2F start = { startPoint.x, startPoint.y };
	D2D1_POINT_2F end = { endPoint.x, endPoint.y };

	m_pRenderTarget->DrawLine(start, end, m_pDefaultBrush, 1.f);
}

void CRenderManager::Line(Vector startPoint, Vector endPoint, Color color, float strokeWidth)
{
	startPoint = CAMERA->WorldToScreenPoint(startPoint);
	endPoint = CAMERA->WorldToScreenPoint(endPoint);

	D2D1_POINT_2F start = { startPoint.x, startPoint.y };
	D2D1_POINT_2F end = { endPoint.x, endPoint.y };

	m_pCurBrush->SetColor(D2D1::ColorF(
		(FLOAT)color.r / 255.f,
		(FLOAT)color.g / 255.f,
		(FLOAT)color.b / 255.f,
		color.a));
	m_pRenderTarget->DrawLine(start, end, m_pCurBrush, strokeWidth);
}

void CRenderManager::FrameRect(float startX, float startY, float endX, float endY)
{
	Vector start = CAMERA->WorldToScreenPoint(Vector(startX, startY));
	startX = start.x;
	startY = start.y;
	Vector end = CAMERA->WorldToScreenPoint(Vector(endX, endY));
	endX = end.x;
	endY = end.y;

	D2D1_RECT_F rect = { startX, startY, endX, endY };
	m_pRenderTarget->DrawRectangle(rect, m_pDefaultBrush, 1.f);
}

void CRenderManager::FrameRect(float startX, float startY, float endX, float endY, Color color, float strokeWidth)
{
	Vector start = CAMERA->WorldToScreenPoint(Vector(startX, startY));
	startX = start.x;
	startY = start.y;
	Vector end = CAMERA->WorldToScreenPoint(Vector(endX, endY));
	endX = end.x;
	endY = end.y;

	D2D1_RECT_F rect = { startX, startY, endX, endY };

	m_pCurBrush->SetColor(D2D1::ColorF(
		(FLOAT)color.r / 255.f,
		(FLOAT)color.g / 255.f,
		(FLOAT)color.b / 255.f,
		color.a));
	m_pRenderTarget->DrawRectangle(rect, m_pCurBrush, strokeWidth);
}

void CRenderManager::FillRect(float startX, float startY, float endX, float endY)
{
	Vector start = CAMERA->WorldToScreenPoint(Vector(startX, startY));
	startX = start.x;
	startY = start.y;
	Vector end = CAMERA->WorldToScreenPoint(Vector(endX, endY));
	endX = end.x;
	endY = end.y;

	D2D1_RECT_F rect = { startX, startY, endX, endY };
	m_pRenderTarget->FillRectangle(rect, m_pDefaultBrush);
}

void CRenderManager::FillRect(float startX, float startY, float endX, float endY, Color color)
{
	Vector start = CAMERA->WorldToScreenPoint(Vector(startX, startY));
	startX = start.x;
	startY = start.y;
	Vector end = CAMERA->WorldToScreenPoint(Vector(endX, endY));
	endX = end.x;
	endY = end.y;

	D2D1_RECT_F rect = { startX, startY, endX, endY };

	m_pCurBrush->SetColor(D2D1::ColorF(
		(FLOAT)color.r / 255.f,
		(FLOAT)color.g / 255.f,
		(FLOAT)color.b / 255.f,
		color.a));
	m_pRenderTarget->FillRectangle(rect, m_pCurBrush);
}

void CRenderManager::FrameEllipse(float startX, float startY, float endX, float endY)
{
	Vector start = CAMERA->WorldToScreenPoint(Vector(startX, startY));
	startX = start.x;
	startY = start.y;
	Vector end = CAMERA->WorldToScreenPoint(Vector(endX, endY));
	endX = end.x;
	endY = end.y;

	D2D1_ELLIPSE ellipse = {
		(startX + endX) * 0.5f,
		(startY + endY) * 0.5f,
		abs(startX - endX) * 0.5f,
		abs(startY - endY) * 0.5f
	};
	m_pRenderTarget->DrawEllipse(ellipse, m_pDefaultBrush, 1.f);
}

void CRenderManager::FrameEllipse(float startX, float startY, float endX, float endY, Color color, float strokeWidth)
{
	Vector start = CAMERA->WorldToScreenPoint(Vector(startX, startY));
	startX = start.x;
	startY = start.y;
	Vector end = CAMERA->WorldToScreenPoint(Vector(endX, endY));
	endX = end.x;
	endY = end.y;

	D2D1_ELLIPSE ellipse = {
		(startX + endX) * 0.5f,
		(startY + endY) * 0.5f,
		abs(startX - endX) * 0.5f,
		abs(startY - endY) * 0.5f
	};

	m_pCurBrush->SetColor(D2D1::ColorF(
		(FLOAT)color.r / 255.f,
		(FLOAT)color.g / 255.f,
		(FLOAT)color.b / 255.f,
		color.a));
	m_pRenderTarget->DrawEllipse(ellipse, m_pCurBrush, strokeWidth);
}

void CRenderManager::FillEllipse(float startX, float startY, float endX, float endY)
{
	Vector start = CAMERA->WorldToScreenPoint(Vector(startX, startY));
	startX = start.x;
	startY = start.y;
	Vector end = CAMERA->WorldToScreenPoint(Vector(endX, endY));
	endX = end.x;
	endY = end.y;

	D2D1_ELLIPSE ellipse = {
		(startX + endX) * 0.5f,
		(startY + endY) * 0.5f,
		abs(startX - endX) * 0.5f,
		abs(startY - endY) * 0.5f
	};
	m_pRenderTarget->FillEllipse(ellipse, m_pDefaultBrush);
}

void CRenderManager::FillEllipse(float startX, float startY, float endX, float endY, Color color)
{
	Vector start = CAMERA->WorldToScreenPoint(Vector(startX, startY));
	startX = start.x;
	startY = start.y;
	Vector end = CAMERA->WorldToScreenPoint(Vector(endX, endY));
	endX = end.x;
	endY = end.y;

	D2D1_ELLIPSE ellipse = {
		(startX + endX) * 0.5f,
		(startY + endY) * 0.5f,
		abs(startX - endX) * 0.5f,
		abs(startY - endY) * 0.5f
	};

	m_pCurBrush->SetColor(D2D1::ColorF(
		(FLOAT)color.r / 255.f,
		(FLOAT)color.g / 255.f,
		(FLOAT)color.b / 255.f,
		color.a));
	m_pRenderTarget->FillEllipse(ellipse, m_pCurBrush);
}

void CRenderManager::FrameCircle(float pointX, float pointY, float radius)
{
	Vector point = CAMERA->WorldToScreenPoint(Vector(pointX, pointY));
	pointX = point.x;
	pointY = point.y;

	D2D1_ELLIPSE ellipse = { pointX, pointY, radius, radius };
	m_pRenderTarget->DrawEllipse(ellipse, m_pDefaultBrush, 1.f);
}

void CRenderManager::FrameCircle(float pointX, float pointY, float radius, Color color, float strokeWidth)
{
	Vector point = CAMERA->WorldToScreenPoint(Vector(pointX, pointY));
	pointX = point.x;
	pointY = point.y;

	D2D1_ELLIPSE ellipse = { pointX, pointY, radius, radius };

	m_pCurBrush->SetColor(D2D1::ColorF(
		(FLOAT)color.r / 255.f,
		(FLOAT)color.g / 255.f,
		(FLOAT)color.b / 255.f,
		color.a));
	m_pRenderTarget->DrawEllipse(ellipse, m_pCurBrush, strokeWidth);
}

void CRenderManager::FillCircle(float pointX, float pointY, float radius)
{
	Vector point = CAMERA->WorldToScreenPoint(Vector(pointX, pointY));
	pointX = point.x;
	pointY = point.y;

	D2D1_ELLIPSE ellipse = { pointX, pointY, radius, radius };
	m_pRenderTarget->FillEllipse(ellipse, m_pDefaultBrush);
}

void CRenderManager::FillCircle(float pointX, float pointY, float radius, Color color)
{
	Vector point = CAMERA->WorldToScreenPoint(Vector(pointX, pointY));
	pointX = point.x;
	pointY = point.y;

	D2D1_ELLIPSE ellipse = { pointX, pointY, radius, radius };

	m_pCurBrush->SetColor(D2D1::ColorF(
		(FLOAT)color.r / 255.f,
		(FLOAT)color.g / 255.f,
		(FLOAT)color.b / 255.f,
		color.a));
	m_pRenderTarget->FillEllipse(ellipse, m_pCurBrush);
}

void CRenderManager::Image(CImage* pImg, float startX, float startY, float endX, float endY, float alpha)
{
	Vector start = CAMERA->WorldToScreenPoint(Vector(startX, startY));
	startX = start.x;
	startY = start.y;
	Vector end = CAMERA->WorldToScreenPoint(Vector(endX, endY));
	endX = end.x;
	endY = end.y;

	D2D1_RECT_F imgRect = { startX, startY, endX, endY };
	m_pRenderTarget->DrawBitmap(pImg->GetImage(), imgRect);
}

void CRenderManager::FrameImage(CImage* pImg, float dstX, float dstY, float dstW, float dstH, float srcX, float srcY, float srcW, float srcH, float alpha)
{
	Vector dstStart = CAMERA->WorldToScreenPoint(Vector(dstX, dstY));
	dstX = dstStart.x;
	dstY = dstStart.y;
	Vector dstEnd = CAMERA->WorldToScreenPoint(Vector(dstW, dstH));
	dstW = dstEnd.x;
	dstH = dstEnd.y;

	D2D1_RECT_F imgRect = { dstX, dstY, dstW, dstH };
	D2D1_RECT_F srcRect = { srcX, srcY, srcW, srcH };

	m_pRenderTarget->DrawBitmap(pImg->GetImage(), imgRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcRect);
}

IWICImagingFactory* CRenderManager::GetImageFactory()
{
	return m_pImageFactory;
}

ID2D1HwndRenderTarget* CRenderManager::GetRenderTarget()
{
	return m_pRenderTarget;
}

